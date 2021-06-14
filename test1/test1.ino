#include <Servo.h>
#include <Arduino.h>

#define echoPin 7 // broche Echo
#define trigPin 8 // broche Trigger (declenchement)
#define LEDPin 12 // LED de la carte Ardiono (branché sur la broche 13)

int maximumRange = 50; // distance Maximale acceptée (en cm)
int minimumRange = 10;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance
Servo monServo;

// Motor A connections
int enA = 9;
int in1 = 5;
int in2 = 4;
// Motor B connections
int enB = 10;
int in3 = 3;
int in4 = 2;

void setup() {
    // Activer la communication série
    Serial.begin (9600);
    // Activer les broches
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT); // activer la LED sur la carte (si nécessaire)
    monServo.attach(6);
    // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
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
  // looker();
  // enginer();
  //directionControl();
  delay(1000);
  //speedControl();
  delay(1000);
}
