# MSP432-Systick-Timer-and-Interrupts
This code interfaces a 16x02 LCD display using timers and interrupts to display a stopwatch in ms : sec : min

This code implements the use of a stopwatch using a microcontroller. 

Header files: The code includes several header files that are required for using specific functions and features. These header files include stdio.h, string.h, lcdLib_432.h, stdlib.h, and msp.h.

Global variables: The code defines several global variables that are used to keep track of time and the state of the stopwatch. These variables include clk_to_ms, ms_count, sec_count, min_count, i, stopwatch_running, screen_saver_enabled, and name.

LCD initialization: The function LCDInit() initializes the LCD module and clears the screen.

SysTick initialization: The function initSysTick() initializes the SysTick timer, which is used to update the stopwatch counters every millisecond. It also sets the priority of the SysTick interrupt and enables the interrupt.

SysTick interrupt: The function SysTick_Handler() is the interrupt handler for the SysTick timer. It updates the stopwatch counters and updates the LCD display with the new stopwatch values.

Main function: The main function initializes the WDT (watchdog timer) and sets up the input pins for the buttons that control the stopwatch. It then initializes the LCD display and writes the title and initial stopwatch values to the screen. It then enters an infinite loop that checks the state of the buttons and updates the stopwatch accordingly. Finally, it calls the SysTick_Handler() function to update the stopwatch counters and the LCD display.

Button control: The while loop in the main function checks the state of the buttons connected to the microcontroller. If the start button is pressed, the stopwatch_running flag is set to 1. If the stop button is pressed, the stopwatch_running flag is set to 0. If the reset button is pressed, all the stopwatch counters are reset to 0 and the stopwatch_running flag is set to 0.
