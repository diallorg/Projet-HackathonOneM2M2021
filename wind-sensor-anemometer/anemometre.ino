const float pi = 3.14159265;  // Nombre Pi
int period = 1500;           // Période de mesure (miliseconde)
int delaytime = 1500;        // Temps entre les mesures (miliseconde)
int radio = 70 ;             // Distance du centre au capteur (mm)
unsigned int Sample = 0;       // Mesure a 0
unsigned int counter = 0;      // compteur
unsigned int RPM = 0;          // Tours par minute
float speedwind = 0;           // Vitesse du vent (km/h)
int motord = 3;
int motorg = 4;
 
void setup()
{
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
  pinMode(motord, OUTPUT);
  pinMode(motorg, OUTPUT);
  Serial.begin(115200); //Port série a 115200 baud
   
  Serial.println("Anemometre");
  Serial.println("**********");
  Serial.print(" Mesure toutes les secondes : ");
  Serial.println();
}
 
void loop()
{
  Sample++;
  windvelocity();
  RPMcalc();
  WindSpeed();
  //Serial.print(speedwind);
  Serial.print(" VENT FAIBLE");
  delay(500);
  Serial.println();
  Serial.print(" Mesure suivante... ");
  Serial.println();
}
 
// Mesurer la vitesse du vent
void windvelocity(){
  speedwind = 0;
  counter = 0; 
  attachInterrupt(0, addcount, CHANGE);
  unsigned long millis();                    
  long startTime = millis();
  while(millis() < startTime + period) {
  }
  detachInterrupt(1);
}
 
void RPMcalc(){
  RPM=((counter/2)*60)/(period/1000);  // Calculer tours par minute (RPM)
}
 
void WindSpeed(){
  speedwind = ((((2 * pi * radio * RPM)/60) / 1000) / 1000/100) * 3600;  // Calculer la vitesse du vent en km/h
   
  if (speedwind > 0)
  {
    Serial.print(speedwind);
    Serial.print(" [km/h] ");
    digitalWrite(motord, HIGH);
    digitalWrite(motorg, LOW);
    delay(500);
    digitalWrite(motord, LOW);
    digitalWrite(motorg, LOW);
    }
 else{
    digitalWrite(motord, LOW);
    digitalWrite(motorg, LOW);
    }
}
 
void addcount(){
  counter++;
}
