# CasaInteligente
Projeto da Casa Inteligente com o Servidor broker Mosquitto
Para a entrega do projeto, vamos evoluir a aplicação desenvolvida ao longo desta Sprint, utilizando o sensor DHT11 em conjunto com o display OLED para monitorar a umidade e a temperatura.
Também vamos monitorar a umidade e a temperatura, verificar se a porta principal está aberta ou fechada e acender o LED que representa a luz da casa através do aplicativo MQTT Dash ou similar. A média dos valores coletados para temperatura e umidade será apresentada tanto no OLED quanto nos dispositivos clientes usando o protocolo MQTT.
Materiais para o projeto com o ESP32:
1 × Placa ESP32

1 × Cabo de comunicação USB para o ESP32

8 × Jumpers Macho-Macho

1 × Jumper Macho-Fêmea

1 × Sensor magnético com fio para alarme (MC-38)

1 × Protoboard

1 × LED

1 × Resistor 330 ohms (laranja, laranja, marrom, dourado)

1 × Display OLED

1 × Sensor DHT11

Bibliotecas utilizadas:
WiFi (nativa da IDE)

PubSubClient – por Nick O'Leary

DHT sensor library

U8g2 – por Oliver

Wire (nativa da IDE)

Esquema de ligação das GPIO do ESP32:
GPIO 2 → Resistor + LED (220 ou 330 ohms)

GPIO 5 → Módulo MC-38

GND (ESP32) → Protoboard (comum para o módulo MC-38)

GND (ESP32) → Protoboard (comum para o LED)

Esquema de ligação das portas do sensor magnético:
GND (ESP32) → GPIO 5 (ESP32)

Esquema de ligação do LED:
GPIO 4 (ESP32) → Resistor + LED → GND

Esquema de ligação do OLED:
GPIO 21 (ESP32) → SDA

GPIO 22 (ESP32) → SCL

GND (ESP32) → GND (OLED)

VIN (ESP32) → VCC (OLED)

Esquema de ligação do DHT11:
GPIO 13 (ESP32) → Sinal (DATA)

GND (ESP32) → GND (DHT11)

VIN (ESP32) → VCC (DHT11)
