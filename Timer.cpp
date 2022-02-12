#include "public.h"
#include "Timer.h"

Timer::Timer() {    // 객체 생성 시 객체를 reset한다.
    Timer::Reset();
}

void Timer::Reset() { start_clock_ = clock(); }


clock_t Timer::RunTime() {  // 현재 수행 시간을 반환한다.
    return start_clock_;
}


double Timer::ElapsedTime() {   // 소요 시간을 반환한다.
    clock_t current_clock = clock();
    return ((double)(current_clock - start_clock_) / CLOCKS_PER_SEC);
}