/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Temp_Boiler_Pin GPIO_PIN_0
#define Temp_Boiler_GPIO_Port GPIOA
#define Current_LM321_Pin GPIO_PIN_1
#define Current_LM321_GPIO_Port GPIOA
#define Temp_Screw_Pin GPIO_PIN_2
#define Temp_Screw_GPIO_Port GPIOA
#define Temp_Gase_Pin GPIO_PIN_3
#define Temp_Gase_GPIO_Port GPIOA
#define Temp_Water_Pin GPIO_PIN_4
#define Temp_Water_GPIO_Port GPIOA
#define Thermostat_Pin GPIO_PIN_6
#define Thermostat_GPIO_Port GPIOA
#define Relay2_Pin GPIO_PIN_0
#define Relay2_GPIO_Port GPIOB
#define Relay1_Pin GPIO_PIN_1
#define Relay1_GPIO_Port GPIOB
#define Encoder_1_Pin GPIO_PIN_2
#define Encoder_1_GPIO_Port GPIOB
#define Encoder_1_EXTI_IRQn EXTI2_IRQn
#define Encoder_2_Pin GPIO_PIN_3
#define Encoder_2_GPIO_Port GPIOB
#define Encoder_2_EXTI_IRQn EXTI3_IRQn
#define Button_Pin GPIO_PIN_4
#define Button_GPIO_Port GPIOB
#define U7_MOC3021M_Pin GPIO_PIN_6
#define U7_MOC3021M_GPIO_Port GPIOB
#define U6_MOC3021M_Pin GPIO_PIN_7
#define U6_MOC3021M_GPIO_Port GPIOB
#define U2_PC817_Pin GPIO_PIN_9
#define U2_PC817_GPIO_Port GPIOB
#define U2_PC817_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
