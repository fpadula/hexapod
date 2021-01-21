#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "ota.h"
#include <Arduino.h>
#include <Servo.h>
#include "ServoMovement.h"
#include "Easings.h"
#include "ServoPins.h"

#define NO_SERVOS 12

Servo *servos;
ServoMovement **moves;
unsigned long prev_mills;
int curr_move;
void setup(){
    curr_move = 0;
	// Setup needed for OTA
	// Serial.begin(115200);
	// Serial.println("Booting");
	// WiFi.setHostname("hexapod");
	WiFi.mode(WIFI_STA);
	WiFi.begin("VenusWifi", "bisgatafuta");
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}
	
	ota_setup();
	//  My setup onwards	
	
	if (!MDNS.begin("hexapod")) { //http://esp32.local
		// Serial.println("Error setting up MDNS responder!");
		while (1) {
			delay(1000);
		}
    }

    servos = new Servo[NO_SERVOS];    
    servos[RIGHT_TOP_UPPER_KNEE].attach(RIGHT_TOP_UPPER_KNEE_PIN);    
    servos[RIGHT_TOP_LOWER_KNEE].attach(RIGHT_TOP_LOWER_KNEE_PIN);    
    servos[RIGHT_MIDDLE_UPPER_KNEE].attach(RIGHT_MIDDLE_UPPER_KNEE_PIN);    
    servos[RIGHT_MIDDLE_LOWER_KNEE].attach(RIGHT_MIDDLE_LOWER_KNEE_PIN);    
    servos[RIGHT_BOTTOM_UPPER_KNEE].attach(RIGHT_BOTTOM_UPPER_KNEE_PIN);    
    servos[RIGHT_BOTTOM_LOWER_KNEE].attach(RIGHT_BOTTOM_LOWER_KNEE_PIN);    
    servos[LEFT_TOP_UPPER_KNEE].attach(LEFT_TOP_UPPER_KNEE_PIN);
    servos[LEFT_TOP_LOWER_KNEE].attach(LEFT_TOP_LOWER_KNEE_PIN);
    servos[LEFT_BOTTOM_UPPER_KNEE].attach(LEFT_BOTTOM_UPPER_KNEE_PIN);
    servos[LEFT_BOTTOM_LOWER_KNEE].attach(LEFT_BOTTOM_LOWER_KNEE_PIN);
    servos[LEFT_MIDDLE_UPPER_KNEE].attach(LEFT_MIDDLE_UPPER_KNEE_PIN);
    servos[LEFT_MIDDLE_LOWER_KNEE].attach(LEFT_MIDDLE_LOWER_KNEE_PIN);
	
    for(int i = 0; i < NO_SERVOS; i++){
        servos[i].write(90);        
    }

    // smr = new ServoMovement(135.0f,-45.0f,2500.0f, Easings::linear);
    // sml = new ServoMovement(135.0f,-45.0f,2500.0f, false, Easings::linear);

    // smr->add_servo(&servos[RIGHT_TOP_UPPER_KNEE]);
    // smr->add_servo(&servos[RIGHT_MIDDLE_UPPER_KNEE]);
    // smr->add_servo(&servos[RIGHT_BOTTOM_UPPER_KNEE]);

    // sml->add_servo(&servos[LEFT_TOP_UPPER_KNEE]);
    // sml->add_servo(&servos[LEFT_BOTTOM_UPPER_KNEE]);
    // sml->add_servo(&servos[LEFT_MIDDLE_UPPER_KNEE]);
    moves = new ServoMovement *[4];
    moves[0] = new ServoMovement(90.0f, -45.0f, 1000.0f, Easings::linear);
    moves[0]->add_servo(&servos[RIGHT_MIDDLE_LOWER_KNEE]);
    moves[1] = new ServoMovement(45.0f, 90.0f, 1000.0f, Easings::linear);
    moves[1]->add_servo(&servos[RIGHT_MIDDLE_UPPER_KNEE]);
    moves[2] = new ServoMovement(45.0f, 45.0f, 1000.0f, Easings::linear);
    moves[2]->add_servo(&servos[RIGHT_MIDDLE_LOWER_KNEE]);
    moves[3] = new ServoMovement(135.0f, -90.0f, 1000.0f, Easings::linear);
    moves[3]->add_servo(&servos[RIGHT_MIDDLE_UPPER_KNEE]);
}

void loop() {
	float dt;
	ArduinoOTA.handle();
	yield();

	dt = (float) (millis() - prev_mills);
	prev_mills = millis();
    if(!moves[curr_move]->step(dt)){
        curr_move++;
        if(curr_move > 3){
            curr_move = 0;
            for(int i = 0; i < 4; i++)
                moves[i]->reset();
        }
    }	
}