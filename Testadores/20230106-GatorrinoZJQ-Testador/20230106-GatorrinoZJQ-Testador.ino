#include <Control_Surface.h>

USBMIDI_Interface midi;

// Multiplexadores

CD74HC4051 mux1 {5, {15, 14, 16}};
CD74HC4051 mux2 {A7, {15, 14, 16}};
CD74HC4051 mux3 {7, {15, 14, 16}};
CD74HC4051 mux4 {8, {15, 14, 16}};

Button bMux[] {
    { mux4.pin(0) },
    { mux4.pin(1) },
    { mux4.pin(2) },
    { mux4.pin(3) },
    { mux4.pin(4) },
    { mux4.pin(5) },
    { mux4.pin(6) },
    { mux4.pin(7) }
  };
// Botões de Nota

Button Notas[] {
    { mux1.pin(0) },
    { mux1.pin(1) },
    { mux1.pin(2) },
    { mux1.pin(3) },
    { mux1.pin(4) },
    { mux1.pin(5) },
    { mux1.pin(6) },
    { mux3.pin(0) },
    { mux3.pin(1) },
    { mux3.pin(2) },
    { mux3.pin(3) },
    { mux3.pin(4) },
    { mux3.pin(5) },
    { mux3.pin(6) },
    { mux3.pin(7) },
    {18},
    {19},
    {20},
    {21}
};

// #define NOTAS_QTD     10 // Quantidade de botões usados como seletores de notas
// #define NOTAS_MIDI    43, 47, 48, 50, 52, 55, 59, 60, 62, 64 // Separadas por vírgulas. Use o número MIDI. 
// #define NOTA_SOLTA    40  //     

// // Controles = botões que não mandam CCs, servem pra escolher o modo de funcionamento.
// Button controles[] {
//     { mux1.pin(6)},
//     { mux1.pin(7)},
// };

// Button Gatilhos[] {
//     { mux2.pin(6)},
//     { mux2.pin(7)},
// };

// #define GAT_QTD 2

// // Botões CC

// CCButton CC_Dig {
//     mux2.pin(5), {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}
// };

CCPotentiometer CC_Pot[] {
    // { A6, {MIDI_CC::Sound_Controller_4, CHANNEL_1} },
    // { A9, {MIDI_CC::Sound_Controller_5, CHANNEL_1} },
    { mux2.pin(0), {MIDI_CC::Sound_Controller_6, CHANNEL_1} },
    { mux2.pin(1), {MIDI_CC::Sound_Controller_7, CHANNEL_1} },
    // { mux2.pin(2), {MIDI_CC::Sound_Controller_9, CHANNEL_1} },
    // { mux2.pin(3), {MIDI_CC::Sound_Controller_9, CHANNEL_1} },
    // { mux2.pin(4), {MIDI_CC::Sound_Controller_1, CHANNEL_1} },
    // { mux2.pin(5), {MIDI_CC::Sound_Controller_2, CHANNEL_1} },
    // { mux2.pin(6), {MIDI_CC::Sound_Controller_3, CHANNEL_1} },
    // { mux2.pin(7), {MIDI_CC::Sound_Controller_10, CHANNEL_1} },
};

// // Definições

// // A ordem está invertida em relação à instalação

// #define POT0_MIN 6400
// #define POT0_VEL_MAX 8424
// #define POT0_MAX 11000
// #define POT1_MIN 6000
// #define POT1_VEL_MAX 7000
// #define POT1_MAX 12000
// #define POT2_MIN 5300
// #define POT2_VEL_MAX 6800
// #define POT2_MAX 11000
// #define POT_MINS 6400, 6000, 5300

// PBPotentiometer PB_Pot[] {
//   {A10,CHANNEL_1},
//   {A10,CHANNEL_2},
//   {A10,CHANNEL_3} 
// };

// #define CAP_VEL_ON 1 // Liga (1) / Desliga (0)
// #define CAP_VEL_PIN A7
// #define CAP_SACR_PIN A9
// #define CAP_SMOOTH 10
// #define CAP_MIN_A 119
// #define CAP_MAX_A 285
// #define CAP_MIN_B 25
// #define CAP_MAX_B 118
// #define VEL_MIN 50

// // Mapeamento
// // PB 

// analog_t PB_Map(analog_t raw){
//     // make sure that the analog value is between the minimum and maximum
//     raw = constrain(raw, 1, 14733);
//     // map the value from [minimumValue, maximumValue] to [0, 16383]
//     return map(raw, 1, 14733, 8192, 16383);
// }

// analog_t CC_Map1(analog_t raw){
//     // make sure that the analog value is between the minimum and maximum
//     raw = constrain(raw, POT0_MIN, POT0_MAX);
//     raw = map(raw, POT0_MIN, POT0_MAX, 0, 16383);
//     return constrain(raw, 0, 16383);
// }

// analog_t CC_Map2(analog_t raw){
//     // make sure that the analog value is between the minimum and maximum
//     raw = constrain(raw, POT1_MIN, POT1_MAX);
//     raw = map(raw, POT1_MIN, POT1_MAX, 0, 16383);   
//     return constrain(raw, 0, 16383);
    
// }

// analog_t CC_Map3(analog_t raw){
//     // make sure that the analog value is between the minimum and maximum
//     raw = constrain(raw, POT2_MIN, POT2_MAX);
//     raw = map(raw, POT2_MIN, POT2_MAX, 0, 16383);   
//     return constrain(raw, 0, 16383);
// }
