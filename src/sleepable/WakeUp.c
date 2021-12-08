#include "WakeUp.h"

int WakeUp(Sleepable instance) {
  return 0 <= Sleepable_TurnOn(instance) ? 1 : -1;
}
