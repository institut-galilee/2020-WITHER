// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "wifi name";
const char* password = "wifi password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//pin motor
#define STEPPER_PIN_1 23
#define STEPPER_PIN_2 22
#define STEPPER_PIN_3 21
#define STEPPER_PIN_4 5 
int step_number = 0;

//variable for temperature
int ThermistorPin = 36;//GPI36
//valeur du thermistor
int Vo;
//valeur de la resistance utilise 10K
float R1 = 10000;
//variables utilisées
float logR2, R2, T, Tc;
//Steinhart-hart coefficients
float c1 = 1.1384e-03, c2 = 2.3245e-04, c3 = 9.489e-08;

void setup() {
  Serial.begin(115200);
  
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  //Use this adress to get connected
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  
  //temperature calcul
  Vo = analogRead(ThermistorPin);
  //Equation pour un diviseur de tension
  R2 = R1 * ((1023.0 / (float)Vo )- 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //température en kelvins
  //température en celcius
  Tc = T - 273.15;
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             
    Serial.println("New Client.");         
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             /
        Serial.write(c);                   
        header += c;
        if (c == '\n') {    
          // HTTP response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // feed the animal
            if (header.indexOf("GET /feed/on") >= 0) {
              Serial.println("feed on");
              RotationOccur(5,500);
            } 
            
            // HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            // CSS 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: 2px solid black ;color: white; padding: 16px 40px;");
            client.println(".temperature { background-color:grey; border: 2px solid black;color:black;padding: 16px 40px; }");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Food App</h1>");
            
            // Display food button      
            client.println("<p><a href=\"/feed/on\"><button class=\"button\">FEED</button></a></p>");
            client.println("<h2>Current Temperature :</h2>");
            Serial.println(Tc);
            client.println("<p class=\"temperature\">");
            client.println(Tc);
            client.println((char)176);
            client.println("C</p>");
            client.println("</body></html>");
            
            client.println();
            // Break out of the while loop
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;    
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}

void RotationOccur(int o,int stepp){
  for(int j=0;j<o;j++){
    //max step =2048
    for(int a=0;a<stepp;a++){
      OneStep(false);
      //Minimum time between steps
      delay(2);
    }
    for(int a=0;a<stepp;a++){
      OneStep(true);
      delay(2);
    }
  }
}
