/*
 * MessageSensorRaw.h
 *
 *  Created on: 20 janv. 2013
 *      Author: marc
 */

#ifndef MESSAGESENSORRAW_H_
#define MESSAGESENSORRAW_H_

/*----------------------------------------------------
 # SENSORS RAW
 #--------------------------------------------------*/

#define UAVLINK_MSG_SENSOR_RAW_LEN 18
typedef struct __uavlink_message_sensor_raw {
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
    int16_t magX;
    int16_t magY;
    int16_t magZ;
} uavlink_message_sensor_raw_t;

inline static void uavlink_message_sensor_raw_decode(const uavlink_message_t* msg, uavlink_message_sensor_raw_t* sensor)
{

#ifdef PROCOTOL_BITSWAP
    sensor->accX = _UAVLINK_RETURN_uint16_t(msg,0);
    sensor->accY = _UAVLINK_RETURN_uint16_t(msg,2);
    sensor->accZ = _UAVLINK_RETURN_uint16_t(msg,4);
    sensor->gyroX = _UAVLINK_RETURN_uint16_t(msg,6);
    sensor->gyroY = _UAVLINK_RETURN_uint16_t(msg,8);
    sensor->gyroZ = _UAVLINK_RETURN_uint16_t(msg,10);
    sensor->magX = _UAVLINK_RETURN_uint16_t(msg,12);
    sensor->magY = _UAVLINK_RETURN_uint16_t(msg,14);
    sensor->magZ = _UAVLINK_RETURN_uint16_t(msg,16);
#else
    memcpy(sensor, _UAVLINK_PAYLOAD(msg), UAVLINK_MSG_SENSOR_RAW_LEN);
#endif
}

inline static const uavlink_message_t uavlink_message_sensor_raw_encode(uavlink_message_sensor_raw_t* sensor)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_SENSOR_RAW;
    msg.len = UAVLINK_MSG_SENSOR_RAW_LEN;
    memcpy(&msg.datas[0],sensor, UAVLINK_MSG_SENSOR_RAW_LEN);

    return msg;
}


#endif /* MESSAGESENSORRAW_H_ */
