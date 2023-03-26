void loop() {
  // put your main code here, to run repeatedly:

    Control_Surface.loop();

// // // ==== Analogos =========================================
for (byte n = 0; n <2; n++){
  int val;
  val = CC_Pot[n].getRawValue();
  Serial.print(val);
  Serial.print(" - ");
}
Serial.println();
  
// ==== Botões ========================================

// byte Status[19];
// for (byte i = 0; i<19; i++){
//   Status[i] = trad(Notas[i].update());
//   Serial.print(Status[i]);
//   Serial.print(" - ");
// }
// Serial.println();

// byte Status[7];
// for (byte i = 0; i<7; i++){
//   Status[i] = trad(bMux[i].update());
//   Serial.print(Status[i]);
//   Serial.print(" - ");
// }
// Serial.println();

}
