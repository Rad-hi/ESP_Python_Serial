/* 
 * Written by Radhi SGHAIER: https://github.com/Rad-hi
 * --------------------------------------------------------
 * Do whatever you want with the code ...
 * If this was ever useful to you, and we happened to meet on the street, 
 * I'll appreciate a cup of dark coffee, no sugar please.
 * --------------------------------------------------------
 * Build a command based communication between and ESP32 and a Python script:
 *    
 *    Default      --> Blink LED each second
 *    
 *    If received: --> "bxxxx\n" : change the default delay (1 second) to xxxx
 *                 --> "oxxxx\n" : LED ON for xxxx
 *                 --> "fxxxx\n" : LED OFF for xxxx
 *                 --> "hxxxx\n" : Halt --> Just stop working forever
 */

// Communication buffers lengths
#define MAX_BUFF_LEN        255 
#define CMD_BUFF_LEN        6

// Satates of the LED
#define B_STATE             0       // Normal blinking state
#define O_STATE             1       // ON for delay state
#define F_STATE             2       // OFF for delay state
#define H_STATE             3       // Halt state

// LED configs
#define LED_PIN             16
#define DEFAULT_DELAY       1000

// Globals
char c; // IN char
char str[CMD_BUFF_LEN];
uint8_t idx = 0; // Reading index

uint8_t state = B_STATE; // Default state
int delay_t = DEFAULT_DELAY; // Default printing delay
unsigned long prev_time;


// Func prototypes
uint8_t interpret(char);
void toggle_led();


void setup() {
  // Config serial port
  Serial.begin(115200);

  // Config LED
  pinMode(LED_PIN, OUTPUT);

  // 
  prev_time = millis();
}

void loop() {
  
  // Parse incoming command
  if(Serial.available() > 0){ // There's a command
    
    c = Serial.read(); // Read one byte
    
    if(c != '\n'){ // Still reading
      str[idx++] = c; // Parse the string byte (char) by byte
    }
    else{ // Done reading
      str[idx] = '\0'; // Convert it to a string
      
      // Determine nature of the command
      state = interpret(str[0]);
      
      // strtol(string, Ref pointer, Base[Hex-->16])
      delay_t = strtol(str+1, NULL, 10); // str+1 --> exclude the first char
      /* Some input checking could've been done here (like b15f2 --> invalid) */

      // Reset reading index 
      idx = 0;
    }
  }
  else{ // No input from commander
    state = B_STATE;
  }

  // Main state machine
  switch(state){
    case B_STATE: // This is the default blinking state
      if(millis() - prev_time > delay_t){
        toggle_led();
        prev_time = millis();
      }
      break;
      
    case O_STATE: // ON for delay state
      digitalWrite(LED_PIN, HIGH);
      delay(delay_t);
      break;
    
    case F_STATE: // OFF for dealy state
      digitalWrite(LED_PIN, LOW);
      delay(delay_t);
      break;
    
    case H_STATE: // do nothing
      while(1);
      break;
    
    default: break;
  }
  
}

// Func definition

uint8_t interpret(char c){
  switch(c){
    case 'b':
      return B_STATE;
      break;

    case 'o':
      return O_STATE;
      break;

    case 'f':
      return F_STATE;
      break;

    case 'h':
      return H_STATE;
      break;

    default: Serial.println("UNKNOWN");
  }
  return state;
}

void toggle_led(){
  // Toggle the state of the LED pin
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
