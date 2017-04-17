#include <Servo.h>
Servo myservo;  // 定义舵机变量
const int TrigPin = 2; 
const int EchoPin = 3; 
int L_A = 4;
int L_B = 5;
int R_A = 6;
int R_B = 7;
float a[6]={};
float CJ_data_a;

void csb(int pos) 
{
  myservo.write(pos);  
  delay(250);       //舵机动作时间
}

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

//读取前置超声波测距数据
void read_csb(int TrigPin,int EchoPin)
{
  unsigned int s,t,f;   
  // 产生一个10us的高脉冲去触发TrigPin
  for (s=0;s<6;s++)         //连续6次，读取前置超声波测距数值
  {
    digitalWrite(TrigPin, LOW);    //引脚 2 为 低
    delayMicroseconds(2);           //延时
    digitalWrite(TrigPin, HIGH);   //引脚 3 为 高
    delayMicroseconds(10);          
    digitalWrite(TrigPin, LOW);           // 检测脉冲宽度，并计算出距离
    a[s] = pulseIn(EchoPin, HIGH) / 58.00;   //s 即为上面的0～6的数值。分别将数值存入a[0]～a[5]中
    delay(10);
  }
}

//对超声波数组进行排序（冒泡法：小额数值往上走，大的数值往下走）
void Cj_data()
{
  unsigned int i,j,s; 
  float temp1;

  for(s=0;s<6;s++)
  {
    for(j=0;j<=5;j++) 
    {
      for (i=0;i<5-j;i++) 
        if (a[i]>a[i+1]) 
        {
          temp1=a[i];         //前置数值
          a[i]=a[i+1]; 
          a[i+1]=temp1;
        } 
    }
  }
}


//对超声波数组排序结果，掐头去尾取平均，得到测距值
void JL()
 {
    unsigned int i;
    float CJ_temp1;
    for (i=1;i<5;i++)
    {
       CJ_temp1+=a[i];    //累加
    }
      
    CJ_data_a=CJ_temp1*100/400;      //取4个数据取平均
 }
//测定当前距离
void CJ()
 {
  read_csb(2,3);       //读前置超声波
  Cj_data();      //对数据排序
  JL();           //掐头去尾取平均，得到测距值
   
}



void JL_Panduan()
{
    if (CJ_data_a<20) 
  {
      stop();
      delay(200);
      Go_back();
  }
   else
  {
    if (CJ_data_a<35)   
    {
      stop();
      delay(200);
      LR_panduan();
    }
    else
    {
      Go_run();
      }
    }
  }



void LR_panduan()
{
  float M1, M2;
  csb(40);      //舵机转右40°
  CJ();         //测定当前距离
  M1=CJ_data_a;   //40°右侧距离
  csb(160);     //舵机转左160°
  CJ();
  M2=CJ_data_a;   //160°左侧距离
  csb(100);     //舵机归正位

  if((M1<40)&&(M2<40))
  {
    Go_back();
  }
  if((M1<40)&&(M2>40))
  {
    left();
  }
  if((M1>40)&&(M2<40))
  {
    right();
  }
  if((M1>40)&&(M2>40))
  {
    left();
  }
}

 
void setup()
{
   pinMode(2, OUTPUT);   //前置超声波接口引脚
   pinMode(3, INPUT);   
   pinMode(4, OUTPUT);  
   pinMode(5, OUTPUT);   
   pinMode(6, OUTPUT);  
   pinMode(7, OUTPUT); 
   Serial.begin(9600); 
   myservo.attach(13);  //定义舵机接口数字接口13
   csb(100);      //舵机带动超声波传感器至正位
}
void loop()

{
  while(1)
    { 
      CJ();
    JL_Panduan();
    }
}

