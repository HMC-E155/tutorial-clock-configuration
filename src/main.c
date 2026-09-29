// main.c
// Clock configuration activity: use the on-board LED as a clock meter
// Josh Brake
// jbrake@hmc.edu
// 9/29/26
//
// The LED toggles every delay_ms(500). delay_ms() times itself by counting CPU
// clock cycles with SysTick, assuming there are HCLK_HZ of them per second. If
// HCLK_HZ matches the real CPU clock, the LED blinks at exactly 1 Hz and stays in
// step with the metronome on the projector. In general:
//
//     LED blink rate (Hz) = (actual HCLK) / HCLK_HZ
//
// Work through the worksheet one part at a time. Before each flash, write down
// what you expect the LED to do.

#include <stdint.h>
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"

#define LED_PIN 3 // PB3: green user LED (LD3) on the Nucleo-L432KC

// What you *believe* the CPU clock (HCLK) is, in Hz. Update it in every part.
#define HCLK_HZ 4000000

///////////////////////////////////////////////////////////////////////////////
// Provided: delay using SysTick, a 24-bit down-counter built into every Cortex-M
// core. It counts down by 1 every CPU clock cycle. When it reaches 0 it sets
// COUNTFLAG and starts over from LOAD. See the SysTick timer (STK) section of PM0214.
// You do not need to change anything here.
///////////////////////////////////////////////////////////////////////////////

typedef struct {
  volatile uint32_t CTRL;  // 0x00 Control and status
  volatile uint32_t LOAD;  // 0x04 Value to count down from
  volatile uint32_t VAL;   // 0x08 Current count
  volatile uint32_t CALIB; // 0x0C Calibration (not used here)
} SYSTICK_TypeDef;

#define SYSTICK ((SYSTICK_TypeDef *) 0xE000E010UL)

void delay_ms(uint32_t ms) {
  SYSTICK->LOAD = HCLK_HZ / 1000 - 1;  // Count HCLK_HZ/1000 cycles per wrap: 1 ms, *if* HCLK_HZ is right
  SYSTICK->VAL  = 0;                   // Clear the count and COUNTFLAG; it reloads from LOAD next cycle
  SYSTICK->CTRL = (1 << 2) | (1 << 0); // CLKSOURCE = CPU clock, ENABLE

  for (uint32_t i = 0; i < ms; i++) {
    while (!((SYSTICK->CTRL >> 16) & 1)); // Wait for COUNTFLAG: set each time the count wraps
  }

  SYSTICK->CTRL = 0; // Stop counting
}

int main(void) {
  // Part 0: do nothing. What is SYSCLK at reset?

  // Part 1: switch SYSCLK from MSI to HSI16
  // enableHSI16();
  // selectSysclk(SW_HSI16);

  // Part 2: keep Part 1, then divide SYSCLK by 4 on the way to the CPU
  // setAHBPrescaler(HPRE_DIV4);

  // Part 3: 80 MHz from the PLL. Comment out Parts 1 and 2 first.
  // setFlashLatency(/* TODO */);
  // configurePLL(PLLSRC_MSI, /* M */, /* N */, /* R */);
  // selectSysclk(SW_PLL);

  // Turn on clock to GPIOB and set LED_PIN as output
  RCC->AHB2ENR |= (1 << 1);
  pinMode(LED_PIN, GPIO_OUTPUT);

  // Blink LED
  while (1) {
    delay_ms(500);
    togglePin(LED_PIN);
  }
  return 0;
}
