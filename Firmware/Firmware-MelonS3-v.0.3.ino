
// Qwave ESP8266 (LabVIEW) 4M(3M SPIFFS)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <FS.h>

// remove comment when using soft AP mode
#define SOFT_AP
#define DEVICE_NAME "QWAVE"

#define DBG_OUTPUT_PORT   Serial

#ifdef SOFT_AP
// Soft-AP Config
String ssid = "MelonS3";
String password = "88888888";
#else
// Network
String ssid = "";
String password = "";
#endif

#include "QwaveFpga.h"
QwaveFpga Fpga;
String FpgaStart;

extern "C" {
  #include "user_interface.h"
}

const char* bitfileupload = "<h2>FPGA Bit File Upload</h2><form method='POST' action='/' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

ESP8266WebServer server(80);
WiFiUDP udp;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
String ReplyBuffer;

// local port to listen for UDP packets
unsigned int localPort = 4097;

File fsUploadFile;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
  }
  result.toUpperCase();
  return result;
}

String loadConfig(String fname, String field) {
  File configFile = SPIFFS.open("/"+fname, "r");
  if (!configFile) {
    DBG_OUTPUT_PORT.println("Failed to open "+fname+" file!");
    return "";
  }

  size_t size = configFile.size();
  if (size > 1024) {
    DBG_OUTPUT_PORT.println("Config file size is too large");
    return "";
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    DBG_OUTPUT_PORT.println("Failed to parse config file");
    return "";
  }

  const char* _data = json[field];

  DBG_OUTPUT_PORT.print("Loaded "+field+": ");
  DBG_OUTPUT_PORT.println(_data);

  return _data;
}

bool saveConfig(String fname, String field, String value ) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json[field] = value;

  File configFile = SPIFFS.open("/"+fname, "w");
  if (!configFile) {
    DBG_OUTPUT_PORT.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}

//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  else if(filename.endsWith(".svg")) return "image/svg+xml";
  return "text/plain";
}

bool handleFileRead(String path){
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleListFiles()
{
  String FileList = "File List:\n";

  Dir dir = SPIFFS.openDir("/");
  DBG_OUTPUT_PORT.println("File List:");
  while (dir.next())
  {
    String FileName = dir.fileName();
    File f = dir.openFile("r");
    String FileSize = formatBytes(f.size());
    int whsp = 6-FileSize.length();
    while(whsp-->0)
    {
      DBG_OUTPUT_PORT.print(" ");
      FileList += " ";
    }
    DBG_OUTPUT_PORT.println(FileSize+" "+FileName);
    FileList += FileSize+" "+FileName+"\n";
  }     
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", FileList);
}

void SerialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
  
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
    //if (inChar == 0x1A) {
      stringComplete = true;
    }
    else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}

