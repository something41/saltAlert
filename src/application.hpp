#include "scaleManger.hpp"

#define ONE_MS (1)

#define ENUM_GEN(ENUM) ENUM,
#define STRING_GEN(STRING) #STRING,

#define FOREACH_STATE_TYPE(_STATE_) \
    _STATE_(SYSTEM_STATE_SETUP) \
    _STATE_(SYSTEM_STATE_MEASUREMENT) \
    _STATE_(SYSTEM_STATE_WAIT) \
    _STATE_(SYSTEM_STATE_LOW) \
    _STATE_(SYSTEM_STATE_CALIBRATION) \
    _STATE_(SYSTEM_STATE_ERROR) \
    _STATE_(SYSTEM_STATE_MAX)

typedef enum
{
    FOREACH_STATE_TYPE(ENUM_GEN)
} systemState_t;

const char* systemState_strings[] = {
    FOREACH_STATE_TYPE(STRING_GEN)
};

typedef systemState_t (*stateMachineFunction)(void);

typedef struct 
{
    systemState_t state;
    stateMachineFunction function;
} stateMachine_t;

systemState_t setupState();
systemState_t measurementState();
systemState_t waitState();
systemState_t lowState();
systemState_t errorState();
systemState_t calibrationState();

stateMachine_t systemStates[] =
{
    {SYSTEM_STATE_SETUP, setupState},
    {SYSTEM_STATE_MEASUREMENT, measurementState},
    {SYSTEM_STATE_WAIT, waitState},
    {SYSTEM_STATE_LOW, lowState},
    {SYSTEM_STATE_CALIBRATION, calibrationState},
    {SYSTEM_STATE_ERROR, errorState},
};


typedef struct 
{
    systemState_t currentState;
    bool isLastReadingLow;
} saltAlert_t;



void system__init();
void system__update();

void waitForNextMs(uint32_t currentMillis);

