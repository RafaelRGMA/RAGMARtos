#include "DriverEEPROM.h"


struct eeprom_isr{
    procedure isr_routine;
    void* isr_param;
};

driver drvr_eeprom;
procedure list_eeprom[END_EEPROM];
struct eeprom_isr eeprom_isr;

uint8_t eeprom_init(void* param){
    eeprom_isr.isr_param = NULL;
    eeprom_isr.isr_routine = NULL;
    return 0;
}

uint8_t set_memory_addr(void* address){
    EEAR = *((uint16_t*)address);
    return 0;
}

uint8_t set_isr_routine(void* routine){
    EECR |= (1<<EERIE);
    eeprom_isr.isr_routine = (procedure) routine;
    return 0;
}

uint8_t set_isr_param(void* param){
    EECR |= (1<<EERIE);
    eeprom_isr.isr_param = param;
    return 0;
}

uint8_t write_eeprom(void* byte_data){
    if(!(EECR&(1<<EEPE))){
        EEDR = *((uint8_t*)byte_data);
        EECR |= (1<<EEMPE);
        EECR |= (1<<EEPE);
    }
    return 0;
}

uint8_t read_eeprom(void* read_var){
    if(!(EECR&(1<<EEPE))){
        EECR |= (1<<EERE);
        *((uint8_t*)read_var) = EEDR;
    }
    return 0;
}

driver* get_eeprom_driver(){
    drvr_eeprom.driver_init = eeprom_init;
    list_eeprom[READ_EEPROM] = read_eeprom;
    list_eeprom[WRITE_EEPROM] = write_eeprom;
    list_eeprom[SET_MEMORY_ADDR] = set_memory_addr;
    list_eeprom[SET_ISR_ROUTINE] = set_isr_routine;
    list_eeprom[SET_ISR_PARAM] = set_isr_param;
    drvr_eeprom.driver_methods = list_eeprom;
    return &drvr_eeprom;
}

ISR(EE_READY_vect){
    eeprom_isr.isr_routine(eeprom_isr.isr_param);
}