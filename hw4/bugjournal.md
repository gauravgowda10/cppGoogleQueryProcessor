# Bug 1

## A) How is your program acting differently than you expect it to?
- Segmentation fault in ServerSocket.cc

## B) Brainstorm a few possible causes of the bug
- Forgetting to free something
- Casting issue
- 

## C) How you fixed the bug and why the fix was necessary
- `getaddrinfo()` expects its port number argument to be a `char*`. Since a ServerSocket class' port number is stored as a `uint16_t`, I was trying to convert it to a `char*` with `char* port = reintepret_cast<char*>(port_)`. This line was causing the segmentation fault becuse I needed to be casting the address of `port_`, not the value itself. The issue was fixed when I changed the line to `char* port = reintepret_cast<char*>(&port_)`.


# Bug 2

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 


# Bug 3

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 
