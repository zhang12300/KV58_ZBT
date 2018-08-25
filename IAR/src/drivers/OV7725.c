/*
* OV7725.c
*
*  Created on: Feb 18, 2018
*      Author: ZBT
*/

#include "include.h"
#include "define.h"
#include "SCCB.h"
#include "OV7725.h"
#include "OV7725_REG.h"

unsigned char Image_USE[CAMERA_H + 1][CAMERA_DMA_NUM] = { { 0 } };
unsigned char Image_TMP[CAMERA_H + 1][CAMERA_DMA_NUM] = { { 0 } };
volatile u8 img_flag = IMG_FINISH;		//图像状态
edma_tcd_t OV7725_tcd;
edma_handle_t g_EDMA_Handle;
edma_config_t userConfig;

edma_transfer_config_t DMA_Transfer_config;

void Ov7725_exti_Init()
{
  //FIFO端口初始化
  GPIO_Init(PORTC, 0, GPI, HIGH);
  GPIO_Init(PORTC, 1, GPI, HIGH);
  GPIO_Init(PORTC, 2, GPI, HIGH);
  GPIO_Init(PORTC, 3, GPI, HIGH);
  GPIO_Init(PORTC, 4, GPI, HIGH);
  GPIO_Init(PORTC, 5, GPI, HIGH);
  GPIO_Init(PORTC, 6, GPI, HIGH);
  GPIO_Init(PORTC, 7, GPI, HIGH);
  //DMA通道0初始化，上升沿触发DMA传输，源地址为PTD_BYTE0_IN，目的地址为：BUFF ，每次传输1Byte，传输CAMERA_SIZE次后停止传输
  port_init(PCLK_PORT, DMA_RISING | PULL_UP);    //PCLK
  port_init(VSYNC_PORT, RISING | PULL_DOWN | PF);    //场中断，下拉，下降沿触发中断，带滤波
  NVIC_DisableIRQ(VSYNC_IRQ);
  //关闭PTB的中断
  DMAMUX_Init(DMAMUX);
  DMAMUX_SetSource(DMAMUX, CAMERA_DMA_CH, 51);	//PORTC
  DMAMUX_EnableChannel(DMAMUX, CAMERA_DMA_CH);
}

void DMATransfer_Init()
{
  DMA_Transfer_config.srcAddr = (uint32_t)(&PTC_BYTE0_IN);
  DMA_Transfer_config.srcOffset = 0x00u;
  DMA_Transfer_config.destAddr = (uint32_t)(Image_TMP);
  DMA_Transfer_config.destOffset = 0x01u;
  DMA_Transfer_config.destTransferSize = kEDMA_TransferSize1Bytes;
  DMA_Transfer_config.srcTransferSize = kEDMA_TransferSize1Bytes;
  DMA_Transfer_config.majorLoopCounts = 9600;
  DMA_Transfer_config.minorLoopBytes = 0x01u;
  
  EDMA_ResetChannel(DMA0,4);
  EDMA_SetTransferConfig(DMA0,4,&DMA_Transfer_config,NULL);
  
  EDMA_SetBandWidth(DMA0,4,kEDMA_BandwidthStallNone);
  EDMA_EnableAutoStopRequest(DMA0,4,true);
  EDMA_EnableChannelInterrupts(DMA0,4,kEDMA_MajorInterruptEnable);
  
  DMAMUX_SetSource(DMAMUX,4,51);
  DMAMUX_EnableChannel(DMAMUX,4);
  
  EDMA_ClearChannelStatusFlags(DMA0,4,kEDMA_InterruptFlag);
  
  PORT_SetPinInterruptConfig(PORTC,9u,kPORT_DMARisingEdge);
  
  NVIC_EnableIRQ(DMA4_DMA20_IRQn);
  DMA0->SERQ = DMA_SERQ_SERQ(4);
}

void ov7725_get_img()
{
  img_flag = IMG_START;			//开始采集图像
  //	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
  //	EDMA_InstallTCDMemory(&g_EDMA_Handle, &OV7725_tcd, 1);
  //	EDMA_SubmitTransfer(&g_EDMA_Handle, &DMA_Transfer_config);
  //	EDMA_StartTransfer(&g_EDMA_Handle);
  NVIC_DisableIRQ(VSYNC_IRQ);
  DMATransfer_Init();
}

void Camera_start(void)
{
  VSYNC_ISFR = ~0;
  NVIC_EnableIRQ(VSYNC_IRQ);
}

