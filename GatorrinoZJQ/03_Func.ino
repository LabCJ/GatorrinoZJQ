int trad(int estado){
        switch (estado){
        case Button::Released:
        return DESLIGADO;
        case Button::Pressed:
        return TOCANDO;       
        case Button::Rising:
        return DESLIGAR;        
        case Button::Falling:
        return TOCAR;
      }
}

//int gatilhoTCRTcello (int valor, int indice){
//  swith (gatilho[indice]) {
//  case DESLIGADO:
//    if (valor > POT_MIN){
//      gatilho[indice] = TOCAR;
//    break;
//  case TOCAR:
//    gatilho[indice] = TOCANDO;
//    comando[indice] = NOTEON;
//    break;
//  case TOCANDO:
//    if (valor <= POT_MIN){
//      gatilho[indice] = DESLIGAR;
//    break;
//  case DESLIGAR:
//    gatilho[indice] = DESLIGADO;
//    break;
//}

void notasOnOff (byte indice){     
  Channel canal[] = {GATILHOS_CHN};

switch (comando[indice]){
  case NOTEON:
    for (int i = 0; i < (NOTAS_QTD + 1); i++){
      MIDIAddress Evento {notasNum[i], canal[indice]};
      if(notasTocar[i][indice] == TOCAR){
          Control_Surface.sendNoteOn(Evento, Vel[indice]);
          notasTocar[i][indice] = TOCANDO;          
      }
      if (notasTocar[i][indice] == DESLIGAR){
          Control_Surface.sendNoteOff(Evento, 0);
          notasTocar[i][indice] = DESLIGADO; 
      }
    }
    comando[indice] = NADA;
    break;
  case NOTEOFF:
// Desliga apenas as notas marcadas para desligar.
    for (int i = 0; i < (NOTAS_QTD + 1); i++){
      MIDIAddress Evento {notasNum[i], canal[indice]};          
      if(notasTocar[i][indice] == DESLIGAR){
          Control_Surface.sendNoteOff(Evento, 0);
          notasTocar[i][indice] = DESLIGADO;            
        }
      }
    comando[indice] = NADA;
    break;        
  case ALLOFF: 
// Desliga todas as notas ligadas.
    for (int i = 0; i < (NOTAS_QTD + 1); i++){
      MIDIAddress Evento {notasNum[i], canal[indice]};          
      if(notasTocar[i][indice] == TOCANDO){
          Control_Surface.sendNoteOff(Evento, 0);
          notasTocar[i][indice] = DESLIGADO;            
        }
      }
    comando[indice] = NADA;
    break;
  default:
    comando[indice] = NADA;
    break;
  }
}
