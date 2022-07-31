#include <stdio.h>
#define MAX_SIZE 50
// Turnaround Time (TAT):
// It is the time interval from the time of submission of a process to the time of the completion of the process.
// Turn Around Time = Completion Time - Arrival Time

// Waiting Time (WT):
// The time spent by a process waiting in the ready queue for getting the CPU.
// Waiting Time = Turn Around Time - Burst Time
void printGannt(int arr[],int ct[],int p);
int main(){
    int n,time=0;
    float avgwt=0,avgtat=0;
    int AT[MAX_SIZE],BT[MAX_SIZE],CT[MAX_SIZE],WT[MAX_SIZE],TAT[MAX_SIZE];
    printf("Enter the number of processes : ");
    scanf("%d",&n);

    printf("Enter the Arrival Time and Burst Time :\n");
    printf("\tArrival Time\tBurst Time :\n");
    for(int i =0; i<n; i++){
        printf("p[%d] : ",i);
        scanf("%d",&AT[i]);
        scanf("%d",&BT[i]);
    }

    time = AT[0]; // initial time 
    for(int i =0;i<n;i++){
        time += BT[i]; // increasing the Time

        CT[i] = time;   
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i]-BT[i];

        avgtat+=TAT[i];
        avgwt+=WT[i];
    }
    avgtat /= n;
    avgwt /= n;
    printf("\n*******************************************************\n\n");

    printf("Process\tArrival Time\tBurst Time\tCompletion\tTurnAround\tWaiting\n");
    for(int i=0;i<n;i++){
        printf("p[%d]\t",i);
        printf("\t%d\t",BT[i]);
        printf("\t%d\t",AT[i]);
        printf("\t%d\t",CT[i]);
        printf("\t%d\t",TAT[i]);
        printf("\t%d\t\n",WT[i]);


    }
    printf("\nThe Average TurnAroundTime : %f",avgtat);
    printf("\nThe Average WaitingTime : %f",avgwt);
    printGannt(TAT,CT,n);
    return 0;
}
// p - noof processes
void printGannt(int tat[],int ct[],int p){
    printf("\n");
    for(int i=0;i<p;i++){
        // print ******************
        for(int j = 0;j<tat[i];j++){
            printf("*");
        }
        printf("|");
    }
    printf("\n");
    for(int i=0;i<p;i++){
            printf("| P[%d] | ",i);
        }
    printf("\n");
    for(int i=0;i<p;i++){
        // print ******************
        for(int j = 0;j<tat[i];j++){
            printf("*");
        }
        printf("|");
    }
    printf("\n0");
    for(int i=0;i<p;i++){
        for(int j = 0;j<tat[i];j++){
            printf(" ");
        }
        printf("%d",ct[i]);
    }
}