/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <PwmOut.h>

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define MOSI P0_3
#define MISO P0_2
#define SCK P0_4

#define MAX32670_SDA P0_7
#define MAX32670_SCL P0_6

#define MAX32670_SDA1 P0_13
#define MAX32670_SCL1 P0_12


SPI mySPI(MOSI,MISO,SCK);
DigitalOut SSO(P0_5);
//DigitalOut SSO(P0_3);
I2C myI2C(MAX32670_SDA, MAX32670_SCL);

PwmOut myPWM(P0_20);
const uint8_t addr8bit = 0x32;

void SPI_Testing(int data);
void I2C_Testing(uint8_t address, char* data, int length);

int main()
{
    
    char cmd[2];
    cmd[0] = 0xA3;
    cmd[1] = 0x4D;
    
    mySPI.format(8,3);
    mySPI.frequency(1000000);
    
    // Initialise the digital pin LED1 as an output
    DigitalOut led(P0_23);
    
    while (true) {
        //myI2C.start();
        //myI2C.write(addr8bit,cmd,1);
        //myI2C.stop();
        //SSO = 0;
        led = !led;
        //mySPI.write(0x8F);
        //SSO = 1;
        I2C_Testing(addr8bit,cmd,1);
        SPI_Testing(0x8f);
        //ThisThread::sleep_for(BLINKING_RATE);
        thread_sleep_for(1000);
        
    }
}

void I2C_Testing(uint8_t address, char* data, int length){
    myI2C.write(address, data, length);
}

void SPI_Testing(int data){
    SSO = 0;
    mySPI.write(0x8F);
    SSO = 1;

}
