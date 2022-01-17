# Bug 1

## A) How is your program acting differently than you expect it to?
- LinkedList_Pop is not correctly setting the payload pointer

## B) Brainstorm a few possible causes of the bug
- I don't fully understand when to use addresses (&), and I think I am using them incorrectly here
- &pointer would return the address of the pointer itself, so I don't want to be using the value like that.

## C) How you fixed the bug and why the fix was necessary
- I had to dereference the payload pointer before setting it equal to the nodes payload. This is because I am supposed to be setting the value of the pointer to the node's payload value, and not the address.


# Bug 2

## A) How is your program acting differently than you expect it to?
- The LLIterator_Remove() method is not correctly updating the pointers to iter->node and the head of the LinkedList

## B) Brainstorm a few possible causes of the bug
- It seems to be one full pointer address off, so I assume this issue is due to how I am updating the various pointers.
- I verified that there is a pointer that points to the correct address, so I must be setting them in the wrong order.

## C) How you fixed the bug and why the fix was necessary
- While attempting to set the pointers to the nodes before and after the node to be removed, I had
updated the next and previous nodes in the incorrect order. This was causing the output pointer to point
to the node' next next node instead, and fixing the order solving my issue.


# Bug 3

## A) How is your program acting differently than you expect it to?
- Segmentation fault in my HTIterator_Get() function

## B) Brainstorm a few possible causes of the bug
- I think there must be a stray pointer somewhere that is pointing to data that was free'd by the test suite.
- 
- 

## C) How you fixed the bug and why the fix was necessary
- Turns out I was using LLIterator_Get() incorrectly. HTIterator_Get() has an output parameter, "*keyvalue", which is supposed to point to a copy of the gotten payload. I was using LLIterator_Get() to make keyvalue POINT to the payload, when in reality I needed to dereference keyvalue and set it equal to the dereferenced result from LLIterator_Get(). Now, keyvalue isn't concerned with the payload's address, and the memory leak was fixed.
