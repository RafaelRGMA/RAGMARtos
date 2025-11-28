#include "RAGMARtos.h"

uint8_t blue = (1<<0);
uint8_t red = (1<<1);
uint8_t green = (1<<2);
uint8_t yellow = (1<<3);



void blink(void* param){
    call_driver(DRVR_LED, LED_TOGGLE,param);
}

void button_green(){
    uint8_t valor = (1<<2);
    if(PINC&(1<<1)){
        call_driver(DRVR_LED, LED_ON,&valor);
        set_process_suspended(1);
    }else{
        call_driver(DRVR_LED, LED_OFF,&valor);
        set_process_ready(1);
    }
}
int main(void){
    create_kernell(6);
    uint8_t port = 0b00111111;
    init_driver(DRVR_LED, &port);
    kernell_add_process(blink,&blue,1, 1000, false);
    kernell_add_process(blink,&red,1, 500, false);
    kernell_add_process(button_green,NULL,3, 10, false);
    kernell_add_process(blink,&yellow,1, 250, false);
    while(1){
        kernell_init();
    }
    return 0;
}
