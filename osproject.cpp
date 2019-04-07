#include<stdio.h>
#include<stdlib.h>
int students[3][5],ns=3,scheduler[1000],arrivedStudents[100],nap=0;
unsigned int time=0;

void getSystem()
{
	for(int i=0;i<ns;i++)
	{
		printf("\n Arrival Time of P%d: ",i+1);
		scanf("%d",&students[i][0]);
		printf("\n Burst Time of P%d: ",i+1);
		scanf("%d",&students[i][1]);
		students[i][2]=students[i][1];
    	printf("\n ----------------------------");	
	}
}

void printSystem()
{
	printf("\n\t\tOur System is :");
	printf("\nSi:  AT  BT RT");
	for(int i=0; i<ns; i++)
	{
		printf("\nS%d:  %d  %d  %d", i+1, students[i][0], students[i][1], students[i][2]);
	}
	printf("\n ---------------------------------");
} 

unsigned int remainingTime()
{
	for(int i=0;i<ns;i++)
	{
		if(students[i][2]>0)
		{
			return 1;
		}
	}
	return 0;
}

void addArivedStudents()
{
	for(int i=0;i<ns;i++)
	{
		if(students[i][0]==time)
		{
			arrivedStudents[nap]=i;
			nap++;
		}
	}
}

void printArrivedStudents()
{
	printf("\n\nArrived Students %d : ",nap);   //nap=no of arrived students
	for(int i=0;i<nap;i++)
	{
		printf(" %d ",arrivedStudents[i]+1);
	}
}

int getLRT()
{
	if(nap==0)
	{
		return -1;
	}
	unsigned int largestRTP,largestRTPIndex;
	largestRTPIndex=arrivedStudents[0];
	largestRTP=students[arrivedStudents[0]][2];
	for(int i=0;i<nap;i++)
	{
		if(students[arrivedStudents[i]][2]>largestRTP)
		{
			largestRTP = students[arrivedStudents[i]][2];
			largestRTPIndex = arrivedStudents[i];
		}
	}
	return largestRTPIndex;
}

void removeFromArrivedProcesses(int toRun)
{
	printArrivedStudents();
	int temp[100];
	int x = 0;
	for(int i=0; i< nap; i++)
	{
		if(arrivedStudents[i] != toRun)
		{
			temp[x] = arrivedStudents[i];
			x++;
		}
	}
	nap=nap-1;
	for(int i=0; i<nap; i++)
	{
		arrivedStudents[i] = temp[i];
	}	
}

void schedule()
{
	int toRun;
	while(remainingTime()) //boolean function
	{
		addArivedStudents();
		printArrivedStudents();
		toRun = getLRT();
		scheduler[time] = toRun;
		students[toRun][2]=students[toRun][2]-1;
		if(students[toRun][2]==0)
		{
			removeFromArrivedProcesses(toRun);
		}
		if(toRun==-1)
		{
		printf("\nRun=NULL, Time=%d",time);
		}
		else
		{
		printf("\nRun=S%d,Time = %d",toRun+1,time);
		}
		printSystem();
		time++;
	}
}

void printScheduler()
{
	printf("\n\nScheduler: \n");
	for(int t=0;t<time; t++)
	{
		if(scheduler[t] == -1)
		{
			printf("\n[%d, %d] . IDLE", t, t+1);
		}
		else
		{
			printf("\n[%d, %d] . %d", t, t+1, scheduler[t]+1);
		}
	}
}

void waitingTime()
{
	unsigned int releaseTime,t;
	for(unsigned int i=0; i<ns; i++)
	{
		for(t=time-1;scheduler[t]!=i;t--);
		releaseTime=t+1;
		students[i][3]=releaseTime-students[i][0]-students[i][1]-1;
	}
}

void printWaitingTime()
{
	int waitingTime= 0;
	float AWT;
	printf("\nWaiting Time For Each Process: \n");
	for(unsigned int i=0; i<ns; i++)
	{
		printf("\nWT(%d) = %d", i+1, students[i][3]);
		waitingTime=waitingTime+students[i][3];
	//	tat=waitingTilmeSumm+students[i][3];
	}
	AWT = waitingTime/(float)ns;
	printf("\nAverage Waiting Time = %f", AWT);
}
void turnaroundTime()
{
	unsigned int releaseTime,t;
	for(unsigned int i=0; i<ns; i++)
	{
		for(t=time-1;scheduler[t]!=i;t--);
		releaseTime=t+1;
		students[i][4]=releaseTime-students[i][0]-1;
	}
}
void printturnaroundTime()
{
	int turnaroundTime= 0;
	float TAT;
	printf("\nTurn Around Time For Each Process: \n");
	for(unsigned int i=0; i<ns; i++)
	{
		printf("\nTAT(%d) = %d", i+1, students[i][4]);
		turnaroundTime=turnaroundTime+students[i][4];
	//	tat=waitingTilmeSumm+students[i][3];
	}
	TAT = turnaroundTime/(float)ns;
	printf("\nAverage Turn Around Time = %f",TAT);
}

int main()
{
	getSystem(); 
	printSystem();
	schedule();
	printScheduler();
	waitingTime();
	printWaitingTime();
	turnaroundTime();
	printturnaroundTime();
}
