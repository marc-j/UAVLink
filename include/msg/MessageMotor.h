#ifndef UAVLINK_MESSAGE_MOTOR_H
#define UAVLINK_MESSAGE_MOTOR_H

/*----------------------------------------------------
 # MOTORS
 #--------------------------------------------------*/

#define UAVLINK_MSG_MOTOR_LEN 8
typedef struct __uavlink_message_motor {
    int16_t motorFrontLeft;
    int16_t motorFrontRight;
    int16_t motorRearLeft;
    int16_t motorRearRight;
} uavlink_message_motor_t;

inline static void uavlink_message_motor_decode(const uavlink_message_t* msg, uavlink_message_motor_t* motor)
{

#ifdef PROCOTOL_BITSWAP
    motor->motorFrontLeft = _UAVLINK_RETURN_uint16_t(msg,0);
    motor->motorFrontRight = _UAVLINK_RETURN_uint16_t(msg,2);
    motor->motorRearLeft = _UAVLINK_RETURN_uint16_t(msg,4);
    motor->motorRearRight = _UAVLINK_RETURN_uint16_t(msg,6);
#else
    memcpy(motor, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_MOTOR_LEN);
#endif
}

inline static const uavlink_message_t uavlink_message_motor_encode(uavlink_message_motor_t* motor)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_MOTOR;
    msg.len = UAVLINK_MSG_MOTOR_LEN;
    memcpy(&msg.datas[0],motor, UAVLINK_MSG_MOTOR_LEN);

    return msg;
}

#endif // UAVLINK_MESSAGE_MOTOR_H
