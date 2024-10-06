#include <EEPROM.h>
#include <ArduinoJson.h>

// Load configuration from EEPROM
void loadConfigFromEEPROM() {
  int configOffset = 0;
  EEPROM.get(configOffset, generalConfig);
  EEPROM.get(configOffset + sizeof(GeneralConfig), buttonConfigs);

  // Output loaded configuration for debugging  
  Serial.println("{\"status\":\"Loaded configuration from EEPROM.\"}");

  Serial.print("{\"buttons\":[");  
  for (int i = 0; i < 9; i++) {
    Serial.print("{\"button\":");
    Serial.print(i);
    Serial.print(",\"action\":\"");
    Serial.print(buttonConfigs[i].action);
    Serial.print("\"}");

    if (i < 8) {
      Serial.print(",");  // Add a comma after each button except the last one
    }
  }
  
  Serial.println("]}");  // Close the JSON array and object
}

// Save configuration to EEPROM
void saveConfigToEEPROM() {
  int configOffset = 0;
  EEPROM.put(configOffset, generalConfig);
  EEPROM.put(configOffset + sizeof(GeneralConfig), buttonConfigs);

  Serial.println("{\"response\":\"Configuration saved to EEPROM.\"}");
}

void resetEEPROM() {
  int eepromSize = EEPROM.length();

  for (int i = 0; i < eepromSize; i++) {
    EEPROM.write(i, 0);  // Write zeros to the entire EEPROM
  }
  
  Serial.println("{\"response\":\"EEPROM reset completed\"}");

  asm volatile ("jmp 0");  // Inline assembly to jump to address 0 (reset vector)
}
