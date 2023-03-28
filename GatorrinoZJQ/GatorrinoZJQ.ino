#include <Control_Surface.h>
#include "AnalogVelDuplo.h"

USBMIDI_Interface midi;

#define CAB0_MIN 0
#define CAB0_MAX 16383
#define CAB1_MIN 0
#define CAB1_MAX 16383


// Multiplexadores

CD74HC4051 mux3 {5, {15, 14, 16}}; // Digitais (seletores e botões da ponte)
CD74HC4051 mux2 {A7, {15, 14, 16}}; // Analogs 1
CD74HC4051 mux1 {7, {15, 14, 16}}; // Digitais (seletores e botões da ponte)
CD74HC4051 mux4 {A8, {15, 14, 16}}; // Analogs (multiplexador adicional): nele estão os sensores do pé-de-cabrito.

// Botões de Nota

#define NOTAS_QTD     11 // Quantidade de botões usados como seletores de notas
#define NOTAS_MIDI    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 // Separadas por vírgulas. Use o número MIDI. 
#define NOTA_SOLTA    0  // 
// #define NOTAS_MIDI    45, 49, 52, 54, 56, 57, 61, 64, 66, 68, 80 // Separadas por vírgulas. Use o número MIDI. 
// #define NOTA_SOLTA    44  // 

Button Notas[] {
    { mux1.pin(0) },
    { mux1.pin(1) },
    { mux1.pin(2) },
    { mux1.pin(3) },
    { mux1.pin(4) },
    { mux1.pin(5) },
    { mux1.pin(6) },
    { mux1.pin(7) },    
    { mux3.pin(0) },
    { mux3.pin(1) },
    { mux3.pin(2) },
};

#define BOTAO_QTD 8

CCButton botoes[] {
    {18, {0x14, CHANNEL_1}},
    {19, {0x15, CHANNEL_1}},
    {20, {0x16, CHANNEL_1}},
    {21, {0x17, CHANNEL_1}},
    {mux3.pin(3), {0x18, CHANNEL_1}},
    {mux3.pin(4), {0x19, CHANNEL_1}},
    {mux3.pin(5), {0x1A, CHANNEL_1}},
    {mux3.pin(6), {0x1B, CHANNEL_1}}
};

    

// Controles = botões que não mandam CCs, servem pra escolher o modo de funcionamento.
// Button controles[] {
//     { mux1.pin(6)},
//     { mux1.pin(7)},
// };

// Button Gatilhos[] {
//     { mux2.pin(6)},
//     { mux2.pin(7)},
// };

// #define GAT_QTD 2

// Botões CC

// CCButton CC_Dig {
//     mux2.pin(5), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}
// };

#define CC_POT_QTD 5

CCPotentiometer CC_Pot[] {
    { mux2.pin(3), {MIDI_CC::Sound_Controller_1, CHANNEL_1} },
    { mux2.pin(4), {MIDI_CC::Sound_Controller_2, CHANNEL_1} },
    { mux2.pin(5), {MIDI_CC::Sound_Controller_3, CHANNEL_1} },
    { mux2.pin(6), {MIDI_CC::Sound_Controller_4, CHANNEL_1} },
    { mux2.pin(7), {MIDI_CC::Sound_Controller_5, CHANNEL_1} },
};

#define GATILHOS_QTD 7
#define GATILHOS_MODOS 0, 0, 1, 1, 1, 0, 0
#define GATILHOS_INV 1, 1, 0, 0, 1
#define GATILHOS_MARGEM 600, 800, 400, 400, 400
#define GATILHOS_CHN CHANNEL_1, CHANNEL_5, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_6, CHANNEL_7
#define GATILHOS_TEMPO 1000, 1000, 1, 1, 1

CCPotentiometer gatilhos[] {
    { mux2.pin(0), {MIDI_CC::Sound_Controller_6, CHANNEL_1} }, // Gatilhos
    { mux2.pin(1), {MIDI_CC::Sound_Controller_7, CHANNEL_1} },
    { A6, {MIDI_CC::Sound_Controller_8, CHANNEL_1} }, // Pedais
    { A9, {MIDI_CC::Sound_Controller_9, CHANNEL_1} },
    { mux2.pin(2), {MIDI_CC::Sound_Controller_10, CHANNEL_1}}, // Whammy Bar
    { mux4.pin(0), {0x1C, CHANNEL_1} }, // Bola 1 do saco-de-cachorro
    { mux4.pin(1), {0x1D, CHANNEL_1} }, // Bola 2 do saco-de-cachorro
};

