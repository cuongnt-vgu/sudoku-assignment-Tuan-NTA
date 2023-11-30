#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl {
    Cell *p_cells[2];
    int value1;
    int value2;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);

bool is_hidden_pair(Cell **p_cells, int value1, int value2);
bool is_in_cell_hp(Cell *p_cell, int value1, int value2);

int find_hidden_pair_values(Cell **p_cells, int *hidden_pair_values);
void find_hidden_pair(Cell **p_cells, HiddenPair *p_hidden_pair, int *p_counter);
