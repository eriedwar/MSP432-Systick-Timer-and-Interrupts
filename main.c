#include <stdio.h>
#include <string.h>
#include "lcdLib_432.h"
#include <stdlib.h>
#include <msp.h>

volatile int clk_to_ms = 0;
volatile int ms_count = 0;  // Milliseconds counter
volatile int sec_count = 0; // Seconds counter
volatile int min_count = 0; // Minutes counter

void LCDInit()
{
    lcdInit();
    lcdClear();
}

int i;

volatile int stopwatch_running = 0; // Stopwatch running flag
volatile int screen_saver_enabled = 1; // Screen saver enabled flag
char name[] = "Eric"; // Your first name

void initSysTick(void){
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = 3000000 - 1; // Configure SysTick timer
    SysTick->VAL = 0x01;
    NVIC_SetPriority(SysTick_IRQn, 3); // Set SysTick interrupt priority to 3
    //SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Enable SysTick interrupt
}

void SysTick_Handler(void){
  char stopwatch_str[16];
  if (stopwatch_running) { // If stopwatch is running
    ms_count++; // Increment milliseconds counter
    // Update the stopwatch counters
    if (ms_count >= 145) { // If 1 second has elapsed
        ms_count = 0; // Reset milliseconds counter
        sec_count++; // Increment seconds counter
        if (sec_count >= 60) { // If 1 minute has elapsed
            sec_count = 0; // Reset seconds counter
            min_count++; // Increment minutes counter
       }
    }
    // Update the LCD display after 1 second has elapsed
    lcdSetText(stopwatch_str, 0, 1);
  }
  sprintf(stopwatch_str, "%02d:%02d:%02d", min_count, sec_count, ms_count/10);
}

int main(void){

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    P2->DIR &= ~(BIT5 | BIT6 | BIT7); // Set P5.0, P5.1, and P5.2 as inputs
    P2->REN |= BIT5 | BIT6 | BIT7;   // Enable pull-up/pull-down resistors
    P2->OUT &= ~(BIT5 | BIT6 | BIT7);   // Set pull-up resistors

    LCDInit(); // initialize the LCD module
    // Write a string to the first line of the LCD
    lcdSetText("Eric's Stopwatch", 0, 0);

//    // Write the initial stopwatch values to the LCD
    char stopwatch_str[16];
    sprintf(stopwatch_str, "%02d:%02d:%02d", min_count, sec_count, ms_count/10);
    lcdSetText(stopwatch_str, 0, 1);
    __enable_irq();

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    __DSB();

    while (1) {
        if(P2 -> IN & BIT5){
              stopwatch_running = 1;
              printf("whatever start\n");
          }
          else if(P2 -> IN & BIT6){
                stopwatch_running = 0;
                printf("whatever stop\n");
          }
          else if(P2 -> IN & BIT7){
                ms_count = 0;
                sec_count = 0;
                min_count = 0;
                stopwatch_running = 0;
                printf("whatever reset\n");

          }
        SysTick_Handler();
    }
}
