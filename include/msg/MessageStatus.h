/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Marc Jacquier <marc@inodrone.com>
 *  Project: InoDronePegasus
 */
#ifndef UAVLINK_MESSAGE_STATUS_H
#define UAVLINK_MESSAGE_STATUS_H

/*----------------------------------------------------
 # STATUS
 #--------------------------------------------------*/

typedef struct __uavlink_message_status {
    struct {
          float x;
          float y;
          float z;
    } acc;
    struct {
          float x;
          float y;
          float z;
    } gyro;
    struct {
          float x;
          float y;
          float z;
    } mag;
    struct {
          float roll;
          float pitch;
          float yaw;
    } angle;
    uint8_t frameType;
    uint8_t version;
} uavlink_message_status_t;

inline static void uavlink_message_status_decode(const uavlink_message_t* msg, uavlink_message_status_t* status)
{
    memcpy(status, _UAVLINK_PAYLOAD(msg), sizeof(uavlink_message_status_t) );
}

inline static const uavlink_message_t uavlink_message_status_encode(uavlink_message_status_t* pids)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_STATUS;
    msg.len = sizeof(uavlink_message_status_t);
    memcpy(&msg.datas[0],pids, sizeof(uavlink_message_status_t));

    return msg;
}

#endif // UAVLINK_MESSAGE_PID_H
