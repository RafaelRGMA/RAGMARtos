#include "DriverLed.h"



driver drvr_led;
procedure list_methods[END];


uint8_t led_init(void* param){
    DDRB |= *((uint8_t*)param);
    return 0;
}

uint8_t led_on(void* param){
    PORTB |= *((uint8_t*)param);
    return 0;
}

uint8_t led_off(void* param){
    PORTB &= ~*((uint8_t*)param);
    return 0;
}

uint8_t led_toggle(void* param){
    PORTB ^= *((uint8_t*)param);
    return 0;
}

driver* get_led_driver(){
    drvr_led.driver_init = led_init;
    list_methods[LED_ON] = led_on;
    list_methods[LED_OFF] = led_off;
    list_methods[LED_TOGGLE] = led_toggle;
    drvr_led.driver_methods = list_methods;
    return &drvr_led;
}
