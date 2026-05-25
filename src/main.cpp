#include <Arduino.h>
#include <Ultrasonic.h>
#include "7_Segment.hpp"

#define POT_R 14
#define POT_G 27
#define POT_B 26

#define RED 25
#define GREEN 33
#define BLUE 32

#define A 23
#define B 16
#define C 21
#define D 19
#define E 18
#define FS 5
#define G 4

#define TRIGGER_PIN  13
#define ECHO_PIN     17

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Segment mySegment(A, B, C, D, E, FS, G);

int barvy[] = {0,0,0};
int ledky[] = {25,33,32};
int hracbarvy[] = {0,0,0};


int body = 0;
int streak = 0;

void cil(int barvy[], int ledky[]);
void prubeh(int hracbarvy[]);
int vyhodnoceni(int barvy[], int hracbarvy[]);

void setup(){
    Serial.begin(115200);

    mySegment.test();

    delay(1000);

    pinMode(POT_R, INPUT);
    pinMode(POT_G, INPUT);
    pinMode(POT_B, INPUT);

    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);

    analogWrite(RED, 255);
    delay(500);
    analogWrite(GREEN, 255);
    delay(500);
    analogWrite(BLUE, 255);

    delay(1000);

    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);

    randomSeed(analogRead(34));

    mySegment.vykresli(body);
}

void loop() {
  float msecToCM = 999;
  long microsec = ultrasonic.timing();

  msecToCM = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.println(msecToCM);

  if(msecToCM < 10 && msecToCM > 2){
    cil(barvy, ledky);
    prubeh(hracbarvy);
    int score = vyhodnoceni(barvy, hracbarvy);

    if(score == 0){
        body = 0;
        streak = 0;
    } else {
        body += score;
        streak++;
    }

    mySegment.vykresli(body);

    for(int i = 0; i < 3; i++){
        analogWrite(ledky[i], 0);
    }
    delay(5000);
  }

  /*for(int i = 0; i < 16; i++){
    mySegment.vykresli(i);
    delay(1000);
  }*/
}

/**
 * @brief Vygeneruje náhodnou cílovou barvu a zobrazí ji na LED.
 *
 * Funkce nastaví náhodné RGB hodnoty (0–255), zapíše je do LED,
 * poté provede blikání jako vizuální upozornění.
 *
 * @param barvy Pole, kam se uloží cílové RGB hodnoty (R, G, B)
 * @param ledky Pole pinů LED diod (R, G, B)
 */

void cil(int barvy[], int ledky[]){
    for(int i = 0; i < 3; i++){
        barvy[i] = random(256);
        analogWrite(ledky[i], barvy[i]);
    }
    delay(7000);

    Serial.println(barvy[0]);
    Serial.println(barvy[1]);
    Serial.println(barvy[2]);

    int cas = 0;

    while(cas < 3){
        for(int i = 0; i < 3; i++){
            analogWrite(ledky[i], 0);
        }
        delay(500);
        for(int i = 0; i < 3; i++){;
            analogWrite(ledky[i], barvy[i]);
        }
        delay(500);
        cas++;
    }
}

/**
 * @brief Zpracovává průběh hry a načítá hráčovu barvu.
 *
 * Funkce čeká, dokud hráč není v dosahu senzoru, poté čte hodnoty
 * potenciometrů a převádí je na RGB hodnoty. Tyto hodnoty ukládá
 * do pole hracbarvy.
 *
 * @param hracbarvy Pole, kam se uloží RGB hodnota hráče (R, G, B)
 */

void prubeh(int hracbarvy[]){
    int red = 0, green = 0, blue = 0;

    float msecToCM = 999;

    while(msecToCM > 10 || msecToCM < 2){
        long microsec = ultrasonic.timing();

        msecToCM = ultrasonic.convert(microsec, Ultrasonic::CM);
        Serial.println(msecToCM);

        int r = analogRead(POT_R);
        int g = analogRead(POT_G);
        int b = analogRead(POT_B);

        red = map(r, 0, 4095, 0, 255);
        green = map(g, 0, 4095, 0, 255);
        blue = map(b, 0, 4095, 0, 255);

        delay(100);

        analogWrite(RED, red);
        analogWrite(GREEN, green);
        analogWrite(BLUE, blue);        
    }

    hracbarvy[0] = red;
    hracbarvy[1] = green;
    hracbarvy[2] = blue;
}

/**
 * @brief Vyhodnotí přesnost hráčovy barvy vůči cílové barvě.
 *
 * Spočítá absolutní rozdíl mezi jednotlivými RGB složkami a podle
 * celkového rozdílu a aktuálního streaku určí bodové ohodnocení.
 *
 * @param barvy Pole cílové RGB barvy (R, G, B)
 * @param hracbarvy Pole hráčovy RGB barvy (R, G, B)
 * @return int Počet bodů (0 = špatně, 1 = středně, 2 = přesně)
 */

int vyhodnoceni(int barvy[], int hracbarvy[]){

    int rozdilR = barvy[0] - hracbarvy[0];
    int rozdilG = barvy[1] - hracbarvy[1];
    int rozdilB = barvy[2] - hracbarvy[2];


    rozdilR = abs(rozdilR);
    rozdilG = abs(rozdilG);
    rozdilB = abs(rozdilB);

    int celkovyrozdil = rozdilR + rozdilG + rozdilB;

    if(streak <= 3){
        if(celkovyrozdil > 383){
            return 0;
        } else if (celkovyrozdil < 383 && celkovyrozdil > 192){
            return 1;
        } else {
            return 2;
        }
    } else if(streak <= 5){
        if(celkovyrozdil > 128){
            return 0;
        } else if (celkovyrozdil < 128 && celkovyrozdil > 64){
            return 1;
        } else {
            return 2;
        }
    } else {
        if(celkovyrozdil > 77){
            return 0;
        } else if (celkovyrozdil < 77 && celkovyrozdil > 39){
            return 1;
        } else {
            return 2;
        }        
    }
}