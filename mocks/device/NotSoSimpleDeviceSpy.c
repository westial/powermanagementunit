#include "NotSoSimpleDeviceSpy.h"
#include <string.h>

int not_so_simple_device_sleep_counter;
char not_so_simple_device_content_param_spy[INPUT_LENGTH];

int not_so_simple_device_wake_up_counter;

int NotSoSimpleDeviceSpy_Sleep(char *content, int size) {
  strcpy(not_so_simple_device_content_param_spy, content);
  ++not_so_simple_device_sleep_counter;
  return size;
}

int NotSoSimpleDeviceSpy_WakeUp(char *content, int size) {
  strcpy(not_so_simple_device_content_param_spy, content);
  ++not_so_simple_device_wake_up_counter;
  return size;
}