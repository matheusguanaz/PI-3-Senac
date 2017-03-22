#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBD, 0xEF, 0xFA, 0x04};
byte ip[]={192, 168, 0, 23};
byte servidor[]= {93, 188, 160, 98};

EthernetClient cliente;

float sensor1=0;
unsigned long int intervalo = 60000;
unsigned long int tempo_ant= 0;

int x=0;
char temp[2];
void setup() {
    Serial.begin(9600);
    Ethernet.begin(mac, ip);
    pinMode(13, OUTPUT);
    if(cliente.connect(servidor,80)){
      Serial.println("conectado");
    }
}


void loop() {
  recebeDados(); 
enviaDados(sensor1);


delay(3000);

}

void enviaDados(int sensor){
  unsigned long int tempo_atual = millis() - tempo_ant;
  Serial.println(tempo_atual);

   if( tempo_atual > intervalo){
        
         sensor1+=5;

       if(cliente.connect(servidor,80)){
         cliente.print("GET http://msguanaz.esy.es//salvadados.php?sensor1=");
         cliente.println(sensor1);
         cliente.println("Connection: close");
         Serial.print("sensor1=");
         Serial.println(sensor1);
         tempo_ant= tempo_atual;   

          cliente.stop();
      }
   }
      if (!cliente.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    cliente.stop();

    while (true);
  }
      
}
void recebeDados(){
  
   if(cliente.connect(servidor,80)){
    cliente.print("GET http://msguanaz.esy.es//controle.php");
    cliente.println("Connection: close");
      for(x=0; x<2;x++){
      char c = cliente.read();
      temp[x]=c;
      Serial.println(temp[x]); 
     }  
     x=0;

     if(temp[0]==0){
        Serial.println("Rele desligado");
        digitalWrite(13, LOW);
     }
     if(temp[0]==1){
      Serial.println("Rele ligado");
      digitalWrite(13, HIGH);
     }
     cliente.stop();
   }
    if (!cliente.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    cliente.stop();

    while (true);
  }
}
