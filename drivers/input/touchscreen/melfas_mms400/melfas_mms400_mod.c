/***********uniscope-driver-modify-file-on-qualcomm-platform*****************/
 * MELFAS MMS400 Touchscreen
 *
 * Copyright (C) 2014 MELFAS Inc.
 *
 *
 * Model dependent functions
 * 
 */

#include "melfas_mms400.h"
#include <linux/regulator/consumer.h>

int mms_regulator_control(struct i2c_client *client, int enable)
{
	//int ret = 0;

	//////////////////////////
	// MODIFY REQUIRED
	//

#if 0	
	static struct regulator *reg_l22;

	dev_dbg(&client->dev, "%s [START]\n", __func__);

	if (!reg_l22) {
		reg_l22 = regulator_get(&client->dev, "vd33");
		//reg_l22 = regulator_get(NULL, "8941_l22");		
		if (IS_ERR(reg_l22)) {
			dev_err(&client->dev, "%s [ERROR] regulator_get\n", __func__);
			goto ERROR;
		}
		
		ret = regulator_set_voltage(reg_l22, 3300000, 3300000);
		if (ret) {
			dev_err(&client->dev, "%s [ERROR] regulator_set_voltage\n", __func__);
			goto ERROR;
		}
	}

	if (enable) {
		ret = regulator_enable(reg_l22);
		if (ret) {
			dev_err(&client->dev, "%s [ERROR] regulator_enable [%d]\n", __func__, ret);
			goto ERROR;
		}
	}
	else{
		if (regulator_is_enabled(reg_l22)){
			ret = regulator_disable(reg_l22);
			if (ret) {
				dev_err(&client->dev, "%s [ERROR] regulator_disable [%d]\n", __func__, ret);
				goto ERROR;
			}
		}
	}

	regulator_put(reg_l22);

#endif

	//
	//////////////////////////

	dev_dbg(&client->dev, "%s [DONE]\n", __func__);
	return 0;

//ERROR:
	dev_err(&client->dev, "%s [ERROR]\n", __func__);
	return -1;
}

/**
* Turn off power supply
*/
int mms_power_off(struct mms_ts_info *info)
{
	//int ret = 0;

	dev_dbg(&info->client->dev, "%s [START]\n", __func__);
		
	//////////////////////////
	// MODIFY REQUIRED
	//

	//Control regulator
	//mms_regulator_control(info->client, 0);

	//Control power switch
	//gpio_direction_output(info->pdata->gpio_vdd_en, 0);
	gpio_direction_output(info->pdata ->gpio_reset, 0);

	//
	//////////////////////////

	msleep(50);
	
	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);
	return 0;

//ERROR:
	dev_err(&info->client->dev, "%s [ERROR]\n", __func__);	
	return -1;
}

/**
* Turn on power supply
*/
#define VDD_LOAD_MAX_UA	10000 //liguowei

static int reg_set_optimum_mode_check(struct regulator *reg, int load_uA)
{
	return (regulator_count_voltages(reg) > 0) ?
		regulator_set_optimum_mode(reg, load_uA) : 0;
}

