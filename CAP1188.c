#include <xc.h>
#include "CAP1188.h"

#define MSSPx   2

#define CS  LATDbits.LATD7

#if MSSPx == 1
#define SSPxCON1bits    SSPCON1bits
#define SSPxSTATbits    SSPSTATbits
#define SSPxBUF         SSPBUF
#define SPI_TRIS()      TRISCbits.TRISC3=0;TRISCbits.TRISC4=1;TRISCbits.TRISC5=0  
                        //SDO=RC5, SDI=RC4, SCL=RC3
#define SSPxIF          SSPIF
#elif MSSPx == 2
#define SSPxCON1bits    SSP2CON1bits
#define SSPxSTATbits    SSP2STATbits
#define SSPxBUF         SSP2BUF
#define SPI_TRIS()      TRISDbits.TRISD4=0;TRISDbits.TRISD5=1;TRISDbits.TRISD6=0
                        //SDO=RD4, SDI=RD5, SCL=RD6
#define SSPxIF          SSP2IF
#else
#error Invalid MSSPx selection
#endif

typedef unsigned char BYTE;

BYTE SPI(BYTE b) {
    SSPxIF = 0;
    SSPxBUF = b;
    while (!SSPxIF);
    b = SSPxBUF;
    return b;
}

void writeRegister(char reg, char data) {
    CS = 0;
    SPI(0x7d);
    SPI(reg);
    SPI(0x7e);
    SPI(data);
    CS = 1;
}

BYTE readRegister(char reg) {
    BYTE b;
    CS = 0;
    SPI(0x7d);
    SPI(reg);
    SPI(0x7f);
    b = SPI(0x7f);
    CS = 1;
    return b;
}

void InitCAP1188(void) {
    CS = 1;
    TRISDbits.TRISD7 = 0;
    SPI_TRIS();
    SSPxSTATbits.CKE = 1;
    SSPxCON1bits.CKP = 0;
    SSPxSTATbits.SMP = 0;
    SSPxCON1bits.SSPM = 0b0001;
    SSPxCON1bits.SSPEN = 1;
    CS = 0;
    SPI(0x7a);
    SPI(0x7a);
    CS = 1;
    writeRegister(0x72, 0xff); //Link LED's to buttons
    writeRegister(0x81, 0b00000010); //LED1 pulse
}

char GetButtonState(void) {
    char buttons = 0;
    buttons = readRegister(0x03);
    return buttons;
}
 
void ClearButtonState(void) {
    char status;
    status = readRegister(0x00);
    status &= 0b11111110; //Clear INT bit
    writeRegister(0x00, status);
}

void ConfigureLED(char led, char mode) {
    
}

void SetLED(char led, char state) {
    
}