/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  **************************************                                                                                                                                                      ****************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "App/Sens_and_all.h"
#include "App/Failure.h"
#include "stdio.h" //для отладки через swo
#include "App/sim800.h"

#include "Control/buttons.h"
#include "Graphics/draw_functions.h"

//#include "freertos.c"



#define Enc_A() HAL_GPIO_ReadPin(Encoder_1_GPIO_Port, Encoder_1_Pin)
#define Enc_B() HAL_GPIO_ReadPin(Encoder_2_GPIO_Port, Encoder_2_Pin)


//uint8_t rot_old_state = 0, rot_new_state = 0;
//uint8_t rot_cnt = 0;
//uint16_t encode_val = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

//typedef struct {
//
//	uint16_t Value;
//	int8_t Sender;
//
//} DataQueue;

//uint32_t DataonTask = 0;








/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern uint16_t adcData[ADC_CHANNELS_NUM]; //В буфере adcData[] будем сохранять сырые данные с АЦП
extern uint32_t adcVoltage[ADC_CHANNELS_NUM]; //пересчитанные в миллиВольты значения
extern struct Sens_Analog Sens_a;

extern uint8_t flag_work; //Запущен ли котел 0 - нет

extern uint8_t Try_count; // Кол-во попыток, устанавливается пользователем от 2 до 7
extern uint8_t Fail_current_screw_count; //кол-во аварий шнека подряд
extern uint8_t Try_Time; //- нужно добавить. Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается

extern int8_t rot_cnt;
extern INPUT input;
//extern Parameters state_arr[ADC_CHANNELS_NUM];


uint8_t short_clicking = 0;
uint8_t long_clicking = 0;
//uint32_t Enc_Counter = 0; //счетчик енкодера

//extern float Resist;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