int regulator_power_init(struct mms_ts_info *info)
{
	int ret;
	info->avdd = regulator_get(&info->client->dev, "avdd");
	if (IS_ERR(info->avdd)) {
		ret = PTR_ERR(info->avdd);
		dev_info(&info->client->dev,
			"Regulator get failed avdd ret=%d\n", ret);
	}
	return 0;

}
int regulator_power_off(struct mms_ts_info *info)
{
	int ret;
	pr_err("regulator_power_off\n");
	if (info->power_on==0) {
		dev_err(&info->client->dev,
				"Device already power off\n");
		return 0;
	}
	if (!IS_ERR(info->avdd)) {
		ret = reg_set_optimum_mode_check(info->avdd,
			VDD_LOAD_MAX_UA);
		if (ret < 0) {
			dev_err(&info->client->dev,
				"Regulator avdd set_opt failed rc=%d\n", ret);
			goto err_set_opt_avdd;
		}
		pr_err("regulator_power_off1\n");
		ret = regulator_disable(info->avdd);
		if (ret) {
			pr_err("Regulator avdd enable failed re\n");
			goto err_enable_avdd;
		} 
		pr_err("regulator_power_off2\n");
	}
	info->power_on=false;
	return 0;
err_enable_avdd:
err_set_opt_avdd:
	info->power_on=true;
	return ret;

}
int regulator_power_on(struct mms_ts_info *info)
{
	int ret;
/*
	info->avdd = regulator_get(&info->client->dev, "avdd");
	if (IS_ERR(info->avdd)) {
		ret = PTR_ERR(info->avdd);
		dev_info(&info->client->dev,
			"Regulator get failed avdd ret=%d\n", ret);
	}
*/
	if (info->power_on) {
		dev_info(&info->client->dev,
				"Device already power on\n");
		return 0;
	}
	if (!IS_ERR(info->avdd)) {
		ret = reg_set_optimum_mode_check(info->avdd,
			VDD_LOAD_MAX_UA);
		if (ret < 0) {
			dev_err(&info->client->dev,
				"Regulator avdd set_opt failed rc=%d\n", ret);
			goto err_set_opt_avdd;
		}
		ret = regulator_enable(info->avdd);
		if (ret) {
			dev_err(&info->client->dev,
				"Regulator avdd enable failed ret=%d\n", ret);
			goto err_enable_avdd;
		} 
	}
		info->power_on=true;
		return 0;
 err_enable_avdd:
 err_set_opt_avdd:
	info->power_on=false;
	return ret;
}

int mms_power_on(struct mms_ts_info *info)
{
	int ret = 0;

	dev_dbg(&info->client->dev, "%s [START]\n", __func__);
	
	//////////////////////////
	// MODIFY REQUIRED
	//
	
	//Control regulator
	//mms_regulator_control(info->client, 1);

	//Control power switch
	//gpio_direction_output(info->pdata->gpio_vdd_en, 1);
	

		ret = gpio_direction_output(info->pdata ->gpio_reset, 0);
		if (ret) {
			printk("mms_reset failed!\n");
		}
		msleep(20);
		gpio_set_value_cansleep(info->pdata ->gpio_reset, 1);

	//
	//////////////////////////
	
	msleep(50);
	
	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);
	return 0;

//ERROR:
	dev_err(&info->client->dev, "%s [ERROR]\n", __func__);	
	return -1;
}

/**
* Clear touch input events
*/
void mms_clear_input(struct mms_ts_info *info)
{
	int i;
	
	for (i = 0; i< MAX_FINGER_NUM; i++) {
		/////////////////////////////////
		// MODIFY REQUIRED
		//
		
		input_mt_slot(info->input_dev, i);
		input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, false);
		
		//
		/////////////////////////////////
	}
	
	input_sync(info->input_dev);
	
	return;
}

