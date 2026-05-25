#include "7_Segment.hpp"

int piny[] = {0,0,0,0,0,0,0};

int nula[] = {0, 0, 0, 0, 0, 0, 1};
int jedna[] = {1, 0, 0, 1, 1, 1, 1};
int dva[] = {0, 0, 1, 0, 0, 1, 0};
int tri[] = {0, 0, 0, 0, 1, 1, 0};
int ctyri[] = {1, 0, 0, 1, 1, 0, 0};
int pet[] = {0, 1, 0, 0, 1, 0, 0};
int sest[] = {0, 1, 0, 0, 0, 0, 0};
int sedm[] = {0, 0, 0, 1, 1, 1, 1};
int osm[] = {0, 0, 0, 0, 0, 0, 0};
int devet[] = {0, 0, 0, 0, 1, 0, 0};
int A[] = {0, 0, 0, 1, 0, 0, 0};
int B[] = {1, 1, 0, 0, 0, 0, 0};
int C[] = {0, 1, 1, 0, 0, 0, 1};
int D[] = {1, 0, 0, 0, 0, 1, 0};
int E[] = {0, 1, 1, 0, 0, 0, 0};
int F[] = {0, 1, 1, 1, 0, 0, 0};

/**
 * @brief Konstruktor třídy Segment.
 *
 * Inicializuje piny pro jednotlivé segmenty 7segmentového displeje
 * a nastaví je jako výstupní. Zároveň si uloží mapování pinů
 * do interního pole.
 *
 * @param segA Pin segmentu A
 * @param segB Pin segmentu B
 * @param segC Pin segmentu C
 * @param segD Pin segmentu D
 * @param segE Pin segmentu E
 * @param segF Pin segmentu F
 * @param segG Pin segmentu G
 */

Segment::Segment(int segA, int segB, int segC, int segD, int segE, int segF, int segG){
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);

    piny[0] = segA;
    piny[1] = segB;
    piny[2] = segC;
    piny[3] = segD;
    piny[4] = segE;
    piny[5] = segF;
    piny[6] = segG;
}

/**
 * @brief Vykreslí číslo nebo znak na 7segmentovém displeji.
 *
 * Funkce vezme hodnotu (0–15) a podle ní zobrazí odpovídající
 * segmentovou kombinaci na displeji.
 *
 * Podporované hodnoty:
 * - 0–9 → číslice
 * - 10–15 → hex znaky A–F
 *
 * @param body Hodnota, která se má zobrazit na displeji (0–15)
 */

void Segment::vykresli(int body){
    celkoveBody = body;
    
    switch(celkoveBody){
        case 0:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], nula[i]);
            }
            break;
        case 1:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], jedna[i]);
            }
            break;
        case 2:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], dva[i]);
            }
            break;
        case 3:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], tri[i]);
            }
            break;
        case 4:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], ctyri[i]);
            }
            break;
        case 5:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], pet[i]);
            }
            break;
        case 6:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], sest[i]);
            }
            break;
        case 7:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], sedm[i]);
            }
            break;
        case 8:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], osm[i]);
            }
            break;
        case 9:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], devet[i]);
            }
            break;
        case 10:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], A[i]);
            }
            break;
        case 11:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], B[i]);
            }
            break;
        case 12:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], C[i]);
            }
            break;
        case 13:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], D[i]);
            }
            break;
        case 14:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], E[i]);
            }
            break;
        case 15:
            for(int i = 0; i < 7; i++){
                digitalWrite(piny[i], F[i]);
            }
            break;
            
    }
}

/**
 * @brief Otestuje všechny segmenty displeje.
 * 
 * Funkce nejprve zhasne všechny segmenty displeje,
 * poté je postupně rožíná s prodlevou 500 ms
 * a nakonec znovu zhasne všechny segmenty.
 * 
 * @note Segmenty jsou aktivní v logické úrovni LOW.
 * @note Pole `piny` obsahuje piny jednotlivých segmentů.
 */

void Segment::test(){
    for(int i = 0; i < 7; i++){
        digitalWrite(piny[i], HIGH);
    }
    delay(500);
    for(int i = 0; i < 7; i++){
        digitalWrite(piny[i], LOW);
        delay(500);
    }
    for(int i = 0; i < 7; i++){
        digitalWrite(piny[i], HIGH);
    }
}