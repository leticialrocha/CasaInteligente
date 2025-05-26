## Projeto Casa Inteligente com ESP32 e Broker Mosquitto

Este projeto é uma aplicação de automação residencial utilizando **ESP32**, sensores e o protocolo **MQTT** com o **broker Mosquitto**. A solução permite monitorar **temperatura**, **umidade** e o **estado da porta**, além de controlar uma **luz (LED)** remotamente via aplicativo como **MQTT Dash**.

### Funcionalidades

- Leitura de **temperatura e umidade** com o sensor **DHT11**
- Exibição das leituras no **display OLED**
- Monitoramento do **estado da porta** com sensor magnético (MC-38)
- Controle remoto de **luz (LED)** via MQTT
- Cálculo e exibição da **média de temperatura e umidade** localmente e via MQTT

---

### Materiais Utilizados

| Quantidade | Componente                         |
|------------|-------------------------------------|
| 1x         | Placa ESP32                         |
| 1x         | Cabo USB                            |
| 1x         | Sensor DHT11                        |
| 1x         | Display OLED                        |
| 1x         | Sensor magnético (MC-38)            |
| 1x         | LED                                 |
| 1x         | Resistor 330 ohms                   |
| 1x         | Protoboard                          |
| 8x         | Jumpers macho-macho                 |
| 1x         | Jumper macho-fêmea                  |

---

### Bibliotecas Utilizadas

- `WiFi` (nativa da IDE Arduino)
- `Wire` (nativa da IDE Arduino)
- `PubSubClient` – por Nick O'Leary
- `DHT sensor library`
- `U8g2` – por Oliver

---

### Ligações no ESP32

#### LED
- GPIO 2 → Resistor + LED → GND  
- GPIO 4 → Controle de LED  

#### Sensor Magnético (MC-38)
- GPIO 5 → Sinal do sensor  
- GND → Comum (sensor e LED)

#### Sensor DHT11
- GPIO 13 → DATA  
- VIN → VCC  
- GND → GND

#### Display OLED
- GPIO 21 → SDA  
- GPIO 22 → SCL  
- VIN → VCC  
- GND → GND

---

### Comunicação MQTT

- Protocolo: **MQTT**
- Broker: **Mosquitto**
- Cliente sugerido: **MQTT Dash**
- Dados de temperatura, umidade e estado da porta são publicados em tópicos MQTT
- Controle do LED por comando MQTT

---

### Exibição de Dados

- A média de temperatura e umidade é:
  - Exibida no display OLED
  - Publicada nos tópicos MQTT para visualização remota

---

### Conclusão

Este projeto integra sensores e dispositivos com comunicação MQTT para criar uma solução básica de **casa inteligente**, com monitoramento e controle em tempo real via rede.
