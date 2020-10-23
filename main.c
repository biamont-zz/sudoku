#include<stdio.h>
#include<stdlib.h>
#include "sudoku.h"

int main(){

	FILE *fptr;
	fptr = fopen("teste3","r");
	if(fptr == NULL) printf("Erro em abrir o arquivo.\n");
	
	int*** sudoku = create_matrix();
	int total = 81;

	for(int i=0; i<9; i++){
		for(int j=0;j<9;j++){
			fscanf(fptr, "%d", &sudoku[i][j][0]);  //coloca numero dado na posicao
			if(sudoku[i][j][0] == 0)sudoku[i][j][10] = 9;
			sudoku[i][j][11] = 0;
		}
	}

	print_matrix(sudoku);
	firstRead_matrix(sudoku);
	printf("\n\n\n\n");
	//for(int i = 0; i<12; i++) printf("%d ", sudoku[0][0][i]);
	
	//	for(int i=0; i<12; i++) printf("%d ", sudoku[0][8][i]);
	print_matrix(sudoku);
	printf("\n\n\n\n\n");

	printf("vai comecar a putaria\n");
	for(int i=0; i<9; i++){
		for(int j=0;j<9;j++){
			if(sudoku[i][j][0] == 0){
				for(int k=0; k<9; k++){
					if(sudoku[i][j][k] == 0){
						recheckRow(sudoku, i, j, k);
						recheckCol(sudoku, i, j, k);
						recheckGroup(sudoku,i, j, k);
					}
				}
			}
		}
	}

	print_matrix(sudoku);

	//for(int i=0; i<12; i++) printf("%d ", sudoku[0][8][i]);

	free_matrix(sudoku);

	fclose(fptr);

	return 0;
}