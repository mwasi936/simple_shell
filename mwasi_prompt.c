#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        char *argv[] = {"/bin/sh", "-c", command, NULL};
        execvp(argv[0], argv);
        // If execvp returns, it must have failed.
        printf("Unknown command: %s\n", command);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking failed
        perror("Fork failed");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char *command;
    char prompt[] = "my_shell$ ";

    while (1) {
        command = readline(prompt);
        if (!command) {
            // EOF (Ctrl+D) received, exit the shell
            printf("\n");
            break;
        }

        if (strlen(command) > 0) {
            add_history(command);
            execute_command(command);
        }

        free(command);
    }

    return EXIT_SUCCESS;
}
