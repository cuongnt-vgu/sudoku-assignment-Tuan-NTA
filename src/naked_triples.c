#include "naked_triples.h"
#include <stdlib.h>

bool is_naked_triple(Cell **p_cells, int value1, int value2, int value3){
    int count = 0;
    for (int i =0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates == 3){
            if(is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2) && is_candidate(p_cells[i], value3)){
                count ++;
            }
        }
    }
    return (count == 3);
}

bool is_in_naked_triple_cell(NakedTriple *p_array, Cell *p){
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if ((p_array[i].p_cell1 == p)||(p_array[i].p_cell2 == p)||(p_array[i].p_cell3 == p)){
            return true;
        }
    }
    return false;
}

bool is_naked_triple_cell(Cell *p_cell, int value1, int value2, int value3){
    if (p_cell->num_candidates == 3){
        return (is_candidate(p_cell, value1) && is_candidate(p_cell, value2) && is_candidate(p_cell, value3));
    }
    return 0;
}

int find_naked_triple_values(Cell **p_cells, int *naked_triple_values)
{
    int naked_triple_count = 0;
    int naked_triple_array[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++){
        naked_triple_array[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (p_cells[i]->num_candidates >= 2){
            int* candidate_array = get_candidates(p_cells[i]); 
            for (int j = 0; j < p_cells[i]->num_candidates; j++){
                naked_triple_array[candidate_array[j]-1] += 1; 
            }
            free(candidate_array);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        if (naked_triple_array[i] >= 2){
            naked_triple_values[naked_triple_count++] = i+1;                  
        }
    }
    return naked_triple_count;
}

void find_naked_triple(Cell **p_cells, NakedTriple *p_naked_triple, int *p_counter)
{       
    int naked_triple_value_array[BOARD_SIZE];
    int num_value = find_naked_triple_values(p_cells, naked_triple_value_array);

    for (int i = 0; i < num_value-2; i++){
        for (int j = i+1; j < num_value-1; j++){
            for (int k = j+1; k < num_value; k++){
                if(is_naked_triple(p_cells, naked_triple_value_array[i], naked_triple_value_array[j], naked_triple_value_array[k])){
                    for (int l = 0; l < BOARD_SIZE-2; l++){
                        for (int m = l+1; m < BOARD_SIZE-1; m++){
                            for (int n = m+1; n < BOARD_SIZE; n++){
                                if (is_naked_triple_cell(p_cells[l], naked_triple_value_array[i], naked_triple_value_array[j], naked_triple_value_array[k]) && 
                                    is_naked_triple_cell(p_cells[m], naked_triple_value_array[i], naked_triple_value_array[j], naked_triple_value_array[k]) &&
                                    is_naked_triple_cell(p_cells[n], naked_triple_value_array[i], naked_triple_value_array[j], naked_triple_value_array[k])){
                                    NakedTriple naked_triple_object;
                                    naked_triple_object.p_cell1 = p_cells[l];
                                    naked_triple_object.p_cell2 = p_cells[m];
                                    naked_triple_object.p_cell3 = p_cells[n];
                                    naked_triple_object.p_cells = p_cells;
                                    naked_triple_object.value1 = naked_triple_value_array[i];
                                    naked_triple_object.value2 = naked_triple_value_array[j];
                                    naked_triple_object.value3 = naked_triple_value_array[k];
                                    p_naked_triple[(*p_counter)++] = naked_triple_object;
                                }
                            }
                        }                
                    }
                }
            }
        }   
    }
}



int naked_triples(SudokuBoard *p_board)
{
    NakedTriple p_naked_triple[BOARD_SIZE*BOARD_SIZE];
    int p_counter = 0;
    for (int i = 0; i< BOARD_SIZE; i++){
        find_naked_triple(p_board->p_cols[i], p_naked_triple, &p_counter);
        find_naked_triple(p_board->p_rows[i], p_naked_triple, &p_counter);
        find_naked_triple(p_board->p_boxes[i], p_naked_triple, &p_counter);
    }
    int repeated = 0;
    NakedTriple solved_cell[BOARD_SIZE*BOARD_SIZE];
    int solved_cell_count = 0;
    for (int i = 0; i < p_counter; i++){
        Cell **p_cells = p_naked_triple[i].p_cells;
        if (is_in_naked_triple_cell(solved_cell, p_naked_triple[i].p_cell1))
        {
            repeated += 1;
            continue;
        }
        solved_cell[solved_cell_count++] = p_naked_triple[i];
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            if (p_cells[k] == p_naked_triple[i].p_cell1 || p_cells[k] == p_naked_triple[i].p_cell2 || p_cells[k] == p_naked_triple[i].p_cell3){
                continue; 
            }
            int* candidate_array = get_candidates(p_cells[k]);
            int num_candidates = p_cells[k]->num_candidates;
            for (int j = 0; j < num_candidates; j++){
                if ((candidate_array[j]== p_naked_triple[i].value1)){
                unset_candidate(p_cells[k], candidate_array[j]);
                }
                if ((candidate_array[j]== p_naked_triple[i].value2)){
                unset_candidate(p_cells[k], candidate_array[j]);
                }
                if ((candidate_array[j]== p_naked_triple[i].value3)){
                unset_candidate(p_cells[k], candidate_array[j]);
                }
            } 
            free(candidate_array);
        }
    }
    return p_counter - repeated;
}


