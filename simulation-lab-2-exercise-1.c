include <string.h>
include <stdio.h>
include <stdlib.h>

define BUFSIZE 256

// Function to safely encode the user input for shell usage
void encodeShellString(char *dest, size_t size, const char *src) {
    snprintf(dest, size, "\"%s\"", src); // Simple quoting for demonstration
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    {
        // the user string is encoded by a library routine.
        char filePath[BUFSIZE] = {0};
        encodeShellString(filePath, sizeof(filePath), argv[1]);
	
	char cmd[BUFSIZE] = {0};
	snprintf(cmd, sizeof(cmd), "wc -c < \"%s\"", filePath);
	system(cmd);
   }

    return 0;
}
