#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char name[256];
    struct Node *leftMostChild, *rightSibling;
}Node;

Node *makeNode(char *name){
    Node *p = (Node*)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    return p;
}

Node *root;

Node *find(Node *r, char *name){
    if (r == NULL)
        return NULL;
    if (strcmp(r->name, name) == 0)
        return r;
    Node *p = r->leftMostChild;
    while (p != NULL){
        Node *q = find(p, name);
        if (q != NULL)
            return q;
        p = p->rightSibling;
    }
}

Node *addLast(Node *p, char *name){
    if (p == NULL)
        return makeNode(name);
    p->rightSibling = addLast(p->rightSibling, name);
    return p;
}

void addChild(char *name, char* child){
    Node* r = find(root,name);
    if(r == NULL)
        return;
    r->leftMostChild = addLast(r->leftMostChild,child);
}

void load(const char *filename){
    FILE *f  = fopen(filename, "r");
    if (f == NULL)
        printf("Not found file\n");
    char rootname[256];
    fscanf(f, "%s", rootname);
    root = makeNode(rootname);
    rewind(f);
    while (!feof(f)){
        char name[256], child[256];
        fscanf(f, "%s", name);
        while (strcmp(name, "$$")!= 0){
            fscanf(f, "%s", child);
            while (strcmp(child, "$")!=0){
                addChild(name, child);
                fscanf(f, "%s", child);
            }
            fscanf(f, "%s", name);
        }
    }
    fclose(f);
}

void printTree(Node *r){
    if (r == NULL)
        return;
    printf("%s: ", r->name);
    Node *p = r->leftMostChild;
    while(p != NULL){
        printf("%s ", p->name);
        p = p->rightSibling;
    }
    printf("\n");
    p = r->leftMostChild;
    while(p != NULL){
        printTree(p);
        p = p->rightSibling;
    }
}

void fprintTree(Node *r, FILE *f){
    if (r == NULL)
        return;
    fprintf(f, "%s ",r->name);
    Node *p = r->leftMostChild;
    while (p != NULL){
        fprintf(f, "%s ", p->name);
        p = p->rightSibling;
    }
    fprintf(f, "\n");
    p = r->leftMostChild;
    while(p != NULL){
        fprintTree(p, f);
        p = p->rightSibling;
    }
}

int height(Node *p){
    if (p == NULL)
        return 0;
    int maxH = 0;
    Node *q = p->leftMostChild;
    while(q != NULL){
        int h = height(q);
        maxH = maxH < h ? h : maxH;
        q = q->rightSibling;
    }
    return maxH + 1;
}

int count(Node *r){
    if (r == NULL)
        return 0;
    int cnt = 1;
    Node *q = r->leftMostChild;
    while (q!=NULL){
        cnt += count(q);
        q = q->rightSibling;
    }
    return cnt;
}

void freeTree(Node *r){
    if (r == NULL)
        return;
    Node *p = r ->leftMostChild;
    while(p!= NULL){
        Node *sp = p->rightSibling;
        freeTree(p);
        p = sp;
    }
    printf("free node %s\n", r->name);
    free(r);
    r = NULL;
}

int main(){
    int i;
    int choice;
    char filename[256];
    char name[256];
    Node *p;
    while(1){
        printf("1. Load data\n");
        printf("2. Find children\n");
        printf("3. Add child\n");
        printf("4. Print Tree\n");
        printf("5. Height\n");
        printf("6. Count\n");
        printf("7. Store\n");
        printf("8. Quit\n");
        printf("Enter command: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter filename:");
                scanf("%s", filename);
                load(filename);
                break;

            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                p = find(root, name);
                if (p != NULL){
                    printf("\n Childen of the given name: \n");
                    Node *q = p->leftMostChild;
                    while(q!= NULL){
                        printf("%s ",q->name);
                        q = q->rightSibling;
                    }
                    printf("\n");
                }
                else
                    printf("Not found!\n");
                break;

            case 3:
                printf("Enter the parent's name: ");
                scanf("%s", name);
                char insertName[256];
                printf("Enter the child's name: ");
                scanf("%s", insertName);
                addChild(name, insertName);
                break;

            case 4:
                printTree(root);
                break;

            case 5:
                printf("Enter name:");
                scanf("%s", name);
                Node *p = find(root, name);
                printf("The height of the given name is: %d\n", height(p));
                break;

            case 6:
                printf("The family have %d members\n", count(root));
                break;

//            case 7:
//                printf("Enter filename: \n");
//                scanf("%s", filename);
//                store(filename);
//                break;
            case 8:
                freeTree(root);
                return 0;
        }
    }
}
