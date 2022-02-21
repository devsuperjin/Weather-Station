#include "FS.h"
#include "EPD_drive.h"
#include "EPD_drive_gpio.h"


unsigned char UNICODEbuffer[200];
String fontname;



 Duck_EPD::Duck_EPD(){
 
}


void Duck_EPD::SetFont(FONT fontindex)
{
     FontIndex=fontindex;
     switch (fontindex)
     {
     case 0:
     fontname="/font16";fontwidth=16;fontheight=16;break;
     case 1:
     fontname="/font32";fontwidth=32;fontheight=32;break;
     case 2:
     fontname="/font10";fontwidth=10;fontheight=10;break;
     case 3:
     fontname="/font12";fontwidth=12;fontheight=12;break;
     case 5:
     fontname="/font70";fontwidth=70;fontheight=70;break;
     case 6:
     fontname="/font12num";fontwidth=12;fontheight=12;break;
     case 7:
     fontname="/font24";fontwidth=24;fontheight=24;break;
     case 8:
     fontname="/font8";fontwidth=8;fontheight=8;break;
     case 9:
     fontname="/font100num";fontwidth=100;fontheight=100;break;
     case 11:
     fontname="/weathericon";fontwidth=32;fontheight=32;break;
     case 12:
     fontname="/weathericon80";fontwidth=80;fontheight=80;break;
      case 13:
     fontname="/weathericon32";fontwidth=32;fontheight=32;break;
     case 14:
     fontname="/weathericon50";fontwidth=50;fontheight=50;break;
     }
  }
  void Duck_EPD::DrawCircle(int x,int y,int r,bool fill)
  {
    if(fill==0)
    {
      for(int i=0; i<360; i++)
    {
      SetPixel(round(cos(i)*r+x),round(sin(i)*r)+y);
      
    }
    }
    else
    {
      for(int j=0;j<r;j++)
      {
        
                for(int i=0; i<360; i++)
            {
              SetPixel(round(cos(i)*j+x),round(sin(i)*j)+y);
              
            }
        }
      }  
 }

 void Duck_EPD::DrawBox(byte x,int y, int w, int h)
 {

    for(int i=x;i<x+h;i++)
  {
    DrawXline( y, y+ w-1,  i);
  }
  
 }
 void Duck_EPD::DrawEmptyBox(int x,int y,int w,int h)
{
   DrawXline(y,y+w, x);
   DrawXline(y,y+w, x+h);
   DrawYline(x,x+w, y);
   DrawYline(x,x+w, y+w);
  
}
 
 void Duck_EPD::DrawChart(int x,int y,int w, int c1, int c2, int c3, int c4, int c5,int c6)
  {
    
    int percent,sum,max_c=0;
    sum=c1+c2+c3+c4+c5+c6;
    if(sum==0) sum=1;
    max_c=max(c1,max_c);max_c=max(c2,max_c);max_c=max(c3,max_c);
    max_c=max(c4,max_c);max_c=max(c5,max_c);max_c=max(c6,max_c);
    if(max_c==0) max_c=1;
    w=w*sum/(2*max_c);
    
    SetFont(FONT12);
    DrawUTF(x,y,">0.3um");
    percent=w*c1/sum;
    DrawBox(x+1,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+2,y+41+percent,String(c1));
   
    SetFont(FONT12);
    DrawUTF(x+12,y,">0.5um");
    percent=w*c2/sum;
    DrawBox(x+13,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+14,y+41+percent,String(c2));

    SetFont(FONT12);
    DrawUTF(x+24,y,">1.0um");
    percent=w*c3/sum;
    DrawBox(x+25,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+26,y+41+percent,String(c3));

    SetFont(FONT12);
    DrawUTF(x+36,y,">2.5um");
    percent=w*c4/sum;
    DrawBox(x+37,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+38,y+41+percent,String(c4));

    SetFont(FONT12);
    DrawUTF(x+48,y,">5.0um");
    percent=w*c5/sum;
    DrawBox(x+49,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+50,y+41+percent,String(c5));

    SetFont(FONT12);
    DrawUTF(x+60,y,">10um");
    percent=w*c6/sum;
    DrawBox(x+61,y+41,percent,10);
    SetFont(FONT8);
    DrawUTF(x+62,y+41+percent,String(c6));
    
    
    }
 void Duck_EPD::DrawCircleChart(int x,int y,int r,int w,int c1,int c2,int c3)
 {
     int sum=c1+c2+c3;
     if(sum==0) sum=1;
        for(int i=0;i<360;i++)
      {
        SetPixel(-round(cos(M_PI*i/180)*r)+x,round(sin(M_PI*i/180)*r)+y);
        
      }
      
      for(int i=0;i<360;i++)
      {
        SetPixel(-round(cos(M_PI*i/180)*(r-w))+x,round(sin(M_PI*i/180)*(r-w))+y);
        
      }
      
      for(int i=0;i<c1*360/sum;i++)
      {
        for(int j=0;j<w;j++)
        { 
        SetPixel(-round(cos(M_PI*i/180)*(r-j))+x,round(sin(M_PI*i/180)*(r-j))+y);
        }
      }
      
      for(int i=(c1+c2)*360/sum-1;i<(c1+c2)*360/sum;i++)
      {
        
        for(int j=0;j<w;j++)
        { 
        SetPixel(-round(cos(M_PI*i/180)*(r-j))+x,round(sin(M_PI*i/180)*(r-j))+y);
        }
      }
      
      for(int i=(c1+c2)*360/sum;i<360;i+=10)
      {
        
        for(int j=0;j<w;j++)
        { 
        SetPixel(-round(cos(M_PI*i/180)*(r-j))+x,round(sin(M_PI*i/180)*(r-j))+y);
        }
      }
      
      y+=2;
      DrawBox(x-r,y+r+2,8,8);
      SetFont(FONT12);
      DrawUTF(x-r-2,y+r+12,"PM1.0");
      SetFont(FONT12);
      DrawUTF(x-r-2,y+r+12+30,String(c1));
      
      
      SetFont(FONT12);
      DrawEmptyBox(x-r+14,y+r+2,8,8);
      DrawUTF(x-r+12,y+r+12,"PM2.5");
      
      SetFont(FONT12);
      DrawUTF(x-r+12,y+r+12+30,String(c2));
      DrawEmptyBox(x-r+28,y+r+2,8,8);
      for(int i=y+r+2;i<y+r+2+8;i+=2)
        {
          DrawYline(x-r+28,x-r+28+7,i);
          }
      SetFont(FONT12);
      DrawUTF(x-r+26,y+r+12,"PM10");
      SetFont(FONT12);
      DrawUTF(x-r+26,y+r+12+30,String(c3));
  
  
  }
