#ifndef FSM_H
#define FSM_H
#include <stddef.h>

typedef enum {
  FSM_SUCCESS = 0,
  FSM_FAILURE_TRANSITION = -1,
  FSM_FAILURE_UNKNOWN_SYMBOL = -2,
  FSM_NOT_FINITE_STATE = -3,
} FSM_STATUS;

typedef struct {
  int state;
  char symbol;
  int next;
} Transition;

typedef struct {
  int *state;
  size_t len;
} States;

typedef struct {
  int current_state;
  
  States states;
  States finite_states;
 
  struct {
    Transition *transition;
    size_t len;
  } transitions;
  
  char *alphabet;
} FSM;

void fsm_init(FSM *fsm, char *alphabet,
  int *states, size_t states_len, int start_state,
  int *finite_states, size_t finite_states_len,
  Transition *transitions, size_t transitions_len);

FSM_STATUS fsm_validate_input(FSM *fsm, char *input, size_t input_len);
void fsm_transitions_by_alphabet(Transition *to, int state, char *alphabet, int next_state);

#endif /* FSM_H */
