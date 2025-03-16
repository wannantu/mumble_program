#include "mbed.h"

// main() runs in its own thread in the OS
//入力が３つ　デジタル信号が２つPWM信号が１つ

class TA7291P{
    public:
    TA7291P(PinName In1, PinName In2, PinName Verf);
    void output(int IN1, int IN2, float verf);

    private:
    DigitalOut in1;
    DigitalOut in2;
    PwmOut verf;
};

TA7291P::TA7291P(PinName In1, PinName In2, PinName Verf):in1(In1),in2(In2),verf(Verf){
    in1 = 0;
    in2 = 0;
    verf.write(0.0);
}

void TA7291P::output(int IN1, int IN2, float VERF){
    in1.write(IN1);
    in2.write(IN2);
    verf.write(VERF);
}


int main()
{
    TA7291P motor(PF_1,PA_8,PA_1);
    TA7291P motor2(D10,D11,PA_2);
    int in1 = 0;
    int in2 = 0;
    float pwm = 0.0;
    while (true) {
        //モータを正転させる
        in1 = 1;
        in2 = 0;
        pwm = 0.3;
        motor.output(in1,in2,pwm);
        motor2.output(in2,in1,pwm);
        wait_us(500000);

        in1 = 0;
        in2 = 1;
        motor.output(in1,in2,pwm);
        motor2.output(in2,in1,pwm);
        wait_us(500000);

    }
}

