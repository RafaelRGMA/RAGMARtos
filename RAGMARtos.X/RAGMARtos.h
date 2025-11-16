#ifndef AVRTOS
#define AVRTOS


#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct process Process;
typedef void(*task)();

void create_kernell();
void kernell_add_process(task routine, int period, bool reschedule);
void kernell_init();
void terminate_kernell();



#endif

