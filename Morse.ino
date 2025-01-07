/*
  Blink Morse Code

  Turns an LED on and off to signal a Morse Code message, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified  8 May 2014 by Scott Fitzgerald
  modified  2 Sep 2016 by Arturo Guadalupi
  modified  8 Sep 2016 by Colby Newman
  modified 29 Dec 2024 by Dave's Think Tank
    - converted from Blink to S-O-S
  modified 6 Jan 2025 by Dave's Think Tank
    - converted from S-O-S to full Morse Code interpreter

  The original Blink code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

String Message = "your message here :)"; // no capitals

int MorseCode[47][8] = { // character, number of dots and dashes, Morse code for the character, finish with zeroes
                             {'a', 2, 0, 1, 0, 0, 0, 0}, // a
                             {'b', 4, 1, 0, 0, 0, 0, 0}, // b
                             {'c', 4, 1, 0, 1, 0, 0, 0}, // c
                             {'d', 3, 1, 0, 0, 0, 0, 0}, // d
                             {'e', 1, 0, 0, 0, 0, 0, 0}, // e
                             {'f', 4, 0, 0, 1, 0, 0, 0}, // f
                             {'g', 3, 1, 1, 0, 0, 0, 0}, // g
                             {'h', 4, 0, 0, 0, 0, 0, 0}, // h
                             {'i', 2, 0, 0, 0, 0, 0, 0}, // i
                             {'j', 4, 0, 1, 1, 1, 0, 0}, // j
                             {'k', 3, 1, 0, 1, 0, 0, 0}, // k
                             {'l', 4, 0, 1, 0, 0, 0, 0}, // l
                             {'m', 2, 1, 1, 0, 0, 0, 0}, // m
                             {'n', 2, 1, 0, 0, 0, 0, 0}, // n
                             {'o', 3, 1, 1, 1, 0, 0, 0}, // o
                             {'p', 4, 0, 1, 1, 0, 0, 0}, // p
                             {'q', 4, 1, 1, 0, 1, 0, 0}, // q
                             {'r', 3, 0, 1, 0, 0, 0, 0}, // r
                             {'s', 3, 0, 0, 0, 0, 0, 0}, // s
                             {'t', 1, 1, 0, 0, 0, 0, 0}, // t
                             {'u', 3, 0, 0, 1, 0, 0, 0}, // u
                             {'v', 4, 0, 0, 0, 1, 0, 0}, // v
                             {'w', 3, 0, 1, 1, 0, 0, 0}, // w
                             {'x', 4, 1, 0, 0, 1, 0, 0}, // x
                             {'y', 4, 1, 0, 1, 1, 0, 0}, // y
                             {'z', 4, 1, 1, 0, 0, 0, 0}, // z
                             {'1', 5, 0, 1, 1, 1, 1, 0}, // 1
                             {'2', 5, 0, 0, 1, 1, 1, 0}, // 2
                             {'3', 5, 0, 0, 0, 1, 1, 0}, // 3
                             {'4', 5, 0, 0, 0, 0, 1, 0}, // 4
                             {'5', 5, 0, 0, 0, 0, 0, 0}, // 5
                             {'6', 5, 1, 0, 0, 0, 0, 0}, // 6
                             {'7', 5, 1, 1, 0, 0, 0, 0}, // 7
                             {'8', 5, 1, 1, 1, 0, 0, 0}, // 8
                             {'9', 5, 1, 1, 1, 1, 0, 0}, // 9
                             {'0', 5, 1, 1, 1, 1, 1, 0}, // 0
                             {',', 6, 1, 1, 0, 0, 1, 1}, // ,
                             {'.', 6, 0, 1, 0, 1, 0, 1}, // .
                             {'?', 6, 0, 0, 1, 1, 0, 0}, // ?
                             {'"', 6, 0, 1, 0, 0, 1, 0}, // "
                             {':', 6, 1, 1, 1, 0, 0, 0}, // :
                             {'\'',6, 0, 1, 1, 1, 1, 0}, // ' single quote
                             {'-', 6, 1, 0, 0, 0, 0, 1}, // -
                             {'/', 5, 1, 0, 0, 1, 0, 0}, // /
                             {'(', 5, 1, 0, 1, 1, 0, 0}, // (
                             {')', 6, 1, 0, 1, 1, 0, 1}, // )
                             {' ', 0, 0, 0, 0, 0, 0, 0}  //   space

};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
int i = 0, j = 0, k = 0;
unsigned long dot = 200; // length of a dot

while (Message[i]) {
  for (j = 0; j < 46; ++j) {
    if (MorseCode[j][0] == Message[i]) break;
  }
  if (j >= 46) delay(2 * dot);                   // space, off for total 7 dots
  else 
    for (k = 2; k < 2 + MorseCode[j][1]; ++k) {
      digitalWrite(LED_BUILTIN, HIGH);           // turn the LED on (HIGH is the voltage level)
      delay(MorseCode[j][k] ? 3 * dot: dot);     // wait for a dot or dash
      digitalWrite(LED_BUILTIN, LOW);            // turn the LED off by making the voltage LOW
      delay(dot);                                // off for a dot
    }
    delay (2 * dot);                             // end of letter, off for total 3 dots
  ++i;
}
delay (7 * dot);                                 // end of message, off for total 10 dots
}