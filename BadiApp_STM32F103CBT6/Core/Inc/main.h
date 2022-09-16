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
/*!< Uncomment the following line if you need to send Bluetooth data via USB */
/* #define debugBT */
/*!< Uncomment the following line if you need to simulate RPM signal */
#define DebugRPM
#define VERISON "0.0.1B"

#define BUFFER_USB_LENGTH 100
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
