#include "stm32f411xe.h"
#include <stdint.h>

// NOTE: MUST use no compiler optimizations otherwise the loops get optimized out
void fake_delay()
{
    for (uint32_t i = 0; i < 500000; ++i);
}

int main()
{

    // setup clocks
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN; // reset bit
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // enable GPIOA clock
    RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN; // reset bit
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // enable USART1 clock

    // setup PA9
    GPIOA->MODER &= ~(3 << 18); // reset bits
    GPIOA->MODER |= (2 << 18); // set PA9 as alternate function
    GPIOA->AFR[1] &= ~(0xF << 4); // reset bits
    GPIOA->AFR[1] |= (7 << 4); // set alternate function register for line 10

    // setup USART1
    USART1->CR1 &= ~(1 << 13); // reset bit
    USART1->CR1 |= (1 << 13); // enable USART
    USART1->CR1 &= ~(1 << 3); // reset bit
    USART1->CR1 |= (1 << 3); // enable transmitter

    // setup baud rate to 115200 (default clock speed = 16MHz)
    USART1->BRR &= ~(0xFFF << 4); // reset bits
    USART1->BRR |= (8 << 4); // mantissa = 8
    USART1->BRR &= ~(0xF << 0); // reset bits
    USART1->BRR |= (11 << 0); // fraction = 11

    uint8_t uart_tx_value = 3;
    GPIOA->ODR |= (1 << 3);

    while(1)
    {
        while (!(USART1->SR & USART_SR_TXE));
        USART1->DR = 19;
        fake_delay();

    }
    return 0;
}