/**
 * @file ptp_message.h
 * @brief Implements the various PTP message types.
 * @note Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef _PTP_MESSAGE_H_
#define _PTP_MESSAGE_H_

#include <linux/time.h>

#include "ddt.h"

/// PTP message types.
#define PTP_SYNC                    0x0 ///< Sync
#define PTP_DELAY_REQ               0x1 ///< Delay_Req
#define PTP_PDELAY_REQ              0x2 ///< Pdelay_Req
#define PTP_PDELAY_RESP             0x3 ///< Pdelay_Resp
#define PTP_FOLLOW_UP               0x8 ///< Follow_Up
#define PTP_DELAY_RESP              0x9 ///< Delay_Resp
#define PTP_PDELAY_RESP_FOLLOW_UP   0xA ///< Pdelay_Resp_Follow_Up
#define PTP_ANNOUNCE                0xB ///< Announce
#define PTP_SIGNALING               0xC ///< Signaling
#define PTP_MANAGEMENT              0xD ///< Management

/// PTP message flags.
#define PTP_ALTERNATE_MASTER        0x0001      ///<
#define PTP_TWO_STEP                0x0002      ///<
#define PTP_UNICAST                 0x0004      ///<
#define PTP_PROFILE1                0x0020      ///<
#define PTP_PROFILE2                0x0040      ///<
#define PTP_LI_61                   0x0100      ///<
#define PTP_LI_59                   0x0200      ///<
#define PTP_UTC_OFFSET_VALID        0x0400      ///<  The value of current_utc_offset_valid
#define PTP_TIMESCALE               0x0800      ///<  The value of ptp_timescale of the time properties data set.
#define PTP_TIME_TRACEABLE          0x1000      ///<  The value of time_traceable of the time properties data set.
#define PTP_FREQ_TRACEABLE          0x1000      ///<  The value of frequency_traceable of the time properties data set.

/// PTP header control field values (for backward combatibility).
#define PTP_CTRL_SYNC               0x0 ///< Sync
#define PTP_CTRL_DELAY_REQ          0x1 ///< Delay_Resp
#define PTP_CTRL_FOLLOW_UP          0x2 ///< Follow_Up
#define PTP_CTRL_DELAY_RESP         0x3 ///< Delay_Resp
#define PTP_CTRL_MANAGEMENT         0x4 ///< Management
#define PTP_CTRL_OTHER              0x5 ///< All other messages

/** 
* Default value for logMeanMessageInterval 
* (for Delay_Req, Signaling, Management, Pdelay_Req, 
* Pdelay_Resp, Pdelay_Resp_Follow_Up)
*/
#define PTP_MSG_DEFAULT_INTERVAL    0x7F        ///< default interval


enum timestamp_type {
	TS_SOFTWARE,
	TS_HARDWARE,
	TS_LEGACY_HW,
	TS_ONESTEP,
};

struct hw_timestamp {
	enum timestamp_type type;
	struct timespec ts;
	struct timespec sw;
};

enum controlField {
	CTL_SYNC,
	CTL_DELAY_REQ,
	CTL_FOLLOW_UP,
	CTL_DELAY_RESP,
	CTL_MANAGEMENT,
	CTL_OTHER,
};

struct ptp_header {
	uint8_t             tsmt; /* transportSpecific | messageType */
	uint8_t             ver;  /* reserved          | versionPTP  */
	UInteger16          messageLength;
	UInteger8           domainNumber;
	Octet               reserved1;
	Octet               flagField[2];
	Integer64           correction;
	UInteger32          reserved2;
	struct PortIdentity sourcePortIdentity;
	UInteger16          sequenceId;
	UInteger8           control;
	Integer8            logMessageInterval;
} PACKED;

struct announce_msg {
	struct ptp_header    hdr;
	struct Timestamp     originTimestamp;
	Integer16            currentUtcOffset;
	Octet                reserved;
	UInteger8            grandmasterPriority1;
	struct ClockQuality  grandmasterClockQuality;
	UInteger8            grandmasterPriority2;
	struct ClockIdentity grandmasterIdentity;
	UInteger16           stepsRemoved;
	Enumeration8         timeSource;
	uint8_t              suffix[0];
} PACKED;

struct sync_msg {
	struct ptp_header   hdr;
	struct Timestamp    originTimestamp;
} PACKED;

struct delay_req_msg {
	struct ptp_header   hdr;
	struct Timestamp    originTimestamp;
} PACKED;

struct follow_up_msg {
	struct ptp_header   hdr;
	struct Timestamp    preciseOriginTimestamp;
	uint8_t             suffix[32];
} PACKED;

struct delay_resp_msg {
	struct ptp_header   hdr;
	struct Timestamp    receiveTimestamp;
	struct PortIdentity requestingPortIdentity;
	uint8_t             suffix[0];
} PACKED;

struct pdelay_req_msg {
	struct ptp_header   hdr;
	struct Timestamp    originTimestamp;
	struct PortIdentity reserved;
} PACKED;

struct pdelay_resp_msg {
	struct ptp_header   hdr;
	struct Timestamp    requestReceiptTimestamp;
	struct PortIdentity requestingPortIdentity;
} PACKED;

struct pdelay_resp_fup_msg {
	struct ptp_header   hdr;
	struct Timestamp    responseOriginTimestamp;
	struct PortIdentity requestingPortIdentity;
	uint8_t             suffix[0];
} PACKED;

struct signaling_msg {
	struct ptp_header   hdr;
	struct PortIdentity targetPortIdentity;
	uint8_t             suffix[0];
} PACKED;

struct management_msg {
	struct ptp_header   hdr;
	struct PortIdentity targetPortIdentity;
	UInteger8           startingBoundaryHops;
	UInteger8           boundaryHops;
	uint8_t             flags; /* reserved | actionField */
	uint8_t             reserved;
	uint8_t             suffix[0];
} PACKED;
/**
 * Obtain the message type.
 * @param m  Message to test.
 * @return   The value of the messageType field.
 */
static inline int msg_type(const struct ptp_header *m)
{
	return m->tsmt & 0x0f;
}
#endif