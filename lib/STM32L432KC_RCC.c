// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

// Part 1
void enableHSI16(void) {
  // TODO: Turn on the HSI16 oscillator

  // TODO: Wait until the hardware reports that HSI16 is ready (stable)

}

// Part 1
void selectSysclk(uint32_t sw) {
  // TODO: Write sw into the SW field of RCC_CFGR, leaving the other bits alone

  // TODO: Wait until SWS reports that the switch has actually happened

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
