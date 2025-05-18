#include <Arduino.h>
#include "application.hpp"

saltAlert_t saltAlert;

scaleManager_t scaleManagerObj = SCALE_MANAGER_INIT(-3773, 1, 0.01);
scaleManager_t * scaleManager = &scaleManagerObj;


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
	uint32_t currentMillis = millis();

	system__update();

	if (previousValue != scaleManager__getScaledValue(scaleManager))
	{
		//Serial.println(scaleManager__getScaledValue(scaleManager));
		previousValue = scaleManager__getScaledValue(scaleManager);
	}
	//Serial.println(scaleManager__getRawValue(scaleManager));

	systemState_t nextState = systemStates[saltAlert.currentState].function();
	if (nextState != saltAlert.currentState)
	{
		Serial.print(systemState_strings[systemStates[saltAlert.currentState].state]);
		Serial.print("->");
		Serial.println(systemState_strings[systemStates[nextState].state]);
		saltAlert.currentState = nextState;
	}

	waitForNextMs(currentMillis);
}

systemState_t setupState()
{
	return SYSTEM_STATE_MEASUREMENT;
}
systemState_t measurementState()
{
	return SYSTEM_STATE_WAIT;
}
systemState_t waitState()
{
	return SYSTEM_STATE_LOW;
}
systemState_t lowState()
{
	return SYSTEM_STATE_ERROR;
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
}

void system__update()
{
	scaleManager__update(scaleManager);
}

void waitForNextMs(uint32_t currentMs)
{
	while (millis() - currentMs < ONE_MS){}
}
