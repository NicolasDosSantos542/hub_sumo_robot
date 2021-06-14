#include <Arduino.h>

/* Senseur de distance Ultrason HC-SR04:
 VCC sur Arduino 5v
 GND sur Arduino GND
 Echo sur Arduino broche 7
 Trig sur Arduino broche 8

 Ce sketch/croquis est originaire de Virtualmix: http://goo.gl/kJ8Gl
 Il a été modifié par Winkle ink ici:
   http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 Puis modifié par ScottC le 10 Nov 2012:
   http://arduinobasics.blogspot.com/
 Finalement traduit par MCHobby.be pour le tutoriel:
   http://wiki.mchobby.be/index.php?title=HC-SR04
 */


#define echoPin 7 // broche Echo
#define trigPin 8 // broche Trigger (declenchement)
#define LEDPin 12 // LED de la carte Ardiono (branché sur la broche 13)

int maximumRange = 200; // distance Maximale acceptée (en cm)
int minimumRange = 0;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance

void setup() {
    // Activer la communication série
    Serial.begin (9600);
    // Activer les broches
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT); // activer la LED sur la carte (si nécessaire)
}

// Partie du code continuellement exécuté
// Son but est d'effectuer un cycle de détection pour déterminer
// la distance de l'objet le plus proche (par réverbération de
// l'onde sur ce dernier)
//
void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(12, HIGH);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(12, LOW);
    digitalWrite(10, HIGH);
    delay(100);
    // Envoi une impulsion de 10 micro seconde sur la broche "trigger"
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    // Attend que la broche Echo passe au niveau HAUT
    // retourne la durée
    duration = pulseIn(echoPin, HIGH);

    //Calculer la distance (en cm, basé sur la vitesse du son).
    distance = duration/58.2;

    // Si la distance mesurée est HORS des valeurs acceptables
    if (distance >= maximumRange || distance <= minimumRange){
        /* Envoyer une valeur négative sur la liaison série.
           Activer la LED pour indiquer que l'erreur */
        Serial.println("-1");
        digitalWrite(LEDPin, HIGH);
    }
    else {
        /* Envoyer la distance vers l'ordinateur via liaison série.
           Eteindre la LED pour indiquer une lecture correcte. */
        Serial.println(distance);
        Serial.println("cm");
        digitalWrite(LEDPin, LOW);
    }

    //Attendre 50ms avant d'effectuer la lecture suivante.
    delay(50);
}