#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include<Wire.h>
#include <FastLED.h>
#define NUM_LEDS 30
#define DATA_PIN 6

//musica
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

  
//-led e botão
CRGB leds[NUM_LEDS];
int numero = 0; 
int cont = 0;
int cont2 = 0;
int cont3 = 0;
int estadoBoton1 = 0;  
//movimentacao
const int MPU = 0x68; 
float AccX, AccY, AccZ;


void setup() { 
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  //inicializa os leds
  LEDS.addLeds<WS2811,DATA_PIN,GRB>(leds,NUM_LEDS); 
  pinMode(A1,INPUT_PULLUP);

/*  // Inicializa o MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  // Configura Acelerometro para fundo de escala desejado
  /*
      Wire.write(0b00000000); // fundo de escala em +/-2g
      Wire.write(0b00001000); // fundo de escala em +/-4g
      Wire.write(0b00010000); // fundo de escala em +/-8g
      Wire.write(0b00011000); // fundo de escala em +/-16g
 
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0b00001000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();
*/
    // Verifica se o módulo de som está conectado e se cartão SD foi inserido
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Inicializando módulo DFPlayer..."));
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Não inicializado:"));
    Serial.println(F("- Verifique se módulo foi corretamente conectado ou"));
    Serial.println(F("- Insira um cartão SD"));
    while (true);
  }
    // Definições iniciais
  myDFPlayer.setTimeOut(500); //  Timeout serial 500ms
  myDFPlayer.volume(26);      //  Volume (de 0 até 30)
  myDFPlayer.EQ(0);           //  Equalização normal
  Serial.println();
  Serial.print("Número de arquivos no cartão: ");
  Serial.println(myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD)); 
  Serial.println();
  Serial.println(F("Módulo DFPlayer Mini inicializado corretamente!"));
}
void loop() { 

  

  estadoBoton1 = digitalRead(A1);
  //opcoes do botão de ligar e desligar
  if (estadoBoton1 == LOW and numero <= 11) { 
    numero = numero + 1;
    delay(20);   
  }

  if(numero>2){
    numero=1
    ;
  }

  switch (numero) { 
    case 1:    
      if(cont==0){
             ligaLed();
      cont=1;
      }
      delay(500);
      if(cont3 == 0){
      cont3=1;
      } 
        
      cont2=0;
      break; 
    case 2:   
      
      if(cont2==0){        
       desligaLed();
          cont2=1;
         
      }      
      cont=0;
      cont3=0;
    break; 
  }
    
}


//liga o sabre
void ligaLed(){
      //ligando o sabre
          myDFPlayer.play(1);
       for(int a=0; a<30; a++){
          leds[a] = CRGB::White;
          delay(30); 
          FastLED.show();
       }
       if(leds[30]=CRGB::White){
              delay(950);
              myDFPlayer.play(2);
            Serial.println("led 30 ligou");
            
        }
         Serial.println("ligado");

  // Comandos para iniciar transmissão de dados
 /* Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

    // Imprime na Serial os valores obtidos
   Alterar divisão conforme fundo de escala escolhido:
      Acelerômetro
      +/-2g = 16384
      +/-4g = 8192
      +/-8g = 4096
      +/-16g = 2048
 
  float alguloX =  AccX / 4096;
  float anguloY = AccY / 4096;
  float anguloZ = AccZ / 4096;
  
  Serial.print(alguloX);
  Serial.print(" ");
  Serial.print(anguloZ);
  Serial.print(" ");
  Serial.println(anguloZ);
    */  
}
 //desliga sabre
void desligaLed(){
       myDFPlayer.play(6);
       for(int b=30; b>0-1; b--){
          leds[b]= CRGB::Black;
          delay(20);
          FastLED.show();
       }
        
       Serial.println("desligado");
}
