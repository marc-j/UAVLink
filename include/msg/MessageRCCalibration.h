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
#ifndef UAVLINK_MESSAGE_RCCALIBRATION_H
#define UAVLINK_MESSAGE_RCCALIBRATION_H

/*----------------------------------------------------
 # RC CALIBRATION
 #--------------------------------------------------*/

typedef struct __uavlink_rc_calibration {
        uint16_t min;
        uint16_t max;
        uint16_t center;
} uavlink_rc_calibration;

typedef struct __uavlink_message_rc_calibration {
        uavlink_rc_calibration throttle;
        uavlink_rc_calibration roll;
        uavlink_rc_calibration pitch;
        uavlink_rc_calibration yaw;
} uavlink_message_rc_calibration_t;

inline static void uavlink_message_rc_calibration_decode(const uavlink_message_t* msg, uavlink_message_rc_calibration_t* rc)
{
    memcpy(rc, _UAVLINK_PAYLOAD(msg), sizeof(uavlink_message_rc_calibration_t) );
}

inline static const uavlink_message_t uavlink_message_rc_calibration_encode(uavlink_message_rc_calibration_t* rc)
{
    uavlink_message_t msg;
    msg.cmd = UAVLINK_MSG_RC_CALIBRATION;
    msg.len = sizeof(uavlink_message_rc_calibration_t);
    memcpy(&msg.datas[0],rc, sizeof(uavlink_message_rc_calibration_t));

    return msg;
}

#endif // UAVLINK_MESSAGE_RCCALIBRATION_H
