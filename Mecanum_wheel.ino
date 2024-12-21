#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>

//HC06 Tx, Rx 핀 2번, 3번으로 설정
SoftwareSerial mySerial(2, 3);
//모터 선언 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1;

//함수 선언
void M_Forward();
void M_Backward();
void M_Right();
void M_Left();
void M_Stop();
char MoveInfo;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  //모터 설정
  motor1.setSpeed(100);
  motor1.run(RELEASE);
  motor2.setSpeed(100);
  motor2.run(RELEASE);
  motor3.setSpeed(100);
  motor3.run(RELEASE);
  motor4.setSpeed(100);
  motor4.run(RELEASE);

  servo1.attach(10);
  servo1.write(60);


  //시리얼 통신 시작
  Serial.println("HC06 Connect!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  mySerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (mySerial.available()) { //블루투스에서 넘어온 데이터가 있는지 확인
    MoveInfo = mySerial.read();
    Serial.println(MoveInfo);
    switch(MoveInfo) {
      case 'w':
        Serial.println("FORWARD");
        M_Forward();
        break;

      case 'a':
        Serial.println("LEFT");
        M_Left();
        break;

      case 's':
        Serial.println("BACKWARD");
        M_Backward();
        break;

      case 'd':
        Serial.println("RIGHT");
        M_Right();
        break;
      case 'z':
        Serial.println("STOP");
        M_Stop();
        break;
      case 'x':
        Serial.println("SERVO");
        servo1.write(0);
        delay(1000);
        servo1.write(60);
        delay(1000);
    }

  }
  if (Serial.available()) {    //시리얼모니터에 입력된 데이터가 있다면
    mySerial.write(Serial.read());  //블루투스를 통해 입력된 데이터 전달
  }
}

//모터 이동 함수
void M_Forward() {
  delay(100);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void M_Backward() {
  delay(100);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void M_Right() {
  delay(100);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void M_Left() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void M_Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}