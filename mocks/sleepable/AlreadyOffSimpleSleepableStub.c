#include "AlreadyOffSimpleSleepableStub.h"
#include "SleepablePrivate.h"
#include <malloc.h>

typedef struct SimpleSleepableStruct {
  SleepableStruct base;
  void (*Sleep)();
} SimpleSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  SimpleSleepable self = (SimpleSleepable) super;
  if (1 == self->base.is_sleeping) return 0;
  self->Sleep();
  self->base.is_sleeping = 1;
  return 1;
}

static void destroy(Sleepable super) {
  SimpleSleepable self = (SimpleSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {turn_off, destroy};

// -----------------------------------------------------------------------------

Sleepable AlreadyOffSimpleSleepable_Create(unsigned char power_threshold, void (*sleep)()) {
  SimpleSleepable self = calloc(1, sizeof(SimpleSleepableStruct));
  self->base.vtable = &interface;
  self->base.power_threshold = power_threshold;
  self->base.is_sleeping = 1;
  self->Sleep = sleep;
  return (Sleepable) self;
}