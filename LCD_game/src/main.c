/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include <misc.h>
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"
//#include "stm32f4xx_spi.h"
			
static void TP_Config(void);
uint8_t mySPI_GetData(uint8_t adress);
void mySPI_SendData(uint8_t adress, uint8_t data);
void SPI5_Init();
void convertValue(uint8_t inValue, uint8_t inValue2);
void convert8Value(uint8_t inValue);

static volatile int8_t valueRead, valueRead2;
static volatile int16_t valueCombined;
static volatile char value [6];
static volatile int temp;

int count = 0;

int main(void)
{
	int8_t data;

	LCD_Init();
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
	LCD_SetLayer(LCD_FOREGROUND_LAYER);

	TP_Config();
	SPI5_Init();

	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
	mySPI_SendData(0x20, 0x0F);
	mySPI_SendData(0x20, 0x0F);

	while(1)
	{


		valueRead = mySPI_GetData(0x28);
		for (int j = 0;j<1000;j++);
		//valueRead = valueRead << 1;

		valueRead2 = mySPI_GetData(0x29);
		valueRead = valueRead << 1;
		valueRead2 = valueRead2 << 1;
		//valueRead2 = valueRead2 << 1;
		//valueCombined = valueRead | (valueRead2 << 8)  ;
		//valueCombined^= 0xC000;
		//valueCombined =~valueCombined;
		//temp = (int)valueRead;
		//valueCombined=~ valueCombined;
		convertValue(valueRead, valueRead2);
		LCD_DisplayStringLine(LCD_LINE_2,(uint8_t*)(value));
		valueCombined = NULL;

		//LCD_DrawFullCircle(temp, count, 1);
		valueRead = mySPI_GetData(0x2A);
		for (int j = 0;j<1000;j++);
		//valueRead = valueRead << 1;
		valueRead2 = mySPI_GetData(0x2B);
		valueRead = valueRead << 1;
		valueRead2 = valueRead2 << 1;
		//valueRead2 = valueRead2 << 1;
		//valueCombined = valueRead | (valueRead2 << 8);
		//valueCombined=~ valueCombined;
		//valueCombined =~valueCombined;
		//temp = (int)valueRead;
		convertValue(valueRead, valueRead2);
		LCD_DisplayStringLine(LCD_LINE_4,(uint8_t*)(value));
		valueCombined = NULL;


		valueRead = mySPI_GetData(0x2C);
		for (int j = 0;j<1000;j++);
		//valueRead = valueRead << 1;
		valueRead2 = mySPI_GetData(0x2D);
		valueRead = valueRead << 1;
		valueRead2 = valueRead2 << 1;
		//valueRead2 = valueRead2 << 1;
		//valueCombined = valueRead | (valueRead2 << 8);
		//valueCombined=~ valueCombined;
		//valueCombined =~valueCombined;
		//temp = (int)valueRead;
		convertValue(valueRead, valueRead2);
		LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)(value));
		valueCombined = NULL;



		valueRead = mySPI_GetData(0x0F);
		valueRead = valueRead << 1;
		convert8Value(valueRead);
		//valueRead = valueRead << 1;
		//valueCombined =~valueCombined;
		//temp = (int)valueRead;
		LCD_DisplayStringLine(LCD_LINE_10,(uint8_t*)(value));
		valueCombined = NULL;

		count++;

		/*if(count>305)
			{
				count = 0;
				//LCD_Clear(LCD_COLOR_WHITE);
			}*/

		//data = mySPI_GetData(0x29) + 48;
		//value[0] = mySPI_GetData(0x29) + 48;
		//value[1] = mySPI_GetData(0x29) + 48;
		//value[2] = 0;//mySPI_GetData(0x2B) + 48;
		//value[3] = 0;//mySPI_GetData(0x29) + 48;
		for (int j = 0;j<1000000;j++);

	}
}
void convert8Value(uint8_t inValue)
{
	int counter = 0;

	/*while(counter !=16)
	{
		value[counter] = '0';
		counter++;
	}*/

	//inValue = inValue << 1;
	//inValue -= 3;
	//inValue += 1;


	temp = (int)(inValue);




	  if (temp < 10000)
		  value [0] = '0';
	  else
		  value [0] = (char)(temp/10000) + 48;
	  if (temp < 1000)
		  value [1] = '0';
	  else
		  value [1] = (char)((temp/1000)%10) + 48;		//tysi¹ce mV
	if (temp < 100)
		value [2] = '0';
	else
		value [2] = (char)(((temp/100)%10)) + 48;		//setki mV
	if (temp < 10)
		value [3] = '0';
	else
		value [3] = (char)((temp%100)/10) + 48;
	if (temp == 0)
		value [4] = '0';
	else
		value [4] = (char)(temp%10) + 48;
	value[5] = NULL;
}



