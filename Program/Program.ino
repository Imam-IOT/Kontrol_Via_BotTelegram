#include "CTBot.h"
#include <ESP8266WiFi.h> 

CTBot imamaris;
int relay = 13;

const char* ssid     = "SiGro_2022";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "SiGro_TJKT_2022";     // The password of the Wi-Fi network


void setup() {
 Serial.begin(115200);
 pinMode(relay,OUTPUT);
 digitalWrite(relay,HIGH);

 imamaris.setTelegramToken("5902309509:AAGc1g12L_GH_q_hdmMpmz17mTfgfplhYwY");


  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Menghubungkan Ke Internet");
 if(imamaris.testConnection())
 Serial.println("Berhasil Terhubung");
 else
 Serial.println("Errorr !!!");
 
}
}

void loop() {
 TBMessage pesan;

//Perintah Menyalahkan Lampu
 if(imamaris.getNewMessage(pesan)){
  Serial.print("Ada Pesan Masuk : ");
  Serial.println(pesan.text);
  if(pesan.text.equalsIgnoreCase("LAMPU_HIDUP")) {
    digitalWrite(relay,LOW);
    imamaris.sendMessage(pesan.sender.id,"Menghidupkan Lampu");
  }

//Perintah Mematikan Lampu
  else if(pesan.text.equalsIgnoreCase("LAMPU_MATI")){
    digitalWrite(relay,HIGH);
    imamaris.sendMessage(pesan.sender.id,"Mematikan Lampu");
  }
  else{
    String balas;
    balas="Maaf Perintah Yang Anda Masukan Salah !!!";
    imamaris.sendMessage(pesan.sender.id,balas);
  }
}
}
