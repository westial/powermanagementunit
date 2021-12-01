#include "SimpleSleepableStub.h"
#include "SleepablePrivate.h"
#include <malloc.h>

typedef struct SimpleSleepableStruct {
  SleepableStruct base;
  void (*Sleep)();
} SimpleSleepableStruct;

// Fulfill the interface methods -----------------------------------------------

static int turn_off(Sleepable super) {
  SimpleSleepable self = (SimpleSleepable) super;
  self->Sleep();
  return 1;
}

static void destroy(Sleepable super) {
  SimpleSleepable self = (SimpleSleepable) super;
  free(self);
}

static SleepableInterfaceStruct interface = {turn_off, destroy};

// -----------------------------------------------------------------------------

Sleepable SimpleSleepable_Create(unsigned char power_threshold, void (*sleep)()) {
  SimpleSleepable self = calloc(1, sizeof(SimpleSleepableStruct));
  self->base.vtable = &interface;
  self->base.power_threshold = power_threshold;
  self->Sleep = sleep;
  return (Sleepable) self;
}