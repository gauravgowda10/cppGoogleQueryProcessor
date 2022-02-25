# Bug 1

## A) How is your program acting differently than you expect it to?
- Segmentation fault in WriteDocIDToPositionListFn()

## B) Brainstorm a few possible causes of the bug
- Not truncating to 32 bits correctly
- Not using casting correctly, using reintepret_cast<> in the wrong context
- The issue seems to happen when I use LLIterator_Get()

## C) How you fixed the bug and why the fix was necessary
- I had to completely change the way I was setting the `position` field in the for loop. I first reintepret_casted the retrieved payload into a generic 
intptr_t so it would be the same size as the LLPayload. Once it was a generic pointer, I static_casted it to a DocPositionOffset_t, since those are 32-bit ints. The segmentation fault went away with these changes.

# Bug 2

## A) How is your program acting differently than you expect it to?
- WriteIndex.cc test not passing, incorrect values returned by fileIndexChecker()

## B) Brainstorm a few possible causes of the bug
- Incorrect read/write, maybe forgot to fseek() correctly?

## C) How you fixed the bug and why the fix was necessary
- We forgot to convert headers to disk format in many of the functions. Simple error but we overlooked it early on. Calling ToDiskFormat() on each header fixed the problem.

# Bug 3

## A) How is your program acting differently than you expect it to?
- filesearchshell() is not case insensitive when it should be

## B) Brainstorm a few possible causes of the bug
- Something to do with how we are converting strings to lowercase, since the function works in general

## C) How you fixed the bug and why the fix was necessary
- Instead of using pointers to strings in our toLowerCase implementation, we used const references and returned a new string each time. This way, the user input is always being converted to lowercase before we conduct the search.
