#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

#define POTPIN 0  // analog pin used to connect the potentiometer
#define BTNPIN 4  // analog pin used to connect the potentiometer

int val;    // variable to read the value from the analog pin
int btn_state, toggle;

void setup() {
	myservo.attach(2);  // attaches the servo on pin 9 to the servo object
	pinMode(BTNPIN, INPUT);
	Serial.begin(9600);
	toggle = 0;
	btn_state = 1;
}

void loop() {	
	if((digitalRead(BTNPIN) == HIGH) && (toggle == 0)){
		toggle = 1;
		if(btn_state == 1)
			btn_state = 0;
		else
			btn_state = 1;
	}
	else if (digitalRead(BTNPIN) == LOW){
		toggle = 0;
	}

	if(btn_state == 1){
		Serial.print("Reading from pot: ");
        Serial.println(val);
		val = analogRead(POTPIN);            // reads the value of the potentiometer (value between 0 and 1023)
		val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
	}
	else{
		Serial.println("Fixed pos");
		val = 90;	
	}	
	myservo.write(val);
	delay(15);
}