#ifndef LIBLCD
#define	LIBLCD

#include "DriverLCD.h"
#include "RAGMARtos.h"

uint8_t lcd_start();
void task_print_string(void* string_buffer);

#endif

