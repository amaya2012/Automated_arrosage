
/* Projet arrosage automatique
- L'appli se connecte chaque jour à https://script.google.com/macros/s/AKfycbyzgNwg63VFdDYp4PzsluVC8VzzaFRrWnox_JyVtAUKl7SBMUQMz2siVh_RkDXO6ol_/exec?duration=15&eau_detect=1&comment=lastDays_2_lastHours_10
- Marco retourne: le code "Idx,Nb jour,Heure départ,durée (s),tempo durée,;1,3,18,10," au format JSON
- Récuperation de la la durée pour actionner une pompe d’arrosage via un relai.
- Un capteur sécurité d’eau est présent pour empêcher l’arrosage si l’eau manque.  */

#include "Wire.h"
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}