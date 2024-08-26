// #include <Arduino.h>
// #include <Wire.h>
// #include "MAX30100_PulseOximeter.h"
// #include <Keypad.h>
// #include <Adafruit_Sensor.h>
// #include<Adafruit_BusIO_Register.h>
// #include <DHT.h>
// #include <WiFi.h>
// #include <PubSubClient.h>
// #include <WiFiClientSecure.h>
// #include <time.h>
// #include <LiquidCrystal_I2C.h>
// #include <Firebase_ESP_Client.h> 
// #include <addons/TokenHelper.h>
// #include <addons/RTDBHelper.h>
// #include <EEPROM.h> 

// LiquidCrystal_I2C lcd(0x27, 16, 2);
// #define DHTTYPE DHT22
// #define REPORTING_PERIOD_MS 1000
// #define DHT_REPORTING_PERIOD_MS 2000
// #define DISPLAY_CYCLE_MS 2000 // Cycle time for displaying messages (2 seconds)
// #define EEPROM_SIZE 512            
// #define REFRESH_TOKEN_ADDRESS 0 
// #define API_KEY "AIzaSyBTKdWN9NRb9JGhhY0rPWEc26jUljChyBw"
// #define FIRBASE_PROJECT_ID "flutter-844ee"
// #define USER_EMAIL "marr@gmail.com"
// #define USER_PASSWORD "123456"

// FirebaseData fbdo;
// FirebaseAuth auth;
// FirebaseConfig config;
// bool basicDataSent = false;
// unsigned long sendDataPrevMillis = 0;
// unsigned long calibrationStart; 
// bool signupOK = false;

// uint32_t tsLastReport = 0;
// uint32_t tsLastDHTRead = 0;
// uint32_t tsLastDisplayCycle = 0;
// int displayStep = 0;  // 0: Heart Rate & SpO2, 1: EE & Intensity & Water, 2: Temp & Humidity
// WiFiClientSecure wifiClient;
// PubSubClient mqttClient(wifiClient);

// const char* ssid = "...";
// const char* password = "password";
// const char* mqtt_broker = "6e3d738d12824ef5afc1d35354f43032.s1.eu.hivemq.cloud";
// const int mqtt_port = 8883;
// const char* mqtt_username = "RomaMagdy";
// const char* mqtt_password = "Password2912";

// const char* ntpServer = "pool.ntp.org";
// const long gmtOffset_sec = 0;
// const int daylightOffset_sec = 3600;

// const int ir_pin = 34;
// const int vib_motor_pin = 15;
// const int temp_pin = 4;
// int weight = 0;
// int age = 0;
// String input = "";
// char key;
// int MHR = 0;
// int ir ;
// int heartRate;
// int waterIntake;
// int spO2;
// float EE;
// float temp;
// float humidity;
// String intensity;

// PulseOximeter pox;
// DHT dht(temp_pin, DHTTYPE);

// const byte ROWS = 4;
// const byte COLS = 4;
// char keys[ROWS][COLS] = {
//     {'1', '2', '3', 'A'},
//     {'4', '5', '6', 'B'},
//     {'7', '8', '9', 'C'},
//     {'*', '0', '#', 'D'}
// };

// byte rowPins[ROWS] = {13, 12, 14, 27};
// byte colPins[COLS] = {26, 25, 33, 32};
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// void test() {
//     FirebaseJson json;
//     json.set("MHR", MHR);

//     // Send the JSON object to Firestore
//     if (Firebase.Firestore.patchDocument(&fbdo, FIRBASE_PROJECT_ID, "", "users/q9BOdIyhk7cGLStebc8T", json.raw(), "MHR")) {
//         Serial.println("Document updated successfully");
//     } else {
//         Serial.println(fbdo.errorReason());
//     }}


