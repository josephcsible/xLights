#include "DimmingCurve.h"

#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

class BaseDimmingCurve : public DimmingCurve {
public:
    BaseDimmingCurve(int ch = -1) : DimmingCurve(), channel(ch)  {
        for (int x = 0; x < 256; x++) {
            data[x] = x;
            reverseData[x] = 0;
        }
    }
    virtual ~BaseDimmingCurve() {}

    void fixupReverseData() {
        int lastIdx = 0;
        
        for (int x = 1; x < 256; x++) {
            if (reverseData[x] == 0) {
                //possibly not set, let's average between
                int origX = x;
                while (x < 256 && reverseData[x] == 0) {
                    x++;
                }
                if (x < 256) {
                    int newV = reverseData[x];
                    for (int x2 = origX; x2 < x; x2++) {
                        reverseData[x2] = reverseData[lastIdx] + float(newV - reverseData[lastIdx]) * float(x2-origX) / float(x-origX);
                    }
                    lastIdx = x;
                } else {
                    for (int x2 = origX; x2 < x; x2++) {
                        reverseData[x2] = reverseData[lastIdx];
                    }
                }
            } else {
                lastIdx = x;
            }
        }
    }
    
    virtual void apply(xlColor &c) {
        switch (channel) {
            case -1:
                c.green = data[c.green];
                c.blue = data[c.blue];
                c.red = data[c.red];
                break;
            case 0:
                c.red = data[c.red];
                break;
            case 1:
                c.green = data[c.green];
                break;
            case 2:
                c.blue = data[c.blue];
                break;
            case 4:
                if (c.blue == c.red && c.green == c.red) {
                    c.green = c.blue = c.red = data[c.red];
                }
                break;
        }
    }
    virtual void reverse(xlColor &c) {
        switch (channel) {
            case -1:
                c.green = reverseData[c.green];
                c.blue = reverseData[c.blue];
                c.red = reverseData[c.red];
                break;
            case 0:
                c.red = reverseData[c.red];
                break;
            case 1:
                c.green = reverseData[c.green];
                break;
            case 2:
                c.blue = reverseData[c.blue];
                break;
            case 4:
                if (c.blue == c.red && c.green == c.red) {
                    c.green = c.blue = c.red = reverseData[c.red];
                }
                break;
        }
    }

    
    int channel;
    unsigned char data[256];
    unsigned char reverseData[256];
};


class BasicDimmingCurve : public BaseDimmingCurve {
public:
    BasicDimmingCurve(int ch = -1) : BaseDimmingCurve(ch)  {
    }
    BasicDimmingCurve(int brightness, float gamma, int ch = -1) : BaseDimmingCurve(ch) {
        init(brightness, gamma);
    }
    virtual ~BasicDimmingCurve() {}

    void init(int brightness, float gamma) {
        for (int x = 0; x < 256; x++) {
            float i = x;
            i = i * float(brightness + 100) / 100.0;
            i = 255 * powf(i / 255.0, gamma);
            if (i > 255) {
                i = 255;
            }
            if (i < 0) {
                i = 0;
            }
            data[x] = i;
            reverseData[(int)i] = x;
        }
        fixupReverseData();
    }
};

class FileDimmingCurve : public BaseDimmingCurve {
public:
    FileDimmingCurve(const wxString &f, int ch = -1) : BaseDimmingCurve(ch) {
        wxFileInputStream fin(f);
        wxTextInputStream text(fin);
        
        int count = 0;
        while(fin.Eof() == false){
            wxString data = text.ReadLine();
            if (data != "") {
                data[count] = wxAtoi(data);
                reverseData[data[count]] = count;
                count++;
                if (count == 256) {
                    return;
                }
            }
        }
        fixupReverseData();
    }
};

class CompositeDimmingCurve : public DimmingCurve {
public:
    CompositeDimmingCurve(DimmingCurve *r, DimmingCurve *g, DimmingCurve *b) : DimmingCurve(), red(r), green(g), blue(b) {
    }
    virtual ~CompositeDimmingCurve() {
        if (red != nullptr) {
            delete red;
        }
        if (green != nullptr) {
            delete green;
        }
        if (blue != nullptr) {
            delete blue;
        }
    }
    virtual void apply(xlColor &c) {
        if (red != nullptr) {
            red->apply(c);
        }
        if (green != nullptr) {
            green->apply(c);
        }
        if (blue != nullptr) {
            blue->apply(c);
        }
    }
    virtual void reverse(xlColor &c) {
        if (red != nullptr) {
            red->reverse(c);
        }
        if (green != nullptr) {
            green->reverse(c);
        }
        if (blue != nullptr) {
            blue->reverse(c);
        }
    }
    DimmingCurve *red;
    DimmingCurve *green;
    DimmingCurve *blue;
};

DimmingCurve::DimmingCurve()
{
}

DimmingCurve::~DimmingCurve()
{
}

DimmingCurve *createCurve(wxXmlNode *dc, int channel = -1) {
    if (dc->HasAttribute("filename")) {
        wxString fn = dc->GetAttribute("filename");
        if (wxFile::Exists(fn)) {
            return new FileDimmingCurve(fn);
        }
    } else {
        return new BasicDimmingCurve(wxAtoi(dc->GetAttribute("brightness", "0")),
                                     wxAtof(dc->GetAttribute("gamma", "1.0")));
    }
    return nullptr;
}

DimmingCurve *DimmingCurve::createFromXML(wxXmlNode *node) {
    DimmingCurve *red = nullptr;
    DimmingCurve *green = nullptr;
    DimmingCurve *blue = nullptr;
    
    wxXmlNode *dc = node->GetChildren();
    while (dc != nullptr) {
        wxString name = dc->GetName();
        if ("all" == name) {
            return createCurve(dc);
        } else if ("red" == dc->GetName()) {
            red = createCurve(dc, 0);
        } else if ("green" == dc->GetName()) {
            green = createCurve(dc, 1);
        } else if ("blue" == dc->GetName()) {
            blue = createCurve(dc, 2);
        }
        dc = dc->GetNext();
    }
    if (red != nullptr || blue != nullptr || green != nullptr) {
        return new CompositeDimmingCurve(red, green, blue);
    }
    return nullptr;
}

DimmingCurve *DimmingCurve::createBrightnessGamma(int brightness, float gamma) {
    BasicDimmingCurve *c = new BasicDimmingCurve(brightness, gamma);
    return c;
}
DimmingCurve *DimmingCurve::createFromFile(const wxString &fileName) {
    if (wxFile::Exists(fileName)) {
        return new FileDimmingCurve(fileName);
    }
    return new BasicDimmingCurve(100, 1.0);
}