int Duck_EPD::getIcon(int weathercodeindex) {
  if(weathercodeindex==0) return 12;
  if(weathercodeindex==1) return 58;
  if(weathercodeindex==2) return 58;
  if(weathercodeindex==3) return 58;
  if(weathercodeindex==4) return 54;
  if(weathercodeindex>=5&&weathercodeindex<=18) return 0;
  if(weathercodeindex>=19&&weathercodeindex<=32) return 19;
  if(weathercodeindex>=33&&weathercodeindex<=36)   return 5;
  if(weathercodeindex>=37&&weathercodeindex<=40)   return 16;
  if(weathercodeindex==41) return 28;
  if(weathercodeindex==42) return 28;
  if(weathercodeindex==43) return 28;
  return 17;
 }
 void Duck_EPD::DrawWeatherChart(int xmin,int xmax,int ymin,int ymax,int point_n,int line_n,String tmax,String tmin,String code_d,String code_n,String text_d,String text_n,String date,String week)//绘制天气温度变化曲线
 {
  if(tmax==",,,,,")
  {
    tmax="5,5,5,5,5,5";
    tmin="2,2,2,2,2,2";
    code_d="0,0,0,0,0,0";
    code_n="0,0,0,0,0,0";
    text_n="晴,晴,晴,晴,晴,晴";
    text_d="晴,晴,晴,晴,晴,晴";
    date="1-1,1-2,1-3,1-4,1-5,1-6";
    week="1,1,1,1,1,1";
    }
  String code_d_a[point_n],code_n_a[point_n],text_d_a[point_n],text_n_a[point_n],date_a[point_n],week_a[point_n];
  int tmax_a[point_n],tmin_a[point_n];
  int min_data=999,max_data=-999;  
  int tmin_x_cord[point_n],tmax_x_cord[point_n];//将数值转成屏幕坐标
  
  String temp_min[point_n];
  String temp_max[point_n];
  int j=0,k=0,l=0;
  //分割tmax和tmin
 // Serial.println(tmax); Serial.println(tmin);
  //Serial.println(code_d);
  for(int i=0;i<tmin.length();i++)
  {
    temp_min[j]+=tmin[i];
   
    if(tmin.charAt(i)==char(',')) j++;
    
    }
  for(int i=0;i<tmax.length();i++)
  {
   
    temp_max[k]+=tmax[i];    
   
    if(tmax.charAt(i)==char(',')) k++;
    } 
  j=0;
  //分割code_d
  for(int i=0;i<code_d.length();i++)
  {
    code_d_a[j]+=code_d[i];    
    if(code_d.charAt(i)==char(',')) j++;
    }
  //分割code_n
  j=0;
  for(int i=0;i<code_n.length();i++)
  {
    code_n_a[j]+=code_n[i];    
    if(code_n.charAt(i)==char(',')) j++;
    }
   //分割text_d
   j=0;
   for(int i=0;i<text_d.length();i++)
  {
    if(text_d.charAt(i)==char(',')) j++;
    else text_d_a[j]+=text_d[i];    
    }
   //分割text_n
   j=0;
   for(int i=0;i<text_n.length();i++)
  {
    if(text_n.charAt(i)==char(',')) j++;
    else text_n_a[j]+=text_n[i];   
    }
  //分割week_n
   j=0;
   for(int i=0;i<week.length();i++)
  {
    if(week.charAt(i)==char(',')) j++;
    else week_a[j]+=week[i];   
    }
  for(int i=0;i<point_n;i++)
  {
  tmax_a[i]=temp_max[i].toInt();//Serial.printf("max:%d\n",tmax_a[i]);
  tmin_a[i]=temp_min[i].toInt();//Serial.printf("min:%d\n",tmin_a[i]);
  }
  //找出计算最大最小值
  for(int i=0;i<point_n;i++)
  {
    if(tmax_a[i]>max_data) max_data=tmax_a[i];
    if(tmax_a[i]<min_data) min_data=tmax_a[i];
    if(tmin_a[i]>max_data) max_data=tmin_a[i];
    if(tmin_a[i]<min_data) min_data=tmin_a[i];
    }
 //转换坐标
  if((max_data-min_data)!=0)
  {
  for(int i=0;i<point_n;i++)
  {
    tmin_x_cord[i]=xmax-((xmax-xmin)*(tmin_a[i]-min_data)/(max_data-min_data));
    tmax_x_cord[i]=xmax-((xmax-xmin)*(tmax_a[i]-min_data)/(max_data-min_data));   
    }
  }
  int dy=(ymax-ymin)/(point_n-1);
  
  /*
  Spline line;
  float x[point_n];float y[point_n];
  for(int i=0;i<point_n;i++)
  {
    y[i]=*data;x[i]=ymin+dy*i;
    data++;
    }
  data=o;
 line.setPoints(x,y,point_n);
 line.setDegree(11);
 for(int i=ymin;i<ymax;i++)
  {
    SetPixel(line.value(i),i);
   
  }
 */
//画折线
  for(int i=0;i<point_n-1;i++)
  {          
      DrawLine(tmin_x_cord[i],ymin+dy*i,tmin_x_cord[i+1],ymin+dy*(i+1));   
      DrawLine(tmax_x_cord[i],ymin+dy*i,tmax_x_cord[i+1],ymin+dy*(i+1));   

     // DrawLine(tmin_x_cord[i]-1,ymin+dy*i,tmin_x_cord[i+1]-1,ymin+dy*(i+1));   
     // DrawLine(tmax_x_cord[i]-1,ymin+dy*i,tmax_x_cord[i+1]-1,ymin+dy*(i+1));   
  }
 //画圆圈，添加标注
 for(int i=0;i<point_n;i++)
  {    
      DrawCircle(tmin_x_cord[i],ymin+dy*i,3,1);
      DrawCircle(tmax_x_cord[i],ymin+dy*i,3,1);
      SetFont(FONT12);fontscale=1;
    
      DrawUTF(tmax_x_cord[i]-14,ymin+dy*i-3*(String(tmax_a[i]).length()+1),String(tmax_a[i])+"°");
      DrawUTF(tmin_x_cord[i]+2,ymin+dy*i-3*(String(tmax_a[i]).length()+1),String(tmin_a[i])+"°");
      
      SetFont(ICON32);DrawUTF(xmin-44,ymin+dy*i-16,String(char(getIcon(code_d_a[i].toInt()))));
      SetFont(FONT12);DrawUTF(xmin-56,ymin+dy*i-2*text_d_a[i].length(),text_d_a[i]);
      DrawUTF(xmin-82,ymin+dy*i-2*week_a[i].length(),week_a[i]);
      
      SetFont(ICON32);DrawUTF(xmax+14,ymin+dy*i-16,String(char(getIcon(code_n_a[i].toInt()))));
      SetFont(FONT12);DrawUTF(xmax+46,ymin+dy*i-2*text_n_a[i].length(),text_n_a[i]);

     
      
      //Serial.print("code_d:");
      //Serial.println(code_d_a[i]);
      //Serial.print("txt_n:");
      //Serial.println(text_n_a[i]);
  } 
   Inverse(xmin-83,xmin-69,0,400);
  }
 void Duck_EPD::DrawXline(int start,int end, int x)
  {
    for(int i=start;i<=end;i++)
    {
      SetPixel(x,i);
      }
  }
void Duck_EPD::DrawYline(int start,int end,  int y)
  {
    for(int i=start;i<=end;i++)
    {
      SetPixel(i,y);
      }
  }
