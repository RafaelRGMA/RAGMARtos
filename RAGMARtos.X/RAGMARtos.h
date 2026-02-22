#ifndef RAGMARTOS
#define RAGMARTOS


#include "GlobalIncludes.h"
#include "Driver_controller.h"

typedef void(*task)(void* param);

void create_kernel(uint8_t max_process_buffer_length);
void kernel_add_process(task routine,void* param, uint8_t priority, int period, bool suspended);
void kernel_init();

void set_process_suspended(uint8_t process_buffer_index);
void set_process_ready(uint8_t process_buffer_index);



#endif

