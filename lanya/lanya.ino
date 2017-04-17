int L_A = 4;
int L_B = 5;
int R_A = 6;
int R_B = 7;

#define LEFT '3' //左转编码
#define RIGHT '4'//右转编码
#define GO '1'//前进编码
#define BACK '2'//后退编码
#define STOP '0'//停止编码

char left_code = '1';


void Go_run()
{
  digitalWrite(L_A,HIGH);
  digitalWrite(L_B,LOW);
  digitalWrite(R_A,HIGH);
  digitalWrite(R_B,LOW);
}



void Go_back()
{
  digitalWrite(L_A,LOW);
  digitalWrite(L_B,HIGH);
  digitalWrite(R_A,LOW);
  digitalWrite(R_B,HIGH);
  delay(80);     
}

void left()
{
  digitalWrite(L_A,HIGH);
  digitalWrite(L_B,LOW);
  digitalWrite(R_A,LOW);
  digitalWrite(R_B,LOW);
  delay(550);
}

void right()
{
  digitalWrite(L_A,LOW);
  digitalWrite(L_B,LOW);
  digitalWrite(R_A,HIGH);
  digitalWrite(R_B,LOW);
  delay(550);
}

void stop()
{
  digitalWrite(L_A,LOW);
  digitalWrite(L_B,LOW);
  digitalWrite(R_A,LOW);
  digitalWrite(R_B,LOW);
  
}

void initCar(){
  //默认全是低电平 停止状态
  digitalWrite(L_A,LOW);      
  digitalWrite(L_B,LOW);
  digitalWrite(R_A,LOW);   
  digitalWrite(R_B,LOW);
}

void setup()
{ 
   pinMode(4, OUTPUT);  
   pinMode(5, OUTPUT);   
   pinMode(6, OUTPUT);  
   pinMode(7, OUTPUT); 
   Serial.begin(9600); 
   initCar();
}



void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
      char ch = Serial.read();
      if(ch == GO){
         //前进
         Go_run();
      }else if(ch == BACK){
         //后退
         Go_back();
      }else if(ch == LEFT){
         //左转
         left();
      }else if(ch == RIGHT){
        //右转
        right();
      }else if(ch=='0'){
        //停车
        stop();
      }
    }
}
