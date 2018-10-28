/*
 * Muhammet Tayyip Çankaya
 * 8x8 dot matrix
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/adc.h"

/*8x8 MATRIX
 * PA5 - DIN
 * PA3 - CS
 * PA2 - CLK*/
void spi_write(uint16_t data)
{
    SSIDataPut(SSI0_BASE, data);
    while (SSIBusy(SSI0_BASE))
    {}
    return;
}

void zero(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x24);
    spi_write(3<<8 | 0x24); spi_write(4<<8 | 0x24);
    spi_write(5<<8 | 0x24); spi_write(6<<8 | 0x24);
    spi_write(7<<8 | 0x24); spi_write(8<<8 | 0x3C);}

void one(){
    spi_write(1<<8 | 0x08); spi_write(2<<8 | 0x18);
    spi_write(3<<8 | 0x28); spi_write(4<<8 | 0x08);
    spi_write(5<<8 | 0x08); spi_write(6<<8 | 0x08);
    spi_write(7<<8 | 0x08); spi_write(8<<8 | 0x3E);}

void two(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x04);
    spi_write(3<<8 | 0x04); spi_write(4<<8 | 0x04);
    spi_write(5<<8 | 0x3C); spi_write(6<<8 | 0x20);
    spi_write(7<<8 | 0x20); spi_write(8<<8 | 0x3C);}

void three(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x04);
    spi_write(3<<8 | 0x04); spi_write(4<<8 | 0x04);
    spi_write(5<<8 | 0x3C); spi_write(6<<8 | 0x04);
    spi_write(7<<8 | 0x04); spi_write(8<<8 | 0x3C);}

void four(){
    spi_write(1<<8 | 0x04); spi_write(2<<8 | 0x0C);
    spi_write(3<<8 | 0x14); spi_write(4<<8 | 0x24);
    spi_write(5<<8 | 0x24); spi_write(6<<8 | 0x3C);
    spi_write(7<<8 | 0x04); spi_write(8<<8 | 0x04);}

void five(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x20);
    spi_write(3<<8 | 0x20); spi_write(4<<8 | 0x20);
    spi_write(5<<8 | 0x3C); spi_write(6<<8 | 0x04);
    spi_write(7<<8 | 0x04); spi_write(8<<8 | 0x3C);}

void six(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x20);
    spi_write(3<<8 | 0x20); spi_write(4<<8 | 0x20);
    spi_write(5<<8 | 0x3C); spi_write(6<<8 | 0x24);
    spi_write(7<<8 | 0x24); spi_write(8<<8 | 0x3C);}

void seven(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x04);
    spi_write(3<<8 | 0x04); spi_write(4<<8 | 0x08);
    spi_write(5<<8 | 0x10); spi_write(6<<8 | 0x20);
    spi_write(7<<8 | 0x20); spi_write(8<<8 | 0x20);}

void eight(){
    spi_write(1<<8 | 0x18); spi_write(2<<8 | 0x24);
    spi_write(3<<8 | 0x24); spi_write(4<<8 | 0x24);
    spi_write(5<<8 | 0x18); spi_write(6<<8 | 0x24);
    spi_write(7<<8 | 0x24); spi_write(8<<8 | 0x18);}

void nine(){
    spi_write(1<<8 | 0x3C); spi_write(2<<8 | 0x24);
    spi_write(3<<8 | 0x24); spi_write(4<<8 | 0x24);
    spi_write(5<<8 | 0x3C); spi_write(6<<8 | 0x04);
    spi_write(7<<8 | 0x04); spi_write(8<<8 | 0x3C);}


int main(void)
{
    uint32_t pui32DataRx;
    int i=0;

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4 );
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);   // enable F4's pullup, the drive strength won't affect the input

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_2);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,1000000, 16);
    SSIEnable(SSI0_BASE);
    while (SSIDataGetNonBlocking(SSI0_BASE, &pui32DataRx)){}

    spi_write(0x09 << 8 | 0x00);       //decoding ：BCD
    spi_write(0x0a << 8 | 0x01);       //brightness
    spi_write(0x0b << 8 | 0x07);       //scanlimit；8 LEDs
    spi_write(0x0c << 8 | 0x01);       //power-down mode：0，normal mode：1
    spi_write(0x0f << 8 | 0x00);       //test display：1；EOT，display：0

    //ADC EKLENDI
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //ADC yi enable et
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);//portE2 yi ADC icin kullan
    ADCHardwareOversampleConfigure(ADC0_BASE,64);//64 sample al ortalamasını döndür
    ADCSequenceDisable(ADC0_BASE,3);//Disable et ayarlamalari yapmak için
    ADCSequenceConfigure(ADC0_BASE,3,ADC_TRIGGER_PROCESSOR,0); //ADC_TRIGGER_TIMER EKLENDI
    ADCSequenceStepConfigure(ADC0_BASE , 3 , 0 , ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);//CH1-->PE2 ---- IE-->interrupt enable
    ADCSequenceEnable(ADC0_BASE,3);

    while(1){
        uint32_t AdcValues[1];
        ADCIntClear(ADC0_BASE,3);
        ADCProcessorTrigger(ADC0_BASE,3);
        while(!ADCIntStatus(ADC0_BASE,3,false));
        ADCSequenceDataGet(ADC0_BASE,3,AdcValues);
        if(AdcValues[0]<1000)
            i++;
        else if(AdcValues[0]>2700 & AdcValues[0]<3000)
            i--;
        //printf("(AdcValues[0] = %d  i =  %d \n",AdcValues[0],i);
        SysCtlDelay(SysCtlClockGet()/8);

        if(i<0)
            i=0;

        i=i%10;
        printf("sonuc i =  %d \n",i);

        if(i==0)zero();
        else if(i==1)one();
        else if(i==2)two();
        else if(i==3)three();
        else if(i==4)four();
        else if(i==5)five();
        else if(i==6)six();
        else if(i==7)seven();
        else if(i==8)eight();
        else if(i==9)nine();
    }
}
