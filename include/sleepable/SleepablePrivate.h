#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SleepableInterfaceStruct {
  void (*TurnOff)(Sleepable instance);
  void (*Destroy)(Sleepable instance);
} SleepableInterfaceStruct;

typedef struct SleepableStruct {
  unsigned char power_threshold;
} SleepableStruct;

#ifdef __cplusplus
}
#endif


#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEPRIVATE_H_
