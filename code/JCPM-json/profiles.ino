#include <EEPROM.h>
#include <ArduinoJson.h>

// Load configuration from EEPROM
void loadConfigFromEEPROM() {
  int configOffset = 0;
  
  // Load general configuration
  EEPROM.get(configOffset, generalConfig);
  configOffset += sizeof(GeneralConfig);
  
  // Load button configurations
  EEPROM.get(configOffset, buttonConfigs);
  configOffset += sizeof(buttonConfigs);

  // Load encoder configurations
  EEPROM.get(configOffset, encoderConfigs);

  // Output loaded configuration for debugging  
  Serial.println("{\"status\":\"Loaded configuration from EEPROM.\"}");

  Serial.print("{\"buttons\":[");  
  for (int i = 0; i < 9; i++) {
    Serial.print("{\"button\":");
    Serial.print(i);
    Serial.print(",\"action\":\"");
    Serial.print(buttonConfigs[i].action);
    Serial.print("\"}");

    // Set the button's color if it has a color configured
    setPixelColor(i - 1, buttonConfigs[i].color[0], buttonConfigs[i].color[1], buttonConfigs[i].color[2]);


    if (i < 8) {
      Serial.print(",");  // Add a comma after each button except the last one
    }
  }
  
  Serial.println("]}");  // Close the JSON array and object

    // Print encoder configurations
  Serial.print("{\"encoder\":{\"increment\":{");
  Serial.print("\"action\":\"");
  Serial.print(encoderConfigs[0].action);
  Serial.print("\",\"keys\":\"");
  Serial.print(encoderConfigs[0].keys);
  Serial.print("\",\"modifiers\":\"");
  Serial.print(encoderConfigs[0].modifiers);
  Serial.print("\"},\"decrement\":{");

  Serial.print("\"action\":\"");
  Serial.print(encoderConfigs[1].action);
  Serial.print("\",\"keys\":\"");
  Serial.print(encoderConfigs[1].keys);
  Serial.print("\",\"modifiers\":\"");
  Serial.print(encoderConfigs[1].modifiers);
  Serial.println("\"}}}");
}

// Save configuration to EEPROM
void saveConfigToEEPROM() {
  int configOffset = 0;
  
  // Save general configuration
  EEPROM.put(configOffset, generalConfig);
  configOffset += sizeof(GeneralConfig);

  // Save button configurations
  EEPROM.put(configOffset, buttonConfigs);
  configOffset += sizeof(buttonConfigs);

  // Save encoder configurations
  EEPROM.put(configOffset, encoderConfigs);

  Serial.println("{\"response\":\"Configuration saved to EEPROM.\"}");
}

void resetEEPROM() {
  int eepromSize = EEPROM.length();

  for (int i = 0; i < eepromSize; i++) {
    EEPROM.write(i, 0);  // Write zeros to the entire EEPROM
  }
  
  Serial.println("{\"response\":\"EEPROM reset completed\"}");
}
