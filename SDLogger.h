#ifndef SDLOGGER_H
#define SDLOGGER_H
#include <pfatfs.h>

class SDLogger
{
public:
    SDLogger();
#if _SoftSPI
    FRESULT begin (unsigned char,unsigned char,unsigned char,unsigned char);
#else
    FRESULT begin (unsigned char);
#endif

    virtual ~SDLogger();
protected:
private:
    uint16_t byteWritten;
};

#endif // SDLOGGER_H
