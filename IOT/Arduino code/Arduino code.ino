#include <Arduino.h>

#define buzzerPin 2
#define greenLed 3
// shift register
#define stcp_Pin 6
#define shcp_Pin 5
#define ds_Pin 4


bool button0State = false;
bool button9State = false;
bool button10State = false;

String button_clicked;
String axis_name;
String axis_value;

const byte continuos_strip[] = {0B10000000, 0B11000000, 0B11100000, 0B11110000, 0B11111000, 0B11111100, 0B11111110, 0B11111111};
int continuos_strip_position = 0;

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(stcp_Pin, OUTPUT);
  pinMode(shcp_Pin, OUTPUT);
  pinMode(ds_Pin, OUTPUT);
}

void loop() {
  if (Serial.available()) {                   // Check if data is available to read
    String s = Serial.readStringUntil('\n');  // Read the incoming string until newline character
    parseString(s);
  }
  digitalWrite(stcp_Pin, LOW);
  shiftOut(ds_Pin, shcp_Pin, LSBFIRST, continuos_strip[continuos_strip_position]);
  digitalWrite(stcp_Pin, HIGH);
}

void trigger_action() {
  if (button_clicked == "0") {
    button0State = !button0State;
    digitalWrite(greenLed, button0State ? HIGH : LOW);
  } else if (button_clicked == "1") {
    // do something
  }else if (button_clicked == "2") {
    // do something
  }else if (button_clicked == "3") {
    // do something
  } else if (button_clicked == "4") {
    // do something
  }else if (button_clicked == "5") {
    // do something
  }else if (button_clicked == "6") {
    // do something
  }else if (button_clicked == "7") {
    // do something
  }else if (button_clicked == "8") {
    // do something
  }else if (button_clicked == "9") {
    button9State = !button9State;
    digitalWrite(LED_BUILTIN, button9State ? HIGH : LOW);
  } else if (button_clicked == "10") {
    button10State = !button10State;
    digitalWrite(buzzerPin, button10State ? HIGH : LOW);
  }else if (button_clicked == "11") {
    // do something
  }else if (button_clicked == "12") {
    // do something
  }else if (button_clicked == "13") {
    if(continuos_strip_position > 0 && continuos_strip_position <= 7){
      continuos_strip_position--;
    }
  }else if (button_clicked == "14") {
    if(continuos_strip_position >= 0 && continuos_strip_position < 7){
      continuos_strip_position++;
    }
  }else if (button_clicked == "15") {
    // do something
  }
}

void parseString(String s) {
  String output = "";
  int colon_pos = s.indexOf(":");
  String s1 = s.substring(0, colon_pos);
  String s2 = s.substring(colon_pos + 1);
  String s3 = "";
  String s4 = "";

  if (s2 != "None") {
    int slash_pos = s2.indexOf("/");
    s3 += s2.substring(0, slash_pos);
    s4 += s2.substring(slash_pos + 1);
  }

  button_clicked = s1;
  axis_name = s3;
  axis_value = s4;


  output += s1 + "\t";
  output += s3 + "\t";
  output += s4;

  trigger_action();
  Serial.println(output);
}