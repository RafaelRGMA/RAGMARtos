#ifndef DRIVEREEPROM
#define	DRIVEREEPROM

#include "Diver_template.h"

enum{SET_ISR_ROUTINE,SET_ISR_PARAM,SET_MEMORY_ADDR,SET_DATA,
WRITE_EEPROM,READ_EEPROM,END_EEPROM};
driver* get_eeprom_driver();

#endif

