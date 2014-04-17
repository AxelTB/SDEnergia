#include "SD.h"

/** @brief write
  *
  * @todo: document this function
  */
void SD::write(uint8_t c)
{
    this->buffer[this->bufferIndex++]=c; //Save character

    if(this->bufferIndex==BLOCKSIZE) //Block full
    {
        uint16_t wcount=0;
        int16_t index=this->updateIndex(); //Update index
        FatFs.lseek(index*BLOCKSIZE); //Move to the right block
        FatFs.write(this->buffer,BLOCKSIZE,&wcount);
    }
}

/** @brief ~SD
  *
  * @todo: document this function
  */
 SD::~SD()
{

}

/** @brief read
  *
  * @todo: document this function
  */
int16_t SD::read(void *data,size_t dimension)
{

}

/** @brief printf
  *
  * @todo: document this function
  */
int16_t SD::printf(const char *format, ...)
{

}

/** @brief write
  *
  * @todo: document this function
  */
int16_t SD::write(const void *data,size_t dimension)
{

}

/** @brief begin
  *
  * @todo: document this function
  */
uint8_t SD::begin(uint8_t csPin)
{
    this->bufferIndex=0;
}

/** @brief SD
  *
  * @todo: document this function
  */
 SD::SD()
{
    this->bufferIndex=0;
}

