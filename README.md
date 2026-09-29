# STM32L432KC Clock Configuration Tutorial

Starter code for the E155 clock configuration activity. You will change the MCU's clock several different
ways and check each change using nothing but the on-board LED. No oscilloscope is needed.

This is a structured tutorial Git repository:

- `dev` is where you do your work. It starts with the same starter code as `main`.
- `solution` has a worked solution, with one commit per part of the worksheet. You can compare your work
  against it at any time (see [Tips](#tips)).

## The idea: the LED is a frequency meter

`src/main.c` toggles the on-board LED (PB3) after every `delay_ms(500)`. `delay_ms()` is provided. It uses
SysTick, a counter built into the Cortex-M4 that counts down by one every CPU clock cycle, and assumes one
millisecond is `HCLK_HZ/1000` cycles. `HCLK_HZ` is a `#define` at the top of `main.c`: the clock frequency
you *believe* the CPU is running at. So

    LED blink rate (Hz) = actual CPU clock (HCLK) / HCLK_HZ

If your clock configuration matches `HCLK_HZ`, the LED blinks at exactly 1 Hz, in step with the metronome
on the projector (or a phone metronome at 120 BPM: one click per toggle). If it gains on the metronome, the
real clock is faster than you think. If it falls behind, the real clock is slower.

## Getting started

1. Clone this repository and check out `dev`: `git checkout dev`.
2. Create a SEGGER Embedded Studio project for the STM32L432KC (see the
   [SEGGER Embedded Studio Setup tutorial](https://hmc-e155.github.io/tutorials/tutorial-posts/segger-embedded-studio-setup/)).
   Add `src/main.c` and the `.c` files in `lib/` to it, and add `lib/` to the project's user include directories.
3. Build and flash the unchanged starter code. The LED should blink at 1 Hz. This is Part 0.

## What you write

Fill in the `#define`s in `lib/STM32L432KC_RCC.h` as you go. Each one is the bit pattern that goes *into the
register field*, not the divide ratio. Then write these functions in `lib/STM32L432KC_RCC.c`:

| Part | Goal | Functions |
|---|---|---|
| 0 | Find the clock out of reset (MSI, 4 MHz) | none |
| 1 | Switch SYSCLK from MSI to HSI16 | `enableHSI16()`, `selectSysclk()` |
| 2 | Divide SYSCLK by 4 on the way to the CPU | `setAHBPrescaler()` |
| 3 | Run at 80 MHz from the PLL | `configurePLL(src, m, n, r)` |
| 4 | Run at 24 MHz from the PLL | none (reuse Part 3) |

`setFlashLatency()` in `lib/STM32L432KC_FLASH.c` is provided. You choose how many wait states to ask for.

The basic procedure for raising the clock speed is:

1. Raise the number of flash wait states for the new HCLK frequency. See RM0394 Ch. 3 for the table; 80 MHz
   needs 4 wait states.
2. Configure the PLL:
   * The input clock source
   * The dividers (M, R) and multiplier (N)
   * Enable the PLL's R output
3. Turn on the PLL and wait until it locks.
4. Switch the system clock to the PLL and wait until the hardware confirms the switch.

The STM32L432KC's maximum clock speed is 80 MHz. The PLL also has two internal limits: the VCO input
(source ÷ M) must be 4–16 MHz, and the VCO output (VCO input × N) must be 64–344 MHz.

# Tips

This tutorial is structured in Git so you can compare your work to the solution line by line with
`git diff`.

## Compare your current branch with the tip of another one

`git diff <current branch> <solution branch> <file to diff>`

For example, run the following to compare your RCC driver with the final solution:

`git diff dev solution lib/STM32L432KC_RCC.c`

## Compare your current branch with a commit in the revision history of another branch

You can refer to commits further back in a branch's history with a tilde. `solution~1` is one commit before
the tip of `solution`, `solution~2` is two commits before, and so on. The last three commits on `solution` are
Part 1, Part 2, and Part 3, in that order. So to check only your Part 1 work, run:

`git diff dev solution~2 lib/STM32L432KC_RCC.c`

That shows `enableHSI16()` and `selectSysclk()` filled in, with `setAHBPrescaler()` and `configurePLL()`
still empty.
