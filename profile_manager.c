#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 10000

typedef struct Profile{
    char name[MAX_L];
    char email[MAX_L];
}Profile;

Profile list[MAX];

void swap(Profile *a, Profile *b){
    Profile temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int n, int i){
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    //if leftchild is greater than parent
    if(l<n && strcmp(list[l].name, list[largest].name) > 0)
        largest = l;
    //if rightchild is greater than parent
    if(r<n && strcmp(list[r].name, list[largest].name) > 0)
        largest = r;

    if(largest != i){
        swap(&list[i], &list[largest]);
        heapify(n, largest);
    }
}

void heapsort(int n){
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(n, i); //creates a max heap
    for (int i = n -1; i>= 0; i--){
        swap(&list[0], &list[i]); //swaps first and last node
        heapify(i, 0); //creates max heap on reduced array
    }
}

int count(){
    int n;
    FILE *f  = fopen("list.txt", "r");
    fscanf(f, "%d", &n);
    fclose(f);
    return n; 
}

void load(){
    int n;
    FILE *f  = fopen("list.txt", "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
        fscanf(f, "%s %s", list[i].name, list[i].email);
    fclose(f);
    
}

int search(char *name, int left, int right){
    if (left > right)
        return -1;
    int mid = (left + right)/2;
    if(strcmp(list[mid].name, name) == 0)
        return mid;
    else if(strcmp(list[mid].name, name) < 0)
        return search(name, mid + 1, right);
    else
        return search(name, left, mid - 1);
}

void add(char *name, char *email, int n){
    strcpy(list[n].name, name);
    strcpy(list[n].email, email);
}

void store(int n){
    FILE *f = fopen("list.txt","w");
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++)
        fprintf(f, "%s %s\n", list[i].name, list[i].email);
    fclose(f);
}

int main(){
    int choice;
    char name[MAX_L];
    char email[MAX_L];
    int n = count();
    while(1){
        printf("1. Load data\n");
        printf("2. Search a profile\n");
        printf("3. Create new profile\n");
        printf("4. Remove a profile\n");
        printf("5. Save data\n");
        printf("6. Quit\n");
        printf("Enter command: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                load();
                heapsort(n);
                break;
            case 2:
                printf("Enter the student's name: ");
                scanf("%s", name);
                int found = search(name, 0, n - 1);
                if(found < 0)
                    printf("Not found profile\n");
                else
                    printf("Found profile: %s %s\n", list[found].name, list[found].email);
                break;
            case 3:
                printf("Enter name: "); scanf("%s", name);
                printf("Enter email: "); scanf("%s", email);
                add(name, email, n);
                n = n + 1;
                heapsort(n);
                break;
            case 4:
                printf("Enter the student's name: ");
                scanf("%s", name);
                found = search(name, 0, n - 1);
                if(found < 0)
                    printf("Not found profile\n");
                else{
                    swap(&list[found], &list[n-1]);
                    n = n - 1;
                    heapsort(n);
                }
                break;
            case 5:
                store(n);
                break;
            case 6:
                return 0;
        }
    }
}
