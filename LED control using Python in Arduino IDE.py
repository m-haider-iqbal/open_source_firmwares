# Import the necessary libraries
import time
import board
import digitalio

# Set up the pin connected to the LED
led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

# Flash the LED 10 times
for i in range(10):
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)

# Turn the LED off
led.value = False
