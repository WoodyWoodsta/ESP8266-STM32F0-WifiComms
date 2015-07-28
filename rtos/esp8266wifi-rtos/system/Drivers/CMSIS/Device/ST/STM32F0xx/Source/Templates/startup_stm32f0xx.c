/*
	This file contains the entry point (Reset_Handler) of your firmware project.
	The reset handled initializes the RAM and calls system library initializers as well as
	the platform-specific initializer and the main() function.
*/

extern void *_estack;

#define NULL ((void *)0)

void Reset_Handler();
void Default_Handler();

#define BootRAM ((void *)0xF108F85F)

void NMI_Handler()                    __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()              __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()                    __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()                 __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()                __attribute__ ((weak, alias ("Default_Handler")));
void WWDG_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void PVD_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void RCC_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void EXTI0_1_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void EXTI2_3_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void EXTI4_15_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void TS_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel2_3_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel4_5_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_COMP_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler() __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIM2_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM3_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void TIM7_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM14_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM15_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM16_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM17_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SPI2_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void USART3_4_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void CEC_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void USB_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));

void * g_pfnVectors[0x31] __attribute__ ((section (".isr_vector"))) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&SVC_Handler,
	NULL,
	NULL,
	&PendSV_Handler,
	&SysTick_Handler,
	&WWDG_IRQHandler,
	&PVD_IRQHandler,
	&RTC_IRQHandler,
	&FLASH_IRQHandler,
	&RCC_IRQHandler,
	&EXTI0_1_IRQHandler,
	&EXTI2_3_IRQHandler,
	&EXTI4_15_IRQHandler,
	&TS_IRQHandler,
	&DMA1_Channel1_IRQHandler,
	&DMA1_Channel2_3_IRQHandler,
	&DMA1_Channel4_5_IRQHandler,
	&ADC1_COMP_IRQHandler,
	&TIM1_BRK_UP_TRG_COM_IRQHandler,
	&TIM1_CC_IRQHandler,
	&TIM2_IRQHandler,
	&TIM3_IRQHandler,
	&TIM6_DAC_IRQHandler,
	&TIM7_IRQHandler,
	&TIM14_IRQHandler,
	&TIM15_IRQHandler,
	&TIM16_IRQHandler,
	&TIM17_IRQHandler,
	&I2C1_IRQHandler,
	&I2C2_IRQHandler,
	&SPI1_IRQHandler,
	&SPI2_IRQHandler,
	&USART1_IRQHandler,
	&USART2_IRQHandler,
	&USART3_4_IRQHandler,
	&CEC_IRQHandler,
	&USB_IRQHandler,
	BootRAM
};

void SystemInit();
void __libc_init_array();
void main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure 
	//asm ("ldr sp, =_estack");

	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	SystemInit();
	__libc_init_array();
	main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	//If we ended up here, an unexpected interrupt has happened (we did not defined the XXX_Handler function for it).
	//See the definition of g_pfnVectors above for interrupt handler names.
	for (;;) ;
}
