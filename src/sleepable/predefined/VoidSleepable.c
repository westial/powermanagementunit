#include "VoidSleepable.h"
#include "SleepablePrivate.h"
#include <malloc.h>

typedef struct VoidSleepableStruct {
  SleepableStruct base;
  void (*Sleep)();
  void (*WakeUp)();
} VoidSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  VoidSleepable self = (VoidSleepable) super;
  self->Sleep();
  return 1;
}

static int turn_on(Sleepable super) {
  VoidSleepable self = (VoidSleepable) super;
  self->WakeUp();
  return 1;
}

static void destroy(Sleepable super) {
  VoidSleepable self = (VoidSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {
    .TurnOff = turn_off,
    .TurnOn = turn_on,
    .Destroy = destroy
};

// -----------------------------------------------------------------------------

Sleepable VoidSleepable_Create(
    unsigned char power_threshold,
    void (*sleep)(),
    void (*wake_up)()
    ) {
  VoidSleepable self = calloc(1, sizeof(VoidSleepableStruct));
  Sleepable_Init((Sleepable)self, &interface, power_threshold);
  self->Sleep = sleep;
  self->WakeUp = wake_up;
  return (Sleepable) self;
}