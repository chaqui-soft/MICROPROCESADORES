
#include "stm32f10x.h"
#include "adc.h"
#include "dma.h"

int main(void)
{
    // Configurar PA1 como entrada analogica
    init_adc_pin();

    // Configurar ADC1
    init_adc1();

    // Configurar DMA1 para guardar datos en RAM
    init_dma1();

    // Iniciar las conversiones del ADC
    adc_iniciar();

    while (1)
    {
        // El DMA transfiere automaticamente
        // los datos del ADC hacia la RAM.
        __NOP();
    }
}