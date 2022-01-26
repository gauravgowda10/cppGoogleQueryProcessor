/*
 * Copyright ©2022 Arjun Srivastava & Gaurav Gowda. All rights reserved.
 * UW Email: arj1@uw.edu & ggowda@uw.edu
 */

#include "ro_file.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


/*** INTERNAL DATA TYPES AND CONSTANTS **************************************/

static const int RO_FILE_BUF_LEN = 512;  // do not modify

struct ro_file_st {
  int fd;         // The file descriptor we are currently managing.

  char* buf;      // Pointer to our internal buffer for this file.

  off_t buf_pos;  // The position in the file that the beginning of our
                  // internal buffer currently corresponds to.

  int buf_index;  // The index in our internal buffer that corresponds to the
                  // user's current position in the file.

  int buf_end;    // How many bytes currently in our internal buffer are
                  // actually from the file.
                  // To understand why this is important to track, consider
                  // the case when the file length is < RO_FILE_BUF_LEN.
};


/*** STATIC HELPER FUNCTION DECLARATIONS ************************************/

// Copy up to 'amount' bytes from the RO_FILE's internal buffer to 'out'.
// Returns the number of bytes copied.
static size_t flush_buffer(RO_FILE* file, char* out, int amount);

// Fill in the RO_FILE's internal buffer with as many bytes as can be read
// from the file.
// Returns the number of bytes copied into the buffer, or -1 on any error.
static ssize_t fill_buffer(RO_FILE* file);


/*** FUNCTION DEFINITIONS ***************************************************/

RO_FILE *ro_open(char *filename) {
  // 1. Allocate a new RO_FILE
  if (filename == NULL) {
    return NULL;
  }
  RO_FILE* file = (RO_FILE*) malloc(sizeof(RO_FILE));

  // 2. Get the file descriptor for the file
  file->fd = open(filename, O_RDONLY);
  if (file->fd == -1) {
    perror("Could not open file");
    return NULL;
  }

  // 3. Allocate the internal buffer
  char* int_buff = (char*) malloc(sizeof(char) * RO_FILE_BUF_LEN);

  if (int_buff == NULL) {
    return NULL;
  }
  file->buf = int_buff;

  // 4. Initialize the other fields (no reading done yet)
  file->buf_pos = 0;
  file->buf_index = 0;
  file->buf_end = 0;

  return file;
}

// THIS FUNCTION IS COMPLETED FOR YOU
ssize_t ro_read(char *ptr, size_t len, RO_FILE *file) {
  // 1. If we have bytes in our internal buffer, flush as many as we can to
  //    'ptr'.
  size_t num_copied_out = flush_buffer(file, ptr, len);

  while (num_copied_out != len) {
    // 2. If we haven't provided the bytes requested, repopulate our buffer
    //    with bytes from the file.
    ssize_t num_filled = fill_buffer(file);
    if (num_filled == 0) {
      // reached EOF; no more bytes to copy
      break;
    } else if (num_filled < 0) {
      // pass error back to client
      return num_filled;
    }

    // 3. Copy filled bytes into 'ptr'.
    num_copied_out += flush_buffer(file, ptr+num_copied_out,
                                   len-num_copied_out);

    // 4. Repeat steps 2-3 until request is fulfilled.
  }

  return num_copied_out;
}

off_t ro_tell(RO_FILE *file) {
  if (file == NULL) {
    return -1;
  }
  // Get the current offset into the file
  return file->buf_pos + file->buf_index;
}

int ro_seek(RO_FILE *file, off_t offset, int whence) {
  // 1. Check validity of arguments, where applicable.
  if (file == NULL || file->buf == NULL || file->fd == -1) {
    return 1;
  }

  if (whence != SEEK_SET && whence != SEEK_END && whence != SEEK_CUR) {
    return 1;
  }

  // 2. Seek to specified offset from specified whence using lseek.
  //    No need to check if new position is already in our buffer.
  file->buf_pos = lseek(file->fd, offset, whence);
  if (file->buf_pos == -1) {
    return 1;
  }


  // 3. Update our buffer indicators
  file->buf_index = 0;
  file->buf_end = 0;

  return 0;
}

int ro_close(RO_FILE *file) {
  // Clean up all RO_FILE resources, returns non-zero on error
  if (file == NULL) {
    return -1;
  }
  // clean up resources,
  // return non 0 on error
  int res = close(file->fd);
  free(file->buf);
  free(file);
  return res;
}

/*** STATIC HELPER FUNCTION DEFINITIONS *************************************/

size_t flush_buffer(RO_FILE *file, char *out, int amount) {
  if (file == NULL || out == NULL) {
    return 0;
  }

  // 1. Copy/flush bytes to 'out' starting from the buffer index. The amount
  //    flushed should be the min of 'amount' and the remaining unflushed bytes
  //    in the buffer.
  int bytes_flushed = 0;
  int remaining_bytes_unflushed = file->buf_end - file->buf_index;
  while (bytes_flushed < remaining_bytes_unflushed && bytes_flushed < amount) {
    out[bytes_flushed] = file->buf[file->buf_index + bytes_flushed];
    bytes_flushed++;
    remaining_bytes_unflushed = file->buf_end - file->buf_index;
  }

  // 2. Advance buffer index by the number of bytes flushed.
  file->buf_index += bytes_flushed;

  // 3. Return the number of bytes flushed.
  return bytes_flushed;
}

ssize_t fill_buffer(RO_FILE *file) {
  // NOTES:
  // - For maximum buffering benefit, we are "resetting" the buffer and then
  //   filling it with as much file data as possible, starting from the current
  //   file position -- how does this change the buffer indicators?
  // - For simplicity, you should ignore any unflushed bytes that started in
  //   the buffer (i.e., it's okay to re-read them from the file).
  // - You will need to implement a POSIX read loop with all appropriate
  //   return value checking.
  if (file == NULL) {
    return -1;
  }
  // reset buf_index, buf_pos, and buf_end
  file->buf_pos += file->buf_index;
  file->buf_index = 0;
  file->buf_end = 0;
  int bytes_buffered = 0;

  do {
    ssize_t result = read(file->fd, (file->buf) + bytes_buffered,
    RO_FILE_BUF_LEN - bytes_buffered);
    // reached the end of file
    if (result == 0) {
      break;
    } else if (result < 0 && (errno == EINTR || errno == EAGAIN)) {
       // reached error, check for error code
        continue;
    } else if (errno == EINTR || errno == EAGAIN) {
      return result;
    }
    bytes_buffered += result;
  } while (bytes_buffered < RO_FILE_BUF_LEN);

  // update buffer status
  file->buf_end = bytes_buffered;
  return bytes_buffered;
}

