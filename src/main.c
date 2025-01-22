#include "Wire.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DUREE_ARROSAGE 10
#define DURRE_VEILLE 60 * 1000000

#define PIN_SECURE 23  // Pin pour la détection d'eau
#define PIN_RELAIS 19   // Pin pour l'activation de la pompe
#define LED_BUILTIN 2  // LED intégrée

const char* ssid = "fbx_buceo";
const char* password = "1970C1998A";

// Fonction pour vérifier le capteur de sécurité d'eau
bool isWaterAvailable() {
  int buttonState = digitalRead(PIN_SECURE); // Lecture de l'état du capteur
  return buttonState == LOW; // Si LOW, l'eau est disponible
}

// Fonction pour activer la pompe
void activatePump(int t) {
  digitalWrite(LED_BUILTIN, HIGH); // Active la pompe
  //digitalWrite(PIN_RELAIS, HIGH); // Active la pompe
  delay(1000 * t);              // Attente de t secondes
  digitalWrite(LED_BUILTIN, LOW); // Arrête la pompe
  //digitalWrite(PIN_RELAIS, LOW); // Arrête la pompe

}

void connectWifi(){
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);              // Initialisation de la communication série
  delay(1000);

  // Initilaisation des Pins
  pinMode(PIN_SECURE, INPUT_PULLUP); // Configure GPIO23 en entrée avec résistance pull-up interne
  pinMode(PIN_RELAIS, OUTPUT);        // Configure GPIO19 en sortie
  pinMode(LED_BUILTIN, OUTPUT);      // Configure la LED intégrée en sortie
  Serial.println("Initialisation du système...");


  // Initialisation du WIFI
  connectWifi();
}

void loop() {
  // Vérifier le capteur de sécurité
  if (isWaterAvailable()) { 

    Serial.println("Activation de la pompe...");
    activatePump(DUREE_ARROSAGE);
    Serial.println("Arrosage terminé...");
    delay(100);
    Serial.println("Passage en veille pour 1 minute...");
    esp_deep_sleep(DURRE_VEILLE); // Veille pendant DURRE_VEILLE secondes (1 minute)
    

  } else { //
    Serial.println("Pas d'eau disponible. Attente...");
  }
  delay(1000); // Petit délai pour éviter de surcharger le processeur
}
