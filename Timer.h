#ifndef _MY_TIMER_
#define _MY_TIMER_

#include "public.h"

class Timer {   // 시간을 측정하는 클래스
public:
    Timer();
    void Reset();   // 시작 시간을 reset하는 함수
    clock_t RunTime();  // 현재 수행 시간을 반환하는 함수
    double ElapsedTime();   // 소요 시간을 반환하는 함수

private:
    clock_t start_clock_;   // 시작 시간
};

#endif