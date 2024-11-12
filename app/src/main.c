#include "common_defines.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/common.h>
#define LED_PIN GPIO13
#define LED_PORT GPIOC

static inline void rcc_setup(void){
    rcc_clock_setup_in_hsi_out_48mhz();
}
static inline void gpio_setup(void){
    rcc_periph_clock_enable (RCC_GPIOC);
    gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);


}
static inline void delay_cycle(uint32_t cycles){
    for (uint32_t i = 0; i< cycles; i++){
        __asm__("nop");
    }
}

int main(void){
    rcc_setup();
    gpio_setup();
    while(1){
        gpio_toggle(LED_PORT, LED_PIN);
        delay_cycle(1000000);

    }
    return 0;
}