// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Hardware/FSMC.h"
#include "FPGA/Data.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Display/Display.h"
#include <stm32f4xx_hal.h>
#include "stm32f4xx_it.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NMI_Handler(void)
{
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void HardFault_Handler(void)
{
    bool val1 = enter1;
    bool val2 = enter2;
    
    DataSettings *ds = DS;
    
    bool run = true;
    while (run)
    {
        val1 = val1;
        val2 = val2;
        ds = ds;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void MemManage_Handler(void)
{
    bool run = true;
    while (run)
    {
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void BusFault_Handler(void)
{
    bool run = true;
    while (run)
    {
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void UsageFault_Handler(void)
{
    bool run = true;
    while (run)
    {
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void SVC_Handler(void)
{
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DebugMon_Handler(void)
{
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void PendSV_Handler(void)
{
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void SysTick_Handler(void)
{
    HAL_IncTick();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&handleADC);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// This interrupt call soft NSS for spi (see Hardware::SPIforPanel.c::
// PanelInit() and HAL_GPIO_EXTI_Callback())
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// See Hardware::SPIforPanel.c::HAL_SPI_RxCpltCallback()
void SPI1_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&handleSPI);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� ��� ������
void OTG_FS_IRQHandler(void)
{
    HAL_HCD_IRQHandler(&handleHCD);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DMA1_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(handleDAC.DMA_Handle1);
}
    

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DMA2_Stream0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&handleDMA_RAM);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������� ���������� ��� ������ ����� ���������� ����� � ������ ����������� ������ (Pin 116 - PD2)
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    extern uint16 adcValueFPGA;
    adcValueFPGA = (uint16)HAL_ADC_GetValue(hadc);
}
