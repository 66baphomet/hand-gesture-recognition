import serial
import time
import os
import queue
import sounddevice as sd
import vosk
import sys
import json

MODEL_PATH = "vosk-model-small-en-us-0.15"
SAMPLE_RATE = 16000
q = queue.Queue()

def callback(indata, frames, time_, status):
    if status:
        print(status, file=sys.stderr)
    q.put(bytes(indata))

def main():
    # Initialize serial port
    try:
        arduino = serial.Serial('COM3 ', 9600, timeout=1)  # Replace COM3 with your actual port
        time.sleep(2)  # Give Arduino time to reset
    except Exception as e:
        print(f"Error connecting to Arduino: {e}")
        return

    if not os.path.exists(MODEL_PATH):
        print("Model not found. Download and unzip it first.")
        return

    model = vosk.Model(MODEL_PATH)
    recognizer = vosk.KaldiRecognizer(model, SAMPLE_RATE)

    with sd.RawInputStream(samplerate=SAMPLE_RATE, blocksize=8000, dtype='int16',
                           channels=1, callback=callback):
        print("🎤 Speak into the microphone (Ctrl+C to stop)...")
        try:
            while True:
                data = q.get()
                if recognizer.AcceptWaveform(data):
                    result = json.loads(recognizer.Result())
                    text = result.get("text", "")
                    if text:
                        print("You said:", text)
                        arduino.write((text + "\n").encode())  # Send to Arduino
        except KeyboardInterrupt:
            print("\n🛑 Stopped.")
        finally:
            arduino.close()

if __name__ == "__main__":
    main()
