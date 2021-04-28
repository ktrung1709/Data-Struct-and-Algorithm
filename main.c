#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_L 256

typedef struct Profile{
    char name[MAX_L];
    char email[MAX_L];
    struct Profile *next;
    struct Profile *prev;
}Profile;

Profile *first, *last;

void init();
void cleanup();

Profile *getFirst();
Profile *getLast();

bool isEmpty();

void insertLast(char* name, char* email);
void removeProfile(char* name);
Profile* findProfile(Profile* first, char* name);

void printl2r();
void printr2l();

void load(char* filename);
void save(char* filename);

void init(){
    first = NULL;
    last = NULL;
}

bool isEmpty(){
    if ((first == NULL) && (last == NULL))
        return true;
    else
        return false;
}

Profile *makeProfile(char* name, char* email){
    Profile *node = (Profile*)malloc(sizeof(Profile));
    strcpy(node->name,name);
    strcpy(node->email,email);
    node->next = NULL;
    node->prev= NULL;
    return node;
}

void load(char *filename){
    FILE *f  = fopen(filename, "r");
    if (f == NULL)
        printf("Not found file\n");
    init();
    while (!feof(f)){
        char name[MAX_L], email[MAX_L];
        fscanf(f, "%s%s", name, email);
        insertLast(name,email);
        printf("Inserted: %s, %s\n", name, email);
    }
    fclose(f);
}

Profile* getFirst() {
    return first;
}

Profile* getLast() {
    return last;
}

void insertLast(char *name, char *email){
    Profile* profile = makeProfile(name,email);
    if(isEmpty())
        first = last = profile;
    else{
        last->next = profile;
        profile->prev = last;
        last = profile;
    }
}

void insertFirst(char *name, char *email){
    Profile* profile = makeProfile(name,email);
    if(isEmpty())
        first = last = profile;
    else{
        first->prev = profile;
        profile->next = first;
        first = profile;
    }
}

void printl2r(){
    Profile *p;
    for (p = first; p!= NULL; p = p->next)
        printf("%s, %s\n",p->name, p->email);
}

void printr2l(){
    Profile *p;
    for (p = last; p!= NULL; p = p->prev)
        printf("%s, %s\n",p->name, p->email);
}
void removeProfile(char *name){
    if (isEmpty())
        return;
    Profile *profile = findProfile(getFirst(), name);
    if (profile == NULL)
        printf("Not found %s\n", name);
    else{
        Profile *left = profile->prev;
        Profile *right = profile->next;
        if(left != NULL)  
            left->next = right;
        if(right != NULL) 
            right->prev= left;
        if(left == NULL) 
            first = right;
        if(right == NULL) 
            last = left;
        free(profile);
    }
}

Profile *findProfile(Profile *first, char *name){
    Profile *i = first;
    while (i!= NULL){
        if (strcmp(i->name, name)==0)
            return i;
        else
            i = i->next;
    }
}

void save(char *filename){
    FILE *f = fopen(filename, "w");
    if (f == NULL){
        printf("Can't save data\n");
        return;
    }
    for (Profile *p = first; p!=NULL; p = p->next){
        fprintf(f, "%s %s",p->name,p->email);
        if (p->next != NULL)
            fprintf(f, "\n");
    }
    fclose(f);
}

void cleanup() {
    Profile* i = first;
    Profile *tmp;
    while ( i!= NULL) {
        tmp = i;
        i = i->next;
        free(tmp);
    }
    first = last = NULL;
}

int main(){
    int i;
    int choice;
    char filename[128];
    char name[MAX_L];
    char email[MAX_L];
    Profile *p;
    init();
    while(1){
        printf("1. Load data\n");
        printf("2. Display list\n");
        printf("3. Create new profile\n");
        printf("4. Remove a profile\n");
        printf("5. Search a profile\n");
        printf("6. Save data\n");
        printf("7. Quit\n");
        printf("Enter command: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter filename:");
                scanf("%s", filename);
                load(filename);
                break;

            case 2:

                printf("Print list left to right press 1 or right to left press 2: ");
                scanf("%d", &i);
                if (i == 1)
                    printl2r();
                else if(i == 2)
                    printr2l();
                break;

            case 3:
                printf("Insert first press 1 or last press 2: ");
                scanf("%d", &i);
                printf("Enter name:");
                fflush(stdin);
                scanf ("%s", name);
                printf("Enter email:");
                fflush(stdin);
                scanf ("%s", email);
                if (i == 2)
                    insertLast(name, email);
                else if (i == 1)
                    insertFirst(name, email);
                break;

            case 4:
                printf("Enter name:");
                scanf("%s", name);
                removeProfile(name);
                break;

            case 5:
                printf("Enter name:");
                scanf("%s", name);
                p = findProfile(getFirst(), name);
                if (p != NULL){
                    printf("\n Profile Found: \n");
                    printf("Name:%s\nEmail:%s\n",p->name,p->email);
                }
                else
                    printf("Not found!\n");
                break;

            case 6:
                printf("Enter filename:");
                scanf("%s", filename);
                save(filename);
                break;

            case 7:
                cleanup();
                return 0;
        }
    }
    cleanup();
    return 0;
}