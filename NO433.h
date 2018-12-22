#include <RCSwitch.h> // biblioteka obsługi nadawania i odbioru 433 MHz
RCSwitch mySwitch = RCSwitch();
void routerakcja();

unsigned long o_kod = 0;  //received kod

void no433rec() {
  if (procesor == D1MINI) {
    if ((modul == all) || (modul == rec))mySwitch.enableReceive(12);
  }
  if (procesor == ESP01) {
    if ((modul == all) || (modul == rec))mySwitch.enableReceive(3);
  }
}
void no433tran() {
  if (procesor == D1MINI) {
    if ((modul == all) || (modul == tran))mySwitch.enableTransmit(14);
  }
  if (procesor == ESP01) {
    if ((modul == all) || (modul == tran))mySwitch.enableTransmit(1);
  }
}
void no433setup()
{
  no433rec();
  no433tran();
}

void no433akcja()
{
  if (mySwitch.available()) {

    if (procesor == D1MINI) { //przełącznik wysyłania info o odebranym kodzie na monitor
      Serial.println("Kod " + String(mySwitch.getReceivedValue()) + " / " + String(mySwitch.getReceivedBitlength()) + " IMP " + String(mySwitch.getReceivedDelay())
                     + " Prot  "  + " / " + String(mySwitch.getReceivedProtocol()) );
    }
    if ((modul == all) || (modul == rec)) {
      terminal.println("Kod " + String(mySwitch.getReceivedValue()) + " / " + String(mySwitch.getReceivedBitlength()) + " IMP " + String(mySwitch.getReceivedDelay())
                       + " Prot " + " / " + String(mySwitch.getReceivedProtocol()) );
      terminal.flush();
      String str = String(mySwitch.getReceivedValue()) + " / " + String (mySwitch.getReceivedDelay());
      Blynk.virtualWrite(V3, str);
      str = String(mySwitch.getReceivedValue());
      Blynk.virtualWrite(V20, str);
    }
    o_kod = mySwitch.getReceivedValue();
    routerakcja();
    mySwitch.resetAvailable();
  }
}

void sendkod(unsigned long code, int impuls, byte bity, byte prot) { // wysłanie kodu z routera
  mySwitch.disableReceive();  no433tran(); // nadajnika

  mySwitch.setPulseLength(impuls);
  mySwitch.setRepeatTransmit(4);
  mySwitch.send(code, bity);

  mySwitch.disableTransmit();   no433rec();   // nadajnika
}

void sendkodpilot (unsigned long code) {
  sendkod(code, 340, 24, 1);
}

