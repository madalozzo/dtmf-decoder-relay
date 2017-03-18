/*

DTMF Decoder Relay
 
Created by Saulo Madalozzo, saulo.zz@gmail.com March/2017
based on dtmf_loopback by Igor Ramos

Receive a DTMF (Dual Tone Multi Frequency) signal using a shield.

You will need:
- One Arduino or compatible.
- Dossant DTMF shield - https://www.seeedstudio.com/DTMF(Dual-Tone-Multi-Frequency)-Shield-p-1839.html
- Relays conected to 2, 3, 4 and 5, or other thing

This program is for activating digital outputs of Arduino based on DTMF tones.
Its intend to be used in radio stations to do some functions based on audio like turn on or off some equipments at exact moment.

It receive one tone (doesn't matter what), and must receive the second one in less than 1000ms (can be configured in code).
The second tone can be 2, 3, 4 or 5, and activate respective digital output for 500ms.
 */
 
//max interval between dtmf tones
#define WINDOW_INTERVAL 1000

int dr = 12; //dr goes high when data ready
int d0 = 11;
int d1 = 10;
int d2 = 9;
int d3 = 8;

char data_ready=0;
char data[4] = {0,0,0,0};
char data_ready_status=0;
char dr_serviced=0;

unsigned long last_read_time = 0;
unsigned long time_now = 0;

unsigned long rx_time = 0;

bool first_byte = false;

void setup() {      

     Serial.begin(9600);
    
     Serial.println("DTMF decoder relay");   
     
    // initialize the digital pin as an output.
    pinMode(d0, INPUT);    
    pinMode(d1, INPUT); 
    pinMode(d2, INPUT); 
    pinMode(d3, INPUT); 
    pinMode(dr, INPUT);
    
    pinMode(2, OUTPUT); 
    pinMode(3, OUTPUT); 
    pinMode(4, OUTPUT); 
    pinMode(5, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {

    data_ready_status = digitalRead(dr);
   
    if (data_ready_status) 
    {
      if (!dr_serviced)
      {
        time_now = millis();
        read_data();
        int digit = dtmf_digit();
        Serial.print(digit);
        if (!valid_window(time_now)){
            first_byte = false;
        }
        
        if (!first_byte){
            Serial.println (" first ");

            first_byte = true;
            last_read_time = millis();
        }
        else if(first_byte && valid_window(time_now)){
            Serial.println(" second ");
            if (digit >= 2 || digit <= 5){
              digitalWrite(digit, HIGH);   // sets the LED on
              delay(500);                  // waits for a second
              digitalWrite(digit, LOW); 
            }
        }

        dr_serviced =1; //clear received flag
        
      }
    }
    else{
      dr_serviced =0;
    }
}


  
// DTMF receive functions
int dtmf_digit ( void  )  //assemble the bits into a digit
{
  int dtmf_digit;

// dtmf digit is decoded per Page 5 Table 1 of chip datasheet
// http://www.zarlink.com/zarlink/mt8870d-datasheet-oct2006.pdf

  dtmf_digit = 8* data[3] +  4* data[2] + 2* data[1] + data[0] ;
  
  if (dtmf_digit==10)
    dtmf_digit =0;
    
  return dtmf_digit;
}


boolean valid_window(unsigned long time){
 if((time - last_read_time) >= WINDOW_INTERVAL){
    return false;
 }else{
   return true;
 }
}

void read_data(){
        data[0] = digitalRead(d0);
        data[1] = digitalRead(d1);
        data[2] = digitalRead(d2);
        data[3] = digitalRead(d3);
}


