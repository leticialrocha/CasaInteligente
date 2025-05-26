#define LED_PIN 4
#define PORTA_PIN 5

bool estado_sensor;
long millisatual = 0;
int intervalo = 10000;  //15000

/************* Wi-Fi *************/
#include <WiFi.h>
const char* ssid = "sala 10";
const char* senha = "info@134";
WiFiClient espClient;

/************* MQTT *************/
#include <PubSubClient.h>
const char* mqtt_server = "172.16.58.1 ";
const int mqtt_porta = 1883;

const char* led_topico     = "LED";
const char* porta_topico   = "Porta";
const char* temp_topico    = "Temperatura";
const char* umid_topico    = "Umidade";
const char* retorno_led    = "retornLED";
const char* retorno_porta  = "retornPorta";

PubSubClient client(espClient);

/************* Display OLED *************/
#include <Wire.h>
#include <U8g2lib.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0X3C

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCL, SDA);

/************* Sensor DHT *************/
#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int leitura = 10;
float temp[leitura];
float humid[leitura];

/************* Funções Wi-Fi *************/
void setup_Wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nconectado");
  Serial.println("endereco ip");
  Serial.println(WiFi.localIP());
}

/************* Reconnect MQTT *************/
void reconnect() {
  while (!client.connected()) {
    Serial.print("reconectando ao mqtt");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado");
      client.subscribe(led_topico);
      client.subscribe(porta_topico);
      client.subscribe(temp_topico);
      client.subscribe(umid_topico);
    }
  }
}

/************* Callback MQTT *************/
void callback(char* topico, byte* payload, unsigned int length) {
  Serial.print("mensagem recebida no topico ");
  Serial.println(topico);

  if (strcmp(topico, led_topico) == 0) {
    if (payload[0] == '1') {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("led ligado");
      client.publish(retorno_led, "led ligado");

      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.setCursor(70, 15);
      u8g2.print("LED");
      u8g2.sendBuffer();

      u8g2.setCursor(70, 28);
      u8g2.print("Ligado");
      u8g2.sendBuffer();

    } else if (payload[0] == '0') {
      digitalWrite(LED_PIN, LOW);
      Serial.println("led desligado");
      client.publish(retorno_led, "led desligado");

      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.setCursor(70, 15);
      u8g2.print("LED");
      u8g2.sendBuffer();

      u8g2.setCursor(70, 28);
      u8g2.print("Desligado");
      u8g2.sendBuffer();
    }
  }
}

/************* Display OLED *************/
void oled() {
  u8g2.clearBuffer();
  u8g2.drawFrame(1, 1, 64, 38);     // temp
  u8g2.drawFrame(66, 1, 62, 32);    // coluna 1
  u8g2.drawFrame(1, 40, 64, 24);    // umidade
  u8g2.drawFrame(66, 34, 62, 30);   // coluna 2
}

/************* Temperatura e Umidade *************/
void temperatura() {
  float somat = 0.0;
  float somah = 0.0;

  for (int i = 0; i < leitura; i++) {
    temp[i] = dht.readTemperature();
    humid[i] = dht.readHumidity();

    if (isnan(humid[i]) || isnan(temp[i])) {
      Serial.println("falha ao ler sensor");
      continue;
    }

    somat += temp[i];
    somah += humid[i];
  }

  float mediat = somat / leitura;
  float mediah = somah / leitura;

  Serial.println("\nA temperatura média é: " + String(mediat) + "°C");
  Serial.println("A umidade média é: " + String(mediah) + "%");

  u8g2.setFont(u8g2_font_ncenB12_tr);
  u8g2.setCursor(5, 28);
  u8g2.print(String(mediat) + "ºC");
  u8g2.sendBuffer();

  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 56);
  u8g2.print(String(mediah) + "%");
  u8g2.sendBuffer();

  client.publish(temp_topico, String(mediat).c_str());
  client.publish(umid_topico, String(mediah).c_str());
}

/************* Setup *************/
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(PORTA_PIN, INPUT_PULLUP);

  setup_Wifi();

  client.setServer(mqtt_server, mqtt_porta);
  client.setCallback(callback);

  dht.begin();
  u8g2.begin();
}

/************* Loop Principal *************/
void loop() {
  oled();

  unsigned long contadorMillis = millis();

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if (contadorMillis - millisatual > intervalo) {
    millisatual = contadorMillis;

    temperatura();

    estado_sensor = digitalRead(PORTA_PIN);
    if (estado_sensor == 1) {
      Serial.println("porta aberta");
      client.publish(porta_topico, "porta aberta");
    } else {
      Serial.println("porta fechada");
      client.publish(porta_topico, "porta fechada");
    }
  }
}
