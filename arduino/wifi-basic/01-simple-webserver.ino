/**
 * WiFi Web Server LED Blink (adapted from WiFi Web Server LED Blink by Tom Igoe)
 * 
 * A simple web server that lets you blink an LED via the web. It uses the WiFi
 * module to create to an access point and creates a server that listens for
 * incoming HTTP requests. If the IP address of your board is yourAddress:
 * 
 * - http://yourAddress:serverPort/H turns the LED on
 * - http://yourAddress:serverPort/L turns it off
 * 
 * Configuration:
 * - LED: built-in LED (ledPin)
 * - Server port: 8080 (serverPort) - Change this value to adjust the server port
 * - Wait time: 500 ms (waitWiFiMs) - Change this value to adjust the delay between
 *  WiFi connection attempts
 * - Wait time: 1 ms (waitClientMs) - Change this value to adjust the delay between
 * client checks
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

#define SECRET_SSID "network" // Change this value to your WiFi network name
#define SECRET_PASS "password" // Change this value to your WiFi network password

#include <WiFiS3.h>

const int ledPin =  LED_BUILTIN; // Built-in LED
const int serverPort = 8080; // Server port. Can be any port from 1 to 65535
const int waitWiFiMs = 500; // Delay between WiFi connection attempts
const int waitClientMs = 1; // Delay between client checks
WiFiServer server(serverPort); // Create a server on the specified port

void setup()
{ // Setup, runs only once, after reset or power on:
    DEBUG_BEGIN; // Start serial monitor, if DEBUG is enabled
    pinMode(ledPin, OUTPUT); // Set LED pin as output

    if (WiFi.status() == WL_NO_MODULE) { // Check if the WiFi module is available
        DEBUG_PRINTLN("Communication with WiFi module failed!"); // Print error message
        while (true); // Stay here forever
    }

    WiFi.begin(SECRET_SSID, SECRET_PASS); // Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) { // Wait for the WiFi connection
        delay(waitWiFiMs); // If not connected, wait and try again
        DEBUG_PRINT("."); // Print a dot to show the connection is in progress
    }
    DEBUG_PRINTLN(""); // Print a new line
    DEBUG_PRINTLN("WiFi connected"); // Print a message to show the connection is successful
    DEBUG_PRINT("IP address: ");
    DEBUG_PRINTLN(WiFi.localIP()); // Print the IP address

    server.begin(); // Start the server
    DEBUG_PRINTLN("Server started"); // Print a message to show the server is running
}


void loop()
{ // Main loop, runs code repeatedly, after setup, until reset or power off:
    WiFiClient client = server.available(); // Check if a client has connected
    if (!client) { // If no client has connected, return to the beginning of the loop
        return;
    }
    DEBUG_PRINTLN("New client"); // Print a message to show a new client has connected
    while (!client.available()) { // Wait for the client to send data
        delay(waitClientMs); // If no data is available, wait and try again
    }
    String request = client.readStringUntil('\r'); // Read the first line of the request
    DEBUG_PRINTLN("Request: " + request); // Print the request to the serial monitor
    client.flush(); // Clear the client buffer
    if (request.indexOf("GET /H") != -1) { // If the request contains "GET /H"
        DEBUG_PRINTLN("LED ON"); // Print a message to show the LED is on
        digitalWrite(ledPin, HIGH); // Turn on the LED
    }
    if (request.indexOf("GET /L") != -1) { // If the request contains "GET /L"
        DEBUG_PRINTLN("LED OFF"); // Print a message to show the LED is off
        digitalWrite(ledPin, LOW); // Turn off the LED
    }
    client.println("HTTP/1.1 200 OK"); // Send a response to the client
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html></html>");
    client.stop(); // Close the connection
}
