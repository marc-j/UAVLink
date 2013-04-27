#ifndef UAVLINK_MESSAGE_SENSOR_VARIANCE_H
#define UAVLINK_MESSAGE_SENSOR_VARIANCE_H

/*----------------------------------------------------
 # SENSORS
 #--------------------------------------------------*/

#define UAVLINK_MSG_SENSOR_VARIANCE_LEN 12
typedef struct __uavlink_message_sensor_variance {
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
} uavlink_message_sensor_variance_t;

inline static void uavlink_message_sensor_variance_decode(const uavlink_message_t* msg, uavlink_message_sensor_variance_t* sensor)
{

#ifdef PROCOTOL_BITSWAP
    sensor->accX = _UAVLINK_RETURN_uint16_t(msg,0);
    sensor->accY = _UAVLINK_RETURN_uint16_t(msg,2);
    sensor->accZ = _UAVLINK_RETURN_uint16_t(msg,4);
    sensor->gyroX = _UAVLINK_RETURN_uint16_t(msg,6);
    sensor->gyroY = _UAVLINK_RETURN_uint16_t(msg,8);
    sensor->gyroZ = _UAVLINK_RETURN_uint16_t(msg,10);
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
