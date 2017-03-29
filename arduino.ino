#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = {93, 188, 160, 98};
byte ip[] = {192, 168, 0, 23};

EthernetClient client;
int sensor1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  Serial.println("connecting...");
  pinMode(13, OUTPUT);
}

void loop() {

  if (client.connect(server, 80)) {
    Serial.println("conectado 1° vez");
    client.println("GET http://msguanaz.esy.es/comando.txt");
    //client.println("Host:www.msguanaz.esy.es");
    // client.println("Connection: close");
    client.println();
  } 
  
  if (client.available()) {
    char c = client.read();
   // Serial.print(c);
    if(c=='1'){
      Serial.println("Ligado");
        digitalWrite(13, LOW);
      }
    if(c=='0'){
      Serial.print("Desligado");
        digitalWrite(13, HIGH);
      }  
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  delay(500);
  if (client.connect(server, 80)) {
    sensor1 += 5;

    // cliente.print("GET http://msguanaz.esy.es//salvadados.php?sensor1=");
    // cliente.println(sensor1);
    // cliente.print(" HTTP/1.1");
    Serial.print("sensor1=");
    Serial.println(sensor1);
    client.stop();
  }
}


