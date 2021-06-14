#include <Servo.h>

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

int maximumRange = 50; // distance Maximale acceptée (en cm)
int minimumRange = 10;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance
Servo monServo;

void setup() {
    // Activer la communication série
    Serial.begin (9600);
    // Activer les broches
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT); // activer la LED sur la carte (si nécessaire)
    monServo.attach(6);
}

// Partie du code continuellement exécuté
// Son but est d'effectuer un cycle de détection pour déterminer
// la distance de l'objet le plus proche (par réverbération de
// l'onde sur ce dernier)
//
void looker(){
   
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
    if (distance <= minimumRange){
        /* Envoyer une valeur négative sur la liaison série.
           Activer la LED pour indiquer que l'erreur */
        Serial.println("trop court");
        digitalWrite(LEDPin, LOW);
    }
    else if(distance >= maximumRange ){
      Serial.println("trop long");
              digitalWrite(LEDPin, LOW);

    }
    
    else {
        /* Envoyer la distance vers l'ordinateur via liaison série.
           Eteindre la LED pour indiquer une lecture correcte. */
        Serial.println(distance);
         digitalWrite(LEDPin, HIGH);
         monServo.write(180);
         
          for (int position = 0; position <=180; position ++){ // on crée une variable position qui prend des valeurs entre 0 à 180 degrés
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(0);  // on attend 15 millisecondes
                Serial.println("toto");
    }

    }

    //Attendre 50ms avant d'effectuer la lecture suivante.
    delay(50);
}
void enginer(){
  
  for (int position = 0; position <=180; position ++){ // on crée une variable position qui prend des valeurs entre 0 à 180 degrés
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(0);  // on attend 15 millisecondes

    }

    for (int position = 180; position >=0; position --){ // cette fois la variable position passe de 180 à 0°
      monServo.write(position);  // le bras du servomoteur prend la position de la variable position
    delay(0);  // le bras du servomoteur prend la position de la variable position

    }
}
void loop() {
    // put your main code here, to run repeatedly:
   looker();
  // enginer();
}
