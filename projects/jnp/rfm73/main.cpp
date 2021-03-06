// Test code for the RF73 driver, with continuous reads and periodic sends.

#include "sys.h"
#include "spi.h"

#define RFM73 0 // 0 = RFM70, 1 = RFM73
#include "rf73.h"

RF73<SpiDev0,15> rf;

int main () {
  serial.init(115200);
  printf("\n[rfm73] %d\n", RFM73);

  // j169: sck 17, ssel 23, miso 9, mosi 8, ce 15
  LPC_SWM->PINASSIGN[3] = 0x11FFFFFF;
  LPC_SWM->PINASSIGN[4] = 0xFF170908;

  rf.init(42);

  uint16_t cnt = 0;
  uint8_t txBuf[RF73_MAXLEN];
  for (int i = 0; i < RF73_MAXLEN; ++i)
    txBuf[i] = i;

  while (true) {
    if (++cnt == 0) {
        int txLen = ++txBuf[0] % RF73_MAXLEN;
        printf(" > #%d, %db\n", txBuf[0], txLen);
        rf.send(0, txBuf, txLen);
    }

    uint8_t rxBuf [RF73_MAXLEN];
    int len = rf.receive(rxBuf, sizeof rxBuf);
    if (len > 0) {
      printf("OK ");
      for (int i = 0; i < len; ++i)
          printf("%02x", rxBuf[i]);
      printf("\n");
    }
  }
}
