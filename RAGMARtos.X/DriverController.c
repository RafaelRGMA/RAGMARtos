#include "DriverController.h"


driver* drvrs_list[DRVR_END];

void load_controller(){
    drvrs_list[DRVR_LED] = get_led_driver();
    drvrs_list[DRVR_LCD] = get_lcd_driver();
    drvrs_list[DRVR_COUNTER16] = get_counter16_driver();
}

uint8_t init_driver(uint8_t id, void* params){
    return drvrs_list[id]->driver_init(params);
}

uint8_t call_driver(uint8_t id, uint8_t procedure_id, void* params){
    return drvrs_list[id]->driver_methods[procedure_id](params); 
}
