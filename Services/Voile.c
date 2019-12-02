#include "Voile.h"

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
void  SystemClock_Config(void);

//Configuration Timer
/**
	* @brief  Configure le Timer Indiqué
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4;
  * @retval None
  */
	void Config_TIM (TIM_TypeDef *TIMx) {
		
		if (TIMx==TIM1)		{
			//On active 
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
			//On configure 
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_OC_SetMode(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_PWM1);
	LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);
	TIM1->BDTR|=TIM_BDTR_MOE;
			
			
				//On configure ARR etPSC pour avoir le PWM voulu
	LL_TIM_SetAutoReload(TIM1,1799);
	LL_TIM_SetPrescaler(TIM1,799);

		}
		else if (TIMx==TIM3){
			//On active 
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
			//On configure 
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_SetClockSource(TIM3,LL_TIM_CLOCKSOURCE_EXT_MODE1);
	LL_TIM_SetEncoderMode(TIM3,LL_TIM_ENCODERMODE_X2_TI1);
	LL_TIM_SetAutoReload(TIM3,720);
	
			//Configuration du TIM3 en mode Encoder
	LL_TIM_ENCODER_InitTypeDef MyEncoder;

	MyEncoder.EncoderMode=LL_TIM_ENCODERMODE_X2_TI1;
	MyEncoder.IC1Polarity=LL_TIM_IC_POLARITY_RISING;
	MyEncoder.IC1ActiveInput=LL_TIM_ACTIVEINPUT_DIRECTTI;
	MyEncoder.IC1Prescaler=LL_TIM_ICPSC_DIV2;
	MyEncoder.IC1Filter=LL_TIM_IC_FILTER_FDIV1;
	MyEncoder.IC2Polarity=LL_TIM_IC_POLARITY_RISING;
	MyEncoder.IC2ActiveInput=LL_TIM_ACTIVEINPUT_DIRECTTI;
	MyEncoder.IC2Prescaler=LL_TIM_ICPSC_DIV2;
	MyEncoder.IC2Filter=LL_TIM_IC_FILTER_FDIV1;
	LL_TIM_ENCODER_Init(TIM3,&MyEncoder); //On veut un vecteur et pas la struct !
		}			
	}
//Fin Config Timer
// ---------------
	
	
/**
	* @brief  Configure le GPIO indiqué
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4; GPIO_TypeDef *GPIOx Selectionne le GPIO voulu, GPIOA GPIOB GPIOC
  * @retval None
  */
	void Config_GPIO(GPIO_TypeDef *GPIOx,TIM_TypeDef *TIMx){
				
	//On active le clock interne du GPIOA
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		if (GPIOx == GPIOA && TIMx==TIM1){
	
	//On configure le GPIOA
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
		}
	else if  (GPIOx == GPIOA && TIMx==TIM3){
		//Configuration GPIO
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_5,LL_GPIO_MODE_FLOATING );
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING );
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_7,LL_GPIO_MODE_FLOATING );	
  //Index
  LL_GPIO_InitTypeDef StructA5;
	StructA5.Mode=LL_GPIO_MODE_FLOATING;
	StructA5.Pin=LL_GPIO_PIN_5;
	StructA5.Speed=LL_GPIO_MODE_OUTPUT_10MHz;
	StructA5.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	StructA5.Pull=LL_GPIO_PULL_UP;	
	LL_GPIO_Init(GPIOA,&StructA5);
	//Channel A
	LL_GPIO_InitTypeDef StructA6;
	StructA6.Mode=LL_GPIO_MODE_FLOATING;
	StructA6.Pin=LL_GPIO_PIN_6;
	StructA6.Speed=LL_GPIO_MODE_OUTPUT_10MHz;
	StructA6.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	StructA6.Pull=LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOA,&StructA6);
	//Channel B
	LL_GPIO_InitTypeDef StructA7;
	StructA7.Mode=LL_GPIO_MODE_FLOATING;
	StructA7.Pin=LL_GPIO_PIN_7;
	StructA7.Speed=LL_GPIO_MODE_OUTPUT_10MHz;
	StructA7.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	StructA7.Pull=LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOA,&StructA7);
	}
}
	//Fin Config GPIO
// ----------------
	

/**
	* @brief  Configuration generale des voiles
  * @note   
	* @param  None
  * @retval None
  */
	void Config_voiles(){
		Config_TIM(TIM1);
		Config_GPIO(GPIOA,TIM1);
	}
//Fin Config Voiles
// ----------------
	
	
	/**
	* @brief  Configuration generale générale de la Girouette
  * @note   
	* @param  None
  * @retval None
  */
	void Config_girouette(){
		Config_TIM(TIM3);
		Config_GPIO(GPIOA,TIM3);
	}
//Fin Config Girouette
// -------------------
	
	
	/**
	* @brief  Fonction bloquante, tant que l'index n'est pas trouvé sur la Girouette
  * @note   
	* @param  None
  * @retval None
  */
	void Gestion_Index(){
	while (!(LL_GPIO_IsInputPinSet(GPIOA,LL_GPIO_PIN_5))) 
	{
		LL_TIM_SetCounter(TIM3,0);
	
	}
}
//Fin Gestion Index
// ----------------

//----------------------------
//Fin Partie 1 Configuration -
// ---------------------------



//----------------------------
// 2- Partie Fontions Utiles -
//----------------------------
	
/**
	* @brief  Prends l'information de l'angle sur la Girouette
  * @note   
	* @param  None
  * @retval Angle Girouette
  */
	int Angle_Girouette() {
		return(LL_TIM_GetCounter(TIM3)/2);	
	}
//Fin Angle Girouette
// ------------------
	
	
	/**
	* @brief  Calcule l'angle teta des voiles en fontion de l'angle de la Girouette
  * @note   
	* @param  Angle récupéré sur la girouette
  * @retval Angle des Voiles
  */	
	int Calcul_teta(int alpha){
				if ((alpha >=45) &&(alpha <= 180)){
			return ((-0.53*alpha)+114);
		}
		else if((alpha > 180) && (alpha <=315)){
			return ((0.53*alpha)-78);
	}
		else
		{
			return(90); //Voiles ferme
		}
	}
//Fin Calcul Teta
// --------------
	

	/**
	* @brief  Regle le Signal PWM pour avoir l'angle des Voiles voulu
  * @note   
	* @param  Angle des voiles souhaité
  * @retval None
  */
	void Set_Voile(int Angle_voulu){
		
		LL_TIM_OC_SetCompareCH1(TIM1,90 + Angle_voulu);
	}
	//Fin Set Voile
// --------------

	
	/**
	* @brief  Gere l'impact du Roulis sur le fonctionnement des voiles
  * @note   Si Roulis vrai alors les voiles sont laissés sans tension
	jusqu'a avoir le bateau de nouveau dans une position correcte
	* @param Roulis :excessif ou pas
  * @retval None
  */	
	void Run_Vent (int Roulis_exces){
		if (Roulis_exces == 0) {
		Set_Voile(Calcul_teta(Angle_Girouette()));
	}
		else if (Roulis_exces == 1) {
			Set_Voile(20);
		}
	}
//Fin Run Vent
// -----------
	
	
	/************************ (C) COPYRIGHT  *****END OF FILE****/
	
	

	
	