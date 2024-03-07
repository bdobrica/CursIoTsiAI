/**
 * Light sensor
 * 
 * This example shows how to use a light sensor to turn on a LED when the light
 * is above a certain threshold.
 * 
 * The light sensor is connected to the analog pin A6 and the LED is connected
 * to pin 4.
 * 
 * Configuration:
 * - Light sensor: analog pin A6 (sensorPin)
 * - LED: pin 4 (ledPin)
 * - Threshold: 200 (threshold). Change this value to adjust the sensitivity.
 *   The value is between 0 and 1023.
 * - Wait time: 200 ms (waitMs). Change this value to adjust the delay between
 *   readings.
 * 
 * The sensor value is read and printed to the serial monitor. If the value is
 * above the threshold, the LED is turned on.
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

const int sensorPin = A6; // Light sensor PIN
const int ledPin = 4; // LED PIN
const int threshold = 200; // Light sensor threshold
const int waitMs = 200; // Delay between readings
int sensorValue = 0; // Light sensor initial value

void setup()
{ // Setup, runs only once, after reset or power on:
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    pinMode(sensorPin, INPUT); // Set light sensor pin as input
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
}

void loop()
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
    sensorValue = analogRead(sensorPin); // Read light sensor value
    DEBUG_PRINT("Sensor Value: ");
    DEBUG_PRINTLN(sensorValue); // Print sensor value to serial monitor
    if (sensorValue >= threshold)
    { // If sensor value is above threshold
        digitalWrite(ledPin, HIGH); // Turn on LED
        DEBUG_PRINTLN("LED ON"); // Print LED status to serial monitor
    }
    else
    { // If sensor value is below threshold
        digitalWrite(ledPin, LOW); // Turn off LED
    }
    delay(waitMs); // Wait before reading sensor value again
}
