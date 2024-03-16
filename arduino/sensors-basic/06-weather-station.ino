/**
 * Weather Station
 * 
 * This sketch reads data from the light, sound, temperature, humidity, pressure
 * and accelerometer sensors and displays the values on a 128x64 OLED display,
 * while at the same time sending the data in CSV format to the serial monitor.
 * 
 * The output format is:
 *  light,sound,temp_h,humidity,temp_p,pressure,altitude,accelX,accelY,accelZ
 * 
 * With the following notes:
 * - light: light sensor value should be between 0 and 1
 * - sound: sound sensor value should be between 0 and 1
 * - temp_h: temperature from the DHT20 sensor
 * - temp_p: temperature from the BMP280 sensor
 * 
 */

#define DEBUG // Comment this line to disable debug output
#define DEBUG_BAUDS 115200 // Debug output baud rate
#ifdef DEBUG
    #define DEBUG_BEGIN Serial.begin(DEBUG_BAUDS)
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_BEGIN
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

/**
 * Include the required libraries.
 * These libraries need to be installed in the Arduino IDE. Go to "Sketch" ->
 * "Include Library" -> "Manage Libraries..." and search for the library name.
 * Then click "Install".
 */
#include <DHT.h> // "Grove Temperature and Humidity Sensor" library
#include <U8x8lib.h> // "U8G2" library
#include <Seeed_BMP280.h> // "Grove - Barometer Sensor BMP280" library
#include <LIS3DHTR.h> // "LIS3DHTR" library

const int waitErrorMs = 1000; // Wait time before retrying sensor initialization
const int waitMs = 200; // Delay between readings

const int sensorPin = A6; // Light sensor PIN
const int soundPin = A2; // Sound sensor PIN
DHT dht(DHT20); // Create a DHT object using the DHT20 constant
BMP280 bmp280; // Create a BMP280 object, for accessing the sensor
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); // Create a U8X8 object
LIS3DHTR<TwoWire> LIS; // Configurează I2C în hardware

void setup(void)
{ // Setup, runs only once, after reset or power on:
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    pinMode(sensorPin, INPUT); // Set light sensor pin as input
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
    Wire.begin(); // Start I2C bus
    dht.begin(); // Start DHT sensor
    while (!bmp280.init()) // Initialize BMP280 sensor
    { // If sensor could not be initialized, print error message
        DEBUG_PRINTLN("Sensor could not be found. Check wiring.");
        delay(waitErrorMs); // Wait before retrying
    }
    DEBUG_PRINTLN("Sensor initialized."); // Print message to serial monitor
    Wire.begin(); // Start I2C bus
    u8x8.begin(); // Start OLED display
    u8x8.setPowerSave(0); // Wake up OLED display
    u8x8.setFlipMode(1); // Rotate OLED display
    DEBUG_PRINTLN("Display initialized."); // Print message to serial monitor
    u8x8.begin(); // Start OLED display
    u8x8.setPowerSave(0); // Set display power save mode to off
    u8x8.setFlipMode(1); // Set display flip mode to on
    DEBUG_PRINTLN("Display conectat."); // Print message to serial monitor
    LIS.begin(Wire, 0x19);
    do {
        DEBUG_PRINTLN("Așteptare senzor...");
        delay(waitSensorMs);
    } while (!LIS);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
    DEBUG_PRINTLN("Senzor conectat.");
    u8x8.begin();
    u8x8.setPowerSave(0);
    u8x8.setFlipMode(1);
    DEBUG_PRINTLN("Display conectat.");
}

