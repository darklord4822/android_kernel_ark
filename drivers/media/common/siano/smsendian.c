/**********uniscope-driver-modify-file-on-qualcomm-platform*****************/
/****************************************************************

 Siano Mobile Silicon, Inc.
 MDTV receiver kernel modules.
 Copyright (C) 2006-2009, Uri Shkolnik

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ****************************************************************/

#include <asm/byteorder.h>

#include "smsendian.h"
#include "smscoreapi.h"

void smsendian_handle_tx_message(void *buffer)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgData_S *msg = (struct SmsMsgData_S *)buffer;
	int i;
	int msgWords;
//sms_err("smsendian_handle_tx_message%d\n",msg->xMsgHeader.msgType);
	switch (msg->xMsgHeader.msgType) {
	case MSG_SMS_DATA_DOWNLOAD_REQ:
	{
		msg->msgData[0] = le32_to_cpu(msg->msgData[0]);
		break;
	}

	default:
		msgWords = (msg->xMsgHeader.msgLength -
				sizeof(struct SmsMsgHdr_S))/4;

		for (i = 0; i < msgWords; i++)
			msg->msgData[i] = le32_to_cpu(msg->msgData[i]);

		break;
	}
#endif /* __BIG_ENDIAN */
}


void smsendian_handle_rx_message(void *buffer)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgData_S *msg = (struct SmsMsgData_S *)buffer;
	int i;
	int msgWords;

	switch (msg->xMsgHeader.msgType) {
	case MSG_SMS_GET_VERSION_EX_RES:
	{
		struct SmsVersionRes_S *ver =
			(struct SmsVersionRes_S *) msg;
		ver->xVersion.ChipModel = le16_to_cpu(ver->xVersion.ChipModel);
		break;
	}

	case MSG_SMS_DVBT_BDA_DATA:
	case MSG_SMS_DAB_CHANNEL:
	case MSG_SMS_DATA_MSG:
	{
		break;
	}

	default:
	{
		msgWords = (msg->xMsgHeader.msgLength -
				sizeof(struct SmsMsgHdr_S))/4;

		for (i = 0; i < msgWords; i++)
			msg->msgData[i] = le32_to_cpu(msg->msgData[i]);

		break;
	}
	}
#endif /* __BIG_ENDIAN */
}


void smsendian_handle_message_header(void *msg)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgHdr_S *phdr = (struct SmsMsgHdr_S *)msg;

	phdr->msgType = le16_to_cpu(phdr->msgType);
	phdr->msgLength = le16_to_cpu(phdr->msgLength);
	phdr->msgFlags = le16_to_cpu(phdr->msgFlags);
#endif /* __BIG_ENDIAN */
}

