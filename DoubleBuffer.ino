/*
  Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com) - www.fabgl.com
  Copyright (c) 2019-2020 Fabrizio Di Vittorio.
  All rights reserved.

  This file is part of FabGL Library.

  FabGL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FabGL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FabGL.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "fabgl.h"



fabgl::VGAController DisplayController;
fabgl::Canvas        canvas(&DisplayController);



#define DOUBLEBUFFERING 1


struct Test {
  virtual ~Test() { };
  virtual void update() = 0;
  virtual bool nextState() = 0;
  virtual int testState() = 0;
  virtual char const * name() = 0;
};


#include "ballstest.h"
#include "polygonstest.h"
#include "spritestest.h"
#include "arcstest.h"


void setup()
{
  DisplayController.begin();
  DisplayController.setResolution(VGA_320x200_75Hz, -1, -1, DOUBLEBUFFERING);
  //DisplayController.moveScreen(-8, 0);

  // get a font for about 40x14 text screen
  canvas.selectFont(&fabgl::FONT_8x8);

  canvas.setGlyphOptions(GlyphOptions().FillBackground(true));
}


void loop()
{
  static int64_t stime  = esp_timer_get_time();
  static int FPS        = 0;
  static int FPSCounter = 0;
  static int testIndex  = 0;
  static Test * test    = new ArcsTest; // Moved arc to first just for test

  if (test->nextState() == false) {
    delete test;
    ++testIndex;
    switch (testIndex) {
      /*case 3:
        test = new PolygonsTest;
        break;
      case 2:
        test = new SpritesTest;
        break;
      case 0:
        test = new ArcsTest;
        break;
      default:
        testIndex = 0;
        test = new BallsTest;
        break;*/
      default:
        test = new ArcsTest;
        testIndex = 0;
        break;
    }
  }

  if (esp_timer_get_time() - stime > 1000000) {
    // calculate FPS
    FPS = FPSCounter;
    stime = esp_timer_get_time();
    FPSCounter = 0;
  }
  ++FPSCounter;

  test->update();

  // display test state and FPS
  canvas.setPenColor(Color::Blue);
  canvas.setBrushColor(Color::Yellow);
  canvas.drawTextFmt(80, 5, " %d %s at %d FPS ", test->testState(), test->name(), FPS);

  if (DOUBLEBUFFERING)
    canvas.swapBuffers();
}
