#include "DriverLCD.h"

driver drvr_lcd;
procedure list_LCD[END_LCD];

uint8_t format_data(uint8_t raw_data){
    PORTB  &= ~EN;
    uint8_t data;
    uint8_t port_data;
    
    port_data = PINB;
    port_data &= 0b11110000;
    raw_data  &= 0b00001111;
    data = port_data | raw_data;
    return data;
}

void send(){
    PORTB |= EN;
    _delay_ms(2);
    PORTB &= ~EN; 
}

void function_set(){
    uint8_t raw_data = 0b00101100;
    PORTB &= ~RS;
    /*
     * Inverte-se a palavra do dado para enviar o nibble mais significativo
     * pelo nibble menos significativo da porta de dados
     */
    PORTB = format_data((raw_data<<4)|(raw_data>>4));
    send();
    send();
    PORTB = format_data(raw_data);
    send();
}

uint8_t display_setup_item(){
    uint8_t raw_data = 0b00001111;
    PORTB &= ~RS;
    
      /*
     * Inverte-se a palavra do dado para enviar o nibble mais significativo
     * pelo nibble menos significativo da porta de dados
     */
    PORTB = format_data((raw_data<<4)|(raw_data>>4));
    send();
    PORTB = format_data(raw_data);
    send();
    return 0;
}

uint8_t print_char(void* byte){
    uint8_t raw_data = *((uint8_t*)byte);
    PORTB |= RS;
      /*
     * Inverte-se a palavra do dado para enviar o nibble mais significativo
     * pelo nibble menos significativo da porta de dados
     */
    PORTB = format_data((raw_data<<4)|(raw_data>>4));
    send();
    PORTB = format_data(raw_data);
    send();
    return 0;
}



uint8_t LCD_init(){
    DDRB |= 0b00111111;
    PORTB &= 0b1100000;
    
    function_set();
    //Display ON/OFF
    display_setup_item();
    return 0;
}


driver* get_lcd_driver(){
    list_LCD[SETUP_ITEM] = display_setup_item;
    list_LCD[PRINT_CHAR] = print_char;
    drvr_lcd.driver_init = LCD_init;
    drvr_lcd.driver_methods = list_LCD;
    return &drvr_lcd;
}
