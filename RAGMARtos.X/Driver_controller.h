#ifndef DRIVERCONTROLLER
#define	DRIVERCONTROLLER

#include "Diver_template.h"
#include "DriverLed.h"
#include "DriverLCD.h"
#include "DriverCounter16.h"
#include "DriverADC.h"
#include "DriverEEPROM.h"

enum {DRVR_LED, DRVR_COUNTER16, DRVR_LCD, DRVR_ADC, DRVR_EEPROM, DRVR_END};

uint8_t call_driver(uint8_t id, uint8_t procedure_id, void* params);
uint8_t init_driver(uint8_t id, void* params);
void load_controller();
#endif

