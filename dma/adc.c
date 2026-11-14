
#include "adc.h"

// Configuracion del pin PA1
void init_adc_pin(void)
{
    // Habilitar reloj del puerto A
    RCC->APB2ENR |= (1U << 2);

    // PA1 como entrada analogica
    GPIOA->CRL &= ~(0xFU << 4);
}

// Configuracion de ADC1
void init_adc1(void)
{
    volatile uint32_t espera;

    // Habilitar reloj ADC1
    RCC->APB2ENR |= (1U << 9);

    // Prescaler ADC: PCLK2 / 6
    RCC->CFGR &= ~(3U << 14);
    RCC->CFGR |=  (2U << 14);

    // Una conversion regular
    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;

    // Seleccionar canal 1 (PA1)
    ADC1->SQR3 = 1;

    // Tiempo de muestreo: 239.5 ciclos
    ADC1->SMPR2 &= ~(7U << 3);
    ADC1->SMPR2 |=  (7U << 3);

    // Configuracion independiente
    ADC1->CR1 = 0;

    // CONT = 1: conversion continua
    // DMA = 1: habilitar solicitudes DMA
    // EXTSEL = 111: inicio por software
    // EXTTRIG = 1: permitir disparo
    ADC1->CR2 = (1U << 1) |
                (1U << 8) |
                (7U << 17) |
                (1U << 20);

    // Encender ADC1
    ADC1->CR2 |= (1U << 0);

    // Tiempo de estabilizacion
    for (espera = 0; espera < 10000U; espera++)
    {
        __NOP();
    }

    // Reiniciar calibracion
    ADC1->CR2 |= (1U << 3);

    while (ADC1->CR2 & (1U << 3))
    {
    }

    // Iniciar calibracion
    ADC1->CR2 |= (1U << 2);

    while (ADC1->CR2 & (1U << 2))
    {
    }
}

// Iniciar conversiones del ADC
void adc_iniciar(void)
{
    // SWSTART = 1
    ADC1->CR2 |= (1U << 22);
}