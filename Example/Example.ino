#include "Information.h"
#include "libDisplay.h"

Information info; 

void setup() {
  
  setupDisplay();
  
  info.zulauf = 5; 
  info.ablauf = 3; 
  info.fuellstand = 1; 
  info.temperatur = 12.3; 
  info.isTuerOffen = true; 
  info.isAkkuAlarm = true; 
  info.isSystemError = false; 
  info.isReceiveValid = false; 
  info.isCheckSumValid = true; 
  info.isError=false; 
  displayInformation(info); 
}

void loop() {
}