void convertValue(uint8_t inValue, uint8_t inValue2)
{
	int counter = 0;
	uint16_t valueCombined = 0x0000;
	/*while(counter !=16)
	{
		value[counter] = '0';
		counter++;
	}*/
	//inValue = inValue << 1;
	//inValue = inValue << 1;
	//inValue2 = inValue2 << 1;
	//inValue2 = inValue2 >> 1;

	//inValue = ~inValue;
	//inValue2 = ~inValue2;

	valueCombined = (uint16_t)inValue2;
	valueCombined = valueCombined << 8;
	valueCombined = valueCombined | (uint16_t)inValue;

	//valueCombined = ~valueCombined;

	temp = (int)(valueCombined);


	/*if(temp<0)
		value [0] = '-';
	else
		value [0] = '+';*/

		//if(temp > 65000) temp = temp-65000;
	  if (temp < 10000)
		  value [0] = '0';
	  else
		  value [0] = (char)(temp/10000) + 48;
	  if (temp < 1000)
		  value [1] = '0';
	  else
		  value [1] = (char)((temp/1000)%10) + 48;		//tysi¹ce mV
	if (temp < 100)
		value [2] = '0';
	else
		value [2] = (char)(((temp/100)%10)) + 48;		//setki mV
	if (temp < 10)
		value [3] = '0';
	else
		value [3] = (char)((temp%100)/10) + 48;
	if (temp == 0)
		value [4] = '0';
	else
		value [4] = (char)(temp%10) + 48;
	value[5] = NULL;

	/*while(temp != 0)
	{
		value[counter] = (temp % 2) + 48;
		temp = temp / 2;
		counter++;
	}
	value [16] = NULL;*/



}





void SPI5_Init()
{


	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5 , ENABLE);

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //SPI_BaudRatePrescaler_8;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; //| SPI_NSSInternalSoft_Set;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	//SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI5, &SPI_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//MISO, MOSI, SCK
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	//PC1 - 0 = SPI, 1 = I2C
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_SPI5);



	GPIO_SetBits(GPIOC, GPIO_Pin_1);

	SPI_Cmd(SPI5, ENABLE);
}

void mySPI_SendData(uint8_t adress, uint8_t data)
{

	GPIO_ResetBits(GPIOC, GPIO_Pin_1);

	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI5, adress);
	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI5);

	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI5, data);
	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI5);

	GPIO_SetBits(GPIOC, GPIO_Pin_1);
}

uint8_t mySPI_GetData(uint8_t adress)
{

	GPIO_ResetBits(GPIOC, GPIO_Pin_1);

	adress = 0x80 | adress;

	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI5, adress);
	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI5); //Clear RXNE bit

	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI5, 0x00); //Dummy byte to generate clock
	while(!SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE));


	GPIO_SetBits(GPIOC, GPIO_Pin_1);

	return  SPI_I2S_ReceiveData(SPI5);
}




static void TP_Config(void)
{

  LCD_Clear(LCD_COLOR_WHITE);


  if (IOE_Config() == IOE_OK)
  {
    LCD_SetFont(&Font8x8);

  }
  else
  {
    LCD_Clear(LCD_COLOR_RED);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)"   IOE NOT OK      ");
    LCD_DisplayStringLine(LCD_LINE_7,(uint8_t*)"Reset the board   ");
    LCD_DisplayStringLine(LCD_LINE_8,(uint8_t*)"and try again     ");
  }
}
