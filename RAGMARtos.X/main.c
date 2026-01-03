#include "RAGMARtos.h"
#include "LibLCD.h"

struct eeprom_stats{
    uint16_t mem_address;
    uint8_t data;
};

uint8_t contagem = 0;
char label[9] = "label: 0";
struct eeprom_stats stats;

void contar_lote(){
    contagem = (contagem == 9)?0:contagem+1;
    label[7] = (contagem + 0x30);
}

void wrt_eeprom(){
    call_driver(DRVR_EEPROM, SET_MEMORY_ADDR, &stats.mem_address);
    call_driver(DRVR_EEPROM, WRITE_EEPROM, &stats.data);
}


int main(void){
    uint16_t maximo = 5;
    stats.data = 'R';
    stats.mem_address = 0x000F;
    
    
    create_kernell(2);
    init_driver(DRVR_COUNTER16, &maximo);
    init_driver(DRVR_EEPROM, NULL);
    
    call_driver(DRVR_COUNTER16,ISR_THREAD,contar_lote);
    call_driver(DRVR_COUNTER16,ISR_PARAM,NULL);
    lcd_start();
   
    kernell_add_process(task_print_string, label, 3,25,false);
    kernell_add_process(wrt_eeprom, NULL, 3, 100, false);
    kernell_init();
    return 0;
}
