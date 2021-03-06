#ifndef TIMINGPANEL_H
#define TIMINGPANEL_H

//(*Headers(TimingPanel)
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
//*)

class TimingPanel: public wxPanel
{
	public:

		TimingPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TimingPanel();

        void UpdateEffectLayerMix();
        wxString GetTimingString();

		//(*Declarations(TimingPanel)
		wxStaticText* StaticText2;
		wxPanel* Panel_Sizer;
		wxTextCtrl* TextCtrl_Fadein;
		wxBitmapButton* BitmapButton_OverlayBkg;
		wxStaticText* StaticText1;
		wxSlider* Slider_EffectLayerMix;
		wxStaticText* StaticText3;
		wxBitmapButton* BitmapButton_FadeOut;
		wxBitmapButton* BitmapButton_FadeIn;
		wxBitmapButton* BitmapButton_CheckBox_LayerMorph;
		wxCheckBox* CheckBox_LayerMorph;
		wxChoice* Choice_LayerMethod;
		wxBitmapButton* BitmapButton_EffectLayerMix;
		wxTextCtrl* TextCtrl_Fadeout;
		wxScrolledWindow* ScrolledWindowTiming;
		wxCheckBox* CheckBox_OverlayBkg;
		wxTextCtrl* txtCtlEffectMix;
		//*)

	protected:

		//(*Identifiers(TimingPanel)
		static const long ID_STATICTEXT4;
		static const long ID_CHECKBOX_LayerMorph;
		static const long ID_BITMAPBUTTON_CHECKBOX_LayerMorph;
		static const long ID_CHOICE_LayerMethod;
		static const long ID_SLIDER_EffectLayerMix;
		static const long ID_TEXTCTRL_LayerMix;
		static const long ID_BITMAPBUTTON_SLIDER_EffectLayerMix;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL_Fadein;
		static const long ID_BITMAPBUTTON_TEXTCTRL_Fadein;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL_Fadeout;
		static const long ID_BITMAPBUTTON_TEXTCTRL_Fadeout;
		static const long ID_CHECKBOX_OverlayBkg;
		static const long ID_BITMAPBUTTON_OverlayBkg;
		static const long ID_SCROLLEDWINDOW1;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(TimingPanel)
		void OnCheckBox_OverlayBkgClick(wxCommandEvent& event);
		void OnBitmapButton_FadeOutClick(wxCommandEvent& event);
		void OnBitmapButton_FadeInClick(wxCommandEvent& event);
		void OnBitmapButton_OverlayBkgClick(wxCommandEvent& event);
		void OnResize(wxSizeEvent& event);
		void OnLeftDClick(wxMouseEvent& event);
		void OnSlider_EffectLayerMixCmdScroll(wxScrollEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
