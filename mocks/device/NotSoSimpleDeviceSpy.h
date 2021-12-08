#ifndef POWERMANAGEMENTUNIT_MOCKS_DEVICE_NOTSOSIMPLEDEVICESPY_H_
#define POWERMANAGEMENTUNIT_MOCKS_DEVICE_NOTSOSIMPLEDEVICESPY_H_

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_LENGTH 100

extern int not_so_simple_device_sleep_counter;
extern char not_so_simple_device_content_param_spy[INPUT_LENGTH];

extern int not_so_simple_device_wake_up_counter;

int NotSoSimpleDeviceSpy_Sleep(char *content, int size);

int NotSoSimpleDeviceSpy_WakeUp(char *content, int size);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_MOCKS_DEVICE_NOTSOSIMPLEDEVICESPY_H_
