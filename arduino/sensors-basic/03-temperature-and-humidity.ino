/**
 * Digital Termometer and Hygrometer
 * 
 * This sketch reads temperature and humidity from a DHT20 sensor and displays
 * the values on a 128x64 OLED display.
 * 
 * The DHT20 sensor is connected to pin 3 and the OLED display is connected to
 * the I2C bus.
 * 
 * Configuration:
 * - DHT20 sensor: I2C bus (DHT20)
 * - OLED display: I2C bus (u8x8)
 * - Wait time: 200 ms (waitMs). Change this value to adjust the delay between
 *  readings.
 * 
 * The sensor values are read and printed to the serial monitor. The temperature
 * and humidity are displayed on the OLED display.
 * 
 * Requirements:
 * - the "Grove Temperature and Humidity Sensor" library is used to read the
 *   temperature and humidity values.
 * - the "U8G2" library is used to control the OLED display.
 * - the "Wire" library is used to control the I2C bus. It is included by
 *   default in the Arduino IDE.
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

#define DHTTYPE DHT20 // Temperature and humidity sensor type

const int waitMs = 200; // Delay between readings (ms)

DHT dht(DHTTYPE); // Create a DHT object using the DHTTYPE constant
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); // Create a U8X8 object

void setup(void)
{ // Setup, runs only once, after reset or power on:
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
    Wire.begin(); // Start I2C bus
    dht.begin(); // Start DHT sensor
    DEBUG_PRINTLN("Sensor initialized."); // Print message to serial monitor
    u8x8.begin(); // Start OLED display
    u8x8.setPowerSave(0); // Wake up OLED display
    u8x8.setFlipMode(1); // Rotate OLED display
    DEBUG_PRINTLN("Display initialized."); // Print message to serial monitor
}

void loop(void)
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
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
}
