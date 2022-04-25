#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include "stdio.h"
#include "string.h"
#include "math.h"
#include <stdlib.h>

#define BUFFERSIZE 15




typedef enum ERROR_TYPE{
NO_ERR = 0,
OVER_FLOW_ERR,
SYSTEM_ERR,
FATAL_ERR,
ERR_MAX
}Error_Type;

#endif // _RING_BUFFER_H_
