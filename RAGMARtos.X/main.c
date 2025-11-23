#include "RAGMARtos.h"


void blink_blue(){
    uint8_t valor = (1<<0);
    call_driver(DRVR_LED, LED_TOGGLE,&valor);
}

void blink_red(){
    uint8_t valor = (1<<1);
    call_driver(DRVR_LED, LED_TOGGLE,&valor);
}

void blink_green(){
    uint8_t valor = (1<<2);
    call_driver(DRVR_LED, LED_TOGGLE,&valor);
}

void blink_yellow(){
    uint8_t valor = (1<<3);
    call_driver(DRVR_LED, LED_TOGGLE,&valor);
}

void button_yellow(){
    PORTB = (PINC&(1<<0))?PORTB|(1<<3):PORTB&(~(1<<3));
}

void button_green(){
    uint8_t valor = (1<<2);
    if(PINC&(1<<1)){
        call_driver(DRVR_LED, LED_ON,&valor);
    }else{
        call_driver(DRVR_LED, LED_OFF,&valor);
    }
}
int main(void){
    create_kernell();
    init_driver(DRVR_LCD,NULL);
    while(1){
        kernell_init();
    }
    return 0;
}
