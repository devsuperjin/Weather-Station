#include <ESP8266WiFi.h>
#include <Arduino.h>
//#include <Ticker.h>
#include <EEPROM.h>
#include "Wire.h"
#include <SPI.h>
#include "EPD_drive.h"
#include "EPD_drive_gpio.h"
#include "bitmaps.h"
#include "FS.h"
#include "SHT31.h"
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#define SHT31_ADDRESS   0x44
#define debug 1; ///< 调试模式，打开串口输出
#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

Duck_EPD EPD;
SHT31 sht;
char  tmpbuffer[10];
char  humbuffer[10];
float fTemperature;
float fHumidity;

void setup() {
wifi_connect(); // in wifi_info.h
  my_homekit_setup();
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
 
  initInfo();  //加载初始化信息

}

void initInfo()
{
 EPD.EPD_Set_Model(OPM42);    //设置屏幕类型 DKE42_3COLOR
 EPD.EPD_init_Full();         //全刷初始化，使用全刷波形
 EPD.clearbuffer();           //清空缓存(全白)
 EPD.fontscale=2;             //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
 EPD.SetFont(FONT12);         //选择字体(仅FONT12支持中文)，字体可用群文件工具生成上传至spiffs使用
 EPD.DrawUTF(0,0,"POWERD BY SUPERJIN");   //绘制字符串
 EPD.DrawUTF(26,0,"COPYRIGHT 2022");  //绘制字符串
 EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer,1);//将缓存中的图像传给屏幕控制芯片刷新屏幕
 EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
 EPD.deepsleep();
 delay(2000);
 //刷白准备数据
 EPD.EPD_init_Full();      
 EPD.fontscale=2;       
 EPD.SetFont(FONT12);       
 EPD.clearbuffer();     
 EPD.DrawUTF(270,2,"TRUMP 2024");   //绘制字符串

  EPD.DrawUTF(0,1,"环境温度：");   //绘制字符串
 EPD.DrawUTF(26,1,"环境湿度："); 
 EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer,1);//将缓存中的图像传给屏幕控制芯片刷新屏幕
 EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
 EPD.deepsleep();
}

void loop()
{
  //temp and hum
  SPI.end();
  Wire.begin(13,14);
   pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  sht.begin(SHT31_ADDRESS);
  sht.read();   
   digitalWrite(12,LOW);
  fTemperature=sht.getTemperature();
  
  fHumidity=sht.getHumidity();
  
  itoa((int)fTemperature, tmpbuffer, 10);
  itoa((int)fHumidity, humbuffer, 10);

   //display
   SPI.begin();
 EPD.EPD_init_Part();
 EPD.clearbuffer();           //清空缓存(全白)
 EPD.fontscale=2;             //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
 EPD.SetFont(FONT12);         //选择字体(仅FONT12支持中文)
 
 EPD.DrawUTF(0,120,tmpbuffer);   //绘制字符串

 EPD.DrawUTF(26,145,"%");   //绘制字符串
 EPD.DrawUTF(0,145,"C");   //绘制字符串

 EPD.DrawUTF(26,120,humbuffer); 
 //局刷范围为x 0~23 y 0~199,其中y坐标的开始位置必须是8的倍数，y坐标的结束位置必须是8的倍数减一，x坐标随意(仅针对4.2,其他尺寸xy限制相反）
 EPD.EPD_Dis_Part(0,52,120,199,(unsigned char *)EPD.EPDbuffer,1);//将缓存中的图像传给屏幕控制芯片刷新屏幕
 EPD.ReadBusy();//等待屏幕刷新完成后才继续往下运行
 EPD.deepsleep();//睡眠 屏幕进入低功耗模式，屏幕用完后必须使用，否则图像会慢慢变色，唤醒可用Init函数
  my_homekit_loop();

 delay(30000);
//  yield();//长时间的循环中务必加次语句，防止看门狗复位
}




extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_current_temperature;
extern "C" homekit_characteristic_t cha_humidity;
static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_setup() {
  arduino_homekit_setup(&config);
}


void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_report_millis) {
    // report sensor values every 10 seconds
    next_report_millis = t + 10 * 1000;
    my_homekit_report();
  }
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

  }
}

void my_homekit_report() {
  //float temperature_value = random_value(10, 30); // FIXME, read your real sensor here.
  cha_current_temperature.value.float_value = fTemperature;
  cha_humidity.value.float_value = fHumidity;
  LOG_D("Current temperature: %.1f", fTemperature);
  LOG_D("Current humidity: %.1f", fHumidity);
  homekit_characteristic_notify(&cha_current_temperature, cha_current_temperature.value);
  homekit_characteristic_notify(&cha_humidity, cha_humidity.value);
}
