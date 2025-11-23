#ifndef AVRTOS
#define AVRTOS


#include "GlobalIncludes.h"
#include "DriverController.h"

typedef struct process Process;
typedef void(*task)();

void create_kernell();
void kernell_add_process(task routine, int period, bool reschedule);
void kernell_init();
void terminate_kernell();



#endif

