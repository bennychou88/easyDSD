/*
	Hardware API for project openDSD. Glue code for your specific hardware.
	Initially designed for STM32F407VE.

	License: GPL 3.0
	Copyright (C) 2020 Lukas Neverauskis
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DSD_HWG_H_
#define DSD_HWG_H_

#include "stdio.h"
#include "main.h"

#define TH_STM32

#ifdef __cplusplus
extern "C" {
#endif

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

#ifdef __cplusplus
}
#endif

typedef bool boolean;

#define HIGH ((boolean)true)
#define LOW ((boolean)false)

/* prototypes of API functions here */

/* for accessing STM32cubeMx generated handlers */

extern I2S_HandleTypeDef hi2s2;
extern I2S_HandleTypeDef hi2s3;
extern DMA_HandleTypeDef hdma_spi2_tx;
extern DMA_HandleTypeDef hdma_spi3_tx;
extern RTC_HandleTypeDef hrtc;
extern SD_HandleTypeDef hsd;
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_tx;

//typedef std::string String;
typedef char const * String;
typedef char const * __FlashStringHelper;

typedef struct tft_pinout_stm32_{

	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}tft_pinout_stm32;

typedef enum tft_pinout_id_{

	TFT_PIN_CS,
	TFT_PIN_RESET,
	TFT_PIN_SDA,
	TFT_PIN_SCK,
	TFT_PIN_A0,

}tft_pinout_id;

/* Arduino workaround to work with AdafruitGFX */

class Print {
public:
	virtual size_t write(unsigned char c) = 0;
	void printDebug(char * const buffer, uint32_t size);
	void print(unsigned char c);
	void print(String str);
	void println(String str = "\0");
	void print(const float value);
	void println(const float value);
};

/* SPI workaround */


typedef enum dc_mode_{
	DC_DATA, DC_COMMAND
}dc_mode_e;

class SPI {

public:

	SPI() {}
	void begin() {};
	int8_t transfer(uint8_t* data, dc_mode_e dc, uint32_t size = 1);

	/* dummy code. todo: add functionality to it if ever needed... */

private:
	static bool _dmaBusy;
	static SPI_HandleTypeDef* _hspi;

	friend void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
};

extern SPI spi;

/* Arduino naming work-around */

#define pinMode(pin, mode)  /* todo: does nothing, for now its enough. */
#define millis() HAL_GetTick()
#define bitClear(byte, bit) byte &= ~(1 << bit)
#define bitSet(byte, bit) byte |= (1 << bit)
#define delay(ms) HAL_Delay(ms)

void digitalWrite(uint8_t pin, boolean state);
boolean digitalRead(uint8_t pin);

#endif  // DSD_HWG_H_