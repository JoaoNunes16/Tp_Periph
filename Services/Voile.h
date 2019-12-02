
#ifndef VOILE_H
#define VOILE_H


// Proprietaires Programme -
//                         -
//AMOUR Chadi              - 
//BRAY Cameron             -
//BERTA Pauline            - 
//CONCEICAO NUNES Joao     -
//LE ROCH Victor           -
//TRUONG Luan              -
// -------------------------


#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Con#
#include "stm32f1xx_ll_gpio.h" 
#include "stm32f1xx_ll_bus.h"
#include "stdio.h"
#include "stm32f1xx_ll_tim.h"

//Variable utilisée pour stocker l'angle de la girouette
int Angle_Girouette(void);

//Fonction permetant de configurer TIM1 et TIM3 respectivement pour le PWM et pour la recuperation d'angle Girouette
void Config_TIM (TIM_TypeDef *TIMx) ;

//Configure les PIN du GPIO sur les modes necessaire pour la Giroutette, CHA CHB et Index
void Config_GPIO(GPIO_TypeDef *GPIOx,TIM_TypeDef *TIMx);

//Fonction de configuration generale de tout ce qui concerne la gestion des voiles. Utilise les deux fonctions precedentes
void Config_voiles(void);

//Fonction de configuration generale de tout ce qui concerne la gestion des voiles. Utilise les deux fonctions precedentes
void Config_girouette(void);

//Attends de recevoir le signal index de la girouette. Cette fonction est bloquante
void Gestion_Index(void);

//Permet de calculer la valeur teta de l'angle des voiles en fonction de l'angle donné par le Girouette	
int Calcul_teta(int alpha);


//Reajuste la valeur du PWM en accord avec l'angle des voiles voulu
void Set_Voile(int Angle_voulu);


//Fonction finale qui met en ouvre la gestion en temps reel des voiles et qui prends en argument le roulis. Trop de roulis-> Voiles relachées
void Run_Vent (int Roulis_exces);



#endif





	
	
	