#include <Ps3Controller.h>
#include <math.h>

uint8_t senddata[5];
const double pi = 3.141592;
int Lx = 0;
int Ly = 0;
int Rx = 0;
int Ry = 0;
bool pin = false;

void  setup()
{
    Serial.begin(9600);
    Ps3.begin("24:0A:C4:81:7E:3A"); 
    //Serial.println("Ready");
    
}

int stick_data(double x1, double y1){
    if(abs(x1)+abs(y1) <= 30){
      return 0;
    }
    
    double x2 = 0, y2 = -128;
    double dotProduct = x1*x2 + y1*y2;
    double mag1 = sqrt(x1*x1 + y1*y1);
    double mag2 = sqrt(x2*x2 + y2*y2);
    double cosTheat = dotProduct/(mag1*mag2);
    double angleRad = acos(cosTheat);
    double angleDeg = (angleRad/pi)*180;

    double crossProduct = x1 * y2 - y1 * x2;
    if (crossProduct > 0) { angleDeg = 360.0 - angleDeg; }

    //Serial.printf("dotProduct = %f angleDeg = %f mag2 = %d",dotProduct,mag1,mag2);
    //Serial.printf("cosTheat = %d mag1 = %d mag2 = %d",cosTheat,mag1,mag2);
    //Serial.printf("angleDeg = %f ",angleDeg);
    
    //送信するデータの計算
    int Data = 0;
      for(int i = 1; i < 8;i++){
        if((45*(i-1)+22.5 <= angleDeg) &&(angleDeg <45*i+22.5)){
          Data = pow(2,i);
          return Data;
        }
      }
    return 1;
}


void  loop()
{
  for(int i = 0; i < 5;i++){
      senddata[i] = 0;
    }
  if  (Ps3.isConnected()){
    pin = false;

    if (Ps3.data.button.circle)   {senddata[1] += 1;  pin = true;}
    if (Ps3.data.button.cross)    {senddata[1] += 2;  pin = true;}
    if (Ps3.data.button.square)   {senddata[1] += 4;  pin = true;}
    if (Ps3.data.button.triangle) {senddata[1] += 8;  pin = true;}
    if (Ps3.data.button.right)    {senddata[1] += 16; pin = true;}
    if (Ps3.data.button.down )    {senddata[1] += 32; pin = true;}
    if (Ps3.data.button.left )      {senddata[1] += 64; pin = true;}
    if (Ps3.data.button.up)     {senddata[1] += 128;pin = true;}
    if (Ps3.data.button.r1 )      {senddata[2] += 1;  pin = true;}
    if (Ps3.data.button.l1)       {senddata[2] += 2;  pin = true;}
    if (Ps3.data.button.r2 )      {senddata[2] += 4;  pin = true;}
    if (Ps3.data.button.l2)       {senddata[2] += 8;  pin = true;}
    if (Ps3.data.button.select)   {senddata[2] += 16; pin = true;}
    if (Ps3.data.button.start)    {senddata[2] += 32; pin = true;}
    if (Ps3.data.button.l3)       {senddata[2] += 64; pin = true;}
    if (Ps3.data.button.r3)       {senddata[2] += 128;pin = true;}

    
    Lx = Ps3.data.analog.stick.lx;
    Ly = Ps3.data.analog.stick.ly;
    Rx = Ps3.data.analog.stick.rx;
    Ry = Ps3.data.analog.stick.ry;
    senddata[3] = stick_data(Lx,Ly);
    senddata[4] = stick_data(Rx,Ry);
    
  }
  else{
    pin = false;
    for(int i = 0; i < 5;i++){
      senddata[i] = 0;
    }
  }

  if(pin || (senddata[3] || senddata[4])){
    senddata[0] = 128;
  }
  else{
    senddata[0] = 0;
  }
  
  for(int i = 0; i < 5;i++){
      //Serial.printf("data[%d] = %d ", i, senddata[i]);//デバック
      Serial.write(senddata[i]);
    }
   //Serial.println();//デバック

  delay(100);
}