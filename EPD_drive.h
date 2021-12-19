//#define WF 1 //使用从威锋墨水屏排线上有WFT029
//#define WX 1 //使用从微雪购买的墨水屏hink
//#define WF5X83 1 //5.83寸
//#define OPM42 1 //奥翼4.2寸opm042
#pragma once
extern unsigned char UNICODEbuffer[200];
extern String fontname;
#ifndef _EPD_DRIVE_H_
#define _EPD_DRIVE_H_
//#include "spline.h"


static const unsigned char GDVol[] = {0x03, 0x00}; // Gate voltage +15V/-15V
static  unsigned char GDOControl[] = {0x01, 39, 1, 0x00}; //for 1.54inch
static  unsigned char softstart[] = {0x0c, 0xd7, 0xd6, 0x9d};
static  unsigned char Rambypass[] = {0x21, 0x8f};  // Display update
static unsigned char MAsequency[] = {0x22, 0xf0};   // clock
static  unsigned char SDVol[] = {0x04, 0x0a}; // Source voltage +15V/-15V
static  unsigned char VCOMVol[] = {0x2c, 0xa8}; // VCOM 7c 0xa8
static unsigned char GateVol[] = {0x03, 0xea};

static  unsigned char BOOSTERFB[] = {0xf0, 0x1f}; // Source voltage +15V/-15V
static  unsigned char DummyLine[] = {0x3a, 0x01}; // 4 dummy line per gate
static  unsigned char Gatetime[] = {0x3b, B1000}; // 2us per line
static  unsigned char BorderWavefrom[] = {0x3c, 0x63}; // Border
static  unsigned char RamDataEntryMode[] = {0x11, 0x01}; // Ram data entry mode
static const unsigned char LUTDefault_part[31] = {
  0x32, // command
  0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x14, 0x44, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 10 wb  01 bw
     10 H REPEAT 3
     10 H 01 L REPEAT 1
     10 H 01 L REPEAT 4
     01 L REPEAT 1
     10 H 01 L REPEAT 4
     10 H 01 L REPEAT 4
     01 L REPEAT 2


  */
};
static const unsigned char LUTDefault_full[31] = {
  0x32, // command
  0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00,
  0x00, 0xF8, 0xB4, 0x13, 0x51, 0x35, 0x51, 0x51, 0x19, 0x01, 0x00,
};

