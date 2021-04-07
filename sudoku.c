#include <stdio.h>

int x[9][9];
int cnt = 0; // Count board(s)

void solution(void){
    printf("Board %d: \n", ++cnt);
    for (int i = 0; i < 9; i++){
        if (i == 0 || i == 3 || i == 6)
            printf("+-------+-------+-------+\n");
        for (int j = 0; j < 9; j++){
            if (j == 0 || j == 3 || j == 6)
                printf("| %d ", x[i][j]);
            else
                printf("%d ", x[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n\n");
}

int check(int v, int r, int c){
	for (int i = 0; i < r; i++)
		if (x[i][c] == v)
			return 0;

	for (int j = 0; j < c; j++)
		if (x[r][j] == v)
			return 0;

	int I = r / 3;
	int J = c / 3;
	int ending_row = r - 3 * I;
	int ending_col = c - 3 * J;

	for (int i = 0; i < ending_row; i++)
		for (int j = 0; j < 3; j++)
			if (x[i + 3 * I][j + 3 * J] == v)
				return 0;

	for (int j = 0; j < ending_col; j++)
		if (x[r][j + 3 * J] == v)
			return 0;

	return 1;
}

void Try(int r, int c) {
	for (int v = 1; v <= 9; v++)
		if (check(v, r, c)){
			x[r][c] = v;
			if (r == 8 && c == 8)
				solution();
			else{
				if (c != 8)
					Try(r, c + 1);
				else
					Try(r + 1, 0);
			}
		}
}

int main(void){
	Try(0, 0);
	return 0;
}