/* 
 * File:   DriverLCD.h
 * Author: rafae
 *
 * Created on 23 de Novembro de 2025, 19:25
 */

#ifndef DRIVERLCD
#define	DRIVERLCD

#define RS (1<<5);
#define EN (1<<4);

#include "Diver_template.h"

enum{PRINT_CHAR,SETUP_ITEM,END_LCD};

driver* get_lcd_driver();
#endif	

