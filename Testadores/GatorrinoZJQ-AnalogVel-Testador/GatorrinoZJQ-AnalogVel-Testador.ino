// Sketch criada com a finalidade de testar a classe tcrtVelocityDuplo, atualmente usado para auxiliar na sua configuração

// USO:
// Escolha abaixo o MODO e, se necessário, o PINO.
// Na guia "Setup.ino", as variaveis trigger.li, trigger.ls,trigger.ti e trigger.ts configuram a sensibilidade dos sensores. 
// [0] e [1] indicam a qual dos sensores corresponde à configuração.
// trigger.li indica o primeiro limiar do sensor (usado para começar o disparo e cálculo do velocity)
// trigger.ls indica o segundo limiar do senor (a partir dele o gatilho é efetivamente disparado)
// trigger.ti indica quantos millisegundos devem se passar entre o primeiro e o segundo limiar para que a velocity seja 0 (maior tempo = menor velocity)
// trigger.ts indica quantos millisegundos devem se passar entre o primeiro e o segundo limiar para que a velocity seja 127 (em geral, o menor tempo facilmente obtido tocando)

// MODOS
// MODO 0 >>> Lê apenas um dos sensores, definido pela macro PINO
// - Prefira usar o MODO 1, se o 0 não for necessário.
// MODO 1 >>> Lê e imprime os valores dos sensores lado a lado, constantemente. O valor da esquerda corresponde ao sensor [0]. 
// Em lugar de leituras entre 0 e 1023 (10 bits), os sensores retornam valores entre 0 e 16383 (14 bits).
// - Esse modo pode ser usado para escolher os valores de li e ls. 
// - li deve ser um pouco menor do que o valor que o sensor lê quando parado. Observe se o acionamento de um dos sensores reduz o valor do outro (isso pode afetar a escolha de li).
// - ls deve ser um pouco maior que li.
// MODO 2 >>> Testa ambos os sensores utilizando já o cálculo de disparo. Retorno, junto com NoteOn, o tempo (em millis) entre os dois limiares.
// - Pode ser usado para definir ti e ts experimentalmente.
// MODO 3 >>> Testa ambos os sensores utilizando já o cálculo de disparo e de velocity
// - Simula o funcionamento regular do sensor, imprimindo NoteOn e NoteOff no monitor, junto com o velocity.
// - Pode ser usado para verificar se os valores de li, ls, ti e ts estão adequados.

#define MODO 0
#define PINO 0


#include <Control_Surface.h>
#include "AnalogVelDuplo.h"

USBMIDI_Interface midi;

// Multiplexadores

CD74HC4051 mux3 {5, {15, 14, 16}};
CD74HC4051 mux2 {A7, {15, 14, 16}};
CD74HC4051 mux4 {A8, {15, 14, 16}}; // Analogs (multiplexador adicional). Nele estão ligados os sensores do saco-de-cachorro

// Botões de Nota

Button botoes[] {
    { mux3.pin(3) },
    { mux3.pin(4) },
    { mux3.pin(5) },
    { mux3.pin(6) }
};

CCPotentiometer CC_Pot[] {
    { mux4.pin(0), {MIDI_CC::Sound_Controller_6, CHANNEL_1} }, // Esses são os terminais aos quais estão ligados os sensores do pé-de-bode.
    { mux4.pin(1), {MIDI_CC::Sound_Controller_7, CHANNEL_1} }
};

AnalogVelDuplo trigger;
int counter = 0;




