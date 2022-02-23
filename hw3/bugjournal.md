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
