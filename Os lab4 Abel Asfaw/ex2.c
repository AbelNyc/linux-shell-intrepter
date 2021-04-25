

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#include <unistd.h>

#include <stdbool.h>


// please run this command on linux ./ex2 student.txt
int main(int argc, char* argv[])
{
	int pid,work,fd,grade,avrg,student_info[10][10];;
        int m_grade = 0;
	int num = 0;
	int total_sum = 0;
	int row_grade= 0;
	int count = 0;
	int i = 0;
	char *row,*filename = argv[1];
	char string[25];
	FILE* file = NULL;
	
	printf("........Welcome to  Abel's Grading System.....\n");
	if(filename == NULL){
		printf("Please enter the grade file:\n");
	}
	
	// Check if file exists
	if(access(filename, F_OK) == 0)
	{
		fd = open(filename,O_RDWR|O_CREAT,S_IRWXU);

		if(fd == -1)
		{
			printf("\tThe file couldn't be opened\n");
			exit(-1);
		} else {
			printf("\tThe file '%s' has opened Successfully\n",filename);	
		} 

		// Close File
		close(fd);
	}
	
	else {
		 printf ("\tThe file does not exist\n");
		 exit(EXIT_FAILURE);
	    }



    if(access(filename, R_OK)== 0)
	{
		printf("\tThe file can be read\n");
	} else {
		printf("\tThe file is not readable\n");
	} 
    
   if(access(filename, W_OK) == 0) 
	{
		printf("\tThe file can be modified");
	} else {
		printf("\tThe file can't be modified.");
	}
    printf("\n");
    
    // read from file
    file = fopen(filename,"r");
    
    //gets sutdent grades from file
    while((row = fgets(string,sizeof(string),file)) != NULL){
    	
    	while(sscanf(row,"%d%n",&grade,&num) == 1){
    		
    		student_info[row_grade][i] = grade;
    		
    		if(row_grade == 0) 
		
			count++;
    		
    		row += num;
    		i++;
    	}
    	
    	i = 0;
    	row_grade++;;
    }

    fclose(file);
   

    
    for(int i = 0; i < row_grade; i++)
	{
	
    	// Creation Manager
    	pid = fork();
		if(pid < 0) 
		{
			printf("Forking failed");
		}
		else if(pid == 0)
		{
		
		
			for(int t = 0; t < count; t++)
			{
				// Worker Creation
				work = fork();
				
				if(work < 0) 
				
				{
					
					printf("Forking failed");
				}
				else if(work == 0)
				{
					for(int m = 0; m < row_grade; m++) {
				         total_sum += student_info[m][t];
					   if (m_grade < student_info[m][t])
                        {
                            m_grade = student_info[m][t];
                        }
					}

			avrg = total_sum / row_grade;
printf("\tThe avrg of Homework %d is %d,Maximum grade is %d\n",t+1,avrg,m_grade);
			
			avrg = 0;
			
			break;
				}
				
				else if(work > 0) 
					wait(NULL);
			}
			
			break;
			
		}
		else if(pid > 0)
		{
			wait(NULL);
			break;
		}
		printf("Grading System exiting....");
    }

	return 0;
}



