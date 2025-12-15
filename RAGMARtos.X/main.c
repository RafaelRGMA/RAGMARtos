#include "RAGMARtos.h"
#include "LibLCD.h"

uint8_t contagem = 0;
char label[9] = "label: 0";

void contar_lote(){
    contagem = (contagem == 9)?0:contagem+1;
    label[7] = (contagem + 0x30);
}


int main(void){
    uint16_t maximo = 5;
    create_kernell(1);
    init_driver(DRVR_COUNTER16, &maximo);
    call_driver(DRVR_COUNTER16,ISR_THREAD,contar_lote);
    call_driver(DRVR_COUNTER16,ISR_PARAM,NULL);
    lcd_start();
   
    kernell_add_process(task_print_string, label, 3,25,false);
    kernell_init();
    return 0;
}
