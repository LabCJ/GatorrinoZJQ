void loop() {
  // put your main code here, to run repeatedly:

    Control_Surface.loop();

// === GATILHO ====================================================
  // byte gat[2];
  // for (byte i=0; i < GAT_QTD; i++){
  //   gat[i] = trad(Gatilhos[i].update());
  //   }    
  // if (gat[0] == TOCAR || gat[1] == TOCAR){
  //   gatilho[0] = TOCAR;
  // }
  // else if (gat[0] == DESLIGAR || gat[1] == DESLIGAR){
  //   gatilho[0] = DESLIGAR;
  // }
  // else if (gat[0] == TOCANDO || gat[1] == TOCANDO){
  //   gatilho[0] = TOCANDO;
  // }
  // else {
  //   gatilho[0] = DESLIGADO;
  // }

// ==== CAPACITIVO ================================================

#if CAP_VEL_ON  

    int capVal = capVel.read();   
    capVelSoma -= capVelArray[capVelIndice];
    capVelArray[capVelIndice] = capVal;
    capVelSoma += capVelArray[capVelIndice];
    capVelIndice += 1;
    if (capVelIndice >= CAP_SMOOTH) {
      capVelIndice = 0;
    }
    int capValMedia = capVelSoma / CAP_SMOOTH;


  // Eventos desencadeados
  if (gatilho[0] == TOCAR){
    Vel[0] = capValMedia;
    if (Vel[0] <= CAP_MAX_B){
      Vel[0] = max(CAP_MIN_B, Vel[0]);
      Vel[0] = round(map(Vel[0], CAP_MIN_B, CAP_MAX_B, VEL_MIN, 127));
      Vel[0] = constrain(Vel[0], VEL_MIN, 127);
    }
    else {
      Vel[0] = min(CAP_MAX_A, Vel[0]);
      Vel[0] = round(map(Vel[0], CAP_MIN_A, CAP_MAX_A, VEL_MIN, 127));
      Vel[0] = constrain(Vel[0], VEL_MIN, 127);          
    }
    comando[0] = NOTEON;  
  }
#endif

// ==== OUTROS GATILHOS ===========================================
/* Esse trecho diz respeitto aos controles que alternam os modos de
funcionamento dos gatilhos "auxiliares" (os digitais). */

  
  // int Ctrl;
  // Ctrl = CC_Pot[3].getRawValue();
  // if (Ctrl >= 4500 && CtrlStatus == 0){
  //   modo += 1;
  //   if (modo > 3){
  //     modo = 0;
  //   }
  //   CtrlStatus = 1;
  // }     
  
  // if (Ctrl <= 3500 && CtrlStatus == 1){
  //   CtrlStatus = 0;
  // }

  // switch (modo){
  //   case 0:
  //     gatilhosAtivos = 1;
  //     break;
  //   case 1:
  //     gatilhosAtivos = 2;
  //     break;
  //   case 2:
  //     gatilhosAtivos = 3;
  //     break;
  //   case 3:
  //     gatilhosAtivos = 3;
  //     break;
  // }
  // // Serial.print(gatMaxs[0]-gatilhos[0].getRawValue());
  // Serial.print(gatMaxs[0]);
  // Serial.print(" - ");
  // // Serial.print(gatMaxs[1]-gatilhos[1].getRawValue());
  // Serial.print(gatMaxs[1]);
  // Serial.print(" - ");
  // // Serial.print(gatMaxs[4]-gatilhos[4].getRawValue());
  // Serial.print(gatMaxs[4]);
  // Serial.println();

// Gatilho Principal (Pizzicato)

for (byte i=0; i<2; i++){
  if(trigger.sensStatus[i] == 1){
    int val = gatilhos[i].getRawValue();
    trigger.atualize(i, val);
  }
}

byte trigCom = trigger.execute();
bool sensor = trigger.sensorAtivo;
gatilho[sensor] = trigCom;

if (trigCom == 1){
  Vel[sensor] = trigger.vel;
  comando[sensor] = NOTEON;
}

if (trigCom == 4){
  comando[sensor] = NOTEOFF;
}




// ==== GATILHO CELLO =============================================
  for (byte m = 0; m<(gatilhosAtivos); m++){
    int PGat = gatilhos[m].getRawValue();
    int li;
    int ls;
    if (inverte[m] == 1){
      PGat = gatMaxs[m]-PGat;
      if (PGat < 0){
        PGat = 0;
      }
      li = margem[m];
      ls = gatMaxs[m]-gatVelMaxs[m];
    }
    else {
      li = gatMins[m]+margem[m];
      ls = gatVelMaxs[m];
    }
    switch (modos[m]){
      case 0:
        break;
      case 1:
        switch (gatilho[m]) {
          case DESLIGADO:   
              if (PGat > li){
                gatilho[m] = TOCAR;
                comando[m] = NOTEON;
                Vel[m] = 127;
              }
            break;
          case TOCAR:
            gatilho[m] = TOCANDO;
            break;
          case TOCANDO:
            if (PGat <= li-(margem[m]/2)){
              gatilho[m] = DESLIGAR;
              Vel[m] = 0;
            }
            break;
          case DESLIGAR:
            gatilho[m] = DESLIGADO;
            break;
        }
        break;
      case 2:
        switch (pizStatus[m]) {
          case REPOUSO:
            gatilho[m] = DESLIGADO;
            if (PGat > li){
              pizStatus[m] = LENDO;
              pizTempo[m] = micros();       
            }
            break;
          case LENDO:
              pizValor[m] = max(pizValor[m], PGat);
              if (micros() - pizTempo[m] >= tempo[m]){
                Vel[m] = map(pizValor[m], li, ls, 35, 127);
                Vel[m] = constrain(Vel[m], 35, 127);
                pizStatus[m] = ATIVO;
                gatilho[m] = TOCAR;
                comando[m] = NOTEON;
                pizValor[m] = 0;
              }
            break;
          case ATIVO:
            gatilho[m] = TOCANDO;
            if (PGat <= li-(margem[m]/2)){
              gatilho[m] = DESLIGAR;
              pizStatus[m] = REPOUSO;
            }
            break;
        }
        break;
    }
  }
  
// ==== SELETORES DE NOTAS ========================================

   bool notaSolta = true;
   bool soltar = false;
   bool apertar = false;
  
  for (byte i = 0; i < NOTAS_QTD; i++) {
      byte Status[NOTAS_QTD];
      Status[i] = trad(Notas[i].update());

      
      // Verifica se as notas estão todas soltas
      notaSolta = notaSolta && (Status[i] == DESLIGADO);
      soltar = soltar || (Status[i] == DESLIGAR);
      apertar = apertar || Status[i] == TOCAR || Status[i] == TOCANDO;

      for (byte j = 0; j < gatilhosAtivos; j++){
      // Liga e desliga as notas
      // Liga as notas quando: seletor está apertado e um dos gatilhos também.  
      
        if ((Status[i] == TOCANDO) && (gatilho[j] == TOCAR)) {
          notasTocar[i][j] = TOCAR;
        }    
    
        // [!!!] Liga a nota se o seletor foi apetado após o gatilho e esse ainda está apertado.
        if ((Status[i] == TOCAR) && (gatilho[j] == TOCANDO)) {
          notasTocar[NOTAS_QTD][j] = DESLIGAR;
          notasTocar[i][j] = TOCAR;
          comando[j] = NOTEON;
          }
        
       // Desliga a nota quando o seletor correspondente é solto.    
        if (Status[i] == DESLIGAR){
          notasTocar[i][j] = DESLIGAR;
          comando[j] = NOTEOFF;
        }
      }
  } // Fim do FOR
  
   for (byte j = 0; j < gatilhosAtivos; j++){
     // Liga "corda solta"  
     if ((notaSolta == true) && (gatilho[j] == TOCAR)) {
       notasTocar[NOTAS_QTD][j] = TOCAR;
     }
    
     // Toca corda solta quando todos os seletores forem soltos enquanto um gatilho ainda estiver selecionado.        
     if (((soltar == true) && (apertar != true)) && (gatilho[j] == TOCANDO)){
       notasTocar[NOTAS_QTD][j] = TOCAR;
       comando[j] = NOTEON;
     }
  
    // Desliga todas as notas quando o gatilho é solto.
    if (gatilho[j] == DESLIGAR){
      comando[j] = ALLOFF;
    }
  }

// === TOCAR ======================================================
  for (byte j=0; j<gatilhosAtivos; j++){
    notasOnOff(j);
  }
}
