#include<stdio.h>
#include<unistd.h>
// #include<pthread.h>

int req_resourse(int cid, int req[]);

int req_resourse(int cid, int req[]){
    int i;
    for(i=0;i<5;i++){
        printf("%d ",req[i]);
    }
    printf("\n");
    return 0;
    
};

int main(){
    int n,m;
    pid_t a;
    int req1[5];
    int req2[8];
    req_resourse(7,req1);

}