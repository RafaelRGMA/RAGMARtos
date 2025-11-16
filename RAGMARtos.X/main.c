#include "RAGMARtos.h"

void blink_blue(){
    PORTB ^=(1<<0);
}

void blink_red(){
    PORTB ^=(1<<1);
}

void blink_green(){
    PORTB ^=(1<<2);
}

void blink_yellow(){
    PORTB ^=(1<<3);
}

void button_yellow(){
    PORTB = (PINC&(1<<0))?PORTB|(1<<3):PORTB&(~(1<<3));
}

void button_green(){
    PORTB = (PINC&(1<<1))?PORTB|(1<<2):PORTB&(~(1<<2));
}
int main(void){
    DDRB |= (1<<0);
    DDRB |= (1<<1);
    DDRB |= (1<<2);
    DDRB |= (1<<3);
    
    DDRC = 0x00;
    
    create_kernell();
    kernell_add_process(blink_blue, 1000, true);
    kernell_add_process(blink_red, 500, true);
    kernell_add_process(blink_yellow, 100, true);
    kernell_add_process(button_green, 5, true);
    while(1){
        kernell_init();
    }
    return 0;
}
