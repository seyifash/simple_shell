#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
extern char** environ;

#define BUFSIZE 1024
typedef struct {
    char* command;
    int count;
} CommandInfo;

void execute_commands_alternatively(char *input);
int check_same_logical_operator(char *input);
void execute_sequentially(char *input);
void freememory_pp(char **ptr);
char **token_cmd(char *line);
int execute(char *cmd);
void execute_command_groups(char *input);
char *getlocation(char *command);
void handle_commands(char *input);
int main() 
{
    char line[100]; // Adjust the size as per your requirements

    while (1) {
        printf("Enter a command: ");
        fgets(line, sizeof(line), stdin);

        // Remove the trailing newline character from the input line
       // line[strcspn(line, "\n")] = '\0';

        // Check if the command is 'exit' to exit the program
        if (strcmp(line, "exit") == 0) {
            break;
        }

        // Handle the commands
        handle_commands(line);
    }

    return 0;
}
void execute_command_groups(char *input) {
    char* delim = "&&";
    char* cmd_cpy = strdup(input);
    char* token = strtok(input, delim);

    int prev_status = 0; // Track previous command status (0 = success, 1 = failure)

    while (token != NULL) {
        if (prev_status == 0) { // Only execute if the previous command succeeded
            int result = execute(token);
            if (result != 0) {
                prev_status = 1; // Set prev_status to indicate failure
            }
        }

        token = strtok(NULL, delim);
    }

    free(cmd_cpy);
}
int execute(char *cmd) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char **argv = token_cmd(cmd);

        char *command = argv[0];
        char *actual_command = getlocation(command);
        execve(actual_command, argv, environ);
        exit(1); // Exit child process on failure
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    } else {
        perror("Fork failed");
        return -1;
    }
}
void execute_sequentially(char *input) 
{
    char* delim = ";";
    char* cmd_cpy = strdup(input);
    char* cmd_token = strtok(input, delim);

    while (cmd_token != NULL) {
        execute(cmd_token);
        cmd_token = strtok(NULL, delim);
    }

    free(cmd_cpy);
}
void execute_commands_alternatively(char *input) 
{
	char* delim = "||";
	char* cmd_cpy = strdup(input);
	char* cmd_token = strtok(cmd_cpy, delim);

	while (cmd_token != NULL) 
	{
	execute(cmd_token);
	cmd_token = strtok(NULL, delim);
	}

	free(cmd_cpy);
}

void handle_commands(char *input) 
{

	if (strchr(input, ';') != NULL) 
	{
        execute_sequentially(input);
        }
	else if (strstr(input, "&&") != NULL) 
	{
        execute_command_groups(input);
	}
	else if (strstr(input, "||") != NULL) 
	{
        if (check_same_logical_operator(input))
	{
	execute(input);
	}
	execute_commands_alternatively(input);	
	}
	else 
	{
	execute(input);
	}

}
int check_same_logical_operator(char *input) {
	char* delim = "||";
	char* cmd_cpy = strdup(input);
	int same_operator = 1; // Assume same operator initially


	char* cmd_token = strtok(cmd_cpy, delim);
	 char* first_command = strdup(cmd_token);
	while (cmd_token != NULL) {
	cmd_token = strtok(NULL, delim);
	if (strcmp(cmd_token, first_command) != 0) {
        same_operator = 0; // Different command  found
        break;
        }
	}

	free(cmd_cpy);
	return same_operator;
}

char *getlocation(char *command)
{
        char *path, *path_copy, *path_token, *file_path;
        int command_length, directory_length;
        struct stat buffer;

        path = getenv("PATH");
        if (path)
        {
        path_copy = strdup(path);
        command_length = strlen(command);
        path_token = strtok(path_copy, ":");
        while (path_token != NULL)
        {
        directory_length = strlen(path_token);
        file_path = malloc(command_length + directory_length + 2);
        strcpy(file_path, path_token);
        strcat(file_path, "/");
        strcat(file_path, command);
        strcat(file_path, "\0");
        if (stat(file_path, &buffer) == 0)
        {
        free(path_copy);
        return (file_path);
        }
        else
        {
        free(file_path);
	        path_token = strtok(NULL, ":");
        }
        }
        free(path_copy);
        if (stat(command, &buffer) == 0)
        {
        return (command);
        }
        return (NULL);
        }
}
char **token_cmd(char *line)
{
        size_t n = 10;
        char *cmd_cpy = NULL;
        char *token = NULL;
        char *delim = " \n";
        int argc = 0, i = 0;
        char **argv = NULL;

        cmd_cpy = strdup(line);
        token = strtok(line, delim);
        while (token != NULL)
        {
        argc++;
        token = strtok(NULL, delim);
        }

        argv = malloc(sizeof(char *) * (argc + 1));
        if(!argv)
        {
                printf("Error: malloc failed\n");
                exit(1);
        }

        token = strtok(cmd_cpy, delim);

	i = 0;
        while (token != NULL)
        {
        argv[i] = strdup(token);
	i++;
        token = strtok(NULL, delim);
        }
        argv[i] = NULL;

         free(cmd_cpy);
	 return (argv);
}
void freememory_pp(char **ptr)
{
        int i;

        if (ptr == NULL)
        return ;

        for (i = 0; ptr[i] != NULL; i++)
        {
        free(ptr[i]);
        }
        free(ptr);
}
