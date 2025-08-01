#include "stm32f4xx.h"
#include <stdio.h>

void UART2_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  

    // PA2=TX, PA3=RX
    GPIOA->MODER &= ~((3<<(2*2)) | (3<<(3*2)));
    GPIOA->MODER |= (2<<(2*2)) | (2<<(3*2)); 
    GPIOA->AFR[0] |= (7<<(2*4)) | (7<<(3*4)); 

    USART2->BRR = 0x8B; //115200 baudrate
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UART2_SendChar(char c)
{
    while (!(USART2->SR&USART_SR_TXE));
    USART2->DR=c;
}

void UART2_SendString(char *str)
{
    while(*str) UART2_SendChar(*str++);
}

void ADC1_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    GPIOA->MODER |= (3<<(0 * 2));      // PA0 analog mode
    GPIOA->PUPDR &= ~(3<<(0 * 2));   
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  

    ADC->CCR = 0;                        
    ADC1->SQR1 = 0;                     
    ADC1->SQR3 = 0;                      
    ADC1->SMPR2 |= (3 << 0);             
    ADC1->CR2=0;                       
    ADC1->CR2 &= ~ADC_CR2_CONT;          
    ADC1->CR2 |= ADC_CR2_ADON;           

    for (volatile int i=0; i<1000; i++); 
}

uint16_t ADC1_Read(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;        
    while (!(ADC1->SR & ADC_SR_EOC));    
    return ADC1->DR;                     
}

int main(void)
{
    char buffer[40];
    uint16_t adc_value;
    int volt_int, volt_frac;
    UART2_Init();
    ADC1_Init();

    UART2_SendString("ADC Test with Voltage\r\n");

    while (1)
    {
        adc_value = ADC1_Read();
        // Calculate voltage
        int voltage_mV = (adc_value*3300)/4095;
        volt_int = voltage_mV/1000;     
        volt_frac = voltage_mV%1000;    
        snprintf(buffer, sizeof(buffer),
                 "ADC: %4d  Voltage: %d.%03d V\r\n",
                 adc_value, volt_int, volt_frac);

        UART2_SendString(buffer);

        for (volatile int i = 0; i< 800000; i++); 
    }
}
