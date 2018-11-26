#include <xc.h>
#include "config encoder.h"
#define _XTAL_FREQ 32000000
#include <stdio.h>
#include "flex_lcd.h"

unsigned char buffer1[16];
float  a=0;

void main(void) {
    OSCFRQbits.HFFRQ=0b110;
    PORTA = 0;
    ANSELA = 0;
    TRISA = 255;
    PORTB = 0;
    ANSELB = 0;
    TRISB=0b11111111;
    ANSELD = 0;
    ANSELE = 0;
    
    Lcd_Init(); //iniciar LCD
    Lcd_Cmd(LCD_CLEAR);//LIMPIAR LCD
    __delay_ms(10);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(1);
    
    WPUBbits.WPUB0=1;
    WPUBbits.WPUB1 =1;
    
    INTCONbits.GIE=1;
    PIR0bits.IOCIF =0;
    PIE0bits.IOCIE = 1;
    
    IOCBNbits.IOCBN0 = 1;
    IOCBNbits.IOCBN1 = 1;
    IOCBFbits.IOCBF0 = 0;
    IOCBFbits.IOCBF1 = 0;
    while (1);
    return;
}
void __interrupt () ISR (void){
    if(IOCBFbits.IOCBF0){
        if(IOCBFbits.IOCBF1){
            a=a+2.59;
            sprintf (buffer1, "Distancia en cm: ");
            Lcd_Out2(1,0,buffer1);
            sprintf(buffer1, "%f", a);
            Lcd_Out2(2,3,buffer1);
            IOCBFbits.IOCBF0=0;
            IOCBFbits.IOCBF1=0;
        }
    }
    else{
        a=a;
    }
    PIR0bits.IOCIF=0;
    
}
