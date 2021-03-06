/***************************************************************
 * Name:      RgbEffects.cpp
 * Purpose:   Implements RGB effects
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-12-23
 * Copyright: 2012 by Matt Brown
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

void RgbEffects::RenderTree(int Branches, int tspeed)
{

    effectState = (curPeriod - curEffStartPer) * tspeed * frameTimeInMs / 50;
    
    int x,y,i,r,ColorIdx,pixels_per_branch;
    int maxFrame,mod,branch,row,b,f_mod,m,frame;
    int number_garlands,f_mod_odd,s_odd_row,odd_even;
    float V,H;

    number_garlands=1;
    xlColor color;
    if(Branches<1)  Branches=1;
    pixels_per_branch=(int)(0.5+BufferHt/Branches);
    if(pixels_per_branch<1) pixels_per_branch=1;

    maxFrame=(Branches+1) *BufferWi;
    if(effectState>0 && maxFrame>0) frame = (effectState/4)%maxFrame;
    else frame=1;

    i=0;

    for (y=0; y<BufferHt; y++) // For my 20x120 megatree, BufferHt=120
    {
        for (x=0; x<BufferWi; x++) // BufferWi=20 in the above example
        {
            if(pixels_per_branch>0) mod=y%pixels_per_branch;
            else mod=0;
            if(mod==0) mod=pixels_per_branch;
            V=1-(1.0*mod/pixels_per_branch)*0.70;
            i++;

            ColorIdx=0;
            palette.GetColor(ColorIdx, color); // Now go and get the hsv value for this ColorIdx
            if (allowAlpha) {
                color.alpha = 255.0 * V;
            } else {
                wxImage::HSVValue hsv = color.asHSV();
                hsv.value = V; // we have now set the color for the background tree
                color = hsv;
            }

            //   $orig_rgbval=$rgb_val;
            branch = (int)((y-1)/pixels_per_branch);
            row = pixels_per_branch-mod; // now row=0 is bottom of branch, row=1 is one above bottom
            //  mod = which pixel we are in the branch
            //	mod=1,row=pixels_per_branch-1   top picrl in branch
            //	mod=2, second pixel down into branch
            //	mod=pixels_per_branch,row=0  last pixel in branch
            //
            //	row = 0, the $p is in the bottom row of tree
            //	row =1, the $p is in second row from bottom
            b = (int) ((effectState)/BufferWi)%Branches; // what branch we are on based on frame #
            //
            //	b = 0, we are on bottomow row of tree during frames 1 to BufferWi
            //	b = 1, we are on second row from bottom, frames = BufferWi+1 to 2*BufferWi
            //	b = 2, we are on third row from bottome, frames - 2*BufferWi+1 to 3*BufferWi
            f_mod = (effectState/4)%BufferWi;
            //   if(f_mod==0) f_mod=BufferWi;
            //	f_mod is  to BufferWi-1 on each row
            //	f_mod == 0, left strand of this row
            //	f_mod==BufferWi, right strand of this row
            //
            m=(x%6);
            if(m==0) m=6;  // use $m to indicate where we are in horizontal pattern
            // m=1, 1sr strand
            // m=2, 2nd strand
            // m=6, last strand in 6 strand pattern



            r=branch%5;
            H = r/4.0;

            odd_even=b%2;
            s_odd_row = BufferWi-x+1;
            f_mod_odd = BufferWi-f_mod+1;

            if(branch<=b && x<=frame && // for branches below or equal to current row
                    (((row==3 || (number_garlands==2 && row==6)) && (m==1 || m==6))
                     ||
                     ((row==2 || (number_garlands==2 && row==5)) && (m==2 || m==5))
                     ||
                     ((row==1 || (number_garlands==2 && row==4)) && (m==3 || m==4))
                    ))
                if((odd_even ==0 && x<=f_mod) || (odd_even ==1 && s_odd_row<=f_mod))
                {
                    wxImage::HSVValue hsv;
                    hsv.hue = H;
                    hsv.saturation=1.0;
                    hsv.value=1.0;
                    color = hsv;
                }
            //	if(branch>b)
//	{
//		return $rgb_val; // for branches below current, dont dont balnk anything out
//	}
//	else if(branch==b)
//	{
//		if(odd_even ==0 && x>f_mod)
//		{
//			$rgb_val=$orig_rgbval;// we are even row ,counting from bottom as zero
//		}
//		if(odd_even ==1 && s_odd_row>f_mod)
//		{
//			$rgb_val=$orig_rgbval;// we are even row ,counting from bottom as zero
//		}
//	}
            //if($branch>$b) $rgb_val=$orig_rgbval; // erase rows above our current row.


            // Yes, so now decide on what color it should be


            //  we left the Hue and Saturation alone, we are just modifiying the Brightness Value
            SetPixel(x,y,color); // Turn pixel on

        }
    }
}
