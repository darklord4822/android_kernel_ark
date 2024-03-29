/***********uniscope-driver-modify-file-on-qualcomm-platform*****************/
 * MELFAS MMS400 Touchscreen
 *
 * Copyright (C) 2014 MELFAS Inc.
 *
 *
 * Protocol information
 * 
 * Protocol Version : MIP 4.0
 */

//Address
#define MIP_R0_INFO							0x01
#define MIP_R1_INFO_PRODUCT_NAME			0x00
#define MIP_R1_INFO_RESOLUTION_X			0x10
#define MIP_R1_INFO_RESOLUTION_Y			0x12
#define MIP_R1_INFO_NODE_NUM_X			0x14
#define MIP_R1_INFO_NODE_NUM_Y			0x15
#define MIP_R1_INFO_KEY_NUM				0x16
#define MIP_R1_INFO_VERSION_BOOT			0x20
#define MIP_R1_INFO_VERSION_CORE			0x22
#define MIP_R1_INFO_VERSION_CUSTOM		0x24
#define MIP_R1_INFO_VERSION_PARAM			0x26
#define MIP_R1_INFO_SECT_BOOT_START		0x30
#define MIP_R1_INFO_SECT_BOOT_END			0x31
#define MIP_R1_INFO_SECT_CORE_START		0x32
#define MIP_R1_INFO_SECT_CORE_END			0x33
#define MIP_R1_INFO_SECT_CUSTOM_START	0x34
#define MIP_R1_INFO_SECT_CUSTOM_END		0x35
#define MIP_R1_INFO_SECT_PARAM_START		0x36
#define MIP_R1_INFO_SECT_PARAM_END		0x37
#define MIP_R1_INFO_BUILD_DATE				0x40
#define MIP_R1_INFO_BUILD_TIME				0x44
#define MIP_R1_INFO_CHECKSUM_PRECALC		0x48
#define MIP_R1_INFO_CHECKSUM_REALTIME	0x4A
#define MIP_R1_INFO_CHECKSUM_CALC			0x4C
#define MIP_R1_INFO_PROTOCOL_NAME		0x50
#define MIP_R1_INFO_PROTOCOL_VERSION		0x58
#define MIP_R1_INFO_IC_ID					0x70

#define MIP_R0_EVENT						0x02
#define MIP_R1_EVENT_SUPPORTED_FUNC		0x00
#define MIP_R1_EVENT_FORMAT				0x04
#define MIP_R1_EVENT_SIZE					0x06
#define MIP_R1_EVENT_PACKET_INFO			0x10
#define MIP_R1_EVENT_PACKET_DATA			0x11

#define MIP_R0_CTRL							0x06	
#define MIP_R1_CTRL_READY_STATUS			0x00
#define MIP_R1_CTRL_EVENT_READY			0x01
#define MIP_R1_CTRL_MODE					0x10
#define MIP_R1_CTRL_EVENT_TRIGGER_TYPE	0x11
#define MIP_R1_CTRL_RECALIBRATE			0x12
#define MIP_R1_CTRL_POWER_STATE			0x13
#define MIP_R1_CTRL_GESTURE_TYPE			0x14
#define MIP_R1_CTRL_DISABLE_ESD_ALERT		0x18
#define MIP_R1_CTRL_CHARGER_MODE			0x19
#define MIP_R1_CTRL_GLOVE_MODE			0x1A
#define MIP_R1_CTRL_WINDOW_MODE			0x1B
#define MIP_R1_CTRL_PALM_REJECTION		0x1C
#define MIP_R1_CTRL_DISABLE_EDGE_EXPAND	0x1D

#define MIP_R0_PARAM						0x08
#define MIP_R1_PARAM_BUFFER_ADDR			0x00
#define MIP_R1_PARAM_PROTOCOL			0x04
#define MIP_R1_PARAM_MODE				0x10

#define MIP_R0_TEST							0x0A
#define MIP_R1_TEST_BUF_ADDR				0x00
#define MIP_R1_TEST_PROTOCOL				0x02
#define MIP_R1_TEST_TYPE					0x10
#define MIP_R1_TEST_DATA_FORMAT			0x20
#define MIP_R1_TEST_ROW_NUM				0x20
#define MIP_R1_TEST_COL_NUM				0x21
#define MIP_R1_TEST_BUFFER_COL_NUM		0x22
#define MIP_R1_TEST_COL_AXIS				0x23
#define MIP_R1_TEST_KEY_NUM				0x24
#define MIP_R1_TEST_DATA_TYPE				0x25

#define MIP_R0_IMAGE						0x0C
#define MIP_R1_IMAGE_BUF_ADDR				0x00
#define MIP_R1_IMAGE_PROTOCOL_ID			0x04
#define MIP_R1_IMAGE_TYPE					0x10
#define MIP_R1_IMAGE_DATA_FORMAT			0x20
#define MIP_R1_IMAGE_ROW_NUM				0x20
#define MIP_R1_IMAGE_COL_NUM				0x21
#define MIP_R1_IMAGE_BUFFER_COL_NUM		0x22
#define MIP_R1_IMAGE_COL_AXIS				0x23
#define MIP_R1_IMAGE_KEY_NUM				0x24
#define MIP_R1_IMAGE_DATA_TYPE			0x25
#define MIP_R1_IMAGE_FINGER_NUM			0x30
#define MIP_R1_IMAGE_FINGER_AREA			0x31

#define MIP_R0_LOG							0x10
#define MIP_R1_LOG_TRIGGER					0x14

//Value
#define MIP_EVENT_INPUT_PRESS			0x80
#define MIP_EVENT_INPUT_SCREEN			0x40
#define MIP_EVENT_INPUT_HOVER			0x20
#define MIP_EVENT_INPUT_PALM			0x10
#define MIP_EVENT_INPUT_ID				0x0F

#define MIP_ALERT_ESD					1
#define MIP_ALERT_WAKEUP				2

#define MIP_CTRL_STATUS_NONE			0x05
#define MIP_CTRL_STATUS_READY			0xA0
#define MIP_CTRL_STATUS_LOG			0x77

#define MIP_CTRL_MODE_NORMAL			0		
#define MIP_CTRL_MODE_PARAM			1
#define MIP_CTRL_MODE_TEST_CM			2

#define MIP_TEST_TYPE_NONE				0
#define MIP_TEST_TYPE_CM_DELTA			1
#define MIP_TEST_TYPE_CM_ABS			2
#define MIP_TEST_TYPE_CM_JITTER			3
#define MIP_TEST_TYPE_SHORT			4

#define MIP_IMG_TYPE_NONE				0
#define MIP_IMG_TYPE_INTENSITY			1
#define MIP_IMG_TYPE_RAWDATA			2
#define MIP_IMG_TYPE_WAIT				255

#define MIP_TRIGGER_TYPE_NONE			0
#define MIP_TRIGGER_TYPE_INTR			1
#define MIP_TRIGGER_TYPE_REG			2

#define MIP_LOG_MODE_NONE			0
#define MIP_LOG_MODE_TRIG				1

