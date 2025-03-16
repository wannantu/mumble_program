#ifndef ESP32_H
#define ESP32_H
 
#include "mbed.h"

#define Circle 1
#define Cross  2
#define Square 3
#define Triangle 4
#define Right 5
#define Down 6
#define Left 7
#define Up 8
#define R1 9
#define L1 10
#define R2 11
#define L2 12
#define select 13
#define Start 14
#define L3 15
#define R3 16

class ESP32{
public  :
    bool Button[16];
    int Stick[2];
    ESP32(PinName TX, PinName RX);
    void init(long baudrate);
    bool button(int num);
    void ButtonBit();
    void StickBit();
    void resetBit();
    char data[5];
    int deduck;
 
private :
    static UnbufferedSerial* esp;
    
    int data_size = 5;
    int start_flag = 128;
    int button_data[2];
    void intSerial();

 
};
 
#endif