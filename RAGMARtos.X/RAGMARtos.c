#include "RAGMARtos.h"


struct process{
	task routine;
    void* param;
	int period;
	int remaining_time;
    uint8_t priority;
	bool suspended;
};

struct kernell{
    uint8_t buffer_length;
    uint8_t buffer_max_length;
    struct process* buffer;
	struct process* execute;
};
bool kernell_created = false;
struct kernell kernell;

void load_kernell(uint8_t buffer_max_length){
    load_controller();
    struct process buffer[buffer_max_length];
	kernell.buffer_max_length = buffer_max_length;
    kernell.buffer_length = 0;
    kernell.buffer = buffer;
	kernell.execute = NULL;
    kernell_created = true;
}



void scheduler_process_selection(){ //O(n)
    kernell.execute = NULL;
	for(int i = 0;i < kernell.buffer_length; i++){
        if(kernell.buffer[i].remaining_time <= 0 && (!kernell.buffer[i].suspended)){
            kernell.execute = ((kernell.execute == NULL)||(kernell.execute->priority < kernell.buffer[i].priority))?
                &kernell.buffer[i]:kernell.execute;
        }
    }
}

void schedule_decrement_time(){ //O(n)
	for(int i = 0;i < kernell.buffer_length; i++){
        kernell.buffer[i].remaining_time--;
    }
}

//PUBLIC
void create_kernell(uint8_t max_process_buffer_length){
    if(!kernell_created){
        load_kernell(max_process_buffer_length);
        kernell_created = true;
    } 
}

void set_process_suspended(uint8_t process_buffer_index){
    if(process_buffer_index < kernell.buffer_max_length){
        kernell.buffer[process_buffer_index].suspended = true;
    }
}

void set_process_ready(uint8_t process_buffer_index){
    if(process_buffer_index < kernell.buffer_max_length){
        kernell.buffer[process_buffer_index].suspended = false;
    }
}

void kernell_add_process(task routine,void* param, uint8_t priority, int period, bool suspended){
	if(kernell.buffer_length < kernell.buffer_max_length){
        struct process process;
        process.routine = routine;
        process.param = param;
        process.period = period;
        process.suspended = suspended;
        process.remaining_time = period;
        process.priority = priority;
        kernell.buffer[kernell.buffer_length] = process;
        kernell.buffer_length++;
    }
}

void kernell_init(){
    TIMSK1 = 0x02; //Timer/Counter1, Output Compare A Match Interrupt Enable
    OCR1AL = 0xFA; //2500 counter * 64=> 10ms
    //OCR1AH = 0x09;
    TCCR1B = 0b00001011; //prescaler 1:64, modo CTC
	sei();
	while(1){
		scheduler_process_selection();
		if(kernell.execute != NULL){
			kernell.execute->routine(kernell.execute->param);
			kernell.execute->remaining_time = kernell.execute->period;
		}
	}
}


ISR(TIMER1_COMPA_vect){
    schedule_decrement_time();
}