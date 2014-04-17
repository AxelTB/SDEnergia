#ifndef SD_H
#define SD_H

#include "pfatfs.h"


class SD
{
    public:
        SD();
        virtual ~SD();
    protected:
    private:
    PFFS FatFs;
};

#endif // SD_H
