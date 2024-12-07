#include "fsm.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FSM_LIMIT_CHARS 1024

static bool belongs_alphabet(FSM *fsm, char symbol);
static bool change_state(FSM *fsm, char symbol);
static bool is_finite_state(FSM *fsm);
Transition* exists_transition(FSM *fsm, char symbol);

bool belongs_alphabet(FSM *fsm, char symbol) {
  for(char *p = fsm->alphabet; *p; p++) {
    if(*p == symbol) {
      return true;
    }
  }

  return false;
}

Transition* exists_transition(FSM *fsm, char symbol) {
  for(size_t i = 0; i < fsm->transitions.len; i++) {
    if(fsm->transitions.transition[i].state == fsm->current_state &&
        fsm->transitions.transition[i].symbol == symbol) {
      return &fsm->transitions.transition[i];
    }
  }

  return NULL;
}

bool change_state(FSM *fsm, char symbol) {
  Transition *transition = exists_transition(fsm, symbol);
  if (!transition) return false;

  fsm->current_state = transition->next;

  return true;
}

bool is_finite_state(FSM *fsm) {
  for(size_t i = 0; i < fsm->finite_states.len; i++) {
    if(fsm->finite_states.state[i] == fsm->current_state) {
      return true;
    }
  }

  return false;
}

void fsm_init(FSM* fsm, char *alphabet,
  int *states, size_t states_len, int start_state,
  int *finite_states, size_t finite_states_len,
  Transition *transitions, size_t transitions_len) {

  fsm->alphabet = alphabet;
  fsm->states.state = states;
  fsm->states.len = states_len;
  fsm->current_state = start_state;
  fsm->finite_states.state = finite_states;
  fsm->finite_states.len = finite_states_len;
  fsm->transitions.transition = transitions;
  fsm->transitions.len = transitions_len;
}

FSM_STATUS fsm_validate_input(FSM *fsm, char *input, size_t input_len) {
  for(size_t i = 0; i < input_len; i++) {
    if(!belongs_alphabet(fsm, input[i])) {
      return FSM_FAILURE_UNKNOWN_SYMBOL;
    }

    if(!change_state(fsm, input[i])) {
      return FSM_FAILURE_TRANSITION;
    }

  }

  if(!is_finite_state(fsm)) {
    return FSM_NOT_FINITE_STATE;
  }

  return FSM_SUCCESS;
}

void fsm_transitions_by_alphabet(Transition *to, int state, char *alphabet, int next_state) {
  size_t alphabet_size = strlen(alphabet);

  for (size_t i = 0; i < alphabet_size; i++) {
    to[i] = (Transition){
      state,
      alphabet[i],
      next_state,
    };
  }
}
