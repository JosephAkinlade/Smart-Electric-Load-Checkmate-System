# Smart-Electric-Load-checkmate-system

This project aims to develop an electrical appliance monitoring and control system for halls of residence. The system measures the current consumption in each room to detect unauthorized appliances and takes appropriate actions to ensure compliance with safety regulations. Additionally, the system includes a web server hosted on the ESP8266, allowing authorized personnel to set thresholds and restore power to rooms after necessary punishment has been meted out.

# Features
1. Current consumption monitoring: The system measures the current consumption in each room to detect unauthorized appliances.
2. Unauthorized load detection: When the current consumption exceeds a predefined threshold, the system identifies it as an unauthorized load.
3. Alert notification: The system sends alerts to designated personnel when unauthorized appliances are detected in rooms.
4. Power cutoff: The system cuts off the power supply to rooms with unauthorized loads, ensuring compliance with safety regulations.
5. Web server interface: The system includes a web server hosted on the ESP8266, providing an interface for authorized personnel to set thresholds and control power restoration.
6. Threshold configuration: Authorized personnel can set and adjust the current thresholds for each room through the web server.
7. Power restoration control: After necessary punishment or corrective action has been taken, authorized personnel can restore power to the rooms through the web server interface.
8. Real-time monitoring: The system provides real-time monitoring of current consumption, enabling immediate detection and action against unauthorized appliances.

# Components
1. ESP8266 and Arduino Nano
2. PZEM-004T Metering Module
3. NRF24L01 Transceiver
4. Relays
5. 20x4 LCD
