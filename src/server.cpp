#include <Arduino.h>
#include <WiFi.h>
#include "lib/server.h"
#include "lib/config.h"


#include "Server.h"
extern float temp;
extern float humidity;
extern int soil_moi_val;
extern int soil_moisture_sensitivity;
extern int timer_setting;
extern int relay_module_state;
WiFiServer server(80);

void startServer() {
  server.begin();
  Serial.println("Serwer HTTP uruchomiony.");
};

void handleClient() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nowe połączenie!");
    String request = client.readStringUntil('\r');
    Serial.println("Żądanie: " + request);
    client.flush();

    // Prosta odpowiedź HTTP
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println();
client.println("<!DOCTYPE html>");
client.println("<html lang='pl'>");
client.println("<head>");
client.println("<meta charset='UTF-8'>");
client.println("<meta http-equiv=\"refresh\" content=\"5\">");
client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
client.println("<title>SmartGarden Dashboard</title>");
client.println("<style>");
client.println("body { font-family: 'Segoe UI', sans-serif; background: #0f1115; color: #ffffff; margin: 0; padding: 20px; }");
client.println("h1 { color: #00ff99; text-align: center; margin-bottom: 30px; }");
client.println(".grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 20px; }");
client.println(".card { background: #1e1e1e; border-radius: 12px; padding: 20px; box-shadow: 0 4px 12px rgba(0,0,0,0.3); }");
client.println(".label { font-size: 0.9em; color: #aaaaaa; margin-bottom: 5px; display: block; }");
client.println(".value { font-size: 1.5em; font-weight: bold; color: #00ffcc; }");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<h1>🌿 SmartGarden – Panel Domowy</h1>");
client.println("<div class='grid'>");

client.println("<div class='card'><span class='label'>🌡️ Temperatura</span><span class='value'>" + String(temp) + " °C</span></div>");
client.println("<div class='card'><span class='label'>💧 Wilgotność powietrza</span><span class='value'>" + String(humidity) + " %</span></div>");
client.println("<div class='card'><span class='label'>🌱 Wilgotność gleby</span><span class='value'>" + String(soil_moi_val) + " %</span></div>");
client.println("<div class='card'><span class='label'>🎛️ Czułość wilgotności</span><span class='value'>" + String(soil_moisture_sensitivity) + " %</span></div>");
client.println("<div class='card'><span class='label'>⏱️ Timer przekaźnika</span><span class='value'>" + String(timer_setting) + " sek</span></div>");
client.println("<div class='card'><span class='label'>🔌 Przekaźnik</span><span class='value'>" + String(relay_module_state == LOW ? "WŁĄCZONY" : "WYŁĄCZONY") + "</span></div>");
client.println("<form method='GET' style='text-align:center; margin-top:30px;'>");
client.println("<button name='relay' value='on' style='background:#00cc66; color:white; border:none; padding:15px 30px; font-size:1em; border-radius:8px; margin-right:10px;'>Włącz przekaźnik</button>");
client.println("<button name='relay' value='off' style='background:#cc0033; color:white; border:none; padding:15px 30px; font-size:1em; border-radius:8px;'>Wyłącz przekaźnik</button>");
client.println("</form>");
client.println("</div>");
client.println("</body></html>");


if (request.indexOf("relay=on") >= 0) {
  digitalWrite(RELAY_MODULE, HIGH);
  relay_module_state = HIGH;
}
if (request.indexOf("relay=off") >= 0) {
  digitalWrite(RELAY_MODULE, LOW); 
  relay_module_state = LOW;
}

    client.stop();
  }
}
