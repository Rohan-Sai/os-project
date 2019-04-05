#include<stdio.h>
#include<stdlib.h>
int processes[3][4],np=3,scheduler[1000],arrivedProcesses[100],nap=0;
unsigned int time=0;

void getSystem()
{
//	printf("\nEnter number of processes: ");
//	scanf("%d",&np);
	for(int i=0;i<np;i++)
	{
		printf("\n Arrival Time of P%d: ",i+1);
		scanf("%d",&processes[i][0]);
		printf("\n Burst Time of P%d: ",i+1);
		scanf("%d",&processes[i][1]);
		processes[i][2]=processes[i][1];
		printf("\n ----------------------------");	
	}
}

void printSystem()
{
	printf("\n\t\tOur System is :");
	printf("\nPi:  AT  BT RT");
	for(int i=0; i<np; i++)
	{
		printf("\nP%d:  %d  %d  %d", i+1, processes[i][0], processes[i][1], processes[i][2]);
	}
} 

unsigned int remainTimes()
{
	for(int i=0;i<np;i++)
	{
		if(processes[i][2]>0)
		{
			return 1;
		}
	}
	return 0;
}

void addArivedProcesses()
{
	for(int i=0;i<np;i++)
	{
		if(processes[i][0]==time)
		{
			arrivedProcesses[nap]=i;
			nap++;
		}
	}
}

void printArrivedProcesses()
{
	printf("\n\nArrived Processes %d : ",nap);   //nap=no of arrived processes
	for(int i=0;i<nap;i++)
	{
		printf(" %d ",arrivedProcesses[i]+1);
	}
}

int getSRT()
{
	if(nap==0)
	{
		return -1;
	}
	unsigned int largestRTP,largestRTPIndex;
	largestRTPIndex=arrivedProcesses[0];
	largestRTP=processes[arrivedProcesses[0]][2];
	for(int i=0;i<nap;i++)
	{
		if(processes[arrivedProcesses[i]][2]>largestRTP)
		{
			largestRTP = processes[arrivedProcesses[i]][2];
			largestRTPIndex = arrivedProcesses[i];
		}
	}
	return largestRTPIndex;
}

void removeFromArrivedProcesses(int toRun)
{
	printArrivedProcesses();
	int temp[100];
	int x = 0;
	for(int i=0; i< nap; i++)
	{
		if(arrivedProcesses[i] != toRun)
		{
			temp[x] = arrivedProcesses[i];
			x++;
			
		}
	}
	nap=nap-1;
	for(int i=0; i<nap; i++)
	{
		arrivedProcesses[i] = temp[i];
	}
//	printArrivedProcesses();
	
}

//}

void schedule()
{
	int x;
	int toRun;
	while(remainTimes()) //boolean function
	{
		addArivedProcesses();
		printArrivedProcesses();
		toRun = getSRT();
		scheduler[time] = toRun;
		processes[toRun][2]--;
		if(processes[toRun][2]==0)
		{
			removeFromArrivedProcesses(toRun);
		}
		if(toRun==-1)
		{
		printf("\nRun=NULL, Time=%d",time);
		}
		else
		{
		printf("\nRun=P%d,Time = %d",toRun+1,time);
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
	for(unsigned int i=0; i<np; i++)
	{
		for(t=time-1;scheduler[t]!=i;t--);
		releaseTime=t+1;
		processes[i][3]=releaseTime-processes[i][0]-processes[i][1];
	}
}
void printWaitingTime()
{
	int waitingTilmeSumm = 0,tat=0;
	float AWT;
	printf("\nWaiting Time For Each Process: \n");
	for(unsigned int i=0; i<np; i++)
	{
		printf("\nWT(%d) = %d", i+1, processes[i][3]);
		waitingTilmeSumm = waitingTilmeSumm + processes[i][3];
		tat=waitingTilmeSumm+processes[i][3];
	}
	AWT = waitingTilmeSumm/(float)np;
	printf("\nAverage Waiting Time = %f", AWT);
}
int main()
{
	getSystem(); 
	printSystem();
	schedule();
	printScheduler();
	waitingTime();
	printWaitingTime();
}
