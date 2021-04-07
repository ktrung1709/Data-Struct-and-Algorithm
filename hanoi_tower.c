#include <stdio.h>
int cnt= 0;
void move(int n, char A, char B, char C){
    if(n == 1){
        cnt++;
        printf("Step %d: Move a disk from %c to %c\n",cnt,A,B);
    }
    else{
        move(n-1,A,C,B);
        move(1,A,B,C);
        move(n-1,C,B,A);
    }
}

int main(){
    move(3,'A','B','C');
}