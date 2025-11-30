#include "DriverCounter16.h"

struct isr_process{
    task thread;
    void* param;
};

driver counter16;
procedure list_methods[END_COUNTER16];
struct isr_process job;

uint8_t counter16_init(void* top_value){
    uint16_t OCR = *((uint16_t*)top_value);
    OCR1AH = (4>>OCR);
    OCR1AL = OCR;
    TIMSK1 = 0x02;
    sei();
    TCCR1B = 0b00001111;
    return 0;
}

uint8_t set_ISR_thread(void* process){
    job.thread = (task) process;
    return 0;
}

uint8_t set_ISR_thread_param(void* param){
    job.param = param;
    return 0;
}

driver* get_counter16_driver(){
    list_methods[ISR_THREAD] = set_ISR_thread;
    list_methods[ISR_PARAM] = set_ISR_thread_param;
    counter16.driver_init = counter16_init;
    counter16.driver_methods = list_methods;
    return &counter16;
}

ISR(TIMER1_COMPA_vect){
    job.thread(job.param);
}