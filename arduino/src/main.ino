#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>

BLEService sensorService("66df5109-edde-4f8a-a5e1-02e02a69cbd5");
BLEStringCharacteristic alert("8326959a-2068-4e38-935b-7091daaa5976", BLERead | BLENotify,15);


const int LED = 12;               // 조도가 약해질때 LED를 켜기 위해 연결하는 PIN
int ble_connect = 0;              // 블루투스 연결 상태 변수
int alert_v = 0;                  // 장애물 상태 변수(0:장애물 없음, 1:장애물 있음, 라이다 거리 탐지 1.5m 이내의 경우)
int distance_v = 0;               // 라이다 감지 거리 변수 (mm)
int light_v = 0;                  // 조도 값 변수

unsigned long lastTime = 0;       // 센서 데이터 측정한 마지막 접속 시간 저장 변수
unsigned long timerDelay = 250;   // 센서 데이터 측정 간격 저장 변수 (100ms = 0.1sec)

void setup() {
  Serial.begin(115200);  // 시리얼 모니터 연결 시작
  delay(5000);  // 시리얼 모니터가 연결되는 시간을 보장하기 위해 5초간 대기

  Serial.println("Initializing Please wait for a moment...");

  Serial1.begin(115200);  // 라이다 통신 연결 시작

  if (!APDS.begin()) {    //APDS9960 센서 시작
    Serial.println("APDS9960 센서 시작 오류");
    while (1);
  }
  Serial.println("APDS9960 센서 시작 정상");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);

  if (!BLE.begin()) {     // BLE 활성화
    Serial.println("BLE 시작 오류");
    while (1);
  }

  BLE.setLocalName("Arduino_Nano33_BLE");
  BLE.setAdvertisedService(sensorService);
  sensorService.addCharacteristic(alert);
  BLE.addService(sensorService);

  BLE.advertise();
  Serial.println("BLE 활성화 완료 연결 대기중...");
}


void loop() {
  BLEDevice central = BLE.central();

  // timerDelay 시간 간격으로 센서 데이터 전송
  if ((millis() - lastTime) > timerDelay) {
    readData();   // 센서 데이터 읽기, 시리얼 출력, LED 제어

    if (central.connected()) {
      if (ble_connect == 0) {
        Serial.print("BLE 연결 시작: ");
        Serial.println(central.address());
        digitalWrite(LED_BUILTIN, HIGH);
        ble_connect = 1;
      }
      sendData();   // 센서 데이터 블루투스 전송
    } else {
      if (ble_connect == 1) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.print("BLE 연결 종료");
        ble_connect = 0;
      }
    }

    lastTime = millis();
  }
}


void readData() {
  int i, r, g, b, n_light = 0;
  int dat[32] = { 0 };

  // 조도 센서 데이터 처리
  if(APDS.colorAvailable()) {
    APDS.readColor(r, g, b, n_light);
    light_v = n_light;
  }

  Serial.print("조도: "); Serial.println(light_v);
  if(light_v < 100) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);

  if (Serial1.available() >= 32) {
    // 라이다 센서 테이터 처리
    for (i=0; i<32; i++) {
      dat[i] = Serial1.read();
    }

    for (i=0; i<16; i++) {
      if (dat[i] == 0x57 && dat[i + 1] == 0 && dat[i + 2] == 0xff && dat[i + 3] == 0) {
        if (dat[i + 12] + dat[i + 13] * 255 == 0) {
          Serial.println("Out of range!");
        } else {
          distance_v = dat[i + 8] + dat[i + 9] * 255;
          Serial.print("거리: ");
          Serial.print(distance_v);
          Serial.print("mm\t");
          Serial.print("장애물: ");
          if(distance_v < 2000) {
            alert_v = 1;
            Serial.println("감지");
          } else {
            alert_v = 0;
            Serial.println("없음");
          }
        }
        break;
      }
    }
  }
}


void sendData() {
  alert.writeValue(String(alert_v));
} 