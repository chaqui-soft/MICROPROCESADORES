
#include "dma.h"

// Arreglo para almacenar datos en memoria RAM
volatile uint16_t adc_buffer[ADC_BUFFER_SIZE] = {0};

// Configuracion de DMA1 Canal 1
void init_dma1(void)
{
    // 1. Habilitar reloj de DMA1
    RCC->AHBENR |= (1U << 0);

    // 2. Deshabilitar Canal 1
    DMA1_Channel1->CCR = 0;

    // 3. Limpiar banderas del Canal 1
    DMA1->IFCR = 0x0F;

    // 4. Direccion de origen:
    // Registro de datos del ADC1
    DMA1_Channel1->CPAR =
        (uint32_t)&ADC1->DR;

    // 5. Direccion de destino:
    // Arreglo ubicado en memoria RAM
    DMA1_Channel1->CMAR =
        (uint32_t)adc_buffer;

    // 6. Numero de datos a transferir
    DMA1_Channel1->CNDTR = ADC_BUFFER_SIZE;

    // 7. Configurar DMA
    // CIRC = 1: modo circular
    // MINC = 1: incremento de memoria
    // PSIZE = 01: periferico de 16 bits
    // MSIZE = 01: memoria de 16 bits
    // PL = 01: prioridad media
    // DIR = 0: periferico hacia memoria

    DMA1_Channel1->CCR =
        (1U << 5)  |
        (1U << 7)  |
        (1U << 8)  |
        (1U << 10) |
        (1U << 12);

    // 8. Habilitar DMA1 Canal 1
    DMA1_Channel1->CCR |= (1U << 0);
}