/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Multicast
IPAddress ipMulti_(224, 0, 23,0);
byte ipMulti[] = {224,0,23,0};
unsigned int portMulti = 3610;      // local port to listen on

WiFiUDP wifiudp ;

char sendData[] = {
  // EHD1, EHD2, TID0, TID1
     0x10, 0x81, 0x00, 0x00,
  //  GRP CLS INST (SEOJ)
     0x0E,0xF0,0x01,
  //  GRP CLS INST (DEOJ)
     0x0E,0xF0,0x01,
  // ESV   OPC  EPC  PDC
     0x62,0x01,0xD6, 0x00
} ;

void setup(){
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFi.begin("handazukecafe", "33313F313");

  Serial.print("Wait for WiFi... ");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi connected: ");
  Serial.println(WiFi.localIP());

  delay(10);
  wifiudp.begin(portMulti) ;
}
void loop(){
  wifiudp.beginPacket(ipMulti , portMulti );
  // wifiudp.beginPacketMulticast(ipMulti_,portMulti,WiFi.localIP());
  wifiudp.write(sendData,14) ;
  wifiudp.endPacket() ;

  Serial.println("Packet sent.") ;

  delay(5000) ;
}

/*


void setup() {


    delay(500);
}


void loop() {
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

    
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    // This will send the request to the server
    client.print("Send this data to server");

    //read back one line from server
    String line = client.readStringUntil('\r');
    client.println(line);

    Serial.println("closing connection");
    client.stop();
    
    Serial.println("wait 5 sec...");
    delay(5000);
}
*/
