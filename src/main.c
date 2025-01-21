
/* Projet arrosage automatique
- L'appli se connecte chaque jour à https://script.google.com/macros/s/AKfycbyzgNwg63VFdDYp4PzsluVC8VzzaFRrWnox_JyVtAUKl7SBMUQMz2siVh_RkDXO6ol_/exec?duration=15&eau_detect=1&comment=lastDays_2_lastHours_10
- Marco retourne: le code "Idx,Nb jour,Heure départ,durée (s),tempo durée,;1,3,18,10," au format JSON
- Récuperation de la la durée pour actionner une pompe d’arrosage via un relai.
- Un capteur sécurité d’eau est présent pour empêcher l’arrosage si l’eau manque.  */

#include "Wire.h"
#include <Arduino.h>

#define PIN_SECURE 23
#define PIN_POMPE 19
#define LED_BUILTIN 2  // la LED intégrée 

//initialiser les pin
//Verifie l'heure qu'il est, s'il est l'heure on s'allume
//Vérifie capteur securité d'eau
//On recupère temps d'arrosage
//Active le temps ecessaire
//Veille

// Fonction pour vérifier le capteur de sécurité d'eau
bool isWaterAvailable() {
  // Lecture de l'état du capteur
  int buttonState = digitalRead(PIN_SECURE);

  // Si le capteur détecte un manque d'eau (état LOW), retourner false
  return buttonState == HIGH;
}



void setup() {
  // put your setup code here
  Serial.begin(115200);                  // Initialisation de la communication série
  pinMode(PIN_SECURE, INPUT_PULLUP); // Configure GPIO23 en entrée avec résistance pull-up interne
  pinMode(PIN_POMPE, OUTPUT); // Configure GPIO19 en en sortie
  pinMode(LED_BUILTIN, OUTPUT);          // Configure la LED intégrée en sortie

  Serial.println("Initialisation du système...");

}

void loop() {

  // Vérifier le capteur de sécurité
  if (isWaterAvailable()) {
    digitalWrite(LED_BUILTIN, HIGH); // Allume la LED pour indiquer que l'eau est disponible
    Serial.println("L'eau est disponible. Prêt à arroser !");
  } else {
    digitalWrite(LED_BUILTIN, LOW); // Éteint la LED si l'eau manque
    Serial.println("Pas d'eau disponible. Attente...");
  }
}
