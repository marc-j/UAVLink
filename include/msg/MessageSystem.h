#ifndef UAVLINK_MESSAGESYSTEM_H
#define UAVLINK_MESSAGESYSTEM_H

/*----------------------------------------------------
 # SYSTEM
 #--------------------------------------------------*/

#define UAVLINK_MSG_SYSTEM_LEN 8
typedef struct __uavlink_message_system {
    uint16_t cpuLoad;
    uint16_t flightMode;
    uint16_t batteryVoltage;
    uint16_t mainLoopTime;
} uavlink_message_system_t;

inline static void uavlink_message_system_decode(const uavlink_message_t* msg, uavlink_message_system_t* system)
{
#ifdef PROCOTOL_BITSWAP
    system->cpuLoad = _UAVLINK_RETURN_uint16_t(msg,0);
    system->flightMode = _UAVLINK_RETURN_uint16_t(msg,2);
    system->batteryVoltage = _UAVLINK_RETURN_uint16_t(msg,4);
    system->mainLoopTime = _UAVLINK_RETURN_uint16_t(msg,6);
#else
    memcpy(system, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_SYSTEM_LEN );
#endif
}

inline static const uavlink_message_t uavlink_message_system_encode(uavlink_message_system_t* system)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_SYSTEM;
    msg.len = UAVLINK_MSG_SYSTEM_LEN;
    memcpy(&msg.datas[0],system, UAVLINK_MSG_SYSTEM_LEN);

    return msg;
}

#endif // UAVLINK_MESSAGESYSTEM_H
