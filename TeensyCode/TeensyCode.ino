#include <Encoder.h> // include the encoder library

//Distance
#define trigPin 2
#define echoPin 3
long duration;
int distance;

//Gyro
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;



Encoder enc(14, 15); // create an encoder object

long current_value; // current read
long previous_value = -999; // previous read

void setup() {
  //Distance
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Gyro
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    
  Serial.begin(57600); // open serial port


  accelgyro.initialize();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
   
  current_value = enc.read(); // read the value of the encoder
  
  if (current_value != previous_value) { // compare to previous reading
    Serial.println(current_value); // if it's changed, print to serial port
    previous_value = current_value; // store the reading for next comparison
  }

  //Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");


  //Gyro
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
    #endif
 
    
 
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);


    delay(50);
}
