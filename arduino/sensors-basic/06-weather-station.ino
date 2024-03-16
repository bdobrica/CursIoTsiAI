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

const int waitSensorMs = 1000;
const int waitErrorMs = 1000; // Wait time before retrying sensor initialization
const int waitMs = 200; // Delay between readings

const int sensorPin = A6; // Light sensor PIN
const int ledPin = 4; // LED PIN
const int threshold = 200; // Light sensor threshold
const int soundPin = A2; // Sound sensor PIN
DHT dht(DHT20); // Create a DHT object using the DHT20 constant
BMP280 bmp280; // Create a BMP280 object, for accessing the sensor
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); // Create a U8X8 object
LIS3DHTR<TwoWire> LIS; // Configurează I2C în hardware

void setup(void)
{ // Setup, runs only once, after reset or power on:
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
    /**
     * Fill in the initialization code for the light and sound sensors.
     */
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    DEBUG_PRINTLN("LED conectat.");

    pinMode(sensorPin, INPUT); // Set light sensor pin as input
    DEBUG_PRINTLN("Light sensor conectat.");

    Wire.begin(); // Start I2C bus
    dht.begin(); // Start DHT sensor
    DEBUG_PRINTLN("DHT Sensor initialized."); // Print message to serial monitor

    /**
     * Fill in the initialization code for the pressure and accelerometer
     * sensors.
     */

    while (!bmp280.init()) // Initialize BMP280 sensor
    { // If sensor could not be initialized, print error message
        DEBUG_PRINTLN("Sensor could not be found. Check wiring.");
        delay(waitErrorMs); // Wait before retrying
    }
    DEBUG_PRINTLN("BMP280 Sensor initialized."); // Print message to serial monitor


    LIS.begin(Wire, 0x19);
    do {
        DEBUG_PRINTLN("Așteptare senzor...");
        delay(waitSensorMs);
    } while (!LIS);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
    DEBUG_PRINTLN("Accelerator senzor conectat.");

    u8x8.begin(); // Start OLED display
    u8x8.setPowerSave(0); // Set display power save mode to off
    u8x8.setFlipMode(1); // Set display flip mode to on
    DEBUG_PRINTLN("Display conectat."); // Print message to serial monitor
}

void loop(void)
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
    float light, sound, temp_h, humidity, temp_p, pressure, altitude;
    float accelX, accelY, accelZ;

    light = (float)analogRead(sensorPin) / 1023; // Read light sensor value
    /**
     * Fill in the code to read the sound sensor value.
     */
    temp_h = dht.readTemperature(); // Read temperature sensor value
    /**
     * Fill in the code to read the humidity sensor value.
     */
    temp_p = bmp280.getTemperature(); // Read temperature sensor value
    /**
     * Fill in the code to read the pressure sensor value.
     */
    altitude = bmp280.calcAltitude(pressure); // Read altitude sensor value
    accelX = LIS.getAccelerationX(); // Read X acceleration sensor value
    /**
     * Fill in the code to read the Y and Z acceleration sensor values.
     */

    /**
     * Fill in the code to print the sensor values in CSV format to the serial
     */ 

    DEBUG_PRINT("TMP_1: ");
    DEBUG_PRINT(temp_h);
    DEBUG_PRINT("TMP_2: ");
    DEBUG_PRINT(temp_p);
    DEBUG_PRINT("LIGHT: ");
    DEBUG_PRINT(light);
    DEBUG_PRINTLN("g");

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
