#ifndef UAVLINK_MESSAGE_PID_H
#define UAVLINK_MESSAGE_PID_H

/*----------------------------------------------------
 # PID
 #--------------------------------------------------*/

#define UAVLINK_MSG_PID_LEN 18
typedef struct __uavlink_message_pid {
    uint16_t rollKP;
    uint16_t rollKI;
    uint16_t rollKD;
    uint16_t pitchKP;
    uint16_t pitchKI;
    uint16_t pitchKD;
    uint16_t yawKP;
    uint16_t yawKI;
    uint16_t yawKD;
} uavlink_message_pid_t;

inline static void uavlink_message_pid_decode(const uavlink_message_t* msg, uavlink_message_pid_t* pids)
{
#ifdef PROCOTOL_BITSWAP
    pids->rollKP = _UAVLINK_RETURN_uint16_t(msg,0);
    pids->rollKI = _UAVLINK_RETURN_uint16_t(msg,2);
    pids->rollKD = _UAVLINK_RETURN_uint16_t(msg,4);
    pids->pitchKP = _UAVLINK_RETURN_uint16_t(msg,6);
    pids->pitchKI = _UAVLINK_RETURN_uint16_t(msg,8);
    pids->pitchKD = _UAVLINK_RETURN_uint16_t(msg,10);
    pids->yawKP = _UAVLINK_RETURN_uint16_t(msg,12);
    pids->yawKI = _UAVLINK_RETURN_uint16_t(msg,14);
    pids->yawKD = _UAVLINK_RETURN_uint16_t(msg,16);
#else
    memcpy(pids, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_PID_LEN );
#endif
}

inline static const uavlink_message_t uavlink_message_pid_encode(uavlink_message_pid_t* pids)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_PID;
    msg.len = UAVLINK_MSG_PID_LEN;
    memcpy(&msg.datas[0],pids, UAVLINK_MSG_PID_LEN);

    return msg;
}

#endif // UAVLINK_MESSAGE_PID_H
