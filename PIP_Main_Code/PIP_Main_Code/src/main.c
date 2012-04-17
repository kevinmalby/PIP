/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <stdio.h>
#include "gpio.h"
#include "LCD.h"
#include "sdramc.h"

int main (void)
{
	board_init();
	sysclk_init();
	
	int clock_speed;
	char msg[100];
	
	LCD_Reset();
	initDisplay();
	fillScreen(BLACK);
	clock_speed = sysclk_get_cpu_hz();
	sprintf(msg, "The clock speed is %d", clock_speed);
	drawCharArray(0, 0, msg, 77);
	
	unsigned long sdram_size, progress_inc, i, j, tmp, noErrors = 0;
	volatile unsigned long *sdram = SDRAM;
	
	// Calculate SDRAM size in words (32 bits).
	sdram_size = SDRAM_SIZE >> 2;

	// Initialize the external SDRAM chip.
	sdramc_init(sysclk_get_hsb_hz());
	
	progress_inc = (sdram_size + 50) / 100;

	  // Fill the SDRAM with the test pattern.
	  for (i = 0, j = 0; i < sdram_size; i++)
	  {
		if (i == j * progress_inc)
		{
		  gpio_tgl_gpio_pin(AVR32_PIN_PB21);
		}
		sdram[i] = i;
	  }
	  gpio_clr_gpio_pin(AVR32_PIN_PB21);

	  // Recover the test pattern from the SDRAM and verify it.
	  for (i = 0, j = 0; i < sdram_size; i++)
	  {
		if (i == j * progress_inc)
		{
		  gpio_tgl_gpio_pin(AVR32_PIN_PB22);
		}
		tmp = sdram[i];
		if (tmp != i)
		{
		  noErrors++;
		}
	  }
	  gpio_clr_gpio_pin(AVR32_PIN_PB22);
	  if (noErrors)
	  {
		gpio_clr_gpio_pin(AVR32_PIN_PB23);
		while (1)
		{
			
			/*fillScreen(RED);
			clock_speed = sysclk_get_cpu_hz();
			sprintf(msg, "The clock speed is %d", clock_speed);
			drawCharArray(0, 0, msg, 77);*/
		  gpio_tgl_gpio_pin(AVR32_PIN_PB23);
		  cpu_delay_ms(200, sysclk_get_cpu_hz());   // Fast blink means errors.
		}
	  }
	  else
	  {
		gpio_clr_gpio_pin(AVR32_PIN_PB30);
		while (1)
		{
			/*fillScreen(BLUE);
			clock_speed = sysclk_get_cpu_hz();
			sprintf(msg, "The clock speed is %d", clock_speed);
			drawCharArray(0, 0, msg, 77);*/
		  gpio_tgl_gpio_pin(AVR32_PIN_PB30);
		  cpu_delay_ms(1000, sysclk_get_cpu_hz());  // Slow blink means OK.
		}
	  }	
	// Insert application code here, after the board has been initialized.
}
