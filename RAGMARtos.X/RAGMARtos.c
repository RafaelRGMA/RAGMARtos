#include "RAGMARtos.h"


struct process{
	task routine;
	int period;
	int remaining_time;
	bool reschedule;
	struct process* next;
};

struct kernell{
	Process* buffer_start;
	Process* buffer_end;
	Process* execute;
};

struct kernell* kernell = NULL;
struct kernell* new_kernell(){
	struct kernell* this = (struct kernell*) malloc(sizeof(struct kernell));
	this->buffer_start = NULL;
	this->buffer_end = NULL;
	this->execute = NULL;
	return this;
}

struct process* new_process(task routine, int period, bool reschedule){
	struct process* this = (struct process*) malloc(sizeof(struct process));
	this->routine = routine;
	this->period = period;
	this->reschedule = reschedule;
	this->remaining_time = period;
	this->next = NULL;
	return this;
}

void scheduler_process_selection(){ //O(n)
	//Este algoritmo ainda deverá ser revisado
	struct process* indexable = kernell->buffer_start;
	kernell->execute = NULL;
	while(indexable != NULL){
		if(indexable->remaining_time <= 0){
			kernell->execute = indexable;
			return;
		}
		indexable = indexable->next;
	}
}

void schedule_decrement_time(){ //O(n)
	struct process* indexable = kernell->buffer_start;
	while(indexable != NULL){
		indexable->remaining_time--;
		indexable = indexable->next;
	}
}

//PUBLIC
void create_kernell(){
	if(kernell == NULL){
		kernell = new_kernell();
	}
}

void kernell_add_process(task routine, int period, bool reschedule){
	struct process* process = new_process(routine, period, reschedule);
	if(kernell->buffer_start == NULL){
		kernell->buffer_start = process;
		kernell->buffer_end = process;
		kernell->execute = process;
	}else{
		kernell->buffer_end->next = process;
		kernell->buffer_end = process;
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
		if(kernell->execute != NULL){
			kernell->execute->routine();
			kernell->execute->remaining_time = kernell->execute->period;
		}
	}
}

void terminate_kernell(){
	struct kernell** object = &kernell;
	struct process* before = (*object)->buffer_start;
	struct process* after = (*object)->buffer_start->next;
	while(after != NULL){
		free(before);
		before = NULL;
		before = after;
		after = after->next;
	}
	free(before);
	before = NULL;
	free(*object);
	*object = NULL;
}

ISR(TIMER1_COMPA_vect){
    schedule_decrement_time();
}