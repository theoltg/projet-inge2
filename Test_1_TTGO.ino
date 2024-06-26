#include <TFT_eSPI.h>

// Set up de la pin de un flexsensor
const int flexSensorPin = 27;

// Set up l'écran de la TTGO
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);


//Set up de la batterie OPTIONNEL

/*const int ADC_PIN = ...;
int vref =5;                       //Batterie de Vcc=5V
float charge_batterie=0.0;          // Charge de la batterie afin de l'afficher
*/

//Set up de l'écran 135x240
int centreX= 67 ;    
int centreY= 120 ;

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.fillScreen(TFT_WHITE);
}

void loop() {
  int valFlex=analogRead(flexSensorPin);
  //valFlex= map(valFlex, 700,900,0,255);
  affichage_Ecran(valFlex);
  delay(100);

}

void affichage_Ecran(int valFlex){

  sprite.createSprite(135, 280);
  sprite.fillSprite(TFT_BLACK);

  //Affichage batterie OPTIONNEL
  // A coder

  sprite.setTextDatum(TC_DATUM);
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("Flex :", centerX, 40, 4);
  sprite.drawNumber(valFlex, centerX, 75, 6);
  sprite.pushSprite(0,0);

}
