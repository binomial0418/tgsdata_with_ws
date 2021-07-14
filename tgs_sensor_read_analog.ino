//本範例使用nodeMCU + TGS2601 sensor，抓取TGS2601 sensor類比訊號後由nodeMCU呼叫WS的方式新增DATA至後端DB

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

// wifi
const char* ssid     = "ap";
const char* password = "password";
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
//For ThingSpeak
const char* apiKey = "token";
const char* resource = "/update?api_key=";
const char* server = "api.thingspeak.com";

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
  if (data > 50) {
    //寫入Thingspeak
    wrt_to_thingspeak(data);
    //寫入DB using ws
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

//寫資料到Thingspeak
void wrt_to_thingspeak(int data){
  int iLnk = 0;
  String sData;
  // 使用 80 Port 連線
  if (client.connect(server, 80)) {
  //  iLnk = 1;
  } 
  sData   = String(data);
  client.print(String("GET ") + resource + apiKey + "&field1=" + sData +
               " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");
                  
  int timeout = 5 * 10; // 5 seconds             
  while(!client.available() && (timeout-- > 0)){
    delay(1000);
  }
  
  if(!client.available()) {
     Serial.println(F("No response, going back to sleep"));
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println(F("\nclosing connection"));
  client.stop();
}

//用WS寫入MySql
void send_data_by_php(String dev_typ,String val){
  int iLnk = 0;
  String s;
 
  if (client.connect("address", 8088)) {
    iLnk = 1;
  }
  while(iLnk ==0){
    delay(500);
    Serial.print(F("\nreconnect php srv"));
    if (client.connect("address", 8088)) {
      iLnk = 1;
    }   
  }
  
  s = "GET /instgsdata.php?devtyp=" + dev_typ + "&val=" + val + 
      " HTTP/1.1\r\n" +
      "Host:address \r\n"+
      "Connection: close\r\n\r\n";
  Serial.print(F("\n"));
  Serial.print(s);
  client.println(s);
  String line = client.readStringUntil('\r');                
  Serial.println(line);
  Serial.print(F("\nclosing connection"));
  client.stop();
}
