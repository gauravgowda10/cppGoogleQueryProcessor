# Bug 1

## A) How is your program acting differently than you expect it to?
- Segmentation fault in ServerSocket.cc

## B) Brainstorm a few possible causes of the bug
- Forgetting to free something
- Casting issue
- 

## C) How you fixed the bug and why the fix was necessary
- `getaddrinfo()` expects its port number argument to be a `char*`. Since a ServerSocket class' port number is stored as a `uint16_t`, I was trying to convert it to a `char*` with `char* port = reintepret_cast<char*>(port_)`. This line was causing the segmentation fault becuse I needed to be casting the address of `port_`, not the value itself. The issue was fixed when I changed the line to `char* port = reintepret_cast<char*>(&port_)`. This did not solve my overall issue, however, which was getting a `char*` from the `uint16-t`. To fix this, I used strings and the `c_str()` function.


# Bug 2

## A) How is your program acting differently than you expect it to?
- `IsPathSafe()` is failing the last test 

## B) Brainstorm a few possible causes of the bug
- I didn't consider the case where the root path and the file path are identical for the entire length of the root path, but not for the rest of the file path.
- For example, my function will return true for root = "test_dir/ok" and file = "test_dir/ok_but_not_really" because it doesn't consider that the file path of "ok_not_really" differs from just "ok/"

## C) How you fixed the bug and why the fix was necessary
- I added another condition to my function. If we are done checking the root path against the file path, we need to make sure that the next character in the file path is a "/". If it is not, then that means the file path is different and we should return false.


# Bug 3

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 
