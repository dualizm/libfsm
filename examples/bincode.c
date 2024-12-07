#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(ARRAY) \
  sizeof(ARRAY) / sizeof(ARRAY[0])

enum {
  Q0,
  Q1,
};

static Transition transitions[] = {
  {Q0, '0', Q1},
  {Q0, '1', Q1},
  {Q1, '0', Q1},
  {Q1, '1', Q1},
};

static char alphabet[] = "01";
static int states[] = { Q0, Q1 };
static int start_state = Q0;
static int finite_states[] = { Q1 };

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s\n", "Error: too few arguments");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    fprintf(stderr, "%s\n", "Error: too many arguments");
    return EXIT_FAILURE;
  }

  char *input = argv[1];
  size_t input_len = strlen(input);

  FSM fsm;
  fsm_init(&fsm, alphabet,
	   states, ARRAY_SIZE(states),
	   start_state,
	   finite_states, ARRAY_SIZE(finite_states),
	   transitions, ARRAY_SIZE(transitions));

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
  
  return EXIT_SUCCESS;
}
