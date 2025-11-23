#ifndef DRIVER_TEMPLATE
#define	DRIVER_TEMPLATE



#include "GlobalIncludes.h"

typedef uint8_t (*procedure)(void* param);
typedef struct {
    procedure driver_init;
    procedure* driver_methods;
}driver;


#endif

