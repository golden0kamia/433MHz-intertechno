#include "Remote.h"

char sp = 0;
char rp = 0;
char re = 0;
int t = 0;

void Remote_init(char sendsp, char recievesp = 0, char repaeat = 5, int time = 260){
	sp = sendsp;
	spMode(sp, OUTPUT);
	rp = recievesp;
	spMode(rp, INPUT);
	re = repeat;
	t = time;
}

void Remote_send(int adresse, int group, char unit, char state){
	for (int y = 0; y < re; y++){
		sendStartPulse();
		sendAdress(adress);
		sendBit(group);
		sendBit(status);
		sendUnit(unit);
		sendStopPulse();
	}
}

void sendStartPulse(){
	digitalWrite(sp, HIGH);
	delayMicroseconds(t);
	digitalWrite(sp, LOW);
	delayMicroseconds(t * 10 + (t >> 1));
}

void sendAdress(int adress){
	for (i = length(adress); i>=0; i--){
		sendBit((adress >> i) & 1);
	}
}

void sendUnit(char unit){
	for (i = length(unit); i>=0; i--){
		sendBit((unit >> i) & 1);
	}
}

void sendBit(char bitSend){
	if (bitSend){
		digitalWrite(sp, HIGH);
		delayMicroseconds(t);
		digitalWrite(sp, LOW);
		delayMicroseconds(t * 5);
		digitalWrite(sp, HIGH);
		delayMicroseconds(t);
		digitalWrite(sp, LOW);
		delayMicroseconds(t;
	} else {
		digitalWrite(sp, HIGH);
		delayMicroseconds(t;
		digitalWrite(sp, LOW);
		delayMicroseconds(t;
		digitalWrite(sp, HIGH);
		delayMicroseconds(t);
		digitalWrite(sp, LOW);
		delayMicroseconds(t * 5);
	}
}

void sendStopPulse(){
	digitalWrite(sp, HIGH);
	delayMicroseconds(t);
	digitalWrite(sp, LOW);
	delayMicroseconds(t * 40);
}
