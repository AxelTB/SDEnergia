#ifndef SDLOGGER_H
#define SDLOGGER_H
#include <pfatfs.h>
#include <Print.h>

#define SPIDIVIDER 2
#define BLOCKSIZE 512

#define LOGFILE     "log.txt"
#define LOGSIZE     524288000l //500 MB
#define INDEXFILE   "index.ax"

class SDLogger : public Print
{
public:
    SDLogger();
#if _SoftSPI
   //FRESULT begin (unsigned char,unsigned char,unsigned char,unsigned char);
#else
    FRESULT begin (unsigned char);
#endif

    virtual size_t write(uint8_t);
    FRESULT getError();


protected:
private:
    uint16_t byteWritten,blockN;
    FRESULT lastError;
    PFFS FatFs;


    FRESULT loadIndex();
    FRESULT saveIndex();
};

#endif // SDLOGGER_H
