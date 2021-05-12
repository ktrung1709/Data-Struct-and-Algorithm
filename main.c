#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int id;
	struct Node *leftChild;
	struct Node *rightChild;
}Node;

Node *root;

Node *makeNode(int id){
	Node *p = (Node*)malloc(sizeof(Node));
	p->id = id;
	p->leftChild = NULL;
	p->rightChild = NULL;
	return p;
}

Node *find(Node *r, int id){
	if (r == NULL)
		return NULL;
	if (r->id == id)
		return r;
	Node *p = find(r->leftChild, id);
	if (p!= NULL)
		return p;
	return find(r->rightChild, id);
}

void addLeftChild(int u, int left){
	Node *pu = find(root, u);
	if (pu == NULL){
		printf("Not found %d\n", u);
		return;
	}
	if (pu->leftChild != NULL){
		printf("Node %d already has a leftChild\n", u);
		return;
	}
	pu->leftChild = makeNode(left);
}

void addRightChild(int u, int right){
	Node *pu = find(root, u);
	if (pu == NULL){
		printf("Not found %d\n", u);
		return;
	}
	if (pu->rightChild != NULL){
		printf("Node %d already has a rightChild\n", u);
		return;
	}
	pu->rightChild = makeNode(right);
}

void load(char *filename){
	FILE* f = fopen(filename,"r");
	root = NULL;
	while(1){
		int u;
		fscanf(f,"%d",&u);
		if(u == -2)
			break;
		if(root == NULL)
			root = makeNode(u);
		int l,r;
		fscanf(f,"%d %d",&l,&r);
		if(l > -1)
			addLeftChild(u,l);
		if(r > -1)
			addRightChild(u,r);
	}
	fclose(f);
}

void printTree(Node *r){
	if(r == NULL)
		return;
	printf("%d: ",r->id);
	if(r->leftChild == NULL)
		printf("leftChild = NULL");
	else
		printf("leftChild = %d",r->leftChild->id);
	if(r->rightChild== NULL)
		printf(", rightChild = NULL");
	else
		printf(", rightChild = %d",r->rightChild->id);
	printf("\n");

	printTree(r->leftChild);
	printTree(r->rightChild);
}

void printChildren(Node* p){
	if(p->leftChild == NULL)
		printf("Node %d does not have a leftChild",p->id);
	else
		printf(", LeftChild = %d",p->leftChild->id);
	if(p->rightChild == NULL)
		printf(" Node %d does not have a rightChild\n",p->id);
	else
		printf(", RightChild= %d\n",p->rightChild->id);
}

int count(Node *p){
	if (p == NULL)
		return 0;
	return (1 + count(p->leftChild) + count(p->rightChild));
}

void printLeaves(Node *p){
    if(p == NULL)
        return;
    if(p->leftChild == NULL && p ->rightChild == NULL)
        printf("%d ",p->id);
    printLeaves(p->leftChild);
    printLeaves(p->rightChild);
}

int height(Node *p){
	if(p == NULL)
		return 0;
	int maxH = 0;
	int hl = height(p->leftChild);
	if(maxH < hl)
		maxH = hl;
	int hr= height(p->rightChild);
	if(maxH < hr)
		maxH= hr;
	return maxH + 1;
}

void printTreeF(Node *r, FILE *f){
    if(r == NULL)
        return;
    fprintf(f,"%d ",r->id);
    if(r->leftChild == NULL)
        fprintf(f,"-1 ");
    else
        fprintf(f,"%d ",r->leftChild->id);
    if(r->rightChild == NULL)
        fprintf(f,"-1 ");
    else
        fprintf(f,"%d ",r->rightChild->id);
    fprintf(f,"\n");

    printTreeF(r->leftChild,f);
    printTreeF(r->rightChild,f);
}

void store(char *filename){
    FILE* f = fopen(filename,"w");
    printTreeF(root,f);
    fprintf(f,"-2");
    fclose(f);
}

void freeTree(Node* r){
	if(r == NULL)
		return;
	freeTree(r->leftChild);
	freeTree(r->rightChild);
	free(r);
	r = NULL;
}

int main(){
    int i;
    int choice;
    int parent, child;
    int id;
    char filename[256];
    Node *p;
    while(1){
        printf("1. Load data\n");
        printf("2. Print\n");
        printf("3. Add Left Child\n");
        printf("4. Add right Child\n");
        printf("5. Find\n");
        printf("6. Count\n");
        printf("7. Print all leaves\n");
        printf("8. Height\n");
        printf("9. Store\n");
        printf("10. Quit\n");
        printf("Enter command: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter filename:");
                scanf("%s", filename);
                load(filename);
                break;

            case 2:
            	printTree(root);
                break;

            case 3:
                printf("Enter the parent's id: ");
                scanf("%d", &parent);
                printf("Enter the child's id: ");
                scanf("%d", &child);
                addLeftChild(parent, child);
                break;

            case 4:
            	printf("Enter the parent's id: ");
                scanf("%d", &parent);
                printf("Enter the child's id: ");
                scanf("%d", &child);
                addRightChild(parent, child);
                break;

            case 5:
                printf("Enter id: ");
                scanf("%d", &id);
                Node *p = find(root,id);
                if(p == NULL)
                	printf("Not found %d\n",id);
                else{
                	printf("Found node %d: ", id);
                	printChildren(p);
                }
                break;

            case 6:
                printf("The tree have %d nodes\n", count(root));
                break;
            case 7:
                printLeaves(root);
                printf("\n");
                break;
            case 8:
            	printf("Enter id:");
                scanf("%d", &id);
                p = find(root, id);
                printf("The height of the given name is: %d\n", height(p));
                break;
            case 9:
                printf("Enter filename: \n");
                scanf("%s", filename);
                store(filename);
                break;
            case 10:
                freeTree(root);
                return 0;
        }
    }
}
