#include<stdio.h>
#include<stdlib.h>
int main(){
    int size;
    printf("give num of processes");
    scanf("%d",&size);
    int arrival[size];
    int burst[size];
    int TAT[size];
    int wait[size];
    int completion[size];
    printf("please give arrival and burst times of a process respectively");
    for(int i=0;i<size;i++)
    {
        scanf("%d %d",&arrival[i],&burst[i]);
    }
    int sum=0;
    int sumburst=0;
    int sumcomp=0;
    for (int i=0;i<size;i++){
        sum=sum+burst[i];
        completion[i]=sum;
        sumburst=sumburst+burst[i];
        sumcomp=+completion[i];
    }
    int tatsum=0;
    for (int i=0;i<size;i++){
        TAT[i]=completion[i]-arrival[i];
        tatsum=tatsum+TAT[i];
    }
    int sumwait=0;
    for (int i=0;i<size;i++){

        wait[i]=TAT[i]-burst[i];
        sumwait=sumwait+wait[i];
    }
    printf("arrival time-- burst time-- completion time-- Turn Around time -- wait time \n");
    for(int i=0;i<size;i++){
       
        printf("%d                 %d            %d                       %d                  %d \n",arrival[i],burst[i],completion[i],TAT[i],wait[i]);
    }
    float avgtat=tatsum/(float)size;
    float avgcomp=sumcomp/(float)size;
    float avgwait=sumwait/(float)size;
    printf("\n avgtat=%f avgwait=%f avgcomp=%f ",avgtat,avgwait,avgwait);
    }