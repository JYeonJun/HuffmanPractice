#ifndef _MY_TIMER_
#define _MY_TIMER_

#include "public.h"

class Timer {   // �ð��� �����ϴ� Ŭ����
public:
    Timer();
    void Reset();   // ���� �ð��� reset�ϴ� �Լ�
    clock_t RunTime();  // ���� ���� �ð��� ��ȯ�ϴ� �Լ�
    double ElapsedTime();   // �ҿ� �ð��� ��ȯ�ϴ� �Լ�

private:
    clock_t start_clock_;   // ���� �ð�
};

#endif