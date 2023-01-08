/*
To implement this behavior in your Arduino code, you can use the sleep() function 
from the esp32-hal-sleep.h library, which is part of the ESP32 Arduino core. 
This function will put the ESP32 into a deep sleep mode, which consumes very 
little power and allows you to wake the device using one of its wakeup sources.

To configure the wakeup source, you can use the esp_sleep_enable_ext0_wakeup() 
function, which allows you to specify a pin as the wakeup source. When the 
pin goes from a low to high level, the ESP32 will wake up from deep sleep.

Here's an example of how you can use these functions to put the 
ESP32 into sleep mode and wake it up using the RTC pin:
*/

#include <esp32-hal-sleep.h>

void setup() {
  // Configure the RTC pin as the wakeup source
  esp_sleep_enable_ext0_wakeup(RTC_PIN, LOW);

  // Put the ESP32 into deep sleep mode
  sleep();
}

void loop() {
  // The code in this function will not be executed, as the ESP32
  // will be in deep sleep mode until the RTC pin goes high
}

/*
When the RTC pin goes from low to high, the ESP32 will wake up from 
deep sleep and begin executing the code in the setup() function again. 
You can then add any additional code that you want to run after the 
wakeup in the loop() function.
*/
