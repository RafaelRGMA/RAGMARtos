#include "LibLCD.h"


uint8_t clear_display = 0X01;
uint8_t second_line = 0b11000000;
uint8_t first_line = 0b10000000;
uint8_t string_index;


uint8_t lcd_start(){
    init_driver(DRVR_LCD, NULL);
    call_driver(DRVR_LCD,SETUP_ITEM,&clear_display);
    call_driver(DRVR_LCD,SETUP_ITEM,&first_line);
    string_index = 0;
    return 0;
}




void task_print_string(void* string_buffer){
    if(((char*)string_buffer)[string_index] != '\0'){
        call_driver(DRVR_LCD,PRINT_CHAR, &((char*)string_buffer)[string_index]);
        string_index++;
        if(string_index == 0x10){
            call_driver(DRVR_LCD,SETUP_ITEM,&second_line);
        }
    }else{
        call_driver(DRVR_LCD,SETUP_ITEM,&first_line);
        string_index = 0;
    }
}



