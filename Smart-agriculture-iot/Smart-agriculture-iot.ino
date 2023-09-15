#include <dht.h>
#include <LiquidCrystal.h>

dht DHT;

#define DHT11_PIN 2
#define Rres 5.6 // Kilo Ohms
#define Vref 5
// #define slope -1.404966547
#define A 12518931.7


  // LiquidCrystal lcd(8,9,10, 11,12,13);  //RS,En D4,D5,D6,D7

int LDRPin = A0;      // input pin for the LDR
int MoistureSensorPin = A1; // input pin for soil moisture sensor
int rainSensorPin = A2;

float digitalValue = 0;  // variable to store the value coming from the sensor
float Vres = 0.00;
float Vldr = 0.00;
double Current = 0.000;
double  slope = -1.404966547;

// default limits
int tempMin = 27;
int tempMax = 32;
int humMin = 70;
int humMax = 90;
int luxMax = 800;
int soilMoistureMin = 20;
unsigned int loopDelay = 1000;
unsigned int loopCount = (1*60*1000)/loopDelay;
int loopIncrement = 0;



int Rldr = 0; // variable
double lux = 0.0000;

void setup() {
  Serial.begin(9600);
  // lcd.begin(16, 2);

    delay(2000);
}


void loop() {
Serial.println(loopDelay);
    Serial.println(loopCount);
  if(loopIncrement == loopCount || loopIncrement == 0)
  {
     int chk = DHT.read11(DHT11_PIN);
    // Serial.print("start::");
      Serial.print("temperatureee:");
      // Serial.print(chk);
      Serial.println(DHT.temperature);
      if(DHT.temperature < tempMin )
      {
        Serial.print("Alarmtemperature:");
       Serial.println("Low Temperature");
      }else if(DHT.temperature > tempMax)
      {
        //cooling system 
            Serial.print("Alarmtemperature:");
          Serial.println("High Temperature");
      }

      delay(100);
      Serial.print("humidity:");
      Serial.println(DHT.humidity);
      if(DHT.humidity < humMin )
      {
        Serial.print("Alarmhumidity:");
          Serial.println("Low humidity");
      }else if(DHT.humidity > humMax)
      {
        Serial.print("Alarmhumidity:");
          Serial.println("High humidity");
      }
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
      if(lux > luxMax )
      {
        //ALert
        Serial.print("Alarmlux:");
          Serial.println("High intensity of sun light");
      }
          // Serial.println(Rldr);
          // Serial.println(Vldr);
          // Serial.println(Current);
          //A*R^B
          
          Serial.print("lux:");
          Serial.println(lux);
    delay(100);
      // Soil Moisture sensor 

      float moisture_percentage;
      int sensor_analog;
      sensor_analog = analogRead(MoistureSensorPin);
      moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
      Serial.print("soilMoisture:");
      Serial.println(moisture_percentage);
      // Serial.print("%\n\n");
      if(moisture_percentage < soilMoistureMin )
      {
        Serial.print("AlarmsoilMoisture:");
          Serial.println("Low soilMoisture Pump start");
      }
    delay(100);
      //Rain Sensor
      int sensorRain = analogRead(rainSensorPin);
      char *Raining = (sensorRain < 235 ) ? "Dry" :"Light Rain";
      
      Raining = (sensorRain > 547 ) ? "Heavy Rain" :Raining;
      Serial.print("rainStatus:");
      Serial.println(Raining);
      
      if(Raining != "Dry")
      {
        Serial.print("AlarmrainStatus:");
          Serial.println("It is Raining in karachi");
      }
      loopIncrement = 0;
  }
  // Serial.print("end::");
  // lcd.print("   CIRCUIT DIGEST");//print name
  //  delay(1000);
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

    if (Serial.available() > 0) {
      // read the incoming byte:
    String teststr = Serial.readString();  //read until timeout
    teststr.trim(); 

      // say what you got:
      Serial.print("I received: ");
      Serial.println(teststr);
    }

    
    loopIncrement++;
    delay(1000);

}

