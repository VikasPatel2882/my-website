#include <stdlib.h>
#include <string.h>

char* removeOuterParentheses(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(sizeof(char) * (len + 1));
    int depth = 0;
    int j = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            // Append '(' only if it's not the outermost opening bracket
            if (depth > 0) {
                result[j++] = s[i];
            }
            depth++;
        } else {
            depth--;
            // Append ')' only if it's not the outermost closing bracket
            if (depth > 0) {
                result[j++] = s[i];
            }
        }
    }

    result[j] = '\0';
    return result;
}