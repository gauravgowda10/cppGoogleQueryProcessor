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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

// Buffer Size
#define INPUT_BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);

//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.

  // Step 1: Crawl from a directory provided by argv[1] to produce and index
  DocTable* table;
  MemIndex* index;
  if (!CrawlFileTree(argv[1], &table, &index)) {
    fprintf(stderr, "Incorrect Crawl File Tree");
    Usage();
  }

  Verify333(table != NULL);
  Verify333(index != NULL);

  // Step 2: Prompt the user for a query and
  // read the query from stdin, in a loop
  LinkedList* documents;
  LLIterator* iterator;
  SearchResult* searchResult;

  char input[INPUT_BUFFER_SIZE];
  char* token;
  char* ptr;

  printf("Indexing '%s'\n", argv[1]);

  while (true) {
    printf("enter query: \n");
    if (fgets(input, INPUT_BUFFER_SIZE, stdin) == NULL) {
      break;
    }
    char** query = (char**) malloc(INPUT_BUFFER_SIZE * sizeof(char**));
    Verify333(query != NULL);

    // Step 3: Split a query into words (check out strtok_r)
    // adjust copy to lowercase
    unsigned char *tptr = (unsigned char *)input;
    while (*tptr) {
      *tptr = tolower(*tptr);
      tptr++;
    }

    char* input_pointer = input;
    int length = 0;

    while (true) {
      token = strtok_r(input_pointer, " ", &ptr);
      if (token == NULL) {
        break;
      }
      query[length++] = token;
      input_pointer = NULL;
    }

    // Change End-Of-Line Character
    char *p = strchr(query[length - 1], '\n');
    if (p) *p = '\0';

    // Step 4: Process a query against the index and print out the results
    documents = MemIndex_Search(index, query, length);
    if (documents != NULL) {
      iterator = LLIterator_Allocate(documents);
      Verify333(iterator != NULL);

      do {
        LLIterator_Get(iterator, (void **) &searchResult);

        printf("  %s (%u)\n",
        DocTable_GetDocName(table, searchResult->doc_id),
        searchResult->rank);

        LLIterator_Next(iterator);
      } while (LLIterator_IsValid(iterator));

      LLIterator_Free(iterator);
      LinkedList_Free(documents, (LLPayloadFreeFnPtr) free);
    }
    free(query);
  }

  DocTable_Free(table);
  MemIndex_Free(index);

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}
