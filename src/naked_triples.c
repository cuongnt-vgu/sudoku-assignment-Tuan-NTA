#include "naked_triples.h"

int find_naked_triples(Cell ** p_cells, int counter){
    for(int i=0; i<BOARD_SIZE-2; i++){
        if(p_cells[i]->num_candidates <= 3){
            for (int j = i+1; j < BOARD_SIZE-1; j++){
                if(p_cells[j]->num_candidates <= 3){
                    for (int m = j+1; m < BOARD_SIZE; m++){
                        if(p_cells[m]->num_candidates <= 3){
                            int triple_candidates[BOARD_SIZE] = {0};
                            for(int index=0; index<BOARD_SIZE; index++){
                                if(p_cells[i]->candidates[index] || p_cells[j]->candidates[index] || p_cells[m]->candidates[index]){
                                    triple_candidates[index] = 1;
                                }
                            }
                            int sum = 0;
                            for(int index=0; index<BOARD_SIZE; index++){
                                sum += triple_candidates[index];
                            }
                            if(sum == 3){
                                for(int t=0; t<BOARD_SIZE; t++){
                                    if(t!=i && t!=j && t!=m){
                                        for(int index=0; index<BOARD_SIZE; index++){
                                            if(triple_candidates[index] && is_candidate(p_cells[t], index+1)){
                                                unset_candidate(p_cells[t], index+1);
                                                counter++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return counter;
}

//split and push the upddate part to naked_triples

int naked_triples(SudokuBoard *p_board)
{
    int counter=0;
    for (int i = 0; i < BOARD_SIZE; i++)
        counter+=find_naked_triples(p_board->p_boxes[i],counter);
    for (int i = 0; i < BOARD_SIZE; i++)
        counter+=find_naked_triples(p_board->p_cols[i],counter);
    for (int i = 0; i < BOARD_SIZE; i++)
        counter+=find_naked_triples(p_board->p_rows[i],counter);
    
    
    
    return counter;
}

