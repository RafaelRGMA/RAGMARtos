#include "DriverADC.h"



driver drvr_adc;
procedure list_ADC[END_ADC];


uint8_t adc_init(void* param){
    DDRC &= ~(1<<0);
    ADMUX |= (1<<6);
    ADCSRA |= 0b11000111;
    return 0;
}

uint8_t convertion(void* digital_result){
    if(!(ADCSRA&(1<<6))){
        ADCSRA |= (1<<6);
        *((uint16_t*)digital_result) = ADC;
    }
    return 0;
}

driver* get_ADC_driver(){
    list_ADC[CONVERTION] = convertion;
    drvr_adc.driver_init = adc_init;
    drvr_adc.driver_methods = list_ADC;
    return &drvr_adc;
}