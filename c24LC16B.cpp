

#include <stddef.h>
#include "WProgram.h"
#include "c24LC16B.h"
#include "../Wire/Wire.h"

#define address_24LC16B 0b1010

c24LC16B::c24LC16B()
{
   Wire.begin(); 
}

uint8_t c24LC16B::get_HighAddress(int address)
{
    return (uint8_t)((address) >> 8);
}

uint8_t c24LC16B::get_LowAddress(int address)
{
    return (uint8_t)((address & 0xFF));
}

uint8_t c24LC16B::makeDevAddress(int address)
{
    return (uint8_t)((address_24LC16B << 3) | ((this->get_HighAddress(address)) & 0x07));
}

void c24LC16B::write(int address, uint8_t data)
{
    Wire.beginTransmission(this->makeDevAddress(address));
    Wire.send(this->get_LowAddress(address));
    Wire.send(data);
    Wire.endTransmission();
}

void c24LC16B::write(int address, uint8_t* buffer, int length)
{
    int page_i = 0;
    uint8_t c = 0;
    while (c < length){
        Wire.beginTransmission(this->makeDevAddress(address + c));
        Wire.send(this->get_LowAddress(address + c));
        page_i = 0;
        while ((page_i < 16) && (c < length)){
            Wire.send(buffer[c]);
            page_i++;
            c++;
        }
        Wire.endTransmission();
        delay(5);
    }
}

uint8_t c24LC16B::read_byte(int address)
{
    Wire.beginTransmission(this->makeDevAddress(address));
    Wire.send(this->get_LowAddress(address));
    Wire.endTransmission();
    uint8_t rdata = 0x00;
    Wire.requestFrom((this->makeDevAddress(address)), (uint8_t)1);
    if (Wire.available()) 
    {
        rdata = Wire.receive();
    }
    return rdata;
}

int c24LC16B::read_int(int address)
{
    int rdata = 0;
    this->read_buffer(address, (uint8_t*) rdata, sizeof(rdata));
    return rdata;
}

void c24LC16B::read_buffer(int address, uint8_t* buffer, int length)
{
    Wire.beginTransmission(this->makeDevAddress(address));
    Wire.send(this->get_LowAddress(address));
    Wire.endTransmission();
    Wire.requestFrom(this->makeDevAddress(address),(uint8_t)length);
    int c = 0;
    for ( c = 0; c < length; c++ )
     if (Wire.available()) buffer[c] = Wire.receive();
}
