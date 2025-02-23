/* 
Fil: arduino_project1_myggan_.ino
Författare: William Kowalski Merrick
Datum: 2025-02-04
Beskrivning: Programmet ska ta emot olika datavärden från olika ljussensorer och ser vilken ljussensor som mäter högst värde. 
Programmet får hjulen att svänga åt det håll som störst ljus läses av. 
*/


const int LDR1_PIN = A0;  // Pin för LDR1
const int LDR2_PIN = A1;  // Pin för LDR2
const int LDR3_PIN = A2;  // Pin för LDR3


const int hjul1 = 2;  //Pin för hjul nr 1
const int hjul2 = 8;  //Pin för hjul nr 2

const int arrLängd = 10;  // Mängden värden som arrayen kan ha

int arr1[arrLängd];  // Array för att lagra de senaste mätvärdena
int arr2[arrLängd];
int arr3[arrLängd];
int index = 0;

int med1 = 0;  // Tar in alla värden i arrayerna från "sum" och delar på "arrLängd" (10). Dessa ska sedan jämföras med alla andra "med" för det största värdet
int med2 = 0;
int med3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(hjul1, OUTPUT);  //Startar igång hjulen
  pinMode(hjul2, OUTPUT);

  pinMode(LDR1_PIN, INPUT);  //Startar igång mina tre LDR
  pinMode(LDR2_PIN, INPUT);
  pinMode(LDR3_PIN, INPUT);
}

void loop() {
  starkaste_ljus();

  Serial.print(med1);
  Serial.print("   ");
  Serial.print(med2);
  Serial.print("   ");
  Serial.println(med3);

  if (med1 < med2 && med1 < med3) { // Tittar vilket värde som är högst, beroende på vilket värde som är högst startar den en viss funktion
    vanster();
  } else if (med2 < med1 && med2 < med3) {
    fram();
  } else if (med3 < med1 && med3 < med2) {
    hoger();
  }
}

// Denna funktion ska se vilken ljussensor som känner starkast ljus. 
void starkaste_ljus() {
  // Beräkna medelvärdet

  int sum1 = 0;  // Summan av alla värdena av array 1 från LDR1
  int sum2 = 0;  // Summan av alla värdena av array 2 från LDR2
  int sum3 = 0;  // Summan av alla värdena av array 3 från LDR3

  arr1[index] = analogRead(LDR1_PIN); // Lägger in värden som mäts 
  arr2[index] = analogRead(LDR2_PIN);
  arr3[index] = analogRead(LDR3_PIN);

  index = (index + 1)%10;

  for (int i = 0; i < arrLängd; i++) { // En for loop 
    sum1 += arr1[i];
    sum2 += arr2[i];
    sum3 += arr3[i];
  }

  med1 = sum1/arrLängd;
  med2 = sum2/arrLängd;
  med3 = sum3/arrLängd;

}

//Mina funktioner som ska bestämma rikting för bilen, jag har fyra olika, en som går fram,
//En annan går till höger och den tredje går till vänster.


//.Denna funktionen gör att bilen åker rakt fram. Det gör vi genom att inom funktionen sätta igång både hjulen (motorerna samtidigt)
void fram() {
  digitalWrite(hjul1, HIGH);
  digitalWrite(hjul2, HIGH);
}

//Denna funktionen gör att bilen kommer att svänga åt höger, genom att sätta igång endast en motor kommer detta att gå, genom att sätta igång den motsatta motorn åt det håll vi vill
void hoger() {
  digitalWrite(hjul1, LOW);
  digitalWrite(hjul2, HIGH);
}

//Denna funktionen gör att bilen kommer att svänga åt vänster, genom att sätta igång endast en motor kommer detta att gå, genom att sätta igång den motsatta motorn åt det håll vi vill
void vanster() {
  digitalWrite(hjul1, HIGH);
  digitalWrite(hjul2, LOW);
}

void stop() {
  digitalWrite(hjul1, LOW);
  digitalWrite(hjul2, LOW);
}