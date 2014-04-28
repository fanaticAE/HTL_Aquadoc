#ifndef LibDisplay_h
#define LibDisplay_h
#include "Information.h"
//Constants for some Pins:

/*Set these constants to useful pins for your configuration. 
*/ 

const int LCD_RS = 12;
const int LCD_ENA = 11; 
const int LCD_D4 = 5; 
const int LCD_D5 = 4;
const int LCD_D6 = 3; 
const int LCD_D7 = 2; 

//Constants for LEDs
/*
Dies hier ist eine Art der Konfiguration fuer die LEDs
in dem integer - Array LEDS werden die Pins aller LEDs hinterlegt, 
um dann im Programmablauf darauf zugreifen zu koennen.
LED_COUNT gibt die Anzahl der verwendeten LEDs an!
*/
const int LEDS[] = {14,15,16,17,18,19}; 
const int LED_COUNT = 6; 

void setupDisplay(); //To be run in setup routine
void displayInformation(Information _info); //To display new Information 
#endif
