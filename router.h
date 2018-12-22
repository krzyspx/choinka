#define zal_choinka 5526609
#define wyl_choinka 5526612
#define A_zal 5588305
#define A_wyl  5588308
#define B_zal 5591377
#define B_wyl  5591380
#define C_zal 5592145
#define C_wyl  5592148
#define D_zal 5592337
#define D_wyl  5592340

int choinka = 0;
int send_choinka = 0;

void send_router_kod()
{
  if (choinka == 1) {
    if (send_choinka == 4)sendkodpilot (A_zal);
    if (send_choinka == 3)sendkodpilot (B_zal);
    if (send_choinka == 2)sendkodpilot (C_zal);
    if (send_choinka == 1)sendkodpilot (D_zal);
    Blynk.setProperty(V15, "onLabel", send_choinka);
  }
  if (choinka == 2) {
    if (send_choinka == 4)sendkodpilot (A_wyl);
    if (send_choinka == 3)sendkodpilot (B_wyl);
    if (send_choinka == 2)sendkodpilot (C_wyl);
    if (send_choinka == 1)sendkodpilot (D_wyl);
    Blynk.setProperty(V15, "offLabel", send_choinka);
  }
  send_choinka--;
  if (send_choinka < 1)choinka = 0;
}
void router_timer()
{
  send_router_kod();
}

void routerakcja() {
  if ((o_kod == zal_choinka) || (o_kod == zal_choinka)) {
    choinka = 1;
    send_choinka = 4;
    o_kod =  0;
    Blynk.setProperty(V15, "color", _RED);
    Blynk.virtualWrite(V15, choinka);
  }
  if ((o_kod == wyl_choinka) || (o_kod == wyl_choinka)) {
    choinka = 2;
    o_kod =  0;
    send_choinka = 4;
    Blynk.setProperty(V15, "color", _GREEN);
    Blynk.virtualWrite(V15, choinka);
  }
}

BLYNK_WRITE(V15) //zalaczenie pompy recznie
{
  choinka = param.asInt();
  send_choinka = 4;
}
