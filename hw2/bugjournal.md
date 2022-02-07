# Bug 1

## A) How is your program acting differently than you expect it to?
- In FileParser.c, my DocTable_GetDocID() is not returning the correct document ID
- Instead of returning 1, it is returning a random > 10000 value that changes with each run

## B) Brainstorm a few possible causes of the bug
- The issue is definitely in the GetDocID() function and not the Add() function
because tests that involve adding new key/values to the hashtable are passing
- I think the issue has something to do with casting since the GetDocID() function
is very simple in its implementation

## C) How you fixed the bug and why the fix was necessary
- Instead of returning (DocID_t) kv.value, I realized I needed to cast like
\*(DocID_t*) kv.value instead. This is because HTValue_t (the type of kv.value)
is defined as a void*. I need to first cast kv.value as a pointer and then dereference it.
This issue popped up in my Add() function as well, but once I made these changes I passed
all the tests.


# Bug 2

## A) How is your program acting differently than you expect it to?
- My readdir() loop inside the CrawlFileTree.c HandleDir() function 
is not updating the array of entries correctly, resulting in memory leaks and incorrect files being passed to HandleFile()

## B) Brainstorm a few possible causes of the bug
- Since I am using a while loop, I must be incrementing/dealing with the 'i' counter incorrectly. 

## C) How you fixed the bug and why the fix was necessary
- I was not properly updating the i value. There were numerous conditionals where i should not have been updated, 
so I fixed my while loop logic to only update i at the end when we are sure the next entry can be processed.


# Bug 3

## A) How is your program acting differently than you expect it to?
- Segmentation fault in MemIndex.c MemIndex_Search() function on line 244.

## B) Brainstorm a few possible causes of the bug
- Payload not getting free'd?
- Something to do with the SearchResult struct
- 

## C) How you fixed the bug and why the fix was necessary
- I was incorrectly casting the SearchResult* result to (LLPayload_t) 
when I really should have been storing a pointer to it as (LLPayload_t*) &result. 
I neglected read the description of the LLPayload_t type definition. In this case 
it makes more sense to be storing a pointer to my struct pointer and not the struct pointer itself.


# Bug 4

## A) How is your program acting differently than you expect it to?
- Certain input when I entered queries to the searchshell class would not work.
No Error would be thrown, but nothing would be outputed.

## B) Brainstorm a few possible causes of the bug
- When I split the queries into multiple words, we could possibly be changing the 
words.
- The query input is not in the correct form (i.e. Capitilization, spaces, etc.)
- Incorrectly changing the end of line character, so the last word is not 
being saved correctly

## C) How you fixed the bug and why the fix was necessary
- After, I split the query into different words, we printed out these words.
We noticed that only the words with capitalized letters were having this issue,
so we changed all letters to lowercase when we split the query into words.



