#ifndef PLATEAU_H
#define PLATEAU_H


// Proprietaires Programme -
//                         -
//AMOUR Chadi              - 
//BRAY Cameron             -
//BERTA Pauline            - 
//CONCEICAO NUNES Joao     -
//LE ROCH Victor           -
//TRUONG Luan              -
// -------------------------


#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h" 
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges

void config_plateau(void);
void commander_vitesse_moteur(float vitesse_moteur_pourcentage);
void commander_plateau(void);
void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc);
void MyTimer_Start(TIM_TypeDef * Timer);//Vraiment Utile??
void MyTimer_Stop(TIM_TypeDef * Timer);//Vraiment Utile??
void conf_capture_pwm_input (TIM_TypeDef * Timer);
void MyTimer_Stop(TIM_TypeDef * Timer); //Vraiment Utile??


	




















#endif
