#include "memoryManager.hpp"
extern "C" {
	#include "user_interface.h"
  }

#define RTC_MEMORY_OFFSET_START (64)


static rawRTCDataType_t rtcBuffer[RTC_MEMORY_SIZE] = {0};


void memoryManager__init()
{
    memset(rtcBuffer, 0, RTC_MEMORY_SIZE);
    system_rtc_mem_write(RTC_MEMORY_OFFSET_START, rtcBuffer, RTC_MEMORY_SIZE);
}

void memoryManager__write()
{
    system_rtc_mem_write(RTC_MEMORY_OFFSET_START, rtcBuffer, RTC_MEMORY_SIZE);
}

void memoryManager__read()
{
    system_rtc_mem_read(RTC_MEMORY_OFFSET_START, rtcBuffer, RTC_MEMORY_SIZE);
}

rawRTCDataType_t * memoryManager__getBuffer()
{
    return rtcBuffer;
}

