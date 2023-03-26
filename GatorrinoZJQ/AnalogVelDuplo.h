#ifndef AnalogVelDuplo_h
#define AnalogVelDuplo_h

#include "Arduino.h"

class AnalogVelDuplo
{
  public:
    AnalogVelDuplo();
    void atualize(bool sens, int leitura);
    byte execute();
    void imprima();
    byte vel;
    bool sensStatus[2]; // Para os dois sensores, indica se devem ser lidos (0 = Não, 1 = Sim)
    bool sensorAtivo;
    int li[2] = {0, 0};
    int ls[2] = {0, 0};
    unsigned int ti[2];
    unsigned int ts[2];
    unsigned int dormencia = 10000;

  private:
    int val[2] = {0, 0};
    byte status = 0; // 0 (Desligado), 1 (Primeiro limiar), 2 (Segundo Limiar), 3 (Desligando)
    unsigned long tempo = 0;
    byte comando = 3; // 1 = LIGAR, 2 = LIGADO; 3 = DESLIGADO; 4 = DESLIGAR
};  
#endif
