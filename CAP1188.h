/* 
 * File:   CAP1188.h
 * Author: bmcgarvey
 *
 * Created on January 25, 2016, 2:30 PM
 */

#ifndef CAP1188_H
#define	CAP1188_H

#define SPI4_MODE
//#define SPI3_MODE
//#define I2C_MODE
//#define I2C_ADDRESS     0b01010010



#ifdef	__cplusplus
extern "C" {
#endif

    void InitCAP1188(void);
    char GetButtonState(void);
    void ClearButtonState(void);
    void ConfigureLED(char led, char mode);
    void SetLED(char led, char state);

#ifdef	__cplusplus
}
#endif

#endif	/* CAP1188_H */

