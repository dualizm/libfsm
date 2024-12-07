#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(ARRAY) \
  sizeof(ARRAY) / sizeof(ARRAY[0])

enum {
  Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10
};

static char alphabetChars[] = "abcdefghijklmnopqrstuvwxyz";
static char alphabetSpecial[] = "!@#$%^&*()";
static char alphabetNumbers[] = "1234567890";

static int states[] = { Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10 };
static int start_state = Q0;
static int finite_states[] = { Q10 };

void target_transition(Transition** it, int target, int a, int b, int c) {
  fsm_transitions_by_alphabet(*it, target, alphabetChars, a);
  *it += ARRAY_SIZE(alphabetChars) - 1;

  fsm_transitions_by_alphabet(*it, target, alphabetSpecial, b);
  *it += ARRAY_SIZE(alphabetSpecial) - 1;

  fsm_transitions_by_alphabet(*it, target, alphabetNumbers, c);
  *it += ARRAY_SIZE(alphabetNumbers) - 1;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Error: too few arguments");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    puts("Error: too many arguments");
    return EXIT_FAILURE;
  }
  
  char *input = argv[1];
  size_t input_len = strlen(argv[1]);
  
  char *alphabet = malloc(sizeof *alphabet * 
			  (ARRAY_SIZE(alphabetChars) - 1 + 
			   ARRAY_SIZE(alphabetSpecial) - 1 +
			   ARRAY_SIZE(alphabetNumbers) - 1) + 1);
  
  strcat(alphabet, alphabetChars);
  strcat(alphabet, alphabetSpecial);
  strcat(alphabet, alphabetNumbers);
  
  size_t transitions_len = (ARRAY_SIZE(alphabetChars) * 11) +
    (ARRAY_SIZE(alphabetSpecial) * 11) +
    (ARRAY_SIZE(alphabetNumbers) * 11);
  Transition *transitions = malloc(sizeof *transitions * transitions_len);
  Transition *it = transitions;
  target_transition(&it, Q0, Q1, Q4, Q7);
  target_transition(&it, Q1, Q1, Q2, Q3);
  target_transition(&it, Q2, Q2, Q2, Q10);
  target_transition(&it, Q3, Q3, Q10, Q3);
  target_transition(&it, Q4, Q5, Q4, Q6);
  target_transition(&it, Q5, Q5, Q5, Q10);
  target_transition(&it, Q6, Q10, Q6, Q6);
  target_transition(&it, Q7, Q8, Q9, Q7);
  target_transition(&it, Q8, Q8, Q10, Q8);
  target_transition(&it, Q9, Q10, Q9, Q9);
  target_transition(&it, Q10, Q10, Q10, Q10);

  FSM fsm;
  fsm_init(&fsm, alphabet, states, ARRAY_SIZE(states), start_state, 
	   finite_states, ARRAY_SIZE(finite_states), 
	   transitions, transitions_len);
  FSM_STATUS status = fsm_validate_input(&fsm, input, input_len);
  
  const char *input_result = NULL;
  switch(status) {
  case FSM_SUCCESS: input_result = "was successful"; break;
  case FSM_FAILURE_TRANSITION: input_result = "an existing transition was not found"; break;
  case FSM_FAILURE_UNKNOWN_SYMBOL: input_result = "an unknown character was found in the string"; break;
  case FSM_NOT_FINITE_STATE: input_result = "the machine is not in one of the finite states"; break;
  }
  
  printf("%s: \"%s\" %s\n",
	 status == FSM_SUCCESS ? "Result for the string" : "Error",
	 input,
	 input_result);
  
  free(transitions);
  free(alphabet);
  
  return EXIT_SUCCESS;
}