void loop(void)
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
    float light, sound, temp_h, humidity, temp_p, pressure, altitude;
    float accelX, accelY, accelZ;

    light = (float)analogRead(sensorPin) / 1023; // Read light sensor value
    sensorValue = analogRead(soundPin); // Read sound sensor value
    DEBUG_PRINT("Sensor Value: ");
    DEBUG_PRINTLN(sensorValue); // Print sensor value to serial monitor

    if (sensorValue > threshold)
    { // If sensor value is above threshold, turn on LED
        digitalWrite(ledPin, HIGH); // Turn on LED
        DEBUG_PRINTLN("LED ON"); // Print LED status to serial monitor
        delay(onTimeMs); // Keep LED on for a while
    }
    else
    { // If sensor value is below threshold, turn off LED
        digitalWrite(ledPin, LOW);
    }
    temp_h = dht.readTemperature(); // Read temperature sensor value
    float temperature, humidity; // Temperature and humidity variables
    temperature = dht.readTemperature(); // Read temperature, in Celsius
    humidity = dht.readHumidity(); // Read humidity, in percentage

    DEBUG_PRINT("Temperature: "); // Print temperature to serial monitor
    DEBUG_PRINT(temperature);
    DEBUG_PRINT("C, Humidity: "); // Print humidity to serial monitor
    DEBUG_PRINT(humidity);
    DEBUG_PRINTLN("%");

    u8x8.setFont(u8x8_font_chroma48medium8_r); // Set font
    u8x8.setCursor(0, 1); // Set cursor position on OLED display
    u8x8.print("Temp:"); // Print temperature to OLED display at cursor position
    u8x8.print(temperature); // Print temperature to OLED display. Cursor moves
                             // to the right after printing
    u8x8.print("C"); // Print "C" to OLED display
    u8x8.setCursor(0, 10); // Set cursor position on OLED display
    u8x8.print("Humi:"); // Print humidity to OLED display at cursor position
    u8x8.print(humidity); // Print humidity to OLED display. Cursor moves to the
                          // right after printing
    u8x8.print("%"); // Print "%" to OLED display
    u8x8.refreshDisplay(); // Refresh OLED display
    delay(waitMs); // Wait before reading again
    temp_p = bmp280.getTemperature(); // Read temperature sensor value
    float temperature, pressure, altitude; // Sensor variables
    temperature = bmp280.getTemperature(); // Read temperature, in Celsius
    pressure = bmp280.getPressure(); // Read pressure, in Pa
    altitude = bmp280.calcAltitude(pressure); // Calculate altitude, in meters

    DEBUG_PRINT("Temperature: "); // Print temperature to serial monitor
    DEBUG_PRINT(temperature);
    DEBUG_PRINT("C, Pressure: "); // Print pressure to serial monitor
    DEBUG_PRINT(pressure);
    DEBUG_PRINT("Pa, Altitude: "); // Print altitude to serial monitor
    DEBUG_PRINT(altitude);

    u8x8.setFont(u8x8_font_chroma48medium8_r); // Set font
    u8x8.setCursor(0, 1); // Set cursor position on OLED display
    u8x8.print("Temp:"); // Print temperature to OLED display at cursor position
    u8x8.print(temperature); // Print temperature to OLED display. Cursor moves
                             // to the right after printing
    u8x8.print("C"); // Print "C" to OLED display
    u8x8.setCursor(0, 10); // Set cursor position on OLED display
    u8x8.print("Pres:"); // Print pressure to OLED display at cursor position
    u8x8.print(pressure); // Print pressure to OLED display. Cursor moves to the
                          // right after printing
    u8x8.print("Pa"); // Print "Pa" to OLED display
    u8x8.setCursor(0, 19); // Set cursor position on OLED display
    u8x8.print("Alt :"); // Print altitude to OLED display at cursor position
    u8x8.print(altitude); // Print altitude to OLED display. Cursor moves to the
                          // right after printing
    u8x8.print("m"); // Print "m" to OLED display
    u8x8.refreshDisplay(); // Refresh OLED display
    delay(waitMs); // Wait before reading again
    altitude = bmp280.calcAltitude(pressure); // Read altitude sensor value
    accelX = LIS.getAccelerationX(); // Read X acceleration sensor value
    float x, y, z;
    x = LIS.getAccelerationX();
    y = LIS.getAccelerationY();
    z = LIS.getAccelerationZ();

    DEBUG_PRINT("X: ");
    DEBUG_PRINT(x);
    DEBUG_PRINT("g, Y: ");
    DEBUG_PRINT(y);
    DEBUG_PRINT("g, Z: ");
    DEBUG_PRINT(z);
    DEBUG_PRINTLN("g");

    u8x8.setFont(u8x8_font_chroma48medium8_r); // Set font
    u8x8.setCursor(0, 1); // Set cursor position on OLED display
    u8x8.print("X:"); // Print temperature to OLED display at cursor position
    u8x8.print(x); // Print temperature to OLED display. Cursor moves
                             // to the right after printing
    u8x8.print("g"); // Print "C" to OLED display
    u8x8.setCuror(0, 10); // Set cursor position on OLED display
    u8x8.print("Y:"); // Print pressure to OLED display at cursor position
    u8x8.print(y); // Print pressure to OLED display. Cursor moves to the
                          // right after printing
    u8x8.print("g"); // Print "Pa" to OLED display
    u8x8.setCursor(0, 19); // Set cursor position on OLED display
    u8x8.print("Z:"); // Print altitude to OLED display at cursor position
    u8x8.print(z); // Print altitude to OLED display. Cursor moves to the
                          // right after printing
    u8x8.print("g"); // Print "m" to OLED display
    u8x8.refreshDisplay(); // Refresh OLED display

    delay(waitMs);

    digitalWrite(ledPin, HIGH); // aprinde ledul
        // trimite datele prin interfața serială în format CSV, folosind virgula ca separator si 4 zecimale
        Serial.print(lightValue, 4); Serial.print(","); // trimite valoarea senzorului de lumină prin interfața serială
        Serial.print(soundValue, 4); Serial.print(","); // trimite valoarea senzorului de sunet prin interfața serială
        Serial.print(dhtTempValue, 4); Serial.print(","); // trimite valoarea temperaturii prin interfața serială
        Serial.print(dhtHumiValue, 4); Serial.print(","); // trimite valoarea umidității prin interfața serială
        Serial.print(bmpTempValue, 4); Serial.print(","); // trimite valoarea temperaturii prin interfața serială
        Serial.print(bmpPresValue, 4); Serial.print(","); // trimite valoarea presiunii prin interfața serială
        Serial.print(bmpAltitudeValue, 4); Serial.print(","); // trimite valoarea altitudinii prin interfața serială
        Serial.print(accX, 4); Serial.print(","); // trimite valoarea acceleratiei pe axa X prin interfața serială
        Serial.print(accY, 4); Serial.print(","); // trimite valoarea acceleratiei pe axa Y prin interfața serială
        Serial.println(accZ, 4); // trimite valoarea acceleratiei pe axa Z prin interfața serială
        digitalWrite(ledPin, LOW);

    u8x8.setFont(u8x8_font_chroma48medium8_r); // Set font
    u8x8.setCursor(0, 1); // Set cursor position on OLED display
    u8x8.print("TMP_1:"); u8x8.print(temp_h); u8x8.print("C"); // Print temperature to OLED display
    u8x8.setCursor(0, 10); // Set cursor position on OLED display // Print humidity to OLED display
    u8x8.print("HUMID:"); u8x8.print(humidity); u8x8.print("%"); // Print humidity to OLED display
    u8x8.setCursor(0, 19); // Set cursor position on OLED display
    u8x8.print("TMP_2:"); u8x8.print(temp_p); u8x8.print("C"); // Print temperature to OLED display
    u8x8.setCursor(0, 28); // Set cursor position on OLED display
    u8x8.print("PRESS:"); u8x8.print(pressure / 1000.0); u8x8.print("kPa");
    u8x8.setCursor(0, 37); // Set cursor position on OLED display
    u8x8.print("LIGHT:"); u8x8.print(light); // Print light to OLED display
    u8x8.setCursor(0, 46); // Set cursor position on OLED display
    u8x8.print("SOUND:"); u8x8.print(sound); // Print sound to OLED display
    u8x8.setCursor(0, 55); // Set cursor position on OLED display
    u8x8.print(accelX, 1); u8x8.print(" "); // Print X acceleration to OLED display
    u8x8.print(accelY, 1); u8x8.print(" "); // Print Y acceleration to OLED display
    u8x8.print(accelZ, 1); u8x8.print(" "); // Print Z acceleration to OLED display
    u8x8.refreshDisplay(); // Refresh OLED display
    delay(waitMs); // Wait before reading again
}
