#ifndef UAVLINK_MESSAGE_SENSOR_VARIANCE_H
#define UAVLINK_MESSAGE_SENSOR_VARIANCE_H

/*----------------------------------------------------
 # SENSORS
 #--------------------------------------------------*/

#define UAVLINK_MSG_SENSOR_VARIANCE_LEN 24
typedef struct __uavlink_message_sensor_variance {
    int32_t accX;
    int32_t accY;
    int32_t accZ;
    int32_t gyroX;
    int32_t gyroY;
    int32_t gyroZ;
} uavlink_message_sensor_variance_t;

inline static void uavlink_message_sensor_variance_decode(const uavlink_message_t* msg, uavlink_message_sensor_variance_t* sensor)
{

#ifdef PROCOTOL_BITSWAP
    sensor->accX = _UAVLINK_RETURN_uint32_t(msg,0);
    sensor->accY = _UAVLINK_RETURN_uint32_t(msg,4);
    sensor->accZ = _UAVLINK_RETURN_uint32_t(msg,8);
    sensor->gyroX = _UAVLINK_RETURN_uint32_t(msg,12);
    sensor->gyroY = _UAVLINK_RETURN_uint32_t(msg,16);
    sensor->gyroZ = _UAVLINK_RETURN_uint32_t(msg,20);
#else
    memcpy(sensor, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_SENSOR_VARIANCE_LEN);
#endif
}

inline static const uavlink_message_t uavlink_message_sensor_variance_encode(uavlink_message_sensor_variance_t* sensor)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_SENSOR_VARIANCE;
    msg.len = UAVLINK_MSG_SENSOR_VARIANCE_LEN;
    memcpy(&msg.datas[0],sensor, UAVLINK_MSG_SENSOR_VARIANCE_LEN);

    return msg;
}

#endif // UAVLINK_MESSAGE_SENSOR_VARIANCE_H
