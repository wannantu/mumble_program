#include "esp32.h"

// 静的メンバ変数の定義および初期化
UnbufferedSerial* ESP32::esp = nullptr;

ESP32::ESP32(PinName TX, PinName RX) {
    esp = new UnbufferedSerial(TX, RX);  // 初期化
    esp->format(8, SerialBase::None, 1);
}

void ESP32::init(long baudrate) {
    esp->baud(baudrate);
    esp->attach(callback(this, &ESP32::intSerial), SerialBase::RxIrq);
}

bool ESP32::button(int num) {
    return Button[num - 1];
}

void ESP32::ButtonBit() {
    for (int i = 0; i < 8; i++) {
        if (button_data[0] & (1 << i)) {
            Button[i] = 1;
        } else {
            Button[i] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (button_data[1] & (1 << i)) {
            Button[i + 8] = 1;
        } else {
            Button[i + 8] = 0;
        }
    }
}

void ESP32::StickBit() {
    Stick[0] = data[3];
    Stick[1] = data[4];
}

void ESP32::resetBit() {
    for (int i = 0; i < 16; i++) {
        Button[i] = 0;
    }
    Stick[0] = 0;
    Stick[1] = 0;
}

void ESP32::intSerial() {
    for(int i = 0; i < 5; i++){
        esp->read(&data[i], 1);
    }
    if (data[0] == start_flag) {
        button_data[0] = data[1];
        button_data[1] = data[2];
        ButtonBit();
        StickBit();
    } else {
        resetBit();
    }
}
