#include <LPC21xx.h>

void lcd_init(void);

void lcd_cmd(unsigned char);
void lcd_string(char *);
void lcd_data(unsigned char);
void delay_ms(unsigned int);

void keypad_init(void);
char keypad_scan(void);

void rtc_init(void);
void rtc_display(void);

void adc_init(void);
unsigned int adc_read(void);

void led_init(void);
void led_on(void);
void led_off(void);

char key;
char temp[3];
unsigned int ldr;

// Wait until the currently pressed key is releasedvoid wait_release(void){delay_ms(1);

void wait_release(void){
  delay_ms(1);
  while(keypad_scan() != 0);// Wait for key release
  delay_ms(1);
 }

// Backspace function for LCD 

void lcd_backspace(void){
  lcd_cmd(0x10); // Move cursor one position left
  lcd_data(' '); // Erase character
  lcd_cmd(0x10);  // Move cursor back to deleted position
}

  void get_2digit_value(unsigned int *value)
	{
		unsigned char i=0;
    while(1)
    {
     key = keypad_scan();
     // Accept numeric keys only

    if((key >= '0') && (key <= '9'))
    {
        // Store maximum 2 digits

        if(i < 2)
        {
            temp[i] = key;
            lcd_data(key);
            i++;
            wait_release();
        }
    }

    // Delete previously entered digit
    else if(key == '*')
    {
        if(i > 0)
        {
            i--;
            lcd_backspace();
            wait_release();
        }
    }

    // Confirm input after entering 2 digits
    else if(key == '#')
    {
        if(i == 2)
        {
            wait_release();
            break;
        }
    }
}

// Convert ASCII digits to integer value
*value = ((temp[0]-48)*10) + (temp[1]-48);
 }

// Edit RTC Hour
void edit_hour(void){	
unsigned int value;
while(1)
{
    lcd_cmd(0x01);
    lcd_string("ENTER HOUR:");
    lcd_cmd(0xC0);

    // Read 2-digit hour value from keypad
    get_2digit_value(&value);

    // Validate hour (00-23)
    if(value <= 23)
    {
        HOUR = value;
        break;
    }

    // Display error message for invalid hour
    lcd_cmd(0x01);
    lcd_string("INVALID HOUR");
    delay_ms(30);
}

// Hour updated successfully

lcd_cmd(0x01);

lcd_string("HOUR UPDATED");

delay_ms(30);

}

// Edit RTC Minute

void edit_min(void){
	unsigned int value;

  while(1)
  {
    lcd_cmd(0x01);

    lcd_string("ENTER MIN:");

    lcd_cmd(0xC0);

    // Read 2-digit minute value from keypad

    get_2digit_value(&value);

    // Validate minute (00-59)

    if(value <= 59)
    {
        MIN = value;

        break;
    }

    // Display error message for invalid minute

    lcd_cmd(0x01);

    lcd_string("INVALID MIN");

    delay_ms(30);
}

// Minute updated successfully

lcd_cmd(0x01);

lcd_string("MIN UPDATED");

delay_ms(30);

}

// Edit RTC Second

void edit_sec(void){unsigned int value;

while(1)
{
    lcd_cmd(0x01);

    lcd_string("ENTER SEC:");

    lcd_cmd(0xC0);

    // Read 2-digit second value from keypad
    get_2digit_value(&value);

    // Validate second (00-59)
    if(value <= 59)
    {
        SEC = value;
        break;
    }

    // Display error message for invalid second
    lcd_cmd(0x01);
    lcd_string("INVALID SEC");
    delay_ms(30);
}

// Second updated successfully
lcd_cmd(0x01);
lcd_string("SEC UPDATED");
delay_ms(30);

}

// Edit RTC Date
void edit_date(void){unsigned int value;

while(1)
{
    lcd_cmd(0x01);
    lcd_string("ENTER DATE:");
    lcd_cmd(0xC0);

    // Read 2-digit date value from keypad
    get_2digit_value(&value);

    // Validate date (01-31)
    if((value >= 1) && (value <= 31))
    {
        DOM = value;
        break;
    }

    // Display error message for invalid date
    lcd_cmd(0x01);
    lcd_string("INVALID DATE");
    delay_ms(30);
}

// Date updated successfully
lcd_cmd(0x01);
lcd_string("DATE UPDATED");
delay_ms(30);
}