void Duck_EPD::DrawLine(int xstart,int ystart, int xend,int yend)
{
  
  int dx=abs(xend-xstart);int dy=abs(yend-ystart);
  if(dx>=dy)
  {
    if(xend>xstart)
    {
        for(int i=xstart;i<=xend;i++)
      {      
        SetPixel(i,round((i-xstart)*(yend-ystart)/(xend-xstart))+ystart);      
      } 
    }
    else
    {      
        for(int i=xstart;i>=xend;i--)
      {      
        SetPixel(i,round((i-xstart)*(yend-ystart)/(xend-xstart))+ystart);      
      } 
      
      }
  }
  
  else
  {
    if(yend>ystart)
    {
    for(int i=ystart;i<=yend;i++)
    {      
      SetPixel(round((i-ystart)*(xend-xstart)/(yend-ystart))+xstart,i);      
    } 
    }
    else
    {
      for(int i=ystart;i>=yend;i--)
    {      
      SetPixel(round((i-ystart)*(xend-xstart)/(yend-ystart))+xstart,i);      
    } 
      
      }
    } 
  }

void Duck_EPD::Inverse(int xStart,int xEnd,int yStart,int yEnd)
{
  for(int i=0;i<(xEnd-xStart);i++)
  {
    for(int j=0;j<(yEnd-yStart);j++)
    {
      InversePixel(xStart+i,yStart+j);
      }
    
    }
  
  }
void Duck_EPD::DrawUTF(int16_t x,int16_t y,String code)
{
  char buffer[200];
  code.toCharArray(buffer,200);
  DrawUTF(x,y,fontwidth,fontheight,(unsigned char *)buffer);
  }
void Duck_EPD::DrawUTF(int16_t x,int16_t y,byte width,byte height,unsigned char *code)
{
  int charcount;
  charcount=UTFtoUNICODE((unsigned char*)code);
  DrawUnicodeStr(x,y,width,height,charcount,(unsigned char *)UNICODEbuffer);
  
  }
int Duck_EPD::UTFtoUNICODE(unsigned char *code)
{ 
  int i=0;int charcount=0;
  while(code[i]!='\0')
  { 
    //Serial.println("current codei");
      //Serial.println(code[i],HEX);
      //  Serial.println(code[i]&0xf0,HEX);
    if(code[i]<=0x7f)  //ascii
    {
      
      UNICODEbuffer[charcount*2]=0x00;
      UNICODEbuffer[charcount*2+1]=code[i];
        // Serial.println("english or number");
      // Serial.println(UNICODEbuffer[charcount*2],HEX);
       //  Serial.println(UNICODEbuffer[charcount*2+1],HEX);
      i++;charcount++;
   
      }
    else if((code[i]&0xe0)==0xc0)
    {
    
      UNICODEbuffer[charcount*2+1]=(code[i]<<6)+(code[i+1]&0x3f);
      UNICODEbuffer[charcount*2]=(code[i]>>2)&0x07;
      i+=2;charcount++;
     // Serial.println("two bits utf-8");
      }
     else if((code[i]&0xf0)==0xe0)
    {
      
      UNICODEbuffer[charcount*2+1]=(code[i+1]<<6)+(code[i+2]&0x7f);
      UNICODEbuffer[charcount*2]=(code[i]<<4)+((code[i+1]>>2)&0x0f);
      
       //Serial.println("three bits utf-8");
       // Serial.println(UNICODEbuffer[charcount*2],HEX);
        // Serial.println(UNICODEbuffer[charcount*2+1],HEX);
        i+=3;charcount++;
      }
     else
     {
      return 0;}
  }
  UNICODEbuffer[charcount*2]='\0';
  return charcount;
  }
void Duck_EPD::DrawUnicodeChar(int16_t x,int16_t y,byte width,byte height,unsigned char *code)
 { 
 
  int offset;
  int sizeofsinglechar;
  if (height%8==0) sizeofsinglechar=(height/8)*width;
  else sizeofsinglechar=(height/8+1)*width;
 offset=(code[0]*0x100+code[1])*sizeofsinglechar;
  // Serial.println("code[1]");
  // Serial.println(code[1]);
   // Serial.println("sizeofsinglechar");
  // Serial.println(sizeofsinglechar);
  File f=SPIFFS.open(fontname,"r");
  f.seek(offset,SeekSet);
  char zi[sizeofsinglechar];
  f.readBytes(zi,sizeofsinglechar);
 /*for(int i=0;i<32;i++)
  {
     
   Serial.println(zi[i],HEX);
    }*/
  // Serial.println("offset");
   //Serial.println(offset);
   if (offset<0xff*sizeofsinglechar && FontIndex<10) 
   {drawXbm(x,y,width,height,(unsigned char *)zi); }
   else  {drawXbm(x,y,width,height,(unsigned char *)zi);}
  
//SPIFFS.end();
}

void Duck_EPD::DrawUnicodeStr(int16_t x,int16_t y,byte width,byte height,byte strlength,unsigned char *code)
{
  int ymax=yDot;
   if(EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
   {
  ymax=400;
   }
  
  CurrentCursor=0;
   byte sizeofsinglechar;
  if (height%8==0) sizeofsinglechar=(height/8)*width;
  else sizeofsinglechar=(height/8+1)*width;
  int ymove=0;
  int xmove=0;
  strlength*=2;
  int i=0;
  while(i<strlength)
  {
      int offset;
      offset=(code[i]*0x100+code[i+1])*sizeofsinglechar;
      if (offset<0xff*sizeofsinglechar&&fontscale==1) 
      {
      
      DrawUnicodeChar(x+xmove,y+ymove,width,height,(unsigned char *)code+i);
      ymove+=CurrentCursor+1;
      if((y+ymove+width/2)>=ymax-1) {xmove+=height+1;ymove=0;CurrentCursor=0;}
      }
     else if(offset<0xff*sizeofsinglechar&&fontscale==2) 
     {
      DrawUnicodeChar(x+xmove,y+ymove,width,height,(unsigned char *)code+i);
      ymove+=CurrentCursor+2;
      if((y+ymove+width)>=ymax-1) {xmove+=height+1;ymove=0;CurrentCursor=0;}
      }
    else if(fontscale==2)
    {
      DrawUnicodeChar(x+xmove,y+ymove,width,height,(unsigned char *)code+i);
      ymove+=width*2;
      if((y+ymove+width*2)>=ymax-1) {xmove+=height*2+2;ymove=0;CurrentCursor=0;}
      }
    else
    {
      DrawUnicodeChar(x+xmove,y+ymove,width,height,(unsigned char *)code+i);
      ymove+=width;
      if((y+ymove+width)>=ymax-1) {xmove+=height+1;ymove=0;CurrentCursor=0;}
      }
    i++;i++;
    }
  
  }
void Duck_EPD::drawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height,unsigned char *xbm) {
  int16_t heightInXbm = (height + 7) / 8;
  uint8_t Data;
  for(int16_t x = 0; x < width; x++) {
    for(int16_t y = 0; y < height; y++ ) {
      if (y & 7) {
        Data <<= 1; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = xbm[(y / 8) + x * heightInXbm];
      }
      // if there is a bit draw it
      if (((Data & 0x80)>>7)) {
       if(fontscale==1) {SetPixel(xMove + y, yMove + x);CurrentCursor=x;}
       if(fontscale==2) {SetPixel(xMove + y*2, yMove + x*2);SetPixel(xMove + y*2+1, yMove + x*2);SetPixel(xMove + y*2, yMove + x*2+1);SetPixel(xMove + y*2+1, yMove + x*2+1);CurrentCursor=x*2;}
       //if(fontscale==2) {SetPixel(xMove + y*2, yMove + x*2);CurrentCursor=x*2;}
      }
    }
  }
}

