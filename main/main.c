#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "blink.h"

#define LED_GPIO    GPIO_NUM_18
#define LED_LEVEL   0

static const char *BLINK_MODES[] = { "UNDEFINED", "OFF", "ON", "TOGGLE", "4HZ", "2HZ", "1HZ", "FADEIN", "FADEOUT", "BREATH" };

void app_main() {
    blink_t mode = BLINK_ON;
    uint8_t led;

    ESP_ERROR_CHECK(blink_init());
    ESP_ERROR_CHECK(blink_add(GPIO_NUM_4, LED_LEVEL, NULL));
    ESP_ERROR_CHECK(blink_add(GPIO_NUM_5, LED_LEVEL, NULL));
    ESP_ERROR_CHECK(blink_add(GPIO_NUM_6, LED_LEVEL, NULL));
    ESP_ERROR_CHECK(blink_add(LED_GPIO, LED_LEVEL, &led));

    ESP_ERROR_CHECK(blink_update(0, BLINK_FADEIN, 256));
    ESP_ERROR_CHECK(blink_update(1, BLINK_FADEOUT, 256));
    ESP_ERROR_CHECK(blink_update(2, BLINK_BREATH, 256));

    for (;;) {
        ESP_ERROR_CHECK(blink_update(led, mode, mode < BLINK_FADEIN ? 128 : 256));
        printf("LED blinks %s\n", BLINK_MODES[mode]);
        vTaskDelay(pdMS_TO_TICKS(5000));
        if (++mode > BLINK_BREATH)
            mode = BLINK_OFF;
    }
}
