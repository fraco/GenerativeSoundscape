///---|Gen-Synth
int trig = 600;

long timeM;
int wait = 6000;
int durationW = 0;

int buzzer = 4;
long timeB;
int buzz = 1000;
int durationB = 0;

int mic;
boolean micOff = false;
boolean buzzOn = false;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup(){
  Serial.begin(9600);
  pinMode(5,OUTPUT); 
}

void loop(){

  mic = analogRead(0);

  if( mic > trig && micOff == false){
    ///-WAIT "Stop hearing"
    micOff = true; 
    timeM = millis();
    ///-BUZZ
    buzzOn = true;
    timeB = millis();
  }

  ///-MIC
  if(micOff == true){
    if (millis() - timeM >= wait){ 
      micOff = false;          
    }
    else {
      durationW = millis() - timeM;   
    }
  }

  ///-BUZZER
  if(buzzOn == true && micOff == true && durationW > buzz/1.6666){
    digitalWrite(buzzer,HIGH);
    ///-speaker
    tone(buzzer,222,buzz);    
    tone(buzzer,444,buzz); 
    tone(buzzer,666,buzz); 
    ///-LEDs
    analogWrite(redPin,255); 
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
    if (millis() - timeB >= buzz){
      buzzOn = false;     
    } 
    if(buzzOn == false){
      digitalWrite(buzzer, LOW);
      digitalWrite(redPin,0); 
      digitalWrite(greenPin,0);
      digitalWrite(bluePin,0);
      //    noTone(); |function out of bounds
    }
  }

  ///-PRINT MIC
  Serial.print("Mic: ");
  Serial.print(mic);
  Serial.print("  timeM: ");
  Serial.print(timeM);
  Serial.print("  durW: ");
  Serial.print(durationW);

  ///-prnt BUZZ
  Serial.print("    TimeB: ");
  Serial.print(timeB);
  Serial.print("  durB: ");
  Serial.print(durationB);

  Serial.print("      MIC: ");
  Serial.print(micOff);
  Serial.print("  BUZZ: ");
  Serial.println(buzzOn);

  delay(10);

}









