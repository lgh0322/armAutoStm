/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#ifndef _TypeDef_H_
#define _TypeDef_H_

#ifdef WIN32
#include <windows.h>
#endif

#ifndef UINT8
#define UINT8  unsigned char
#endif

#ifndef INT8
#define INT8   signed char
#endif

#ifndef UINT16
#define UINT16 unsigned short int
#endif

#ifndef INT16
#define INT16  signed short int
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef INT32
#define INT32  int
#endif

#ifndef LONG
#define LONG  INT32
#endif

#ifndef INT64
#define INT64  __int64
#endif

#ifndef UINT64
#define UINT64 unsigned __int64
#endif

#ifndef CHAR
#define CHAR   char
#endif

#ifndef UCHAR
#define UCHAR  unsigned char
#endif

#ifndef FLOAT
#define FLOAT  float
#endif

#ifndef DOUBLE
#define DOUBLE double
#endif

#ifndef BOOL
#define BOOL  INT8
#endif

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef NULL
#define NULL  (0)
#endif

#ifndef BYTE
#define BYTE    CHAR
#endif

#ifndef  VOID
#define VOID    void
#endif

#ifndef  HANDLE
#define HANDLE     VOID *
#endif

#endif //_TypeDef_H_

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define USART1_RX_BUF_SIZE 128
#define USART1_TX_BUF_SIZE 128

typedef struct{
	uint16_t head;
	uint16_t tail;
	uint16_t DMAsize;
	uint8_t *buf;
	uint8_t flag;
}uart_fifo_t;


extern __align(2) uint8_t uart1_tx_dma_buf[USART1_TX_BUF_SIZE];
extern __align(2) uint8_t uart1_rx_buf[USART1_RX_BUF_SIZE];
static __IO uart_fifo_t fifo_uart1_tx={0,0,0,uart1_tx_dma_buf,0}; 
static __IO uart_fifo_t fifo_uart1_rx={0,0,USART1_RX_BUF_SIZE,uart1_rx_buf,0}; 
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
uint16_t uart1_get_data(uint8_t *data_rsv,uint16_t len);
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
uint8_t uart_dma_send_data(UART_HandleTypeDef *huart,uint8_t *buf,uint16_t len);
uint8_t uart1_dma_send(uint8_t *buf,uint16_t len);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
