#include "mbed.h"

// main() runs in its own thread in the OS

PwmOut pwm(PA_8);

double minPluse = 0.0005;
double maxPluse = 0.002;
double range = 180;
static UnbufferedSerial serial_port(USBTX, USBRX);

double outputPluse(int degree){
    double Pwm = (maxPluse - minPluse)/range * degree + minPluse;
    return Pwm;
}

int main()
{
    // パルス幅の設定
    double pulseWidth0 = 0.0005;  // 0.5ms（0度の位置）
    double pulseWidth135 = 0.002;  // 2ms（135度の位置）

    char c[256];
    // 周期の設定（20ms）
    pwm.period(0.02);

    while (true) {
        // 0度を出力
        pwm.pulsewidth(outputPluse(0));
        wait_us(1000000);

        // 135度を出力
        pwm.pulsewidth(outputPluse(180));
        wait_us(1000000);
         int size = sprintf(c,"pwm = %d\n",int(outputPluse(0))*1000);//出力2のデバック
        serial_port.write(&c, size);
    }
}
