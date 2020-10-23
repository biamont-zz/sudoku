#ifndef SUDOKU_H
#define SUDOKU_H

void print_matrix(int*** matrix);
void free_matrix(int***matrix);
int*** create_matrix();
void invalidateRow(int*** sudoku, int row, int col);
void invalidateCollun(int*** sudoku, int row, int col);
void invalidateGroup(int*** sudoku, int row, int col);
void valid_matrix(int*** sudoku, int i, int j);
void firstRead_matrix(int*** sudoku);
void recheckRow(int*** sudoku, int row, int col, int pos);
void recheckCol(int*** sudoku, int row, int col, int pos);
void recheckGroup(int*** sudoku, int row, int col, int pos);

#endif