# Barumi

### 시각 장애인을 위한 대중교통 도움 지팡이 및 버스 정보 앱 개발

![image](https://github.com/user-attachments/assets/063c3acf-bbf8-40dd-8215-67ce2cdc7882)


지팡이 
1) 조도센서를 통해 설정 밝기값 이하로 내려갈 경우 LED 점등이 되고 설정 밝기값 이상으로 올라갈 경우 LED 소등
2) 라이다 센서를 통해 장애물 감지
3) 지팡이를 통해 장애물을 감지한 데이터를 블루투스를 이용해 어플로 전송

어플
1) 공공데이터 API 통해 서울 버스 위치 정보조회, 서울 버스 도착 정보 조회, 대중교통 환승 경로 데이터 받기
2) 버스 정보 데이터를 이용하여 현재 버스 정보를 확인3) 장애물을 감지한 데이터를 받아와 알림
4) 버스 정보 데이터를 통해 경유하는 버스 정보 알림
5) 목적지 정류장 도착 전 알림

### 서비스 흐름도

![image](https://github.com/user-attachments/assets/b63fd3c8-c6e0-46c5-8ccb-bc5c060dbb72)


### 기능 흐름도

![image](https://github.com/user-attachments/assets/9d14d7ad-946d-4670-a068-90c65b3d96b3)
