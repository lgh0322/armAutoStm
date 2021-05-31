/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
__align(2) uint8_t uart1_tx_dma_buf[USART1_TX_BUF_SIZE]={0};
__align(2) uint8_t uart1_rx_buf[USART1_RX_BUF_SIZE]={0};

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint16_t uart1_get_data(uint8_t *data_rsv,uint16_t len)
{
	uint16_t i=0;
	if(fifo_uart1_rx.flag &&(fifo_uart1_rx.DMAsize > 0))
	{
		for(;i<len;i++)
		{
			data_rsv[i] = fifo_uart1_rx.buf[fifo_uart1_rx.head];
			fifo_uart1_rx.head ++;
			fifo_uart1_rx.head %= USART1_RX_BUF_SIZE;
			if(fifo_uart1_rx.head == fifo_uart1_rx.tail) 
			{
				fifo_uart1_rx.flag = 0;
				i++;
				break;
			}
		}
	}
	return (i);
}
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
   if(USART1 == huart->Instance){
        uint8_t data_len1;                                        
        data_len1  = USART1_RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   
        fifo_uart1_rx.tail =  data_len1; 
 
        if(fifo_uart1_rx.head <= fifo_uart1_rx.tail)
        {
            fifo_uart1_rx.DMAsize = fifo_uart1_rx.tail - fifo_uart1_rx.head;
        }
        else if(fifo_uart1_rx.head > fifo_uart1_rx.tail)
        {
            fifo_uart1_rx.DMAsize = USART1_RX_BUF_SIZE - fifo_uart1_rx.head + fifo_uart1_rx.tail;
        }
		fifo_uart1_rx.flag = 1;
//        if(p_uart1_rx_complete_callback != NULL)
//            (*p_uart1_rx_complete_callback)();
 
    }
}


void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if(USART1 == huart->Instance)                                   
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     
            USAR_UART_IDLECallback(huart);                          
        }
    }
}








uint8_t uart_dma_send_data(UART_HandleTypeDef *huart,uint8_t *buf,uint16_t len){
    
    uint16_t i=0;
    if(huart->Instance == USART1){
        /*?????????????*/
        for(i=0;i<len;i++)
        {
            fifo_uart1_tx.buf[fifo_uart1_tx.tail] = buf[i];
            fifo_uart1_tx.tail++;
            fifo_uart1_tx.tail %= USART1_TX_BUF_SIZE;
            if(fifo_uart1_tx.tail == (fifo_uart1_tx.head + USART1_TX_BUF_SIZE - 5) % USART1_TX_BUF_SIZE)//????,?????????
            {
                i++;
                fifo_uart1_tx.flag = 1;//buffer??
                break;//??for??
            }
        }
  
        if(huart1.gState != HAL_UART_STATE_BUSY_TX){ 
            if(fifo_uart1_tx.head < fifo_uart1_tx.tail){
                fifo_uart1_tx.DMAsize = fifo_uart1_tx.tail - fifo_uart1_tx.head;
            }
            else if(fifo_uart1_tx.head > fifo_uart1_tx.tail)
            {
                fifo_uart1_tx.DMAsize = USART1_TX_BUF_SIZE - fifo_uart1_tx.head;
            }
      
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)fifo_uart1_tx.buf + fifo_uart1_tx.head, fifo_uart1_tx.DMAsize);
        }
    }else if(huart->Instance == USART1){
        for(i=0;i<len;i++)
        {
            fifo_uart1_tx.buf[fifo_uart1_tx.tail] = buf[i];
            fifo_uart1_tx.tail++;
            fifo_uart1_tx.tail %= USART1_TX_BUF_SIZE;
            if(fifo_uart1_tx.tail == (fifo_uart1_tx.head + USART1_TX_BUF_SIZE - 5) % USART1_TX_BUF_SIZE)//????,?????????
            {
                i++;
                fifo_uart1_tx.flag = 1;//buffer??
                break;//??for??
            }
        }
        if(huart1.gState != HAL_UART_STATE_BUSY_TX){ //??????
            if(fifo_uart1_tx.head < fifo_uart1_tx.tail){
                fifo_uart1_tx.DMAsize = fifo_uart1_tx.tail - fifo_uart1_tx.head;
            }
            else if(fifo_uart1_tx.head > fifo_uart1_tx.tail)
            {
                fifo_uart1_tx.DMAsize = USART1_TX_BUF_SIZE - fifo_uart1_tx.head;
            }
      
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)fifo_uart1_tx.buf + fifo_uart1_tx.head, fifo_uart1_tx.DMAsize);
        }
    }
    return i;
}


uint8_t uart1_dma_send(uint8_t *buf,uint16_t len){
    uint16_t slen=0;
	uint32_t timeout = 36000000;
      
	while(1)
	{
		if(slen<len)
		{
			while(fifo_uart1_tx.flag&&(timeout--));
			if(0 == timeout)
				break;
		}
		else
			break;
		slen += uart_dma_send_data(&huart1,buf+slen,len-slen);
	}
	return HAL_OK;
 
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)//head
{
    if(huart->Instance == USART1){
        fifo_uart1_tx.head += (fifo_uart1_tx.DMAsize);
        fifo_uart1_tx.head %= USART1_TX_BUF_SIZE;
        if((fifo_uart1_tx.head != fifo_uart1_tx.tail))//||(tx_rbuf->flag)) 
        {
            if(fifo_uart1_tx.head < fifo_uart1_tx.tail) 
            {
                fifo_uart1_tx.DMAsize = fifo_uart1_tx.tail - fifo_uart1_tx.head;
			
            }
            else if(fifo_uart1_tx.head > fifo_uart1_tx.tail) 
            {
                fifo_uart1_tx.DMAsize = USART1_TX_BUF_SIZE - fifo_uart1_tx.head;
			
            }
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)fifo_uart1_tx.buf + fifo_uart1_tx.head, fifo_uart1_tx.DMAsize);
        }
        fifo_uart1_tx.flag = 0;
    }
    else if(huart->Instance == USART1){
        fifo_uart1_tx.head += (fifo_uart1_tx.DMAsize);
        fifo_uart1_tx.head %= USART1_TX_BUF_SIZE;
        if((fifo_uart1_tx.head != fifo_uart1_tx.tail))//||(tx_rbuf->flag)) 
        {
            if(fifo_uart1_tx.head < fifo_uart1_tx.tail) 
            {
                fifo_uart1_tx.DMAsize = fifo_uart1_tx.tail - fifo_uart1_tx.head;
			
            }
            else if(fifo_uart1_tx.head > fifo_uart1_tx.tail) 
            {
                fifo_uart1_tx.DMAsize = USART1_TX_BUF_SIZE - fifo_uart1_tx.head;
			
            }
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)fifo_uart1_tx.buf + fifo_uart1_tx.head, fifo_uart1_tx.DMAsize);
        }
        fifo_uart1_tx.flag = 0;
    }      
}
 
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
