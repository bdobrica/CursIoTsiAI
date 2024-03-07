
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

#include <U8x8lib.h> // "U8G2" library
#include <LIS3DHTR.h>

const int waitSensorMs = 1000;
const int waitMs = 20;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); // Create a U8X8 object
LIS3DHTR<TwoWire> LIS; // Configurează I2C în hardware

void setup()
{
    DEBUG_BEGIN;
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
void loop()
{
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
}
