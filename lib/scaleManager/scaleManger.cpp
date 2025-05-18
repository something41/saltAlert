#include "scaleManger.hpp"
#include "Wire.h"

void scaleManager__init(scaleManager_t * scaleManager)
{
	Wire.begin();
    scaleManager->driver.begin();
}

int32_t scaleManager__update(scaleManager_t * scaleManager)
{
	if(scaleManager->driver.available() == true)
	{
	  scaleManager->rawReading = scaleManager->driver.getReading();
      scaleManager->cachedValueFiltered  =  scaleManager->cachedValueFiltered - (scaleManager->rollingAverageFilterAmount * (scaleManager->cachedValueFiltered  - scaleManager->rawReading));
	}

    return scaleManager->cachedValueFiltered;
}

int32_t scaleManager__getScaledValue(scaleManager_t * scaleManager)
{
    int32_t value = (scaleManager->cachedValueFiltered * scaleManager->scaler) + scaleManager->bOffset;
    if (value < 0)
    {
        return 0;
    }
    return value;
}

int32_t scaleManager__getFilteredValue(scaleManager_t * scaleManager)
{
    return scaleManager->cachedValueFiltered;
}

uint32_t scaleManager__getRawValue(scaleManager_t * scaleManager)
{
    return scaleManager->rawReading;
}

bool scaleManger__tare(scaleManager_t * scaleManager)
{
    scaleManager->bOffset = scaleManager->rawReading;
    return true;
}

