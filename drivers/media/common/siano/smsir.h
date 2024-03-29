/**********uniscope-driver-modify-file-on-qualcomm-platform*****************/
/****************************************************************

Siano Mobile Silicon, Inc.
MDTV receiver kernel modules.
Copyright (C) 2006-2009, Uri Shkolnik

 Copyright (c) 2010 - Mauro Carvalho Chehab
	- Ported the driver to use rc-core
	- IR raw event decoding is now done at rc-core
	- Code almost re-written

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

#ifndef __SMS_IR_H__
#define __SMS_IR_H__

#include <linux/input.h>
#include <media/rc-core.h>

#define IR_DEFAULT_TIMEOUT		100


struct ir_t {
	struct rc_dev *rc_dev;
	char name[40];
	char phys[32];

	char *rc_codes;
	u64 protocol;

	u32 timeout;
	u32 controller;
	struct device *device;
};

int sms_ir_init(struct ir_t *ir, void* coredev, struct device *device);
void sms_ir_exit(struct ir_t *ir);
void sms_ir_event(struct ir_t *ir, const char *buf, int len);

#endif /* __SMS_IR_H__ */

