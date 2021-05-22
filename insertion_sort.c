#include <stdio.h>

typedef struct Address
{
    char name[30];
    char phone[15];
    char email[30];
}Address;

void insertion_sort(Address list[], int n){
    int i, j;
    Address next;
    for (i=1; i < n; i++){
        next= list[i];
        for (j=i-1;j>=0 && next.name[0]< list[j].name[0];j--)
            list[j+1] = list[j];
        list[j+1] = next;
    }
}

int count(){
    int n;
    FILE *f = fopen("AddressBook.txt","r");
    fscanf(f, "%d", &n);
    fclose(f);
    return n;
}

void load(Address list[], int count){
    int n;
    FILE *f = fopen("AddressBook.txt","r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < count; i++){
        fscanf(f, "%s", list[i].name);
        fscanf(f, "%s", list[i].phone);
        fscanf(f, "%s", list[i].email);
    }
    fclose(f);
}

void print_result(Address list[], int count){
    for (int i = 0; i < count; i++)
    {
        printf("%s ", list[i].name);
        printf("%s ", list[i].phone);
        printf("%s ", list[i].email);
        printf("\n");
    }

}

void store(Address list[], int count){
    FILE *f = fopen("AddressBook.txt","w");
    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s ", list[i].name);
        fprintf(f, "%s ", list[i].phone);
        fprintf(f, "%s ", list[i].email);
        fprintf(f, "\n");
    }
    fclose(f);
}

int main(){
    int n = count();
    Address list[100];
    load (list, n);
    insertion_sort(list, n);
    print_result(list, n);
    store (list, n);
    return 0;
}
