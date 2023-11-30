#pragma once

#include "sudoku.h"

typedef struct HiddenTriple_impl {
    Cell *p_cells[3];
    int value1;
    int value2;
    int value3;
} HiddenTriple;




bool is_hidden_pair(Cell **p_cells, int value1, int value2);
bool is_in_cell_ht(Cell *p_cells, int value1, int value2,int value3);



int hidden_triples(SudokuBoard *p_board);
int find_naked_triples(Cell ** p_cells, int counter);
int find_hidden_pair_values(Cell **p_cells, int *hidden_pair_values);
