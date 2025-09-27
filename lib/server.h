#ifndef SERVER_H
#define SERVER_H

#include <WiFi.h>

extern WiFiServer server;

void startServer();
void handleClient();

#endif
