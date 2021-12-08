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
  self->is_sleeping = 1;
  return self->vtable->TurnOff(self);
}

int Sleepable_TurnOn(Sleepable self) {
  if (0 == self->is_sleeping) return 0;
  return self->vtable->TurnOn(self);
}

void Sleepable_Destroy(Sleepable self) {
  self->vtable->Destroy(self);
}