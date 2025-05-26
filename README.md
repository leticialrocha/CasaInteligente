# 🏠 Projeto Casa Inteligente com ESP32 e Broker Mosquitto

Este projeto é uma solução de automação residencial utilizando o microcontrolador **ESP32**, o protocolo **MQTT** com o **broker Mosquitto**, e sensores para monitoramento ambiental. A aplicação permite monitorar **temperatura**, **umidade** e o **estado da porta principal**, além de controlar uma **luz (LED)** remotamente via aplicativo como **MQTT Dash**.

## 📋 Funcionalidades

- Leitura de **temperatura e umidade** com o sensor **DHT11**
- Exibição das leituras em um **display OLED**
- Monitoramento do **estado da porta** (aberta ou fechada) com sensor magnético
- Controle de **luz (LED)** remotamente via MQTT
- **Média de temperatura e umidade** publicada para clientes MQTT e exibida no OLED

---

## 🧰 Materiais Utilizados

| Quantidade | Componente                         |
|------------|-------------------------------------|
| 1x         | Placa ESP32                         |
| 1x         | Cabo USB para ESP32                 |
| 8x         | Jumpers macho-macho                 |
| 1x         | Jumper macho-fêmea                  |
| 1x         | Sensor magnético (MC-38)            |
| 1x         | Protoboard                          |
| 1x         | LED                                 |
| 1x         | Resistor 330 ohms                   |
| 1x         | Display OLED                        |
| 1x         | Sensor DHT11                        |

---

## 📚 Bibliotecas Utilizadas

- `WiFi` *(nativa da IDE Arduino)*
- `Wire` *(nativa da IDE Arduino)*
- `PubSubClient` – por Nick O'Leary
- `DHT sensor library`
- `U8g2` – por Oliver

---

## 📌 Esquema de Ligações

### 🔌 LED
- GPIO 2 → Resistor 330Ω → LED → GND

### 🚪 Sensor Magnético (MC-38)
- GPIO 5 → Módulo MC-38
- GND (ESP32) → Comum (MC-38 e LED)

### 🌡️ Sensor DHT11
- GPIO 13 → DATA (Sinal)
- VIN (ESP32) → VCC (DHT11)
- GND → GND (DHT11)

### 📺 Display OLED
- GPIO 21 → SDA (OLED)
- GPIO 22 → SCL (OLED)
- VIN (ESP32) → VCC (OLED)
- GND → GND (OLED)

---

## 🌐 Comunicação MQTT

A comunicação é realizada via protocolo MQTT utilizando o **broker Mosquitto**. As leituras de sensores e comandos são enviados/recebidos por tópicos MQTT definidos na aplicação. É possível utilizar aplicativos como **MQTT Dash** para visualizar dados e interagir com o sistema.

---

## 📱 Aplicativo Cliente Sugerido

- **MQTT Dash (Android)** ou outro cliente MQTT para visualização em tempo real das leituras e controle do LED.

---

## 📊 Exibição de Dados

A média das leituras de **temperatura** e **umidade** é:
- Exibida diretamente no **display OLED**
- Publicada periodicamente nos tópicos MQTT para acesso remoto

---

## ✅ Conclusão

Este projeto integra sensores, displays e comunicação remota para criar uma base funcional de uma **casa inteligente**, utilizando o ESP32 e tecnologias modernas de IoT.

---

