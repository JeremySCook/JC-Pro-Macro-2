// Define button states (inverted logic for LOW = pressed)
bool SW1 = HIGH, SW2 = HIGH, SW3 = HIGH, SW4 = HIGH, SW5 = HIGH, SW6 = HIGH, SW7 = HIGH, SW8 = HIGH, SW9 = HIGH;
bool buttonHeld[9] = {false, false, false, false, false, false, false, false, false}; // Track button hold states

// Encoder variables
int16_t encoderPosition = 0;
Encoder myEnc(1, 0); // Pins 1 and 0 for the encoder

int buttonPins[9] = {4, 15, A0, A1, A2, A3, 14, 16, 10}; // Button pin assignments

void checkButtonActions() {
    for (int i = 0; i < 9; i++) {
        int currentState = digitalRead(buttonPins[i]);

        // When button is pressed
        if (currentState == LOW && !buttonHeld[i]) {
            buttonHeld[i] = true;
            Serial.print("{\"button\":");
            Serial.print(i + 1);
            Serial.println(", \"event\":\"pressed\"}");
            setPixelColor(i - 1, buttonConfigs[i].colorOnPress[0], buttonConfigs[i].colorOnPress[1], buttonConfigs[i].colorOnPress[2]);
            executeButtonAction(i);  // Execute the button action
        }

        // When button is released
        if (currentState == HIGH && buttonHeld[i]) {
            buttonHeld[i] = false;
            Serial.print("{\"button\":");
            Serial.print(i + 1);
            Serial.println(", \"event\":\"released\"}");
            setPixelColor(i - 1, buttonConfigs[i].color[0], buttonConfigs[i].color[1], buttonConfigs[i].color[2]);
        }
    }
}

void checkEncoderActions() {
    int16_t newPosition = myEnc.read();
    if (newPosition > encoderPosition) {
        Serial.println("{\"encoder\":\"increment\"}"); // JSON output for increment action
        executeEncoderAction(encoderConfigs[0]);
        encoderPosition = newPosition;
    }
    if (newPosition < encoderPosition) {
        Serial.println("{\"encoder\":\"decrement\"}"); // JSON output for decrement action
        executeEncoderAction(encoderConfigs[1]);
        encoderPosition = newPosition;
    }
    delay(50);
}

void executeHIDAction(const char* action, const char* keys, const char* modifiers, int x = 0, int y = 0, bool hasMouseAction = false) {
    // Check if the action type is "constant" and map string to HID keycode
    if (strcmp(action, "const") == 0) {
      if (strcmp(keys, "UpArrow") == 0) {
            Keyboard.press(HID_KEYBOARD_UPARROW);
        } else if (strcmp(keys, "DownArrow") == 0) {
            Keyboard.press(HID_KEYBOARD_DOWNARROW);
        } else if (strcmp(keys, "LeftArrow") == 0) {
            Keyboard.press(HID_KEYBOARD_LEFTARROW);
        } else if (strcmp(keys, "RightArrow") == 0) {
            Keyboard.press(HID_KEYBOARD_RIGHTARROW);
        } else if (strcmp(keys, "Enter") == 0) {
            Keyboard.press(KEY_ENTER);
        } else {
            Serial.print("{\"error\":\"Invalid constant: ");
            Serial.print(keys);
            Serial.println("\"}");
            return;
        }
        delay(100); // Short delay for key press
        Keyboard.releaseAll();
    }
    // Handle "key" action to press any key provided in the config
    else if (strcmp(action, "key") == 0) {
        // Handle modifiers if any
        if (strstr(modifiers, "Ctrl")) Keyboard.press(KEY_LEFT_CTRL);
        if (strstr(modifiers, "Shift")) Keyboard.press(KEY_LEFT_SHIFT);
        if (strstr(modifiers, "Alt")) Keyboard.press(KEY_LEFT_ALT);

        // Directly press the specified key as a character
            // Loop over each character in keys and press it
        for (int i = 0; i < strlen(keys); i++) {
            Keyboard.press(keys[i]);  // Press each character in the string
            delay(50);  // Optional small delay between each key press
        }
        delay(100);  // Short delay for key press
        Keyboard.releaseAll();
    }
    // Handle mouse actions if needed
    else if (hasMouseAction && strcmp(action, "mouse") == 0) {
        Mouse.move(x, y);
    }
}

void executeButtonAction(int buttonIndex) {
    ButtonConfig config = buttonConfigs[buttonIndex];    
    executeHIDAction(config.action, config.keys, config.modifiers, config.x, config.y, true);    
}

void executeEncoderAction(const EncoderConfig &config) {
    executeHIDAction(config.action, config.keys, config.modifiers);
}
