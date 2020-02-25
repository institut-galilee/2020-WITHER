# Control a LED Brightness with a variable resistance.

Without a microcontroller :
--------
Le potentiomètre agit directement sur l'intensité lumineuse de la LED.

![](image/image%20without/1.jpg)

![](image/image%20without/2.jpg)


With a microcontroller :
-------
Ici, on va récupérer la valeur de la resistance et l'envoyer au microcontrôleur. Celui-ci envoie un signal PWM à la led en fonction de la valeur de la résistance qu'il à reçu.

![](image/image%20with/1.jpg)

![](image/image%20with/2.jpg)

![](image/image%20with/3.jpg)

![](image/image%20with/4.jpg)

Voici le code utilisé pour : 

(On sait que la valeur de la résistance oscille entre 0 et 4095, donc on prend une résolution de 12 car 2^12=4096)

```arduino
const int potPin=15;//Resistance variable connected on GPIO15
int dutyCycle=0;//Variable to record variable resistance value
const int ledPin=9;//GPIO9
//PWM properties
const int freq=5000;
const int ledChannel=0;
const int resolution =12; //(0 à 4095)
void setup() { 
  //LED pwm functionnalities
  ledcSetup(ledChannel, freq, resolution);
  //Link the channel to the GPIO9 
  ledcAttachPin(ledPin,ledChannel);
}
void loop() {
  //read resistance value
  dutyCycle = analogRead(potPin);
  //change LED brightness 
  ledcWrite(ledChannel, dutyCycle);
  delay(15);
}
```
On privilégiera l'utilisation du microcontrôleur comme intermédiaire car cette méthode envoie un signal d'intensité variable, ce qui permet de modifier l'intensité lumineuse de la led beaucoup plus précisément.

