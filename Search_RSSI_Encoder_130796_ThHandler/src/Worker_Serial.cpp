#include "Worker_Serial.h"
#include <QDebug>
#include "serial_message.h"
Worker_Serial::Worker_Serial(QObject *parent) :
    QObject(parent)
{
    SerialSearchThread = new QSerialPort(this);
    serialConnected = false;
    ringBufferFull = false;
    ringMsgNo = 0;
    myDate = new QDateTime();
}
Worker_Serial::~Worker_Serial()
{
    // free resources
    disconnect(SerialSearchThread,SIGNAL(readyRead()),this,SLOT(readyData()));
    delete myDate;
    delete SerialSearchThread;
}

void Worker_Serial::beforProcess()
{
    afterProcess();
}

void Worker_Serial::afterProcess()
{
    disconnect(SerialSearchThread,SIGNAL(readyRead()),this,SLOT(readyData()));
    SerialSearchThread->close();
    //emit finished();
}

// --- PROCESS ---
// Start processing data.
void Worker_Serial::process()
{
   // emit rcvDataSignal();
    // allocate resources using new here
    SerialSearchThread->setPortName(serialName);
    if (SerialSearchThread->open(QIODevice::ReadWrite))
    {
        if (SerialSearchThread->setBaudRate(serialBaudrate,QSerialPort::AllDirections)
                && SerialSearchThread->setDataBits(QSerialPort::Data8)
                && SerialSearchThread->setParity(QSerialPort::NoParity)
                && SerialSearchThread->setStopBits( QSerialPort::OneStop)
                && SerialSearchThread->setFlowControl(QSerialPort::NoFlowControl))
            {
                //SerialSearch->setReadBufferSize(128000);
                SerialSearchThread->setDataTerminalReady(false);
                connect(SerialSearchThread,SIGNAL(readyRead()),this,SLOT(readyData()));
                serialConnected = true;
            }
    }
    else
    {
        disconnect(SerialSearchThread,SIGNAL(readyRead()),this,SLOT(readyData()));
        serialConnected = false;
    }
}
void Worker_Serial::readyData()
{
    QByteArray data = SerialSearchThread->readAll();
    int b = data.size();
    qDebug() << "Buffered data (byte) =  "<< b;
    for(int i = 0; i < data.size(); i++)
        parseByte(data.at(i));

    //emit rcvDataSignal();
    //int bb = data.at(0);
    //parseByte((unsigned char)data[i]);
}

void Worker_Serial::txDataSlot()
{
    dataTxInternal = dataTx;
    //dataTx.clear();
    if(SerialSearchThread->isOpen())
        SerialSearchThread->write(dataTxInternal);
}


Message_Status_t operator ++(Message_Status_t &id, int)
{
    Message_Status_t currentID = id;
    if(msgGOT_PAYLOAD < id + 1) id = msgUNINIT;
    else id = static_cast<Message_Status_t>(id + 1);

    return (currentID);
}

uint Message_Length_test = 17;
int errorNo = 0;
uint8_t DataArray[500];
int dtCnt = 0;
char cntCRC = 0;
typedef union
{
    uint16_t u16;
    uint8_t u8[2];
}u16_8_t;
u16_8_t u16_8;
uint16_t TesterCRC = 0;
uint16_t Receive_Check_Sum;
MCU_Data_Array_t MCU_Data_u_ws;

char Worker_Serial::parseByte(unsigned char Data)
{
    if (Message_Status < msgGOT_PAYLOAD)
    Receive_Check_Sum += Data;

    switch(Message_Status)
    {
        case msgUNINIT:
        if (Data == msgRecieve_Sync1)
        {
            Message_Status++;
        }
        break;

        case msgGOT_SYNC1:
        if (Data != msgRecieve_Sync2)
        {
            goto restart;
        }
        Receive_Check_Sum = 0;
        Message_Index = 0;
        Message_Status++;
        break;

        case msgGOT_SYNC2:
        Message_ID = Data;
        Message_Status++;
        break;

        case msgGOT_ID:
        Message_Length = Data;
        Message_Status++;
        break;

        case msgGOT_LEN:
        Message.MessageChar[Message_Index] = Data;
        Message_Index++;
        if (Message_Index >= Message_Length) {
            Message_Status++;
            cntCRC = 0;
        }
        break;

        case msgGOT_PAYLOAD:

        switch(cntCRC)
        {
        case 0:
            u16_8.u8[0] = Data;
            break;
        case 1:
            u16_8.u8[1] = Data;
            break;
        }
        cntCRC++;

        if(cntCRC == 2)
        {
            cntCRC = 0;
            if(u16_8.u16 != gen_crc16(Message.MessageChar,Message_Length))
                goto error;
            for(int i = 0; i < Message_Length ; i++)
                dataRcvPersedInternal.append(Message.MessageChar[i]);

            vecTemp2dInternal.push_back(dataRcvPersedInternal);
            vecTempDateInternal.push_back(myDate->currentDateTime());
            dataRcvPersedInternal.clear();

            if(vecTemp2dInternal.size() >= 20)
            {
                if(ringBufferFull == false)
                {
                    vecTemp2d = vecTemp2dInternal;
                    vecTempDate = vecTempDateInternal;
                    vecTemp2dInternal.clear();
                    vecTempDateInternal.clear();
                    ringBufferFull = true;
                    emit rcvDataSignal();
                }
                else
                {

                }
            }
            if(vecTemp2dInternal.size() == 3)
            {
                if(ringBufferFull)
                    qDebug() << "Ring Buffer is Full";
                else
                    qDebug() << "Ring Buffer is empty";
            }

        }
        else
            break;

        //parseMessage();
        goto restart;

    }
    return -1;

    error:
    {
        qDebug()<<"an Error Occure in ParseByte";
    }
    restart: Message_Status = msgUNINIT;
    return Message_ID;
}


#define CRC16 0x8005
uint16_t Worker_Serial::gen_crc16(const uint8_t *data,uint16_t size)
{
    uint16_t out =0;
    int bits_read = 0, bit_flag;

    if(data == NULL)
        return 0;

    while(size > 0)
    {
        bit_flag = out >> 15;

        /* Get next bit */
        out <<= 1;
        out |= (*data >> bits_read) & 1;

        bits_read++;
        if(bits_read > 7)
        {
            bits_read = 0;
            data++;
            size--;
        }
        /* Cycle Check */
        if(bit_flag)
            out ^= CRC16;
    }
    int i;
    for(i = 0; i < 16 ; i++)
    {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16;
    }

    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for(; i != 0; i >>= 1, j <<= 1){
        if(i & out) crc |= j;
    }

    return crc;
}
