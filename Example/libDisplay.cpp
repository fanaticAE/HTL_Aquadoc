#include "libDisplay.h"// Own Header File
#include "Information.h"//Include for the Information Struct! 
#include "LiquidCrystal.h" //LiquidCrystalLib
#include <Arduino.h>//Arduino Lib


//Setup
void setupLED(); 
void setupLCD(); 
//LED 
void displayLED(Information _info); 
void clearLED(); 
//LCD
void displayLCD(Information _info); 
void resetLCD(); 
void setLineLCD(int line); 
void writeError(int errorCode); 
void writeErrorCode(int errorCode); 
void writeErrorMessage(int errorCode); 
void writeTemperatur(float temperatur); 
void writeLevel(int level); 
void writeInflow(int inflow); 
void writeDrain(int drain); 
void writeWarnings(Information _info); 
void writeIntValue(const char ident[], int value,int offset,int position, int line );
//MISC
int checkErrors(Information _info); 
int dirtyRound(float f); 


//Konstanten 
//ERRORS
const int ERROR_NOERROR = 0; 
const int ERROR_INVALID_RECEIVE = 1; 
const int ERROR_INVALID_CHECKSUM = 2; 
const int ERROR_MISC = 3; 
const int ERROR_REMOTE = 4; 
const int ERROR_HIGH_TEMPERATUR = 5;

const char ERRORDISPLAY[] = "ERROR:"; 

const char ERRORMESSAGE_INVALID_RECEIVE[] = "Empfangsfehler"; 
const char ERRORMESSAGE_INVALID_CHECKSUM[] = "Summenfehler"; 
const char ERRORMESSAGE_MISC[] = "Unbek. Fehler"; 
const char ERRORMESSAGE_REMOTE[] = "Messs. Fehler"; 
const char ERRORMESSAGE_HIGH_TEMPERATUR[] = "zu hohe Temp."; 

//Warnings
const char WARNINGMESSAGE_BATTERY = 'A'; 
const char WARNINGMESSAGE_DOOR_OPEN = 'T'; 

//Positions
const int LINE_FIRST  = 0; 
const int LINE_SECOND = 1; 


const int POSITION_TEMPERATUR = 0; 
const int POSITION_LEVEL = 8; 
const int POSITION_INFLOW = 0; 
const int POSITION_DRAIN = 8; 

const int POSITION_WARNING_BATTERY=14; 
const int POSITION_WARNING_DOOR_OPEN=15; 

//IDENTS

const char IDENT_TEMPERATUR[] = "T:"; 
const char IDENT_LEVEL[] = "F:"; 
const char IDENT_INFLOW[] = "ZL:"; 
const char IDENT_DRAIN[] = "AL:"; 

//ASCII
const int ASCII_OFFSET_NUMBER = 48; 


//Breite des Displays
const int DISPLAY_WIDTH = 16;
//Hoehe des Displays
const int DISPLAY_HEIGHT = 2; 

