byte presetChange = 0xC0; // MIDI poruka za promjenu preseta

int presets[] {0x0, 0x1, 0x2, 0x3, 0x4, 0x5,
               0x6, 0x7, 0x8, 0x9, 0xA, 0xB,
               0xC, 0xD, 0xE, 0xF, 0x10, 0x11,
               0x12, 0x13, 0x14, 0x15, 0x16, 0x17}; // hex vrijednosti za presete od 1-24

int razina = 1;
int pomak = 0;


//vraća pomak ovisno o vrijednosti konstante razina
int vratiPomak(){               
  if(razina == 1) return 0;
  else if(razina == 2) return 4;
  else if(razina == 3) return 8;
  else if(razina == 4) return 12;
  else if(razina == 5) return 16;
  else if(razina == 6) return 20;
}

// ukljućuje ledicu ovisno koji je preset odnosno tipka aktivna
void ledice(int brojTipke){
  if(brojTipke == 0){
    digitalWrite(16, HIGH);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
  }
  if(brojTipke == 1){
    digitalWrite(16, LOW);
    digitalWrite(17, HIGH);
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
  }
  if(brojTipke == 2){
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, HIGH);
    digitalWrite(19, LOW);
  }
  if(brojTipke == 3){
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    digitalWrite(19, HIGH);
  }
}

//poziva se na početku, zbog estetskog dojma
void ukljucivanje(){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      ledice(j);
      delay(60);
    }
    for(int k = 4; k >= 0; k--){
       ledice(k);
      delay(60);
  }
  }
}

//u procesu promjene razine isključuje aktivne ledice 
//jer je aktivan preset na prethodnoj razini a na novoj
//odabranoj ne, iz tog razloga se isključuju sve ledice
void izmjenaRazine(){
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
}

void promjeniPreset(int brojTipke){
  Serial.write(presetChange);
  Serial.write(presets[brojTipke+vratiPomak()]);
  ledice(brojTipke);
}


//funkcija za ispis razine na HEX pokaznik
void ispis(int brojRazine){
    if(brojRazine == 1){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, LOW);
    }
    if(brojRazine == 2){
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);
    }
    if(brojRazine == 3){
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);
    }
    if(brojRazine == 4){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    }
    if(brojRazine == 5){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    }
    if(brojRazine == 6){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    }
}

//koristi se za povećanje i smanjivanje varijable razina 
//u ovisnosti o tipkama za povećanje i smanjivanje razine
void promjeniRazinu(int brojTipke){
  if (brojTipke == 0){
    if(razina == 6){
      razina = 1;
    }
    else{
      razina++;
    }
  }
  else{
    if(razina == 1) {
      razina = 1;
    }
    else{
      razina--;
    }
  }
  ispis(razina);  
  izmjenaRazine();
}




void setup() {
  
  for(int i = 2; i < 8; i++){  //inicijalizacija ulaza, tipke
    pinMode(i, INPUT);
  }

  for(int j = 8; j < 13; j++){ //inicijalizacija izlaza, HEX pokaznik
    pinMode(j, OUTPUT);
  }

  for(int k = 13; k < 20; k++){ //inicijalizacija izlaza, HEX pokaznik i ledice
    pinMode(k, OUTPUT);
  }
  
  Serial.begin(31250); //uspostava serijske komunikacije, 31250 Bauda
  promjeniPreset(0);   //postavljanje defaultnog preseta
  ukljucivanje();      //vizualni efekt
  ispis(1);            //defaultni preset ispis na HEX pokaznik
}


void loop() {     // vršenje stalne provjere koja je tipka pritisnuta

  if(digitalRead(2) == HIGH){
  delay(10);  
   if(digitalRead(2) == HIGH){
     promjeniPreset(0);
     delay(250);
   }
  }

  if(digitalRead(3) == HIGH){
  delay(10);  
   if(digitalRead(3) == HIGH){
     promjeniPreset(1);
     delay(250);
   }
  }

  if(digitalRead(4) == HIGH){
  delay(10);  
   if(digitalRead(4) == HIGH){
     promjeniPreset(2);
     delay(250);
   }
  }

  if(digitalRead(5) == HIGH){
  delay(10);  
   if(digitalRead(5) == HIGH){
     promjeniPreset(3);
     delay(250);
   }
  }
                         
  if(digitalRead(6) == HIGH){ 
  delay(10);  
   if(digitalRead(6) == HIGH){
     promjeniRazinu(0);
     delay(250);
   }
  }

  if(digitalRead(7) == HIGH) {
  delay(10);  
   if(digitalRead(7) == HIGH){
     promjeniRazinu(1);
     delay(250);
   }
  } 
}
