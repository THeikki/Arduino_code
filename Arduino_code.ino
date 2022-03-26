#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
double a = 0.00000017002;
double b = 0.00022647;
double c = 0.18481;
double d = 33.136;

int ntcSensorValue = 0;
const int MQ5PIN = 7;
const int ARRAYSIZE = 16;
double temp, sum, val, average = 0;
double temps[ARRAYSIZE];

void setup() {

  pinMode(MQ5PIN, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);

  //mySerial.begin(9600);
  Serial.begin(9600);
  delay(20000);       //    Annetaan MQ5 -sensorin lämmetä ennen ohjelman alkua
}

void loop() {
  
  val = sumOfTemperatures();
  printAverageTemperature(val);
  getGasValue();
  clearVariableValues();
  delay(2000);   
}

double sumOfTemperatures() {
  for(int i=0;i<ARRAYSIZE;i++) {
    temps[i] = getTemperature();
    sum += temps[i];
    //Serial.print("val");
    //Serial.print(i);
    //Serial.print(": ");
    //Serial.println(temps[i]);
    delay(200);
  }
  return sum;
}

double getTemperature() {
  ntcSensorValue = analogRead(A0);

  temp = (a*ntcSensorValue*ntcSensorValue*ntcSensorValue) - (b*ntcSensorValue*ntcSensorValue) + c*ntcSensorValue - d; 
  return temp;
}

void printAverageTemperature(double val) {
  average = val / ARRAYSIZE;
  Serial.print(average);
  Serial.print(" ");
  /*
  if (mySerial.available() > 0) {
     mySerial.println(average); 
     //mySerial.print(temp);
  }
  */
}

void getGasValue() {
  float gas = digitalRead(MQ5PIN);
  Serial.print(gas);
  Serial.println();
}

void clearVariableValues() {
  sum = 0;
  val = 0;
}