// void sendTofirebase(String collection, String documentId, String field, int value) {
//     if (Firebase.ready() && (millis() - sendDataPrevMillis >= 200 || sendDataPrevMillis == 0)) {
//         sendDataPrevMillis = millis();
//         FirebaseJson content;
//         content.set(field, value);
//         String documentPath = collection + "/" + documentId;
//         pox.shutdown();
//         if (Firebase.Firestore.createDocument(&fbdo, FIRBASE_PROJECT_ID, "", documentPath.c_str(), content.raw())) {
//             Serial.print("Successfully saved: ");
//             Serial.println(value);
//             Serial.print(fbdo.payload().c_str());
//             pox.resume();
//         } else {
//             Serial.print("FAILED: ");
//             Serial.println(fbdo.errorReason());
//         }
//     }
// }

// void sendTofirebase(String collection, String documentId, String field, double value){
//      if (Firebase.ready() && (millis() - sendDataPrevMillis >= 200 || sendDataPrevMillis == 0)) {
//         sendDataPrevMillis = millis();
//         FirebaseJson content;
//         content.set(field, value);
//         String documentPath = collection + "/" + documentId;
//         pox.shutdown();

// //   FirebaseFirestoreDocument document = firestore.collection(collection).document(documentId);
// //   document.setJSON(content);
//         // if (Firebase.Firestore.createDocument(&fbdo, FIRBASE_PROJECT_ID, "", documentPath.c_str(), content.raw())) {
//         //     Serial.print("Successfully saved: ");
//         //     Serial.println(value);
//         //     Serial.print(fbdo.payload().c_str());
//         //     pox.resume();
//         // } else {
//         //     Serial.print("FAILED: ");
//         //     Serial.println(fbdo.errorReason());
//         // }
//     }
// }
// void sendTofirebase(String collection, String documentId, String field, String value){
//      if (Firebase.ready() && (millis() - sendDataPrevMillis >= 200 || sendDataPrevMillis == 0)) {
//         sendDataPrevMillis = millis();
//         FirebaseJson content;
//         content.set(field, value);
//         String documentPath = collection + "/" + documentId;
//         pox.shutdown();
//         if (Firebase.Firestore.createDocument(&fbdo, FIRBASE_PROJECT_ID, "", documentPath.c_str(), content.raw())) {
//             Serial.print("Successfully saved: ");
//             Serial.println(value);
//             Serial.print(fbdo.payload().c_str());
//             pox.resume();
//         } else {
//             Serial.print("FAILED: ");
//             Serial.println(fbdo.errorReason());
//         }
//     }
// }
// void sendTofirebase(String collection, String documentId, String field, float value){
//      if (Firebase.ready() && (millis() - sendDataPrevMillis >= 200 || sendDataPrevMillis == 0)) {
//         sendDataPrevMillis = millis();
//         FirebaseJson content;
//         content.set(field, value);
//         String documentPath = collection + "/" + documentId;
//         pox.shutdown();
//         if (Firebase.Firestore.createDocument(&fbdo, FIRBASE_PROJECT_ID, "", documentPath.c_str(), content.raw())) {
//             Serial.print("Successfully saved: ");
//             Serial.println(value);
//             Serial.print(fbdo.payload().c_str());
//             pox.resume();
//         } else {
//             Serial.print("FAILED: ");
//             Serial.println(fbdo.errorReason());
//         }
//     }
// }


// void displayMessageWithDelay(String message, int row) {
//     lcd.setCursor(0, row);
//     lcd.print("                ");
//     lcd.setCursor(0, row);
//     lcd.print(message);
//     Serial.println(message);
// }

// void displayHeartRateAndSpO2() {
//     heartRate = pox.getHeartRate();
//     spO2 = pox.getSpO2();
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Heart rate: ");
//     lcd.print(heartRate);
//     lcd.setCursor(0, 1);
//     lcd.print("SpO2: ");
//     lcd.print(spO2);
//     char heartRateStr[8];
//     itoa(heartRate, heartRateStr, 10);
//     char spO2Str[8];
//     itoa(spO2, spO2Str, 10);
//     mqttClient.publish("sensor/heartRate", heartRateStr);
//     mqttClient.publish("sensor/spO2", spO2Str);
//     sendTofirebase("Sensor" ,"heartRateDoc","heartRate",  heartRate);
//     sendTofirebase("Sensor" ,"spO2Doc" ,"spO2", spO2);
// }

