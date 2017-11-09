

/**
    @filename   :   epd2in9-demo.ino
    @brief      :   2.9inch e-paper display demo
    @author     :   Yehui from Waveshare

    Copyright (C) Waveshare     September 9 2017

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documnetation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to  whom the Software is
   furished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/
#include <LowPower.h>
#include <SPI.h>
#include <epd2in9.h>
#include <epdpaint.h>
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1

/**
    Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    In this case, a smaller image buffer is allocated and you have to
    update a partial display several times.
    1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
*/
unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (epd.Init(lut_full_update) != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  if (epd.Init(lut_partial_update) != 0) {
    Serial.print("e-Paper init failed");
    return;
  }
  /**
      there are 2 memory areas embedded in the e-paper display
      and once the display is refreshed, the memory area will be auto-toggled,
      i.e. the next action of SetFrameMemory will set the other memory area
      therefore you have to clear the frame memory twice.
  */
  epd.ClearFrameMemory(0xff);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xff);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_0);
  paint.SetWidth(128);
  paint.SetHeight(24);
  paint.Clear(UNCOLORED);

  // delay(1000);
  //

}


/**
    there are 2 memory areas embedded in the e-paper display
    and once the display is refreshed, the memory area will be auto-toggled,
    i.e. the next action of SetFrameMemory will set the other memory area
    therefore you have to set the frame memory and refresh the display twice.
*/
void limpiar() {
  paint.Clear(UNCOLORED);
  epd.ClearFrameMemory(0x00);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xff);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.WaitUntilIdle();
}

void loop() {

  limpiar();
  
  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

  limpiar();

  epd.SetFrameMemory(IMAGE_DATA2);
  epd.DisplayFrame();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

  limpiar();

  epd.SetFrameMemory(IMAGE_DATA4);
  epd.DisplayFrame();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

  limpiar();

  epd.SetFrameMemory(IMAGE_DATA5);
  epd.DisplayFrame();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);



}

