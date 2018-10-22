#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define MAX 1050//value kbira 3shan atcheck el 512 7rf

int main()
{
    printf("Write 'exit' to quit the shell\n");
    while (1)
    {
        char *tempPtr, *newLinePtr;
        int i=0; // iterator
        int r=0,k; //return value of execvp()
        int j; //second iterator
        pid_t backgroundProcessID; //grandChild for background
        char  line[MAX] ; //scaned input
        char *cmd[MAX]; //pointer array, points to command tokens
        printf("Shell > ");
        fgets(line,MAX,stdin);//scanning
        if (strlen(line)>512)
        {
            printf("Error : Your command must be 512 letters at most\n");
            fprintf(stderr, "Error : Command must be 512 letters at most\n");
        }
        else
        {
            for (k = strlen(line) - 1; k >= 0; k--) // Determining the true end of the command (in case of empty spaces at the end of the string"
            {
                if(line[k] == ' ' || line[k] == '\n')
                    continue;
                else
                    break;
            }
            if (k == -1)
                continue; //Empty command, scan again

            tempPtr = strtok(line," \n"); //Getting first token
            while (tempPtr != NULL) //Looping on all tokens
            {
                cmd[i] = tempPtr; //Saving a pointer to the ith token
                tempPtr = strtok(NULL," \n"); //Getting a pointer for the next token
                i++;
            }
            cmd[i] = NULL; //Last token, terminator

            for (j = 0; j < i; j++) //replacing new line character with a null terminator
            {
                if ( (newLinePtr = strchr(cmd[j], '\n')) != NULL)
                {
                    *newLinePtr = '\0';
                }
            }

            if (strcmp(cmd[0],"exit")==0)
                kill(0,SIGKILL);

            if (strcmp(cmd[i-1],"&")==0) //background
            {
                backgroundProcessID = fork();
                if (backgroundProcessID >= 0) //grandChild sucess
                {
                    if (backgroundProcessID == 0) //grandChild
                    {
                        //Executing command
                        printf("Spawned child (%d)\n", backgroundProcessID);
                        system(line);
                    }
                }
            }
            else //foreground
            {
                //Executing command
                system(line);
            }
        }
        if (r!=0)
            perror("Error ");
    }
    return 0;
}
