set(HEADER_FILES
        Sleepable.h
        AskToSleep.h
        SleepablePrivate.h
        SleepableBus.h
        WakeUp.h)

add_library(sleepable STATIC ${HEADER_FILES})