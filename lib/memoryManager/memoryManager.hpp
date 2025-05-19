#define RTC_MEMORY_SIZE (512)

typedef  unsigned char rawRTCDataType_t;

void memoryManager__init();
void memoryManager__write();
void memoryManager__read();
rawRTCDataType_t * memoryManager__getBuffer();
