/*
 * LCD.c
 *
 * Created: 4/15/2012 5:55:17 PM
 *  Author: kevin
 */ 

#include "LCD.h"

void set_LCD_Data(int data) {
	int mask = 1;
	int i;
	int result = 0;
	for (i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA7);
			} else {
				gpio_clr_gpio_pin(LCD_DATA7);
			}
			break;
		case 1:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA6);
			} else {
				gpio_clr_gpio_pin(LCD_DATA6);
			}
			break;
		case 2:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA5);
			} else {
				gpio_clr_gpio_pin(LCD_DATA5);
			}
			break;
		case 3:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA4);
			} else {
				gpio_clr_gpio_pin(LCD_DATA4);
			}
			break;
		case 4:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA3);
			} else {
				gpio_clr_gpio_pin(LCD_DATA3);
			}
			break;
		case 5:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA2);
			} else {
				gpio_clr_gpio_pin(LCD_DATA2);
			}
			break;
		case 6:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA1);
			} else {
				gpio_clr_gpio_pin(LCD_DATA1);
			}
			break;
		case 7:
			result = mask & data;
			if (result == 1) {
				gpio_set_gpio_pin(LCD_DATA0);
			} else {
				gpio_clr_gpio_pin(LCD_DATA0);
			}
			break;
		}
		data = data >> 1;
	}
}


void set_LCD_data_in()
{
	gpio_configure_pin(LCD_DATA0, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA1, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA2, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA3, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA4, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA5, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA6, GPIO_DIR_INPUT);
	gpio_configure_pin(LCD_DATA7, GPIO_DIR_INPUT);
}

void set_LCD_data_out()
{
	gpio_configure_pin(LCD_DATA0, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA1, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA2, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA3, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA4, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA5, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA6, GPIO_DIR_OUTPUT);
	gpio_configure_pin(LCD_DATA7, GPIO_DIR_OUTPUT);
}

void get_LCD_Data() {
	int i = 0;
	data_reg = 0;


	for (i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			data_reg = gpio_get_pin_value(LCD_DATA0);
			break;
		case 1:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA1);
			break;
		case 2:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA2);
			break;
		case 3:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA3);
			break;
		case 4:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA4);
			break;
		case 5:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA5);
			break;
		case 6:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA6);
			break;
		case 7:
			data_reg = data_reg << 1;
			data_reg = data_reg | gpio_get_pin_value(LCD_DATA7);
			break;
		}

	}

}

/*LCD Functions*/
void LCD_Init() {
	gpio_set_gpio_pin(LCD_CS); //cs
	gpio_set_gpio_pin(LCD_RS); //rs
	gpio_set_gpio_pin(LCD_RD); //rd
	gpio_set_gpio_pin(LCD_WR); //wr
	gpio_set_gpio_pin(LCD_RST); //reset
}


void writeCommand(int cmd) {
	set_LCD_data_out();
	gpio_set_gpio_pin(LCD_RD); //rd high
	gpio_set_gpio_pin(LCD_WR); //wr high
	gpio_clr_gpio_pin(LCD_CS); //cs low
	set_LCD_Data(0x0);
	gpio_clr_gpio_pin(LCD_RS); //rs low
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
	set_LCD_Data(cmd);
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
	gpio_set_gpio_pin(LCD_RS); //rs high
}

void writeData(int data) {
	set_LCD_data_out();
	set_LCD_Data(data >> 8);
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
	set_LCD_Data(data);
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
	gpio_set_gpio_pin(LCD_CS); //cs high
}

void writeData_unsafe(int data) {
	set_LCD_data_out();
	set_LCD_Data(data >> 8);
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
	set_LCD_Data(data);
	gpio_clr_gpio_pin(LCD_WR); //wr low
	gpio_set_gpio_pin(LCD_WR); //wr high
}

void readData() {

	gpio_clr_gpio_pin(LCD_RD); //rd low
	cpu_delay_ms(1, 115200);
	set_LCD_data_in();
	get_LCD_Data();
	final_data = data_reg;
	gpio_set_gpio_pin(LCD_RD); //rd high
	gpio_clr_gpio_pin(LCD_RD); //rd low
	cpu_delay_ms(1, 115200);
	get_LCD_Data();
	final_data <<= 8;
	final_data |= data_reg;
	gpio_set_gpio_pin(LCD_RD); //rd high
	gpio_set_gpio_pin(LCD_CS); //cs high
}

void writeRegister(int addr, int data) {
	writeCommand(addr);
	writeData(data);
}

void readRegister(int addr) {
	writeCommand(addr);
	readData();
}

void goTo(int x, int y) {
	writeRegister(TFTLCD_GRAM_HOR_AD, x); // GRAM Address Set (Horizontal Address) (R20h)
	writeRegister(TFTLCD_GRAM_VER_AD, y); // GRAM Address Set (Vertical Address) (R21h)
	writeCommand(TFTLCD_RW_GRAM); // Write Data to GRAM (R22h)
}

