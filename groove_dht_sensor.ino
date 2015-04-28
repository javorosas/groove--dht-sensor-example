#include <TinyDHT.h>
#define TEMP_SENSOR A0
#define LIGHT_SENSOR A2
#define DHTTYPE DHT11
#define LED 13

DHT dht(TEMP_SENSOR, DHTTYPE);

float Rsensor = 0;

void setup() {
  Serial.begin(9600);
  Serial.println('Connected!');
  dht.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to A0 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
      Serial.println("Failed to read from DHT");
  }
  else
  {
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" *C");
  }
  
  // Read light sensor
  int light = analogRead(LIGHT_SENSOR);
  Rsensor=(float)(1023-light)*10/light;
  Serial.print("Analog light: ");
  Serial.print(light);
  Serial.print("\t");
  Serial.print("Light resistance: ");
  Serial.println(Rsensor,DEC);//show the ligth intensity on the serial monitor;
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    if (inChar == '1') {
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
  }
}
