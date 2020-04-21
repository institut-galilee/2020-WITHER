#include "OV7670.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <WiFi.h>
#include "BMP.h"

const int SIOD = 18; //SDA
const int SIOC = 19; //SCL

const int VSYNC = 34;
const int HREF = 35;

const int XCLK = 32;
const int PCLK = 33;

const int D0 = 27;
const int D1 = 17;
const int D2 = 16;
const int D3 = 15;
const int D4 = 14;
const int D5 = 13;
const int D6 = 26;
const int D7 = 4;

const int TFT_DC = 2;
const int TFT_CS = 5;

#define ssid        "wifi name"
#define password    "wifi password"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, 0/*no reset*/);
OV7670 *camera;

WiFiServer server(80);

unsigned char bmpHeader[BMP::headerSize];

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

void setup() 
{
  Serial.begin(115200);
  //link esp pins to motor
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
  Serial.println("IP address: ");
  //Use this adress to get connected
  Serial.println(WiFi.localIP());
  
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
  server.begin();
}

void loop()
{
  camera->oneFrame();
  //temperature calcul
  Vo = analogRead(ThermistorPin);
  //Equation pour un diviseur de tension
  R2 = R1 * ((1023.0 / (float)Vo )- 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //température en kelvins
  //température en celcius
  Tc = T - 273.15;
  
  WiFiClient client = server.available();
  if (client) 
  {
    //Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // feed the animal
            if (header.indexOf("GET /feed/on") >= 0) {
              Serial.println("feed on");
              RotationOccur(4,300);
            }
            
            // HTML
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            // CSS 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\nimg{height: 60%; width: auto}");
            client.println(".button { background-color: #4CAF50; border: 2px solid black ;color: white; padding: 16px 40px;");
            client.println(".temperature { background-color:grey; border: 2px solid black;color:black;padding: 16px 40px; }");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Food App</h1>");
            //Content    
            client.println("<p><a href=\"/feed/on\"><button class=\"button\">FEED</button></a></p>");
            client.println("<h2>Current Temperature :</h2>");
            Serial.println(Tc);
            client.println("<p class=\"temperature\">");
            client.println(Tc);
            //special character for degree
            client.println((char)176);
            client.println("C</p>");
            client.println("<h2>Camera :</h2>");
             client.print(
              "<img id='a' src='/camera' onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now(); '>"
              "<img id='b' style='display: none' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now(); '>");
            client.println("</body></html>");
            client.println();
            //HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } 
          else // clear the currentline
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {
          currentLine += c;
        }
        
       
         if(currentLine.endsWith("GET /camera"))
        {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:image/bmp");
            client.println();
            
            client.write(bmpHeader, BMP::headerSize);
            client.write(camera->frame, camera->xres * camera->yres * 2);
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
  displayRGB565(camera->frame, camera->xres, camera->yres);
}

void displayY8(unsigned char * frame, int xres, int yres)
{
  tft.setAddrWindow(0, 0, yres - 1, xres - 1);
  int i = 0;
  for(int x = 0; x < xres; x++)
    for(int y = 0; y < yres; y++)
    {
      i = y * xres + x;
      unsigned char c = frame[i];
      unsigned short r = c >> 3;
      unsigned short g = c >> 2;
      unsigned short b = c >> 3;
      tft.pushColor(r << 11 | g << 5 | b);
    }  
}

void displayRGB565(unsigned char * frame, int xres, int yres)
{
  tft.setAddrWindow(0, 0, yres - 1, xres - 1);
  int i = 0;
  for(int x = 0; x < xres; x++)
    for(int y = 0; y < yres; y++)
    {
      i = (y * xres + x) << 1;
      tft.pushColor((frame[i] | (frame[i+1] << 8)));
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
      OneStep(true);
      delay(2); 
    }
    for(int a=0;a<stepp;a++){
      OneStep(false);
      //Minimum time between steps
      delay(2);
    }
  }
}
