#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"

void print_matrix(int*** matrix){

	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			//for(int k=0; k<9; k++){
				printf("%d ", matrix[i][j][0]);
				//if(k == 2 || k == 5) printf("\t");
			//}
			if(j == 2 || j== 5) printf("\t");
			
		}
		printf("\n");
		if(i == 2 || i== 5) printf("\n");
	}


	return;
}

void free_matrix(int***matrix){

	for(int i=0;i<9;i++){
		for(int j=0; j<9;j++){
			free(matrix[i][j]);
		}
	} 
	for(int i=0;i<9;i++) free(matrix[i]);
	free(matrix);

	return;
}

int*** create_matrix(){

// o tabuleiro terá uma matriz 9x9 para casa quadradinho para que se possa analisar todas as possibilidades de resultado
	int i, j;
	
	int*** board = (int***)calloc(9, sizeof(int**));  
	//printf("prmeiro calloc ok\n");
	for(i=0;i<9; i++) board[i] = (int**)calloc(9, sizeof(int*));
	//printf("segundo calloc ok\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			board[i][j] = (int*)calloc(12, sizeof(int));
		}
	}
	//printf("terceiro calloc ok\n");


	//printf("retornou\n");
	return board;
}

void recheckRow(int*** sudoku, int row, int col, int pos){ // aqui vc manda o zero
	for(int i=0; i<9; i++){
		if(sudoku[row][i][0] == 0 && sudoku[row][i][pos] == 0 && i != col) return;
	}
	//se chegou aqui significa que esse é o unico numedo que pode ser
	sudoku[row][col][0] = pos;
	sudoku[row][col][10] = 1;
	if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
	
	
}

void recheckCol(int*** sudoku, int row, int col, int pos){ // aqui vc manda o zero
	for(int i=0; i<9; i++){
		if(sudoku[i][col][0] == 0 && sudoku[i][col][pos] == 0 && i != row) return;
	}
	//se chegou aqui significa que esse é o unico numedo que pode ser
	sudoku[row][col][0] = pos;
	sudoku[row][col][10] = 1;
	if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
	
	
}

void recheckGroup(int*** sudoku, int row, int col, int pos){

/*Grupos: 0 a 2, 3 a 5, 6 a 8*/

/* 00 01 02   03 04 05   06 07 08
   10 11 12   13 14 15   16 17 18
   20 21 23   23 24 25   26 27 28 */
	if(0<=row && row<=2){
		if(0<=col && col<=2){
			for(int i = 0; i<3; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10] = 1;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}

		else if(3<=col && col<=5){
			for(int i = 0; i<3; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10] = 1;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}
		else if(6<=col && col<=8){
			for(int i = 0; i<3; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10] = 1;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}
	}

/*30 31 32  33 34 35  36 37 38
  40 41 45  43 44 45  46 47 48
  50 51 52  53 54 55  56 57 58*/

	else if(3<=row && row<=5){
		if(0<=col && col<=2){
			for(int i = 3; i<6; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);

		}
		else if(3<=col && col<=5){
			for(int i = 3; i<6; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);

		}
		else if(6<=col && col<=8){
			for(int i = 3; i<6; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);

		}
	}

	else if(6<=row && row<=8){
		/*60 61 62
		  70 71 72
		  80 81 82*/
		if(0<=col && col<=2){
			for(int i = 6; i<9; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}
		/*63 64 65
		  73 74 75
		  83 84 85*/
		else if(3<=col && col<=5){
			for(int i = 6; i<9; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}
		/*66 67 68
		  76 77 78
		  86 87 88*/
		else if(6<=col && col<=8){
			for(int i = 6; i<9; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][0] == 0 && sudoku[i][j][pos] == 0 && i != row && j != col) return;
				}
			}
			sudoku[row][col][0] = pos;
			sudoku[row][col][10]--;
			if(sudoku[row][col][10] == 1) valid_matrix(sudoku, row, col);
		}
	}

}

/*Lógica: das 12 casas: 
						 
5 0 0 0 0 0 0 0 0 0 0 0  --- casa 0 já veio marcada, outros numeros zererados
0 1 0 0 1 0 0 0 1 0 0 9  --- 1a casa zero (ainda vazia), NÃO podem ser os números com 1 - se só houver 1 zero,
						    essa casa marca o numero correto da casa 0 (do tabuleiro)
						 --- casa 11 mostra quantas possibilidades ainda existem]
						 --- casa 12 é uma flag indicando se a casa já foi visitada ou nao*/


