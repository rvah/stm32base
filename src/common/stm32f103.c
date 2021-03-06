#include "common/stm32f103.h"

void stm32_clock_init() {
	/* CFGR must be setup before setting CR register */
	RCC_CFGR = RCC_CFGR_PLL_MUL_9 | RCC_CFGR_PLL_USE_HSE | RCC_CFGR_PCLK2_DIV_6
			| RCC_CFGR_PCLK1_DIV_2 | RCC_CFGR_SYSCLK_USE_PLL;

	RCC_CR = RCC_RC_HSI_ENABLE | RCC_RC_PLL_ENABLE | RCC_RC_HSE_ENABLE
			| RCC_RC_HSI_TRIM_16;

	/* wait for clocks to become ready */

	while(!(RCC_CR & RCC_RC_HSE_READY)) ;
	while(!(RCC_CR & RCC_RC_PLL_READY)) ;
	while(!(RCC_CR & RCC_RC_HSI_READY)) ;

	while(((RCC_CFGR & RCC_CFGR_M_SWS) >> 2) != (RCC_CFGR & RCC_CFGR_M_SW)) ;
}

void stm32_gpio_init() {
	/* enable port A */
	RCC_APB2ENR |= RCC_IOPAEN;

	/* enable port B */
	RCC_APB2ENR |= RCC_IOPBEN;

	GPIOA_CRL = 0x12112228;

	GPIOB_CRL &= 0x00FFFFFF;
	GPIOB_CRL |= 0xff000000;
}
