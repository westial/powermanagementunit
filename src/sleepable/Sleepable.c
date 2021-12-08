#include "Sleepable.h"

void Sleepable_Init(
    Sleepable instance,
    SleepableInterface interface,
    unsigned char power_threshold) {
  instance->vtable = interface;
  instance->power_threshold = power_threshold;
  instance->is_sleeping = 0;
}

int Sleepable_TurnOff(Sleepable self) {
  if (1 == self->is_sleeping) return 0;
  return self->vtable->TurnOff(self);
}

void Sleepable_Destroy(Sleepable self) {
  self->vtable->Destroy(self);
}