#include <Servo.h>
#include <stdio.h>
#include <LiquidCrystal.h>



//DECLARATION DES COMPOSANTS

Servo servoMoteur;                              //On définit le.s servomoteur.s
LiquidCrystal lcd(13,12,11,10,9,8,7,6,5,4);   //Ainsi que l'écran LCD lcd(RS,E,DB0,...,DB7)

const int boutonPlay =6;                       //Bouton poussoir afin d'activer le programme  

const int f1=A0;                                 // On définit les pins des  flexomètres 
const int f2=A1;
const int f3=A2;
const int f4=A3; 
const int f5=A4;


 
// PARTIE FEEDBACK

struct pos_main{
  char name[20];
  int posO1;
  int posO2;
  int posO3;
  int posO4;
  int posO5;
};
struct pos_main data[]={
  {"Main Ouverte", 700,700,700,700,700},
  {"Main Fermee",900,900,900,900,900}

};

int valF1;                      // On définit les valeurs des flexomètres
int valF2;
int valF3;
int valF4;
int valF5;

const int nombreMesureMax = 300;    // 30 flexions/min - entrainement de 10 min => 300 mesures
int mesureF1[nombreMesureMax];
int mesureF2[nombreMesureMax];
int mesureF3[nombreMesureMax];
int mesureF4[nombreMesureMax];
int mesureF5[nombreMesureMax];
int nombreMesure=0;


void setup() {
  servoMoteur.attach(3);        //On attache le servomoteur au pin PWM 9

  pinMode(f1, INPUT);           //On définit les inputs du systèmes=>capteur de flexion
  pinMode(f2, INPUT);
  pinMode(f3, INPUT);
  pinMode(f4, INPUT);
  pinMode(f5, INPUT);

  pinMode(boutonPlay,INPUT);
  
  //pinMode(..., OUTPUT);       //Definir quel est notre sortie pour analyser les données
  lcd.begin(16, 2);
  Serial.begin(9600);         //Vitesse de 9600 bauds mais voir si la transmission est assez rapide
}

void loop() {

  int boutonState = digitalRead(boutonPlay); 
  if(boutonState == HIGH){          //Si on appuie sur le bouton play
    lcd.clear();
    lcd.print("Ouvrez et fermez votre main");
    activationResistance();
  }
  else{
    moyenneFlexion();
    desactivationResistance();
    lcd.clear();
    lcd.print("Bravo, vous avez fini ");
    lcd.setCursor(0, 1);
    lcd.print("Score : "+ String(moyenneFlexion)+"%");
    delay(20000);
    lcd.clear();
    
  }
  int valF1=analogRead(f1);       //On lit la valeur des Flexomètres
  int valF2=analogRead(f2);
  int valF3=analogRead(f3);
  int valF4=analogRead(f4);
  int valF5=analogRead(f5);

  /*Serial.println(valF1);      //On affiche les valeurs => faire des tests et voir si on doit map les données        
  Serial.println(valF2); 
  Serial.println(valF3);
  Serial.println(valF4);  
  Serial.println(valF5); 
  */
  valF1= map(valF1, 700,900,0,255);   //O -> doigt tendu.  255-> point fermé
  valF2= map(valF2, 700,900,0,255);
  valF3= map(valF3, 700,900,0,255);
  valF4= map(valF4, 700,900,0,255);
  valF5= map(valF5, 700,900,0,255);

  mesureF1[nombreMesure]+=valF1;    //On ajoute la valeur de flexion du doigt dans le tableau de mesure du même doigt
  mesureF2[nombreMesure]+=valF2;
  mesureF3[nombreMesure]+=valF3;
  mesureF4[nombreMesure]+=valF4;
  mesureF5[nombreMesure]+=valF5;
  nombreMesure++;
  if(nombreMesure >= nombreMesureMax){
    nombreMesure= nombreMesureMax-1;
  }


}

void activationResistance(){
  servoMoteur.write(180);       //Tester l'angle de rotation du servo 
}

void desactivationResistance(){
  servoMoteur.write(0);
}

float moyenneFlexion(){
  float moyenne1=0;         //Initialise Moyennes par doigt
  float moyenne2=0;
  float moyenne3=0;
  float moyenne4=0;
  float moyenne5=0;

  for (int i =0; i<nombreMesure; i++){    // On fait la somme des mesures
    moyenne1+=mesureF1[i];
    moyenne2+=mesureF2[i];
    moyenne3+=mesureF3[i];
    moyenne4+=mesureF4[i];
    moyenne5+=mesureF5[i];
  }
  moyenne1= moyenne1/nombreMesure;        // Moyennes par doigt
  moyenne2= moyenne2/nombreMesure;
  moyenne3= moyenne3/nombreMesure;
  moyenne4= moyenne4/nombreMesure;
  moyenne5= moyenne5/nombreMesure;


  float moyenneMain = (moyenne1+moyenne2+moyenne3+moyenne4+moyenne5)/5; //Moyenne flexion de la main entière
  float moyenneMain%= (moyenneMain*100)/255;

  return moyenneMain%;

}














