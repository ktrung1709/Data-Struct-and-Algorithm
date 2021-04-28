#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct Node{
    int row, col;
    int step;
    struct Node *next, *parent;
}Node;

Node *head, *tail;

Node* listNode[MAX*MAX];// mảnglưucácphầntửđượccấpphátđộng, đểgiảiphóngBN
int szList= 0;// sốphầntửcủalistNode
int A[MAX][MAX];
int n,m;
int r0,c0;
int visited[MAX][MAX];
const int dr[4] = {1,-1,0,0};
const int dc[4] = {0,0,1,-1};
Node* finalNode;

Node *makeNode(int row, int col, int step, Node *parent){
    Node *node = (Node*)malloc(sizeof(Node));
    node->row = row;
    node->col = col;
    node->next = NULL;
    node->step = step;
    node->parent = parent;
    return node;
}

void initQueue(){
    head = NULL;
    tail = NULL;
}

int queueEmpty(){
    return (head == NULL && tail == NULL);
}

void pushQueue(Node *node){
    if (queueEmpty())
        head = tail = node;
    else{
        tail->next = node;
        tail = node;
    }
}

Node *popQueue(){
    if (queueEmpty())
        return NULL;
    Node *node = head;
    head = node->next;
    if (head == NULL)
        tail = NULL;
    return node;
}

void input(){
    FILE* f = fopen("maze.txt","r");
    fscanf(f,"%d%d%d%d",&n,&m,&r0,&c0);
    for(int i= 1; i<= n; i++){
        for(int j =1; j <= m; j++){
            fscanf(f,"%d",&A[i][j]);
        }
    }
    fclose(f);
}

int legal(int row, int col){
    return A[row][col] == 0 && !visited[row][col];
}

int target(int row, int col){
    return row < 1 || row > n || col < 1 || col > m;
}

void finalize(){
    for(int i= 0; i< szList; i++){
        free(listNode[i]);
    }
}

void addList(Node* node){// them phan tuvaolistNodede thuchiengiaiphongbonho
    listNode[szList] = node;
    szList++;
}
int main(){
    printf("MAZE\n");
    input();
    for(int r = 1; r <= n; r++)
        for(int c = 1; c <= m; c++)
            visited[r][c] = 0;
    initQueue();
    Node* startNode= makeNode(r0,c0,0,NULL);
    addList(startNode);
    pushQueue(startNode);
    visited[r0][c0]= 1;
    while(!queueEmpty()){
        Node* node = popQueue();
        printf("POP (%d,%d)\n",node->row,node->col);
        for(int k = 0; k < 4; k++){
            int nr = node->row + dr[k];
            int nc= node->col + dc[k];
            if(legal(nr,nc)){
                visited[nr][nc] = 1;
                Node* newNode= makeNode(nr,nc,node->step + 1, node);
                addList(newNode);
                if(target(nr,nc)){
                    finalNode= newNode; 
                    break;
                }
                else
                    pushQueue(newNode);
            }
        }
        
        if(finalNode!= NULL) 
            break;// found solution
    }
    Node* s = finalNode;
    while(s != NULL){
        printf("(%d,%d) ",s->row,s->col);
        s = s->parent;
    }
    finalize();
}