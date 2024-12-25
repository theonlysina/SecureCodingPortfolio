include <string.h>
include <stdio.h>
include <stdlib.h>

define BUFSIZE 256

// Function to safely encode the user input for shell usage
void encodeShellString(char *dest, size_t size, const char *src) {
// Escape characters to prevent command injection
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0' && j < size - 1; i++) {
        if (src[i] == '"') {
            if (j < size - 2) {
                dest[j++] = '\\'; // Escape the quote
                dest[j++] = '"';
            }
        } else if (src[i] == '\\') {
            if (j < size - 2) {
                dest[j++] = '\\'; // Escape the backslash
                dest[j++] = '\\';
            }
        } else {
            dest[j++] = src[i];
        }
    }
    snprintf(dest, size, "\"%s\"", src); // Simple quoting for demonstration
}

// Function to construct the command safely
void constructCommand(char *cmd, size_t size, const char *filePath) {
    snprintf(cmd, size, "wc -c < %s", filePath); // Construct the command string
}

// main function of the progra; prints size of a file in bytes
int main(int argc, char** argv) {
    // makes sure the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }
	
	// the user string is encoded by a library routine.
	char filePath[BUFSIZE] = {0};
	encodeShellString(filePath, sizeof(filePath), argv[1]);
		
	// safely construct command (a string)
    char cmd[BUFSIZE] = {0};
    constructCommand(cmd, sizeof(cmd), filePath);
	
    // Execute command and handle errors
    if (system(cmd) == -1) {
        perror("Error executing command");
        return -1;
    }

    return 0;
}
