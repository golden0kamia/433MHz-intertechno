#ifndef Remote_h
#define Remote_h

void Remote_init(char sendPin, char recievePin, char repaeat = 5);
void Remote_send(int adresse, int group, char unit, char state);

#endif



/*
//-------- Global variables --------//
char pin = 4;
int repeat = 4;
int i = 0;
int time = 260; //initialize here for all the functions

//-------- Functions --------//
void sendStartPulse();
void sendAdress(int adress);
void sendUnit(int unit);
void sendStopPulse();
void sendBit(int bitsend);

//-------- Main --------//
int main(int argc, char *argv[])
{
	//-------- Setting up --------//
	wiringPiSetupGpio();
	pinMode(pin, OUTPUT);
	int adress = ctoi(argv[1]);
	int status = ctoi(argv[2]);
	int group  = ctoi(argv[3]);
	int unit   = ctoi(argv[4]);
	time       = ctoi(argv[5]);
	printf("run \"%s\" with parameter:\nadress:%d\nstatus:%d\ngroup:%d\nunit:%d\ntime:%d\n", argv[0], adress, status, group, unit, time);
	
	//-------- Send information --------//
	for (int y = 0; y < repeat; y++)
	{
		sendStartPulse();
		sendAdress(adress);
		sendBit(group);
		sendBit(status);
		sendUnit(unit);
		sendStopPulse();
	}
	return 0;
}

void sendStartPulse()
{
	digitalWrite(pin, HIGH);
	delayMicroseconds(time);
	digitalWrite(pin, LOW);
	delayMicroseconds(time * 10 + (time >> 1));
}

void sendAdress(int adress)
{
	for (i = 25; i>=0; i--)
	{
		sendBit((adress >> i) & 1);
	}
}

void sendUnit(int unit)
{
	for (i = 3; i>=0; i--)
	{
		sendBit((unit >> i) & 1);
	}
}

void sendStopPulse()
{
	digitalWrite(pin, HIGH);
	delayMicroseconds(time);
	digitalWrite(pin, LOW);
	delayMicroseconds(time * 40);
}

void sendBit(int bitSend)
{
	if (bitSend)
	{
		digitalWrite(pin, HIGH);
		delayMicroseconds(time);
		digitalWrite(pin, LOW);
		delayMicroseconds(time * 5);
		digitalWrite(pin, HIGH);
		delayMicroseconds(time);
		digitalWrite(pin, LOW);
		delayMicroseconds(time);
	} else {
		digitalWrite(pin, HIGH);
		delayMicroseconds(time);
		digitalWrite(pin, LOW);
		delayMicroseconds(time);
		digitalWrite(pin, HIGH);
		delayMicroseconds(time);
		digitalWrite(pin, LOW);
		delayMicroseconds(time * 5);
	}
}
*/