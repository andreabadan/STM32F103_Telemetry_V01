/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include <stdio.h>
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ToDeleate_Led_Pin GPIO_PIN_13
#define ToDeleate_Led_GPIO_Port GPIOC
#define Led_status_Pin GPIO_PIN_0
#define Led_status_GPIO_Port GPIOA
#define Track_Sensor_Pin GPIO_PIN_1
#define Track_Sensor_GPIO_Port GPIOA
#define Track_Sensor_EXTI_IRQn EXTI1_IRQn
#define Buzzer_Pin GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOA
#define RPM_Sensor_Pin GPIO_PIN_5
#define RPM_Sensor_GPIO_Port GPIOA
#define RPM_Sensor_EXTI_IRQn EXTI9_5_IRQn
#define H2O_NTC__Pin GPIO_PIN_7
#define H2O_NTC__GPIO_Port GPIOA
#define GPS_ONOFF_Pin GPIO_PIN_0
#define GPS_ONOFF_GPIO_Port GPIOB
#define GPS_PPS_Pin GPIO_PIN_1
#define GPS_PPS_GPIO_Port GPIOB
#define HOLD_Flash_Pin GPIO_PIN_2
#define HOLD_Flash_GPIO_Port GPIOB
#define WP_Flash_Pin GPIO_PIN_8
#define WP_Flash_GPIO_Port GPIOA
#define GPS_NRST_Pin GPIO_PIN_4
#define GPS_NRST_GPIO_Port GPIOB
#define IMU_Interrupt_Pin GPIO_PIN_9
#define IMU_Interrupt_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define VERISON "0.0.1B"
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
