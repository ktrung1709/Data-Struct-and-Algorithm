#include<stdio.h>
int compare(int n, int a[], int b[]){
    int i;
    for (i = 0;i<n;i++)
        if(a[i] != b[i])
            return 0;
    return 1;
}


int main(){
    int n, i;
    printf("Enter the size of the two arrays: ");
    scanf("%d", &n);
    int a[n], b[n];
    for (i = 0; i<n; i++){
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");
    for (i = 0; i<n; i++){
        printf("b[%d] = ", i);
        scanf("%d", &b[i]);
    }

    if (compare(n, a, b) == 1)
        printf("Two arrays are equal\n");
    else
        printf("Two arrays are not equal\n");
    return 0;
}
