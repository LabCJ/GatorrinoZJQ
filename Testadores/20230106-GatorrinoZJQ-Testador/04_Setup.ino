void setup() {
  Serial.begin(9600);


  pinMode(LED_BUILTIN, OUTPUT);

  Control_Surface.begin();

  // controles[0].setDebounceTime(1);
  // for (byte i = 0; i<2; i++){
  //   controles[i].begin();
  // }
  // for (byte i = 0; i<3; i++){
  //   PB_Pot[i].map(PB_Map);
  // }
  // CC_Pot[0].map(CC_Map1);
  // CC_Pot[1].map(CC_Map2);
  // CC_Pot[2].map(CC_Map3);    

  // for (byte j = 0; j < 3; j++){
  //   Vel[j] = 0;
  //   comando[j] = NADA;
  //   gatilho[j] = DESLIGADO;
  //   pizStatus[j] = REPOUSO;
  //   pizTempo[j] = 0;
  //   pizValor[j] = 0;
  //   for (byte i = 0; i < NOTAS_QTD; i++){
  //     notasTocar[i][j] = DESLIGADO;
  //   }
  // }

//   for (byte i = 0; i < 19; i++){
//     Notas[i].begin();
// //    Gatilhos[i].invert();
//   }

//   for (byte i = 0; i < 7; i++){
//     bMux[i].begin();
// //    Gatilhos[i].invert();
//   }


//   for (byte i = 0; i < GAT_QTD; i++){
//     Gatilhos[i].begin();
// //    Gatilhos[i].invert();
    
  // }  
}
