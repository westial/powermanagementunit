#include "NotSoSimpleSleepableStub.h"
#include <malloc.h>

typedef struct NotSoSimpleSleepableStruct
{
  SleepableStruct base;
  int (*Sleep)(char *, int);
  char *input;
  int input_size;
} NotSoSimpleSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  NotSoSimpleSleepable self = (NotSoSimpleSleepable) super;
  self->Sleep(self->input, self->input_size);
  return 1;
}

static void destroy(Sleepable super) {
  NotSoSimpleSleepable self = (NotSoSimpleSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {turn_off, destroy};

// -----------------------------------------------------------------------------

Sleepable NotSoSimpleSleepable_Create(
    unsigned char power_threshold,
    int (*sleep)(char *, int),
    char *input,
    int input_size) {
  NotSoSimpleSleepable self = calloc(1, sizeof(NotSoSimpleSleepableStruct));
  self->base.power_threshold = power_threshold;
  self->input = input;
  self->input_size = input_size;
  self->Sleep = sleep;
  return (Sleepable) self;
}

void NotSoSimpleSleepable_InstallInterface() {
  Sleepable_SetInterface(&interface);
}