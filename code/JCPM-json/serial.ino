#include <ArduinoJson.h>
#include <EEPROM.h>

// Handle the serial commands
void handleSerialInput() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Read input from serial
    input.trim();  // Remove any leading/trailing whitespaces or newlines

    if (input.length() == 0) {
      // Manually create JSON error response
      Serial.println("{\"error\":\"Empty input\"}");
      return;
    }

    // Debug message to show the input received
    //Serial.print("{\"debug\":\"Received input: ");
    //Serial.print(input);
    //Serial.println("\"}");

    // Create a JSON document for parsing
    StaticJsonDocument<512> doc;  // Define a smaller, fixed-size JSON document
    //Serial.print("{\"status\":\"Free memory: ");
    //Serial.print(freeMemory());
    //Serial.println("\"}");

    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      // Output the specific deserialization error in JSON format
      Serial.print("{\"error\":\"Deserialization error: ");
      Serial.print(error.c_str());
      Serial.println("\"}");
      return;
    }

    // Handle "HELLO" command
    if (doc["command"] == "HELLO") {      
      Serial.println("{\"response\":\"ok\"}");
    }

    // Handle "RESET_EEPROM" command
    else if (doc["command"] == "RESET_EEPROM") {
      resetEEPROM();  // Call the reset function
      // Send confirmation message
      Serial.println("{\"response\":\"success\"}");
    }

    // Handle "SET_COLOR" command for NeoPixels
    else if (doc["command"] == "SET_COLOR") {
      int pixel = doc["pixel"].as<int>();  // Extract the pixel index
      JsonArray color = doc["color"];      // Extract the color array
      
      if (color.size() == 3) {  // Ensure we have an RGB color
        int r = color[0];
        int g = color[1];
        int b = color[2];
        
        // Set the NeoPixel color
        setPixelColor(pixel, r, g, b);
        
        // Send confirmation message
        Serial.print("{\"response\":\"success");
        Serial.print(pixel);
        Serial.println("\"}");
      } else {
        // Send error if color array is invalid
        Serial.println("{\"error\":\"Invalid color array\"}");
      }
    }

    // Handle "SET" command for general configuration, buttons, and encoder
       else if (doc["command"] == "SET") {
      // General Config
      JsonObject generalConfig = doc["generalConfig"];
      buttonConfigs[0].color[0] = generalConfig["defaultColor"][0];
      buttonConfigs[0].color[1] = generalConfig["defaultColor"][1];
      buttonConfigs[0].color[2] = generalConfig["defaultColor"][2];

      // Button Configurations
      JsonObject buttons = doc["buttons"];
      for (int i = 0; i < 9; i++) {
          JsonObject button = buttons[String(i)];
          strcpy(buttonConfigs[i].action, button["action"]);
          strcpy(buttonConfigs[i].keys, button["keys"]);
          strcpy(buttonConfigs[i].modifiers, button["modifiers"]);
          buttonConfigs[i].x = button["x"];
          buttonConfigs[i].y = button["y"];
          buttonConfigs[i].color[0] = button["color"][0];
          buttonConfigs[i].color[1] = button["color"][1];
          buttonConfigs[i].color[2] = button["color"][2];

          // Only set colorOnPress if it exists in the JSON
          if (button.containsKey("colorOnPress")) {
              buttonConfigs[i].colorOnPress[0] = button["colorOnPress"][0];
              buttonConfigs[i].colorOnPress[1] = button["colorOnPress"][1];
              buttonConfigs[i].colorOnPress[2] = button["colorOnPress"][2];
          } else {
              buttonConfigs[i].colorOnPress[0] = buttonConfigs[i].color[0];  // Fallback to normal color
              buttonConfigs[i].colorOnPress[1] = buttonConfigs[i].color[1];
              buttonConfigs[i].colorOnPress[2] = buttonConfigs[i].color[2];
          }
      }

      // Encoder Config
      JsonObject encoderConfig = doc["encoder"];
      strcpy(encoderConfigs[0].action, encoderConfig["increment"]["action"]);
      strcpy(encoderConfigs[0].keys, encoderConfig["increment"]["keys"]);
      strcpy(encoderConfigs[0].modifiers, encoderConfig["increment"]["modifiers"]);

      strcpy(encoderConfigs[1].action, encoderConfig["decrement"]["action"]);
      strcpy(encoderConfigs[1].keys, encoderConfig["decrement"]["keys"]);
      strcpy(encoderConfigs[1].modifiers, encoderConfig["decrement"]["modifiers"]);

      Serial.println("{\"response\":\"set ok\"}");
    }
 
    // Handle "GET" command for button configuration
    else if (doc["command"] == "GET") {
      int buttonIndex = doc["button"].as<int>();   // Button index

      if (buttonIndex >= 0 && buttonIndex < 9) {
        // Manually create JSON response for GET
        Serial.print("{\"button\":");
        Serial.print(buttonIndex);

        ButtonConfig config = buttonConfigs[buttonIndex];

        Serial.print(",\"config\":{\"action\":\"");
        Serial.print(config.action);
        Serial.print("\",\"keys\":\"");
        Serial.print(config.keys);
        Serial.print("\",\"modifiers\":\"");
        Serial.print(config.modifiers);
        Serial.print("\",\"x\":");
        Serial.print(config.x);
        Serial.print(",\"y\":");
        Serial.print(config.y);

        Serial.print(",\"color\":[");
        Serial.print(config.color[0]);
        Serial.print(",");
        Serial.print(config.color[1]);
        Serial.print(",");
        Serial.print(config.color[2]);
        Serial.print("],\"colorOnPress\":[");

        Serial.print(config.colorOnPress[0]);
        Serial.print(",");
        Serial.print(config.colorOnPress[1]);
        Serial.print(",");
        Serial.print(config.colorOnPress[2]);
        Serial.println("]}}");

      } else {
        // Manually create JSON error response for invalid button index
        Serial.println("{\"error\":\"Invalid button index\"}");
      }
    }

    // Unknown command
    else {
      // Manually create JSON error response for unknown command
      Serial.println("{\"error\":\"Unknown command\"}");
    }
  }
}
  