void Duck_EPD::DrawXbm_P(int16_t xMove, int16_t yMove, int16_t width, int16_t height,const unsigned char *xbm) {
 int16_t heightInXbm = (height + 7) / 8;
 uint8_t Data;
 //unsigned char temp[heightInXbm*width];
 //memcpy_P(temp, xbm, heightInXbm*width);
  
  for(int16_t x = 0; x < width; x++) {
    for(int16_t y = 0; y < height; y++ ) {
      if (y & 7) {
        Data <<= 1; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = pgm_read_byte(xbm+(y / 8) + x * heightInXbm);
      }
      // if there is a bit draw it
      if (((Data & 0x80)>>7)) {
       if(fontscale==1) {SetPixel(xMove + y, yMove + x);CurrentCursor=x;}
       if(fontscale==2) {SetPixel(xMove + y*2, yMove + x*2);SetPixel(xMove + y*2+1, yMove + x*2);SetPixel(xMove + y*2, yMove + x*2+1);SetPixel(xMove + y*2+1, yMove + x*2+1);}
      }
    }
  }
}
void Duck_EPD::DrawXbm_p_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height,const unsigned char *xbm,byte level)
{
  int16_t heightInXbm = (height+1)/2;
  uint8_t Data;

  
  for(int16_t x = 0; x < width; x++) {
    for(int16_t y = 0; y < height; y++ ) {
      if (y%2!=0) {
        Data <<= 4; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = pgm_read_byte(xbm+(y / 2) + x * heightInXbm);
      }
      // if there is a bit draw it
      if (((Data & 0xf0)>>4==level)) {SetPixel(xMove + y, yMove + x);CurrentCursor=x;}
    }
  }
  
  }
void Duck_EPD::DrawXbm_spiff_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height,byte level)
{
  File f = SPIFFS.open("/pic.xbm", "r"); 
   
  int16_t heightInXbm = (height+1)/2;
  uint8_t Data;

  
  for(int16_t x = 0; x < width; x++) {
    for(int16_t y = 0; y < height; y++ ) {
      if (y%2!=0) {
        Data <<= 4; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = ~f.read();
      }
      // if there is a bit draw it
      if (((Data & 0xf0)>>4==level)) {SetPixel(xMove + y, yMove + x);CurrentCursor=x;}
    }
  }
  f.close();
  }
void Duck_EPD::SetPixel(int16_t x, int16_t y)
{ 
    
    if(EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
   {
    int16_t temp=x;
    x=y;y=yDot-1-temp;
    if(x<xDot&&y<yDot)  EPDbuffer[x/8+y*xDot/8]&=~(0x80>>x%8) ;
   }
   else if(EPD_Type==WF29BZ03)
   {
    
      if(x<(xDot*2)&&y<(yDot*2))  EPDbuffer[x/4+y*xDot/4]&=~(0xc0>>((x%4)*2)) ;
    }
   else
    {
      if(x<xDot&&y<yDot)  EPDbuffer[x/8+y*xDot/8]&=~(0x80>>x%8) ;
      }
   
  }
void Duck_EPD::InversePixel(int16_t x, int16_t y)
{ 
    
    if(EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
   {
    int16_t temp=x;
    x=y;y=yDot-1-temp;
    if(x<xDot&&y<yDot)  EPDbuffer[x/8+y*xDot/8]^=(0x80>>x%8) ;
   }
   else if(EPD_Type==WF29BZ03)
   {
    
      if(x<(xDot*2)&&y<(yDot*2))  EPDbuffer[x/4+y*xDot/4]^=(0xc0>>((x%4)*2)) ;
    }
   else
   {
    if(x<xDot&&y<yDot)  EPDbuffer[x/8+y*xDot/8]^=(0x80>>x%8) ;
    //Serial.printf("(%d,%d)\n",x,y);
   }
  }
void Duck_EPD::clearbuffer()
{
  
  if(EPD_Type==WF29BZ03)
   {
    for(int i=0;i<(xDot*yDot/4);i++) EPDbuffer[i]=0xff;
   }
  else for(int i=0;i<(xDot*yDot/8);i++) EPDbuffer[i]=0xff;
  }
void Duck_EPD::EPD_Set_Model(byte model)
{
  EPD_Type=epd_type(model);
  
  switch (model)
     {
     case 0:
     xDot=128;yDot=296;break;//WX29
     case 1:
     xDot=128;yDot=296;break;//WF29
     case 2:
     xDot=400;yDot=300;break;//OPM4_2
     case 3:
     xDot=648;yDot=480;break;//WF58
     case 4:
     xDot=128;yDot=296;break;//WF29BZ03
     case 5:
     xDot=152;yDot=152;break;//C154
     case 6:
     xDot=400;yDot=300;break;//DKE42_3COLOR
     }
  
  
  }
unsigned char Duck_EPD::ReadBusy(void)
{
  unsigned long i=0;
  for(i=0;i<100;i++){
	//	println("isEPD_BUSY = %d\r\n",isEPD_CS);
if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
{
      if(isEPD_BUSY==EPD_BUSY_LEVEL) {
				//Serial.println("Busy is Low \r\n");
      	return 1;
      }
}
if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03)
  {
if(isEPD_BUSY!=EPD_BUSY_LEVEL) {
				//Serial.println("Busy is H \r\n");
      	return 1;
      }
  }
	  delay(2);
   //Serial.println("epd is Busy");
  }
  return 0;
}
unsigned char Duck_EPD::ReadBusy_long(void)
{
  unsigned long i=0;
  for(i=0;i<2000;i++){
  //  println("isEPD_BUSY = %d\r\n",isEPD_CS);
if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
{
      if(isEPD_BUSY==EPD_BUSY_LEVEL) {
        //Serial.println("Busy is Low \r\n");
        return 1;
      }
}
if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  {
if(isEPD_BUSY!=EPD_BUSY_LEVEL) {
        //Serial.println("Busy is H \r\n");
        return 1;
      }
  }
    delay(2);
   //Serial.println("epd is Busy");
  }
  return 0;
}
void Duck_EPD::EPD_WriteCMD(unsigned char command)
{ 
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  ReadBusy();
  }     
	
	EPD_CS_0;	
	EPD_DC_0;    // command write
	SPI_Write(command);
	EPD_CS_1;
}
void Duck_EPD::EPD_WriteData (unsigned char Data)
{
 
  EPD_CS_0; 
  EPD_DC_1;     
  SPI_Write(Data);  
  EPD_CS_1;
}

void Duck_EPD::EPD_WriteCMD_p1(unsigned char command,unsigned char para)
{
	if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
 {
  ReadBusy();
 }
  EPD_CS_0; 
  EPD_DC_0;    // command write		
	SPI_Write(command);
	EPD_DC_1;		// command write
	SPI_Write(para);
  EPD_CS_1;	
}

