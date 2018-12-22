
#define BLYNK_MSG_LIMIT 0
// #error "Compiles"
#include <EEPROM.h>
#include <Timers.h> //  my favorite timer 
Timers <7> akcja; //

#include "blynk.h" //obsługa BLYNKa
#include "led.h"
#include "NO433.h" // obsługa transmisji 433 MHz
#include "router.h" // 

void setup()
{
  ledsetup();
  if (procesor == D1MINI) {
    Serial.begin(115200);  delay(100);
    Serial.println();  Serial.println(F(__FILE__));  //BLYNK .4.10 Arduino IDE.cc 1.8.3
    Serial.println("moduł = " + String(modul));
  }
  akcja.attach(0, 3000, blynk_timer); //
  akcja.attach(2, 2000, led_timer);
  akcja.attach(3, 2001, router_timer); //

  blynksetup(); // setup biblioteki BLYNK
  no433setup();  //setup 433 MHz
}
void loop()
{
  akcja.process(); // timer
  blynkakcja();    //BLYNK
  no433akcja();
}








