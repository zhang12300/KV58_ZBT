/*
 * define.h
 *
 *  Created on: Feb 14, 2018
 *      Author: ZBT
 */

#ifndef DEFINE_H_
#define DEFINE_H_
#define MYCAR_A
//#define MYCAR_B

#define Camera_CNST 85
#define NRF_LINKADDRESS {0x74, 0x18, 0x52, 0x96, 0x30}

//CAM
#define PCLK_PORT PORTC,9
#define VSYNC_PORT PORTB,23
#define VSYNC_IRQ PORTB_IRQn
#define VSYNC_ISFR PORTB_ISFR

//LCD
#define LCD_RST_PORT PORTE,27
#define LCD_RS_PORT PORTE,0
#define LCD_SDA_PORT PORTE,1
#define LCD_SCL_PORT PORTE,2

#define LCD_SPIn kSPI1
#define LCD_OTH_PCSn SPIn_PCS0
#define LCD_DC_PCSn SPIn_PCS1

#define rs PTE0_OUT
#define sda PTE1_OUT
#define scl PTE2_OUT
#define reset PTE27_OUT

//nRF
#define NRF_SPIn kSPI0
#define NRF_PCSn SPIn_PCS0
#define NRF_CE_PORT PORTA,25
#define NRF_IRQ_PORT PORTA,24

#define NRF_CE PTA25_OUT
#define NRF_IRQ PTA24_OUT

#endif /* DEFINE_H_ */
