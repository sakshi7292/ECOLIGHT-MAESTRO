# ECOLIGHT-MAESTRO
An LPC2129-based smart street light system using RTC, LDR, LCD, and keypad. The system automatically controls street lights based on time and ambient light conditions and allows real-time editing of time and date through a keypad interface.
## Features
- Automatic street light control
- RTC based time monitoring
- LDR based light intensity sensing
- LCD display for time, date, and LDR value
- Keypad based RTC editing
- Individual editing of hour, minute, second, date, month, and year
- Night-time based street light operation
  
  ## Hardware Components
- LPC2129 ARM7 Microcontroller
- 16x2 LCD
- 4x4 Keypad
- LDR Sensor
- LED
- Crystal Oscillator
- Power Supply

 ## Software Used
- Keil uVision
- Proteus
- Embedded C

## Working Principle

The RTC continuously monitors the current time. During night hours (6 PM to 6 AM), the LDR senses ambient light intensity. If the environment becomes dark, the LED turns ON automatically. The keypad allows the user to edit time and date parameters individually.
  
