# Bug 1

## A) How is your program acting differently than you expect it to?
- LinkedList_Pop is not correctly setting the payload pointer
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- I had to dereference the payload pointer before setting it equal to the nodes payload. This is because I am supposed to be setting the value of the pointer to the node's payload value, and not the address.


# Bug 2

## A) How is your program acting differently than you expect it to?
- The LLIterator_Remove() method is not correctly updating the pointers to iter->node and the head of the LinkedList

## B) Brainstorm a few possible causes of the bug
- It seems to be one full pointer address off, so I assume this issue is due to how I am updating the various pointers.
- 
- 

## C) How you fixed the bug and why the fix was necessary
- The order of how I was setting 


# Bug 3

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 
