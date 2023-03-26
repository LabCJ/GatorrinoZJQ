void setup() {
  Serial.begin(9600);

  trigger.li[0] = 15000;
  trigger.li[1] = 15450;
  trigger.ls[0] = 13700;
  trigger.ls[1] = 14000;
  trigger.ti[0] = 50000;
  trigger.ts[0] = 2000;
  trigger.ti[1] = 50000;
  trigger.ts[1] = 2000;

  pinMode(LED_BUILTIN, OUTPUT);

  Control_Surface.begin();

  // controles[0].setDebounceTime(1);
  // for (byte i = 0; i<2; i++){
  //   controles[i].begin();
  // }

  for (byte i = 0; i<1; i++){
    PB_Pot[i].map(PB_Map);
  }

  for (byte i = 0; i<CC_POT_QTD; i++){
    CC_Pot[i].map(Pot_Map);
  }

  gatilhos[0].map(Anlg_Map5);
  gatilhos[1].map(Anlg_Map6);
  gatilhos[2].map(Anlg_Map7);
  gatilhos[3].map(Anlg_Map8);
  gatilhos[4].map(Anlg_Map9);

  for (byte j = 0; j < GATILHOS_QTD; j++){
    Vel[j] = 0;
    comando[j] = NADA;
    gatilho[j] = DESLIGADO;
    pizStatus[j] = REPOUSO;
    pizTempo[j] = 0;
    pizValor[j] = 0;
    for (byte i = 0; i < NOTAS_QTD; i++){
      notasTocar[i][j] = DESLIGADO;
    }
  }

  for (byte i = 0; i < NOTAS_QTD; i++){
    Notas[i].begin();
//    Gatilhos[i].invert();
  }

  for (byte i = 0; i < (BOTAO_QTD); i++){
    botoes[i].begin();
  }  
}
