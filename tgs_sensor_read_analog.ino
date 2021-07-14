//本範例使用nodeMCU + TGS2601 sensor，抓取TGS2601 sensor類比訊號後由nodeMCU呼叫WS的方式新增DATA至後端DB

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

// wifi
const char* ssid     = "XXXX";
const char* password = "xxxx";
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

//一些全域變數
int iLinkNetWork=0;


void setup()
{
  iLinkNetWork = 0;
  //初始化序列阜，監控視窗用
  Serial.begin(115200);
  //連線wifi
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  WiFiMulti.addAP(ssid, password);
  Serial.println(F("Wait for WiFi... "));
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("");
  
  Serial.println("WiFi connected  IPaddress:");
  Serial.print(WiFi.localIP());
  iLinkNetWork = 1;
  delay(500);
}


void loop()
{ 
  int data = tgs_analog_read();
  Serial.println("data :" + String(data));
  //寫入DB using ws
  if (data > 50) {
    send_data_by_php("TGS-1",String(data));
  }
  delay(60000);
}

//讀取tgs sensor數據
long tgs_analog_read() {
  int sensorValue = 0;
  // read the analog in value
  sensorValue = analogRead(analogInPin);
  return sensorValue;
}

//用WS寫入MySql
void send_data_by_php(String dev_typ,String val){
  int iLnk = 0;
  String s;
 
  if (client.connect("dns", 80)) {
    iLnk = 1;
  }
  while(iLnk ==0){
    delay(500);
    Serial.print(F("\nreconnect php srv"));
    if (client.connect("dns", 80)) {
      iLnk = 1;
    }   
  }
  
  s = "GET /instgsdata.php?devtyp=" + dev_typ + "&val=" + val + 
      " HTTP/1.1\r\n" +
      "Host:inskychen.com \r\n"+
      "Connection: close\r\n\r\n";
  Serial.print(F("\n"));
  Serial.print(s);
  client.println(s);
  String line = client.readStringUntil('\r');                
  Serial.println(line);
  Serial.print(F("\nclosing connection"));
  client.stop();
}