// int calculateWaterIntake(float intensityFactor, float temp, float humidity, int heartRate) {
//     // Base water intake based on intensity factor (in ml)
//     waterIntake = intensityFactor;

//     // Adjust for temperature
//     if (temp > 30.0) {
//         waterIntake *= 1.1;  // Increase by 10% if temperature > 30°C
//     }

//     // Adjust for humidity
//     if (humidity > 60.0) {
//         waterIntake *= 1.1;  // Increase by 10% if humidity > 60%
//     }

//     // Adjust for high heart rate
//     if (heartRate > 140) {
//         waterIntake *= 1.15;  // Increase by 15% if heart rate > 140 BPM
//     }
//     return waterIntake;  // Return the final water intake suggestion
// }

// void displayEEAndIntensity() {
//     heartRate = pox.getHeartRate();
//     if (age > 0 && weight > 0) {
//         // Example EE calculation: EE = (heartRate × weight × time × constant)
//         EE = heartRate * weight * 0.001; // Simplified formula for example
//         char eeStr[8];
//         dtostrf(EE, 4, 2, eeStr);  // Convert float to string

//         mqttClient.publish("sensor/EE", eeStr);
  

//         // Display workout intensity and water intake suggestion
//         float intensityFactor = 0.0;
//         float percentage = ((float)heartRate / MHR) * 100;
        
//         // Determine intensity and water intake suggestion
//         if (percentage < 50) {
//             intensityFactor = 250.0;  // Low intensity
//             displayMessageWithDelay("Low intensity", 1);
//             intensity = "Low";
//         } else if (percentage < 70) {
//             intensityFactor = 500.0;  // Moderate intensity
//             displayMessageWithDelay("Moderate", 1);
//             intensity = "Moderate";
          
//         } else {
//             intensityFactor = 750.0;  // High intensity
//             displayMessageWithDelay("High intensity", 1);
//             intensity = "High";
            
//         }

//         // Calculate the water intake suggestion
//         waterIntake = calculateWaterIntake(intensityFactor, temp, humidity, heartRate);
//            lcd.setCursor(0, 0);
//         lcd.print("Water:");
//         lcd.print(waterIntake);
//         lcd.print("ml/hr");
//         sendTofirebase("calc", "waterIntakeDoc" , "waterIntake" , waterIntake);
//         sendTofirebase("calc" ,"EEDoc", "EE", EE);
//         sendTofirebase("calc" ,"intensityDoc", "intensity", intensity);
     
//     } else {
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Enter weight/age");
//     }
// }

// void displayTemperatureAndHumidity() {
//     if (digitalRead(ir_pin) == LOW) {
//         temp = dht.readTemperature();
//         humidity = dht.readHumidity();
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Temp:");
//         lcd.print(temp);
//         lcd.print("*C");
//         lcd.setCursor(0, 1);
//         lcd.print("Humidity:");
//         lcd.print(humidity);
//         lcd.print("%");
//         char tempStr[8];
//         itoa(temp, tempStr, 10);
//         char humidityStr[8];
//         itoa(humidity, humidityStr, 10); 
//         mqttClient.publish("sensor/temperature", tempStr);
//         mqttClient.publish("sensor/humidity", humidityStr);
//         sendTofirebase("Sensor" ,"temperatureDoc", "temperature", temp);
//          sendTofirebase("Sensor", "humidityDoc","humidity", humidity);
//         if (isnan(temp) || isnan(humidity)) {
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             lcd.print("Failed to read!");
//             return;
//         }
  
//     }
// }



