
float val, voltage, temp;
String ssid     = "wifiSimulado";
String password = "senhaSimulada";
String host     = "api.thingspeak.com";
const int httpPort   = 80;
String url     = "/update?api_key=96K7XHSV1WW2U7EZ&field1=0";


void setupESP8266(void) {

  Serial.begin(115200);
  Serial.println("AT");
  delay(10);
  if (Serial.find("OK"))
    Serial.println("OK");


 /*
 como no tinkercad nao possui modulo wifi pensaremos que aqui estaria
 um codigo para conectar ao wifi
 */
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);
  if (Serial.find("OK")){
   Serial.println("ESP8266 Connectado ao servidor") ;
  }else{
    //devido ao modulo wifi não esar mais funcionando no tinkercad 100% das vezes teremos este erro
   Serial.println("ESP8266 Erro ao se conectar ao servidor") ;
  }
}

void anydata(void) {

  val=analogRead(A0);
  voltage=val*0.0048828125;
  temp = (voltage - 0.5) * 100.0;


  String httpPacket = "GET " + url + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();


  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10);


  Serial.print(httpPacket);
  delay(10);
  if (Serial.find("SEND OK\r\n"))
    Serial.println("ESP8266 enviou dados para o servidor");

}


void setup() {
  pinMode(A0, INPUT);
  setupESP8266();

}

void loop() {

 anydata();

  delay(4000);
}
