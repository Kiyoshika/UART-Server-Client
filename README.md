# STM32 Bare Metal - UART Server/Client
This project shows how to make two MCUs communicate with each other over UART.

## Project Description
A "server" MCU is set up to send alternating bits of 1 and 0 to a "client" MCU. The client reads that data and turns an LED on if the bit received was 1 and turns the LED off if the bit received was 0.

## Server MCU
For the "server", I am using an STM32F411xx. PA9 is configured as UART Tx with baud rate of 115200.

## Client MCU
For the "client", I am using a STM32WB55xx. PA10 is configured as UART Rx with baud rate 115200 and PA1 is configured as output to toggle LED.