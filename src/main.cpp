#include <Arduino.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
// #include "nvs_flash.h"
#include "driver/gpio.h"

#define BLINK_GPIO_BLUE GPIO_NUM_2 // Blue LED is onboard ESP32
#define BLINK_GPIO_RED GPIO_NUM_16 // Red LED is an external connected to GPIO 16 with a 220 ohm resistor

// declare tasks upfront
void taskSerialPrint(void * pvParameter);
void taskBlinkBlueLED(void * pvParameter);
void taskBlinkRedLED(void * pvParameter);

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  xTaskCreate(
    taskSerialPrint,
    "TaskSerialPrint",
    configMINIMAL_STACK_SIZE,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    taskBlinkRedLED,
    "TaskBlinkRedLED",
    configMINIMAL_STACK_SIZE,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    taskBlinkBlueLED,
    "TaskBlinkBlueLED",
    configMINIMAL_STACK_SIZE,
    NULL,
    1,
    NULL
  );
}

void loop() 
{
 delay(1000);
}

void taskSerialPrint(void *pvParameter)
{
  for(;;)
  {
    Serial.println("Task 1 - Serial Print Text");
    delay(1000);
  }
  
  Serial.println("Ending Task 1");
  vTaskDelete(NULL);
}

void taskBlinkBlueLED(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO_BLUE);
    gpio_set_direction(BLINK_GPIO_BLUE, GPIO_MODE_OUTPUT);

    for (;;)
    {
      Serial.println("Task 2 - Blue LED ON - GPIO 2");
      gpio_set_level(BLINK_GPIO_BLUE, 1);
      vTaskDelay(1000 / portTICK_RATE_MS);
      Serial.println("Task 2 - Blue LED OFF - GPIO 2");
      gpio_set_level(BLINK_GPIO_BLUE, 0);
      vTaskDelay(1000 / portTICK_RATE_MS);
    }

  Serial.println("Ending Task 2");
  vTaskDelete(NULL);
}

void taskBlinkRedLED(void *pvParameter)
{
  gpio_pad_select_gpio(BLINK_GPIO_RED);
  gpio_set_direction(BLINK_GPIO_RED, GPIO_MODE_OUTPUT);

  for(;;)
  {
    Serial.println("Task 3 - Red LED ON - GPIO 16");
    gpio_set_level(BLINK_GPIO_RED, 1);
    vTaskDelay(1000 / portTICK_RATE_MS);
    Serial.println("Task 3 - Red LED OFF - GPIO 16");
    gpio_set_level(BLINK_GPIO_RED, 0);
    vTaskDelay(1000 / portTICK_RATE_MS);
  }

  Serial.println("Ending Task 3");
  vTaskDelete(NULL);
}