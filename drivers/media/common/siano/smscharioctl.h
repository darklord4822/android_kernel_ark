/**********uniscope-driver-modify-file-on-qualcomm-platform*****************/
/****************************************************************

Siano Mobile Silicon, Inc.
MDTV receiver kernel modules.
Copyright (C) 2006-2008, Uri Shkolnik

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
#ifndef __SMS_CHAR_IOCTL_H__
#define __SMS_CHAR_IOCTL_H__

#include <linux/ioctl.h>

enum smschar_pnp_event_t {
	SMSCHAR_PLUG_IN_EVENT,
	SMSCHAR_PLUG_OUT_EVENT,
	SMSCHAR_SUSPEND_EVENT,
	SMSCHAR_RESUME_EVENT,
	SMSCHAR_UNKNOWN_EVENT,
	SMSCHAR_TERMINATE_EVENT
};

struct smschar_buffer_t {
	unsigned long offset;	/* offset in common buffer (mapped to user) */
	int size;
};

struct smschar_get_fw_filename_ioctl_t {
	int mode;
	char filename[200];
};

struct smschar_send_fw_file_ioctl_t {
	char *fw_buf;
	int fw_size;
};

struct smschar_send_fw_chunk_ioctl_t {
	char *buf;
	int size;
};

#define SMSCHAR_SET_DEVICE_MODE		_IOW('K', 0, int)
#define SMSCHAR_GET_DEVICE_MODE		_IOR('K', 1, int)
#define SMSCHAR_GET_BUFFER_SIZE		_IOR('K', 2, int)
#define SMSCHAR_WAIT_GET_BUFFER		_IOR('K', 3, struct smschar_buffer_t)
#define SMSCHAR_IS_DEVICE_PNP_EVENT 	_IOR('K', 4, int)
#define SMSCHAR_GET_FW_FILE_NAME	\
	_IOWR('K', 5, struct smschar_get_fw_filename_ioctl_t)
#define SMSCHAR_SEND_FW_FILE		\
	_IOW('K', 6, struct smschar_send_fw_file_ioctl_t)
#define SMSCHAR_CANCEL_WAIT_BUFFER	_IO('K', 7)
#define SMSCHAR_CANCEL_POLL			_IO('K', 8)
#define SMSCHAR_IS_CANCEL_DEVICE_PNP_EVENT _IO('K', 9)
#define SMSCHAR_SEND_FW_CHUNK              \
	_IOW('K', 10, struct smschar_send_fw_chunk_ioctl_t)
#define SMSCHAR_SEND_LAST_FW_CHUNK         \
	_IOW('K', 11, struct smschar_send_fw_chunk_ioctl_t)
#define SMSCHAR_RESET_GPIO_VALUE_CHANGE  _IOW('K', 12, int)


#endif /* __SMS_CHAR_IOCTL_H__ */