void invalidateRow(int*** sudoku, int row, int col){
//	printf("chegou no invalidateRow\n");
	for(int i=0; i<9; i++){
		if(sudoku[row][i][sudoku[row][col][0]] != 1 && sudoku[row][i][0] == 0){
//			printf("sudoku[%d][%d]\n", row, i);
			sudoku[row][i][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
			sudoku[row][i][10]--;
			if(sudoku[row][i][10] == 1) valid_matrix(sudoku, row, i);
		}
	}

}

void invalidateCollun(int*** sudoku, int row, int col){
//	printf("chgou no invalidate col\nsudoku[%d][%d]\n", row, col);
	for(int i=0; i<9; i++){
		if(sudoku[i][col][sudoku[row][col][0]] != 1 && sudoku[i][col][0] == 0){
			sudoku[i][col][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
			sudoku[i][col][10]--;
			if(sudoku[i][col][10] == 1) valid_matrix(sudoku, i, col);
		}
	}
}

void invalidateGroup(int*** sudoku, int row, int col){
//	printf("chgou no invalidate group\nsudoku[%d][%d]\n", row, col);
/*Grupos: 0 a 2, 3 a 5, 6 a 8*/

/* 00 01 02   03 04 05   06 07 08
   10 11 12   13 14 15   16 17 18
   20 21 23   23 24 25   26 27 28 */
	if(0<=row && row<=2){
		if(0<=col && col<=2){
			for(int i = 0; i<3; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}

		}
		else if(3<=col && col<=5){
			for(int i = 0; i<3; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}

		}
		else if(6<=col && col<=8){
			for(int i = 0; i<3; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}
		}
	}

/*30 31 32  33 34 35  36 37 38
  40 41 45  43 44 45  46 47 48
  50 51 52  53 54 55  56 57 58*/

	else if(3<=row && row<=5){
		if(0<=col && col<=2){
			for(int i = 3; i<6; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}

		}
		else if(3<=col && col<=5){
			for(int i = 3; i<6; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}

		}
		else if(6<=col && col<=8){
			for(int i = 3; i<6; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}

		}
	}

	else if(6<=row && row<=8){
		/*60 61 62
		  70 71 72
		  80 81 82*/
		if(0<=col && col<=2){
			for(int i = 6; i<9; i++){
				for(int j = 0; j<3; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}
		}
		/*63 64 65
		  73 74 75
		  83 84 85*/
		else if(3<=col && col<=5){
			for(int i = 6; i<9; i++){
				for(int j = 3; j<6; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}
		}
		/*66 67 68
		  76 77 78
		  86 87 88*/
		else if(6<=col && col<=8){
			for(int i = 6; i<9; i++){
				for(int j = 6; j<9; j++){
					if(sudoku[i][j][sudoku[row][col][0]] != 1 && sudoku[i][j][0] == 0){
						sudoku[i][j][sudoku[row][col][0]] = 1; //sudoku[linha fixa][coluna nao fixa][numero do sudoku]
						sudoku[i][j][10]--;
						if(sudoku[i][j][10] == 1) valid_matrix(sudoku, i, j);
					}
				}
			}
		}
	}

}
 
void valid_matrix(int*** sudoku, int i, int j){
//	printf("chegou no valid matrix %d %d\n", i ,j);
	if(sudoku[i][j][0] == 0){
		for(int k = 1; k<10; k++){
			if(sudoku[i][j][k] != 1){

			 sudoku[i][j][0] = k; 
	//		printf("novo valor: sudoku[%d][%d] = %d\n", i, j, k);
		}
		}
	}
	if(sudoku[i][j][0] != 0 && sudoku[i][j][11] != 1){
		sudoku[i][j][11] = 1;
		//printf("sudoku[%d][%d] = %d\n", i, j, sudoku[i][j][0]);
	//	printf("vai coemar o invalidate row\n");
		invalidateRow(sudoku, i, j);
		//printf("invalidatwRowOK\n");
		invalidateCollun(sudoku, i, j);
		//printf("invalidateCollunOK\n");
		invalidateGroup(sudoku, i, j);
	//	printf("voltou do invalidate grupo\n");
	//	printf("sudoku[%d][%d] = %d\n", i, j, sudoku[i][j][0]);
		//print_matrix(sudoku);
		//printf("\n\n\n");
	}
}

void firstRead_matrix(int*** sudoku){
	//printf("chegou no 1st read\n");
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9; j++){
			if(sudoku[i][j][0] != 0 && sudoku[i][j][11] != 1){
				//printf("sudoku[%d][%d] = %d\n", i, j, sudoku[i][j][0]);
				invalidateRow(sudoku, i, j);
				//printf("invalidatwRowOK\n");
				invalidateCollun(sudoku, i, j);
				//printf("invalidateCollunOK\n");
				invalidateGroup(sudoku, i, j);
				//printf("invalidateGroupOK\n");
				sudoku[i][j][11] = 1;
			}
		}
	}
}