void Duck_EPD::deepsleep(void)
{
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
    ReadBusy_long();
	  EPD_WriteCMD_p1(0x10,0x01);
	 // EPD_WriteCMD_p1(0x22,0xc0);//power off
	  EPD_WriteCMD(0x20);
  }
 if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  {
	  ReadBusy_long();
	  EPD_WriteCMD(0x50); 
	  EPD_WriteData (0xf7);//border floating
	  EPD_WriteCMD(0x02);//power off
	  EPD_WriteCMD(0x07);//sleep
	  EPD_WriteData(0xa5);
  }
}


void Duck_EPD::EPD_Write(unsigned char *value, unsigned char Datalen)
{
  
	unsigned char i = 0;
	unsigned char *ptemp;
	ptemp = value;
	if(EPD_Type==WX29)
    { ReadBusy();}
       
	EPD_CS_0;
	EPD_DC_0;		// When DC is 0, write command 
	SPI_Write(*ptemp);	//The first byte is written with the command value
	ptemp++;
	EPD_DC_1;		// When DC is 1, write Data
	for(i= 0;i<Datalen-1;i++){	// sub the Data
		SPI_Write(*ptemp);
		ptemp++;
	}
	EPD_CS_1;
}

void Duck_EPD::EPD_WriteDispRam(unsigned int XSize,unsigned int YSize,unsigned char *Dispbuff,unsigned int offset,byte label)
{
	
	int i = 0,j = 0;
	if(EPD_Type==WF29BZ03)
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;   
  for(i=0;i<(YSize*2);i++){
    for(j=0;j<(XSize*2);j++){
      SPI_Write(*Dispbuff);
      Dispbuff++;
    }  
  } 
    EPD_CS_1; 
    return;
  }
	
  
  if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==C154 )
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;
     for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(0xFF);      
       }
     }    
    EPD_CS_1; 
  }
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  ReadBusy();  
	EPD_DC_0;    //command write
	EPD_CS_0;	
	SPI_Write(0x24);
  }
 
 if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==C154)
  {
  EPD_CS_0;  
  EPD_DC_0;   //command write
  SPI_Write(0x13);
  }
	EPD_DC_1;		//Data write
  //Serial.printf("Xsize=%dYsize=%d\r\n",XSize,YSize);
 
  if(label!=1)
  {
    for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(label);
     
       }
     }    
     
    }
  else
  {
    Dispbuff+=offset;
	for(i=0;i<YSize;i++){
		for(j=0;j<XSize;j++){
			SPI_Write(*Dispbuff);
			Dispbuff++;
		}
   Dispbuff+=xDot/8-XSize;
	}
  }

  
	EPD_CS_1;

}
void Duck_EPD::EPD_WriteDispRam_RED(unsigned int XSize,unsigned int YSize,unsigned char *Dispbuff,unsigned int offset,byte label)
{
  
  int i = 0,j = 0;
  if(EPD_Type==WF29BZ03)
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;   
  for(i=0;i<(YSize*2);i++){
    for(j=0;j<(XSize*2);j++){
      SPI_Write(*Dispbuff);
      Dispbuff++;
    }  
  } 
    EPD_CS_1; 
    return;
  }
  
  
  if(EPD_Type==WF29||EPD_Type==WF58)
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;
     for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(0x00);      
       }
     }    
    EPD_CS_1; 
  }
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  ReadBusy();  
  EPD_DC_0;    //command write
  EPD_CS_0; 
  SPI_Write(0x26);
  }
 
 if(EPD_Type==WF29||EPD_Type==WF58)
  {
  EPD_CS_0;  
  EPD_DC_0;   //command write
  SPI_Write(0x13);
  }
  EPD_DC_1;   //Data write
  //Serial.printf("Xsize=%dYsize=%d\r\n",XSize,YSize);
 
  if(label!=1)
  {
    for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(label);
     
       }
     }    
     
    }
  else
  {
    Dispbuff+=offset;
  for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(~*Dispbuff);
      Dispbuff++;
    }
   Dispbuff+=xDot/8-XSize;
  }
  }

  
  EPD_CS_1;

}
void Duck_EPD::EPD_WriteDispRam_Old(unsigned int XSize,unsigned int YSize,unsigned char *Dispbuff,unsigned int offset,byte label)
{
  
  int i = 0,j = 0;
  if(EPD_Type==WF29BZ03)
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;   
  for(i=0;i<(YSize*2);i++){
    for(j=0;j<(XSize*2);j++){
      SPI_Write(*Dispbuff);
      Dispbuff++;
    }  
  } 
    EPD_CS_1; 
    return;
  }
  
  
  if(EPD_Type==WF29||EPD_Type==WF58)
  {
      EPD_WriteCMD(0x10);
      EPD_CS_0; 
      EPD_DC_1;
     for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(0x00);      
       }
     }    
    EPD_CS_1; 
  }
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  ReadBusy();  
  EPD_DC_0;    //command write
  EPD_CS_0; 
  SPI_Write(0x26);
  }
 
 if(EPD_Type==WF29||EPD_Type==WF58)
  {
  EPD_CS_0;  
  EPD_DC_0;   //command write
  SPI_Write(0x13);
  }
  EPD_DC_1;   //Data write
  //Serial.printf("Xsize=%dYsize=%d\r\n",XSize,YSize);
 
  if(label!=1)
  {
    for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(label);
     
       }
     }    
     
    }
  else
  {
    Dispbuff+=offset;
  for(i=0;i<YSize;i++){
    for(j=0;j<XSize;j++){
      SPI_Write(*Dispbuff);
      Dispbuff++;
    }
   Dispbuff+=xDot/8-XSize;
  }
  }

  
  EPD_CS_1;

}



void Duck_EPD::EPD_SetRamArea(uint16_t Xstart,uint16_t Xend,
						unsigned char Ystart,unsigned char Ystart1,unsigned char Yend,unsigned char Yend1)
{
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  unsigned char RamAreaX[3];	// X start and end
	unsigned char RamAreaY[5]; 	// Y start and end
	RamAreaX[0] = 0x44;	// command
	RamAreaX[1] = Xstart/8;
	RamAreaX[2] = Xend/8;
	RamAreaY[0] = 0x45;	// command
	RamAreaY[1] = Ystart;
	RamAreaY[2] = Ystart1;
	RamAreaY[3] = Yend;
  RamAreaY[4] = Yend1;
	EPD_Write(RamAreaX, sizeof(RamAreaX));
	EPD_Write(RamAreaY, sizeof(RamAreaY));
  //Serial.printf("set ram area%d %d %d %d %d %d %d %d %d\n",RamAreaX[0],RamAreaX[1],RamAreaX[2],RamAreaY[0],RamAreaY[1],RamAreaY[2],RamAreaY[3],RamAreaY[4]);

  }
  if(EPD_Type==WF29||EPD_Type==WF58)
  {
      EPD_WriteCMD(0x91); //enter partial refresh mode
      EPD_WriteCMD(0x90); 
      EPD_WriteData (Xstart);
      EPD_WriteData (Xend);
      EPD_WriteData (Ystart);
      EPD_WriteData (Ystart1);
      EPD_WriteData (Yend);
      EPD_WriteData (Yend1);
      EPD_WriteData (0x0);
  }
}

