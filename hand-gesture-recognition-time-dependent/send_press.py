import serial
import keyboard
import time

# Set this to your Arduino COM port (check in Arduino IDE or Device Manager)
arduino_port = 'COM3'  # Change to 'COM4', 'COM8', etc. as needed
baud_rate = 9600

try:
    arduino = serial.Serial(arduino_port, baud_rate)
    time.sleep(2)  # Wait for Arduino to reset after connection
    print("Connected to Arduino.")

    print("Press 'S' to send message. Press 'ESC' to exit.")
    while True:
        if keyboard.is_pressed('s'):
            arduino.write(b'Hi\n')  # Send bytes
            print("Sent: Hello from Python!")
            time.sleep(0.5)  # debounce to avoid multiple sends

        if keyboard.is_pressed('esc'):
            print("Exiting...")
            break

except serial.SerialException:
    print(f"Could not open port {arduino_port}.")
except Exception as e:
    print(f"Error: {e}")
finally:
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
