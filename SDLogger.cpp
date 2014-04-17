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
size_t SDLogger::write(uint8_t c)
{
    WORD bw;

    lastError=this->FatFs.write(&c,1,&bw);

    //If file not open
    if(lastError==FR_NOT_OPENED)
    {
        if(this->FatFs.open(LOGFILE)) //If file open fails give up
            return 0;
        //Reset written byte & error
        this->lastError=FR_OK;
        this->byteWritten=0;
        lastError=this->FatFs.write(&c,1,&bw);

    }

    if(bw==1)
        this->byteWritten++; //Increment byte write count

    if(this->byteWritten==BLOCKSIZE)
    {

        this->FatFs.write(0,0,&bw); //Finalize Write
        this->FatFs.close(); //Close log file

        this->blockN++; //Switch to next block

        saveIndex(); //Save current Block number

        this->FatFs.open(LOGFILE); //Re-open logfile
        this->FatFs.lseek(blockN*BLOCKSIZE); //Go to next free block
    }

    return 1;
}

/** @brief Init SDLogger
  *
  * @todo: document this function
  */
FRESULT SDLogger::begin(unsigned char csPin)
{
    //Reset writtend byte & error
    this->lastError=FR_OK;
    this->byteWritten=0;

    this->lastError=this->FatFs.begin(csPin,SPIDIVIDER);
    if(!this->lastError)
    {
        loadIndex(); //Load last index
        this->lastError=this->FatFs.open(LOGFILE); //Open log File
        this->FatFs.lseek(blockN*BLOCKSIZE);
    }
    return this->lastError;
}

/** @brief SDLogger
  *
  * @todo: document this function
  */
SDLogger::SDLogger()
{
    this->lastError=FR_OK;
    this->byteWritten=0;
}

FRESULT SDLogger::loadIndex()
{
    uint16_t index;
    WORD br;

    if((this->lastError=this->FatFs.open(INDEXFILE))) //Open Index file
        return lastError;


    this->lastError=this->FatFs.read(&index,sizeof(uint16_t),&br); //Read block index


    if(br==2 && index*BLOCKSIZE<LOGSIZE && !lastError) //If all right
        this->blockN=index; //Save block number

    return this->FatFs.close(); //Close index file
}

FRESULT SDLogger::saveIndex()
{
    WORD bw;

    if((this->lastError=this->FatFs.open(INDEXFILE))) //Open Index file
        return lastError;

    this->lastError=this->FatFs.write(&this->blockN,sizeof(uint16_t),&bw); //Save block index

    return this->FatFs.close(); //Close index file

}
