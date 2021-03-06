// Write a program that opens the text.txt  file (with the `open()` system call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `open()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // Your code here
    int fileDesc = open("text.txt", O_RDWR);
    if(fileDesc < 0) {
      printf("Exiting...%d\n", fileDesc);
      exit(1);
    }
    printf("File descriptor: %d\n", fileDesc);

    int rc = fork();
    if (rc < 0) {    // fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if (rc == 0) { // Child Process
      printf("Child Process: %d (pid: %d)\n", fileDesc, (int) getpid());
      printf("Writing through Child Process...\n");
      write(fileDesc, "Writing to Child process concurrently..\n", 41);
    } else { // Parent Process
      printf("Parent Process: %d (pid: %d)\n", fileDesc, (int) getpid());
      printf("Writing through Parent Process...\n");
      write(fileDesc, "Writing to Parent process concurrently..\n", 42);
    }
    // Writes Parent then Child, Writing to Parent process concurrently..
    //  Writing to Child process concurrently..

    close(fileDesc);
    return 0;
}
