
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define true 1
#define false 0

int main() {
    regex_t regex;
    size_t size = 10;
    regmatch_t match[size];

    int out = -1;

    char* string = "software-v3.0.1 - (1.0.0 Beta)";
    char* test = "software-v3.0 - Beta";
    char* pattern = "([0-9]+\\.[0-9]+\\.[0-9]+)";
    char buffer[100];

    if (0 != (out = regcomp(&regex, pattern, REG_EXTENDED))) {
        regerror(out, &regex, buffer, 100);
        printf("regcomp() failed with '%s'\n", buffer);

        return -1;
    }

    int status = false;
    while (!status) {
        status = regexec(&regex, string, size, match, 0);

        if (!status){
            // printf("With the whole expression, a matched substring \"%.*s\" is found at position %d to %d.\n",
            //     match[0].rm_eo - match[0].rm_so, &string[match[0].rm_so],
            //     match[0].rm_so,
            //     match[0].rm_eo - 1);
            printf("The matched substring \"%.*s\" is found at position %d to %d.\n", match[0].rm_eo - match[0].rm_so, &string[match[0].rm_so], match[0].rm_so, match[0].rm_eo - 1);
            // Move further into the string, passed end of current match
            string += match[0].rm_eo;
        } else {
            printf("No match found.");
        }
    }

    regfree(&regex);

    return 0;
}