#include <stdio.h>
void replace(char line[], char a, char b){
int i = 0;
while (line[i] != '\0'){
    if (line[i] == a)
        line[i] = b;
    i++;
}
}
void main(){
char line[50];
char a, b;
printf("Enter a string (no space): ");
gets(line);
printf("Enter the first character: ");
scanf("%c", &a);
fflush(stdin);
printf("Enter the second character: ");
scanf("%c", &b);
replace(line, a, b);
printf("%s", line);
}
