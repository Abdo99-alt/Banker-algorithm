// Banker's Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

    bool flag ;
	char filename[15];
	int process,resource, i, j, k ,y=0,P=5;
	process = 5; // Number of processes
	resource = 3; // Number of resources

	int alloc[5][3];    //current allocation matrix 
    int max[5][3];      //maximum required resources 
    int avail[3] ;      //current avaiable resources
	
	printf("Enter a test file name :");
	scanf("%s" , filename);
    FILE *fptr1 =fopen(filename,"r");

	//loop to store the current allocated resources
	for (i = 0; i < process; i++)
	{
		for (j = 0; j < resource; j++)
			fscanf(fptr1, "%d", &alloc[i][j]);
	}
	//loop to store the max required resources
	for (i = 0; i < process; i++)
	{
		for (j = 0; j < resource; j++)
			fscanf(fptr1, "%d", &max[i][j]);
	}
	//loop to store the current available resources
	for (j = 0; j < resource; j++)
		fscanf(fptr1, "%d", &avail[j]);

	int found_process[process], ans[process], ind = 0;
    for (k = 0; k < process; k++) {
        found_process[k] = 0;
    }

	/*the algorithm works as follows :
	in every iteration we check if there is
	a process that can take its max need then 
	we assume it does and get back the resources 
	that were held by this one , add them to the
	avaiable matrix and so on.At the end we check if 
	all processes terminated successfully if so then
	it is a safe state and print the possible sequence 
	of execution.If there is one process -at least- that 
	can't take all its needs then it is unsafe state*/
	while(P){
		for (i = 0; i < P; i++) {
			if (found_process[i] == 0) {
				for (j = 0; j < resource; j++) {
					if ((max[i][j] - alloc[i][j]) <= avail[j]){
						continue;
					}
					else break;
				}

				if (j==3) {
					ans[ind++] = i;
					for (y = 0; y < resource; y++)
						avail[y] += alloc[i][y];
					found_process[i] = 1;
				}
			}
		}
		P-- ;
	}

	flag=true ;

	for(int i=0;i<process;i++)
	{
	if(found_process[i]==0)
	{
		flag=false ;
		printf("The current state is not safe");
		break;
	}
	}

	if(flag==true)
	{
	printf("The current state is safe\n");
	for (i = 0; i < process - 1; i++)
		printf("P%d -> ", ans[i]);
	printf("P%d", ans[process - 1]);
	}

	return (0);

}