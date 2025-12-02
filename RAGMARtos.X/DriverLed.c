#include "DriverLed.h"



driver drvr_led;
procedure list_LED[END];


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
    list_LED[LED_ON] = led_on;
    list_LED[LED_OFF] = led_off;
    list_LED[LED_TOGGLE] = led_toggle;
    drvr_led.driver_methods = list_LED;
    return &drvr_led;
}