// void reconnect() {
//     while (!mqttClient.connected()) {
//         Serial.print("Attempting MQTT connection...");
//         if (mqttClient.connect("ESP32Client", mqtt_username, mqtt_password)) {
//             Serial.println("connected");
//             mqttClient.subscribe("sensor/heartRate");
//         } else {
//             Serial.print("failed, rc=");
//             Serial.print(mqttClient.state());
//             delay(5000);  // Wait before retrying
//         }
//     }
// }

// void callback(char* topic, byte* payload, unsigned int length) {
//     char msg[length + 1];
//     for (int i = 0; i < length; i++) {
//         msg[i] = (char)payload[i];
//     }
//     msg[length] = '\0';

//     int receivedHeartRate = atoi(msg);

//     //if(receivedHeartRate > MHR && MHR !=0){
//     if (receivedHeartRate > 120) {
//         digitalWrite(vib_motor_pin, LOW);  // Turn off motor if heart rate is high
//     }
// //}
//      else {
//         digitalWrite(vib_motor_pin, HIGH); // Turn on motor if heart rate is low
//     }
// }
// // void storeRefreshTokenInEEPROM(String refreshToken) {
// //     for (int i = 0; i < refreshToken.length(); ++i) {
// //         EEPROM.write(REFRESH_TOKEN_ADDRESS + i, refreshToken[i]);
// //     }
// //     EEPROM.write(REFRESH_TOKEN_ADDRESS + refreshToken.length(), '\0');  // Null-terminate the string
// //     EEPROM.commit();  // Save changes to EEPROM
// // }

// // String readRefreshTokenFromEEPROM() {
// //     String refreshToken;
// //     char ch;
// //     for (int i = 0; (ch = EEPROM.read(REFRESH_TOKEN_ADDRESS + i)) != '\0'; ++i) {
// //         refreshToken += ch;
// //     }
// //     return refreshToken;
// // }
// // void tokenStatusCallback(TokenInfo info) {
// //     Serial.printf("Token info: type = %s, status = %s\n", getTokenType(info.type).c_str(), getTokenStatus(info.status).c_str());
// // }
// void setup() {
//     Serial.begin(115200);
//     lcd.init();
//     lcd.backlight();

//     // Initialize WiFi
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.println("Connecting to WiFi...");
//     }
//     Serial.println("Connected to WiFi");
//     config.api_key = API_KEY;
//    auth.user.email = USER_EMAIL;  
//     auth.user.password = USER_PASSWORD;

  
// //   if(Firebase.signUp(&config, &auth, "", "" )){
// //     Serial.println("Sign up OK");
// //     signupOK = true;
// //   }else {
// //     Serial.printf("%s\n", config.signer.signupError.message.c_str());
// //   }
// //    config.token_status_callback = FirestoreTokenStatusCallback;

//   Firebase.begin(&config, &auth);
// //   Firebase.reconnectWiFi(true);
 
// //  String storedRefreshToken = readRefreshTokenFromEEPROM();

//     // if (storedRefreshToken.length() > 0) {
//     //     // Use stored refresh token
//     //     auth.token.refresh_token = storedRefreshToken.c_str();
//     //     Firebase.begin(&config, &auth);
//     // } else {
//     //     // Authenticate with email and password
//     //     auth.user.email = "roma.magdy.iv@gmail.com";  
//     //     auth.user.password = "AB123_456";       
//     //     Firebase.begin(&config, &auth);
//     // }

//     // if (Firebase.ready()) {
//     //     Serial.println("Firebase authenticated successfully!");

//     //     if (storedRefreshToken.length() == 0) {
//     //         String refreshToken = auth.token.refresh_token;
//     //         Serial.print("Refresh Token: ");
//     //         Serial.println(refreshToken);
//     //         storeRefreshTokenInEEPROM(refreshToken);
//     //     }
//     // } else {
//     //     Serial.printf("Firebase authentication failed: %s\n", config.signer.signupError.message.c_str());
//     // }


//     // Configure time
//     configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

//     // Wait for time to be set
//     struct tm timeinfo;
//     if (!getLocalTime(&timeinfo)) {
//         Serial.println("Failed to obtain time");
//         while (true);  // Halt if time synchronization fails
//     }
//     Serial.println(&timeinfo, "Time set: %A, %B %d %Y %H:%M:%S");