// Edit RTC Month
void edit_month(void){unsigned int value;

while(1)
{
    lcd_cmd(0x01);
    lcd_string("ENTER MONTH:");
    lcd_cmd(0xC0);

    // Read 2-digit month value from keypad
    get_2digit_value(&value);

    // Validate month (01-12)
    if((value >= 1) && (value <= 12))
    {
        MONTH = value;
        break;
    }

    // Display error message for invalid month
    lcd_cmd(0x01);
    lcd_string("INVALID MON");
    delay_ms(30);
}

// Month updated successfully
lcd_cmd(0x01);
lcd_string("MON UPDATED");
delay_ms(30);

}
// Edit RTC Year
void edit_year(void){unsigned int y1,y2,y3,y4;unsigned int value;
while(1)
{
    lcd_cmd(0x01);
    lcd_string("ENTER YEAR:");
    lcd_cmd(0xC0);

    // Read first digit of year
    while(1)
    {
        y1 = keypad_scan();
        if((y1 >= '0') && (y1 <= '9'))
        {
            lcd_data(y1);
            wait_release();
            break;
        }
    }

    // Read second digit of year
    while(1)
    {
        y2 = keypad_scan();
        if((y2 >= '0') && (y2 <= '9'))
        {
            lcd_data(y2);
            wait_release();
            break;
        }
    }

    // Read third digit of year
    while(1)
    {
        y3 = keypad_scan();
        if((y3 >= '0') && (y3 <= '9'))
        {
            lcd_data(y3);
            wait_release();
            break;
        }
    }

    // Read fourth digit of year
    while(1)
    {
        y4 = keypad_scan();
        if((y4 >= '0') && (y4 <= '9'))
        {
            lcd_data(y4);
            wait_release();
            break;
        }
    }

    // Convert ASCII digits to integer year
    value =
    ((y1-48)*1000) +
    ((y2-48)*100) +
    ((y3-48)*10) +
    (y4-48);

    // Validate year range

    if((value >= 2000) && (value <= 2099))
    {
        YEAR = value;
        break;
    }

    // Display error message for invalid year
    lcd_cmd(0x01);
    lcd_string("INVALID YEAR");
    delay_ms(30);
}

// Year updated successfully

lcd_cmd(0x01);
lcd_string("YEAR UPDATED");
delay_ms(30);
}
// RTC Menu for editing individual Time and Date fields
void rtc_menu(void){	
unsigned char page = 0;   // Menu page number
while(1)
{
    lcd_cmd(0x01);
    // Page 1 : Hour and Minute
    if(page == 0)
    {
        lcd_cmd(0x80);
        lcd_string("1.HOUR");
        lcd_cmd(0xC0);
        lcd_string("2.MIN #NEXT");
    }

    // Page 2 : Second and Date
    else if(page == 1)
    {
        lcd_cmd(0x80);
        lcd_string("3.SEC");
        lcd_cmd(0xC0);
        lcd_string("4.DATE#NEXT");
    }
    // Page 3 : Month and Year
    else
    {
        lcd_cmd(0x80);
        lcd_string("5.MON");
        lcd_cmd(0xC0);
        lcd_string("6.YEAR#EXIT");
    }
    // Wait for user key press
    while(1)
    {
        key = keypad_scan();

        if(key != 0)
        {
            wait_release();
            break;
        }
    }
    // Handle Page-1 options
    if(page == 0)
    {
        if(key == '1')
        {
            edit_hour();      // Edit Hour
            return;
        }
        else if(key == '2')
        {
            edit_min();       // Edit Minute
            return;
        }
        else if(key == '#')
        {
            page = 1;         // Go to next page
        }
    }
    // Handle Page-2 options
    else if(page == 1)
    {
        if(key == '3')
        {
            edit_sec();       // Edit Second
            return;
        }
        else if(key == '4')
        {
            edit_date();      // Edit Date
            return;
        }
        else if(key == '#')
        {
            page = 2;         // Go to next page
        }
    }
    // Handle Page-3 options
    else
    {
        if(key == '5')
        {
            edit_month();     // Edit Month
            return;
        }

        else if(key == '6')
        {
            edit_year();      // Edit Year
            return;
        }

        else if(key == '#')
        {
            // Exit menu
            lcd_cmd(0x01);
            lcd_string("EXIT");
            delay_ms(30);
            lcd_cmd(0x01);
            return;
       }
    }
  }
}

  int main()
	 {
    lcd_init();
    keypad_init();
    rtc_init();
    adc_init();
    led_init();
    lcd_cmd(0x80);
    lcd_string("STREET LIGHT");
    delay_ms(30);

    lcd_cmd(0x01);
   while(1)
    {
      // DISPLAY RTC
			rtc_display();
			// READ KEYPAD
			key = keypad_scan();
      // OPEN MENU

    if(key == '1')
    {
        wait_release();
        rtc_menu();
        lcd_cmd(0x01);
    }

    // READ LDR
    ldr = adc_read();

    // DISPLAY LDR VALUE

    lcd_cmd(0x8A);
    lcd_data((ldr/1000) + 48);
    lcd_data(((ldr/100)%10) + 48);
    lcd_data(((ldr/10)%10) + 48);
    lcd_data((ldr%10) + 48);

    // NIGHT CONDITION

    if((HOUR >= 18) || (HOUR < 6))
    {
        if(ldr < 400)
        {
            led_on();
        }
        else
        {
            led_off();
        }
    }
    else
    {
        led_off();
    }
    delay_ms(1);
}
	// OPEN MENU
   if(key == '1'){wait_release();
   rtc_menu();
   lcd_cmd(0x01);
   }
 }