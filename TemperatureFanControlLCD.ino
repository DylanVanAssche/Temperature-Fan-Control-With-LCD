/*

 ******************************************
 *                                        *
 *--> TEMPERATURE FAN CONTROL WITH LCD <--*
 *                                        *
 *               V 1.0.1 RC               *
 ******************************************
 
 (c) Dylan Van Assche, you use this sketch for free! It's opensource :)
 */

#include <SoftPWM_timer.h>
#include <SoftPWM.h>
#include <LiquidCrystal.h>
#include <TimedAction.h>

// Defines the pins for the LCD screen.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Basic declarations.
int temperature    =    0;
int tempsensor     =   A1;
int fanpower       =    0;
int fan            =    8;

// Set up the LCD check timer.
TimedAction Update =  TimedAction(100,UpdateLCD);

void setup() 
{

  // Set up the LCD and some basic information on the LCD:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Power:");
  lcd.setCursor(0,1);
  lcd.print("Temp.:");

  // Set up the SoftPWM library, with this library it doesn't make a difference if your pin is connected to a PWM-pin or not.
  SoftPWMBegin();
  SoftPWMSet(fan, 0);
  SoftPWMSetFadeTime(fan, 1000, 1000);

}

void loop() 
{

  // Check the timer during the loop.  
  Update.check(); 

}

// The LCD update function, it updates the information on the LCD display and controls the fan at the same time.
void UpdateLCD()
{

  // Converte analogRead to °C
  temperature = (5.0 * analogRead(tempsensor) * 100.0) / 1024;

  // Temperature on LCD.
  lcd.setCursor(10,1);
  lcd.print(temperature); 
  lcd.setCursor(13,1);
  lcd.print((char)223);
  lcd.setCursor(14,1);
  lcd.print("C");

  // Start the fans when the temperature reach 27 degrees.
  if(temperature >= 24)
  {
    fanpower = map(analogRead(tempsensor),35,140,15,100);
    lcd.setCursor(10,0);
    lcd.print(fanpower); 
    lcd.setCursor(13,0); 
    lcd.print("%"); 
    SoftPWMSetPercent(fan, fanpower);
  }
  else
  {
    lcd.setCursor(10,0); 
    lcd.print("0 ");  
    lcd.setCursor(13,0); 
    lcd.print("%"); 
    SoftPWMSetPercent(fan, 0);
  }

}


