
#define led_czerw   0

void ledsetup() {
  pinMode(led_czerw, OUTPUT); //LED na module
  digitalWrite(led_czerw, HIGH);
}

BLYNK_WRITE(V10) {
  if (param.asInt()) akcja.updateInterval(2, 500); else akcja.updateInterval(2, 2000);
}

int flaga_led = 0;
void led_timer()
{
  flaga_led = !flaga_led;
  digitalWrite(led_czerw, flaga_led);
}