/**
* Input event handler - Report touch input event
*/
void mms_input_event_handler(struct mms_ts_info *info, u8 sz, u8 *buf)
{
	struct i2c_client *client = info->client;
	int i;

	dev_dbg(&client->dev, "%s [START]\n", __func__);
	dev_dbg(&client->dev, "%s - sz[%d] buf[0x%02X]\n", __func__, sz, buf[0]);

	for (i = 1; i < sz; i += info->event_size) {
		u8 *tmp = &buf[i];

		int id = (tmp[0] & 0xf) - 1;
		int x = tmp[2] | ((tmp[1] & 0xf) << 8);
		int y = tmp[3] | (((tmp[1] >> 4) & 0xf) << 8);
		int touch_major = tmp[4];
		int pressure = tmp[5];
						
		// Report input data
		if ((tmp[0] & MIP_EVENT_INPUT_SCREEN) == 0) {
			//Touchkey Event
			int key = tmp[0] & 0xf;
			int key_state = (tmp[0] & MIP_EVENT_INPUT_PRESS) ? 1 : 0;
			int key_code = 0;
			
			/////////////////////////////////
			// MODIFY REQUIRED
			//

			//Report touchkey event
			switch (key) {
				case 1:
					key_code = KEY_MENU;
					dev_dbg(&client->dev, "Key : KEY_MENU\n");
					break;
				case 2:
					key_code = 172;
					dev_dbg(&client->dev, "Key : KEY_HOME\n");
					break;
				case 3:
					key_code = KEY_BACK;
					dev_dbg(&client->dev, "Key : KEY_BACK\n");
					break;
				default:
					dev_err(&client->dev, "%s [ERROR] Unknown key code [%d]\n", __func__, key);
					continue;
					break;
			}
			input_report_key(info->input_dev, key_code, key_state);
			
			dev_dbg(&client->dev, "%s - Key : ID[%d] Code[%d] State[%d]\n", __func__, key, key_code, key_state);			
			
			//
			/////////////////////////////////			
		}
		else
		{
			//Touchscreen Event
			
			/////////////////////////////////
			// MODIFY REQUIRED
			//

			//Report touchscreen event
			if((tmp[0] & MIP_EVENT_INPUT_PRESS) == 0) {
				//Release
				input_mt_slot(info->input_dev, id);
				input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, false);				
				dev_dbg(&client->dev, "%s - Touch : ID[%d] Release\n", __func__, id);
				input_sync(info->input_dev);  //zhangbing@uni drv 20150408 add
				continue;
			}			
			
			//Press or Move
			input_mt_slot(info->input_dev, id);
			input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, true);						
			input_report_abs(info->input_dev, ABS_MT_POSITION_X, x);
			input_report_abs(info->input_dev, ABS_MT_POSITION_Y, y);
			input_report_abs(info->input_dev, ABS_MT_PRESSURE, pressure);
			input_report_abs(info->input_dev, ABS_MT_TOUCH_MAJOR, touch_major);
			dev_dbg(&client->dev, "%s - Touch : ID[%d] X[%d] Y[%d] P[%d] M[%d] \n", __func__, id, x, y, pressure, touch_major);			

			//input_mt_sync(info->input_dev);//zhangbing@uni drv 20150407 add Multipoint report
			//
			/////////////////////////////////
		}
		input_sync(info->imnput_dev);//zhangbing@uni drv 20150407 add2
	}
	
	//input_sync(info->input_dev); //  zhangbing@uniscope drv 20150407 modify the position of input_sync(info->input_dev) function
	
//EXIT:
	dev_dbg(&client->dev, "%s [DONE]\n", __func__);
	return;
}

/**
* Wake-up event handler
*/
int mms_wakeup_event_handler(struct mms_ts_info *info, u8 *rbuf)
{
	//u8 gesture_type = rbuf[2];
	
	dev_dbg(&info->client->dev, "%s [START]\n", __func__);
	
	/////////////////////////////////
	// MODIFY REQUIRED
	//

	//Report wake-up event
	
	//
	//
	/////////////////////////////////
	
	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);
	return 0;
	
//ERROR:
	//return 1;
}

