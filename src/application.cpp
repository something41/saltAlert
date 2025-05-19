#include <Arduino.h>
#include "application.hpp"

#include "scaleManger.hpp"

saltAlert_t saltAlert;

scaleManager_t scaleManagerObj = SCALE_MANAGER_INIT(-3773, 1, 0.01);
scaleManager_t * scaleManager = &scaleManagerObj;

rtcData_t * rtcData;

#define ENABLE_PLAYGROUND (0)

uint32_t testCounter = 0;

void setup()
{

	Serial.begin(115200);
	Serial.println("Begin");
	system__init();


	delay(1000);
}

float previousValue = 0;

void loop()
{

#if (ENABLE_PLAYGROUND)
	playGroundState();
	return;
#endif
	uint32_t currentMillis = millis();

	system__update();

	if (previousValue != scaleManager__getScaledValue(scaleManager))
	{
		//Serial.println(scaleManager__getScaledValue(scaleManager));
		previousValue = scaleManager__getScaledValue(scaleManager);
	}
	//Serial.println(scaleManager__getRawValue(scaleManager));

	systemState_t nextState = systemStates[saltAlert.currentState]();
	if (nextState != saltAlert.currentState)
	{
		Serial.print(systemState_strings[saltAlert.currentState]);
		Serial.print("->");
		Serial.println(systemState_strings[nextState]);
		saltAlert.currentState = nextState;
	}

	waitForNextMs(currentMillis);
}

systemState_t playGroundState()
{

	ESP.deepSleep(100);


	return SYSTEM_STATE_PLAYGROUND;
}

systemState_t setupState()
{
	rtcData = (rtcData_t*) memoryManager__getBuffer();

	return SYSTEM_STATE_MEASUREMENT;
}
systemState_t measurementState()
{
	float value = scaleManger__sampleNReadings(scaleManager, 10);
	if (value <= LOW_THRESHOLD_LBS)
	{
		if (saltAlert.isLastReadingLow == false)
		{
			return SYSTEM_STATE_LOW;
		}
	}
	else
	{
		saltAlert.isLastReadingLow = false;
	}

	return SYSTEM_STATE_WAIT;
}
systemState_t waitState()
{
	delay(WAIT_AMOUNT);
	return SYSTEM_STATE_MEASUREMENT;
}
systemState_t lowState()
{
	saltAlert.isLastReadingLow = true;
	Serial.println("do notification");

	return SYSTEM_STATE_WAIT;
}
systemState_t errorState()
{
	return SYSTEM_STATE_CALIBRATION;
}

systemState_t calibrationState()
{
	return SYSTEM_STATE_CALIBRATION;
}

void system__init()
{
	scaleManager__init(scaleManager);
	memoryManager__init();
}

void system__update()
{
	scaleManager__update(scaleManager);
}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS){}
}
