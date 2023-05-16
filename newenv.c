#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int unset_environment_variable(const char *name) {

    int env_count = 0;
    int new_index = 0;
    char **new_env;
    int i;
    while (environ[env_count] != NULL) {
        env_count++;
	}

    new_env = (char **)malloc((env_count + 1) * sizeof(char *));
    if (new_env == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return -1;
    }

    new_index = 0;


    for (i = 0; i < env_count; i++) {
        if (strncmp(environ[i], name, strlen(name)) != 0 || environ[i][strlen(name)] != '=') {
            new_env[new_index++] = environ[i];
        }
    }

    new_env[new_index] = NULL;

    environ = new_env; 

    return 0;
}

int main() {
  
    const char *variable_name = "MY_VARIABLE";
    int i;

    if (unset_environment_variable(variable_name) == 0) {
        printf("Environment variable '%s' successfully unset\n", variable_name);
    } else {
        fprintf(stderr, "Failed to unset environment variable '%s'\n", variable_name);
    }

   
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}

