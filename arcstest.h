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


#include "fabutils.h"


using fabgl::twrap;


// Arcs by Carles Oriol 

const int cos_table[360] = {
1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974, 970, 966, 
961, 956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883, 875, 866, 857, 
848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731, 719, 707, 695, 682, 
669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530, 515, 500, 485, 469, 454, 
438, 423, 407, 391, 375, 358, 342, 326, 309, 292, 276, 259, 242, 225, 208, 191, 
174, 156, 139, 122, 105, 87, 70, 52, 35, 17, 0, -17, -35, -52, -70, -87, -105, 
-122, -139, -156, -174, -191, -208, -225, -242, -259, -276, -292, -309, -326, 
-342, -358, -375, -391, -407, -423, -438, -454, -469, -485, -500, -515, -530, 
-545, -559, -574, -588, -602, -616, -629, -643, -656, -669, -682, -695, -707, 
-719, -731, -743, -755, -766, -777, -788, -799, -809, -819, -829, -839, -848, 
-857, -866, -875, -883, -891, -899, -906, -914, -921, -927, -934, -940, -946, 
-951, -956, -961, -966, -970, -974, -978, -982, -985, -988, -990, -993, -995, 
-996, -998, -999, -999, -1000, -1000, -1000, -999, -999, -998, -996, -995, -993, 
-990, -988, -985, -982, -978, -974, -970, -966, -961, -956, -951, -946, -940, 
-934, -927, -921, -914, -906, -899, -891, -883, -875, -866, -857, -848, -839, 
-829, -819, -809, -799, -788, -777, -766, -755, -743, -731, -719, -707, -695, 
-682, -669, -656, -643, -629, -616, -602, -588, -574, -559, -545, -530, -515, 
-500, -485, -469, -454, -438, -423, -407, -391, -375, -358, -342, -326, -309, 
-292, -276, -259, -242, -225, -208, -191, -174, -156, -139, -122, -105, -87, 
-70, -52, -35, -17, 0, 17, 35, 52, 70, 87, 105, 122, 139, 156, 174, 191, 208, 
225, 242, 259, 276, 292, 309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 
485, 500, 515, 530, 545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695, 
707, 719, 731, 743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857, 866, 
875, 883, 891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961, 966, 970, 
974, 978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000
};

RGB888 palette[12] = {  RGB888(255, 0, 0),RGB888(255, 255, 128),RGB888(255, 0, 255),
                            RGB888(0, 0, 255),RGB888(128, 255, 255),RGB888(255, 255,0 ),
                            RGB888(128, 0, 0),RGB888(0, 128, 0),RGB888(128, 0, 128),
                            RGB888(0, 0, 128),RGB888(0, 128, 128),RGB888(128, 128, 0),
                          };
                          


void drawArcAddPunt(Point punts[], int &npunts)
{
  if ( npunts == 0) npunts++;
  else if ( punts[npunts].X != punts[npunts - 1].X || punts[npunts].Y != punts[npunts - 1].Y)
      npunts++;  
}

void drawArc(int x, int y, int rmin, int rmax, const int gstart, const int gend)
{
  Point punts[360 * 2];
  int npunts = 0;

  int oldx, oldy;

  for ( int ncompta = gstart; ncompta <= gend; ncompta+=10)
  {
    punts[npunts].X = x + (cos_table[ncompta%360] * rmin)/800; // rounder 
    punts[npunts].Y = y + (cos_table[(ncompta+270)%360] * rmin)/1000;    
    drawArcAddPunt(punts, npunts);    
  }
  for ( int ncompta = gend; ncompta >= gstart; ncompta-=10)
  {
    punts[npunts].X = x + (cos_table[ncompta%360] * rmax)/800; // rounder
    punts[npunts].Y = y + (cos_table[(ncompta+270)%360] * rmax)/1000;            
    drawArcAddPunt(punts, npunts);
  }
  canvas.fillPath( punts, npunts);
}


class ArcsTest : public Test {
public:

  ArcsTest()
  {
    
  }

  virtual ~ArcsTest()
  {

  }

  void update()
  {
    static int npos[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
      canvas.setBrushColor(RGB888(0, 0, 64));

  canvas.clear();

  int ox = -cos_table[counter_%360]/8; 
  int oy = cos_table[(counter_+270)%360]/10;
  
  for(int l = -10; l<20; l++)
  {    
    canvas.setPenColor(l %3 == 0 ? RGB888(0,0,0) : RGB888(64,64,64));
    
    canvas.drawLine(0, 20*l+oy, 319, 20*l-oy);
    canvas.drawLine(32*l+ox, 0, 32*l-ox, 199);
  }

  for(int ncompta = 0; ncompta<12; ncompta++)
  {
    canvas.setPenColor(palette[ncompta]);  
    canvas.setBrushColor(palette[ncompta]);      
    drawArc(160+cos_table[counter_%360]/8, 
    //(sizeCount_ < 12) ? 100: (100+cos_table[(counter_*10)%360]/40), 
    (100+cos_table[(counter_*10)%360]/40), 
    ncompta*13+sizeCount_/2+2, (ncompta+1)*13+sizeCount_+3, npos[ncompta], npos[ncompta]+(sizeCount_/3)*(12-ncompta)+1 );
    npos[ncompta] += ncompta * 2+3;
  }
  }

  bool nextState()
  {
    if (sizeCount_ == MAXSIZE)
      return false;
    if (counter_ % 40 == 0) 
    {
      sizeCount_++;
    }
    ++counter_;
    return true;
  }

  int testState()
  {
    return sizeCount_;
  }

  char const * name() { return "size Arcs"; }

private:

  static const int MAXSIZE = 50;

  int sizeCount_ = 0;

  int counter_ = 0;

};
