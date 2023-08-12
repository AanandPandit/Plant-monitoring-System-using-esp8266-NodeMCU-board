#include <ESP8266WiFi.h>
#include <DHT.h>
String apiKey = "IYE74WL19NIHWNTN";  //  Enter your Write API key from ThingSpeak

const char* ssid = "test";          // your wifi ssid
const char* pass = "qwertyuiop";    // your wifi password
const char* server = "api.thingspeak.com";

#define DHTPIN D1                 //pin where the dht11 is connected
#define SOIL_MOISTURE_PIN A0      //pin where soil moisture is connected 
#define LED_need_water D2         //pin where led glows when moisture is low
#define LED_good_moisture D0      //pin where led keeps glowing until moisture is good
#define LED_wifi D3               //pin where led keeps blinking unitl connected to wifi

DHT dht(DHTPIN, DHT11);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();    // initialize dht11 
  pinMode(SOIL_MOISTURE_PIN, INPUT);    //initialize soil moisture
  pinMode(LED_good_moisture, OUTPUT);     //initialize led D0 for good moisture
  pinMode(LED_need_water, OUTPUT);        //initialize led D2 for need water
  pinMode(LED_wifi, OUTPUT);


  Serial.println("Connecting to ");
  Serial.println(ssid);


  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_wifi, HIGH);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(LED_wifi, HIGH);
  delay(500);
  digitalWrite(LED_good_moisture, HIGH);
  delay(500);
  digitalWrite(LED_need_water, HIGH);
  delay(10000);
  digitalWrite(LED_wifi, LOW);
  delay(500);
  digitalWrite(LED_good_moisture, LOW);
  delay(500);
  digitalWrite(LED_need_water, LOW);
  delay(5000);
}

void loop() {

  // fecthing value from dht11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // fetcheing value from soil moisture sensor
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercentage = map(soilMoistureValue, 4095, 0, 0, 100); 
  // int moisturePercentage = random(0,70);

  // setting LED for good moisture 
  if(moisturePercentage >= 21 && moisturePercentage <=40){
    digitalWrite(LED_good_moisture, HIGH);
    Serial.println("Moisture of soil is perfect.");
  }
  // indicates moisture is high
  else if(moisturePercentage >=41){
    digitalWrite(LED_good_moisture, HIGH);
    Serial.println("Moisture of soil is very high, turning off the irrigation system.");
    delay(500);
    digitalWrite(LED_good_moisture, LOW);
  }

  // setting LED for need water
  if(moisturePercentage <= 21){
    digitalWrite(LED_need_water, HIGH);
    digitalWrite(LED_wifi, HIGH);
    Serial.println("Moisture of soil is Low, turning on irrigation system.");
    delay(500);
    digitalWrite(LED_need_water, LOW);
    digitalWrite(LED_wifi, LOW);
  }
  else if (t >= 30){
    digitalWrite(LED_need_water, HIGH);
    Serial.println("Hot Day.");
  }

  // Check if dht11 sensor reading is valid
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    // Construct the data payload for Thingspeak
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(moisturePercentage);
    postStr += "\r\n\r\n";

    // Send HTTP POST request to Thingspeak
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("ContX-THINGSPEAKAPIKEent-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    // Display data on the serial monitor
    Serial.print("Temperature (degree celcius): ");
    Serial.println(t);
    Serial.print("Humidity (%): ");
    Serial.println(h);
    Serial.print("Soil moisture percentage (%):");
    Serial.println(moisturePercentage);
    Serial.println("Send to Thingspeak.");
    Serial.println("------------------------------------------------------------");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}


// NOTE:
// LED_need_water    --> Red LED
// LED_good_moisture --> Yellow LED
// LED_wifi          --> Green LED
// --------------------------------------------------
// Only Green LED is on := connecting to WiFi
// Only Red LED is on := Hot Day
// Only Yellow is on := Normal moisture
// ---------------------------------------------------
// Low moisture := Red and Green blinking
// High moisture := Yellow LED blinking
//
