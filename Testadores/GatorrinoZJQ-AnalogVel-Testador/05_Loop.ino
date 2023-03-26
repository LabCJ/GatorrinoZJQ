void loop() {
//   // put your main code here, to run repeatedly:

    Control_Surface.loop();

#if MODO == 0 //Testa um sensor de cada vez, definido pela macro PINO
  int val;
  val = CC_Pot[PINO].getRawValue();
  Serial.println(val);
#endif

#if MODO == 1 //Testa os dois sensores de uma vez, apenas lendo.
  for (byte n = 0; n <2; n++){
    int val;
    val = CC_Pot[n].getRawValue();
    Serial.print(val);
    if (n == 0){
      Serial.print(" - ");
    }
  }
  Serial.println();
#endif

#if MODO == 3 // Testa ambos os sensores utilizando já o cálculo de Velocity
  for (byte i=0; i<2; i++){
    if(trigger.sensStatus[i] == 1){ // Verifica se o sensor está ativo e le seu valor.
      int val = CC_Pot[i].getRawValue();
      trigger.atualize(i, val);
    }
  }

  byte trigCom = trigger.execute(); //*.execute retorna o "comando" emitido pelo sensor: 0 - Nada, 1 - NoteOn, 2 - NoteOff
  if (trigCom == 1){ // Verifica se um dos sensores foi disparado (valor 1) e imprime NoteOn[(velocity)], aumenta o contador e imprime seu valor atual (número de disparos desde o início do programa)
    Serial.print("NoteOn [");
    Serial.print(trigger.sensorAtivo);
    Serial.print("(");
    Serial.print(trigger.vel);
    Serial.print(")]");
    counter += 1;
    Serial.print(" - ");
    Serial.println(counter);
  }
  if (trigCom == 2){ // Verifica se o sensor foi desligado (valor 2) e imprime NoteOff[(velocity)].
    Serial.print("NoteOff [");
    Serial.print(trigger.sensorAtivo);
    Serial.print("(");
    Serial.print(trigger.vel);
    Serial.println(")]");
}

#endif

#if MODO == 2 // Testa ambos os sensores usando a biblioteca, mas mensura os tempos iniciais e finais.
  for (byte i=0; i<2; i++){
    if(trigger.sensStatus[i] == 1){ // Verifica se o sensor está ativo e le seu valor.
      int val = CC_Pot[i].getRawValue();
      trigger.atualize(i, val);
    }
  }

  byte trigCom = trigger.execute(); //*.execute retorna o "comando" emitido pelo sensor: 0 - Nada, 1 - NoteOn, 2 - NoteOff

  if (trigCom == 1){ // Verifica se um dos sensores foi disparado (valor 1) e imprime NoteOn[(velocity)], aumenta o contador e imprime seu valor atual (número de disparos desde o início do programa)
    Serial.print("NoteOn [");
    Serial.print(trigger.sensorAtivo);
    Serial.print("(");
    Serial.print(trigger.tempoE);
    Serial.print(")]");
    counter += 1;
    Serial.print(" - ");
    Serial.println(counter);
  }
  if (trigCom == 2){ // Verifica se o sensor foi desligado (valor 2) e imprime NoteOff[(velocity)].
    Serial.print("NoteOff");
}

#endif

}

