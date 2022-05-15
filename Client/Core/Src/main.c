#include "stm32wb55xx.h"
#include <stdint.h>
#include <stdio.h>

int main()
{
    // setup clocks
    RCC->AHB2ENR &= ~(1 << 0); // reset bit
    RCC->AHB2ENR |= (1 << 0); // enable GPIOA clock
    RCC->APB2ENR &= ~(1 << 14); // reset bit
    RCC->APB2ENR |= (1 << 14); // enable USART1 clock

    // setup PA1
    GPIOA->MODER &= ~(3 << 2);
    GPIOA->MODER |= (1 << 2); // set PA1 as output

    // setup PA10
    GPIOA->MODER &= ~(3 << 20); // reset bits
    GPIOA->MODER |= (2 << 20); // set PA10 as alternate function
    GPIOA->AFR[1] &= ~(0b1111 << 8); // reset bits
    GPIOA->AFR[1] |= (7 << 8); // set alternate function register for line 10

    // setup USART1
    USART1->CR1 &= ~(1 << 0); // reset bit
    USART1->CR1 |= (1 << 0); // enable USART
    USART1->CR1 &= ~(1 << 2); // reset bit
    USART1->CR1 |= (1 << 2); // enable receiver

    // setup baud rate to 115200 (default clock speed = 4MHz)
    USART1->BRR = (4000000/115200);

    uint8_t uart_rx_value = 0;

    while(1)
    {
        // wait for data to be received
        while (!(USART1->ISR & (1 << 5)));
        uart_rx_value = USART1->RDR;
        GPIOA->ODR &= ~(1 << 1);
        GPIOA->ODR |= (uart_rx_value << 1);
    }
    return 0;
}