#include <stdio.h>
#include <string.h>
#include "utils.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

char* trim_newline(char* s) {
    char *p = strchr(s, '\n');
    if (p) *p = '\0';
    return s;
}

void press_enter_to_continue(void) {
    printf("Press Enter to continue...");
    getchar();
}
