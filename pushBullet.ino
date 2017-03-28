

// Workshop de Introducao ao NodeMCU - Arduino Day Recife 2017
// Eronides Neto:  eron93@gmail.com 
// Celso Caldeira:  celso_caldeira@yahoo.com.br 

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "CINGUESTS";                   // Digite o nome da Rede Wi-Fi
const char* password = "acessocin";               // Digite o password da rede...

const char* host = "api.pushbullet.com";
const int httpsPort = 443;
const char* PushBulletAPIKEY = "o.5huFq8gC1oVMzPlTTN7cNLEnjfvwRvdy";           // DIGITE SUA CHAVE API, QUE VOCE PEGA NO SITE DO PUSHBULLET

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "2C BC 06 10 0A E0 6E B0 9E 60 E5 96 BA 72 C5 63 93 23 54 B3"; //got it using https://www.grc.com/fingerprints.htm

void msg1()
{
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }
  String url = "/v2/pushes";
  String messagebody = "{\"type\": \"note\", \"title\": \"ESP8266\", \"body\": \"Hello World!\"}\r\n";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + PushBulletAPIKEY + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " +
               String(messagebody.length()) + "\r\n\r\n");
  client.print(messagebody);



  Serial.println("request sent");

  //print the response

  while (client.available() == 0);

  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}

void msg2()
{
  WiFiClientSecure client;
  Serial.print("Se conectando a...");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("falha na conexao!!!");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }
  String url = "/v2/pushes";
  String messagebody = "{\"type\": \"note\", \"title\": \"ESP8266\", \"body\": \"Escreva sua mensagem :)!\"}\r\n";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + PushBulletAPIKEY + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " +
               String(messagebody.length()) + "\r\n\r\n");
  client.print(messagebody);



  Serial.println("request sent");

  //print the response

  while (client.available() == 0);

  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Se conectando a rede.. ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!!");
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());

}

void loop() 
{
  
   msg1();
   delay(15000);
   msg2();
}