void Duck_EPD::EPD_SetRamPointer(uint16_t addrX,unsigned char addrY,unsigned char addrY1)
{
  unsigned char RamPointerX[2];  // default (0,0)
  unsigned char RamPointerY[3];
  //Set RAM X address counter
  RamPointerX[0] = 0x4e;
  RamPointerX[1] = addrX;
  //RamPointerX[1] = 0xff;
  //Set RAM Y address counter
  RamPointerY[0] = 0x4f;
  RamPointerY[1] = addrY;
  RamPointerY[2] = addrY1;
  //RamPointerY[1] = 0x2b;
  //RamPointerY[2] = 0x02;
  
  EPD_Write(RamPointerX, sizeof(RamPointerX));
  EPD_Write(RamPointerY, sizeof(RamPointerY));
}


void Duck_EPD::EPD_Init(void)
{
  EPD_RST_0;   
  driver_delay_xms(5);  
  EPD_RST_1;
  //driver_delay_xms(100);
	if(EPD_Type==WX29)
  {
    EPD_Write(GateVol, sizeof(GateVol));
  	EPD_Write(GDOControl, sizeof(GDOControl));	// Pannel configuration, Gate selection
  	EPD_Write(softstart, sizeof(softstart));	// X decrease, Y decrease
  	EPD_Write(VCOMVol, sizeof(VCOMVol));		// VCOM setting
  	EPD_Write(DummyLine, sizeof(DummyLine));	// dummy line per gate
  	EPD_Write(Gatetime, sizeof(Gatetime));		// Gage time setting
  	EPD_Write(RamDataEntryMode, sizeof(RamDataEntryMode));	// X increase, Y decrease
    EPD_WriteCMD_p1(0x22,0xc0);//poweron
    EPD_WriteCMD(0x20); 
  }

  if(EPD_Type==WF29BZ03)
  {
    EPD_WriteCMD(0x01); 
     EPD_WriteData(0x07);      
     EPD_WriteData(0x00);
     EPD_WriteData(0x0B);      
     EPD_WriteData(0x00);
    
     EPD_WriteCMD(0x06);         
     EPD_WriteData(0x07);
     EPD_WriteData(0x07);
     EPD_WriteData(0x07);
    
     EPD_WriteCMD(0x04);         
     ReadBusy();          
    
     EPD_WriteCMD(0X00);
     EPD_WriteData(0xb7);    
    
     EPD_WriteCMD(0X50);
     EPD_WriteData(0x37);
    
        EPD_WriteCMD(0x30);     
        EPD_WriteData(0x39);    
        
        EPD_WriteCMD(0x61);     
        EPD_WriteData(0x80);    
        EPD_WriteData(0x01);    
        EPD_WriteData(0x28);
        
        EPD_WriteCMD(0x82);     
        EPD_WriteData(0x0E);  
    
    }
	if(EPD_Type==WF29)
	{
     
     EPD_WriteCMD(0x01);     
     EPD_WriteData (0x03);
     EPD_WriteData (0x00);
     EPD_WriteData (0x26);//default26 max2b
     EPD_WriteData (0x26);//default26 max2b
     EPD_WriteData (0x03);
     
     EPD_WriteCMD(0x06);
     EPD_WriteData (0x17);
     EPD_WriteData (0x17);
     
     EPD_WriteCMD(0x04);
     //
     
     EPD_WriteCMD(0x00); 
     EPD_WriteData (0xb7);
      
     EPD_WriteCMD(0x30);  //PLL
     EPD_WriteData (0x3a);
     
     EPD_WriteCMD(0x61); //resolution
     EPD_WriteData (0x80);
     EPD_WriteData (0x01);
     EPD_WriteData (0x28);
     
     EPD_WriteCMD(0X82);
     EPD_WriteData (0x20);
     
     EPD_WriteCMD(0X50);
     EPD_WriteData (0x97);
	}
  
  if(EPD_Type==WF58)
  {
    EPD_WriteCMD(0x01); 
    EPD_WriteData (0x37);     //POWER SETTING
    EPD_WriteData (0x00);

    EPD_WriteCMD(0X00);     //PANNEL SETTING
    EPD_WriteData(0xb7);
    //EPD_WriteData(0x08);
    
    EPD_WriteCMD(0x30);     //PLL setting
    EPD_WriteData(0x3a);   //PLL:    0-15¦:0x3C, 15+:0x3A  
    EPD_WriteCMD(0X82);     //VCOM VOLTAGE SETTING
    EPD_WriteData(0x28);    //all temperature  range
    
    EPD_WriteCMD(0x06);         //boost
    EPD_WriteData (0xc7);     
    EPD_WriteData (0xcc);
    EPD_WriteData (0x28);

    EPD_WriteCMD(0X50);     //VCOM AND Data INTERVAL SETTING
    EPD_WriteData(0x77);

    EPD_WriteCMD(0X60);     //TCON SETTING
    EPD_WriteData(0x22);

    EPD_WriteCMD(0X65);     //FLASH CONTROL
    EPD_WriteData(0x00);

    EPD_WriteCMD(0x61);         //tres      
    EPD_WriteData (0x02);   //source 600
    EPD_WriteData (0x88);
    EPD_WriteData (0x01);   //gate 448
    EPD_WriteData (0xe0);

    EPD_WriteCMD(0xe5);     //FLASH MODE        
    EPD_WriteData(0x03);  

    EPD_WriteCMD(0X00);     //PANNEL SETTING
    EPD_WriteData(0x17);
    
    EPD_WriteCMD(0x04);       //POWER ON
    ReadBusy();
  }
  if(EPD_Type==DKE42_3COLOR)
  {
    ReadBusy();   
    EPD_WriteCMD(0x12);     //SWRESET
    ReadBusy();   
  
    EPD_WriteCMD(0x74);
    EPD_WriteData(0x54);
    EPD_WriteCMD(0x7E);
    EPD_WriteData(0x3B);
    EPD_WriteCMD(0x2B);  // Reduce glitch under ACVCOM  
    EPD_WriteData(0x04);           
    EPD_WriteData(0x63);

    EPD_WriteCMD(0x0C);  // Soft start setting
    EPD_WriteData(0x8B);           
    EPD_WriteData(0x9C);
    EPD_WriteData(0x96);
    EPD_WriteData(0x0F);

    EPD_WriteCMD(0x01);  // Set MUX as 300
    EPD_WriteData(0x2B);           
    EPD_WriteData(0x01);
    EPD_WriteData(0x00);     

    EPD_WriteCMD(0x11);  // Data entry mode
    EPD_WriteData(0x01);         
    EPD_WriteCMD(0x44); 
    EPD_WriteData(0x00); // RAM x address start at 0
    EPD_WriteData(0x31); // RAM x address end at 31h(49+1)*8->400
    EPD_WriteCMD(0x45); 
    EPD_WriteData(0x2B);   // RAM y address start at 12Bh     
    EPD_WriteData(0x01);
    EPD_WriteData(0x00); // RAM y address end at 00h     
    EPD_WriteData(0x00);
    EPD_WriteCMD(0x3C); // board
    EPD_WriteData(0x01); // HIZ

    EPD_WriteCMD(0x18);
    EPD_WriteData(0X80);
    EPD_WriteCMD(0x22);
    EPD_WriteData(0XB1);  //Load Temperature and waveform setting.
    EPD_WriteCMD(0x20);
    ReadBusy();   
    

    EPD_WriteCMD(0x4E); 
    EPD_WriteData(0x00);
    EPD_WriteCMD(0x4F); 
    EPD_WriteData(0x2B);
    EPD_WriteData(0x01);
    
    }
  if(EPD_Type==OPM42)
  {
EPD_WriteCMD_p1(0x22,0xc0);//poweron
    EPD_WriteCMD(0x74);       // 
    EPD_WriteData(0x54);    // 
    EPD_WriteCMD(0x7E);       // 
    EPD_WriteData(0x3B);    // 
    EPD_WriteCMD(0x01);       // 
    EPD_WriteData(0x2B);    // 
    EPD_WriteData(0x01);
    EPD_WriteData(0x00);    // 

    EPD_WriteCMD(0x0C);       // 
    EPD_WriteData(0x8B);    // 
    EPD_WriteData(0x9C);    // 
    EPD_WriteData(0xD6);    //     
    EPD_WriteData(0x0F);    // 

    EPD_WriteCMD(0x3A);       // 
    EPD_WriteData(0x21);    // 
    EPD_WriteCMD(0x3B);       // 
    EPD_WriteData(0x06);    // 
    EPD_WriteCMD(0x3C);       // 
    EPD_WriteData(0x03);    // 

    EPD_WriteCMD(0x11);       // data enter mode
    EPD_WriteData(0x01);    // 01 –Y decrement, X increment,

    EPD_WriteCMD(0x2C);       // 
    EPD_WriteData(0x15);    //fff


    EPD_WriteCMD(0x37);       // 
    EPD_WriteData(0x00);    // 
    EPD_WriteData(0x00);    // 
    EPD_WriteData(0x00);    // 
    EPD_WriteData(0x00);    // 
    EPD_WriteData(0x80);    // 
  
    EPD_WriteCMD(0x21);       // 
    EPD_WriteData(0x40);    // 
    EPD_WriteCMD(0x22);
    EPD_WriteData(0xc7);    //c5forgraymode// 
  }
  if(EPD_Type==C154)
  {
  EPD_WriteCMD(0x01);
  EPD_WriteData(0x03);
  EPD_WriteData(0x00);
  EPD_WriteData(0x2b);
  EPD_WriteData(0x26);
  EPD_WriteData(0x03);
  
  EPD_WriteCMD(0x06); //boost soft start
  EPD_WriteData(0x17);
  EPD_WriteData(0x17);
  EPD_WriteData(0x17);
  EPD_WriteCMD(0x04);

  ReadBusy();

  EPD_WriteCMD(0x00); //panel setting
  EPD_WriteData(0xff); //LUT from OTP，160x296
  EPD_WriteData(0x0d); //VCOM to 0V fast

  EPD_WriteCMD(0x61); //resolution setting
  EPD_WriteData(0x98); //152
  EPD_WriteData(0x00); //152
  EPD_WriteData(0x98);

  EPD_WriteCMD(0X30);
  EPD_WriteData(0x29);

  EPD_WriteCMD(0X50); //VCOM AND DATA INTERVAL SETTING     
  EPD_WriteData(0x97); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
  ReadBusy();  
    }
}
void Duck_EPD::EPD_Set_Contrast(byte vcom)
{   if(EPD_Type==OPM42)
  {
    EPD_WriteCMD(0x2C);       // 
    EPD_WriteData(vcom);    //fff
  }
  }

