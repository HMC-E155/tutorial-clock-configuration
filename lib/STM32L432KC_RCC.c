// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

// Part 1
void enableHSI16(void) {
  RCC->CR |= (1 << 8);            // HSION: turn on the 16 MHz internal RC oscillator
  while (!((RCC->CR >> 10) & 1)); // Wait for HSIRDY: oscillator is stable
}

// Part 1
void selectSysclk(uint32_t sw) {
  // One read-modify-write so SW never passes through an intermediate value.
  // (Clearing first and then setting would briefly select MSI = 0b00.)
  RCC->CFGR = (RCC->CFGR & ~(0b11 << 0)) | (sw << 0);

  // SW is a request; SWS reports which source is actually driving SYSCLK
  while (((RCC->CFGR >> 2) & 0b11) != sw);
}

// Part 2
void setAHBPrescaler(uint32_t hpre) {
  // TODO: Write hpre into the HPRE field of RCC_CFGR, leaving the other bits alone

}

// Part 3
void configurePLL(uint32_t src, uint32_t m, uint32_t n, uint32_t r) {
  // PLLCLK = (src / M) * N / R
  // m, n, r are the actual divide/multiply ratios (e.g., r = 2 means divide by 2).
  // Convert each one to the bit pattern its field expects.

  // TODO: Turn off the PLL and wait until it has stopped

  // TODO: Set the PLL input clock source (PLLSRC)

  // TODO: Set M (PLLM)

  // TODO: Set N (PLLN)

  // TODO: Set R (PLLR)

  // TODO: Enable the PLL's R output (PLLREN)

  // TODO: Turn on the PLL and wait for it to lock

}