//     // Initialize MQTT
//     wifiClient.setInsecure();
//     mqttClient.setServer(mqtt_broker, mqtt_port);
//     mqttClient.setCallback(callback);

//     // Connect to MQTT
//     reconnect();

//     if (!pox.begin()) {
//         Serial.println("ERROR: Failed to initialize pulse oximeter");
//     }
//     dht.begin();

//     // Initialize pins
//     pinMode(ir_pin, INPUT);
//     pinMode(vib_motor_pin, OUTPUT);
//     digitalWrite(vib_motor_pin, HIGH);
//     lcd.clear();
//     lcd.setCursor(0, 0);
//       lcd.print("Enter A for age");
//      lcd.setCursor(0, 1);
//     lcd.print("B for weight");
//     Serial.println("Enter A for weight entry, B for age, * for reset: ");
// }

// void loop() {
//     // Ensure the MQTT client is connected
//     if (!mqttClient.connected()) {
//         reconnect();
//     }
//     mqttClient.loop(); // Process incoming messages and keep the connection alive

//     // Update Pulse Oximeter data
    
//         pox.update();

//     // Keypad input handling
//     key = keypad.getKey();
//     if (key) {
//         if (key == 'B') {
//             Serial.print("Your weight: ");
//             weight = input.toFloat();
//             Serial.println(weight);
//             displayMessageWithDelay("Your weight: " + input, 1);
//             input = "";  // Clear input after processing
//         } else if (key == 'A') {
//             Serial.print("Your age: ");
//             age = input.toInt();
//             Serial.println(age);
//             displayMessageWithDelay("Your age: " + input, 1);
//             input = "";  // Clear input after processing
//         } else if (key >= '0' && key <= '9') {
//             input.concat(key);
//             Serial.print("Input: ");
//             Serial.println(input);
//             lcd.clear();
//             displayMessageWithDelay("Input: " + input, 0);
//         } else if (key == '*') {
//             input = "";  // Clear input on *
//         }
//     }
//     if(MHR == 0 && age !=0){
//     MHR = 220 - age;
// }

//     if ( age !=0 && weight !=0 && MHR !=0 && basicDataSent == false)
//     {
//         //  sendTofirebase("users","t38R8nFIpMaMiNlS6Fidx9HqzNk2" , "MHR", MHR);
//         //  sendTofirebase("users","t38R8nFIpMaMiNlS6Fidx9HqzNk2","weight" ,weight);
//         //  sendTofirebase("users", "t38R8nFIpMaMiNlS6Fidx9HqzNk2","age", age);
//         test();
//          basicDataSent = true;
//     }

//     // Display cycle logic
//      ir = digitalRead(ir_pin);
  
//     if (ir == LOW) {
//         if (millis() - tsLastDisplayCycle > DISPLAY_CYCLE_MS) {
//             tsLastDisplayCycle = millis();
//             switch (displayStep) {
//                 case 0:
//                     displayHeartRateAndSpO2();
//                     break;
//                 case 1:
//                     displayEEAndIntensity();
//                     break;
//                 case 2:
//                     displayTemperatureAndHumidity();
//                     break;  
//             }
//             displayStep = (displayStep + 1) % 3;  // Cycle through 3 steps
//         }

//     }

// }

#include<Adafruit_BusIO_Register.h>
#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Keypad.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>
#include <Firebase_ESP_Client.h> 
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTTYPE DHT22
#define REPORTING_PERIOD_MS 1000
#define DHT_REPORTING_PERIOD_MS 2000
#define DISPLAY_CYCLE_MS 2000 // Cycle time for displaying messages (2 seconds)
#define API_KEY "AIzaSyBBBkTMKdegGRfGMRfWn_dTYR5S4EPp--g"
#define DATABASE_URL "https://iot-workout-tracker-default-rtdb.europe-west1.firebasedatabase.app/" 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool basicDataSent = false;
unsigned long sendDataPrevMillis = 0;
unsigned long calibrationStart; 
bool signupOK = false;

