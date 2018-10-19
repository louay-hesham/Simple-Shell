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
    printf("Write 'q' to quit the shell\n");
    while (1)
    {
        char *tempPtr, *newLinePtr, *ampersandPtr;
        int i=0;// iterator
        int r=0,k;//return value of execvp()
        int j;//second iterator
        int m; //iterator for spaces
        int f=0;//flag
        pid_t ChildID;//first child
        pid_t backgroundProcessID; //grandChild for background
        char  line[MAX] ;//scaned input
        char *cmd[MAX];//pointer array

        ChildID = fork();

        if (ChildID >=0)//fork sucess
        {
            if (ChildID==0) //Child
            {
                printf("Shell > ");
                fgets(line,MAX,stdin);//scanning

                if (strlen(line)>512)
                {
                    printf("Error : Your command must be 512 letters at most\n");
                    fprintf(stderr, "Error : Command must be 512 letters at most\n");
                }
                else
                {
                    for (k = strlen(line); k > 0; k--)
                    {
                        if(line[k] == ' ' || line[k] == '\n') continue;
                        else break;
                    }
                    if (k == 0) continue; //User only pressed "Enter"

                    tempPtr = strtok(line," \n");
                    while (tempPtr != NULL)
                    {
                        cmd[i] = tempPtr;
                        tempPtr = strtok(NULL," \n");
                        i++;
                    }
                    cmd[i] = NULL;

                    for (j = 0; j < i; j++)
                    {
                        if ( (newLinePtr = strchr(cmd[j], '\n')) != NULL)
                        {
                            *newLinePtr = '\0';
                        }
                    }

                    if (strcmp(cmd[0],"q")==0) kill(0,SIGKILL);

                    if (strcmp(cmd[i-1],"&")==0) //background
                    {
                        *cmd[i-1]='\0';
                        backgroundProcessID = fork();
                        if (backgroundProcessID >= 0) //grandChild sucess
                        {
                            if (backgroundProcessID == 0) //grandChild
                            {
                                if (strcmp(cmd[0],"cd")==0) chdir(cmd[1]);
                                else r = execvp(cmd[0],cmd);
                            }
                            else break;
                        }
                    }
                    else //foreground
                    {
                        if (strcmp(cmd[0],"cd")==0) chdir(cmd[1]);
                        else r = execvp(cmd[0],cmd);
                    }
                }
            }
            else wait(NULL);
        }
        if (r!=0) perror("Error ");
    }
    return 0;
}
