#ifndef UAVLINK_MESSAGE_COMMAND_H
#define UAVLINK_MESSAGE_COMMAND_H

/*----------------------------------------------------
 # COMMAND
 #--------------------------------------------------*/

#define UAVLINK_MSG_COMMAND_LEN 10
typedef struct __uavlink_message_command {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    uint16_t throttle;
    uint8_t armed;
    uint8_t flightMode;
} uavlink_message_command_t;

inline static void uavlink_message_command_decode(const uavlink_message_t* msg, uavlink_message_command_t* command)
{
#ifdef PROCOTOL_BITSWAP
    command->roll = _UAVLINK_RETURN_uint16_t(msg,0);
    command->pitch = _UAVLINK_RETURN_uint16_t(msg,2);
    command->throttle = _UAVLINK_RETURN_uint16_t(msg,4);   
    command->armed = _UAVLINK_RETURN_uint8_t(msg,6);
    command->flightMode = _UAVLINK_RETURN_uint8_t(msg,7);
#else
    memcpy(command, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_COMMAND_LEN );
#endif
}

inline static const uavlink_message_t uavlink_message_command_encode(uavlink_message_command_t* command)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_COMMAND;
    msg.len = UAVLINK_MSG_COMMAND_LEN;
    memcpy(&msg.datas[0],command, UAVLINK_MSG_COMMAND_LEN);

    return msg;
}

#endif // UAVLINK_MESSAGE_COMMAND_H
