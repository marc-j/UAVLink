#ifndef UAVLINK_MESSAGE_H
#define UAVLINK_MESSAGE_H
#include <stdint.h>
#include <string.h>

//#define PROCOTOL_BITSWAP 1

enum UAVLINK_CMD
{
   UAVLINK_UNKNOW,
   UAVLINK_MSG_SENSOR,
   UAVLINK_MSG_SYSTEM,
   UAVLINK_MSG_COMMAND,
   UAVLINK_MSG_PID,
   UAVLINK_MSG_MOTOR,
   UAVLINK_MSG_SENSOR_RAW,
   UAVLINK_MSG_SENSOR_VARIANCE,
   UAVLINK_MSG_RC_CALIBRATION,
   UAVLINK_MSG_STATUS,
   UAVLINK_STATE,
   UAVLINK_ACK
};

enum UAVLINK_STATE {
    UAVLINK_SYS_SAVECONFIG = 0x11,
    UAVLINK_SYS_READCONFIG = 0x12,
    UAVLINK_SYS_PID = 0x20,
    UAVLINK_ESCCALIBRATION = 0xAA,
    UAVLINK_RCCALIBRATION = 0xBB,
    UAVLINK_PING  = 0xCC,
    UAVLINK_DEBUG = 0xDD,
    UAVLINK_START = 0xEE
};

enum UAVLINK_STEP {
    STX1,
    STX2,
    CTX,
    LTX,
    DTX,
    CRC8
};

enum UAVLINK_STATUS {
    UAVLINK_ERROR_MSG = -1,
    UAVLINK_WAITING_MSG = 0,
    UAVLINK_VALID_MSG
};

typedef struct __uavlink_message {
    uint8_t cmd;
    uint8_t len;
    uint8_t datas[255];
} uavlink_message_t;

typedef struct __uavlink_status {
        uint8_t  buffer[255];
        uint8_t* ptr;
        uint8_t step;
        uint8_t crc;
        uint16_t len;
} uavlink_status;

#define _UAVLINK_PAYLOAD(msg) ((const char *)(&((msg)->datas[0])))
#define _UAVLINK_RETURN_uint8_t(msg, offset) (uint8_t)_UAVLINK_PAYLOAD(msg)[offset];

static inline uint16_t _UAVLINK_RETURN_uint16_t(const uavlink_message_t* msg, uint8_t offset)
{
    return (msg->datas[offset] << 8) + (msg->datas[offset+1] & 0xFF);
}

static inline uint16_t _UAVLINK_RETURN_uint32_t(const uavlink_message_t* msg, uint8_t offset)
{
    uint16_t hsb = (msg->datas[offset] << 8) + (msg->datas[offset+1] & 0xFF);
    uint16_t lsb = (msg->datas[offset+2] << 8) + (msg->datas[offset+3] & 0xFF);

    return (hsb << 16) + (lsb & 0xFFFF);
}

static inline void uavlink_init(uavlink_status* status)
{
    status->ptr = &status->buffer[0];
    status->step = STX1;
    status->crc = 0;
    status->len = 0;
}

static inline uint8_t uavlink_parse(uint8_t byte, uavlink_status* status, uavlink_message_t* msg)
{
    switch(status->step) {
        case STX1:
            if (byte == 0xFF) {
                status->step = STX2;
            }
            break;
        case STX2:
            if (byte == 0xFF) {
                status->ptr = &status->buffer[0];
                status->crc = 0;
                status->step = CTX;
            } else {
                status->step = STX1;
            }
            break;
        case CTX:
            *status->ptr++ = byte;
            status->crc ^= byte;
            status->step = LTX;
            break;
        case LTX:
            *status->ptr++ = byte;
            status->crc ^= byte;
            status->len = byte;
            if (status->len <= 0) {
                status->step = STX1;
            } else {
                status->step = DTX;
            }
            break;
        case DTX:
            *status->ptr++ = byte;
            status->crc ^= byte;
            status->len--;
            if (status->len == 0) {
                status->step = CRC8;
            }
            break;
        case CRC8:

            status->step = STX1;
            if (status->crc == byte) {
                uint16_t i = 0;
                msg->cmd = status->buffer[i++];
                msg->len = status->buffer[i++];
                for (uint16_t j=0; j< msg->len; j++) {
                        msg->datas[j] = status->buffer[i++];
                }
                return UAVLINK_VALID_MSG;
            }

            return UAVLINK_ERROR_MSG;
    }

    return UAVLINK_WAITING_MSG;
}

inline static uint16_t uavlink_get_buffer(uint8_t *buffer,uavlink_message_t msg)
{
    uint8_t crc = 0;
    *buffer++ = 0xFF;
    *buffer++ = 0xFF;
    *buffer++ = msg.cmd;
    crc ^= msg.cmd;
    *buffer++ = msg.len;
    crc ^= msg.len;
    for (uint8_t j=0; j< msg.len; j++) {
        *buffer++ = msg.datas[j];
        crc ^= msg.datas[j];
    }
    *buffer++ = crc;

    return 4 + msg.len + 1;
}

inline static const uavlink_message_t uavlink_generate_ack(uint8_t cmd, uint8_t flag)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_ACK;
    msg.len = 2;
    msg.datas[0] = cmd;
    msg.datas[1] = flag;

    return msg;
}

inline static const uavlink_message_t uavlink_generate_state(uint8_t cmd)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_STATE;
    msg.len = 1;
    msg.datas[0] = cmd;

    return msg;
}

#include "msg/MessageSystem.h"
#include "msg/MessageSensor.h"
#include "msg/MessageMotor.h"
#include "msg/MessageCommand.h"
#include "msg/MessagePID.h"
#include "msg/MessageSensorRaw.h"
#include "msg/MessageSensorVariance.h"
#include "msg/MessageStatus.h"
#include "msg/MessageRCCalibration.h"

#endif // UAVLINK_MESSAGE_H
