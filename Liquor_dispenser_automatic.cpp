#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int PIN_IR4=3;
const int PIN_IR3=4;
const int PIN_IR2=5;
const int PIN_IR1=6;
const int PIN_SERVO=2;
const int PIN_POMPA=9;

const int POS_REPAUS=0;
const int POS_IR4=30;
const int POS_IR3=70;
const int POS_IR2=113;
const int POS_IR1=153;

const unsigned long TIMP_DETECTIE_NECESAR=5000;
const int TIMP_POMPA_ON=1500;

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servoMotor;

struct SensorData{
  int pin;
  int unghiServo;
  int idPahar;
  bool esteDetectat;
  bool esteServit;
  bool inCoada;
  unsigned long timpInceputDetectie;
};

SensorData senzori[4];
int coada[10];
int coadaHead=0;
int coadaTail=0;

void setup(){
  pinMode(PIN_POMPA,OUTPUT);
  digitalWrite(PIN_POMPA,LOW);

  senzori[0]={PIN_IR1,POS_IR1,1,false,false,false,0};
  senzori[1]={PIN_IR2,POS_IR2,2,false,false,false,0};
  senzori[2]={PIN_IR3,POS_IR3,3,false,false,false,0};
  senzori[3]={PIN_IR4,POS_IR4,4,false,false,false,0};

  for(int i=0;i<4;i++) pinMode(senzori[i].pin,INPUT);

  servoMotor.attach(PIN_SERVO);
  servoMotor.write(POS_REPAUS);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("   Pornire   ");
  delay(2000);
  lcd.clear();
  lcd.print("Astept pahare...");
}

void loop(){
  verificaSenzori();
  proceseazaCoada();
}

void verificaSenzori(){
  for(int i=0;i<4;i++){
    bool detectatAcum=!digitalRead(senzori[i].pin);
    if(detectatAcum){
      if(!senzori[i].esteDetectat){
        senzori[i].esteDetectat=true;
        senzori[i].timpInceputDetectie=millis();
      }
      if((millis()-senzori[i].timpInceputDetectie>=TIMP_DETECTIE_NECESAR)){
        if(!senzori[i].esteServit&&!senzori[i].inCoada) adaugaInCoada(i);
      }
    }else{
      senzori[i].esteDetectat=false;
      senzori[i].esteServit=false;
      senzori[i].inCoada=false;
    }
  }
}

void adaugaInCoada(int indexSenzor){
  coada[coadaTail]=indexSenzor;
  coadaTail++;
  if(coadaTail>=10) coadaTail=0;
  senzori[indexSenzor].inCoada=true;
}

void proceseazaCoada(){
  if(coadaHead!=coadaTail){
    int indexCurent=coada[coadaHead];
    SensorData &s=senzori[indexCurent];
    if(!s.esteDetectat){eliminaDinCoada();return;}

    servoMotor.write(s.unghiServo);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pahare ramase:");
    lcd.print(catePahareInCoada());

    lcd.setCursor(0,1);
    lcd.print("Umplu: Pahar ");
    lcd.print(s.idPahar);

    delay(2000);

    long timpRamasDePompat=TIMP_POMPA_ON;
    int pulsOn=70;
    int pulsOff=150;

    while(timpRamasDePompat>0){
      digitalWrite(PIN_POMPA,HIGH);
      delay(pulsOn);
      digitalWrite(PIN_POMPA,LOW);
      delay(pulsOff);
      timpRamasDePompat-=pulsOn;
    }

    digitalWrite(PIN_POMPA,LOW);
    s.esteServit=true;
    s.inCoada=false;
    eliminaDinCoada();

    if(coadaHead==coadaTail){
      servoMotor.write(POS_REPAUS);
      lcd.clear();
      lcd.print("   Finalizat!   ");
      lcd.setCursor(0,1);
      lcd.print("Astept pahare...");
    }
  }
}

void eliminaDinCoada(){
  coadaHead++;
  if(coadaHead>=10) coadaHead=0;
}

int catePahareInCoada(){
  if(coadaTail>=coadaHead) return coadaTail-coadaHead;
  else return (10-coadaHead)+coadaTail;
}
