/***************************************************************
 * Name:      RenderCircles
 * Purpose:   Extends RGB effects with Circle effects
 * Author:    Frank Reichstein (phar_hp@yahoo.com)
 * Created:   2013-07-28
 * Copyright: 2013 by Frank Reichstein
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include <cmath>
#include "RgbEffects.h"


void RgbEffects::RenderCircles(int number,int radius, bool bounce, bool collide, bool random,
                               bool radial, int start_x, int start_y)
{

    int ii=0;
    int colorIdx;
    size_t colorCnt=GetColorCount();
    wxImage::HSVValue hsv;
    float spd;
    float angle;
    static int numBalls = 0;

    if (radial)
    {
        RenderRadial(start_x, start_y, radius, colorCnt);
        return; //radial is the easiest case so just get out.
    }


    if ( 0 == state || radius != balls[ii]._radius || number != numBalls)
    {
        numBalls = number;
        for(ii=0; ii<number; ii++)
        {
            start_x = rand()%(BufferWi);
            start_y = rand()%(BufferHt);
            colorIdx = ii%colorCnt;
            palette.GetHSV(colorIdx, hsv);
            spd = rand()%3 + 1;
            angle = rand()%2?rand()%90:-rand()%90;
            balls[ii].Reset((float) start_x, (float) start_y, spd, angle, (float)radius, hsv);
        }
    }
    else
    {
        RenderCirclesUpdate(number);
    }

    if (bounce)
    {
        //update position in case something hit a wall
        for(ii = 0; ii < number; ii++)
        {
            balls[ii].Bounce(BufferWi,BufferHt);
        }
    }
    if(collide)
    {
        //update position if two balls collided
    }

    for (ii=0; ii<number; ii++)
    {
        hsv = balls[ii].hsvcolor;
        for(int r = balls[ii]._radius; r >= 0; r--)
        {
            if(!bounce && !collide)
            {
                DrawCircle(balls[ii]._x, balls[ii]._y, r, hsv);
            }
            else
            {
                DrawCircleClipped(balls[ii]._x, balls[ii]._y, r, hsv);
            }
        }
    }

}

void RgbEffects::RenderCirclesUpdate(int ballCnt)
{
    int ii;
    for (ii=0; ii <ballCnt; ii++)
    {
        balls[ii].updatePosition(speed/4, BufferWi, BufferHt);
    }
}

void RgbEffects::RenderRadial(int x, int y,int thickness, int colorCnt)
{
    wxImage::HSVValue hsv;
    int ii,n;
    int colorIdx;
    int barht = BufferHt/(thickness+1);
    if(barht<1) barht=1;
    int maxRadius = state>BufferHt?BufferHt: state/2 + thickness;
    int blockHt   = colorCnt*barht;
    int f_offset  = state/4 % (blockHt+1);

    barht = barht>0?barht:1;
    palette.GetHSV(0,hsv);
    for( ii = maxRadius ; ii >= 0;  ii--)
    {
        n=ii-f_offset+blockHt;
        colorIdx = (n)%blockHt/barht;
        palette.GetHSV(colorIdx,hsv);

        DrawCircle(x, y, ii, hsv);
    }
}

