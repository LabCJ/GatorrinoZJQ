// byte notasNum[NOTAS_QTD+1] = {NOTAS_MIDI, NOTA_SOLTA};

// // === TOCAR ==================================

// byte comando[3]; // Variável de controle (liga e desliga a seção que manda noteOn)
// byte notasTocar[NOTAS_QTD+1][3]; // Mantenha zero, mas regule o número de entradas. [Se -1, nota recebera NoteOff, se 0, nada, se > 0, tocará a nota correspondente.]
// byte ocupado = 0; // Variável de controle (auxilia na ativação da corda solta quando o gatilho já foi ativado.
// uint8_t Vel[3];

// int potMins[3] = {POT_MINS};

// byte pizStatus[3];
// unsigned int pizTempo[3];
// unsigned int pizValor[3];
// int potMaxs[3] = {POT0_VEL_MAX, POT1_VEL_MAX, POT2_VEL_MAX}; 

// byte gatilhosAtivos = 1;
// byte modo = 3;

// byte gatilho[3];

// bool CtrlStatus = 0;

// // === CAPACITIVO ============================

// #if CAP_VEL_ON
// #include <ADCTouchSensor.h>
// ADCTouchSensor capVel = ADCTouchSensor(CAP_VEL_PIN, CAP_SACR_PIN);
// unsigned int capVelSoma = 0;
// unsigned int capVelArray[CAP_SMOOTH];
// byte capVelIndice = 0;
// #endif
