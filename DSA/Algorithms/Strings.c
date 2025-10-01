#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

int main(int argc, char** argv) {
    
    char* str = "A normal string with no much to it";
    
    int len = strnlen(str, MAX_LEN); // number of chats plus \0 terminator 

    // Tokenization (destructive)!!!!
    
    char* piece = strtok(str, " "); // returns the string until the separator 
    // will return "A\0"

    piece = strtok(NULL, " "); // will take the previosly used string but now without "A"
    
    printf("%s", piece);
    
    
    // Newer alternaitves 
    char* original = strdup("AHHHHHH, ajbakjnvkjnc , ijajavja");
    char* rest = original;
    char* token;
    
    // Similar to the original but with only one call
    while ((token = strtok_r(rest, ",", &rest))) {
        printf("Token: %s", token);
    }

    
    // This one also return separators separated by separators 
    while ((token = strsep(&original, ",")) != NULL) {
        printf("Token: %s", token);
    }
    
    return 0;
}
