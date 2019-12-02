#include "plateau.h"

// Proprietaires Programme -
//                         -
//AMOUR Chadi              - 
//BRAY Cameron             -
//BERTA Pauline            - 
//CONCEICAO NUNES Joao     -
//LE ROCH Victor           -
//TRUONG Luan              -
// -------------------------

//Sommaire

// 1- Partie Configuration
// 2- Partie Fontions Utiles

//------------------------------------------------------------


//-------------------------
//1- Partie Configuration -
//-------------------------

/**
	* @brief  Configure le Timer Indiqué
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4; Arr et Psc sont des entiers.
  * @retval None
  */
void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc)
{
	LL_TIM_InitTypeDef My_LL_Tim_Init_Struct;
	
	// Validation horloge locale
	if (Timer==TIM1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	else if (Timer==TIM2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	else if (Timer==TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	else  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	// chargement structure Arr, Psc, Up Count
	My_LL_Tim_Init_Struct.Autoreload=Arr;
	My_LL_Tim_Init_Struct.Prescaler=Psc;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	
	LL_TIM_Init(Timer,&My_LL_Tim_Init_Struct);
	

	// Blocage IT
	LL_TIM_DisableIT_UPDATE(Timer);
	
	
	// Blocage Timer
	LL_TIM_DisableCounter(Timer);
	

		
}
//Fin Configuration Timer
// ----------------------


/**
	* @brief  Démarre le timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Start(TIM_TypeDef * Timer)
{
		LL_TIM_EnableCounter(Timer);
}
//Fin Start Timer
// --------------


/**
	* @brief  Arrêt le timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Stop(TIM_TypeDef * Timer)
{
	LL_TIM_DisableCounter(Timer);
}
//Fin Arret Timer
// --------------


/**
	* @brief  Recoit le signal PWM sur le CH1 du Timer 4
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void conf_capture_pwm_input (TIM_TypeDef * Timer) 
{
	// Configuration GPIOB
	//Enable Horloge pour GPIOB
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
	// Configuration de PB6, soit le pin 6 du GPIOB
		LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);
	
	// Config PWM timer 4, channel 1
	if (Timer == TIM4) {
	Timer -> CCMR1 |= TIM_CCMR1_CC1S_0 ; 
	Timer -> CCMR1 &= ~TIM_CCMR1_CC1S_1 ;
	
	Timer -> CCER &= ~TIM_CCER_CC1P_Msk ;

	Timer -> CCMR1 &= ~TIM_CCMR1_CC2S_0;
	Timer -> CCMR1 |= TIM_CCMR1_CC2S_1;

	Timer-> CCER |= TIM_CCER_CC2P_Msk ;
	
	Timer -> SMCR |= TIM_SMCR_TS_0 ;
	Timer -> SMCR &= ~TIM_SMCR_TS_1;
	Timer -> SMCR |= TIM_SMCR_TS_2 ;
		
	Timer -> SMCR &= ~TIM_SMCR_SMS_0 ;
	Timer -> SMCR &= ~TIM_SMCR_SMS_1 ;
	Timer -> SMCR |= TIM_SMCR_SMS_2 ;
		
	Timer -> CCER |= TIM_CCER_CC1E ;
	Timer -> CCER |= TIM_CCER_CC2E ;
	}
	
}
//Fin Configuration CH1
// --------------------


/**
	* @brief  Configure le Port A pour la reception du signal PWM sur le CH2
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void conf_commande_pwm_output ( TIM_TypeDef * Timer) 
{
	// Configuation GPIO A
	// Enable horloge GPIOA
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	
	
	
	// Paramétrage du pin 1 et du pin 2 
		LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT );
	
		LL_TIM_OC_SetMode(TIM2,LL_TIM_CHANNEL_CH2,LL_TIM_OCMODE_PWM1);
		LL_TIM_CC_EnableChannel(TIM2,LL_TIM_CHANNEL_CH2);
		
}
//Fin Configuration Port A
// -----------------------


/**
	* @brief  Fonction Generale de configuration de plateau
  * @note   
	* @param  None
  * @retval None
  */
void config_plateau(){
	MyTimer_Conf(TIM4,400, 3598);
	conf_capture_pwm_input(TIM4);
	MyTimer_Conf(TIM2,10, 359);
	conf_commande_pwm_output(TIM2);
	MyTimer_Start(TIM4);
	MyTimer_Start(TIM2);
	
}
//Fin Configuration Plateau
// ------------------------

//----------------------------
//Fin Partie 1 Configuration -
// ---------------------------



//----------------------------
// 2- Partie Fontions Utiles -
//----------------------------


/**
	* @brief  Commande la vitesse de rotation du moteur
  * @note   
  * @param  float vitesse_moteur_pourcentage : Vitesse voulue pour la rotation du plateau
  * @retval None
  */
void commander_vitesse_moteur(float vitesse_moteur_pourcentage) {
		
		float vitesse = (vitesse_moteur_pourcentage / 100.0) * 10.0 ;
		LL_TIM_OC_SetCompareCH2(TIM2,vitesse);
}
//Fin Commande vitesse moteur
// --------------------------


/**
	* @brief  Commande generale du plateau
  * @note   
  * @param  None
  * @retval None
  */
void commander_plateau(){
	
		float impulsion = TIM4->CCR2 ;
		
		float pourcentage = 0.0;
	
		if (impulsion < 30.0){
			
			pourcentage = ((30.0 - impulsion)/10.0) * 100.0;
			GPIOA->ODR |= GPIO_ODR_ODR2 ;
			commander_vitesse_moteur(pourcentage);
			
		}
		
		else if ( impulsion > 30.0){
			
			pourcentage = ((impulsion - 30.0 )/10.0) * 100.0;
			GPIOA->ODR &= ~GPIO_ODR_ODR2 ;
			commander_vitesse_moteur(pourcentage);
				
		}
		commander_vitesse_moteur(pourcentage);
							 				
	}
//Fin Commande Plateau
// --------------------------
	
	
//-------------------------------
//Fin Partie 2 Focntions Utiles -
// ------------------------------

	
/************************ (C) COPYRIGHT  *****END OF FILE****/
	
