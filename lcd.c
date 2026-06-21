#include <LPC21xx.h>

#define LCDDATA 0x00FF0000    // LCD Data pins connected to P0.16-P0.23

#define RS (1<<8)             // Register Select pin
#define EN (1<<9)             // Enable pin

// Software delay function

void delay_ms(unsigned int ms)
{
    unsigned int i,j;

    for(i=0;i<ms;i++)
    {
        for(j=0;j<6000;j++);
    }
}

// Send command to LCD

void lcd_cmd(unsigned char cmd)
{
    IOCLR0 = LCDDATA;         // Clear previous data

    IOSET0 = (cmd<<16);       // Put command on data pins

    IOCLR0 = RS;              // RS=0 => Command Register

    IOSET0 = EN;              // Enable pulse

    delay_ms(2);

    IOCLR0 = EN;
}

// Send data/character to LCD

void lcd_data(unsigned char data)
{
    IOCLR0 = LCDDATA;         // Clear previous data

    IOSET0 = (data<<16);      // Put data on data pins

    IOSET0 = RS;              // RS=1 => Data Register

    IOSET0 = EN;              // Enable pulse

    delay_ms(2);

    IOCLR0 = EN;
}

// Display string on LCD

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

// Initialize LCD in 8-bit mode

void lcd_init(void)
{
    IODIR0 |= LCDDATA | RS | EN;   // Configure LCD pins as output

    delay_ms(20);

    lcd_cmd(0x38);                 // 8-bit, 2-line LCD

    lcd_cmd(0x0C);                 // Display ON, Cursor OFF

    lcd_cmd(0x06);                 // Auto increment cursor

    lcd_cmd(0x01);                 // Clear LCD
}

// Display integer number on LCD

void lcd_num(unsigned int num)
{
    char arr[5];

    int i=0;

    if(num==0)
    {
        lcd_data('0');

        return;
    }

    // Convert number into digits

    while(num)
    {
        arr[i++] = (num%10)+48;

        num = num/10;
    }

    // Display digits in correct order

    while(i)
    {
        lcd_data(arr[--i]);
    }
}