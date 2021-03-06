#ifndef XLGRIDCANVASMORPH_H
#define XLGRIDCANVASMORPH_H

#include "wx/wx.h"
#include "xlGridCanvas.h"
#include "Effect.h"

wxDECLARE_EVENT(EVT_EFFECT_CHANGED, wxCommandEvent);

class xlGridCanvasMorph : public xlGridCanvas
{
    public:

        xlGridCanvasMorph(wxWindow* parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition,
                          const wxSize &size=wxDefaultSize,long style=0, const wxString &name=wxPanelNameStr);
        virtual ~xlGridCanvasMorph();

        virtual void SetEffect(Effect* effect_);
        virtual void ForceRefresh();

    protected:
        virtual void InitializeGLCanvas();

    private:

        int CheckForCornerHit(int x, int y);
        void mouseMoved(wxMouseEvent& event);
        void mouseLeftDown(wxMouseEvent& event);
        void mouseLeftUp(wxMouseEvent& event);
        void render(wxPaintEvent& event);
        void DrawMorphEffect();
        void CreateCornerTextures();
        void UpdateMorphPositionsFromEffect();
        void UpdateSelectedMorphCorner(int x, int y);
        void StoreUpdatedMorphPositions();

        int x1a, x1b, x2a, x2b, y1a, y1b, y2a, y2b;
        int mSelectedCorner;
        bool mMorphStartLinked;
        bool mMorphEndLinked;
        wxBitmap corner_1a, corner_1b, corner_2a, corner_2b;
        GLuint mCornerTextures[6];

        DECLARE_EVENT_TABLE()
};

#endif // XLGRIDCANVASMORPH_H