void Duck_EPD::EPD_Update(void)
{
   if(EPD_Type==OPM42)
   {
    EPD_WriteCMD(0x20);
   }
   if(EPD_Type==DKE42_3COLOR)
   {
    EPD_WriteCMD(0x22); //Display Update Control
    EPD_WriteData(0xC7);   
    EPD_WriteCMD(0x20);  //Activate Display Update Sequence
    }
  	if(EPD_Type==WX29)
    {
  	EPD_WriteCMD_p1(0x22,0x04);
  	EPD_WriteCMD(0x20);
    }
    if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  	{
  	EPD_WriteCMD(0x12);
  	}
}
void Duck_EPD::EPD_Update_Part(void)
{
  if(EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
   {
  EPD_WriteCMD(0x20);
   }
 if(EPD_Type==WX29)
  {
	EPD_WriteCMD_p1(0x22,0x04);
	EPD_WriteCMD(0x20);
  }
 if(EPD_Type==WF29)
 {
  EPD_WriteCMD(0x12);
  EPD_WriteCMD(0x92);  
 }
}

void Duck_EPD::EPD_init_Full(void)
{	
  EPD_Init();

	if(EPD_Type==WX29)
   {	
	EPD_Write((unsigned char *)LUTDefault_full,sizeof(LUTDefault_full));
   }
	if(EPD_Type==OPM42)
 {
  EPD_Write((unsigned char *)LUTDefault_full_opm42,sizeof(LUTDefault_full_opm42));
  }
	if(EPD_Type==WF29BZ03)
  {
  EPD_Write((unsigned char *)lut_vcomDC2,sizeof(lut_vcomDC2));
  EPD_Write((unsigned char *)lut_ww2,sizeof(lut_ww2));
  EPD_Write((unsigned char *)lut_bw2,sizeof(lut_bw2));
  EPD_Write((unsigned char *)lut_wb2,sizeof(lut_wb2));
  EPD_Write((unsigned char *)lut_bb2,sizeof(lut_bb2));
    
    }
	
	if(EPD_Type==WF29)
  {	
  EPD_Write((unsigned char *)lut_vcomDC,sizeof(lut_vcomDC));
  EPD_Write((unsigned char *)lut_ww,sizeof(lut_ww));
  EPD_Write((unsigned char *)lut_bw,sizeof(lut_bw));
  EPD_Write((unsigned char *)lut_wb,sizeof(lut_wb));
  EPD_Write((unsigned char *)lut_bb,sizeof(lut_bb));
  }
  if(EPD_Type==C154)
  {
  EPD_Write((unsigned char *)lut_vcomDC_154,sizeof(lut_vcomDC_154));
  EPD_Write((unsigned char *)lut_ww_154,sizeof(lut_ww_154));
  EPD_Write((unsigned char *)lut_bw_154,sizeof(lut_bw_154));
  EPD_Write((unsigned char *)lut_wb_154,sizeof(lut_wb_154));
  EPD_Write((unsigned char *)lut_bb_154,sizeof(lut_bb_154));
    
    }
}


void Duck_EPD::EPD_init_Part(void)
{	
  
  if(EPD_Type==WX29)
   {
	EPD_Init();			// display
	EPD_Write((unsigned char *)LUTDefault_part,sizeof(LUTDefault_part));
	EPD_WriteCMD_p1(0x22,0xc0);//poweron

 	 EPD_WriteCMD(0x20);   		
   }
if(EPD_Type==OPM42)
 {
//EPD_WriteCMD_p1(0x22,0xc0);//poweron
  EPD_Init();
  EPD_WriteCMD(0x21); 
  EPD_WriteData(0x00);
  EPD_Write((unsigned char *)LUTDefault_part_opm42,sizeof(LUTDefault_part_opm42));
//EPD_WriteCMD_p1(0x22,0xc0);//poweron
  }
	if(EPD_Type==WF29)
  {  
	  EPD_Init();
	  EPD_WriteCMD(0x50); 
    EPD_WriteData(0xb7);
    EPD_Write((unsigned char *)lut_vcomDC1,sizeof(lut_vcomDC1));
    EPD_Write((unsigned char *)lut_ww1,sizeof(lut_ww1));
    EPD_Write((unsigned char *)lut_bw1,sizeof(lut_bw1));
    EPD_Write((unsigned char *)lut_wb1,sizeof(lut_wb1));
    EPD_Write((unsigned char *)lut_bb1,sizeof(lut_bb1));
  }
}
void Duck_EPD::EPD_Transfer_Full_BW(unsigned char *DisBuffer,unsigned char Label)
{
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
    {
  unsigned int yStart=0;
  unsigned int yEnd=yDot-1;
  unsigned int xStart=0;
  unsigned int xEnd=xDot-1;
  unsigned long temp=yStart;
 
  yStart=yDot-1-yEnd;yEnd=yDot-1-temp;
  EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
 
  if(Label == 2){
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer, 0,0x00); // white  
  }
  else if(Label==3)
  {
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,0xff);  // black
    }
  else{
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); 
  } 
  //EPD_Update();
  //ReadBusy_long();
  //EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); 
    }
  
  if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  {
  if(Label == 2){
    EPD_WriteDispRam(xDot/8, yDot,(unsigned char *)DisBuffer,0, 0xff); // white  
  }
  else if(Label==3)
  {
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,0x00);  // black
    }else{
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); // white
  } 
  //EPD_Update(); 
  }
    
}
void Duck_EPD::EPD_Transfer_Full_RED(unsigned char *DisBuffer,unsigned char Label)
{
  if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
    {
  unsigned int yStart=0;
  unsigned int yEnd=yDot-1;
  unsigned int xStart=0;
  unsigned int xEnd=xDot-1;
  unsigned long temp=yStart;
 
  yStart=yDot-1-yEnd;yEnd=yDot-1-temp;
  EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
 
  if(Label == 2){
    EPD_WriteDispRam_RED(xDot/8, yDot, (unsigned char *)DisBuffer, 0,0x00); // white  
  }
  else if(Label==3)
  {
    EPD_WriteDispRam_RED(xDot/8, yDot, (unsigned char *)DisBuffer,0,0xff);  // black
    }
  else{
    EPD_WriteDispRam_RED(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); 
  } 
  //EPD_Update();
  //ReadBusy_long();
  //EPD_WriteDispRam_Old(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); 
    }
  
  if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  {
  if(Label == 2){
    EPD_WriteDispRam_RED(xDot/8, yDot,(unsigned char *)DisBuffer,0, 0xff); // white  
  }
  else if(Label==3)
  {
    EPD_WriteDispRam_RED(xDot/8, yDot, (unsigned char *)DisBuffer,0,0x00);  // black
    }else{
    EPD_WriteDispRam_RED(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); // white
  } 
  //EPD_Update(); 
  }
    
}
void Duck_EPD::EPD_Dis_Full(unsigned char *DisBuffer,unsigned char Label)
{
	if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
    {
  unsigned int yStart=0;
  unsigned int yEnd=yDot-1;
  unsigned int xStart=0;
  unsigned int xEnd=xDot-1;
  unsigned long temp=yStart;
 
  yStart=yDot-1-yEnd;yEnd=yDot-1-temp;
  EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
 
	if(Label == 2){
		EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer, 0,0x00);	// white	
	}
	else if(Label==3)
	{
	  EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,0xff);  // black
	  }
	else{
		EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1);	
	}	
	EPD_Update();
  ReadBusy_long();
  EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1); 
    }
	
	if(EPD_Type==WF29||EPD_Type==WF58||EPD_Type==WF29BZ03||EPD_Type==C154)
  {
	if(Label == 2){
    EPD_WriteDispRam(xDot/8, yDot,(unsigned char *)DisBuffer,0, 0xff); // white  
  }
  else if(Label==3)
  {
    EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,0x00);  // black
    }else{
		EPD_WriteDispRam(xDot/8, yDot, (unsigned char *)DisBuffer,0,1);	// white
	}	
	EPD_Update();	
  }
	  
}


