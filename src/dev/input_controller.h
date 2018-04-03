#ifndef input_controller_h
#define input_controller_h

//#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <driver/gpio.h>

#define ESP_INTR_FLAG_DEFAULT 0
#define GPIO_INPUT_IO_0 13
#define GPIO_INPUT_PIN_SEL (1ULL<<GPIO_INPUT_IO_0)

static xQueueHandle gpio_evt_queue = NULL;

volatile bool showDisplay = true;

void IRAM_ATTR gpio_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void toggleDisplay(void *args) {
    //showDisplay = !showDisplay;
    //Serial.printf("toggle display, display shown: %d\n", showDisplay);
}

static void gpio_task_example(void* arg) {
    gpio_num_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
            Serial.printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}

class InputController {

    gpio_num_t menuButtonPin;

    public:
        InputController(gpio_num_t button1) : menuButtonPin(button1) {}

    void init() {
        // pinMode(menuButtonPin, INPUT_PULLUP);
        // attachInterrupt(digitalPinToInterrupt(menuButtonPin), toggleDisplay, RISING);

        gpio_config_t io_conf;

        //disable interrupt
        // io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
        //interrupt of rising edge
        io_conf.intr_type = GPIO_INTR_POSEDGE;
        //bit mask of the pins, use GPIO4/5 here
        io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
        //set as input mode    
        io_conf.mode = GPIO_MODE_INPUT;
        //enable pull-up mode
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
        gpio_config(&io_conf);

        //change gpio intrrupt type for one pin
        gpio_set_intr_type(menuButtonPin, GPIO_INTR_ANYEDGE);

        //create a queue to handle gpio event from isr
        gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
        //start gpio task
        xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
        //install gpio isr service
        gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

        //hook isr handler for specific gpio pin
        gpio_isr_handler_add(menuButtonPin, gpio_isr_handler, (void*) menuButtonPin);
        
        //remove isr handler for gpio number.
        gpio_isr_handler_remove(menuButtonPin);
    }
};

#endif //input_controller_h