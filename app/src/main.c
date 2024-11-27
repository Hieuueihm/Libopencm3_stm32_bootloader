#include "common_defines.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/systick.h>
#define LED_PIN GPIO13
#define LED_PORT GPIOC
#define CPU_FREQ (48000000)
#define SYSTICK_FREQ (1000)

volatile uint64_t ticks = 0;
void sys_tick_handler(void){
    ticks++;
}

static inline uint64_t get_ticks(void){
    return ticks;
}



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

static inline void systick_setup(void){
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable(); 
    systick_interrupt_enable(); 
}


int main(void){
    rcc_setup();
    gpio_setup();
    systick_setup();
    uint64_t start_time = get_ticks();
    while(1){
        if(get_ticks() - start_time >= 2000){
                gpio_toggle(LED_PORT, LED_PIN);
                start_time = get_ticks();
        }
       
        
    }
    return 0;
}