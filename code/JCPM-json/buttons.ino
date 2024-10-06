// Define buttons and button states (inverted logic for LOW = pressed)
bool SW1 = HIGH;
bool SW2 = HIGH;
bool SW3 = HIGH;
bool SW4 = HIGH;
bool SW5 = HIGH;
bool SW6 = HIGH;
bool SW7 = HIGH;
bool SW8 = HIGH;
bool SW9 = HIGH;

// Define states to track when buttons are held or released
bool buttonHeld[9] = {false, false, false, false, false, false, false, false, false};

//Encoder vars
int16_t encoderPosition = 0;   // Tracks position change


// Encoder setup
Encoder myEnc(1, 0); // Pin 1 and 0 for the encoder (adjust if needed)

// Check button actions
// Function to check and update button states
void checkButtonActions() {
  int buttonPins[9] = {4, 15, A0, A1, A2, A3, 14, 16, 10};  // Array of button pin numbers

  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
    int currentState = digitalRead(buttonPins[i]);  // Read the current state of each button

    // Button press detected (LOW state and not already held)
    if (currentState == LOW && !buttonHeld[i]) {
      buttonHeld[i] = true;  // Mark button as held
      Serial.print("{\"button\":");
      Serial.print(i + 1);  // JSON output for button press
      Serial.println(", \"event\":\"pressed\"}");

      executeButtonAction(i);  // Execute the button action when pressed
    }

    // Button release detected (HIGH state and was previously held)
    if (currentState == HIGH && buttonHeld[i]) {
      buttonHeld[i] = false;  // Reset button held state
      Serial.print("{\"button\":");
      Serial.print(i + 1);  // JSON output for button release
      Serial.println(", \"event\":\"released\"}");
    }
  }
}

void checkEncoderActions() {
  int16_t newPosition = myEnc.read();  // Read the encoder position

  // Detect if the encoder has moved forward
  if (newPosition > encoderPosition) { 
    Serial.println("{\"encoder\":\"increment\"}");  // Send JSON output for increment
    encoderPosition = newPosition;  // Update the last known position
  }

  // Detect if the encoder has moved backward
  if (newPosition < encoderPosition) {
    Serial.println("{\"encoder\":\"decrement\"}");  // Send JSON output for decrement
    encoderPosition = newPosition;  // Update the last known position
  }

  delay(50);  // Small delay to allow more frequent checks and avoid missing pulses
}

// Define the executeButtonAction function
void executeButtonAction(int buttonIndex) {
  ButtonConfig config = buttonConfigs[buttonIndex];

  // Set the LED color to "press" color
  setPixelColor(buttonIndex, config.colorOnPress[0], config.colorOnPress[1], config.colorOnPress[2]);

  // Execute the HID action
  if (strcmp(config.action, "key") == 0) {
    // Handle key presses with modifiers
    if (strstr(config.modifiers, "Ctrl")) Keyboard.press(KEY_LEFT_CTRL);
    if (strstr(config.modifiers, "Shift")) Keyboard.press(KEY_LEFT_SHIFT);

    for (int i = 0; i < strlen(config.keys); i++) {
      Keyboard.press(config.keys[i]);
    }
    delay(100);
    Keyboard.releaseAll();
  } else if (strcmp(config.action, "mouse_move") == 0) {
    // Handle mouse movement
    Mouse.move(config.x, config.y);
  }

  // Reset the LED color to default after the action
  setPixelColor(buttonIndex, config.color[0], config.color[1], config.color[2]); 
}
