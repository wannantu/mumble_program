#include "mbed.h"

// main() runs in its own thread in the OS

InterruptIn pulse(PA_8);
InterruptIn Bsou(PA_11);
int pluseCounter = 0;//パルス数を数える変数
Timer t;
int pre_pluseCounter=0;

void pulse_count(){
    pluseCounter += 1;
}

void pos_rotet(){
    if(!Bsou.read()){
        pluseCounter += 1;
    }
    else{
        pluseCounter -= 1;
    }
}

int get_rpm(){
    t.stop();
    float time = t.read();
    float rpm = ((pluseCounter-pre_pluseCounter)/time)*60/400.0;
    pre_pluseCounter = pluseCounter;
    t.reset();
    t.start();
    return rpm;
}


static UnbufferedSerial serial_port(USBTX, USBRX);

int main()
{
    char c[256];
    //pulse.rise(&pulse_count);
    pulse.rise(&pos_rotet);
    t.start();
    double rpm = 0; 
    while (true) {
        rpm = get_rpm();
        int size = sprintf(c,"rpm = %d\n",int(rpm));//出力2のデバック
        serial_port.write(&c, size);
        wait_us(500000);

    }
}

