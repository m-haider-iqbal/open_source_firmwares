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

'''
This code will flash the LED connected to pin D13 on the board 10 times, 
with a delay of 0.5 seconds between each on and off cycle.

To use this code, you will need to install the necessary libraries (board and digitalio) and 
connect an LED to pin D13 on your board. You will also need 
to upload the code to your board using the Arduino IDE.

'''
