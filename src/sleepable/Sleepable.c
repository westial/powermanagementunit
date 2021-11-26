#include "Sleepable.h"

static SleepableInterface interface = 0;

void Sleepable_SetInterface(SleepableInterface interface_) {
  interface = interface_;
}

void Sleepable_TurnOff(Sleepable self) {
  interface->TurnOff(self);
}

void Sleepable_Destroy(Sleepable self) {
  interface->Destroy(self);
}