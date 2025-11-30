#include "RAGMARtos.h"

uint8_t blue = (1<<0);
uint8_t red = (1<<1);
uint8_t green = (1<<2);
uint8_t yellow = (1<<3);
uint8_t purple = (1<<4);



void blink(void* param){
    call_driver(DRVR_LED, LED_TOGGLE,param);
}

void button_purple(){
    if(PINC&(1<<1)){
        call_driver(DRVR_LED, LED_ON,&purple);
        set_process_suspended(0);
    }else{
        call_driver(DRVR_LED, LED_OFF,&purple);
        set_process_ready(0);
    }
}
int main(void){
    create_kernell(7);
    uint8_t port = 0b00111111;
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
    //kernell_add_process(button_purple,NULL,3, 10, false);
    
    kernell_init();
    
    return 0;
}
