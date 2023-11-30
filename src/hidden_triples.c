#include "hidden_triples.h"

#include<stdio.h>
#include<stdlib.h>

bool is_hidden_triple(Cell **p_cells, int value1, int value2, int value3){
    int count = 0;
    for (int i =0; i < BOARD_SIZE; i++){
        if((is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2) && is_candidate(p_cells[i], value3))||
            (is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2))||
            (is_candidate(p_cells[i], value2) && is_candidate(p_cells[i], value3))||
            (is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value3))){
            count ++;
        }
    }
    return (count ==3);
}

bool is_in_cell_ht(Cell *p_cells, int value1, int value2, int value3){
    return ((is_candidate(p_cells, value1) && is_candidate(p_cells, value2) && is_candidate(p_cells, value3))||
            (is_candidate(p_cells, value1) && is_candidate(p_cells, value2))||
            (is_candidate(p_cells, value2) && is_candidate(p_cells, value3))||
            (is_candidate(p_cells, value1) &&is_candidate(p_cells, value3)));
}

int find_hidden_triple_values(Cell **p_cells, int *hidden_triple_values){
    int hidden_triple_count = 0;
    int hidden_triple_array[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++){
        hidden_triple_array[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates >= 2){
            int* candidate_array = get_candidates(p_cells[i]); 
            for (int j = 0; j < p_cells[i]->num_candidates; j++){
                hidden_triple_array[candidate_array[j]-1] += 1; 
            }
            free(candidate_array);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (hidden_triple_array[i] == 3||hidden_triple_array[i] == 2){
                hidden_triple_values[hidden_triple_count++] = i+1;                  
        }
    }
    return hidden_triple_count;
}

void find_hidden_triple(Cell **p_cells, HiddenTriple *p_hidden_triple, int *p_counter)
{
    int hidden_triple_value_array[BOARD_SIZE];
    int num_value = find_hidden_triple_values(p_cells, hidden_triple_value_array);

    for (int i = 0; i < num_value - 2; i++)
    {
        for (int j = i + 1; j < num_value - 1; j++)
        {
            for (int k = j + 1; k < num_value; k++)
            {
                if (is_hidden_triple(p_cells, hidden_triple_value_array[i], hidden_triple_value_array[j], hidden_triple_value_array[k]))
                {
                    int cell_counter = 0;
                    HiddenTriple hidden_triple_element;
                    hidden_triple_element.value1 = hidden_triple_value_array[i];
                    hidden_triple_element.value2 = hidden_triple_value_array[j];
                    hidden_triple_element.value3 = hidden_triple_value_array[k];

                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (is_in_cell_ht(p_cells[l], hidden_triple_value_array[i], hidden_triple_value_array[j], hidden_triple_value_array[k]))
                        {
                            hidden_triple_element.p_cells[cell_counter++] = p_cells[l];
                        }
                    }

                    if (cell_counter == 3) {
                        p_hidden_triple[(*p_counter)++] = hidden_triple_element;
                    }
                }
            }
        }
    }
}


int hidden_triples(SudokuBoard *p_board)
{
    HiddenTriple p_hidden_triple[BOARD_SIZE*BOARD_SIZE];
    int p_counter = 0;
    for (int i = 0; i< 1; i++){
        //find_hidden_triple(p_board->p_cols[i], p_hidden_triple, &p_counter);
        find_hidden_triple(p_board->p_rows[i], p_hidden_triple, &p_counter);
        //find_hidden_triple(p_board->p_boxes[i], p_hidden_triple, &p_counter);
    }
    int repeated = p_counter;
    for (int i = 0; i < p_counter; i++){
    int count = 0;
    Cell **p_cells = p_hidden_triple[i].p_cells;
    int* candidate_array = get_candidates(*p_cells);
    int num_candidates = (*p_cells)->num_candidates;

    for (int index = 0; index < num_candidates; index++){
        if ((candidate_array[index] != p_hidden_triple[i].value1) && 
        (candidate_array[index] != p_hidden_triple[i].value2) && 
        (candidate_array[index] != p_hidden_triple[i].value3)){
            unset_candidate(*p_cells, candidate_array[index]);
            count = 1;
        }
    }

    repeated -= count;
    free(candidate_array);
}
    return (p_counter - repeated);
}
