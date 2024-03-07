/**
 * Sound sensor
 * 
 * This example shows how to use a sound sensor to turn on a LED when the sound
 * is above a certain threshold.
 * 
 * The sound sensor is connected to the analog pin A2 and the LED is connected
 * to pin 4.
 * 
 * Configuration:
 * - Sound sensor: analog pin A2 (soundPin)
 * - LED: pin 4 (ledPin)
 * - Threshold: 400 (threshold). Change this value to adjust the sensitivity.
 *   The value is between 0 and 1023.
 * - On time: 100 ms (onTimeMs). Change this value to adjust how long the LED
 *   stays on after a sound above the threshold is detected.
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

const int soundPin = A2; // Sound sensor PIN
const int ledPin = 4; // LED PIN
const int threshold = 400; // Sound sensor threshold
const int onTimeMs = 100; // Amount of time to keep the LED on after a sound
int sensorValue = 0; // Sound sensor initial value

void setup()
{
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    pinMode(soundPin, INPUT); // Set sound sensor pin as input
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
}

void loop()
{
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
}
