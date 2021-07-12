// Arduino - WAV Trigger

#include <Metro.h>
#include <AltSoftSerial.h>    // Arduino build environment requires this
#include <wavTrigger.h>

wavTrigger wTrig;             // Our WAV Trigger object

Metro gLedMetro(500);         // LED blink interval timer
Metro gSeqMetro(6000);        // Sequencer state machine interval timer

void setup() {

  // Serial monitor
  Serial.begin(9600);
  pinMode(13, OUTPUT);  // WAV Trigger onset
  pinMode(12, OUTPUT);  // Real sound onset
  pinMode(11, OUTPUT);  // 
  pinMode(10, OUTPUT);
  
  // If the Arduino is powering the WAV Trigger, we should wait for the WAV
  //  Trigger to finish reset before trying to send commands.
  delay(1000);

  // WAV Trigger startup at 57600
  wTrig.start();  
  delay(10);

  // Send a stop-all command and reset the sample-rate offset, in case we have
  //  reset while the WAV Trigger was already playing.
  wTrig.stopAllTracks();   
  wTrig.samplerateOffset(0);  

  // Sound volume control
  //wTrig.masterGain(0);
  
}

int input = 0;
int track = 2;
int prac = 32;

int thres = 11 ;

void loop() {

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);

  int sound_L = analogRead(A0);
  int sound_R = analogRead(A1);
  //Serial.println(sound_L);

   
  // Trigger for start trial
  int input = Serial.read();
  if (input==49){  //int = 1 
    
    // start sound
    wTrig.trackPlaySolo(track);
    
    // Trigger for WAV onset
    digitalWrite(13, HIGH);
          
    while(true) {    
      
      // Detect analog signal of sound(beep sound)
      int sound_L = analogRead(A0);
      int sound_R = analogRead(A1);
      //Serial.println(sound_R);


      if ( sound_L > thres || sound_R > thres) { // threshold =11 // 28 ll 11

        // Trigger for real sound onset
        digitalWrite(12, HIGH);

        // Check LED (ouside)
        digitalWrite(10,HIGH);

        // Play Wav file during 63s 
        delay(62000);     
        
        // for next track
        track++;
        // for next trial
        break;          
      }       
      
    }
  }
  else if (input == 50){  // warm up
    wTrig.trackPlaySolo(1);

      while(true){
        // Detect analog signal of sound(beep sound)
        int sound_L = analogRead(A0);
        int sound_R = analogRead(A1);
  
        if ( sound_L > thres || sound_R > thres) { // threshold =11 // 28 ll 11
  
          // Trigger for real sound onset
          digitalWrite(12, HIGH);
  
          // Check LED (ouside)
          digitalWrite(10,HIGH);
  
          // Play Wav file during 63s 
          delay(10000);     
          
          // for next track
          //track++;
          // for next trial
          break;          
        } 
     }
  }
  else if (input == 51){    // practice
    wTrig.trackPlaySolo(prac);

        // Check LED (ouside)
        digitalWrite(10,HIGH);
        // Play Wav file during 63s 
        delay(15000);     
        
        // for next track
        prac++;
        
      } 
}


              
