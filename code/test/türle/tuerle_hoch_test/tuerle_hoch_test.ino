

//test sketch für hühner türle hoch fahren mit l293d



int motin1 = 1;                 //l293d pin2
int motin2 = 2;                 //l293d pin7
int endpinoben = 3;             //endstopswitch oben/unten am törle
int endpinunten = 4;
int lichtsens = 5;              //tagelichtsensor

int endoben;
int endunten;
int x = 0;                      //start/stopp bedingung while-schleife


void setup() {
  pinMode(motin1, OUTPUT);
  pinMode(motin2, OUTPUT);
  pinMode(endpinoben,INPUT_PULLUP);
  pinMode(endpinunten, INPUT_PULLUP);
  pinMode(lichtsens, INPUT);
  
}

void loop() {

  hoch();

}



void hoch(){                                        //funktion für türle hoch fahren
   endoben = digitalRead(endpinoben);
   endunten = digitalRead(endpinunten);

   
   if(lichtsens >= 500){                            //!!!sensor wert für hochfahren noch testen !!!!

    while(x == 0){
      digitalWrite(motin2, HIGH);
      digitalWrite(motin1, LOW);
      if(endoben == 1){
        x = 1;
      }
    
    }
  }
}
