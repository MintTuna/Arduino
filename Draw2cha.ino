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
void M_Stop();
int goStraight(int a);
int goRight(int a);
int Draw2cha(int a, int b, int c);
char MoveInfo;

//변수 선언
int Move[100] = { 0,};
int i = 0;
int a=0;
int b=0;
int c=0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  //모터 설정
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
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
    //MoveInfo = mySerial.read();
    Move[i] = mySerial.read();
    i++;
    a = Move[0] - 48;
    b = Move[1] - 48;
    c = Move[2] - 48;
    Serial.println(a);
    Serial.println(b);
    Serial.println(c);
    Serial.println("--------------------");
    if (MoveInfo == 'z') {
      Serial.println("Go!");
      M_Stop();
    } else if (MoveInfo == 'x') {
      Serial.println("Stop!");
      Draw2cha(a, b, c);
    }
    //Draw2cha(a, b, c);
  }
  
  if (Serial.available()) {    //시리얼모니터에 입력된 데이터가 있다면
    mySerial.write(Serial.read());  //블루투스를 통해 입력된 데이터 전달
  }
}
//이차함수 그리는 부분
int Draw2cha(int a, int b, int c) {
	int x, y, i = 0;
	for (i=0;i<10;i++) {
		x = i;
		y = (a*x*x + b*x + c);
    goStraight(x);
    goRight(y);
		//printf("(%d, %d)\n", x, y);
	}
}

//모터 이동  함수
int goStraight(int a) {
  delay(100);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(500*a);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int goRight(int a) {
  delay(100);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500*a);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void M_Stop() {
  Move[0] = 0;
  Move[1] = 0;
  Move[2] = 0;
  i = 0;
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}