#include "Sleepable.h"

static SleepableInterface interface = 0;

void Sleepable_SetInterface(SleepableInterface interface_) {
  interface = interface_;
}

int Sleepable_TurnOff(Sleepable self) {
  return self->vtable->TurnOff(self);
}

void Sleepable_Destroy(Sleepable self) {
  interface->Destroy(self);
}