#include "hidden_singles.h"
#include <stdlib.h>

void find_hidden_single_values(Cell *p_cell, int *hidden_single_values)
{
    if (p_cell->num_candidates > 1)
    {
        for (int j = 0; j <= 8; j++)
        {
            if (p_cell->candidates[j] == 1)
            {
                hidden_single_values[j] += 1; 
            }
        }
    }
}

int find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter)
{
    int hidden_single_values[9]; 
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hidden_single_values[i] = 0;
    }

    for (int i = 0; i <= 8; i++)
    {
        find_hidden_single_values(p_cells[i], hidden_single_values);  
    }

    for (int i = 0; i <= 8; i++)
    {
        if (p_cells[i]->num_candidates != 1)
        {
            for (int j = 0; j <= 8; j++)
            {
                if ((hidden_single_values[j] == 1) && (p_cells[i]->candidates[j] == 1)) 
                {
                    HiddenSingle new_hidden_single;
                    new_hidden_single.value = j+1; 
                    new_hidden_single.p_cell = p_cells[i];
                    p_hidden_singles[*p_counter] = new_hidden_single;
                    *p_counter += 1; 
                }
            }
        }
    }
    return *p_counter; 
}

int hidden_singles(SudokuBoard *p_board)
{
    HiddenSingle hidden_singles[BOARD_SIZE*BOARD_SIZE];
    int counter = 0;

    for (int i = 0; i <= 8; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);  
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }

    int repeated = 0;
    for (int i = 0; i < counter; i++)
    {
        
        int is_repeated = 1;
        Cell *p_cell = hidden_singles[i].p_cell;
        for (int j = 0; j <= 8; j++)
        {
            if ((p_cell->candidates[j] == 1) && (j+1 != hidden_singles[i].value))
            {
                unset_candidate(p_cell, j+1);
                is_repeated = 0;
            }
        }
        repeated += is_repeated;
    }
    return counter - repeated; 
}

