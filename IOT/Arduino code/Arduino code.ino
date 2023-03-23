#include <Arduino.h>

#define buzzerPin 2
#define greenLed 3

String button_clicked;
String axis_name;
String axis_value;

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {                   // Check if data is available to read
    String s = Serial.readStringUntil('\n');  // Read the incoming string until newline character
    parseString(s);
  }
}

void trigger_action() {
  if (button_clicked == "10") {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (button_clicked == "9") {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }else if(button_clicked == "3"){
    digitalWrite(greenLed, HIGH);
  }else if(button_clicked == "0"){
    digitalWrite(greenLed, LOW);
  }
  // Serial.println(message);
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