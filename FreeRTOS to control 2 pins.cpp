// This code creates two tasks: relay1_task and relay2_task. 
// Each task toggles the corresponding relay every second. 
// A mutex is used to synchronize access to the relays.

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xSemaphore = NULL;

void relay1_task(void *pvParameters)
{
  for(;;)
  {
    if(xSemaphore != NULL)
    {
      // Wait for the semaphore to be available
      if(xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE)
      {
        // Toggle the relay
        digitalWrite(13, !digitalRead(13));

        // Release the semaphore
        xSemaphoreGive(xSemaphore);
      }
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void relay2_task(void *pvParameters)
{
  for(;;)
  {
    if(xSemaphore != NULL)
    {
      // Wait for the semaphore to be available
      if(xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE)
      {
        // Toggle the relay
        digitalWrite(12, !digitalRead(12));

        // Release the semaphore
        xSemaphoreGive(xSemaphore);
      }
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  // Create the semaphore
  xSemaphore = xSemaphoreCreateMutex();

  // Set the relay pins as output
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // Create the tasks
  xTaskCreate(relay1_task, "Relay1", 128, NULL, 2, NULL);
  xTaskCreate(relay2_task, "Relay2", 128, NULL, 2, NULL);
}

void loop()
{
  // Run the FreeRTOS scheduler
  vTaskStartScheduler();
}
