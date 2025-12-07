#ifndef DRIVER_LED
#define	DRIVER_LED

#include "Diver_template.h"

enum {LED_ON, LED_OFF, LED_TOGGLE, END_LED};

driver* get_led_driver();
#endif

