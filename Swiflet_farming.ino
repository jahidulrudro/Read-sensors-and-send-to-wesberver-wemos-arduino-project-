/*
 * Mohammad Jahidul Alam
 * Universiti Teknoloi Malaysia
 */

#include "DHT.h"
#define DHTPIN 4   // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//WIFI Password & User Name Setting Up

const char* ssid = "iPhone";
const char* password = "1234567890z";

//Web Server address

const char *host = "roommatebd.com";  

DHT dht(DHTPIN, DHTTYPE);

int piezoPin = D6;
unsigned long delayStart = 0; // the time the delay started
void setup() {
 
  Serial.begin(9600);
  Serial.println("Swiflet Farming Monitoring System");
  delayStart=millis();
  //Wifi Connection

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.hostname("iPhone");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

 

  // Print the IP address

  Serial.print("IP address: ");

  Serial.print(WiFi.localIP());

  Serial.println();

  dht.begin();



}

void loop() {
 
 
if((millis()-delayStart)>=50000){
  Serial.println("Music Start");  
  tone(piezoPin, 1000, 2000);
  delay(10000);
  delayStart=millis();
  if(millis()-delayStart>=10000){
  Serial.println("Music Stopped");
  noTone(piezoPin);     // Stop sound...
  }
 
}
      int val;
      val=analogRead(0);   //connect grayscale sensor to Analog 0
      Serial.println("Ambient Light:");
      Serial.print(val,DEC);//print the value to serial
      Serial.print(" LUX");
      Serial.println("");
      Serial.println("===========================");
      if(val<=10000){
        Serial.println("Light On");
        Serial.println();
        pinMode(D9,OUTPUT);
        digitalWrite(D9, HIGH);
        delay(1000);
        digitalWrite(D9,LOW);  
      }

     delay(2000);

  Serial.print("Temperature: ");
  Serial.print(getTemp("c"));
  Serial.print(" *C ");
  Serial.print(getTemp("f"));
  Serial.println (" *F");
  Serial.println("-----------------");  
  Serial.print("Heat: ");
  Serial.print(getTemp("hic"));
  Serial.print(" *C ");
  Serial.print(getTemp("hif"));
  Serial.println(" *F");
  Serial.print(getTemp("k"));
  Serial.println(" *K");
  Serial.println("-----------------");    
  Serial.print("Humidity: ");
  Serial.print(getTemp("h"));
  Serial.println(" % ");
  Serial.println("===========================");
  Serial.println(" ");
  float h = dht.readHumidity();
   float t = dht.readTemperature();
  if(h<80)
  {
    Serial.println("FAN ON");
    digitalWrite(5,HIGH);
    delay(1000);
    digitalWrite(5,LOW);
   
  }

  HTTPClient http;    //Declare object of class HTTPClient
 
  String ADCData, station, postData;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  station = "A";
 String  humidity="10";
 
  //Post Data
  postData = "light=" + ADCData + "&temp=" + t +"&h="+h;
 
  http.begin("http://roommatebd.com/rudro/swiflet/index.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
 
  delay(5000);  //Post Data at every 5 seconds
 
}

float getTemp(String req)
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0.0;
  }
  // Compute heat index in Kelvin
  float k = t + 273.15;
  if(req =="c"){
    return t;//return Cilsus
  }else if(req =="f"){
    return f;// return Fahrenheit
  }else if(req =="h"){
    return h;// return humidity
  }else if(req =="hif"){
    return hif;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic;// return heat index in Cilsus
  }else if(req =="k"){
    return k;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
   
  }
 
}

On Tue, Dec 10, 2019 at 5:24 AM Mohammad Jahidul Alam <engr.rudro@hotmail.com> wrote:
#include "DHT.h"
#define DHTPIN 4   // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "iPhone";

const char* password = "1234567890z";
//Web/Server address to read/write from
const char *host = "roommatebd.com";  
DHT dht(DHTPIN, DHTTYPE);
int piezoPin = 2;
unsigned long delayStart = 0; // the time the delay started
void setup() {
  //pinMode(13, OUTPUT);
  //pinMode(12,OUTPUT);
  Serial.begin(9600);
  Serial.println("Swiflet Farming Monitoring System");
  delayStart=millis();
  //Wifi Connection

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.hostname("iPhone");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

 

  // Print the IP address

  Serial.print("IP address: ");

  Serial.print(WiFi.localIP());

  Serial.println();

  dht.begin();



}

void loop() {
 
 
if((millis()-delayStart)>=50000){
  Serial.println("Music Start");  
  tone(piezoPin, 1000, 2000);
  delay(10000);
  delayStart=millis();
  if(millis()-delayStart>=10000){
  Serial.println("Music Stopped");
  noTone(piezoPin);     // Stop sound...
  }
 
}
      int val;
      val=analogRead(0);   //connect grayscale sensor to Analog 0
      Serial.println("Ambient Light:");
      Serial.print(val,DEC);//print the value to serial
      Serial.print(" LUX");
      Serial.println("");
      Serial.println("===========================");
      if(val<=10000){
        Serial.println("Light On");
        Serial.println();
        pinMode(12,OUTPUT);
        digitalWrite(12, HIGH);
        delay(1000);
        digitalWrite(12,LOW);  
      }

     delay(2000);

  Serial.print("Temperature: ");
  Serial.print(getTemp("c"));
  Serial.print(" *C ");
  Serial.print(getTemp("f"));
  Serial.println (" *F");
  Serial.println("-----------------");  
  Serial.print("Heat: ");
  Serial.print(getTemp("hic"));
  Serial.print(" *C ");
  Serial.print(getTemp("hif"));
  Serial.println(" *F");
  Serial.print(getTemp("k"));
  Serial.println(" *K");
  Serial.println("-----------------");    
  Serial.print("Humidity: ");
  Serial.print(getTemp("h"));
  Serial.println(" % ");
  Serial.println("===========================");
  Serial.println(" ");
  float h = dht.readHumidity();
   float t = dht.readTemperature();
  if(h<80)
  {
    Serial.println("FAN ON");
    digitalWrite(5,HIGH);
    delay(1000);
    digitalWrite(5,LOW);
   
  }

  HTTPClient http;    //Declare object of class HTTPClient
 
  String ADCData, station, postData;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  station = "A";
 String  humidity="10";
 
  //Post Data
  postData = "light=" + ADCData + "&temp=" + t +"&h="+h;
 
  http.begin("http://roommatebd.com/rudro/swiflet/index.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
 
  delay(5000);  //Post Data at every 5 seconds
 
}

float getTemp(String req)
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0.0;
  }
  // Compute heat index in Kelvin
  float k = t + 273.15;
  if(req =="c"){
    return t;//return Cilsus
  }else if(req =="f"){
    return f;// return Fahrenheit
  }else if(req =="h"){
    return h;// return humidity
  }else if(req =="hif"){
    return hif;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic;// return heat index in Cilsus
  }else if(req =="k"){
    return k;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
   
  }
 
}