uint32_t tsLastReport = 0;
uint32_t tsLastDHTRead = 0;
uint32_t tsLastDisplayCycle = 0;
int displayStep = 0;  // 0: Heart Rate & SpO2, 1: EE & Intensity & Water, 2: Temp & Humidity
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

const char* ssid = "...";
const char* password = "password";
const char* mqtt_broker = "6e3d738d12824ef5afc1d35354f43032.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "RomaMagdy";
const char* mqtt_password = "Password2912";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

const int ir_pin = 34;
const int vib_motor_pin = 15;
const int temp_pin = 4;
double weight = 0;
int age = 0;
String input = "";
char key;
int MHR = 0;
int ir ;
int heartRate;
int waterIntake;
int spO2;
float EE;
float temp;
float humidity;
String intensity;

PulseOximeter pox;
DHT dht(temp_pin, DHTTYPE);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void sendTofirebase(String path , int value){
     if(Firebase.ready() && (millis()- sendDataPrevMillis>=200 || sendDataPrevMillis == 0)){
   sendDataPrevMillis = millis();
    pox.shutdown();
   if(Firebase.RTDB.setInt(&fbdo, path , value)){
     Serial.println();
     Serial.println(value);
     Serial.print("successfully saved to: " );
     Serial.print(fbdo.dataPath());
     Serial.print(" (");
     Serial.print(fbdo.dataType());
     Serial.println(")");
     pox.resume();
    calibrationStart = millis();
while (millis() - calibrationStart < 2000) { 
    pox.update();
    delay(100); 
}
   }
   else{
     Serial.print("FAILED: ");
     Serial.println(fbdo.errorReason());
   }
     }
}
void sendTofirebase(String path , double value){
     if(Firebase.ready() && (millis()- sendDataPrevMillis>200 || sendDataPrevMillis == 0)){
   sendDataPrevMillis = millis();

    pox.shutdown();

   if(Firebase.RTDB.setDouble(&fbdo, path , value)){
     Serial.println();
     Serial.println(value);
     Serial.print("successfully saved to: " );
     Serial.print(fbdo.dataPath());
     Serial.print(" (");
     Serial.print(fbdo.dataType());
     Serial.println(")");
     pox.resume();
         calibrationStart = millis();
while (millis() - calibrationStart < 2000) { 
    pox.update();
    delay(100); 
}
   }
   else{
     Serial.print("FAILED: ");
     Serial.println(fbdo.errorReason());
   }
     }
}
void sendTofirebase(String path , String value){
     if(Firebase.ready() && (millis()- sendDataPrevMillis>200 || sendDataPrevMillis == 0)){
   sendDataPrevMillis = millis();

    pox.shutdown();

   if(Firebase.RTDB.setString(&fbdo, path , value)){
     Serial.println();
     Serial.println(value);
     Serial.print("successfully saved to: " );
     Serial.print(fbdo.dataPath());
     Serial.print(" (");
     Serial.print(fbdo.dataType());
     Serial.println(")");
     pox.resume();
         calibrationStart = millis();
while (millis() - calibrationStart < 2000) { 
    pox.update();
    delay(100); 
}
   }
   else{
     Serial.print("FAILED: ");
     Serial.println(fbdo.errorReason());
   }
     }
}
void sendTofirebase(String path , float value){
     if(Firebase.ready() && (millis()- sendDataPrevMillis>200 || sendDataPrevMillis == 0)){
   sendDataPrevMillis = millis();
    pox.shutdown();
   if(Firebase.RTDB.setFloat(&fbdo, path , value)){
     Serial.println();
     Serial.println(value);
     Serial.print("successfully saved to: " );
     Serial.print(fbdo.dataPath());
     Serial.print(" (");
     Serial.print(fbdo.dataType());
     Serial.println(")");
     pox.resume();
         calibrationStart = millis();
while (millis() - calibrationStart < 2000) { 
    pox.update();
    delay(100); 
}
   }
   else{
     Serial.print("FAILED: ");
     Serial.println(fbdo.errorReason());
   }
     }
}


