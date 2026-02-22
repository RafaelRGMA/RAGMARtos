#include "RAGMARtos.h"


struct process{
	task routine;
    void* param;
	int period;
	int remaining_time;
    uint8_t priority;
	bool suspended;
};

struct kernel{
    uint8_t buffer_length;
    uint8_t buffer_max_length;
    struct process* buffer;
	struct process* execute;
};
bool kernel_created = false;
struct kernel kernel;
struct process* buffer;

void load_kernel(uint8_t buffer_max_length){
    load_controller();
    buffer = (struct process*) malloc(buffer_max_length*sizeof(struct process));
	kernel.buffer_max_length = buffer_max_length;
    kernel.buffer_length = 0;
    kernel.buffer = buffer;
	kernel.execute = NULL;
    kernel_created = true;
}



void scheduler_process_selection(){ //O(n)
    kernel.execute = NULL;
	for(int i = 0;i < kernel.buffer_length; i++){
        if(kernel.buffer[i].remaining_time <= 0 && (!kernel.buffer[i].suspended)){
            kernel.execute = ((kernel.execute == NULL)||(kernel.execute->priority < kernel.buffer[i].priority))?
                &kernel.buffer[i]:kernel.execute;
        }
    }
}

void schedule_decrement_time(){ //O(n)
	for(int i = 0;i < kernel.buffer_length; i++){
        kernel.buffer[i].remaining_time -= (kernel.buffer[i].suspended)?0:1;
    }
}

//PUBLIC
void create_kernel(uint8_t max_process_buffer_length){
    if(!kernel_created){
        load_kernel(max_process_buffer_length);
        kernel_created = true;
    } 
}

void set_process_suspended(uint8_t process_buffer_index){
    if(process_buffer_index < kernel.buffer_max_length){
        kernel.buffer[process_buffer_index].suspended = true;
    }
}

void set_process_ready(uint8_t process_buffer_index){
    if(process_buffer_index < kernel.buffer_max_length){
        kernel.buffer[process_buffer_index].suspended = false;
    }
}

void kernel_add_process(task routine,void* param, uint8_t priority, int period, bool suspended){
	if(kernel.buffer_length < kernel.buffer_max_length){
        struct process process;
        process.routine = routine;
        process.param = param;
        process.period = period;
        process.suspended = suspended;
        process.remaining_time = period;
        process.priority = priority;
        kernel.buffer[kernel.buffer_length] = process;
        kernel.buffer_length++;
    }
}

void kernel_init(){
    TIMSK0 = 0x02; //Timer/Counter1, Output Compare A Match Interrupt Enable
    OCR0A = 0xF9; //249 counter * 64=> 1ms (valor corrigido para maior exatidão)
    TCCR0A = 0x02;//modo CTC
    sei();
    TCCR0B = 0b00000011; //prescaler 1:64
	while(1){
		scheduler_process_selection();
		if(kernel.execute != NULL){
			kernel.execute->routine(kernel.execute->param);
			kernel.execute->remaining_time = kernel.execute->period;
		}
	}
}

ISR(TIMER0_COMPA_vect){
    schedule_decrement_time();
}