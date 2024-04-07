/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "buzzer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  MC74HCT595A_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint8_t Rx_data[150] = {0};  //  creating a buffer of 10 bytes
  uint16_t frequnecy_usart[20]={0};
  uint16_t type_usart[20]={0};
  uint16_t bpm_usart[20]={0};
    uint8_t tones = 0;
    uint8_t commas = 0;
  bool start_read = false;
   buzzer_stop();
    uint16_t freq = 0;

    bool button_pressed = false;
    bool ricko_rool = false;
    while (1)
    {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if(freq>=10000)
        writeToRegisters(9999);
    else
        writeToRegisters(freq);
    if(!HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1)){
        if(freq<10000 && !button_pressed)
            freq+=100;
        button_pressed = true;
         buzzer_freq(freq);
	}else if(!HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_4)){
        if(freq>0 && !button_pressed)
            freq-=100;
		button_pressed = true;
         buzzer_freq(freq);
	}else if(!HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_1)){
		if(!button_pressed){
			if(!ricko_rool){
				 play_scale();
				 ricko_rool = true;
			}else{
				 play_rick_roll();
				 ricko_rool = false;
			}
		}
		 button_pressed = true;
	}else{
		buzzer_freq(0);
	}
    if(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1) && HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_4) && HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_1)){
        button_pressed = false;
    }

    HAL_UART_Receive (&huart2, Rx_data, 1, 10);  // receive 4 bytes of data
    if(Rx_data[0] == '$'){
    	HAL_UART_Receive (&huart2, Rx_data, 150, 500);
		if(Rx_data[0] == '&'){
			char *temp;
			temp = malloc(3*sizeof(char));
			int j = 0;
			for(size_t i = 1; i <100;i++){
				if(Rx_data[i] == '%'){
					free(temp);
					while(1){
						buzzer_freq(frequnecy_usart[0]);

					}
					break;
				}
				else if(Rx_data[i] == ','){
					j=0;
					commas++;
					switch (commas)
					{
					case 1:
						frequnecy_usart[tones] = atoi(temp);
						break;
					case 2:
						type_usart[tones] = atoi(temp);
						break;
					case 3:
						bpm_usart[tones] = atoi(temp);
						break;
					default:
						break;
					}
					free(temp);
					temp = malloc(3*sizeof(char));
				}else{
					temp[j++] = Rx_data[i];
				}
				if(commas == 3){
					commas = 0;
					tones++;
				}
			}
		}

    }
//    	HAL_UART_Transmit(&huart2,Rx_data,sizeof(Rx_data),10);// Sending in normal mode
   Rx_data[0] = 0;
//	HAL_Delay(1000);
//	  play_scale();
//	  play_rick_roll();

//	  HAL_Delay(100);
//	  buzzer_stop();
//	  HAL_Delay(100);

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
