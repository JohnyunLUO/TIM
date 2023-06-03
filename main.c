#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
//#include "LED color.h"

//LEC_config
void LED_config(){
	
	GPIO_PinConfigure(GPIOB, 0, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT10MHZ);  // 初始化 GPIOB,0號號腳位，上拉輸出，輸出10MHZ(LED green)
  GPIO_PinConfigure(GPIOB, 1, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT10MHZ);  // 初始化 GPIOB,1號號腳位，上拉輸出，輸出10MHZ(LED bule)
  GPIO_PinConfigure(GPIOB, 5, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT10MHZ);  // 初始化 GPIOB,5號號腳位，上拉輸出，輸出10MHZ(LED red)
	GPIO_PortWrite(GPIOB, 0x23, 0x23);
}
//TIM_config

void TIM_config(){
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=5;         /*!< Specifies the prescaler value used to divide the TIM clock.
																									This parameter can be a number between 0x0000 and 0xFFFF */
  //TIM_TimeBaseInitStruct.TIM_CounterMode;       /*!< Specifies the counter mode.
																									//This parameter can be a value of @ref TIM_Counter_Mode */

  TIM_TimeBaseInitStruct.TIM_Period=1000;            /*!< Specifies the period value to be loaded into the active
																									 Auto-Reload Register at the next update event.
																									 This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  //TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;     /*!< Specifies the clock division.
																									//This parameter can be a value of @ref TIM_Clock_Division_CKD */
	//TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
 //TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM6, ENABLE);
	
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}

//NVIC
void NVIC_config(){
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM6_IRQn;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type 
                                                   (For the complete STM32 Devices IRQ Channels list, please
                                                    refer to stm32f10x.h file) */

  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled. 
                                                   This parameter can be set either to ENABLE or DISABLE */ 
	
	NVIC_Init(&NVIC_InitStruct);
}
int i=0;
int color=0;
//int kkk=0;
//RCC_ClocksTypeDef ttt;
int main(void)
{
	/*while(kkk==0){
	}*/
  LED_config();
	TIM_config();
	NVIC_config();
	
	
	//RCC_GetClocksFreq(&ttt);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	while(1){
		if((color%2)==0){
		GPIO_PortWrite(GPIOB, 0x23, 0x23);
		}
		else{
			GPIO_PortWrite(GPIOB, 0x23, 0);
		}
		if(i==1000){
			i=0;
			color++;
		}
	}
		
	return 0;
}

  
void TIM6_IRQHandler(void) // 將中斷處理函數修改為 EXTI15_10_IRQHandler( 在startup_stm32f10x_hd.s 自動執行)
{
  // 確認是PC 13引腳的中斷
  if(TIM_GetITStatus(TIM6,TIM_IT_Update)) // 將 EXTI_Line0 修改為 EXTI_Line13
  {
    //中斷處理程式
    //在這裡添加你的程式碼以處理按鈕中斷
		
		
    i++;

    // 清除中斷標誌
    TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
  }
}

void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/
