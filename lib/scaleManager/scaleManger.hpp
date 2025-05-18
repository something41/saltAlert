#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

typedef struct 
{
    NAU7802 driver;
    float bOffset;
    float scaler;
    uint32_t rawReading;
    float cachedValueFiltered;
    float rollingAverageFilterAmount;

} scaleManager_t;

void scaleManager__init(scaleManager_t * scaleManager);

int32_t scaleManager__update(scaleManager_t * scaleManger);

int32_t scaleManager__getScaledValue(scaleManager_t * scaleManager);

uint32_t scaleManager__getRawValue(scaleManager_t * scaleManager);

bool scaleManger__tare(scaleManager_t * scaleManager);

int32_t scaleManager__getFilteredValue(scaleManager_t * scaleManager);


#define SCALE_MANAGER_INIT(_bOffset, _scaler, _rollingAverageFilterAmount) \
{ \
    .driver = {}, \
    .bOffset = _bOffset, \
    .scaler = _scaler, \
    .rawReading = 0, \
    .rollingAverageFilterAmount = _rollingAverageFilterAmount, \
}