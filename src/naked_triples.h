#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell;
    int value1;
    int value2;
    int value3;
} NakedTriple;

int naked_triples(SudokuBoard *p_board);
int find_naked_triples(Cell ** p_cells, int counter);