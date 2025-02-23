#include <WiFi.h>
#include <WebServer.h> // Include the web server library
#include <SCServo.h>  
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "Ahhh";        // Replace with your Wi-Fi SSID
const char* password = "sumeadh12"; // Replace with your Wi-Fi Password

SMS_STS st;
#define S_RXD 18
#define S_TXD 19

WebServer server(80); // Create a web server on port 80

void handleData() {
  // Extract data sent via HTTP GET request
  String data = server.arg("data"); // 'data' is the key in the URL query
  Serial.println("Received Data: " + data);

  // Send a response to the client
  server.send(200, "text/plain", "Data received: " + data);
}

void handlePost() {
    if (server.hasArg("plain")) { // Check if there's data in the body
        String data = server.arg("plain");
        Serial.println("Received Data (POST): " + data);

        // Parse the received JSON data into the servo control parameters
        // Example format: [[1, 2048, 3000, 150], [3, 2120, 3000, 150], ...]

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);
        JsonArray servo_data = doc.as<JsonArray>();

        // Loop through the received data and control each motor
        for (int i = 0; i < servo_data.size(); i++) {
            int motor_id = servo_data[i][0];       // Servo ID
            int position = servo_data[i][1];       // Position
            int speed = servo_data[i][2];          // Speed
            int accel = servo_data[i][3];          // Acceleration

            // Write to the motor
            st.WritePosEx(motor_id, position, speed, accel);
        }

        // Send a response to the client
        server.send(200, "text/plain", "Data received and motors updated.");
    } else {
        Serial.println("No data received!");
        server.send(400, "text/plain", "Bad Request: No data received!");
    }
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected! IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize SCServo
    Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
    st.pSerial = &Serial1;

    // Define routes
    server.on("/", HTTP_POST, handlePost); // POST request to root

    server.begin(); // Start the server
    Serial.println("Web server started!");
}

void loop() {
    server.handleClient(); // Handle incoming HTTP requests
}
