#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    char c;
    struct Node *next;
}Node;

Node *top;

Node *makeNode(char x){
    Node *p = (Node*) malloc(sizeof(Node));
    p->c = x;
    p->next = NULL;
    return p;
}

void init(){
    top = NULL;
}

int isEmpty(){
    return (top == NULL);
}

void push(char x){
    Node *p = makeNode(x);
    p->next = top;
    top = p;
}

char pop(){
    if(isEmpty())
        return ' ';
    char x = top->c;
    Node* tmp = top;
    top = top->next;
    free(tmp);
    return x;
}

int match(char a, char b){
    if (a == '(' && b==')') return 1;
    if (a == '[' && b==']') return 1;
    if (a == '{' && b=='}') return 1;
    return 0;
}

int check(char *s){
    init();
    for (int i=0; i<strlen(s); i++){
        if (s[i]=='(' || s[i]=='[' || s[i]=='{')
            push(s[i]);
        else{
            if (isEmpty())
                return 0;
            char x = pop();
            if(!match(x, s[i]))
                return 0;
        }
    }
    return isEmpty();
}

int main(){
    char s[20];
    printf("Enter the string: ");
    scanf("%s", s);
    if (check(s))
        printf("The string is symmetric\n");
    else
        printf("The string is not symmetric\n");
    return 0;
}
