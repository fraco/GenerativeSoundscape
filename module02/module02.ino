///---|Gen-Synth
//#include <MozziGuts.h>
//#include <Oscil.h>
//#include <tables/sin2048_int8.h>
//#define CONTROL_RATE 128
int trig = 600;
//int trig = 450;
long time;
long timeT;
int calibW = 30*1000;
int wait = 6*1000;
int durationW = 0;

int buzzerPin = 5;
int buzz = 1000;
int durationB = 0;

int mic;

boolean micOff = false;
boolean buzzOn = false;
boolean calibrate = false;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//Oscil <2048,AUDIO_RATE> aSin(SIN2048_DATA);

void setup(){
  Serial.begin(9600);
  pinMode(5,OUTPUT); 
  timeT = millis();
  //  startMozzi(CONTROL_RATE);
  //  aSin.setFreq(440);
}

void loop(){

  mic = analogRead(0);

  if( mic > trig && micOff == false){
    ///-WAIT "Stop hearing"
    micOff = true; 
    ///-BUZZ
    buzzOn = true;
    ///-Reset time
    time = millis();
  }
  
  ///-THRESHOLD
  if(millis()-timeT >= calibW){
    calibrate = true;
//    Serial.print("IIIIIINNNNN!");
    trig = analogRead(0)+100;
    timeT = millis();
  } else {
   calibrate = true;
  }
  
  if(calibrate == true){
    trig = trig;
    calibrate = false;
  } else {
   trig = analogRead(0) + 20; 
  }

  ///-MIC
  if(micOff == true){
    if (millis() - time >= wait){ 
      micOff = false;          
    }
    else {
      durationW = millis() - time;   
    }
  }

  ///-BUZZER
  if(buzzOn == true && micOff == true && durationW > buzz/1.6666){
    tone(buzzerPin,220,10);//digitalWrite(buzzer,HIGH);
    tone(buzzerPin,440,10);//digitalWrite(buzzer,HIGH);
    tone(buzzerPin,550,10);//digitalWrite(buzzer,HIGH);
    //    audioHook();
    analogWrite(redPin,255); 
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
    if (millis() - time >= buzz){
      buzzOn = false;     
    } 
    if(buzzOn == false){
      //digitalWrite(buzzer, LOW); 
      digitalWrite(redPin,LOW); 
      digitalWrite(greenPin,LOW);
      digitalWrite(bluePin,LOW);      
    }
  }

  ///-PRINT MIC
  Serial.print("Mic: ");
  Serial.print(mic);
  Serial.print("\tTime: ");
  Serial.print(time);
  Serial.print("\tDurW: ");
  Serial.print(durationW);

///-threshold
  Serial.print("\tTimerThresh: ");
  Serial.print(timeT);
  Serial.print("\tThreshold: ");
  Serial.print(trig);

  Serial.print("\tMIC: ");
  Serial.print(micOff);
  Serial.print("\tBUZZ: ");
  Serial.print(buzzOn);
  Serial.print("\tCalibration: ");
  Serial.println(calibrate);

  delay(10);

}








