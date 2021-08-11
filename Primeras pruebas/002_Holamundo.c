// Comandos de ejecución
// gcc 002_Holamundo.c -o 002 -lwiringPi
// ./002

#include <wiringPi.h>		// librería para utilizar los pines de Raspberry pi

#define pin 7			// pin del LED en formato BOARD

void main(){
	int t=125;		// delay en micro segundos
	int x;
	wiringPiSetup();	// definir los comandos
	pinMode(pin,OUTPUT);	// Fijar el pin como salida
	for (x=0;x<10;x++){	// Ciclo para encender y apagar el LEDc
		digitalWrite(pin,HIGH);
		delay(t);
		digitalWrite(pin,LOW);
		delay(t);
	}
}
