#include<stdio.h>
#include<string.h>
int dem(int n, char word[], char c){
    int count = 0;
    int i;
    for (i=0; i < n; i++)
        if (word[i] == c)
            count++;
    return count;
}
int main(){
    int i = 0;
    char word[30];
    printf("Enter the input line: "); gets(word);
    int letter = 0;
    while (word[i] != '\0'){
        letter++;
        i++;
    }
    for (i = 0; i < letter; i++)
        printf("The letter %c appears %d time(s)\n", word[i], dem(letter, word, word[i]));
}
