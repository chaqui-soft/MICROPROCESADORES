
#ifndef DMA_H
#define DMA_H

#include "stm32f10x.h"

// Numero de muestras a almacenar
#define ADC_BUFFER_SIZE 16

// Arreglo de memoria RAM
extern volatile uint16_t adc_buffer[ADC_BUFFER_SIZE];

// Prototipo de inicializacion DMA
void init_dma1(void);

#endif