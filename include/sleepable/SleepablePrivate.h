#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SleepableInterfaceStruct {
  int (*TurnOff)(Sleepable instance);
  int (*TurnOn)(Sleepable instance);
  void (*Destroy)(Sleepable instance);
} SleepableInterfaceStruct;

typedef struct SleepableStruct {
  SleepableInterface vtable;
  unsigned char power_threshold;
  unsigned char is_sleeping;
} SleepableStruct;

#ifdef __cplusplus
}
#endif


#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_
