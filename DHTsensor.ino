#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define Rres 5 // Kilo Ohms
#define Vref 5
// #define slope -1.404966547
#define A 12518931.7


int LDRPin = A0;      // input pin for the potentiometer
float digitalValue = 0;  // variable to store the value coming from the sensor
float Vres = 0.00;
float Vldr = 0.00;
double Current = 0.000;
double  slope = -1.404966547;

int Rldr = 0; // variable
double lux = 0.0000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperaturee = ");
  Serial.print(chk);
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(100);

  // LDR Sensor
  digitalValue = analogRead(LDRPin);  // read the value from the analog channel
  Serial.print("digital value = ");
  Serial.println(digitalValue);  //print digital value on serial monitor

  Vres = (digitalValue * Vref) / 1023.00;
  Serial.print("  analog voltage = ");


  Vldr = Vref - Vres;
  Current = Vres/Rres;
  Rldr =  (Vldr/ Current) * 1000 ;

  if(Rldr < 0)
  {
     Serial.println("Good Night....");
  }
  else
  {
     Serial.println("Good Day......");
  }


      // Serial.println(Rldr);
      // Serial.println(Vldr);
      // Serial.println(Current);
      //A*R^B
      lux = pow(Rldr, slope) * A;
      //  Serial.println(A);
      Serial.println(lux);



  delay(1000);
}