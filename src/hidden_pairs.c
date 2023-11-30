#include "hidden_pairs.h"
#include "sudoku.h"
#include<stdio.h>
#include<stdlib.h>

bool is_hidden_pair(Cell **p_cells, int value1, int value2){
    int count = 0;
    for (int i =0; i < BOARD_SIZE; i++){
        if(is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2)){
            count ++;
        }

    }
    return (count ==2);
}

bool is_in_cell_hp(Cell *p_cells, int value1, int value2){
    return (is_candidate(p_cells, value1) && is_candidate(p_cells, value2));
}

int find_hidden_pair_values(Cell **p_cells, int *hidden_pair_values){
    int hidden_pair_count = 0;
    int hidden_pair_array[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++){
        hidden_pair_array[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates >= 2){
            int* candidate_array = get_candidates(p_cells[i]); 
            for (int j = 0; j < p_cells[i]->num_candidates; j++){
                hidden_pair_array[candidate_array[j]-1] += 1; 
            }
            free(candidate_array);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (hidden_pair_array[i] == 2){
                hidden_pair_values[hidden_pair_count++] = i+1;                  
        }
    }
    return hidden_pair_count;
}

void find_hidden_pair(Cell **p_cells, HiddenPair *p_hidden_pair, int *p_counter)
{
    int hidden_pair_value_array[BOARD_SIZE];
    int num_value = find_hidden_pair_values(p_cells, hidden_pair_value_array);

    for (int i = 0; i < num_value - 1; i++)
    {
        for (int j = i + 1; j < num_value; j++)
        {
            if (is_hidden_pair(p_cells, hidden_pair_value_array[i], hidden_pair_value_array[j]))
            {
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    if (is_in_cell_hp(p_cells[k], hidden_pair_value_array[i], hidden_pair_value_array[j]))
                    {
                        HiddenPair hidden_pair_element;
                        hidden_pair_element.value1 = hidden_pair_value_array[i];
                        hidden_pair_element.value2 = hidden_pair_value_array[j];
                        hidden_pair_element.p_cells[0] = p_cells[k]; // First cell
                        hidden_pair_element.p_cells[1] = p_cells[k + 1]; // Second cell
                        p_hidden_pair[(*p_counter)++] = hidden_pair_element;
                    }
                }
            }
        }
    }
}


int hidden_pairs(SudokuBoard *p_board)
{
    HiddenPair p_hidden_pair[BOARD_SIZE*BOARD_SIZE];
    int p_counter = 0;
    for (int i = 0; i< BOARD_SIZE; i++){
        find_hidden_pair(p_board->p_cols[i], p_hidden_pair, &p_counter);
        find_hidden_pair(p_board->p_rows[i], p_hidden_pair, &p_counter);
        find_hidden_pair(p_board->p_boxes[i], p_hidden_pair, &p_counter);
    }
    int repeated = p_counter;
    for (int i = 0; i < p_counter; i++){
        int count = 0;
        Cell **p_cells = p_hidden_pair[i].p_cells;
        int* candidate_array = get_candidates(*p_cells);
        int num_candidates = (*p_cells)->num_candidates;

        for (int index = 0; index < num_candidates; index++){
            if ((candidate_array[index] != p_hidden_pair[i].value1) && (candidate_array[index] != p_hidden_pair[i].value2)){
                unset_candidate(*p_cells, candidate_array[index]);
                count = 1;
            }
        }

        repeated -= count;
        free(candidate_array);
    }
    return (p_counter - repeated)/2;
}

