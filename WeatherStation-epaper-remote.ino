/**
  GPL v3.0
  Copyright (c) 2017 by Superjin
*/

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "Wire.h"
#include <EEPROM.h>
#include <SPI.h>
#include "EPD_drive.h"
#include "EPD_drive_gpio.h"
#include "bitmaps.h"
#include "FS.h"
#include "SHT31.h"
#define SHT31_ADDRESS   0x44
#define debug 1; ///< 调试模式，打开串口输出
Duck_EPD EPD;

uint32_t start;
uint32_t stop;

SHT31 sht;

int itime;
void setup() {

#ifdef debug
  Serial.begin(115200);
  Serial.println(ESP.getResetInfoPtr()->reason);
  Serial.printf("Serial begins at %dms\n", millis());
#endif
  pinMode(CS,OUTPUT);//io初始化
  pinMode(DC,OUTPUT);
  pinMode(RST,OUTPUT);
  pinMode(BUSY,INPUT);
  pinMode(CLK,OUTPUT);
  pinMode(DIN,OUTPUT);

  SPIFFS.begin();//使用SPIFFS中存储的字库，不知道怎么上传可以先刷天气固件，工具>FLASH size>选择3MB的FS
  SPI.pins();
  twocolor();  //双色屏
  itime = 0;
}

void twocolor()
{
  EPD.EPD_Set_Model(OPM42);    //设置屏幕类型 DKE42_3COLOR
  EPD.EPD_init_Full();         //全刷初始化，使用全刷波形
  EPD.clearbuffer();
  EPD.fontscale = 2;
  EPD.SetFont(FONT32);       //清空缓存(全白)
  EPD.DrawUTF(50, 20, "TRUMP 2024"); //绘制字符串
  EPD.SetFont(FONT12);
  EPD.DrawUTF(200, 50, "时间:");
  EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片刷新屏幕
  EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
  EPD.deepsleep();
  delay(2000);
}

void loop()
{

  Serial.print(getTemp(), 1);
  delay(2000);
  yield();//长时间的循环中务必加次语句，防止看门狗复位
}

float getTemp(){
  SPI.end();
 // pinMode(15,OUTPUT);
  //digitalWrite(15,HIGH);
  
  delay(200);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  Wire.begin(13,14);
  sht.begin(SHT31_ADDRESS);
  Wire.setClock(100000);
   uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  delay(200);
  start = micros();
  sht.read();         // default = true/fast       slow = false
  stop = micros();
  Serial.println();
  return sht.getTemperature();
}
