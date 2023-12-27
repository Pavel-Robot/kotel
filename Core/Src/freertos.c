/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//extern struct Sens_Analog Sens_a;
volatile unsigned long ulStatsTimerTicks;
extern TIM_HandleTypeDef htim3;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//void StartTask_LED(void *argument)
//{
//  /* USER CODE BEGIN StartTask_LED */
//  /* Infinite loop */
//  for(;;)
//  {
//	//Pumps_Water_Supply(0);
//	//Relay_Set(2, 0);
//	//Screw_process_repeate(0, 5, 5, 5);
//	//osMessagePut(Queue1Handle, (uint32_t) &Data1, 200);
//
//	//HAL_GPIO_TogglePin(Relay1_GPIO_Port, Relay1_Pin);
//    osDelay(100);
//  }
//  /* USER CODE END StartTask_LED */
//}
//
//
//void StartTask_ADC(void *argument)
//{
//  /* USER CODE BEGIN StartTask_ADC */
//	//TaskStatus_t status;
//  /* Infinite loop */
//  for(;;)
//  {
////	struct Sens_Analog Sens;
////	Average_Get_Value_mVolt(); //Снимаем показания с АЦП каналов
////	Pumps_Сentral_Heating(0);
////	status = osMessageQueueGet(QueueAnalogDataHandle, &Sens, NULL, 0);
//    osDelay(200);
//
//  }
//  /* USER CODE END StartTask_ADC */
//}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//void StartTask_T_Water(void *argument)
//{
//  /* USER CODE BEGIN StartTask_T_Water */
//  /* Infinite loop */
//  struct Sens_Analog Sens;
//  for(;;)
//  {
//	osMessageQueueGet(Queue1Handle, &Sens, 6, 100); //получаем данные из очереди
//
//	Temp_Сentral_Heating(Sens.Temp_Water);
//
//    osDelay(100);
//  }
//  /* USER CODE END StartTask_T_Water */
//}

/* USER CODE BEGIN Header_StartTask_Street */
/**
* @brief Function implementing the Task_Street thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Street */
//void StartTask_Street(void *argument)
//{
//  /* USER CODE BEGIN StartTask_Street */
//  /* Infinite loop */
//	struct Sens_Analog Sens;
//	for(;;)
//	{
//		osMessageQueueGet(Queue1Handle, &Sens, 7, 100); //получаем данные из очереди с приоритетом
//
//		Temp_Сentral_Heating(Sens.Temp_Water);
//		//Temp_Street(Sens.Temp_Street); //проверка подключен ли уличный датчик температуры
//
//	    osDelay(1);
//	  }
  /* USER CODE END StartTask_Street */
//}
/* USER CODE END Application */

