//On lit la valeur du thermistor sur GPIO9
int ThermistorPin = 9;//GPIO9
//valeur du thermistor
int Vo;
//valeur de la resistance utilise 10K
float R1 = 10000;
//variables utilisées
float logR2, R2, T, Tc;
//Steinhart-hart coefficients
float c1 = 1.1384e-03, c2 = 2.3245e-04, c3 = 9.489e-08;

void setup() {
Serial.begin(115200);
}

void loop() {

  Vo = analogRead(ThermistorPin);
  //Equation pour un diviseur de tension
  R2 = R1 * ((1023.0 / (float)Vo )- 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //température en kelvins
  //température en celcius
  Tc = T - 273.15;
  //On affiche les températures trouvés dans le moniteur série
  Serial.print("Température: "); 
  Serial.print(Tc);
  Serial.println(" °C");   

  delay(500);
}
