#include "gd32e23x.h"

#include "FreeRTOS.h"
#include "task.h"

#define LEDPORT     GPIOB
#define LEDPIN      GPIO_PIN_1
#define LED_CLOCK   RCU_GPIOB

static void
task1(void *args __attribute((unused))) {

	for (;;) {
		gpio_bit_toggle(LEDPORT, LEDPIN);
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

static void
task2(void *args __attribute((unused))) {

	for (;;) {
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


int main(void)
{
    rcu_periph_clock_enable(LED_CLOCK);

    /* set output as output */
    gpio_mode_set(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
    gpio_output_options_set(LEDPORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LEDPIN);

	xTaskCreate(task1,"LED", 100, NULL, configMAX_PRIORITIES-1, NULL);
	xTaskCreate(task2,"WAIT", 100, NULL, configMAX_PRIORITIES-2, NULL);
	vTaskStartScheduler();

    while (1)
    {
    }
}
