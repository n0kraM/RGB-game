#ifndef SEGMENT_H
#define SEGMENT_H

#include <Arduino.h>

/**
 * @class Segment
 * @brief Ovládání 7segmentového displeje pomocí Arduino pinů.
 *
 * Třída umožňuje zobrazovat čísla 0–9 a některé hex hodnoty (A–F)
 * na 7segmentovém displeji pomocí digitálních výstupů.
 */

class Segment{
private:
    int celkoveBody;
public:
    Segment(int segA, int segB, int segC, int segD, int segE, int segF, int segG);

    void vykresli(int body);

    void test();
};

#endif