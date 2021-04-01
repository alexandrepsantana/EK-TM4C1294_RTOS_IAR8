#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

typedef struct {
  uint8_t   ledNumber;
  uint32_t  duration;
} threadArg_t;

osThreadId_t thread1, thread2, thread3, thread4;

void thread(void *arg){
  threadArg_t* threadArg = (threadArg_t*)arg;
  uint8_t state = 0;
  
  while(1){
    state ^= threadArg->ledNumber;
    LEDWrite(threadArg->ledNumber, state);
    osDelay(threadArg->duration);
  } // while
} // thread1

//
//void thread2(void *arg){
//  uint8_t state = 0;
//  uint32_t tick;
//  
//  while(1){
//    tick = osKernelGetTickCount();
//    
//    state ^= LED2;
//    LEDWrite(LED2, state);
//    
//    osDelayUntil(tick + 100);
//  } // while
//} // thread2

void main(void){
  threadArg_t argLed1;
  argLed1.duration = 200;
  argLed1.ledNumber = LED1;
  
  threadArg_t argLed2;
  argLed2.duration = 300;
  argLed2.ledNumber = LED2;
  
  threadArg_t argLed3;
  argLed3.duration = 500;
  argLed3.ledNumber = LED3;
  
  threadArg_t argLed4;
  argLed4.duration = 700;
  argLed4.ledNumber = LED4;
  
  LEDInit(LED4 | LED3 | LED2 | LED1);

  osKernelInitialize();

  thread1 = osThreadNew(thread, (void*)&argLed1, NULL);
  thread2 = osThreadNew(thread, (void*)&argLed2, NULL);
  thread3 = osThreadNew(thread, (void*)&argLed3, NULL);
  thread4 = osThreadNew(thread, (void*)&argLed4, NULL);
//  thread2_id = osThreadNew(thread2, NULL, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