void displayMessageWithDelay(String message, int row) {
    lcd.setCursor(0, row);
    lcd.print("                ");
    lcd.setCursor(0, row);
    lcd.print(message);
    Serial.println(message);
}

void displayHeartRateAndSpO2() {
    heartRate = pox.getHeartRate();
    spO2 = pox.getSpO2();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart rate: ");
    lcd.print(heartRate);
    lcd.setCursor(0, 1);
    lcd.print("SpO2: ");
    lcd.print(spO2);
    char heartRateStr[8];
    itoa(heartRate, heartRateStr, 10);
    char spO2Str[8];
    itoa(spO2, spO2Str, 10);
    mqttClient.publish("sensor/heartRate", heartRateStr);
    mqttClient.publish("sensor/spO2", spO2Str);
    sendTofirebase("Sensor/heartRate", heartRate);
    sendTofirebase("Sensor/spO2", spO2);
}

int calculateWaterIntake(float intensityFactor, float temp, float humidity, int heartRate) {
    // Base water intake based on intensity factor (in ml)
    waterIntake = intensityFactor;

    // Adjust for temperature
    if (temp > 30.0) {
        waterIntake *= 1.1;  // Increase by 10% if temperature > 30°C
    }

    // Adjust for humidity
    if (humidity > 60.0) {
        waterIntake *= 1.1;  // Increase by 10% if humidity > 60%
    }

    // Adjust for high heart rate
    if (heartRate > 140) {
        waterIntake *= 1.15;  // Increase by 15% if heart rate > 140 BPM
    }
    return waterIntake;  // Return the final water intake suggestion
}

void displayEEAndIntensity() {
    heartRate = pox.getHeartRate();
    if (age > 0 && weight > 0) {
        // Example EE calculation: EE = (heartRate × weight × time × constant)
        EE = heartRate * weight * 0.001; // Simplified formula for example
        char eeStr[8];
        dtostrf(EE, 4, 2, eeStr);  // Convert float to string

        mqttClient.publish("sensor/EE", eeStr);
  

        // Display workout intensity and water intake suggestion
        float intensityFactor = 0.0;
        float percentage = ((float)heartRate / MHR) * 100;
        
        // Determine intensity and water intake suggestion
        if (percentage < 50) {
            intensityFactor = 250.0;  // Low intensity
            displayMessageWithDelay("Low intensity", 1);
            intensity = "Low";
        } else if (percentage < 70) {
            intensityFactor = 500.0;  // Moderate intensity
            displayMessageWithDelay("Moderate", 1);
            intensity = "Moderate";
          
        } else {
            intensityFactor = 750.0;  // High intensity
            displayMessageWithDelay("High intensity", 1);
            intensity = "High";
            
        }

        // Calculate the water intake suggestion
        waterIntake = calculateWaterIntake(intensityFactor, temp, humidity, heartRate);
           lcd.setCursor(0, 0);
        lcd.print("Water:");
        lcd.print(waterIntake);
        lcd.print("ml/hr");
        sendTofirebase("calc/waterIntake", waterIntake);
        sendTofirebase("calc/EE", EE);
        sendTofirebase("calc/intensity", intensity);
     
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter weight/age");
    }
}

void displayTemperatureAndHumidity() {
    if (digitalRead(ir_pin) == LOW) {
        temp = dht.readTemperature();
        humidity = dht.readHumidity();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(temp);
        lcd.print("*C");
        lcd.setCursor(0, 1);
        lcd.print("Humidity:");
        lcd.print(humidity);
        lcd.print("%");
        char tempStr[8];
        itoa(temp, tempStr, 10);
        char humidityStr[8];
        itoa(humidity, humidityStr, 10); 
        mqttClient.publish("sensor/temperature", tempStr);
        mqttClient.publish("sensor/humidity", humidityStr);
        sendTofirebase("Sensor/temperature", temp);
         sendTofirebase("Sensor/humidity", humidity);
        if (isnan(temp) || isnan(humidity)) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Failed to read!");
            return;
        }
  
    }
}



void reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("ESP32Client", mqtt_username, mqtt_password)) {
            Serial.println("connected");
            mqttClient.subscribe("sensor/heartRate");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            delay(5000);  // Wait before retrying
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    char msg[length + 1];
    for (int i = 0; i < length; i++) {
        msg[i] = (char)payload[i];
    }
    msg[length] = '\0';

    int receivedHeartRate = atoi(msg);

    //if(receivedHeartRate > MHR && MHR !=0){
    if (receivedHeartRate > 120) {
        digitalWrite(vib_motor_pin, LOW);  // Turn off motor if heart rate is high
    }
//}
     else {
        digitalWrite(vib_motor_pin, HIGH); // Turn on motor if heart rate is low
    }
}

void setup() {
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();

    // Initialize WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config, &auth, "", "" )){
    Serial.println("Sign up OK");
    signupOK = true;
  }else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

    // Configure time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Wait for time to be set
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        while (true);  // Halt if time synchronization fails
    }
    Serial.println(&timeinfo, "Time set: %A, %B %d %Y %H:%M:%S");

    // Initialize MQTT
    wifiClient.setInsecure();
    mqttClient.setServer(mqtt_broker, mqtt_port);
    mqttClient.setCallback(callback);

    // Connect to MQTT
    reconnect();

    if (!pox.begin()) {
        Serial.println("ERROR: Failed to initialize pulse oximeter");
    }
    dht.begin();

    // Initialize pins
    pinMode(ir_pin, INPUT);
    pinMode(vib_motor_pin, OUTPUT);
    digitalWrite(vib_motor_pin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
      lcd.print("Enter A for age");
     lcd.setCursor(0, 1);
    lcd.print("B for weight");
    Serial.println("Enter A for weight entry, B for age, * for reset: ");
}

void loop() {
    // Ensure the MQTT client is connected
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop(); // Process incoming messages and keep the connection alive

    // Update Pulse Oximeter data
    
        pox.update();

    // Keypad input handling
    key = keypad.getKey();
    if (key) {
        if (key == 'B') {
            Serial.print("Your weight: ");
            weight = input.toFloat();
            Serial.println(weight);
            displayMessageWithDelay("Your weight: " + input, 1);
            input = "";  // Clear input after processing
        } else if (key == 'A') {
            Serial.print("Your age: ");
            age = input.toInt();
            Serial.println(age);
            displayMessageWithDelay("Your age: " + input, 1);
            input = "";  // Clear input after processing
        } else if (key >= '0' && key <= '9') {
            input.concat(key);
            Serial.print("Input: ");
            Serial.println(input);
            lcd.clear();
            displayMessageWithDelay("Input: " + input, 0);
        } else if (key == '*') {
            input = "";  // Clear input on *
        }
    }
    if(MHR == 0 && age !=0){
    MHR = 220 - age;
}

    if ( age !=0 && weight !=0 && MHR !=0 && basicDataSent == false)
    {
         sendTofirebase("calc/MHR", MHR);
         sendTofirebase("Input/weight", weight);
         sendTofirebase("Input/age", age);
         basicDataSent = true;
    }

    // Display cycle logic
     ir = digitalRead(ir_pin);
  
    if (ir == LOW) {
        if (millis() - tsLastDisplayCycle > DISPLAY_CYCLE_MS) {
            tsLastDisplayCycle = millis();
            switch (displayStep) {
                case 0:
                    displayHeartRateAndSpO2();
                    break;
                case 1:
                    displayEEAndIntensity();
                    break;
                case 2:
                    displayTemperatureAndHumidity();
                    break;  
            }
            displayStep = (displayStep + 1) % 3;  // Cycle through 3 steps
        }

    }

}