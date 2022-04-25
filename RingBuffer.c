#include "RingBuffer.h"

//unsigned char Ring_Buf[BUFFERSIZE] = {0};
//static unsignedint *Write_Index = Ring_Buf;
//static unsignedint *Read_Index = Ring_Buf;
static unsigned int Abstract_Write_Index = 0;
static unsigned int Abstract_Read_Index = 0;
char * Ring_Buf = NULL;


#if 1
#define RING
#else
#define FIFO
#endif

Error_Type Write_Queue(unsigned char * data,int datalength)
{
    Error_Type ret = NO_ERR;
    int temp_index = 0;
    printf("get into Write function \n");
    if (datalength > BUFFERSIZE)
        ret = OVER_FLOW_ERR;
    else if (datalength > (BUFFERSIZE - Abstract_Write_Index))
    {
        printf("Write Buffer is not enough currently \n");
#ifdef RING
        printf("Write will continue from the head, and be careful, the last data will be rewrote \n");
        if (BUFFERSIZE == Abstract_Write_Index){
            Abstract_Write_Index = 0;
            memcpy(&Ring_Buf[Abstract_Write_Index], data, datalength);
            Abstract_Write_Index = datalength;
        }
        else {
            //printf("1 \n");
            temp_index = BUFFERSIZE-Abstract_Write_Index;
            memcpy(&Ring_Buf[Abstract_Write_Index], data, (BUFFERSIZE-Abstract_Write_Index));
            Abstract_Write_Index = 0;
            //printf("2 \n");
            memcpy(&Ring_Buf[Abstract_Write_Index], (data + temp_index), (datalength -(temp_index)));
            //printf("3 \n");
            Abstract_Write_Index = datalength -(BUFFERSIZE - Abstract_Write_Index-1);
        }


        ret = NO_ERR;
#endif // RING
#ifdef FIFO
    return OVER_FLOW_ERR;
#endif // FIFO

    }
    else
    {
        printf("normal process \n");
        memcpy(&Ring_Buf[Abstract_Write_Index], data, datalength);
        Abstract_Write_Index += datalength;
        ret = NO_ERR;
    }
/* Test showcase */
    for (int i = 0; i < BUFFERSIZE; i++)
    {
        printf("Ring Buffer data[%d] is %c \n",i, Ring_Buf[i] );
    }

    return ret;
}

Error_Type Read_Queue(int * data)
{
    return NO_ERR;
}

Error_Type Init_Ring_Buffer()
{
    Error_Type ret = NO_ERR;
    Abstract_Write_Index = 0;
    Abstract_Read_Index = 0;
    Ring_Buf = (char *)malloc(BUFFERSIZE * sizeof(char));
    if (Ring_Buf == NULL)
    {
        ret = SYSTEM_ERR;
        printf("allocation failure ! \n");
    }
    return ret;
}

Error_Type Deinit_Ring_Buffer()
{
    Error_Type ret = NO_ERR;
    Abstract_Write_Index = 0;
    Abstract_Read_Index = 0;
    free(Ring_Buf);

    return ret;
}

int main()
{
    Error_Type ret = NO_ERR;
    ret = Init_Ring_Buffer();
    unsigned char C[] = "ABCDEFGHIJKLMNOPQ";
    unsigned char T[] = "+++";
    ret = Write_Queue(C,15);
    ret = Write_Queue(T,3);
    ret = Deinit_Ring_Buffer();
    if (ret != NO_ERR)
        return 0;
    else
        return 1;

}
