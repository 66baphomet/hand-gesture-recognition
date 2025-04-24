import pyttsx3

def safe_speech():
    try:
        engine = pyttsx3.init()
        voices = engine.getProperty('voices')
        engine.setProperty('voice', voices[1].id)#
        engine.setProperty('rate', 150)
        engine.say("Can I have a dozen of eggs.")
        engine.runAndWait()
        engine.stop()
    except TypeError as e:
        if 'catching classes that do not inherit from BaseException' in str(e):
            # Ignore this specific TypeError without crashing the program
            print("Caught and ignored error: ", str(e))
        else:
            raise  # Re-raise other TypeErrors if necessary
    except Exception as e:
        # Catch any other exceptions and print/log them
        print("Error occurred:", type(e).__name__, "-", str(e))

# Call the safe_speech function
safe_speech()