#ifndef DRIVERCOUNTER16
#define	DRIVERCOUNTER16

#include "Diver_template.h"
#include "GlobalIncludes.h"
#include "RAGMARtos.h"

enum{ISR_THREAD, ISR_PARAM, END_COUNTER16};

typedef void(*task)(void* param);
driver* get_counter16_driver();
#endif