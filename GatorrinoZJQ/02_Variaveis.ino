byte notasNum[NOTAS_QTD+1] = {NOTAS_MIDI, NOTA_SOLTA};

// === TOCAR ==================================

byte comando[GATILHOS_QTD]; // Variável de controle (liga e desliga a seção que manda noteOn)
byte notasTocar[NOTAS_QTD+1][GATILHOS_QTD]; // Mantenha zero, mas regule o número de entradas. [Se -1, nota recebera NoteOff, se 0, nada, se > 0, tocará a nota correspondente.]
byte ocupado = 0; // Variável de controle (auxilia na ativação da corda solta quando o gatilho já foi ativado.
uint8_t Vel[GATILHOS_QTD];

int gatMins[GATILHOS_QTD] = {ANLG5_MIN, ANLG6_MIN, ANLG7_MIN, ANLG8_MIN, ANLG9_MIN}; //{GAT_MINS};

byte pizStatus[GATILHOS_QTD];
unsigned int pizTempo[GATILHOS_QTD];
unsigned int pizValor[GATILHOS_QTD];
int gatVelMaxs[GATILHOS_QTD] = {ANLG5_VEL_MAX, ANLG6_VEL_MAX, ANLG7_VEL_MAX, ANLG8_VEL_MAX, ANLG9_VEL_MAX}; //{GAT_MAXS}; 
int gatMaxs[GATILHOS_QTD] = {ANLG5_MAX, ANLG6_MAX, ANLG7_MAX, ANLG8_MAX, ANLG9_MAX};

byte gatilhosAtivos = GATILHOS_QTD;
byte modo = 3;

byte gatilho[GATILHOS_QTD];
byte modos[GATILHOS_QTD] = {GATILHOS_MODOS};
int margem[GATILHOS_QTD] = {GATILHOS_MARGEM};
int tempo[GATILHOS_QTD] = {GATILHOS_TEMPO};
bool inverte[] = {GATILHOS_INV};

bool CtrlStatus = 0;

// === CAPACITIVO ============================

#if CAP_VEL_ON
#include <ADCTouchSensor.h>
ADCTouchSensor capVel = ADCTouchSensor(CAP_VEL_PIN, CAP_SACR_PIN);
unsigned int capVelSoma = 0;
unsigned int capVelArray[CAP_SMOOTH];
byte capVelIndice = 0;
#endif
