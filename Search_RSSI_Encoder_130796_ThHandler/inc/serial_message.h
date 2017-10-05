#include <stdint.h>
#include <QVector>


#define TX_BUFFER_SIZE 					250
#define RX_BUFFER_SIZE 					250

#define msgRecieve_Sync1 				0xAC
#define msgRecieve_Sync2 				0xBD

#define msgRecieve_Sync1_t 				0x7B
#define msgRecieve_Sync2_t 				0xEA

#define msgTrans_Sync1					0xAC
#define msgTrans_Sync2					0xBD
#define msgTrans_ID						0xFE
#define msgAlive_ID                     0xFB

#define cont_arraySize	3
#define msgMCU_detect_reset_ID          0xA8
void parseMessage(char msg_ID);
extern char parseByte(unsigned char Data);

extern char tx_buffer[TX_BUFFER_SIZE];
extern unsigned char tx_wr_index,tx_rd_index,tx_counter;

//extern unsigned char Receive_Check_Sum;
extern uint32_t Message_Index;

extern char Message_ID;
extern uint32_t Message_Length;

extern unsigned char Transmit_Check_Sum;

typedef enum
{
	msgUNINIT,
	msgGOT_SYNC1,
	msgGOT_SYNC2,
    msgGOT_ID,
    msgGOT_LEN,
    msgGOT_PAYLOAD
} Message_Status_t;

typedef union 
{
    uint8_t			MessageChar[RX_BUFFER_SIZE];
    int16_t			MessageInt16[RX_BUFFER_SIZE/2];
	float			MessageFloat[RX_BUFFER_SIZE/4];
	int				MessageInt32[RX_BUFFER_SIZE/4];
} Message_t;

extern Message_Status_t  Message_Status;
extern Message_t	Message;

#define Dopp_1

#ifdef Dopp_1
#define rcvDataMCU_Lenght   17
    typedef struct
    {
        uint8_t bitWatch;
        uint8_t Interrupt_Bits;
        uint8_t RSSI_SUM_UARTs_Data[3];
        uint8_t Dopp_UARTs_data;
        uint8_t RSSI_Delta_UARTs_Data[3];
        uint8_t Encoder_AC_Motor[4];
        uint8_t Encoder_Ref_AC_Motor[4];
    }MCU_Data_t;
#else
#define rcvDataMCU_Lenght   17
    typedef struct
    {
        uint8_t Interrupt_Bits;
        uint8_t ADC_Data[2];
        uint8_t Sensor_UARTs_Data[6];
        uint8_t Encoder_AC_Motor[4];
        uint8_t Encoder_Ref_AC_Motor[4];
    }MCU_Data_t;
#endif

typedef union
{
    MCU_Data_t MCU_Data_S;
    uint8_t MCU_Data_Array[rcvDataMCU_Lenght];
}MCU_Data_Array_t;
extern MCU_Data_Array_t MCU_Data_u;
extern MCU_Data_Array_t MCU_Data_u_ws;

typedef enum
{
    AC_STOP = 0x50,
    AC_FORWARD,
    AC_REVERSE,
    AC_EGC_STOP,
    AC_PARK,
    AC_FREQ,
    AC_ACC,
    AC_DEC
}AC_ID_t;
extern AC_ID_t AC_ID;
