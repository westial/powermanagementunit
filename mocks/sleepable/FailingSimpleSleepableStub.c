#include "FailingSimpleSleepableStub.h"
#include "SleepablePrivate.h"
#include <malloc.h>

typedef struct SimpleSleepableStruct {
  SleepableStruct base;
  void (*Sleep)();
  void (*WakeUp)();
} SimpleSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  return -1;
}

static int turn_on(Sleepable super) {
  return -1;
}

static void destroy(Sleepable super) {
  SimpleSleepable self = (SimpleSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {
    .TurnOff = turn_off,
    .TurnOn = turn_on,
    .Destroy = destroy};

// -----------------------------------------------------------------------------

Sleepable FailingSimpleSleepable_Create(
    unsigned char power_threshold,
    void (*sleep)(),
    void (*wake_up)()) {
  SimpleSleepable self = calloc(1, sizeof(SimpleSleepableStruct));
  Sleepable_Init((Sleepable)self, &interface, power_threshold);
  self->Sleep = sleep;
  self->WakeUp = wake_up;
  return (Sleepable) self;
}