/*
8266お作法：
書き込むときは、白(PRG/IO0)を押しながら赤(RST)を押して赤を放して白を放す。
リセットしたくなったら赤。
*/

#define WIFI_SSID "SSID"
#define WIFI_PASS "PASS"


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Multicast
IPAddress ipMulti_(224, 0, 23,0);
byte ipMulti[] = {224,0,23,0};
unsigned int portMulti = 3610;      // local port to listen on

static WiFiUDP udp ;

unsigned char sendData[] = {
  // EHD1, EHD2, TID0, TID1
     0x10, 0x81, 0x00, 0x00,
  //  GRP CLS INST (SEOJ)
     0x01,0x30,0x01,    //  機器オブジェクトから通知を出す (0130 = エアコン)
     //0x0E,0xF0,0x01,  //　自ノードのノードプロファイルオブジェクトから通知を出す
  //  GRP CLS INST (DEOJ)
     0x0E,0xF0,0x01,
  // ESV   OPC  EPC  PDC   EDT
     0x73,0x01,0x80, 0x01, 0x30 // 動作状態（電源）変更通知
     //0x62,0x01,0xD6, 0x00 // インスタンスリスト要求（機器発見）
} ;
int sendDataLen = 15 ;

void setup(){
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Wait for WiFi... ");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi connected: ");
  Serial.println(WiFi.localIP());

  delay(10);
  //udp.begin(portMulti) ;
  udp.beginMulticast(WiFi.localIP(),ipMulti,portMulti) ;
}
void loop(){
  //udp.beginPacket(ipMulti , portMulti );
  udp.beginPacketMulticast(ipMulti,portMulti,WiFi.localIP());
  udp.write(sendData,sendDataLen) ;
  udp.endPacket() ;

  Serial.println("Packet sent.") ;

  delay(5000) ;
}

