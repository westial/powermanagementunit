#ifndef POWERMANAGEMENTUNIT_MOCKS_SIMPLEDEVICESPY_H_
#define POWERMANAGEMENTUNIT_MOCKS_SIMPLEDEVICESPY_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int simple_device_sleep_counter;
void SimpleDeviceSpy_Sleep();

extern int simple_device_wake_up_counter;
void SimpleDeviceSpy_WakeUp();

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_MOCKS_SIMPLEDEVICESPY_H_