void Duck_EPD::EPD_Dis_Part(int xStart,int xEnd,int yStart,int yEnd,unsigned char *DisBuffer,unsigned char Label)
{
  if(EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
  {
  int temp1=xStart,temp2=xEnd;
  xStart=yStart;xEnd=yEnd;
  yEnd=yDot-temp1-2;yStart=yDot-temp2-3;
    }
   unsigned int Xsize=xEnd-xStart;
      unsigned int Ysize=yEnd-yStart+1;
     if(Xsize%8!= 0){
      Xsize = Xsize+(8-Xsize%8);
      }
      Xsize = Xsize/8;
  unsigned int offset=yStart*xDot/8+xStart/8; 
	if(EPD_Type==WX29||EPD_Type==OPM42||EPD_Type==DKE42_3COLOR)
 {
  
  unsigned long temp=yStart;
  yStart=yDot-1-yEnd;yEnd=yDot-1-temp;
  
  EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
  EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
	if(Label==2)  EPD_WriteDispRam(xEnd-xStart, yEnd-yStart+1,(unsigned char *)DisBuffer,offset,0x00);
  else if(Label==3) EPD_WriteDispRam(xEnd-xStart, yEnd-yStart+1,(unsigned char *)DisBuffer,offset,0xff);
  else  EPD_WriteDispRam(Xsize, Ysize,(unsigned char *)DisBuffer,offset,1);  
  EPD_Update_Part();
  ReadBusy();
  EPD_WriteDispRam_Old(Xsize, Ysize,(unsigned char *)DisBuffer,offset,1);  
  //ReadBusy();
  //EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
  //EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  //EPD_WriteDispRam(Xsize, Ysize,(unsigned char *)DisBuffer,offset,1);  
 }
	
	if(EPD_Type==WF29||EPD_Type==WF58)
  { 
  
	EPD_SetRamArea(xStart,xEnd,yStart/256,yStart%256,yEnd/256,yEnd%256);
  if(Label==2)  EPD_WriteDispRam(xEnd-xStart, yEnd-yStart+1,(unsigned char *)DisBuffer,offset,0xff);
  else if(Label==3) EPD_WriteDispRam(xEnd-xStart, yEnd-yStart+1,(unsigned char *)DisBuffer,offset,0x00);
  else  EPD_WriteDispRam(Xsize, Ysize,(unsigned char *)DisBuffer,offset,1);  
  EPD_Update_Part();
  }
}
