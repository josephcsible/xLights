/***************************************************************
 * Name:      PixelBuffer.h
 * Purpose:   Implements pixel buffer and effects
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-21
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

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <wx/xml/xml.h>

#include "ModelClass.h"
#include "RgbEffects.h"

/**
 * \brief enumeration of the different techniques used in layering effects
 */

enum MixTypes
{
    Mix_Normal,  /** Layered with Alpha channel considered **/
    Mix_Effect1, /**<  Effect 1 only */
    Mix_Effect2, /**<  Effect 2 only */
    Mix_Mask1,   /**<  Effect 2 color shows where Effect 1 is black */
    Mix_Mask2,   /**<  Effect 1 color shows where Effect 2 is black */
    Mix_Unmask1, /**<  Effect 2 color shows where Effect 1 is not black */
    Mix_Unmask2, /**<  Effect 1 color shows where Effect 2 is black */
    Mix_1_reveals_2,  /**<  Effect 2 color only shows if Effect 1 is black  1 reveals 2 */
    Mix_2_reveals_1,  /**<  Effect 1 color only shows if Effect 2 is black */
    Mix_Layered, /**<  Effect 1 is back ground and shows only when effect 2 is black */
    Mix_Average, /**<  Average color value between effects per pixel */
    Mix_BottomTop,
    Mix_LeftRight,
    Mix_Shadow_1on2, /**< Take value and saturation from Effect 1 and put them onto effect 2, leave hue alone on effect 2 */
    Mix_Shadow_2on1 /**< Take value and saturation from Effect 3 and put them onto effect 2, leave hue alone on effect 1 */

};
class Effect;
class SequenceElements;
class SettingsMap;
class DimmingCurve;

class PixelBufferClass : public ModelClass
{
private:
    PixelBufferClass(const PixelBufferClass &cls);
    PixelBufferClass &operator=(const PixelBufferClass &);
    int numLayers;
    int frameTimeInMs;

    int CurrentLayer;  // 0 or 1
    DimmingCurve *dimmingCurve;

    //bunch of per layer settings
    RgbEffects *effects;
    int *sparkle_count;
    int *brightness;
    int *contrast;
    double *fadeFactor;
    MixTypes *mixType;
    float *effectMixThreshold;
    bool *effectMixVaries; //allow varying mix threshold -DJ

    void GetMixedColor(const wxCoord &x, const wxCoord &y, xlColour& c, const std::vector<bool> & validLayers, int & sparkle);
    xlColour mixColors(const wxCoord &x, const wxCoord &y, const xlColour &c0, const xlColour &c1, int layer);
    void SetDimmingCurve(DimmingCurve *value);
    void reset(int layers, int timing);
public:
    PixelBufferClass();
    virtual ~PixelBufferClass();
    void InitBuffer(wxXmlNode* ModelNode, int layers, int timing, NetInfoClass &netInfo, bool zeroBased=false);
    void InitStrandBuffer(const ModelClass &pbc, int strand, int timing);
    void InitNodeBuffer(const ModelClass &pbc, int strand, int node, int timing);
    
    void Clear(int which);
    // not used: size_t GetColorCount(int layer);
    void SetMixType(int layer, const wxString& MixName);
    void SetPalette(int layer, xlColourVector& newcolors);
    void SetLayer(int newlayer, int period, bool ResetState);
    void SetTimes(int layer, int startTime, int endTime);
    void SetFadeTimes(int layer, float inTime, float outTime);
    void SetSparkle(int layer, int freq);
    void SetBrightness(int layer, int value);
    void SetContrast(int layer, int value);
    void SetMixThreshold(int layer, int value, bool varies);

    void CalcOutput(int EffectPeriod, const std::vector<bool> &validLayers);
    
    void SetColors(int layer, const unsigned char *fdata);

#include "Effects.h"

};
typedef std::unique_ptr<PixelBufferClass> PixelBufferClassPtr;

#endif // PIXELBUFFER_H
