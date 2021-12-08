#include "NotSoSimpleSleepableStub.h"
#include <malloc.h>

typedef struct NotSoSimpleSleepableStruct
{
  SleepableStruct base;
  int (*Sleep)(char *, int);
  int (*WakeUp)(char *, int);
  char *input;
  int input_size;
} NotSoSimpleSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  NotSoSimpleSleepable self = (NotSoSimpleSleepable) super;
  self->Sleep(self->input, self->input_size);
  return 1;
}

static int turn_on(Sleepable super) {
  NotSoSimpleSleepable self = (NotSoSimpleSleepable) super;
  self->WakeUp(self->input, self->input_size);
  return 1;
}

static void destroy(Sleepable super) {
  NotSoSimpleSleepable self = (NotSoSimpleSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {
    .TurnOff = turn_off,
    .TurnOn = turn_on,
    .Destroy = destroy
};

// -----------------------------------------------------------------------------

Sleepable NotSoSimpleSleepable_Create(
    unsigned char power_threshold,
    int (*sleep)(char *, int),
    int (*wake_up)(char *, int),
    char *input,
    int input_size) {
  NotSoSimpleSleepable self = calloc(1, sizeof(NotSoSimpleSleepableStruct));
  Sleepable_Init((Sleepable)self, &interface, power_threshold);
  self->input = input;
  self->input_size = input_size;
  self->Sleep = sleep;
  self->WakeUp = wake_up;
  return (Sleepable) self;
}