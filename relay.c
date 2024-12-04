// relay.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void relay_message(const char* message) {
    char word[100];
    int i = 0;
    
    for (int j = 0; message[j] != '\0'; j++) {
        if (message[j] == ' ' || message[j] == '\n') {
            word[i] = '\0';
            if (i > 0) {
                printf("%s", word);
                fflush(stdout);
                usleep(200000);  // 0.2 seconds delay
            }
            printf("%c", message[j]);
            fflush(stdout);
            i = 0;
        } else {
            word[i++] = message[j];
        }
    }
    
    // Print last word if exists
    if (i > 0) {
        word[i] = '\0';
        printf("%s", word);
        fflush(stdout);
        usleep(200000);
    }
}