//LCD
LiquidCrystal lcd(LCD_RS, LCD_ENA, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Setup - Routine
void setupDisplay(){
	setupLED(); 
	setupLCD(); 
}
void setupLED(){
/*
	Den Pinmode aller LEDS auf Output schalten 
	und alle Pins auf LOW legen, um Fehlinformation
	nach dem Initialisieren zu vermeiden! 

*/
	for(int i = 0; i < LED_COUNT; i++){ 
		pinMode(LEDS[i], OUTPUT); 
		digitalWrite(LEDS[i], LOW); 
	}  
}
void setupLCD(){
	//Initialsieren des Displays mithilfe der Arduino Display Library
	lcd.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT); 
}
void displayInformation(Information _info){
	displayLCD(_info); 
	displayLED(_info); 

}
void displayLED(Information _info){
	clearLED(); 
	if(checkErrors(_info) == ERROR_NOERROR){	
		int ledsToLit = dirtyRound(_info.fuellstand*LED_COUNT); 
		for(int i = 0; i < ledsToLit; i++){
			digitalWrite(LEDS[i], HIGH); 
		}
	}
}
void clearLED(){
	 for(int i = 0; i < LED_COUNT; i++){
	 digitalWrite(LEDS[i], LOW); 
	 }
}
void displayLCD(Information _info){
	int errorCode = ERROR_NOERROR; 
	resetLCD(); 	
	//Getting Error code
	errorCode = checkErrors(_info);
	//On Error Display and Return
	if(errorCode != ERROR_NOERROR){
		writeError(errorCode); 
		return; 
	}
	//Writing the Temerpatur on the LCD
	writeTemperatur(_info.temperatur); 
	writeLevel(dirtyRound(_info.fuellstand*100)); 
	writeInflow(_info.zulauf); 
	writeDrain(_info.ablauf); 
	writeWarnings(_info); 
	
}
int checkErrors(Information _info){
	//Checking if Receive is valid
	if(!_info.isReceiveValid) return ERROR_INVALID_RECEIVE; 
	//Checking if Checksum is valid
	if(!_info.isCheckSumValid) return ERROR_INVALID_CHECKSUM; 
	//Checking if Misc. Error
	if(_info.isError) return ERROR_MISC; 
	//Checking for Remote System Error
	if(_info.isSystemError)return ERROR_REMOTE; 
	//If Temperatur is to high to be display'd
	if(_info.temperatur >99.9)return ERROR_HIGH_TEMPERATUR; 
	//If no error 
	return ERROR_NOERROR; 
}
void resetLCD(){
	lcd.clear(); 
	lcd.setCursor(0,0); 
}
void setLineLCD(int line){
	lcd.setCursor(0,line); 
}
void writeError(int errorCode){
	//Resetting LCD
	resetLCD(); 
	writeErrorCode(errorCode); 
	writeErrorMessage(errorCode); 
}
void writeErrorCode(int errorCode){
	writeIntValue(ERRORDISPLAY, errorCode,6,0,LINE_FIRST); 	
}
void writeErrorMessage(int errorCode){
	setLineLCD(LINE_SECOND);  //Going to Second Line, First Position
	switch(errorCode){
		
		case ERROR_INVALID_RECEIVE:
			lcd.write(ERRORMESSAGE_INVALID_RECEIVE); 
		break; 
		
		case ERROR_INVALID_CHECKSUM:
			lcd.write(ERRORMESSAGE_INVALID_CHECKSUM); 
		break; 
		
		case ERROR_MISC:
			lcd.write(ERRORMESSAGE_MISC); 
		break; 
		
		case ERROR_REMOTE:
			lcd.write(ERRORMESSAGE_REMOTE); 
		break; 
		case ERROR_HIGH_TEMPERATUR:
			lcd.write(ERRORMESSAGE_HIGH_TEMPERATUR); 
		break; 
	}

}
void writeTemperatur(float temperatur){
    int cursorOffset = 0; 	
	float temp = temperatur; 
        lcd.setCursor(POSITION_TEMPERATUR + cursorOffset,LINE_FIRST); 
        //Print Information
		lcd.print(IDENT_TEMPERATUR); 
        //Printing readable
	      cursorOffset+=2; 
        lcd.setCursor(POSITION_TEMPERATUR +cursorOffset, LINE_FIRST); 
        lcd.print((int)temp);
        
        if(temperatur >=10){
          cursorOffset +=2; 
        }else cursorOffset ++; 

        lcd.setCursor(POSITION_TEMPERATUR +cursorOffset, LINE_FIRST); 
        lcd.print('.');
		cursorOffset++; 
        lcd.setCursor(POSITION_TEMPERATUR +cursorOffset, LINE_FIRST); 
	lcd.print(((int)(temp*10 - 10*(int)temp)));
	
}
void writeLevel(int level){
	writeIntValue(IDENT_LEVEL,level,2,POSITION_LEVEL,LINE_FIRST); 
}
void writeInflow(int inflow){
	writeIntValue(IDENT_INFLOW,inflow,3,POSITION_INFLOW,LINE_SECOND); 
}
void writeDrain(int drain){
	writeIntValue(IDENT_DRAIN,drain,3,POSITION_DRAIN,LINE_SECOND); 
}
void writeWarnings(Information _info){
	if(_info.isTuerOffen){
		lcd.setCursor(POSITION_WARNING_DOOR_OPEN,LINE_FIRST); 
		lcd.print(WARNINGMESSAGE_DOOR_OPEN); 
	}
	if(_info.isAkkuAlarm){
		lcd.setCursor(POSITION_WARNING_BATTERY,LINE_FIRST); 
		lcd.print(WARNINGMESSAGE_BATTERY); 
	}
}
void writeIntValue(const char ident[], int value,int offset,int position, int line ){
	lcd.setCursor(position,line); 
	lcd.print(ident); 
	lcd.setCursor(position+offset,line); 
	lcd.print(value); 
}

int dirtyRound(float f){
	int buff = f; 
	float n = f - buff; 
	if(n>=0.5) buff++; 
	return buff; 
}
