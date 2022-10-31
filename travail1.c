#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


char buffer[30];
unsigned int i = 0;
char inputChar;
bool empty = false;


void sig_handler(int signum){
    if (strlen(buffer) == 0)
        empty = true;
    else {
        printf("   ----> %s\n", buffer); // printing the buffer
        memset(buffer, 0, sizeof(buffer)); // clear previous buffer
        i = 0; // initialization of index buffer
        alarm(5); // sending signal alarm every 5 seconds
    }
}

 
int main(int argc , char * argv []) {
    signal(SIGALRM, sig_handler); // Register signal handler
    alarm(5);
    while(1) {
        if (empty == true) {
            printf("---------------END--------------\n");
            break;
        }
        inputChar = getchar(); // Read input character
        if (inputChar != '\n' && inputChar != EOF) {
            buffer[i] = inputChar - 32;
            i++;
        }
    }
    return EXIT_SUCCESS;
}