/*OV7725初始化配置表*/
Register_Info ov7727_reg[] = {
  //寄存器，寄存器值次
  { COM4, 0xC1 }, 
  { CLKRC, 0x00 }, 
  { COM2, 0x03 }, 
  { COM3, 0xD0 }, 
  { COM7,  0x40 }, 
  { HSTART, 0x3F }, 
  { HSIZE, 0x50 }, 
  { VSTRT, 0x03 }, 
  { VSIZE, 0x78 }, 
  { HREF, 0x00 }, 
  { SCAL0, 0x0A }, 
  { AWB_Ctrl0, 0xE0 }, 
  { DSPAuto, 0xff }, 
  { DSP_Ctrl2, 0x0C }, 
  { DSP_Ctrl3, 0x00 }, 
  { DSP_Ctrl4, 0x00 },
        
#if (CAMERA_W == 80)
        { HOutSize ,0x14},
#elif (CAMERA_W == 160)
        { HOutSize ,0x28},
#elif (CAMERA_W == 240)
        { HOutSize ,0x3c},
#elif (CAMERA_W == 320)
        { HOutSize, 0x50 },
#else
        
#endif
        
#if (CAMERA_H == 60 )
        { VOutSize ,0x1E},
#elif (CAMERA_H == 120 )
        { VOutSize ,0x3c},
#elif (CAMERA_H == 180 )
        { VOutSize ,0x5a},
#elif (CAMERA_H == 240 )
        { VOutSize, 0x78 },
#else
        
#endif
        
        { EXHCH, 0x00 }, 
        { GAM1, 0x0c }, 
        { GAM2, 0x16 }, 
        { GAM3, 0x2a }, 
        { GAM4, 0x4e }, 
        { GAM5, 0x61 }, 
        { GAM6, 0x6f }, 
        { GAM7, 0x7b }, 
        { GAM8, 0x86 }, 
        { GAM9, 0x8e }, 
        { GAM10, 0x97 }, 
        { GAM11, 0xa4 }, 
        { GAM12, 0xaf }, 
        { GAM13, 0xc5 },
        { GAM14, 0xd7 }, 
        { GAM15, 0xe8 }, 
        { SLOP, 0x20 }, 
        { LC_RADI, 0x00 }, 
        { LC_COEF, 0x13 }, 
        { LC_XC, 0x08 }, 
        { LC_COEFB, 0x14 }, 
        { LC_COEFR, 0x17 }, 
        { LC_CTR, 0x05 },
        { BDBase, 0x99 }, 
        { BDMStep, 0x03 }, 
        { SDE, 0x04 }, 
        { BRIGHT, 0x00 },
	{ CNST, 100 }, 	//100//150:楼上楼下都能跑（第一个车稳）70
	{ SIGN, 0x06 }, { UVADJ0, 0x11 }, { UVADJ1, 0x02 }, };

u8 cfgnum = sizeof(ov7727_reg) / sizeof(ov7727_reg[0]); /*结构体数组成员数目*/

/************************************************
* 函数名：Ov7725_Init
* 描述  ：Sensor初始化
* 输入  ：无
* 输出  ：返回1成功，返回0失败
* 注意  ：无
************************************************/
u8 Ov7725_Init()
{
  while (Ov7725_reg_Init() == 0)
    ;
  Ov7725_exti_Init();
  return 0;
}

/************************************************
* 函数名：Ov7725_reg_Init
* 描述  ：Sensor 寄存器 初始化
* 输入  ：无
* 输出  ：返回1成功，返回0失败
* 注意  ：无
************************************************/
u8 Ov7725_reg_Init(void)
{
  u16 i = 0;
  u8 Sensor_IDCode = 0;
  SCCB_GPIO_init();
  OV7725_Delay_ms(50);
  while (0 == SCCB_WriteByte(0x12, 0x80)) /*复位sensor */
  {
    i++;
    if (i == 20)
    {
      return 0;
    }
  }
  OV7725_Delay_ms(50);
  if (0 == SCCB_ReadByte(&Sensor_IDCode, 1, 0x0b)) /* 读取sensor ID号*/
  {
    return 0;
  }
  if (Sensor_IDCode == OV7725_ID)
  {
    for (i = 0; i < cfgnum; i++)
    {
      if(ov7727_reg[i].Address == CNST)
      {
        if (0 == SCCB_WriteByte(ov7727_reg[i].Address, Camera_CNST))
        {
          return 0;
        }
      }
      else
      {
        if (0 == SCCB_WriteByte(ov7727_reg[i].Address, ov7727_reg[i].Value))
        {
          return 0;
        }
      }
      
    }
  }
  else
  {
    return 0;
  }
  return 1;
}
