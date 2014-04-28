#ifndef AquadocInfo_h
#define AquadocInfo_h
#include <Arduino.h>
typedef struct Information{
	//Werte
	int zulauf; //Wert der Zulaufvariable 
	int ablauf; //Wert der Ablaufvariable
	float fuellstand; //Verhaeltniss zwischen empfangenem Fuellstandswert und Maximalfuellstandswert
	float temperatur; //Temperatur 
	//Bitfield
	boolean isTuerOffen; 
	boolean isAkkuAlarm; 
	boolean isSystemError; 	
	//System
	boolean isReceiveValid; //Wenn Empfang Fehlerfrei True, selbst wenn Pruefsumme Falsch
	boolean isCheckSumValid; //Wenn Pruefsumme Okay auf true
	boolean isError; // Wenn sonstiger Fehler auftritt auf true, sonst auf false
  }Information;
  #endif
