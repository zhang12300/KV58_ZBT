/*
 * Port_cfg.h
 *
 *  Created on: Feb 17, 2018
 *      Author: ZBT
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/**********************************  FTM  *******************************************/
#define FTM0_CH0    PTC1        //PTC1  PTE24  PTD0
#define FTM0_CH1    PTC2        //PTC2  PTA4   PTE25  PTD1
#define FTM0_CH2    PTA5        //PTC3  PTA5   PTE29  PTD2  PTC5
#define FTM0_CH3    PTC4        //PTC4  PTA6   PTE30  PTD3
#define FTM0_CH4    PTA7        //PTD4  PTA7   PTE26  PTD4
#define FTM0_CH5    PTD5        //PTD5  PTD5
#define FTM0_CH6    PTD6        //PTD6  PTD6
#define FTM0_CH7    PTD7        //PTD7  PTD7

#define FTM1_CH0    PTA8       //PTA8  PTA12  PTB0  PTE20  PTA2  PTD6
#define FTM1_CH1    PTA9       //PTA9  PTA13  PTB1  PTE21  PTA1  PTD7

#define FTM2_CH0    PTB18       //PTA10  PTB18  PTE22
#define FTM2_CH1    PTB19       //PTA11  PTB19  PTE23

#define FTM3_CH0    PTE5        // PTE5、PTD0
#define FTM3_CH1    PTE6        // PTE6、PTD1
#define FTM3_CH2    PTE7        // PTE7、PTD2 PTB18
#define FTM3_CH3    PTE8        // PTE8、PTD3 PTB19
#define FTM3_CH4    PTC8        // PTE9、PTC8
#define FTM3_CH5    PTE10       // PTE10、PTC9
#define FTM3_CH6    PTC10       // PTE11、PTC10
#define FTM3_CH7    PTC11       // PTE12、PTC11

//正交解码
#define FTM1_QDPHA  PTE20       //PTA8、PTA12、PTB0 PTE20
#define FTM1_QDPHB  PTE21       //PTA9、PTA13、PTB1 PTE21

#define FTM2_QDPHA  PTE22       //PTA10、PTB18 PTE22
#define FTM2_QDPHB  PTE23       //PTA11、PTB19 PTE23

/**********************************  SPI  *******************************************/
#define SPI0_SCK    PTA15       // PTA15、PTC5、PTD1
#define SPI0_SOUT   PTA16       // PTA16、PTC6、PTD2
#define SPI0_SIN    PTA17       // PTA17、PTC7、PTD3

#define SPI0_PCS0   PTA14       // PTA14、PTC4、PTD0
#define SPI0_PCS1   NULL        // PTC3、PTD4
#define SPI0_PCS2   PTD5        // PTC2、PTD5
#define SPI0_PCS3   NULL        // PTC1、PTD6
#define SPI0_PCS4   NULL        // PTC0
#define SPI0_PCS5   NULL       // PTB23


#define SPI1_SCK    PTE2       // PTE2、PTB11
#define SPI1_SOUT   PTE1       // PTE1、PTB16
#define SPI1_SIN    PTE3       // PTE3、PTB17

#define SPI1_PCS0   PTE4        // PTE4、PTB10
#define SPI1_PCS1   PTE0        // PTE0、PTB9
#define SPI1_PCS2   NULL        // PTE5
#define SPI1_PCS3   NULL        // PTE6


#define SPI2_SCK    PTD12       // PTB21、PTD12
#define SPI2_SOUT   PTD13       // PTB22、PTD13
#define SPI2_SIN    PTD14       // PTB23、PTD14
#define SPI2_PCS0   PTD11       // PTB20、PTD11
#define SPI2_PCS1   PTD15       // PTD15

/**********************************  I2C   ***************************************/
//      模块通道    端口          可选范围              建议
#define I2C0_SCL    PTB0        // PTA12 PTB0 PTB2 PTC6 PTD2 PTD8 PTE19 PTE24 
#define I2C0_SDA    PTB1        // PTA11 PTB1 PTB3 PTC7 PTD3 PTD9 PTE18 PTE25

#define I2C1_SCL    PTC10       // PTA14 PTC10 PTD8 PTE1
#define I2C1_SDA    PTC11       // PTA13 PTC11 PTD9 PTE0

/**********************************  UART(引脚复用)***************************/
//      模块通道    端口          可选范围                          建议
#define UART0_RX    PTB0       //PTA1、PTA15、PTB16、PTD6 PTE21 PTB0 PTC6      PTA1不要用（与J-LINK冲突）
#define UART0_TX    PTB1       //PTA2、PTA14、PTB17、PTD7 PTE20 PTB1 PTC7     PTA2不要用（与J-LINK冲突）

#define UART1_RX    PTC3        //PTC3、PTE1
#define UART1_TX    PTC4        //PTC4、PTE0

#define UART2_RX    PTE17        //PTD2 PTE17
#define UART2_TX    PTE16        //PTD3 PTE16

#define UART3_RX    PTC16       //PTB10、PTC16、PTE5
#define UART3_TX    PTC17       //PTB11、PTC17、PTE4

#define UART4_RX    PTE25       //PTC14、PTE25
#define UART4_TX    PTE24       //PTC15、PTE24

#define UART5_RX    PTE9        //PTD8 、PTE9 
#define UART5_TX    PTE8        //PTD9 、PTE8 
/**********************************  UART(引脚复用) ***************************************/
#endif /* PORT_CFG_H_ */
