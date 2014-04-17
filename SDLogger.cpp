#include "SDLogger.h"

/** @brief getError
  *
  * @todo: document this function
  */
FRESULT SDLogger::getError()
{
    return this->lastError;
}

/** @brief write
  *
  * @todo: document this function
  */
void SDLogger::write(uint8_t c)
{
    WORD bw;

    lastError=this->FatFs.write(&c,1,&bw);

    //If file not open
    if(err==FR_NOT_OPENED)
    {
        if(this->FatFs.open(LOGFILE)) //If file open fails give up
            return;
        //Reset written byte & error
        this->lastError=0;
        this->byteWritten=0;
        lastError=this->FatFs.write(&c,1,&bw);

    }
    if(bw==1)
        this->byteWritten++; //Increment byte write count

    if(this->byteWritten==BLOCKSIZE)
    {

        this->FatFs.write(0,0,bw); //Finalize Write
        this->FatFs.close(); //Close log file

        this->blockN++; //Switch to next block

        if(this->FatFs.open(INDEXFILE)); //Open Index
        this->FatFs.write(&blockN,sizeof(uint16_t),&bw); //Save block index
        //this->FatFs.read(&index,sizeof(uint16_t),&bw);
        this->FatFs.close(); //Close index file

        this->FatFs.open(LOGFILE); //Re-open logfile
        this->FatFs.lseek(blockN*BLOCKSIZE); //Go to first free block
    }
}

/** @brief Init SDLogger
  *
  * @todo: document this function
  */
FRESULT SDLogger::begin(unsigned char csPin)
{
    //Reset writtend byte & error
    this->lastError=0;
    this->byteWritten=0;

    this->lastError=this->FatFs.begin(csPin,SPIDIVIDER);

    return this->lastError;
}

/** @brief SDLogger
  *
  * @todo: document this function
  */
SDLogger::SDLogger()
{
    this->lastError=0;
    this->byteWritten=0;
}