void setup(void){

  // Init FPGA Interface
  Fpga.begin();
  
  ESP.wdtEnable(15000); // make the watch dog timeout 15 seconds
  
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(false);
  DBG_OUTPUT_PORT.print("\r\n");
  
  WiFi.disconnect();
  
  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {    
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    DBG_OUTPUT_PORT.printf("\n");
  }

  FpgaStart = loadConfig("config.json","startup");
  if (FpgaStart == "") {
    saveConfig("config.json", "startup", "1" );
  } else if (FpgaStart == "0") {
    DBG_OUTPUT_PORT.println("Skip Fpga Load!");
  } else if (FpgaStart == "1") {
    DBG_OUTPUT_PORT.println("Loading Fpga...");
    Fpga.FpgaLoad("/Fpga.bit");
  }

  uint8_t mac[6];
  wifi_get_macaddr(STATION_IF, mac);
  ReplyBuffer = String(DEVICE_NAME) + "::" + macToStr(mac);

#ifdef SOFT_AP  
  //WIFI INIT
  WiFi.mode(WIFI_AP);
  ssid += String("-") + String(ESP.getChipId(), HEX);
  WiFi.softAP(ssid.c_str(), password.c_str());
  
  IPAddress myIP = WiFi.softAPIP();
  DBG_OUTPUT_PORT.println("*** Soft AP Started ***");
  DBG_OUTPUT_PORT.print("WiFi SSID: ");
  DBG_OUTPUT_PORT.println(ssid);
  DBG_OUTPUT_PORT.print("IP Address: ");
  DBG_OUTPUT_PORT.println(myIP);
  ReplyBuffer += " - "+String(myIP[0])+"."+String(myIP[1])+"."+String(myIP[2])+"."+String(myIP[3]);
#else
  DBG_OUTPUT_PORT.print("Connecting to ");
  DBG_OUTPUT_PORT.println(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DBG_OUTPUT_PORT.print(".");
  }
  IPAddress myIP = WiFi.localIP();
  DBG_OUTPUT_PORT.println("\nWiFi connected");  
  DBG_OUTPUT_PORT.print("IP Address: ");
  DBG_OUTPUT_PORT.println(myIP);
  ReplyBuffer += " - "+String(myIP[0])+"."+String(myIP[1])+"."+String(myIP[2])+"."+String(myIP[3]);
#endif

  udp.begin(localPort);
  DBG_OUTPUT_PORT.print("Starting UDP ");
  DBG_OUTPUT_PORT.print("on port: ");
  DBG_OUTPUT_PORT.println(udp.localPort());
  
  server.onNotFound([](){
    if(!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //list files
  server.on("/files", HTTP_GET, handleListFiles);

  server.on("/reboot", HTTP_GET, [](){
    server.send(200, "text/html", "rebooting in 3 seconds...");
    delay(3000);
    ESP.restart();
  });

  server.on("/startup", HTTP_GET, [](){
    saveConfig("config.json", "startup", "1" );
    server.send(200, "text/html", "done.");
  });

  server.on("/unstartup", HTTP_GET, [](){
    saveConfig("config.json", "startup", "0" );
    server.send(200, "text/html", "done.");
  });
  
  server.on("/delete", HTTP_GET, [](){
      if (server.hasArg("file")) {
        String path = "/" + server.arg("file");
        SPIFFS.remove(path);
        server.send(200, "text/html", "deleted " + path);
      }
      else {
        server.send(404, "text/plain", "Please following format: /delete?file=FileName");
      }
  });
  
  server.on("/", HTTP_GET, [](){
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", bitfileupload);
  });
    
  server.on("/", HTTP_POST, [](){
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/plain", (Update.hasError())?"Update Failed!":"Update Success!");
  },[]() {
      HTTPUpload& upload = server.upload();
      if(upload.status == UPLOAD_FILE_START){
        DBG_OUTPUT_PORT.printf("Update: %s\n", upload.filename.c_str());
        String path = "/" + upload.filename;
        SPIFFS.remove(path);
        fsUploadFile = SPIFFS.open(path, "w");
        Fpga.SaveFile_Init();
      } else if(upload.status == UPLOAD_FILE_WRITE){
        if(fsUploadFile) {
          Fpga.SaveFile_Encypt(upload.buf, upload.currentSize);
          fsUploadFile.write(upload.buf, upload.currentSize);
        }
      } else if(upload.status == UPLOAD_FILE_END){
        if(fsUploadFile) {
          DBG_OUTPUT_PORT.printf("Upload Success: %u\n", upload.totalSize);
          fsUploadFile.close();
          Fpga.FpgaLoad("/" + upload.filename);
        }
      }
      yield();
  });

  server.on("/fpga-run", HTTP_POST, [](){
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/plain", (Update.hasError())?"Run Failed!":"Run Success!");

  },[]() {
      HTTPUpload& upload = server.upload();
      if(upload.status == UPLOAD_FILE_START){
        DBG_OUTPUT_PORT.printf("Download: %s\n", upload.filename.c_str());

        // Init FPGA
        Fpga.Transfer_Init();
        
      } else if(upload.status == UPLOAD_FILE_WRITE){
        
        int count = upload.currentSize;
        Fpga.Transfer(count, upload.buf);
        
      } else if(upload.status == UPLOAD_FILE_END){
        Fpga.Transfer_End();
        DBG_OUTPUT_PORT.println("done.");
        DBG_OUTPUT_PORT.println();
      }
      yield();
  });
    
  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");
  
}

void loop(void){
  ESP.wdtFeed();
  server.handleClient();

  // UDP Communication
  int packetSize = udp.parsePacket();
  if (packetSize)
  {
    /*Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = udp.remoteIP();
    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(udp.remotePort());*/

    // read the packet into packetBufffer
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[packetSize] = '\0';
    
    //Serial.println("Contents:");
    //Serial.println(packetBuffer);

    String inputString = String(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    
    if(inputString.startsWith("#Melon-S3")) {
      udp.write(ReplyBuffer.c_str());
    }
    else if(inputString.startsWith("/fpga-info")) {
      udp.write("Dev1,MelonS3Fpga,Melon-S3");
    }
    else if(inputString.startsWith("/fpga-setasstartup")) {
      saveConfig("config.json", "startup", "1" );
      udp.write("set fpga run as startup.");
    }
    else if(inputString.startsWith("/fpga-unsetasstartup")) {
      saveConfig("config.json", "startup", "0" );
      udp.write("unset fpga run as startup.");
    }
    else if(inputString.startsWith("/fpga-reboot")) {
      udp.write("Rebooting...");
      udp.endPacket();
      delay(3000);
      ESP.restart();
    }
    else if(inputString.startsWith("/fpga-busreset")) {
      Fpga.BusReset();;
      udp.write("done.");
    }
    else if(inputString.startsWith("/fpga-write?addr=")) {
      char addrReg[5], Data[11];
      int dd = inputString.indexOf('&')+1;
      inputString.substring(17).toCharArray(addrReg, (dd-17));
      inputString.substring(dd+5).toCharArray(Data, 11);
      Fpga.writeRegister(atoi(addrReg), strtoul(Data, '\0', 10));
      udp.write(Data);
    }
    else if(inputString.startsWith("/fpga-read?addr=")) {
      char addrReg[5];
      inputString.substring(16).toCharArray(addrReg, 5);
      if( Fpga.getRegister(atoi(addrReg)) ) {
        uint32_t oData = (uint32_t)Fpga.data.bit32[0];
        udp.write(String(oData).c_str());
      }
      else {
        udp.write("error!");
      }
    }
    else if(inputString.startsWith("/fpga-load")) {
      Fpga.FpgaLoad("/Fpga.bit");
      udp.write("done.");
    }
    else {
      udp.write("error!");
    }
    udp.endPacket();
  }

  // UART Communication
  SerialEvent();
  if (stringComplete) {
    int numCommand = inputString.indexOf(' ') + 1;
    
    if (inputString.startsWith("Reg?")) {
      if(numCommand == 5) {
        char addrReg[5];
        inputString.substring(numCommand).toCharArray(addrReg, 5);
        if( Fpga.getRegister(atoi(addrReg)) ) {
          Serial.println((uint32_t)Fpga.data.bit32[0]);
        }
        else {
          Serial.println("error!");
        }
      }
      else {
        Serial.println("Reg? [Register Address]");
      }
    }
    else if (inputString.startsWith("Reg")) {
      int cm = inputString.indexOf(',', numCommand)+1;
      if(numCommand == 4 && cm > 5) {
        char addrReg[5], Data[11];
        inputString.substring(numCommand).toCharArray(addrReg, (cm-numCommand));
        inputString.substring(cm).toCharArray(Data, 11);
        Fpga.writeRegister(atoi(addrReg), strtoul(Data, '\0', 10));
      }
      else {
        Serial.println("Reg [Register Address],[Data]");
      }
    }
    else if (inputString.startsWith("FpgaLoad")) {
      Fpga.FpgaLoad("/Fpga.bit");
    }
    else if (inputString.startsWith("bReset")) {
      Fpga.BusReset();
    }
    else if (inputString.startsWith("viRun")) {
      if( !Fpga.viExecution() ) {
        Serial.println("error!");
      }
    }
    else if (inputString.startsWith("viStop")) {
      if( !Fpga.viStop() ) {
        Serial.println("error!");
      }
    }
        
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  yield();
}
          