#if MMS_USE_DEVICETREE
/**
* Parse device tree
*/
int mms_parse_devicetree(struct device *dev, struct mms_ts_info *info)
{
	//struct i2c_client *client = to_i2c_client(dev);
	//struct mms_ts_info *info = i2c_get_clientdata(client);
	struct device_node *np = dev->of_node;
	u32 val;
	int ret;

	dev_dbg(dev, "%s [START]\n", __func__);

	/////////////////////////////////
	// MODIFY REQUIRED
	//
	
	//Read property
	ret = of_property_read_u32(np, MMS_DEVICE_NAME",max_x", &val);
	if (ret) {
		dev_err(dev, "%s [ERROR] max_x\n", __func__);
		info->pdata->max_x = 1080;
	} 
	else {
		info->pdata->max_x = val;
	}

	ret = of_property_read_u32(np, MMS_DEVICE_NAME",max_y", &val);
	if (ret) {
		dev_err(dev, "%s [ERROR] max_y\n", __func__);
		info->pdata->max_y = 1920;
	}
	else {
		info->pdata->max_y = val;
	}
	
	//Get GPIO 
	ret = of_get_named_gpio(np, MMS_DEVICE_NAME",irq-gpio", 0);
	if (!gpio_is_valid(ret)) {
		dev_err(dev, "%s [ERROR] of_get_named_gpio : irq-gpio\n", __func__);
		goto ERROR;
	}
	else{
		info->pdata->gpio_intr = ret;
	}


	ret = of_get_named_gpio(np, MMS_DEVICE_NAME",reset-gpio", 0);
	if (!gpio_is_valid(ret)) {
		dev_err(dev, "%s [ERROR] of_get_named_gpio : reset-gpio\n", __func__);
		goto ERROR;
	}
	else{
		info->pdata->gpio_reset = ret;
		//pr_err("gpio_reset is %d\n",ret);
	}

	
	//Config GPIO
	ret = gpio_request(info->pdata->gpio_intr, "irq-gpio");
	if (ret < 0) {
		dev_err(dev, "%s [ERROR] gpio_request : irq-gpio\n", __func__);
		goto ERROR;
	}	
	gpio_direction_input(info->pdata->gpio_intr);	
/*
	ret = gpio_tlmm_config(GPIO_CFG(info->pdata->gpio_intr, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	if (ret < 0){
		dev_err(&info->client->dev, "%s [ERROR] gpio_tlmm_config gpio_intr\n", __func__);
		goto ERROR;
	}
	*/


	ret = gpio_request(info->pdata->gpio_reset, "reset-gpio");
	if (ret < 0) {
		dev_err(dev, "%s [ERROR] gpio_request : reset-gpio\n", __func__);
		goto ERROR;
	}		
	gpio_direction_output(info->pdata->gpio_reset, 1);

	
	//Set IRQ
	info->client->irq = gpio_to_irq(info->pdata->gpio_intr); 
	//dev_dbg(dev, "%s - gpio_to_irq : irq[%d]\n", __func__, info->client->irq);
		
	//
	/////////////////////////////////
	
	dev_dbg(dev, "%s [DONE]\n", __func__);	
	return 0;

ERROR:
	if (gpio_is_valid(info->pdata->gpio_reset))
		gpio_free(info->pdata->gpio_reset);
	if (gpio_is_valid(info->pdata->gpio_intr))
		gpio_free(info->pdata->gpio_intr);
	dev_err(dev, "%s [ERROR]\n", __func__);	
	return 1;
}
#endif

/**
* Config input interface	
*/
void mms_config_input(struct mms_ts_info *info)
{
	struct input_dev *input_dev = info->input_dev;

	dev_dbg(&info->client->dev, "%s [START]\n", __func__);	

	/////////////////////////////
	// MODIFY REQUIRED
	//

	//Screen
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);

	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
	
	input_mt_init_slots(input_dev, MAX_FINGER_NUM, 0);

	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, info->max_x, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, info->max_y, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, INPUT_PRESSURE_MAX, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, INPUT_TOUCH_MAJOR_MAX, 0, 0);

	//Key
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(KEY_BACK, input_dev->keybit);
	set_bit(KEY_MENU, input_dev->keybit);
	set_bit(172, input_dev->keybit);

#if MMS_USE_NAP_MODE
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(KEY_POWER, input_dev->keybit);
#endif	
	
	//
	/////////////////////////////

	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);	
	return;
}

#if MMS_USE_CALLBACK
/**
* Callback - get charger status
*/
void mms_callback_charger(struct mms_callbacks *cb, int charger_status)
{
	struct mms_ts_info *info = container_of(cb, struct mms_ts_info, callbacks);

	dev_dbg(&info->client->dev, "%s [START]\n", __func__);

	dev_info(&info->client->dev, "%s - charger_status[%d]\n", __func__, charger_status);
	
	//...
	
	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);
}

/**
* Callback - add callback funtions here
*/
//...

/**
* Config callback functions
*/
void mms_config_callback(struct mms_ts_info *info)
{
	dev_dbg(&info->client->dev, "%s [START]\n", __func__);	

	info->register_callback = info->pdata->register_callback;

	//callback functions
	info->callbacks.inform_charger = mms_callback_charger;
	//info->callbacks.inform_display = mms_callback_display;
	//...
	
	if (info->register_callback){
		info->register_callback(&info->callbacks);
	}
	
	dev_dbg(&info->client->dev, "%s [DONE]\n", __func__);	
	return;
}
#endif