const unsigned char lut_vcomDC_154[] = {
  0x20,
  0x00  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x60  , 0x13 , 0x14 , 0x00 , 0x00 , 0x05,
  0x00  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0x00  , 0x24 , 0x24 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00
  , 0x00 , 0x00,
};
const unsigned char lut_ww_154[] = {
  0x21,
  //
  0x40  , 0x16 , 0x00 , 0x00 , 0x00 , 0x01,
  0x90  , 0x13 , 0x14 , 0x00 , 0x00 , 0x05,
  0x40  , 0x02 , 0x00 , 0x00 , 0x00 , 0x01,
  0xA0  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_wb_154[] = {
  0x23,
  0x80  , 0x02 , 0x00 , 0x00 , 0x00 , 0x01,
  0x90  , 0x13 , 0x14 , 0x00 , 0x00 , 0x05,
  0x80  , 0x02 , 0x00 , 0x00 , 0x00 , 0x01,
  0x50  , 0x24 , 0x24 , 0x00 , 0x00 , 0x05,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};

const unsigned char lut_bw_154[] = {
  0x22,
  0x40  , 0x17 , 0x00 , 0x00 , 0x00 , 0x02 ,
  0x90  , 0x0F , 0x0F , 0x00 , 0x00 , 0x03 ,
  0x40  , 0x0A , 0x01 , 0x00 , 0x00 , 0x01 ,
  0xA0  , 0x0E , 0x0E , 0x00 , 0x00 , 0x02 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
};

const unsigned char lut_bb_154[] = {
  0x24,
  0x80  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x90  , 0x28 , 0x28 , 0x00 , 0x00 , 0x01,
  0x80  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0x50  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};


static const unsigned char LUTDefault_part_opm42[] = {
  /*
    0x08,0x48,0x40,0x00,0x00,0x00,0x00,//L0 B low-high-low-high
    0x20,0x12,0x00,0x00,0x00,0x00,0x00,//L1 W low-high-low
    0x48,0x48,0x40,0x00,0x00,0x00,0x00,
    0x48,0x48,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,//L4 VCOM
    0x0c,0x08,0x0c,0x01,0x00,
    0x0c,0x10,0x0c,0x08,0x00,
    0x0c,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
  */
  0x32, // command
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L0 BB R0 B/W 0
  0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L1 BW R0 B/W 1
  0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L2 WB R1 B/W 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L3 WW R0 W/W 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L4 VCOM
  //b1w1 b2          w2
  0x08, 0x08, 0x00, 0x08, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,


};
static const unsigned char LUTDefault_full_opm42[] = {
  0x32, // command
  /*
    0x08,0x48,0x40,0x00,0x00,0x00,0x00,//L0 B low-high-low-high
    0x08,0x48,0x00,0x00,0x00,0x00,0x00,//L1 W low-high-low
    0x48,0x48,0x40,0x00,0x00,0x00,0x00,
    0x48,0x48,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,//L4 VCOM
    0x0F,0x01,0x0F,0x01,0x00,
    0x0F,0x01,0x0F,0x01,0x00,
    0x0F,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,
  */
  /*
    black
    0x08 vsl repeat f
    0x48 vsh1 repeat f vsl repeat f
    0x40 vshl repeat f

    white
    0x08 vsl repeat f
    0x48 vsh1 repeat f vsl repeat f
  */


  0x08, 0x00, 0x48, 0x40, 0x00, 0x00, 0x00, //L0 B low-high-low-high
  0x20, 0x00, 0x12, 0x20, 0x00, 0x00, 0x00, //L1 W low-high-low
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L4 VCOM
  //    w1白 b1白
  0x05, 0x20, 0x20, 0x05, 0x00,
  //wait
  0x0f, 0x00, 0x00, 0x00, 0x00,
  //b2黑 w2黑 b3白 w3白
  0x20, 0x40, 0x20, 0x20, 0x00,
  //b4黑 w4白
  0x20, 0x05, 0x00, 0x00, 0x00,
  //

  0x05, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char LUT_gray_opm42[] = {
  0x32, // command
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L0 B low-high-low-high 40
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L1 W low-high
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L2 R
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L3 R
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L4 VCOM
  0x03, 0x00, 0x00, 0x00, 0x00, //[36]
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char LUT_gray_red_opm42[] = {
  0x32, // command
  0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, //L0 B low-high-low-high 40
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L1 W low-high
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L2 R
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L3 R
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //L4 VCOM
  0x20, 0x01, 0x00, 0x00, 0x00, //[36]
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_vcomDC[] = {
  0x20,
  0x00  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x60  , 0x28 , 0x28 , 0x00 , 0x00 , 0x01,
  0x00  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0x00  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00
  , 0x00 , 0x00,
};
const unsigned char lut_ww[] = {
  0x21,
  0x40  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x90  , 0x28 , 0x28 , 0x00 , 0x00 , 0x01,
  0x40  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0xA0  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_bw[] = {
  0x22,
  0x40  , 0x17 , 0x00 , 0x00 , 0x00 , 0x02 ,
  0x90  , 0x0F , 0x0F , 0x00 , 0x00 , 0x03 ,
  0x40  , 0x0A , 0x01 , 0x00 , 0x00 , 0x01 ,
  0xA0  , 0x0E , 0x0E , 0x00 , 0x00 , 0x02 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
};
const unsigned char lut_wb[] = {
  0x23,
  0x80  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x90  , 0x28 , 0x28 , 0x00 , 0x00 , 0x01,
  0x80  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0x50  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_bb[] = {
  0x24,
  0x80  , 0x08 , 0x00 , 0x00 , 0x00 , 0x02,
  0x90  , 0x28 , 0x28 , 0x00 , 0x00 , 0x01,
  0x80  , 0x14 , 0x00 , 0x00 , 0x00 , 0x01,
  0x50  , 0x12 , 0x12 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};

//////////////////////////////////////partial screen update LUT////////////////////////////////////////////
const unsigned char lut_vcomDC1[] = {
  0x20,
  0x00  , 0x19 , 0x01 , 0x00 , 0x00 , 0x01, //GND
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00
  , 0x00 , 0x00,
};
const unsigned char lut_ww1[] = {
  0x21,
  //level0 level 1 level 2 level 3
  //frame0
  //frame1
  //frame2
  //frame3
  //repeat
  //level f0    f1   f2    f3    repeat
  0x00  , 0x19 , 0x01 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_bw1[] = {
  0x22,
  //level f0    f1   f2    f3    repeat
  0x80  , 0x19 , 0x01 , 0x00 , 0x00 , 0x01, //LOW - GND
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_wb1[] = {
  0x23,
  0x40  , 0x19 , 0x01 , 0x00 , 0x00 , 0x01, //HIGH - GND
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};
const unsigned char lut_bb1[] = {
  0x24,
  0x00  , 0x19 , 0x01 , 0x00 , 0x00 , 0x01,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
  0x00  , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
};

const unsigned char lut_vcomDCfast[] = {
  0x20,
  0x01 , 0x01 , 0x02 ,
  0x01 , 0x01 , 0x02 ,
  0x41 , 0x41 , 0x02 ,
  0x41 , 0x41 , 0x02 ,
  0x02 , 0x02 , 0x19
};
const unsigned char lut_wwfast[] = { //w
  0x21,

  0x81 , 0x81 , 0x02,
  0x81 , 0x81 , 0x02,
  0x81 , 0x81 , 0x02,
  0x81 , 0x81 , 0x02,
  0x82 , 0xc2 , 0x0f,
};
const unsigned char lut_bwfast[] = { //b
  0x22,

  0x41 , 0x41 , 0x06 ,
  0x41 , 0x41 , 0x02 ,
  0x41 , 0x41 , 0x02 ,
  0x41 , 0x41 , 0x02 ,
  0x42 , 0xc2 , 0x02 ,
};

const unsigned char lut_vcomDC2[] = {
  0x20,
  0x0E  , 0x14 , 0x01 , 0x0A , 0x06 , 0x04 , 0x0A , 0x0A , 0x0F , 0x03 , 0x03 , 0x0C , 0x06 , 0x0A , 0x00
};
const unsigned char lut_ww2[] = { //w
  0x21,
  0x0E  , 0x14 , 0x01 , 0x0A , 0x46 , 0x04 , 0x8A , 0x4A , 0x0F , 0x83 , 0x43 , 0x0C , 0x86 , 0x0A , 0x04
};
const unsigned char lut_bw2[] = { //b
  0x22,
  0x0E  , 0x14 , 0x01 , 0x8A , 0x06 , 0x04 , 0x8A , 0x4A , 0x0F , 0x83 , 0x43 , 0x0C , 0x06 , 0x4A , 0x04
};
const unsigned char lut_wb2[] = {
  0x23,
  0x8E  , 0x94 , 0x01 , 0x8A , 0x06 , 0x04 , 0x8A , 0x4A , 0x0F , 0x83 , 0x43 , 0x0C , 0x06 , 0x0A , 0x04
};
const unsigned char lut_bb2[] = {
  0x24,
  0x8E  , 0x94 , 0x01 , 0x8A , 0x06 , 0x04 , 0x8A , 0x4A , 0x0F , 0x83 , 0x43 , 0x0C , 0x06 , 0x0A , 0x04
};
enum FONT {
  FONT16 = 0,
  FONT32 = 1,
  FONT10 = 2,
  FONT12 = 3,
  FONT70 = 5,
  FONT12_NUM = 6,
  FONT24 = 7,
  FONT8 = 8,
  DIGI_NUM_100 = 9,
  ICON32 = 13,
  ICON80 = 12,
  ICON50 = 14,
};
enum epd_type {
  WX29 = 0,
  WF29 = 1,
  OPM42 = 2,
  WF58 = 3,
  WF29BZ03 = 4,
  C154 = 5,
  DKE42_3COLOR,
};
/*
   典型使用流程
   1.EPD_init_Full/EPD_init_Part初始化
   2.clearbuffer清除缓存图像
   3.SetFont设置字体
   4.fontscale=1设置字体缩放
   5.DrawUTF 绘制文字。图像等
   6.EPD_DisFull/EPD_Dis_Part更新屏幕图像
   7.deepsleep睡眠

   屏幕有圆点的角为（0，0）点，x方向为垂直方向，y方向为水平方向
*/
class Duck_EPD {
  public:
    Duck_EPD();
    void deepsleep(void);

    byte fontscale;///> 字体缩放，仅支持1，2

    unsigned char EPDbuffer[400 * 300 / 8]; ///>屏幕图像
    epd_type EPD_Type;

    void EPD_Set_Model(byte model);
    void EPD_init_Full(void);
    void EPD_init_Part(void);
    void EPD_Dis_Full(unsigned char *DisBuffer, unsigned char Label); //1正常2全白3全黑
    void EPD_Dis_Part(int xStart, int xEnd, int yStart, int yEnd, unsigned char *DisBuffer, unsigned char Label);
    void EPD_Transfer_Full_BW(unsigned char *DisBuffer, unsigned char Label);
    void EPD_Transfer_Full_RED(unsigned char *DisBuffer, unsigned char Label);

    void SetFont(FONT fontindex);
    void DrawUTF(int16_t x, int16_t y, String code);
    void clearbuffer();

    void DrawYline(int start, int end, int y); //画竖线
    void DrawXline(int start, int end, int x); //画横线
    void DrawLine(int xstart, int ystart, int xend, int yend);
    void Inverse(int xStart, int xEnd, int yStart, int yEnd);

    void DrawWeatherChart(int xmin, int xmax, int ymin, int ymax, int point_n, int line_n, String tmax, String tmin, String code_d, String code_n, String text_d, String text_n, String date, String week); //绘制天气温度变化曲线
    void DrawCircle(int x, int y, int r, bool fill); //画圆圈，xy圆心，r半径
    void DrawBox(byte x, int y, int w, int h); //画矩形，填充
    void DrawEmptyBox(int x, int y, int w, int h); //画矩形，空心
    void DrawChart(int x, int y, int w, int c1, int c2, int c3, int c4, int c5, int c6); //画水平方向的柱状图，w图表宽度，c1-C6变量
    void DrawCircleChart(int x, int y, int r, int w, int c1, int c2, int c3); //画圆环图表，r半径，w圆环宽，c1-c3变量


    void DrawUnicodeChar(int16_t x, int16_t y, byte width, byte height, unsigned char *code);
    void DrawUnicodeStr(int16_t x, int16_t y, byte width, byte height, byte strlength, unsigned char *code);
    void drawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, unsigned char *xbm); //绘制图像
    void DrawXbm_P(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const unsigned char *xbm);
    void DrawXbm_p_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const unsigned char *xbm, byte level);
    void DrawXbm_spiff_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, byte level);

    void EPD_Write(unsigned char *value, unsigned char datalen);
    void EPD_WriteCMD(unsigned char command);
    void EPD_WriteData (unsigned char data);
    void EPD_WriteCMD_p1(unsigned char command, unsigned char para);
    unsigned char ReadBusy(void);
    unsigned char ReadBusy_long(void);
    void EPD_Set_Contrast(byte vcom);

    void EPD_Update(void);
  private:
    byte FontIndex;

    int xDot;
    int yDot;
    int16_t CurrentCursor;
    byte fontwidth;
    byte fontheight;


    void EPD_WriteDispRam_Old(unsigned int XSize, unsigned int YSize, unsigned char *Dispbuff, unsigned int offset, byte label);
    void EPD_WriteDispRam_RED(unsigned int XSize, unsigned int YSize, unsigned char *Dispbuff, unsigned int offset, byte label);
    void EPD_WriteDispRam(unsigned int XSize, unsigned int YSize, unsigned char *Dispbuff, unsigned int offset, byte label);
    void EPD_SetRamArea(uint16_t Xstart, uint16_t Xend, unsigned char Ystart, unsigned char Ystart1, unsigned char Yend, unsigned char Yend1);
    void EPD_SetRamPointer(uint16_t addrX, unsigned char addrY, unsigned char addrY1);
    void EPD_WirteLUT(unsigned char *LUTvalue, unsigned char Size);


    void EPD_Init(void);
    void EPD_Update_Part(void);


    int getIcon(int weathercodeindex);
    void SetPixel(int16_t x, int16_t y);
    void InversePixel(int16_t x, int16_t y);
    void DrawUTF(int16_t x, int16_t y, byte width, byte height, unsigned char *code);
    int UTFtoUNICODE(unsigned char *code);



};

#endif
