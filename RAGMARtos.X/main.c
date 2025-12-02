#include "RAGMARtos.h"

uint8_t blue = (1<<0);
uint8_t red = (1<<1);
uint8_t green = (1<<2);
uint8_t yellow = (1<<3);
uint8_t purple = (1<<4);



void blink(void* color){
    call_driver(DRVR_LED, LED_TOGGLE,color);
}

void button(void* color){
    if(PINC&(1<<1)){
        call_driver(DRVR_LED, LED_ON,color);
        set_process_suspended(0);
    }else{
        call_driver(DRVR_LED, LED_OFF,color);
        set_process_ready(0);
    }
}
int main(void){
    uint8_t symbol = 0x26;
    create_kernell(5);
    init_driver(DRVR_LCD, NULL);
    call_driver(DRVR_LCD,PRINT_CHAR, &symbol);
    
    /*uint8_t port = 0b00111111;
    uint8_t count = 10;
    //call_driver(uint8_t id, uint8_t procedure_id, void* params);
    init_driver(DRVR_LED, &port);
    
    init_driver(DRVR_COUNTER16, &count);
    call_driver(DRVR_COUNTER16,ISR_THREAD, blink);
    call_driver(DRVR_COUNTER16,ISR_PARAM, &purple);
    
    kernell_add_process(blink,&blue,1, 1000, false);
    kernell_add_process(blink,&red,1, 500, false);
    kernell_add_process(blink,&green,1, 250, false);
    kernell_add_process(blink,&yellow,1, 125, false);
    kernell_add_process(button,&purple,3, 10, false);*/
    
    kernell_init();
    
    return 0;
}
