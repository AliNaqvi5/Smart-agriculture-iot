#include <dht.h>
#include <LiquidCrystal.h>

dht DHT;

#define DHT11_PIN 2
#define Rres 5.6 // Kilo Ohms
#define Vref 5
// #define slope -1.404966547
#define A 12518931.7


  LiquidCrystal lcd(8,9,10, 11,12,13);  //RS,En D4,D5,D6,D7

int LDRPin = A0;      // input pin for the potentiometer
int MoistureSensorPin = A1; // input pin for soil moisture sensor
int rainSensorPin = A2;

float digitalValue = 0;  // variable to store the value coming from the sensor
float Vres = 0.00;
float Vldr = 0.00;
double Current = 0.000;
double  slope = -1.404966547;


int Rldr = 0; // variable
double lux = 0.0000;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("temperature:");
  // Serial.print(chk);
  Serial.println(DHT.temperature);
  Serial.print("humidity:");
  Serial.println(DHT.humidity);
  delay(100);

  // LDR Sensor
  digitalValue = analogRead(LDRPin);  // read the value from the analog channel
  // Serial.print("digital value = ");
  // Serial.println(digitalValue);  //print digital value on serial monitor

  Vres = (digitalValue * Vref) / 1023.00;
  // Serial.print("  analog voltage = ");


  Vldr = Vref - Vres;
  Current = Vres/Rres;
  Rldr =  (Vldr/ Current) * 1000 ;

  if(Rldr < 0)
  {
    //  Serial.println("Good Night....");
    lux=0;
  }
  else
  {
    //  Serial.println("Good Day......");
    lux = pow(Rldr, slope) * A;
  }


      // Serial.println(Rldr);
      // Serial.println(Vldr);
      // Serial.println(Current);
      //A*R^B
      
       Serial.print("lux:");
      Serial.println(lux);

// Soil Moisture sensor 

  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(MoistureSensorPin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("soilMoisture:");
  Serial.println(moisture_percentage);
  // Serial.print("%\n\n");

  //Rain Sensor
  int sensorRain = analogRead(rainSensorPin);
  char *Raining = (sensorRain < 235 ) ? "Dry" :"Light Rain";
  
  Raining = (sensorRain > 547 ) ? "Heavy Rain" :Raining;
  Serial.print("rainStatus:");
  Serial.println(Raining);
  // lcd.print("   CIRCUIT DIGEST");//print name

  // Serial.println(DHT.temperature);
  // Serial.print("humidity:");
  // Serial.println(DHT.humidity);
  // Serial.print("lux:");
  // Serial.println(lux);
  // Serial.print("soilMoisture:");
  // Serial.println(moisture_percentage);
  // Serial.print("rainStatus:");
  // Serial.println(Raining);

// lcd.setCursor(0, 2); // set the cursor to column 0, line 2


// lcd.print("TEMP ");//print name
// lcd.print(DHT.temperature);

// delay(750);//delay of 0.75sec


// lcd.scrollDisplayLeft();//shifting data on LCD


// lcd.setCursor(0, 0);// set the cursor to column 0, line1

  delay(1000);
}
