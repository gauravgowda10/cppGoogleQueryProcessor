/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include "ro_file.h"


/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);

// Usage/Error functions
void Usage();

void Args();

/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
    Args();
    exit(EXIT_FAILURE);
  }
  char* dirname;
  DIR* dir;
  struct dirent* entry;

  // Check for errors opening directory
  dirname = argv[1];
  dir = opendir(dirname);
  if (!dir) {
    perror("Could not open directory");
    exit(EXIT_FAILURE);
  }

  while ((entry = readdir(dir))) {
    RO_FILE* fp;
    char* file;
    // Found a directory, but ignore . and ..
    if (strcmp(".", entry->d_name) == 0 ||
        strcmp("..", entry->d_name) == 0) {
          continue;
        }
      // Print file contents to stdout
      if (IsTxtFile(entry->d_name)) {
        file = Concatenate(dirname, entry->d_name);
        fp = ro_open(file);
        if (!fp) {
          exit(EXIT_FAILURE);
        }
        int filesize = ro_seek(fp, 0, SEEK_END);
        ro_seek(fp, 0, SEEK_SET);   // Reset file pointer
        
        char* buf
        ro_close(fp);
      }
  }
  closedir(dir);

  exit(EXIT_SUCCESS);
}


/*** HELPER FUNCTION DEFINITIONS *******************************************/

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}

void Usage() {
  fprintf(stderr, "Usage: ./ex4 <dir_name>\n");
}

void Args() {
  printf("This program accepts 1 argument corresponding to a directory name\n");
}

// Add error message if no txt files found?
