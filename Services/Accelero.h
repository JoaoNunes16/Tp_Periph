

#ifndef CHRONO_H
#define CHRONO_H



// Proprietaires Programme -
//                         -
//AMOUR Chadi              - 
//BRAY Cameron             -
//BERTA Pauline            - 
//CONCEICAO NUNES Joao     -
//LE ROCH Victor           -
//TRUONG Luan              -
// -------------------------

/*
Service permettant de chornom�trer jusqu'� 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 � TIMER4).
Utilise la lib MyTimers.h /.c
*/

#include "stm32f103xb.h" 
#include <math.h>
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"

/* =====================================================================================
Les fonctions qui g�rent les IO (ajout par rapport � l'activit� 1)
=======================================================================================*/
typedef struct any init_adc_regular;

struct any {
		uint32_t TRIG ;
		uint32_t SCAN;
		uint32_t DISCONT;
		uint32_t CONT;
		uint32_t DMA;
	};
void adc_gpio_conf(void);
void uart_conf(void);
void UART_Send(USART_TypeDef *,int);
void sendAlerte(void);
	
void start_adc(void);
	
void gpio_conf(void);
	
float read_adc_angle(void);
int sup45(float);
int inf35(float);
int isFucked(int, float);
float lvlBatt(void);
int isBattLow(float);
	
#endif
