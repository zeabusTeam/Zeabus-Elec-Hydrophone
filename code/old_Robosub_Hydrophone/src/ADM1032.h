/*
 * ADM1032.h
 *
 *  Created on: Jan 13, 2015
 *      Description: ADM1032 Temperature Monitor interface on the EZ-Board.
 *  	Author : Anol Paisal
 * 		Company : EmOne (Thailand) Co.,Ltd.
 *		Email : anolpaisal@gmail.com
 * 		Copyright @ 2015
 */

#ifndef ADM1032_H_
#define ADM1032_H_

/*******************************************************************
*  global variables and defines
*******************************************************************/

#define TWI_INTERRUPT (P0I0|P0I1|P0I2|P0I4)
#define TWIDCNT1 BIT_6
#define TWIDCNT2 BIT_7

#define	MAX_TEMPERATURE_SAMPLES	50	/* number of samples to check */

/* device address */
#define TEMP_SENSOR_ADDRESS		0x4C

/* register addresses for ADM1032 Temperature Monitor */

#define LT_R			0x00  	/* local temperature - READ */
#define LHS_W			0x0B 	/* local temperature HIGH limit - WRITE */
#define LHS_R			0x05 	/* local temperature HIGH limit - READ */
#define LLS_W			0x0C 	/* local temperature LOW limit - WRITE */
#define LLS_R			0x06 	/* local temperature LOW limit - READ */

#define RHSHB_W			0x0D 	/* remote temperature HIGH limit (high byte) - WRITE */
#define RHSHB_R			0x07 	/* remote temperature HIGH limit (high byte) - READ */
#define RHSLB_W			0x13 	/* remote temperature HIGH limit (low byte) - WRITE */
#define RHSLB_R			0x13 	/* remote temperature HIGH limit (low byte) - READ */

#define RLSHB_W			0x0E 	/* remote temperature LOW limit (high byte) - WRITE */
#define RLSHB_R			0x08 	/* remote temperature LOW limit (high byte) - READ */
#define RLSLB_W			0x14 	/* remote temperature LOW limit (low byte) - WRITE */
#define RLSLB_R			0x14 	/* remote temperature LOW limit (low byte) - READ */

#define CONFIG_W		0x09 	/* configuration register - WRITE */
#define CONFIG_R		0x03	/* configuration register - READ */
#define RCS_W			0x19	/* remote THERM limit - WRITE */
#define RCS_R			0x19	/* remote THERM limit - READ */
#define LCS_W			0x20	/* local THERM limit - WRITE */
#define LCS_R			0x20	/* local THERM limit - READ */
#define SR_R			0x02	/* status register - READ */

#define RTHB_R			0x01	/* remote temperature value (high byte) - READ */
#define RTLB_R			0x10	/* remote temperature value (low byte) - READ */
#define RTOHB_R			0x11	/* remote temperature offset (high byte) - READ */
#define RTOHB_W			0x11	/* remote temperature offset (high byte) - WRITE */
#define RTOLB_R			0x12	/* remote temperature offset (low byte) - READ */
#define RTOLB_W			0x12	/* remote temperature offset (low byte) - WRITE */

#define HYSTERISIS_R	0x21	/* therm hysterisis value - READ */
#define HYSTERISIS_W	0x21	/* therm hysterisis value - WRITE */
#define CR_W			0x0A	/* conversion rate - WRITE */
#define CR_R			0x04	/* conversion rate - READ */

/* status register bit definitions */
#define ADC_BUSY 0x80
#define LHIGH    0x40
#define LLOW	 0x20
#define RHIGH    0x10
#define RLOW	 0x08
#define OPEN 	 0x04
#define RTHRM    0x02
#define LTHRM    0x01

/* temperature limit settings */
#define REMOTE_OFFSET 			-8
#define LOCAL_THERM_LIMIT 		40
#define REMOTE_THERM_LIMIT  	45
#define THERM_HYSTERISIS 		2
#define REMOTE_ALERT_HIGH_LIMIT 40
#define REMOTE_ALERT_LOW_LIMIT  20
#define LOCAL_ALERT_HIGH_LIMIT  40
#define LOCAL_ALERT_LOW_LIMIT   20

//volatile int g_write_pend = 1;			/* write pending flag */
//volatile int g_read_pend = 1;			/* read pending flag */
//volatile int g_buff_empty = 1;			/* buffer empty flag */
//volatile int g_alert = 0;				/* temperature alert flag */

/*******************************************************************
*  function prototypes
*******************************************************************/
void Init_TWI_TempSensor(void);
////void TempSensor_ISR(int sig_int);
//static void TempSensor_ISR(int, void *);
////void TempSensor_Alert_ISR(int sig_int);
//static void TempSensor_Alert_ISR(int, void *);
//void Clear_Alert_Latch(void);
//int Read_TWI_Register(int address);
//void Write_TWI_Register(int address, int data);

#endif /* ADM1032_H_ */
