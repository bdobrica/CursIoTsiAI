/**
 * Digital Barometer
 * 
 * This sketch reads temperature, pressure and altitude from a BMP280 sensor and
 * displays the values on a 128x64 OLED display.
 * 
 * Both the BMP280 sensor and the OLED display are connected to the I2C bus.
 * 
 * Configuration:
 * - BMP280 sensor: I2C bus (bmp280)
 * - OLED display: I2C bus (u8x8)
 * 
 * The sensor values are read and printed to the serial monitor.
 * The temperature, pressure and altitude are displayed on the OLED display.
 * 
 * Requirements:
 * - the "Grove - Barometer Sensor BMP280" library is used to read the
 *  temperature, pressure and altitude values.
 * - the "U8G2" library is used to control the OLED display.
 * - the "Wire" library is used to control the I2C bus. It is included by
 * default in the Arduino IDE.
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
#include <U8x8lib.h> // "U8G2" library
#include <Seeed_BMP280.h> // "Grove - Barometer Sensor BMP280" library

const int waitErrorMs = 1000; // Wait time before retrying sensor initialization
const int waitMs = 200; // Delay between readings

BMP280 bmp280; // Create a BMP280 object, for accessing the sensor
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); // Create a U8X8 object

void setup(void)
{ // Setup, runs only once, after reset or power on:
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
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
}

void loop(void)
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
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
}