AnalogVelDuplo trigger;
AnalogVelDuplo cabrito; //Pé-de-Cabrito!

// Definições

// Pots
#define ANLG0_MIN 0
#define ANLG0_VEL_MAX 8215
#define ANLG0_MAX 16383
#define ANLG1_MIN 0
#define ANLG1_VEL_MAX 8215
#define ANLG1_MAX 16383
#define ANLG2_MIN 0
#define ANLG2_VEL_MAX 8215
#define ANLG2_MAX 16383
#define ANLG3_MIN 0
#define ANLG3_VEL_MAX 8215
#define ANLG3_MAX 16383
#define ANLG4_MIN 0
#define ANLG4_VEL_MAX 8215
#define ANLG4_MAX 16383

// Gatilhos
#define ANLG5_MIN 8600
#define ANLG5_VEL_MAX 12050
#define ANLG5_MAX 15500
#define ANLG6_MIN 11707
#define ANLG6_VEL_MAX 13669
#define ANLG6_MAX 15631
#define ANLG7_MIN 6358
#define ANLG7_VEL_MAX 10890
#define ANLG7_MAX 15423
#define ANLG8_MIN 4051
#define ANLG8_VEL_MAX 7703
#define ANLG8_MAX 11355
#define ANLG9_MIN 1700
#define ANLG9_VEL_MAX 4347
#define ANLG9_MAX 6900

// #define GAT_MINS ANLG5_MIN, ANLG6_MIN, ANLG7_MIN, ANLG8_MIN, ANLG9_MIN
// #define GAT_MAXS ANLG5_VEL_MAX, ANLG6_VEL_MAX, ANLG7_VEL_MAX, ANLG8_VEL_MAX, ANLG9_VEL_MAX

#define POT_PB_MIN 1700
#define POT_PB_MAX 6900

PBPotentiometer PB_Pot[] {
  {mux2.pin(2),CHANNEL_1},
};

// #define CAP_VEL_ON 1 // Liga (1) / Desliga (0)
// #define CAP_VEL_PIN A7
// #define CAP_SACR_PIN A9
// #define CAP_SMOOTH 10
// #define CAP_MIN_A 119
// #define CAP_MAX_A 285
// #define CAP_MIN_B 25
// #define CAP_MAX_B 118
// #define VEL_MIN 50

// Mapeamento
// PB 

analog_t PB_Map(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, POT_PB_MIN, POT_PB_MAX);
    // map the value from [minimumValue, maximumValue] to [0, 16383]
    raw = map(raw, POT_PB_MIN, POT_PB_MAX, 16383, 8192);
    return constrain(raw, 8192, 16383);
}

analog_t Pot_Map(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG0_MIN, ANLG0_MAX);
    raw = map(raw, ANLG0_MIN, ANLG0_MAX, 0, 16383);
    return constrain(raw, 0, 16383);
}

// Gatilho1
analog_t Anlg_Map5(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG5_MIN, ANLG5_MAX);
    raw = map(raw, ANLG5_MIN, ANLG5_MAX, 16383, 0);
    return constrain(raw, 0, 16383);
}

// Gatilho2
analog_t Anlg_Map6(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG6_MIN, ANLG6_MAX);
    raw = map(raw, ANLG6_MIN, ANLG6_MAX, 16383, 0);
    return constrain(raw, 0, 16383);
}

analog_t Anlg_Map7(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG7_MIN, ANLG7_MAX);
    raw = map(raw, ANLG7_MIN, ANLG7_MAX, 0, 16383);
    return constrain(raw, 0, 16383);
}

analog_t Anlg_Map8(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG8_MIN, ANLG8_MAX);
    raw = map(raw, ANLG8_MIN, ANLG8_MAX, 0, 16383);
    return constrain(raw, 0, 16383);
}

analog_t Anlg_Map9(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, ANLG9_MIN, ANLG9_MAX);
    raw = map(raw, ANLG9_MIN, ANLG9_MAX, 16383, 0);
    return constrain(raw, 0, 16383);
}

analog_t Anlg_Map10(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, CAB0_MIN, CAB0_MAX);
    raw = map(raw, CAB0_MIN, CAB0_MAX, 16383, 0);
    return constrain(raw, 0, 16383);
}

analog_t Anlg_Map11(analog_t raw){
    // make sure that the analog value is between the minimum and maximum
    raw = constrain(raw, CAB1_MIN, CAB1_MAX);
    raw = map(raw, CAB1_MIN, CAB1_MAX, 16383, 0);
    return constrain(raw, 0, 16383);
}