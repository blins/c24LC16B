/* 
 * File:   24LC16B.h
 * Author: blins@yandex.ru
 *
 * Created on 5 Март 2011 г., 9:03
 */

#ifndef c24LC16B_H
#define	c24LC16B_H

#include <inttypes.h>
//#include "../Wire/Wire.h"

//note
//address is 11 bit



class c24LC16B
{
private:
    uint8_t get_HighAddress(int address);
    uint8_t get_LowAddress(int address);
    uint8_t makeDevAddress(int address);
    
public:
    c24LC16B();
    
    //write one byte
    void write(int address, uint8_t data);
    //write buffer
    void write(int address, uint8_t* buffer, int length);
    
    uint8_t read_byte(int address);
    int read_int(int address);
    void read_buffer(int address, uint8_t* buffer, int length);
    
};

#endif	/* c24LC16B_H */

