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
   UAVLINK_MSG_SENSOR_RAW
};

typedef struct __uavlink_message {
    uint8_t cmd;
    uint8_t len;
    uint8_t datas[255];
} uavlink_message_t;

#define _UAVLINK_PAYLOAD(msg) ((const char *)(&((msg)->datas[0])))
#define _UAVLINK_RETURN_uint8_t(msg, offset) (uint8_t)_UAVLINK_PAYLOAD(msg)[offset];

static inline uint16_t _UAVLINK_RETURN_uint16_t(const uavlink_message_t* msg, uint8_t offset)
{
    return (msg->datas[offset] << 8) + (msg->datas[offset+1] & 0xFF);
}

#include "msg/MessageSystem.h"
#include "msg/MessageSensor.h"
#include "msg/MessageMotor.h"
#include "msg/MessageCommand.h"
#include "msg/MessagePID.h"
#include "msg/MessageSensorRaw.h"

#endif // UAVLINK_MESSAGE_H