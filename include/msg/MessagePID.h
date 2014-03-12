#ifndef UAVLINK_MESSAGE_PID_H
#define UAVLINK_MESSAGE_PID_H

/*----------------------------------------------------
 # PID
 #--------------------------------------------------*/

#define UAVLINK_MSG_PID_LEN 22

typedef struct __uavlink_pid {
        float kP;
        float kI;
        float kD;
        float pMax;
        float iMax;
        float dMax;
        float oMax;
} uavlink_pid;

typedef struct __uavlink_message_pid {
        uavlink_pid tilt;
        uavlink_pid yaw;
        uavlink_pid level;

        uavlink_pid altSonar;
} uavlink_message_pid_t;

inline static void uavlink_message_pid_decode(const uavlink_message_t* msg, uavlink_message_pid_t* pids)
{
   memcpy(pids, _UAVLINK_PAYLOAD(msg), sizeof(uavlink_message_pid_t) );
}

inline static const uavlink_message_t uavlink_message_pid_encode(uavlink_message_pid_t* pids)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_PID;
    msg.len = sizeof(uavlink_message_pid_t);
    memcpy(&msg.datas[0],pids, sizeof(uavlink_message_pid_t));

    return msg;
}

#endif // UAVLINK_MESSAGE_PID_H
