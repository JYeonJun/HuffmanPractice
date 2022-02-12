#include "public.h"
#include "Timer.h"

Timer::Timer() {    // ��ü ���� �� ��ü�� reset�Ѵ�.
    Timer::Reset();
}

void Timer::Reset() { start_clock_ = clock(); }


clock_t Timer::RunTime() {  // ���� ���� �ð��� ��ȯ�Ѵ�.
    return start_clock_;
}


double Timer::ElapsedTime() {   // �ҿ� �ð��� ��ȯ�Ѵ�.
    clock_t current_clock = clock();
    return ((double)(current_clock - start_clock_) / CLOCKS_PER_SEC);
}