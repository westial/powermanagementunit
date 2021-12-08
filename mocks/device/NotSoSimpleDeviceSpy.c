#include "NotSoSimpleDeviceSpy.h"
#include <string.h>

int NotSoSimpleDeviceSpy_Sleep(char *content, int size) {
  strcpy(not_so_simple_device_content_param_spy, content);
  ++not_so_simple_device_sleep_counter;
  return size;
}