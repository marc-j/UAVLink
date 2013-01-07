#include <stdio.h>
#include "UAVLink.h"

static inline uint16_t _BITSWAP_RETURN_uint16_t(const uavlink_message_t* msg, uint8_t offset)
{
    return (msg->datas[offset+1] << 8) + (msg->datas[offset] & 0xFF);
}


void testMotor()
{
    // TEST MOTOR
    printf("****************************\n");
    printf("*\tTest MOTOR\n");
    printf("****************************\n");

    int i=0;

    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_MOTOR;
    msg.len = UAVLINK_MSG_MOTOR_LEN;
    for (i=0; i < UAVLINK_MSG_MOTOR_LEN; i++) {
        msg.datas[i] = (uint8_t) 16+i;
    }

    printf("---------- ENCODE ----------\n");
    uavlink_message_motor_t motor;
    uavlink_message_motor_decode(&msg,&motor);

    printf("motorFrontLeft:\t %d", motor.motorFrontLeft);
    if (motor.motorFrontLeft == _BITSWAP_RETURN_uint16_t(&msg,0) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("motorFrontRight: %d", motor.motorFrontRight);
    if (motor.motorFrontRight == _BITSWAP_RETURN_uint16_t(&msg,2) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("motorRearLeft:\t %d", motor.motorRearLeft);
    if (motor.motorRearLeft == _BITSWAP_RETURN_uint16_t(&msg,4) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("motorRearRight:\t %d", motor.motorRearRight);
    if (motor.motorRearRight == _BITSWAP_RETURN_uint16_t(&msg,6) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("---------- DECODE ----------\n");
    uavlink_message_t msg1;
    msg1 = uavlink_message_motor_encode(&motor);
    if (msg.cmd == msg1.cmd && msg.len == msg1.len) {
        printf("Send Header:\t\t[OK]\n");
    } else {
        printf("Send Header:\t\t[NOK] cmd: %d=%d and len: %d=%d \n",msg.cmd,msg1.cmd,msg.len,msg1.len);
    }

    char error = 0;
    for (i=0; i < UAVLINK_MSG_MOTOR_LEN; i++) {
        if (msg.datas[i] != msg1.datas[i]) {
            printf("Data error at %d: %d found %d\n",i,msg.datas[i],msg1.datas[i]);
            error = 1;
            break;
        }
    }

    if (!error) {
        printf("DATA:\t\t\t[OK]\n");
    }
    printf("****************************\n");
}

void testCommand()
{
    // TEST COMMAND
    printf("****************************\n");
    printf("*\tTest COMMAND\n");
    printf("****************************\n");

    int i=0;

    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_COMMAND;
    msg.len = UAVLINK_MSG_COMMAND_LEN;
    for (i=0; i < UAVLINK_MSG_COMMAND_LEN; i++) {
        msg.datas[i] = (uint8_t) 16+i;
    }

    printf("---------- DECODE ----------\n");
    uavlink_message_command_t command;
    uavlink_message_command_decode(&msg,&command);

    printf("Roll:\t\t %d", command.roll);
    if (command.roll == _BITSWAP_RETURN_uint16_t(&msg,0) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("Pitch:\t\t %d", command.pitch);
    if (command.pitch == _BITSWAP_RETURN_uint16_t(&msg,2) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("Yaw:\t\t %d", command.yaw);
    if (command.yaw == _BITSWAP_RETURN_uint16_t(&msg,4) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("Throttle:\t %d", command.throttle);
    if (command.throttle == _BITSWAP_RETURN_uint16_t(&msg,6) ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("Armed:\t\t %d", command.armed);
    if (command.armed == msg.datas[8] ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("FlightMode:\t %d", command.flightMode);
    if (command.flightMode == msg.datas[9] ) {
        printf("\t[OK]\n");
    } else {
        printf("\t[NOK]\n");
    }

    printf("---------- ENCODE ----------\n");

    uavlink_message_t msg1;
    msg1 = uavlink_message_command_encode(&command);
    if (msg.cmd == msg1.cmd && msg.len == msg1.len) {
        printf("Send Header:\t\t[OK]\n");
    } else {
        printf("Send Header:\t\t[NOK] cmd: %d=%d and len: %d=%d \n",msg.cmd,msg1.cmd,msg.len,msg1.len);
    }

    char error = 0;
    for (i=0; i < UAVLINK_MSG_COMMAND_LEN; i++) {
        if (msg.datas[i] != msg1.datas[i]) {
            printf("Data error at %d: %d found %d\n",i,msg.datas[i],msg1.datas[i]);
            error = 1;
            break;
        }
    }

    if (!error) {
        printf("DATA:\t\t\t[OK]\n");
    }
    printf("****************************\n");
}

int main(int argc, char *argv[]) {

    testMotor();
    testCommand();

    return 0;
}
