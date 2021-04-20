# Tempo Ideal
### Projeto de uma estação meteorológica usando C++, Esp8266, JavaScrip, Firebase e Kodular.
## COLABORADORES: Francisco Ivanilson, João Gabriel, Lucas Silva

## 1. O PRODUTO: 
Estação Meteorológica WI-FI.
	
Imaginamos um dispositivo que pudesse ser autoalimentado energeticamente, ligado a WEB que mostrasse dados de temperatura e umidade local, bem como a probabilidade de chuva no local, através de dados da pressão barométrica. No que condiz a versão final iremos implementar um Letreiro LED em cada estação. Um dos percalços presentes nesse projeto será a alimentação de todos os componentes unicamente por baterias recarregáveis a energia solar. 
	
Hardware utilizado: | WEMOS D1 R2 - ESP8266 | Sensor de Temperatura/Umidade DHT11 | Placa fotovoltaica 5v 1w | Bateria Recarregável 3,7V 500mAh | Diodo 1n4007 - 1A 1000V | Módulo carregador TP4056 - 5V 1A.

## 2. A LOGO:

Visando a  identidade visual da nossa proposta de produto, ele seguirá esse modelo à seguir:

![image](https://user-images.githubusercontent.com/77994612/115402133-83fba800-a1c1-11eb-82a1-af65dfddbada.png)

Paleta de cores escolhida:

![image](https://user-images.githubusercontent.com/77994612/115402558-e5237b80-a1c1-11eb-9b0f-4769f237dd0d.png)

## 3. AS PEÇAS:

WEMOS D1 R2 - ESP8266EX
  Escolhemos esta placa visto seu baixo custo de aquisição, ela possui um diferencial que é sua conectividade com WI-FI, ganhando assim espaço em nosso projeto que visa um módulo auto gerenciado energeticamente e sem fios de alimentação.
  Outra característica importante a ser ressaltada é de que o módulo consome pouco energia, sendo o primeiro que iremos usar no processo de aprendizagem das tecnologias, bem como da programação em C e C++ presente no Arduino IDE.
  Seu principal ponto negativo é ter apenas uma porta analógica, algo que pensamos em corrigir ao adquirir a versão mais nova dessa placa, ESP32-WROVER, contendo seis portas analógicas.

| Características| Dimensões          | Preço |
| -------------  |:-------------:     | -----:|
| ESP8266EX      | 70 x 53,5 x 12,5 mm|  $32  |

![image](https://user-images.githubusercontent.com/77994612/115403212-96c2ac80-a1c2-11eb-998f-8ef04e806d1f.png)

Sensor de Temperatura/Umidade DHT11:
Para prototipagem usaremos esse sensor de umidade e temperatura, sua simplicidade e baixo custo são os principais motivos de sua escolha.


| Características| Dimensões          | Preço |
| -------------  |:-------------:     | -----:|
| DHT11          | 23 x 12 x 5mm      |  $12  |

![image](https://user-images.githubusercontent.com/77994612/115403462-cc679580-a1c2-11eb-93a5-7bed45731e26.png)

Modulo Carregador TP4056 de Bateria de Lítio de 5V 1A com Proteção:
Esse módulo servirá para carregar a bateria que fornecerá energia aos componentes eletrônicos
			
| Características| Dimensões                 | Preço |
| -------------  |:-------------:            | -----:|
| TP4056         | 19MM(L) X 5MM(A) X 25MM(C)|  $6  |

## 4. ESQUEMA ELÉTRICO:
![image](https://user-images.githubusercontent.com/77994612/115403740-15b7e500-a1c3-11eb-9c79-f588c7aa0fad.png)

## 5. CÓDIGO ELABORADO PARA O M.C. ESP8266 USANDO:

### C++:

```c++
#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <FirebaseESP8266.h>
 

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

//#define FPM_SLEEP_MAX_TIME           0xFFFFFFF
#define WIFI_SSID "ID DO SEU ROTEADOR WI-FI"
#define WIFI_PASSWORD "SENHA DO SEU ROTEADOR WI-FI"
#define FIREBASE_HOST "HOST DO BANCO DE DADOS FIREBASE"
#define FIREBASE_AUTH "HASH UNICA DO SEU BANCO DE DADOS FIREBASE"

FirebaseData fbdo;
void setup() 
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Conectando ao ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Conectado!");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  dht.setup(4, DHTesp::DHT11);
}
 
void loop() 
{
  Serial.print("Estou acordado!");
  float h = dht.getHumidity();
  float t = dht.getTemperature();  
  int s = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Umidade: ");  
  Serial.print(h);
  
  Serial.print("%  Temperatura: ");  
  Serial.print(t);  
  Serial.println("°C ");

  Serial.print("Sensação térmica: ");
  Serial.print(s);
  Serial.println(".");
   
  Firebase.setFloat(fbdo,"Temperatura: ",t);
  Firebase.setFloat(fbdo,"Umidade: ",h);
  Firebase.setInt(fbdo,"Sensação Térmica: ",s);
  Serial.println("deep sleep por 5 minutos, volto já!");
  wifi_set_sleep_type(NONE_SLEEP_T);
  delay(300000);
}
```

## 6. WEBSITE TEMPO IDEAL:

![screenshot](https://user-images.githubusercontent.com/77994612/115406030-2cf7d200-a1c5-11eb-9dff-6c0252b4491a.png)

https://tempo-ideal.web.app/
Desenvolvido por Lucas Silva, JavaScrip e Firebase.

## 7. APP ANDROID USANDO KODULAR:

![photo5148072845119695067](https://user-images.githubusercontent.com/77994612/115406854-efe00f80-a1c5-11eb-8e2b-2e0098eabad3.jpg)
![photo5148072845119695068](https://user-images.githubusercontent.com/77994612/115406869-f1a9d300-a1c5-11eb-939f-7fab58bc8299.jpg)
![photo5148072845119695069](https://user-images.githubusercontent.com/77994612/115406872-f2db0000-a1c5-11eb-8f65-00e66a0e54f5.jpg)
![photo5148072845119695070](https://user-images.githubusercontent.com/77994612/115406878-f40c2d00-a1c5-11eb-9c24-7381cbd55abf.jpg)


[APP ANDROID.zip](https://github.com/Enkiduzis/TempoIdeal/files/6343991/APP.ANDROID.zip)

Desenvolvido por Francisco Ivanilson, Kodular e Firebase.
