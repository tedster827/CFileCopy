/*
 *  Teddy Williams
 *  Feburary 4, 2017
 *  CS 433 Operating Systems
 *  filecpy MAX SIZE OF COPY is 1024 bytes (for now)
 *  Please Note: Used the diff command on two test files and got no output, so
 *  they were copied successfully! I also used the strace command for read,
 *  open, write, and close. They were 3 for open. 512 for read, 39 for write,
 *  and finally 0 for close.
 */
// Including C Standard Input/Output header file.
#include <stdio.h>
// Including header file for open().
#include <fcntl.h>
// Including header file for read().
#include <unistd.h>

// Defining a bool in C
typedef int bool;
#define true 1
#define false 0

// Using a function prototype for slight recursion.
void readTheFile(bool, int, char const*);

/*
 * Purpose: This function is meant to seperate read and write functions for more
 * readability.
 * Inputs: The char array wdata is the buff where the content is stored. Char
 * const * wOutFile holds the name of the file that it will write to. The last
 * input is the outSize. It is used to only write the size of the data taken.
 * Output: None (Void Function)
 */
void writeToOutput(char wdata[1024], char const *wOutFile, int outSize) {
  printf("%s\n", "Data Extracted. Copying...");
  // Opening the output file.
  int wfiledesc = open(wOutFile, O_WRONLY);
  // Checking the number of bytes writen to see if the write was successful.
  if(write(wfiledesc, wdata, outSize) == outSize) {
    printf("%s\n", "Write Successful");
  }
  // Closing the file when done writing.
  close(wfiledesc);
  // Opening the file with the read flag
  int rfiledata = open(wOutFile, O_RDONLY);
  // Call the read function display contents
  printf("%s%s%s\n", "Copied to ",wOutFile, ":");
  readTheFile(false, rfiledata, wOutFile);
}

/*
 * Purpose: This function used to read any file but also checked if writing to a
 * new file is necessary.
 * Inputs: A bool write flag to check if calling the write function is needed.
 * Int filedesc is the file code for the file that was opened. The char const *
 * is the C string that holds the name of the file.
 * Output: None (Void Function)
 */
void readTheFile(bool write, int filedesc, char const *rOutFile) {
  printf("%s\n", "Reading the file...");

  // Creating a Buffer for the file setting to 1024 for now.
  char data[1024];

  // Calling the read system call to copy the contents of the file.
  int rfiledata = read(filedesc, data, 1024);
  printf("%s%i%s\n", "File Size: ", rfiledata, " Byte(s)");
  printf("%s", "Content: ");
  int i;
  // Displaying contents
  for(i = 0; i < rfiledata; i++) {
    printf("%c", data[i]);
  }
  if(rfiledata < 0) {
    // Displaying error message if the input size is zero
    printf("%s\n", "An error has occur while opening this file. The file may be empty");
  }
  // If the write flag is true it calls the write function.
  if(write) {
    writeToOutput(data, rOutFile, rfiledata);
  }
  else {
    // If writing flag is false the file is closed.
    close(filedesc);
  }
}
/*
 * Purpose: This function is the main driver function that will handle execution
 * arguments.
 * Inputs: The integer argc is the number of arguments that are passing using the
 * execution command. The char const* (or C string array) stores all the arguments.
 * Output: Exit Code (0)
 */
int main(int argc, char const *argv[]) {
  // Execution Command: ./filecpy <input file> <output file>
  // Checking for correct number of command arguments
  if(argc == 3) {
    // Opening input file to read it.
    int filedesc = open(argv[1], O_RDONLY | O_EXCL);
    // Opening output file to make sure it's there.
    int outfile = open(argv[2], O_RDONLY);
    // Checking byte size to check if the file is empty or non-existent.
    if(filedesc > 0 && outfile > 0) {
      printf("%s%s\n", "File Found: ", argv[1]);
      // Calling the read function when found
      readTheFile(true, filedesc, argv[2]);
    }
    else {
      // Displaying error message if the input size is zero
      printf("%s\n", "Input/or Output file was not found!");
    }
  }
  else {
    // Displaying error message if number of execution arguments are invaild.
    printf("%s\n", "Invaild number of execution arguments!");
  }
  // Exit Call 0
  return 0;
}