void drawPixel(int x, int y, int color)
{
	writeRegister(TFTLCD_GRAM_HOR_AD, x);
	writeRegister(TFTLCD_GRAM_VER_AD, y);
	writeRegister(TFTLCD_RW_GRAM, color);
}

void fillScreen(int color) {
	goTo(0,0);
	int i;

	i = 320;
	i *= 240;

	gpio_clr_gpio_pin(LCD_CS); //cs low
	gpio_set_gpio_pin(LCD_RS); //rs high
	gpio_set_gpio_pin(LCD_RD); //rd high
	gpio_set_gpio_pin(LCD_WR); //wr high
	while (i--) {
		writeData_unsafe(color);
	}
	gpio_set_gpio_pin(LCD_CS); //cs high

}

void drawFastLine(int x, int y, int length, int color, int orientation)
{
	int entrymode;
	if (orientation == 0)
		entrymode = 0x1030;	//horizontal line
	else
		entrymode = 0x1028;	//vertical line
		
	writeRegister(TFTLCD_ENTRY_MOD, entrymode);
	
	writeRegister(TFTLCD_GRAM_HOR_AD, x);
	writeRegister(TFTLCD_GRAM_VER_AD, y);
	writeCommand(TFTLCD_RW_GRAM);
	
	gpio_set_gpio_pin(LCD_RS); //rs high
	gpio_set_gpio_pin(LCD_RD); //rd high
	gpio_set_gpio_pin(LCD_WR); //wr high
	
	while(length--)
	{
		writeData_unsafe(color);
	}
	
	gpio_set_gpio_pin(LCD_CS); //cs high
	writeRegister(TFTLCD_ENTRY_MOD, 0x1030);
	
}

void drawVertLine(int x, int y, int length, int color)
{
	drawFastLine(x, y, length, color, 1);
}

void drawHorzLine(int x, int y, int length, int color)
{
	drawFastLine(x, y, length, color, 0);
}

void fillRect(int x, int y, int w, int h, int color)
{
	while (h--)
	{
		drawHorzLine(x, y++, w, color);
	}
}

void drawChar(int x, int y, unsigned char c, int color, int bg, int size)
{
	int i, j;
	if ((x >= 240) || (y >= 320) || ((x + 5 * size - 1) < 0) || ((y + 8 * size - 1) < 0))
		return;
		
	for (i = 0; i < 6; i++)
	{
		int line;
		if (i == 5)
			line = 0x0;
		else
			line = glcdfont[(c*5) + i];
		for (j = 0; j < 8; j++)
		{
			if (line & 0x1)
			{
				if (size == 1)
					drawPixel((x+i), (y+j), color);
				else
					fillRect((x+(i*size)), (y+(j*size)), size, size, color);
			}
			else if (bg != color)
			{
				if (size == 1)
					drawPixel((x+i), (y+j), bg);
				else
					fillRect((x+(i*size)), (y+(j*size)), size, size, bg);
			}
			
			line >>= 1;
		}
	}	
}

void drawCharArray(int x, int y, char * text, int length)
{
	int i, xsofar, ysofar;
	
	xsofar = x;
	ysofar = y;
	for (i = 0; i < length; i++)
	{
		if (text[i] == '\n')
		{
			ysofar = ysofar + (8*text_size);
			xsofar = 0;
			continue;
		}
		if ((xsofar >= 240) || ((xsofar + ((6*text_size)-1)) > 240))
		{
			ysofar = ysofar + (8*text_size);
			xsofar = 0;
		}			
		drawChar(xsofar, ysofar, text[i], font_color, bg_color, text_size);
		xsofar = xsofar + (6*text_size); 
	}
}

void randomLetters()
{
	int x, y, character;
	
	while (1)
	{
		x = (rand() / (RAND_MAX / 240 + 1));
		y = (rand() / (RAND_MAX / 320 + 1));
		character = (rand() / (RAND_MAX / 127 + 1));
		
		drawChar(x, y, character, font_color, bg_color, text_size);
	}		
}

void setFontColor(int color)
{
	font_color = color;
}

void setBgColor(int color)
{
	bg_color = color;
}

void setFontSize(int size)
{
	text_size = size;
}

void LCD_Reset() {
	/*Reset sequence*/
	gpio_clr_gpio_pin(LCD_RST); //reset low
	cpu_delay_ms(50, 115200);
	gpio_set_gpio_pin(LCD_RST); //reset high
}

