#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool processTokens(const char *input, const char *delimiter) {
    char *line = strdup(input);
    char **argv = NULL;
    int argc = 0;

    char *token = strtok(line, delimiter);
    while (token != NULL) {
        argv = realloc(argv, sizeof(char *) * (argc + 1));
        argv[argc] = strdup(token);
        argc++;
        token = strtok(NULL, delimiter);
    }

    bool allTokensSame = true;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], argv[0]) != 0) {
            allTokensSame = false;
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
    free(line);

    return allTokensSame;
}
int main() {
    const char input[] = "ls /hbtn || ls /hbtn || ls /hbtn";
    const char delimiter[] = "||";

	 bool allTokensSame = processTokens(input, delimiter);
    if (allTokensSame == true) {
        printf("All tokens are the same.\n");
    } else {
        printf("Tokens are not all the same.\n");
    }

    return 0;

}
