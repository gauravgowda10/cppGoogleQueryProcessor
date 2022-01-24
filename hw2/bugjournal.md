# Bug 1

## A) How is your program acting differently than you expect it to?
- In FileParser.c, my DocTable_GetDocID() is not returning the correct document ID
- Instead of returning 1, it is returning a random > 10000 value that changes with each run

## B) Brainstorm a few possible causes of the bug
- The issue is definitely in the GetDocID() function and not the Add() function
because tests that involve adding new key/values to the hashtable are passing
- I think the issue has something to do with casting since the GetDocID() function
is very simple in its implementation
- 

## C) How you fixed the bug and why the fix was necessary
- Instead of returning ()


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
