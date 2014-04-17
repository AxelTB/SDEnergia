#ifndef SD_H
#define SD_H

#include "pfatfs.h"
#include <Print.h>

#define BLOCKSIZE 512

class SD
{
    public:
        SD();
        uint8_t begin(uint8_t csPin);
        //uint8_t begin(uint8_t csPin,uint16_t sdDimension);
        int16_t write(const void *data,size_t dimension);
        int16_t printf(const char *format, ...);
        int16_t read(void *data,size_t dimension);
        virtual ~SD();

        virtual void write(uint8_t);
    protected:
    private:
    PFFS FatFs; //Instance the fatfs system

};

#endif // SD_H