uint8_t Encoder_State = 0;
//uint8_t Encoder_Value = 0;
//void encode(){
//
//	  if (Enc_A() == GPIO_PIN_RESET)  // If the OUTA is RESET
//	  {
//		  if (Enc_B() == GPIO_PIN_RESET)  // If OUTB is also reset... CCK
//		  {
//			  while (Enc_B() == GPIO_PIN_RESET){osDelay(1);};  // wait for the OUTB to go high
//			  Encoder_Value--;
//			  while (Enc_A() == GPIO_PIN_RESET){osDelay(1);};  // wait for the OUTA to go high
//			  osDelay(1);
//			  //HAL_Delay (10);  // wait for some more time
//		  }
//
//		  else if (Enc_B() == GPIO_PIN_SET)  // If OUTB is also set
//		  {
//			  while (Enc_B() == GPIO_PIN_SET){osDelay(1);};  // wait for the OUTB to go LOW.. CK
//			  Encoder_Value++;
//			  while (Enc_A() == GPIO_PIN_RESET){osDelay(1);};  // wait for the OUTA to go high
//			  while (Enc_B()){osDelay(1);};  // wait for the OUTB to go high
//			  osDelay(1);
//			  //HAL_Delay (10);  // wait for some more time
//		  }
//
//		  //На случай если нужно ограничить счетчик
//		  if (Encoder_Value<0) Encoder_Value = 0;
//		  if (Encoder_Value>100) Encoder_Value = 100;
//	  }
//}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_ADC */
osThreadId_t Task_ADCHandle;
const osThreadAttr_t Task_ADC_attributes = {
  .name = "Task_ADC",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for Task_T_Screw */
osThreadId_t Task_T_ScrewHandle;
const osThreadAttr_t Task_T_Screw_attributes = {
  .name = "Task_T_Screw",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for Task_Sens_Connt */
osThreadId_t Task_Sens_ConntHandle;
const osThreadAttr_t Task_Sens_Connt_attributes = {
  .name = "Task_Sens_Connt",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow6,
};
/* Definitions for Task_Hopper_Cov */
osThreadId_t Task_Hopper_CovHandle;
const osThreadAttr_t Task_Hopper_Cov_attributes = {
  .name = "Task_Hopper_Cov",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow6,
};
/* Definitions for Task_Current */
osThreadId_t Task_CurrentHandle;
const osThreadAttr_t Task_Current_attributes = {
  .name = "Task_Current",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow5,
};
/* Definitions for Task_T_Boiler */
osThreadId_t Task_T_BoilerHandle;
const osThreadAttr_t Task_T_Boiler_attributes = {
  .name = "Task_T_Boiler",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow3,
};
/* Definitions for Task_T_Gase */
osThreadId_t Task_T_GaseHandle;
const osThreadAttr_t Task_T_Gase_attributes = {
  .name = "Task_T_Gase",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for Task_T_Waters */
osThreadId_t Task_T_WatersHandle;
const osThreadAttr_t Task_T_Waters_attributes = {
  .name = "Task_T_Waters",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for Task_Manage */
osThreadId_t Task_ManageHandle;
const osThreadAttr_t Task_Manage_attributes = {
  .name = "Task_Manage",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Menu */
osThreadId_t Task_MenuHandle;
const osThreadAttr_t Task_Menu_attributes = {
  .name = "Task_Menu",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Button */
osThreadId_t Task_ButtonHandle;
uint32_t Task_ButtonBuffer[ 128 ];
osStaticThreadDef_t Task_ButtonControlBlock;
const osThreadAttr_t Task_Button_attributes = {
  .name = "Task_Button",
  .cb_mem = &Task_ButtonControlBlock,
  .cb_size = sizeof(Task_ButtonControlBlock),
  .stack_mem = &Task_ButtonBuffer[0],
  .stack_size = sizeof(Task_ButtonBuffer),
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for Task_SMS */
osThreadId_t Task_SMSHandle;
uint32_t Task_SMSBuffer[ 128 ];
osStaticThreadDef_t Task_SMSControlBlock;
const osThreadAttr_t Task_SMS_attributes = {
  .name = "Task_SMS",
  .cb_mem = &Task_SMSControlBlock,
  .cb_size = sizeof(Task_SMSControlBlock),
  .stack_mem = &Task_SMSBuffer[0],
  .stack_size = sizeof(Task_SMSBuffer),
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for Task_FanManage */
osThreadId_t Task_FanManageHandle;
uint32_t Task_FanManageBuffer[ 64 ];
osStaticThreadDef_t Task_FanManageControlBlock;
const osThreadAttr_t Task_FanManage_attributes = {
  .name = "Task_FanManage",
  .cb_mem = &Task_FanManageControlBlock,
  .cb_size = sizeof(Task_FanManageControlBlock),
  .stack_mem = &Task_FanManageBuffer[0],
  .stack_size = sizeof(Task_FanManageBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Queue1 */
osMessageQueueId_t Queue1Handle;
const osMessageQueueAttr_t Queue1_attributes = {
  .name = "Queue1"
};
/* Definitions for Timer_Try */
osTimerId_t Timer_TryHandle;
const osTimerAttr_t Timer_Try_attributes = {
  .name = "Timer_Try"
};
/* Definitions for Timer_Boiler_Zero */
osTimerId_t Timer_Boiler_ZeroHandle;
const osTimerAttr_t Timer_Boiler_Zero_attributes = {
  .name = "Timer_Boiler_Zero"
};
/* Definitions for myTimer_test */
osTimerId_t myTimer_testHandle;
const osTimerAttr_t myTimer_test_attributes = {
  .name = "myTimer_test"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);
void StartDefaultTask(void *argument);
void StartTask_ADC(void *argument);
void StartTask_T_Screw(void *argument);
void StartTask_Sens_Connect(void *argument);
void StartTask_Hopper_Cover(void *argument);
void StartTask_Current(void *argument);
void StartTask_T_Boiler(void *argument);
void StartTask_T_Gase(void *argument);
void StartTask_T_Waters(void *argument);
void StartTask_Manage(void *argument);
void StartTask_Menu(void *argument);
void StartTask_Button(void *argument);
void StartTask_SMS(void *argument);
void StartTask_FanManage(void *argument);
void Callback01(void *argument);
void Callback02(void *argument);
void Callback_test(void *argument);

/* USER CODE BEGIN PFP */
//int _write(int file, char *ptr, int len){
//
//	int i =8;
//	for(i=0; i<len; i++)
//			ITM_SendChar((*ptr++));
//
//	return len;
//
//}


//int _write(int file, char *str, int len)
//{
//    if( HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str)) == HAL_OK ) {
//        return len;
//    } else {
//        return -1;
//    }
//}



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  //SIM800_Init(); //инициализация для сим800 - должна быть в таске, там нужна задержка


  HAL_ADCEx_Calibration_Start(&hadc1); //Калибровка АЦП
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcData, ADC_CHANNELS_NUM); //Провести измерение с АЦП-1
  //HAL_TIM_Base_Start_IT(&htim3);
  //HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); //Запустить таймер енкодера

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of Timer_Try */
  Timer_TryHandle = osTimerNew(Callback01, osTimerPeriodic, NULL, &Timer_Try_attributes);

  /* creation of Timer_Boiler_Zero */
  Timer_Boiler_ZeroHandle = osTimerNew(Callback02, osTimerOnce, NULL, &Timer_Boiler_Zero_attributes);

  /* creation of myTimer_test */
  myTimer_testHandle = osTimerNew(Callback_test, osTimerOnce, NULL, &myTimer_test_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */

  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Queue1 */
  Queue1Handle = osMessageQueueNew (1, sizeof(Sens_a), &Queue1_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task_ADC */
  Task_ADCHandle = osThreadNew(StartTask_ADC, NULL, &Task_ADC_attributes);

  /* creation of Task_T_Screw */
  Task_T_ScrewHandle = osThreadNew(StartTask_T_Screw, NULL, &Task_T_Screw_attributes);

  /* creation of Task_Sens_Connt */
  Task_Sens_ConntHandle = osThreadNew(StartTask_Sens_Connect, NULL, &Task_Sens_Connt_attributes);

  /* creation of Task_Hopper_Cov */
  Task_Hopper_CovHandle = osThreadNew(StartTask_Hopper_Cover, NULL, &Task_Hopper_Cov_attributes);

  /* creation of Task_Current */
  Task_CurrentHandle = osThreadNew(StartTask_Current, NULL, &Task_Current_attributes);

  /* creation of Task_T_Boiler */
  Task_T_BoilerHandle = osThreadNew(StartTask_T_Boiler, NULL, &Task_T_Boiler_attributes);

  /* creation of Task_T_Gase */
  Task_T_GaseHandle = osThreadNew(StartTask_T_Gase, NULL, &Task_T_Gase_attributes);

  /* creation of Task_T_Waters */
  Task_T_WatersHandle = osThreadNew(StartTask_T_Waters, NULL, &Task_T_Waters_attributes);

  /* creation of Task_Manage */
  Task_ManageHandle = osThreadNew(StartTask_Manage, NULL, &Task_Manage_attributes);

  /* creation of Task_Menu */
  Task_MenuHandle = osThreadNew(StartTask_Menu, NULL, &Task_Menu_attributes);

  /* creation of Task_Button */
  Task_ButtonHandle = osThreadNew(StartTask_Button, NULL, &Task_Button_attributes);

  /* creation of Task_SMS */
  Task_SMSHandle = osThreadNew(StartTask_SMS, NULL, &Task_SMS_attributes);

  /* creation of Task_FanManage */
  Task_FanManageHandle = osThreadNew(StartTask_FanManage, NULL, &Task_FanManage_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 1;
  DateToUpdate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 63;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 9000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim4, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 5000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Relay2_Pin|Relay1_Pin|GPIO_PIN_12|U7_MOC3021M_Pin
                          |U6_MOC3021M_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : Thermostat_Pin */
  GPIO_InitStruct.Pin = Thermostat_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Thermostat_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay2_Pin Relay1_Pin PB12 U7_MOC3021M_Pin
                           U6_MOC3021M_Pin */
  GPIO_InitStruct.Pin = Relay2_Pin|Relay1_Pin|GPIO_PIN_12|U7_MOC3021M_Pin
                          |U6_MOC3021M_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Encoder_1_Pin Encoder_2_Pin */
  GPIO_InitStruct.Pin = Encoder_1_Pin|Encoder_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : U2_PC817_Pin */
  GPIO_InitStruct.Pin = U2_PC817_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(U2_PC817_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  //START_WORK_ALL_INTEFACES();
  for(;;)
  {
	//encode(); //енкодер
	//encode_turn();
	//encode_defense_noise();
	//encode();
//	    if (upState >= 3)
//	    {
//	      Encoder_Value+=1;
//	      upState = 0;
//	    }
//	    if (downState >= 3)
//	    {
//	      Encoder_Value-=1;
//	      downState = 0;
//	    }
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask_ADC */


/**
* @brief Function implementing the Task_ADC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_ADC */
void StartTask_ADC(void *argument)
{
  /* USER CODE BEGIN StartTask_ADC */
  /* Infinite loop */
  //uint8_t str[30];
  osStatus_t stat;
  osPriority_t priority;
  for(;;)
  {
	priority = osThreadGetPriority(Task_ADCHandle);
	//osThreadSetPriority(StartTask_ADC, priority+1); //повышаем приоритет Task'а который исполняется в данный момент
	//Sens_a.Temp_Boiler = 50; //Температура котла
	Average_Get_Value_mVolt(); //Снимаем показания с АЦП каналов


	//Тестовые данные для проверки работы потоков и ошибок
//	Sens_a.Temp_Boiler.value = 50; //Температура котла                                                                                                                                                                                                                                                             до
//	Sens_a.Current_LM321.value = 2000; //Ток с LM321
//	Sens_a.Temp_Screw.value = 80; //Температура шнека
//	Sens_a.Temp_Gase.value = 250; //Температура дымовых газов
//	Sens_a.Temp_Water.value = 50; //Температура ГВС
//	Sens_a.Temp_Street.value = 40; //Температура улица
//	Sens_a.Hopper_Cover.value = 0; //Крышка бункера
//	Sens_a.Thermostat.value = 0; //Термостат


//	sprintf(str, "1 ADC working!\n ");
//	HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));
	//printf("HELLO\n");

	//osMessageQueuePut(Queue1Handle, &Sens_a, 0, 200);
//	stat = osThreadGetState(Task_Hopper_CovHandle);
//	osThreadSuspend(Task_Hopper_CovHandle);
//	stat = osThreadGetState(Task_Hopper_CovHandle);

	//Enc_Counter = TIM3 -> CNT; //   енкодер

	//osThreadYield() //передаем управление след. потоку
    osDelay(20);


  }
  /* USER CODE END StartTask_ADC */
}

/* USER CODE BEGIN Header_StartTask_T_Screw */
/**
* @brief Function implementing the Task_T_Screw thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_T_Screw */
void StartTask_T_Screw(void *argument)
{
  /* USER CODE BEGIN StartTask_T_Screw */
  /* Infinite loop */
	//struct Sens_Analog Sens;
	//uint8_t str[30];
	for(;;)
	{
		//osMessageQueueGet(Queue1Handle, &Sens, 3, 100); //получаем данные из очереди с приоритетом 2
		//sprintf(str, "4 StartTask_T_Screw!\n ");
		//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

		Temp_Screw(Sens_a.Temp_Screw.value); //Проверяем на температуру шнек

	    osDelay(6);
	  }
  /* USER CODE END StartTask_T_Screw */
}

/* USER CODE BEGIN Header_StartTask_Sens_Connect */
/**
* @brief Function implementing the Task_Sens_Connt thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Sens_Connect */
void StartTask_Sens_Connect(void *argument)
{
  /* USER CODE BEGIN StartTask_Sens_Connect */
  /* Infinite loop */
  //struct Sens_Analog Sens;
  //uint8_t str[30];
  for(;;)
  {
	//osMessageQueueGet(Queue1Handle, &Sens, 0, 100); //получаем данные из очереди

	//sprintf(str, "2-1 Sens_Connect!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

	//Senn_Connect(0); //Если не подключен хотя бы один датчик, то остановить работу котла

	osDelay(9);
  }
  /* USER CODE END StartTask_Sens_Connect */
}

/* USER CODE BEGIN Header_StartTask_Hopper_Cover */
/**
* @brief Function implementing the Task_Hopper_Cov thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Hopper_Cover */
void StartTask_Hopper_Cover(void *argument)
{
  /* USER CODE BEGIN StartTask_Hopper_Cover */
  /* Infinite loop */
 // struct Sens_Analog Sens;
 // uint8_t str[30];
  for(;;)
  {
	//osMessageQueueGet(Queue1Handle, &Sens, 1, 100); //получаем данные из очереди
	//sprintf(str, "2-2 Hopper_Cover!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

	//если подключен, то проверяем
	//if(input.state_Hopper_Cover == 1)
	//Cover_open(Sens_a.Hopper_Cover.value);

    osDelay(8);
  }
  /* USER CODE END StartTask_Hopper_Cover */
}

/* USER CODE BEGIN Header_StartTask_Current */
/**
* @brief Function implementing the Task_Current thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Current */
void StartTask_Current(void *argument)
{
  /* USER CODE BEGIN StartTask_Current */
  /* Infinite loop */
  //struct Sens_Analog Sens;
 // uint8_t str[30];

  osTimerStart(Timer_TryHandle, Try_Time*60000); //Таймер который просто сбрасывает количество попыток реверса Try_count по истечению действия

  for(;;)
  {
	//osMessageQueueGet(Queue1Handle, &Sens, 2, 100); //получаем данные из очереди
	//sprintf(str, "3 Current!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

	//Current_Screw(input.Curr_user, Sens_a.Current_LM321.value);
    osDelay(7);
  }
  /* USER CODE END StartTask_Current */
}

/* USER CODE BEGIN Header_StartTask_T_Boiler */
/**
* @brief Function implementing the Task_T_Boiler thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_T_Boiler */
void StartTask_T_Boiler(void *argument)
{
  /* USER CODE BEGIN StartTask_T_Boiler */
  /* Infinite loop */
  //struct Sens_Analog Sens;
  //uint8_t str[15];
  osTimerStart(Timer_Boiler_ZeroHandle, input.time_boiler_zero*60000); //Таймер который по истечении начнет учет погас ли бойлер
  for(;;)
  {
	//osMessageQueueGet(Queue1Handle, &Sens, 4, 100); //получаем данные из очереди
	//sprintf(str, "5 T_Boiler!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));


	//Аварии: превышение температуры 90-95град и затухание 40<
	//Temp_Boiler(Sens_a.Temp_Boiler.value);

	if(flag_zero_boiler == 1){
		Boiler_Temp_Zero(input.Temp_Boiler_Zero_User, Sens_a.Temp_Boiler.value);}


	//если термостат подключенthermostat_onoff
	if(input.thermostat_onoff == 1){

		//если догрел до определенной температуры, то выключить  шнек и вентилятор
		if(Sens_a.Thermostat.value == flag_thermostat_type && flag_mode_support == 0){

			if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки

			flag_Screw_work = 0; //по сути выключаем шнек
			flag_pwm_fan = 0; //и вентилятор

		}

		//если не догрел, то дальше греем
		if(Sens_a.Thermostat.value != flag_thermostat_type && flag_mode_support == 0 ){

			if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки

			flag_Screw_work = 1; //по сути включаем шнек и вентилятор
			//flag_pwm_fan = 1; //и вентилятор
		}

		//если догрел до температуры и включен режим поддержания температуры, то
		if(Sens_a.Thermostat.value == flag_thermostat_type && flag_mode_support == 1 ){

			//if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки
			flag_Screw_work = 1;


		}

		//Если мы повысили температуру на термостате, то нужно снова в нагрев перейти
		if(Sens_a.Thermostat.value != flag_thermostat_type && flag_mode_support == 1 ){
			flag_mode_support = 0; //если включен режим поддержки

		}


//		//если догрел до температуры и включен режим поддержания температуры, то
//		if(Sens_a.Thermostat.value == flag_thermostat_type && Sens_a.Temp_Boiler.value < input.Temp_Central_Heating - input.Temp_Central_Heating_Hysteresis && flag_mode_support == 1 ){
//
//			if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки
//
//		}

		}	 else{ //если термостат не подключен

	//Если температура котла, достигла установленную пользователем плюс гистерезис, то дождаться падения температуры на 5град (величину гистерезиса минус) и продолжить работу котла или перейти в режим поддержания температуры(когда шнек и вентилятор работают иначе)
	if(Sens_a.Temp_Boiler.value  >= input.Temp_Central_Heating + input.Temp_Central_Heating_Hysteresis && flag_mode_support == 0 ){

		if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки

		flag_Screw_work = 0; //по сути выключаем шнек
		flag_pwm_fan = 0; //и вентилятор
	}

	//Если температура котла достигла нижней границы установленной пользователем (упала), то включить шнек и вентилятор
	if(Sens_a.Temp_Boiler.value < input.Temp_Central_Heating - input.Temp_Central_Heating_Hysteresis  && flag_mode_support == 0 ){

		if(flag_mode_support_onoff == 1) flag_mode_support = 1; //если включен режим поддержки

		flag_Screw_work = 1; //по сути включаем шнек и вентилятор
		//flag_pwm_fan = 1; //и вентилятор
	}

	//Если температура котла стала меньше на величину гистерезиса, то перейдем в режим поддержки
	if(Sens_a.Temp_Boiler.value < input.Temp_Central_Heating - input.Temp_Central_Heating_Hysteresis && flag_mode_support == 1){

		if(flag_mode_support_onoff == 1) flag_mode_support = 1;
		}
	}



    osDelay(5);
  }

  /* USER CODE END StartTask_T_Boiler */
}

/* USER CODE BEGIN Header_StartTask_T_Gase */
/**
* @brief Function implementing the Task_T_Gase thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_T_Gase */
void StartTask_T_Gase(void *argument)
{
  /* USER CODE BEGIN StartTask_T_Gase */
  /* Infinite loop */
  //struct Sens_Analog Sens;
  //uint8_t str[30];
  for(;;)
  {

	//osMessageQueueGet(Queue1Handle, &Sens, 5, 100); //получаем данные из очереди
	//sprintf(str, "6 T_Gase!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

	//если подключен
	if(input.state_Temp_Gase == 1)
	Temp_Gase(input.temp_gase_user, Sens_a.Temp_Gase.value);

	osDelay(4);
  }
  /* USER CODE END StartTask_T_Gase */
}

/* USER CODE BEGIN Header_StartTask_T_Waters */
/**
* @brief Function implementing the Task_T_Waters thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_T_Waters */
void StartTask_T_Waters(void *argument)
{
  /* USER CODE BEGIN StartTask_T_Waters */
  /* Infinite loop */
	//struct Sens_Analog Sens;
	//uint8_t str[30];
	for(;;)
	{
		//osMessageQueueGet(Queue1Handle, &Sens, 6, 100); //получаем данные из очереди
		//sprintf(str, "7 T_Waters!\n ");
		//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

		Temp_Сentral_Heating(Sens_a.Temp_Water.value);

	    osDelay(3);
	}
  /* USER CODE END StartTask_T_Waters */
}

/* USER CODE BEGIN Header_StartTask_Manage */
/**
* @brief Function implementing the Task_Manage thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Manage */
void StartTask_Manage(void *argument)
{
  /* USER CODE BEGIN StartTask_Manage */
  /* Infinite loop */



  //uint8_t str[10];

  for(;;)
  {
	//sprintf(str, "Manage!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

	if(flag_Screw_work == 1){

	//режим нагрева, постоянно подаем топливо
	if(flag_mode_support == 0 && flag_work == 1 && flag_hand_fire == 0){

		//flag_pwm_fan = 1;
		Screw_process_repeate(0, input.time_engine_work_mode_1, input.time_engine_not_work_mode_1, 1);


	}

	//режим поддержки, топливо и воздух подаются размерно по новым параметрам
	if(flag_mode_support == 1 && flag_work == 1 && flag_hand_fire == 0){

		//Blowdown(input.time_fan_work_mode_2, input.time_fan_not_work_mode_2); //Режим продува
		Screw_process_repeate(0, input.time_engine_work_mode_2, input.time_engine_not_work_mode_2, 1);

	}

	}


    osDelay(1);
  }
  /* USER CODE END StartTask_Manage */
}

/* USER CODE BEGIN Header_StartTask_Menu */
/**
* @brief Function implementing the Task_Menu thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Menu */
void StartTask_Menu(void *argument)
{
  /* USER CODE BEGIN StartTask_Menu */
  /* Infinite loop */
	//uint8_t str[10];
	osTimerStart(myTimer_testHandle, 1);
	//START_WORK_ALL_INTEFACES();
	//запускаем работу котла

	START_WORK_ALL_INTEFACES();
	flag_work = 1;
	for(;;){

		//sprintf(str, "Menu!\n ");
		//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));

		//Жестко заданные параметры по умолчанию, лишь некоторые можно редактировать - не подключено внутри кода
		if(1==0){
		input_hard.temp_sneak_default; // = 85 предельная температура на шнеке temp_sneak >= 85 (если так, то это возгорание шнека)

		input_hard.temp_fan_default; // = 90 предельная температура котла при которой отключается вентилятор

		input_hard.temp_central_heat; // = 40 температура при которой включается насос ЦО

		input_hard.Curr_default;//Ток двигателя при зажатой доске, установлмвается пользователем, диапазон токов 100-5000мА, по умолчанию 1600мА

		input_hard.Try_count_default; // Кол-во попыток реверса при аварии шнека, устанавливается пользователем от 2 до 7, по умолчанию 3
		input_hard.Fail_current_screw_count_default; //кол-во аварий шнека подряд (до Try_count), по умолчанию 0 (всегда ноль)
		input_hard.Try_Time_default; // Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается, диапазон 7-15м, по умолчанию 10

		//Должно отчасти определять input значения
		//input = {40, 15, 2000, 300, 80, 100,  5, 5,  1, 1,  10, 2,  0, 10,  1,  60, 1, 3, 0};
		}


		//Вкл-выкл датчики - в файле sens_and_all
		//Sens_a.Temp_Boiler.state = 0;


		//Редактировать параметры можно только в режиме стоп flag_work=0
		uint8_t flag_permit = 1;
		//if(flag_work == 0 && flag_permit == 1){
		if(flag_work == 1 && flag_permit == 1){
		//{40, 15, 2000, 300, 80, 100,  5, 5,  1, 1,  10, 2,  0, 10,  1,  60, 1, 3}


		flag_mode_support_onoff = 0; // включить режим поддеркжи (не путать с другим флагом)

		input.Temp_Boiler_Zero_User = 40; //температура котла при которой котел отключится (будет считаться погасшим)
		input.time_boiler_zero = 15; //время в минутах, которое дается на розжиг котла

		input.Curr_user = 2000; //Ток двигателя при зажатой доске, установливается пользователем, диапазон токов 100-5000мА

		input.temp_gase_user = 300; //температура дымовых газов 130-300 (не учитывается первые 15 минут работы котла)


		input.power_fan_rude = 40; //мощность грубая в процентах вентилятора (10-100)
		input.power_fan_perfect = 100; //мощность точная в процентах вентилятора (0-100)
		input.time_fan_work_mode_2 = 5; // Время работы вентилятора 0-200 с в режиме поддержки
		input.time_fan_not_work_mode_2 = 5; // Время не работы вентилятора 0-200 с в режиме поддержки

		input.time_engine_work_mode_1 = 5; // Время работы шнека 0-200 с в режиме нагрева
		input.time_engine_not_work_mode_1 = 5; //Время не работы шнека 0-200 с в режиме нагрева

		input.time_engine_work_mode_2 =5; // Время работы шнека 0-200 с в режиме поддержки
		input.time_engine_not_work_mode_2 = 5; //Время не работы шнека 0-200 с в режиме поддержки

		input.Try_count = 5; // Кол-во попыток реверса при аварии шнека, устанавливается пользователем от 2 до 7
		input.Fail_current_screw_count = 10; //кол-во аварий шнека подряд (до Try_count)
		input.Try_Time = 15; // Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается, диапазон 7-15м

		input.Temp_Central_Heating = 58; //температура ЦО от 45 до 85 - Здесь задаем температуру до которой котел должен греться
		input.Temp_Central_Heating_Hysteresis = 5; //гистерезис ЦО от 1 до 5

		input.Temp_Water = 60; //температура ГВС от 45 до 85 - Здесь задаем температуру до которой ГВС должен греться
		input.Temp_Water_Hysteresis = 5; //гистерезис определяет запаздывв ГВС от 1 до 5

		input.pump_mode = 0; //Параметр выбора режима по насосам 0-Только насос ЦО 1 - только насос ГВС 2-Насос и ГВС
		input.thermostat_onoff = 1; //Подключен ли термостат 0 - нет, 1 - да
		input.thermostat_type = 0; //Параметр выбора режима по термостату 0-нормально разомкнутый (при нагревании дает 0) 1 - нормально замкнутый (при нагревании дает 1)
		input.fan_mode = 0; //выбор типа вентилятора (у конкурентов только 1 тип)

		//подключены ли датчики
		input.state_Boiler = 1;
		input.state_Temp_Screw = 1;
		input.state_Temp_Gase = 0;
		input.state_Temp_Water = 0;
		input.state_Temp_Street = 0;
		input.state_Hopper_Cover = 1;

		}


		//Если датчики не подключены, то некоторые Task необходимо отправить в состояние Blocked
		//if(input.state_Hopper_Cover == 0) osThreadSuspend(Task_Hopper_CovHandle);
		//if(input.state_Hopper_Cover == 1) osThread(Task_Hopper_CovHandle);


		//Настройка термостата взависимости от введенных парамтеров
		if(input.thermostat_onoff == 1){
			//термостату 0-нормально разомкнутый
			if(input.thermostat_type == 0) flag_thermostat_type = 1;
			if(input.thermostat_type == 1) flag_thermostat_type = 0;
		}


		//Ручной режим
		uint8_t flag_work_hand = 0;
		uint8_t command_work_hand = 0;
		if(flag_work_hand == 1){


			flag_work = 0;

			switch(command_work_hand){

			case 1:
				Screw_direct(); //вкл прямой ход шнека
				break;
			case 2:
				Screw_reverse(); //вкл обратный ход шнека
				break;
			case 3:
				Relay_off(); //выключить шнек
				break;
			case 4:
				Pumps_Сentral_Heating(0); //вкл насос ЦО
				break;
			case 5:
				Pumps_Сentral_Heating(1); //выкл насос ЦО
				break;
			case 6:
				Pumps_Water_Supply(0); //вкл насос ГВС
				break;
			case 7:
				Pumps_Water_Supply(1); //выкл насос ГВС
				break;
			case 8:
				Set_PWM_ONOFF(1); //вкл вентилятор
				Set_PWM_ZC_T4C3_Percent_Power(100); //задать мощность вентилятора в процентах
				break;
			case 9:
				Set_PWM_ONOFF(0); //выкл вентилятор
				break;


			case 10:
				flag_hand_fire = 1;
				Hand_Fire(); //Вкл режим ручная топка - не сюда, но пусть пока тут будет
				break;
			case 11:
				flag_hand_fire = 0; //Выкл режим ручная топка - не сюда, но пусть пока тут будет
				break;
			}

		//STOP_WORK_ALL();
		}


		//код для тарировки бункера
		uint8_t flag_fill = 0;
		uint8_t command_fill = 0;
		uint8_t tim_perc = 0;
		if(flag_fill == 1){

			switch(command_fill){

				case 1:
					Time_Fl(); //бак полон
					break;
				case 2:
					Time_Emp(); //бак пуст
					Time_Fuel_Combustion(); //Вычисляем время сгорания топлива
					//записать в память время сгорания
					Time_Combustion=Time_Combustion-HAL_GetTick();
					tim_perc = Percent_Combustion(Time_Combustion); //в процентах получаем сколько топлива осталось
					break;

					}
			}


//		//запускаем работу котла
//		flag_work = 0;
//		START_WORK_ALL_INTEFACES();
//		if(flag_work == 1){
//		START_WORK_ALL_INTEFACES();}

//		UpdateButtonsStates();
//		UpdateScreen();

	    osDelay(7);
  }
  /* USER CODE END StartTask_Menu */
}

/* USER CODE BEGIN Header_StartTask_Button */




/**
* @brief Function implementing the Task_Button thread.
* @param argument: Not used
* @retval None
*/







uint8_t button(){

	uint32_t Time_button_start = HAL_GetTick();
	uint32_t Time_button_press = 0;



		//если кнопка нажата, то
		if(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == 0){

			//определим короткое нажатие в 0.5 сек
			while(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == 0 ) {

				Time_button_press+=HAL_GetTick() - Time_button_start;

				osDelay(20);
			}

	//		if(TIME_BUTTON_SHORT <= Time_button_press){
	//			long_clicking = 0;
	//			short_clicking = 1;
	//		}
			Time_button_press = Time_button_press/10;

			if(TIME_BUTTON_SHORT >= Time_button_press ){
				long_clicking = 0;
				short_clicking = 1;


				if(button_mail.mail_state == BUTTON_MAIL_PROCESSED) {

					button_mail.mail_state = BUTTON_MAIL_UPDATED;
					button_mail.button_type = BUTTON_CENTER;
					button_mail.button_state = BUTTON_SHORT_PUSHED;

				}

				return 1;
			}
			//osDelay(150);



			if(Time_button_press >= TIME_BUTTON_LONG && Time_button_press > TIME_BUTTON_SHORT){
				long_clicking = 1;
				short_clicking = 0;

				if(button_mail.mail_state == BUTTON_MAIL_PROCESSED) {

					button_mail.mail_state = BUTTON_MAIL_UPDATED;
					button_mail.button_type = BUTTON_CENTER;
					button_mail.button_state = BUTTON_LONG_PUSHED;
				}


				return 2;
			}



			if(button_mail.mail_state == BUTTON_MAIL_PROCESSED) {

				button_mail.mail_state = BUTTON_MAIL_UPDATED;
				button_mail.button_type = BUTTON_CENTER;
				button_mail.button_state = BUTTON_UP;
			}

			return 0;


		} else {
			long_clicking = 0;
			short_clicking = 0;

			if(button_mail.mail_state == BUTTON_MAIL_PROCESSED) {

				button_mail.mail_state = BUTTON_MAIL_UPDATED;
				button_mail.button_type = BUTTON_CENTER;
				button_mail.button_state = BUTTON_UP;
			}

			return 0;
		}




}
uint8_t PressF = 0;
/* USER CODE END Header_StartTask_Button */
void StartTask_Button(void *argument)
{
  /* USER CODE BEGIN StartTask_Button */
  /* Infinite loop */
  //uint8_t str[10];
  for(;;)
  {

	//sprintf(str, "Button!\n ");
	//HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));



	  PressF = button();



	  //osDelay(50);

//	if(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == 1){
//
//		//определим короткое нажатие в 0.5 сек
//		while(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == 1) { osDelay(50); }
//		long_clicking = 1;
//
//
//
//	} else {
//		long_clicking = 0;
//		short_clicking = 0;
//	}



    osDelay(10);
  }
  /* USER CODE END StartTask_Button */
}

/* USER CODE BEGIN Header_StartTask_SMS */



/* USER CODE END Header_StartTask_SMS */
void StartTask_SMS(void *argument)
{
  /* USER CODE BEGIN StartTask_SMS */
  /* Infinite loop */
  HAL_UART_Receive_IT(UART_SIM800, &rx_data, 1); //Запускаем прием по UART для SIM800
  //SIM800_Init(); //инициализация для сим800 - должна быть в таске, там нужна задержка
  SIM800_Init();

  uint8_t PowSignal = 0;
  for(;;)
  {

	  PowSignal = Sim800_Get_Signal(); //Получаем уровень сигнала
	  //uint8_t S = strstr("OK", "OK");

	  //SIM800_Init();
	  //sprintf(str, "Button!\n ");
	  //HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));
	  //HAL_UART_Receive_IT(&huart3, str, strlen((char *)str));

	  //sprintf(str, "Button!\n ");
	  //HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));
	  //answer = "AT\r\n\0"
	  //SIM800_SendCommand(answer, char *reply, CMD_DELAY);

    //HAL_Delay(1000);
    osDelay(15);
  }
  /* USER CODE END StartTask_SMS */
}

/* USER CODE BEGIN Header_StartTask_FanManage */
/**
* @brief Function implementing the Task_FanManage thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_FanManage */
void StartTask_FanManage(void *argument)
{
  /* USER CODE BEGIN StartTask_FanManage */
  /* Infinite loop */
  for(;;)
  {

		if(flag_Screw_work == 1){

		//режим нагрева, постоянно подаем топливо
		if(flag_mode_support == 0 && flag_work == 1 && flag_hand_fire == 0){

			flag_pwm_fan = 1;
			//Screw_process_repeate(0, input.time_engine_work_mode_1, input.time_engine_not_work_mode_1, 1);

		}

		//режим поддержки, топливо и воздух подаются размерно по новым параметрам
		if(flag_mode_support == 1 && flag_work == 1 && flag_hand_fire == 0){

			Blowdown(input.time_fan_work_mode_2, input.time_fan_not_work_mode_2); //Режим продува
			//Screw_process_repeate(0, input.time_engine_work_mode_2, input.time_engine_not_work_mode_2, 1);

		}

		}


    osDelay(15);
  }
  /* USER CODE END StartTask_FanManage */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */
  //По просшествии таймера Timer_Try, вызовится данный Callback

	Try_count = input.Try_count; //сбрасываем значения попыток

  /* USER CODE END Callback01 */
}

/* Callback02 function */
void Callback02(void *argument)
{
  /* USER CODE BEGIN Callback02 */
	flag_zero_boiler = 1; //начинаем учитывать, что котел может погаснуть
  /* USER CODE END Callback02 */
}

/* Callback_test function */
void Callback_test(void *argument)
{
  /* USER CODE BEGIN Callback_test */
//	Sens_a.Temp_Boiler.voltage = 3300;
//	Sens_a.Temp_Boiler.value = 50; //Температура котла
//	Sens_a.Temp_Boiler.state = input.state_Boiler;
//
//	Sens_a.Current_LM321.voltage = 1000;
//	Sens_a.Current_LM321.value = 2000; //Ток с LM321
//	Sens_a.Current_LM321.state = input.state_Temp_Screw;
//
//	Sens_a.Temp_Screw.voltage = 1000;
//	Sens_a.Temp_Screw.value = 80; //Температура шнека
//	Sens_a.Temp_Screw.state = input.state_Temp_Screw; //-
//
//	Sens_a.Temp_Gase.voltage = 1000;
//	Sens_a.Temp_Gase.value = 250; //Температура дымовых газов
//	Sens_a.Temp_Gase.state = input.state_Temp_Gase; //-
//
//	Sens_a.Temp_Water.voltage = 1000;
//	Sens_a.Temp_Water.value = 50; //Температура ГВС
//	Sens_a.Temp_Water.state = input.state_Temp_Water; //-
//
//	Sens_a.Temp_Street.voltage = 1000;
//	Sens_a.Temp_Street.value = 40; //Температура улица
//	Sens_a.Temp_Street.state = input.state_Temp_Street; //-
//
//	Sens_a.Hopper_Cover.voltage = 1000;
//	Sens_a.Hopper_Cover.value = 0; //Крышка бункера
//	Sens_a.Hopper_Cover.state = input.state_Hopper_Cover;
//
//	Sens_a.Thermostat.voltage = 1000;
//	Sens_a.Thermostat.value = 0; //Термостат
//	Sens_a.Thermostat.state = input.thermostat_onoff; //-
//
//
//
//	state_arr[0].state = Sens_a.Temp_Boiler.state;
//	state_arr[0].voltage = Sens_a.Temp_Boiler.voltage;
//
//	state_arr[1].state = Sens_a.Temp_Screw.state;
//	state_arr[1].voltage = Sens_a.Temp_Screw.voltage;
//
//	state_arr[2].state = Sens_a.Temp_Gase.state;
//	state_arr[2].voltage = Sens_a.Temp_Gase.voltage;
//
//	state_arr[3].state = Sens_a.Temp_Water.state;
//	state_arr[3].voltage = Sens_a.Temp_Water.voltage;
//
//	state_arr[4].state = Sens_a.Temp_Street.state;
//	state_arr[4].voltage = Sens_a.Temp_Street.voltage;
//
//	state_arr[5].state = Sens_a.Thermostat.state;
//	state_arr[5].voltage = Sens_a.Thermostat.voltage;

  /* USER CODE END Callback_test */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
//  if (htim->Instance == TIM2)
//  {
//	  encode(); //енкодер
//
////
////	  	NewState=Encoder_State;
////	  	if(NewState != OldState)
////	  	{
////	  	switch(OldState)
////	  		{
////	  		case 2:
////	  			{
////	  			if(NewState == 3) upState++;
////	  			if(NewState == 0) downState++;
////	  			break;
////	  			}
////
////	  		case 0:
////	  			{
////	  			if(NewState == 2) upState++;
////	  			if(NewState == 1) downState++;
////	  			break;
////	  			}
////	  		case 1:
////	  			{
////	  			if(NewState == 0) upState++;
////	  			if(NewState == 3) downState++;
////	  			break;
////	  			}
////	  		case 3:
////	  			{
////	  			if(NewState == 1) upState++;
////	  			if(NewState == 2) downState++;
////	  			break;
////	  			}
////	  		}
////	  	OldState=NewState;
////	  	}
//
////	  	NewState=(ENC_B() & 0b00011000)>>3;
////	  	if(!(ENC_B()&0b00000100)) cnt = 0;
////	  	switch(OldState | NewState)
////	  		{
////	  		case 0x01: case 0x0e:
////	  			cnt++;
////	  			break;
////	  		case 0: case 0x0b:
////	  			cnt--;
////	  			break;
////	  		}
////	  	OldState=NewState<<2;
//  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
