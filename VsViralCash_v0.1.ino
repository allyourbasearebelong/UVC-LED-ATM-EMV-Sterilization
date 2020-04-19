// Darkness triggering LDR > Relay > UVC LED's
// Quite simply, the LDR detects that the card has been entered,
// at which point it triggers the MOSFET relay which completes the circuit to the UVC LED's.
// PIR waits for movement, when the movement stops, it'll trigger the other 

const int ldrPin = A0;
const int pirPin = 7; //digital 7
const int PIR_MOSFET_Pin = 12;
const int LDR_MOSFET_Pin = 13;

void setup() {

  Serial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(PIR_MOSFET_Pin, OUTPUT);  
  pinMode(LDR_MOSFET_Pin, OUTPUT);


}

void loop() {

  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 200) {
                                        //Someone has inserted a bank card
    digitalWrite(LDR_MOSFET_Pin, HIGH);
                                        //Turn on UVC-LED's immediately
    Serial.print("The bank card has been inserted. Turn on the LDR controlled relay & UVC LED's");
                                        //Keep reading the LDR status
    Serial.println(ldrStatus);

  } 
  else {

    digitalWrite(LDR_MOSFET_Pin, LOW);

    Serial.print("The bank card has been removed. Turn off the Relay & UVC LED's");
    delay(5000); 
                                        //This will really need to be an if/else rather than timed, as an ATM transaction isn't timed, 
                                        //people could just withdraw cash or take longer looking at balances etc
    Serial.println(ldrStatus);

  }

  {
    int pirVal = digitalRead(pirPin);

    Serial.println(pirVal);

    if(pirVal == LOW){                  //Motion's been detected, so there's someone at the ATM
    
      Serial.println("Motion Detected");
                                        //This will really need to be an if/else rather than timed, once this goes HIGH again when someone walks away, that's when we'd kick it in
      
      digitalWrite(PIR_MOSFET_Pin, HIGH);
      delay(2000);                      //calibrate time for sterilisation
      
      digitalWrite(PIR_MOSFET_Pin, LOW);  //Turn the UVC-LED's off again
    }
      else {

    Serial.println(pirVal);

  }

  
  }



}







