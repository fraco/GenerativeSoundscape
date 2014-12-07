///---|Gen-Synth
int trig = 555;

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

void setup(){
  pinMode(buzzer,OUTPUT); 
}

void loop(){

  mic = analogRead(3);

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
//    tone(buzzer,1000,buzz); 
    if (millis() - timeB >= buzz){
      buzzOn = false;     
    } 
    if(buzzOn == false){
    digitalWrite(buzzer, LOW);
//    noTone(); |function out of bounds
    }
  }

  delay(10);

}







