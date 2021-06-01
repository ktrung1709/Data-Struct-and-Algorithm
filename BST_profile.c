#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 10000

typedef struct Node{
    char name[MAX_L];
    char email[MAX_L];
    struct Node *left;
    struct Node *right;
}Node;

Node *root;

Node *makeNode (char *name, char *email){
    Node *p = (Node*)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->email, email);
    p->left = NULL;
    p->right = NULL;
    return p;
}

Node *insert(Node *r, char *name, char *email){
    if (r == NULL)
        return makeNode(name, email);
    int c = strcmp(r->name, name);
    if (c == 0){
        printf("Node already exists\n");
        return r;
    }
    else if (c > 0){
        r->left = insert(r->left, name, email);
        return r;
    }
    else{
        r->right = insert(r->right, name, email);
        return r;
    }
} 

void load(){
    FILE *f  = fopen("list.txt", "r");
    root = NULL;
    while(!feof(f)){
        char name[MAX_L], email[MAX_L];
        fscanf(f, "%s %s", name, email);
        root = insert (root, name, email);
    }
    fclose(f);
}

void print(Node *r){
    if (r == NULL)
        return;
    printf("%s %s\n", r->name, r->email);
    print(r->left);
    print(r->right);
}

Node *find(Node *r, char *name){
    if (r == NULL)
        return r;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    else if (c > 0)
        return find(r->left, name);
    else
        return find(r->right, name);
}

Node *findMin(Node *r){
    if (r->left != NULL)
        return findMin(r->left);
    return r;
}

Node *remove_profile(Node *r, char *name){
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->left = remove_profile(r->left, name);
    else if (c < 0)
        r->right = remove_profile(r->right, name);
    else{
        if (r->left != NULL && r->right != NULL){
            Node *tmp = findMin (r->right);
            strcpy(r->name, tmp->name);
            strcpy(r->email, tmp->email);
            r->right = remove_profile(r->right, tmp->name);
        }
        else{
            Node *tmp = r;
            if (r->left == NULL)
                r = r->right;
            else
                r = r->left;
            free(tmp);
        }
    }
    return r;    
}

void printfile(Node *r, FILE *f){
    if (r == NULL)
        return;
    else{
        fprintf(f, "%s %s\n", r->name, r->email);
        printfile(r->left, f);
        printfile(r->right, f);
    }    
}

void store(){
    FILE *f = fopen("list.txt", "w");
    printfile(root, f);
    fclose(f);
}

void freeTree(Node *r){
    if (r == NULL)
        return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

int main(){
    int choice;
    Node *p;
    char name[MAX_L];
    char email[MAX_L];
    while(1){
        printf("1. Load data\n");
        printf("2. Print list\n");
        printf("3. Search a profile\n");
        printf("4. Create new profile\n");
        printf("5. Remove a profile\n");
        printf("6. Save data\n");
        printf("7. Quit\n");
        printf("Enter command: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                load();
                break;
            case 2:
                print(root);
                break;
            case 3:
                printf("Enter the student's name: ");
                scanf("%s", name);
                p = find(root, name);
                if (p == NULL)
                    printf("Not found profile\n");
                else
                    printf("Found profile: %s %s\n", p->name, p->email);
                break;
            case 4:
                printf("Enter name: "); scanf("%s", name);
                printf("Enter email: "); scanf("%s", email);
                root = insert (root, name, email);
                break;
            case 5:
                printf("Enter the student's name: ");
                scanf("%s", name);
                root = remove_profile(root, name);
                break;
            case 6:
                store();
                break;
            case 7:
                freeTree(root);
                return 0;
        }
    }
}
