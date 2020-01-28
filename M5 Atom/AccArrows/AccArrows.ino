#include "M5Atom.h"

extern const unsigned char imageUp[75 + 2];
extern const unsigned char imageDown[75 + 2];
extern const unsigned char imageLeft[75 + 2];
extern const unsigned char imageRight[75 + 2];
extern const unsigned char imageTop[75 + 2];

float accX = 0, accY = 0, accZ = 0;
int lastImage = 0;
bool IMU6886Flag = false;

void setup()
{
    M5.begin(true, false, true);
    if (M5.IMU.Init() != 0)
        IMU6886Flag = false;
    else
        IMU6886Flag = true;
    delay(50);
}

void loop()
{
    if (IMU6886Flag == true)
    {
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        if (accX < -0.8 && abs(accY) < 0.4 && lastImage != 1){
          lastImage = 1;
          M5.dis.displaybuff((uint8_t *)imageRight, 0, 0);
        }
        else if(accX > 0.8 && abs(accY) < 0.4  && lastImage != 2){
          lastImage = 2;
          M5.dis.displaybuff((uint8_t *)imageLeft, 0, 0);
        }
        else if(accY < -0.8 && abs(accX) < 0.4  && lastImage != 3){
          lastImage = 3;
          M5.dis.displaybuff((uint8_t *)imageDown, 0, 0);
        }
        else if(accY > 0.8 && abs(accX) < 0.4  && lastImage != 4){
          lastImage = 4;
          M5.dis.displaybuff((uint8_t *)imageUp, 0, 0);
        }
        else if(abs(accX) < 0.4 && abs(accY) < 0.4 && accZ < -0.8  && lastImage != 5){
          lastImage = 5;
          M5.dis.displaybuff((uint8_t *)imageTop, 0, 0);
        }
        Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX , accY , accZ );
    }
    delay(100);
    M5.update();
}
