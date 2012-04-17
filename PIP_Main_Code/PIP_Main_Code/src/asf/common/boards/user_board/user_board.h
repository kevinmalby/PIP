/**
 * \file
 *
 * \brief User board definition template
 *
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

/* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */

#define FOSC32          32768                                 //!< Osc32 frequency: Hz.
#define OSC32_STARTUP   AVR32_PM_OSCCTRL32_STARTUP_8192_RCOSC //!< Osc32 startup time: RCOsc periods.

#define FOSC0           12000000                              //!< Osc0 frequency: Hz.
#define OSC0_STARTUP    AVR32_PM_OSCCTRL0_STARTUP_2048_RCOSC  //!< Osc0 startup time: RCOsc periods.

#define BOARD_OSC0_HZ           12000000
#define BOARD_OSC0_STARTUP_US   17000
#define BOARD_OSC0_IS_XTAL      true

//Define all of the LED Pins
#define LED1	AVR32_PIN_PB21
#define LED2	AVR32_PIN_PB22
#define LED3	AVR32_PIN_PB23
#define LED4	AVR32_PIN_PB30
#define LED5	AVR32_PIN_PB24
#define LED6	AVR32_PIN_PB25
#define LED7	AVR32_PIN_PB26
#define LED8	AVR32_PIN_PB27
#define LED9	AVR32_PIN_PB28
#define LED10	AVR32_PIN_PB29
#define LED11	AVR32_PIN_PB31
#define LED12	AVR32_PIN_PA00

//Define all of the LCD Pins
#define LCD_DATA0	AVR32_PIN_PB02
#define LCD_DATA1	AVR32_PIN_PB03
#define LCD_DATA2	AVR32_PIN_PB04
#define LCD_DATA3	AVR32_PIN_PB05
#define LCD_DATA4	AVR32_PIN_PB06
#define LCD_DATA5	AVR32_PIN_PB07
#define LCD_DATA6	AVR32_PIN_PB08
#define LCD_DATA7	AVR32_PIN_PB09

#define LCD_CS		AVR32_PIN_PX22
#define LCD_RS		AVR32_PIN_PB01
#define LCD_RD		AVR32_PIN_PA28
#define LCD_WR		AVR32_PIN_PB00
#define LCD_RST		AVR32_PIN_PA29

//! Part header file of used SDRAM(s).
#define SDRAM_PART_HDR  "mt48lc16m16a2tg7e/mt48lc16m16a2tg7e.h"

//! Data bus width to use the SDRAM(s) with (16 or 32 bits; always 16 bits on
//! UC3).
#define SDRAM_DBW       16
#endif // USER_BOARD_H
