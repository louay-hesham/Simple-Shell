#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define MAX 1050//value kbira 3shan atcheck el 512 7rf

void mounirelga7ed(void)
{
//
while (1)
	{ // fi 7agat msh mst3mlha ! kont bgrbha bas !
		char * hmada;//temp
		char *mshmsh;//pointer 3ala mkan el \n
		char *pos;//pointer 3ala mkan el &
		int i=0;// iterator
		int r=0,k;//return value of execvp()
		int j;//second iterator
		int m; //iterator for spaces
		int f=0;//flag
		pid_t ChildID;//first child
		pid_t back; //grandChild for background
		char  line [MAX] ;//scaned input
		char *cmd[MAX];//pointer array

		ChildID = fork();

		if (ChildID >=0)//fork sucess
		{
			if (ChildID==0) //Child
			{
				printf("Shell > ");//input
				fgets(line,MAX,stdin);//scanning

				if (strlen(line)>512)
				{
					//printf("Error : Your command must be 512 letters at most\n");
					fprintf(stderr, "Error : Your command must be 512 letters at most\n");
					mounirelga7ed();
				}
				for (  k= strlen(line);  k>0; k--) {

					//printf("%d",k );
					if(line[i] == ' ' || line[i] == '\n')
					{
						continue;
					}
						else
						break;
				}
				if(k==0){
					mounirelga7ed();
				}

				if (strlen(line)==1)//das enter bas
				{
					//printf("Error!!\nYour command must be 512 letters at most!\n");
					//fprintf(stderr, "Error : You must enter a command\n");
					mounirelga7ed();
				}

				hmada = strtok(line," ");// bshil spaces
				i=0;//zyadet ta2kid m3lsh
				while (hmada!=NULL)//until hamada equal null
				{
				  cmd[i] = hmada;
				  hmada = strtok(NULL," ");
				  i++;
				}

				cmd[i]=NULL;// a5er wa7ed b NULL
				for (j = 0; j < i; j++) // bshil el new line
				 {

					if ((mshmsh=strchr(cmd[j], '\n')) != NULL)//function to cmp
					   {
							  *mshmsh = '\0';
						 }
				}

				if (strcmp(cmd[0],"q")==0) // quit
				{
					//printf("mshmsh\n");
					kill(0,SIGKILL);
				}

				if (strcmp(cmd[i-1],"&")==0)//background
				{
					*cmd[i-1]='\0';
					back=fork();
					if (back >=0) //grandChild sucess
					{
						if (back==0) //grandChild
						{
							if (strcmp(cmd[0],"cd")==0)
							{
								//printf("ana fel background\n");
								chdir(cmd[1]);
							}
							else
								//printf("ana fel background\n");
								r=execvp(cmd[0],cmd);//by return -1 lw feh error




						}//end of grandChild
						else //parent2
						{
							break;
							//printf("ana msh hstna 7ad\n");
						 //mounirelga7ed();//parent won't wait for it's child /////////////////////////////////////////
					 } // end of parent2
					}//end of grandChild sucess
				}// end of background

				if (strcmp(cmd[0],"cd")==0)//foreground
				{
					chdir(cmd[1]);
				}
				else
					r=execvp(cmd[0],cmd);

			} // end of child

			else //parent
		 {
			 wait(NULL);
		 } // end of parent

	 }//end of fork sucess
if (r!=0)
{
	//printf("Error : Please check you command\n" );
	perror("Error ");
}

 }// end of while

}// end of mounirelga7ed


int main()
{
	printf("\n\t\t@\t************\t  @\n\t\tWelcome to our shell program\n\t\t@\t************\t  @\n\n");
	printf("\t  to quit our shell program just press q\n\n");
	mounirelga7ed();
	return 0;
}
