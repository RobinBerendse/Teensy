/*
 * Analog1: read an analog input and send to the monitor
 *
*/
void setup()
{                
  Serial.begin(115200);
}

int val;

void loop()                     
{
  val = analogRead(A0);  // A0 is PIN_F0, or we could just say "14"
  //Serial.print("analog 0 is: ");
  Serial.println(val);
  delay(20);
}
