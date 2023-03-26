#include "AnalogVelDuplo.h"

AnalogVelDuplo::AnalogVelDuplo()
{
  vel = 0;
  sensStatus[0] = 1;
  sensStatus[1] = 1;
  sensorAtivo = 0;
}

void AnalogVelDuplo::atualize(bool sens, int leitura)
{
  val[sens] = leitura;
}

byte AnalogVelDuplo::execute(){
  switch (status){
    case 0: //Não acionado
      for(byte i = 0; i<2; i++){
        if(val[i]<li[i]){
          sensStatus[i] = 1;
          sensStatus[(i+1)%2] = 0;
          tempo = micros();
          status = 1;
          sensorAtivo = i;
          break;
        }
      }
      return comando;
      break;
    case 1: //Acionado o primeiro limite
      if(val[sensorAtivo] < ls[sensorAtivo]){
        tempo = micros() - tempo;
        tempo = constrain(tempo, ts[sensorAtivo], ti[sensorAtivo]);
        vel = map(tempo, ti[sensorAtivo], ts[sensorAtivo], 1, 127);
        status = 2;
        comando = 1;
        return comando;
      }
      if(val[sensorAtivo] > li[sensorAtivo]){
        status = 0;
        sensStatus[0] = 1;
        sensStatus[1] = 1;
        return comando;
      }
      break;
    case 2: //Aguardando segundo limite
      status = 3;
      comando = 2;
      return comando;
      break; 
    case 3: //Acionado o segundo limite
      if(val[sensorAtivo] > li[sensorAtivo]){
        comando = 4;
        status = 4;
        sensStatus[0] = 0;
        sensStatus[1] = 0;
        tempo = micros();
        return comando;
      }
      break;
    case 4:
      comando = 3;
      status = 5;
      return comando;
      break;
    case 5:       
      if(micros() - tempo > dormencia){
        status = 0;
        sensStatus[0] = 1;
        sensStatus[1] = 1;
        return comando;
      }
      break;
  }
}

void AnalogVelDuplo::imprima(){
  Serial.print(val[0]);
  Serial.print(" - ");
  Serial.print(val[1]);
  Serial.println();
  // Serial.println("!!!");
}

