#ifndef SERIAL_MESSAGE_TX_H
#define SERIAL_MESSAGE_TX_H
typedef enum
{
    RotMCU_ID = 0xA0,
    RotMCU_HighSUM = 0xA6,
    RotMCU_LowSUM,
    RotMCU_HighDelta,
    RotMCU_LowDelta,
    RotMCU_SelectDelta,
    RotMCU_SelectSLC
}RotMCU_ID_t;
extern RotMCU_ID_t RotMCU_msg_ID;


typedef enum
{
    we_Rot_COM_SUM = 0,
    we_Rot_COM_Delta,
    w_Rot_SUM_Serial_Pin,
    w_Rot_DeltaSLC_Serial_Pin,
    w_Rot_SelectDeltaSLC,
    e_Not4,
    e_Not5,
    e_Not6
} bitwatch_Status_t;
 extern bitwatch_Status_t bitwatch;
#endif // SERIAL_MESSAGE_TX_H
