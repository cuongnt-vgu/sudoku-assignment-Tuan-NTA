#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    Cell **p_cells;
    int value1;
    int value2;
    int value3;
} NakedTriple;

bool is_naked_triple(Cell **p_cells, int value1, int value2,int value3);
bool is_in_naked_triple_cell(NakedTriple *p_array, Cell *p);
bool is_naked_cell_nt(Cell *p_cell, int value1, int value2, int value3);

int find_naked_triple_values(Cell **p_cells, int *naked_triple_values);
void find_naked_triple(Cell **p_cells,NakedTriple *p_naked_triple, int *p_counter);
int naked_triples(SudokuBoard *p_board);