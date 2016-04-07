#include "random.h"

#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>
#include <sys/time.h>

uint32_t random_value()
{
        struct timeval te;
        gettimeofday(&te, NULL); // get current time
        long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
        return ((milliseconds * rand()) & ULONG_MAX);
}

