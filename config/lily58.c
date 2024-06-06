#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(lily58, LOG_LEVEL_DBG);

#define GPIO_PIN 21  // Используйте правильный номер пина
#define GPIO_PORT DT_LABEL(DT_NODELABEL(gpio0))

void board_init(void) {
    const struct device *dev;
    int ret;

    dev = device_get_binding(GPIO_PORT);
    if (dev == NULL) {
        LOG_ERR("Failed to get binding for GPIO device");
        return;
    }

    ret = gpio_pin_configure(dev, GPIO_PIN, GPIO_OUTPUT_ACTIVE | GPIO_ACTIVE_HIGH);
    if (ret < 0) {
        LOG_ERR("Failed to configure GPIO pin");
        return;
    }

    while (1) {
        gpio_pin_toggle(dev, GPIO_PIN);
        LOG_INF("GPIO Pin toggled");
        k_sleep(K_MSEC(1000));
    }
}

SYS_INIT(board_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
