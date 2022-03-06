/*
 * Copyright ©2022 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int* const listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd"
  // and set the ServerSocket data member "listen_sock_fd_"

  // Populate the "hints" addrinfo structure for getaddrinfo().
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = ai_family;       // IPv6 (also handles IPv4 clients)
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;      // use wildcard "in6addr_any" address
  hints.ai_flags |= AI_V4MAPPED;    // use v4-mapped v6 if no v6 found
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  struct addrinfo* result;

  std::string port = std::to_string(port_);

  int res = getaddrinfo(nullptr, port.c_str(), &hints, &result);

  if (res != 0) {
    return false;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  int fd = -1;
  for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
    fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      sock_family_ = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(fd);
    fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (fd == -1)
    return false;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(fd, SOMAXCONN) != 0) {
    close(fd);
    return false;
  }

  // Return to the client the listening file descriptor.
  *listen_fd = fd;
  listen_sock_fd_ = fd;
  return true;
}

bool ServerSocket::Accept(int* const accepted_fd,
                          std::string* const client_addr,
                          uint16_t* const client_port,
                          std::string* const client_dns_name,
                          std::string* const server_addr,
                          std::string* const server_dns_name) const {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  struct sockaddr_storage caddr;
  struct sockaddr *sock_addr = reinterpret_cast<struct sockaddr *>(&caddr);
  socklen_t caddr_len = sizeof(caddr);
  int client_fd;

  while (1) {
    client_fd = accept(listen_sock_fd_,
                           sock_addr,
                           &caddr_len);

    // Try again if recoverable error
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      return false;
    }
    break;
  }
  *accepted_fd = client_fd;

  // For IPV4
  if (sock_addr->sa_family == AF_INET) {
    char ipstring[INET_ADDRSTRLEN];
    struct sockaddr_in* v4addr =
            reinterpret_cast<struct sockaddr_in*>(sock_addr);\
    // Get client IP addr
    inet_ntop(AF_INET,
              &(v4addr->sin_addr),
              ipstring,
              INET_ADDRSTRLEN);
  *client_addr = std::string(ipstring);
  *client_port = ntohs(v4addr->sin_port);
  // For IPV6
  } else if (sock_addr->sa_family == AF_INET6) {
    char ipstring[INET6_ADDRSTRLEN];
    struct sockaddr_in6* v6addr =
            reinterpret_cast<struct sockaddr_in6*>(sock_addr);\
    // Get client IP addr
    inet_ntop(AF_INET6,
              &(v6addr->sin6_addr),
              ipstring,
              INET6_ADDRSTRLEN);
  *client_addr = std::string(ipstring);
  *client_port = ntohs(v6addr->sin6_port);
  }

  // Get client DNS name
  char dns_name[256];

  if (getnameinfo(sock_addr, caddr_len, dns_name,
      256, nullptr, 0, 0) != 0) {
    // If lookup failes, use client address as substitute
    *client_dns_name = *client_addr;
    return false;
  } else {
    *client_dns_name = std::string(dns_name);
  }

  // Get server address and DNS name

  char hname[1024];

  if (sock_family_ == AF_INET) {
    // For IPV4
    struct sockaddr_in srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET_ADDRSTRLEN];
    getsockname(client_fd,
                reinterpret_cast<struct sockaddr*>(&srvr),
                &srvrlen);
    inet_ntop(AF_INET, &srvr.sin_addr, addrbuf, INET_ADDRSTRLEN);
    getnameinfo(reinterpret_cast<struct sockaddr*>(&srvr),
                srvrlen, hname, 1024, nullptr, 0, 0);
    *server_dns_name = std::string(hname);
    *server_addr = std::string(addrbuf);
  } else {
    // For IPV6.
    struct sockaddr_in6 srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET6_ADDRSTRLEN];
    getsockname(client_fd,
                reinterpret_cast<struct sockaddr*>(&srvr),
                &srvrlen);
    inet_ntop(AF_INET6, &srvr.sin6_addr, addrbuf, INET6_ADDRSTRLEN);
    getnameinfo(reinterpret_cast<struct sockaddr*>(&srvr),
                srvrlen, hname, 1024, nullptr, 0, 0);
    *server_dns_name = std::string(hname);
    *server_addr = std::string(addrbuf);
  }

  return true;
}

}  // namespace hw4
