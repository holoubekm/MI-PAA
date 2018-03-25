#include "stdafx.h"

#ifdef _WIN32
#include <Windows.h>
double GetWallTime() {
    LARGE_INTEGER time,freq;
    if (!QueryPerformanceFrequency(&freq)){
        return 0;
    }
    if (!QueryPerformanceCounter(&time)){
        return 0;
    }
    return (double)time.QuadPart / freq.QuadPart;
}

double GetCPUTime() {
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    } else {
        return 0;
    }
}

#else
#include <time.h>
#include <sys/time.h>
double GetWallTime() {
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

double GetCPUTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif