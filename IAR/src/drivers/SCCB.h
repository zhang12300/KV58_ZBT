/*
 * SCCB.h
 *
 *  Created on: Feb 18, 2018
 *      Author: ZBT
 */

#ifndef USER_DRIVER_OV7725_SCCB_H_
#define USER_DRIVER_OV7725_SCCB_H_

#define ADDR_OV7725   0x42
#define SCCB_SDA_PORT   PORTB,11
#define SCCB_SCL_PORT   PORTB,19
#define SCL_H()         PTB19_OUT = 1
#define SCL_L()         PTB19_OUT = 0
#define	SCL_DDR_OUT() 	DDRB19 = 1
#define	SCL_DDR_IN() 	DDRB19 = 0
#define SDA_H()         PTB11_OUT = 1
#define SDA_L()         PTB11_OUT = 0
#define SDA_IN()      	PTB11_IN
#define SDA_DDR_OUT()	DDRB11 = 1
#define SDA_DDR_IN()	DDRB11 = 0
#define SCCB_DELAY()	SCCB_delay(100)


void SCCB_GPIO_init(void);
int SCCB_WriteByte( u16 WriteAddress , u8 SendByte);
int SCCB_ReadByte(u8* pBuffer,   u16 length,   u8 ReadAddress);
void SCCB_delay(volatile u16 i);


#endif /* USER_DRIVER_OV7725_SCCB_H_ */