void initDisplay() {

	//LCD_Reset();
	
	cpu_delay_ms(100, 115200);
	
	readRegister(0x0);
	//set_LED_Data(final_data);

/*	writeRegister(0x00E3, 0x3008);
	writeRegister(0x00E7, 0x0012);
	writeRegister(0x00EF, 0x1231); */
	
	writeRegister(TFTLCD_START_OSC, 0x0001);//start oscillator

	cpu_delay_ms(50, 115200); //this will make a delay of 50 ms

	writeRegister(TFTLCD_DRIV_OUT_CTRL, 0x0100);
	writeRegister(TFTLCD_DRIV_WAV_CTRL, 0x0700);
	writeRegister(TFTLCD_ENTRY_MOD, 0x1030); //data=0x0030 works
	writeRegister(TFTLCD_RESIZE_CTRL, 0x0000);
	writeRegister(TFTLCD_DISP_CTRL2, 0x0202);
	writeRegister(TFTLCD_DISP_CTRL3, 0x0000);
	writeRegister(TFTLCD_DISP_CTRL4, 0x0000);//data = 0x0002?
	writeRegister(TFTLCD_RGB_DISP_IF_CTRL1, 0x0);
	writeRegister(TFTLCD_FRM_MARKER_POS, 0x0);
	writeRegister(TFTLCD_RGB_DISP_IF_CTRL2, 0x0);

	writeRegister(TFTLCD_POW_CTRL1, 0x0000);
	writeRegister(TFTLCD_POW_CTRL2, 0x0007);//data=0x0007?
	writeRegister(TFTLCD_POW_CTRL3, 0x0000);
	writeRegister(TFTLCD_POW_CTRL4, 0x0000);
	cpu_delay_ms(200, 115200);

	writeRegister(TFTLCD_POW_CTRL1, 0x1690);//data=0x14B0?
	writeRegister(TFTLCD_POW_CTRL2, 0x0227);//data=0x0227?
	cpu_delay_ms(50, 115200);

	writeRegister(TFTLCD_POW_CTRL3, 0x001A); //data=0x008E?
	cpu_delay_ms(50, 115200);

	writeRegister(TFTLCD_POW_CTRL4, 0x1800);//data=0x0C00?
	writeRegister(TFTLCD_POW_CTRL7, 0x002A);//data=0x0015?
	cpu_delay_ms(50, 115200);
	
	writeRegister(TFTLCD_GRAM_HOR_AD, 0x0000);
	writeRegister(TFTLCD_GRAM_VER_AD, 0x0000);

	writeRegister(TFTLCD_GAMMA_CTRL1, 0x0007);
	writeRegister(TFTLCD_GAMMA_CTRL2, 0x0605);
	writeRegister(TFTLCD_GAMMA_CTRL3, 0x0106);
	writeRegister(TFTLCD_GAMMA_CTRL4, 0x0206);
	writeRegister(TFTLCD_GAMMA_CTRL5, 0x0808);
	writeRegister(TFTLCD_GAMMA_CTRL6, 0x0007);
	writeRegister(TFTLCD_GAMMA_CTRL7, 0x0201);
	writeRegister(TFTLCD_GAMMA_CTRL8, 0x0007);
	writeRegister(TFTLCD_GAMMA_CTRL9, 0x0602);
	writeRegister(TFTLCD_GAMMA_CTRL10, 0x0808);

	writeRegister(TFTLCD_HOR_START_AD, 0x0000);
	writeRegister(TFTLCD_HOR_END_AD, 0x00EF);
	writeRegister(TFTLCD_VER_START_AD, 0x0000);
	writeRegister(TFTLCD_VER_END_AD, 0x013F);

	writeRegister(TFTLCD_GATE_SCAN_CTRL1, 0xA700); // Driver Output Control (R60h) data=0xA700?
	writeRegister(TFTLCD_GATE_SCAN_CTRL2, 0x0003); // data = 0x0001 works Driver Output Control (R61h) data = 0x0003?
	writeRegister(TFTLCD_GATE_SCAN_CTRL3, 0x0000); // Driver Output Control (R62h)

	/*writeRegister(0x80, 0x0);
	writeRegister(0x81, 0x0);
	writeRegister(0x82, 0x0);
	writeRegister(0x83, 0x0);
	writeRegister(0x84, 0x0);
	writeRegister(0x85, 0x0);*/

	writeRegister(TFTLCD_PANEL_IF_CTRL1, 0X0010); // Panel Interface Control 1 (R90h)
	writeRegister(TFTLCD_PANEL_IF_CTRL2, 0X0000);
	writeRegister(TFTLCD_PANEL_IF_CTRL3, 0X0003);
	writeRegister(TFTLCD_PANEL_IF_CTRL4, 0X1100); // data = 0x0110 works
	writeRegister(TFTLCD_PANEL_IF_CTRL5, 0X0000);
	writeRegister(TFTLCD_PANEL_IF_CTRL6, 0X0000);

	// Display On
	writeRegister(TFTLCD_DISP_CTRL1, 0X0133); // Display Control (R07h)

}