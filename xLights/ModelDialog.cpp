#include "ModelDialog.h"
#include "ModelClass.h"
#include <wx/msgdlg.h>
#include <wx/clipbrd.h>

//(*InternalHeaders(ModelDialog)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "ModelPreview.h"
#include "PixelAppearanceDlg.h"
#include "StrandNodeNamesDialog.h"
#include "NetInfo.h"
#include "ModelFaceDialog.h"
#include "ModelDimmingCurveDialog.h"

//(*IdInit(ModelDialog)
const long ModelDialog::ID_STATICTEXT1 = wxNewId();
const long ModelDialog::ID_TEXTCTRL1 = wxNewId();
const long ModelDialog::ID_STATICTEXT5 = wxNewId();
const long ModelDialog::ID_CHOICE_DisplayAs = wxNewId();
const long ModelDialog::ID_STATICTEXT12 = wxNewId();
const long ModelDialog::ID_CHOICE_STRING_TYPE = wxNewId();
const long ModelDialog::ID_COLOURPICKERCTRL1 = wxNewId();
const long ModelDialog::ID_STATICTEXT2 = wxNewId();
const long ModelDialog::ID_SPINCTRL1 = wxNewId();
const long ModelDialog::ID_STATICTEXT3 = wxNewId();
const long ModelDialog::ID_SPINCTRL2 = wxNewId();
const long ModelDialog::ID_STATICTEXT4 = wxNewId();
const long ModelDialog::ID_SPINCTRL3 = wxNewId();
const long ModelDialog::ID_STATICTEXT6 = wxNewId();
const long ModelDialog::ID_SPINCTRL4 = wxNewId();
const long ModelDialog::ID_STATICTEXT9 = wxNewId();
const long ModelDialog::ID_SPINCTRL6 = wxNewId();
const long ModelDialog::ID_STATICTEXT8 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON1 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON2 = wxNewId();
const long ModelDialog::ID_STATICTEXT11 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON4 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON3 = wxNewId();
const long ModelDialog::ID_STATICTEXT10 = wxNewId();
const long ModelDialog::ID_CHECKBOX1 = wxNewId();
const long ModelDialog::ID_STATICTEXT15 = wxNewId();
const long ModelDialog::ID_SPINCTRL5 = wxNewId();
const long ModelDialog::ID_TEXTCTRL3 = wxNewId();
const long ModelDialog::ID_BUTTON2 = wxNewId();
const long ModelDialog::ID_BUTTON3 = wxNewId();
const long ModelDialog::ID_BUTTON4 = wxNewId();
const long ModelDialog::ID_BUTTON1 = wxNewId();
const long ModelDialog::ID_CHECKBOX2 = wxNewId();
const long ModelDialog::ID_GRID_START_CHANNELS = wxNewId();
const long ModelDialog::ID_STATICTEXT14 = wxNewId();
const long ModelDialog::ID_BITMAPBUTTON_CUSTOM_CUT = wxNewId();
const long ModelDialog::ID_BITMAPBUTTON_CUSTOM_COPY = wxNewId();
const long ModelDialog::ID_BITMAPBUTTON_CUSTOM_PASTE = wxNewId();
const long ModelDialog::ID_BUTTON_CUSTOM_MODEL_HELP = wxNewId();
const long ModelDialog::ID_BUTTON_CustomModelZoomIn = wxNewId();
const long ModelDialog::ID_BUTTON_CustomModelZoomOut = wxNewId();
const long ModelDialog::ID_GRID_Custom = wxNewId();
//*)

BEGIN_EVENT_TABLE(ModelDialog,wxDialog)
    //(*EventTable(ModelDialog)
    //*)
END_EVENT_TABLE()


ModelDialog::ModelDialog(wxWindow* parent,wxWindowID id)
{
    netInfo = nullptr;

    //(*Initialize(ModelDialog)
    wxFlexGridSizer* FlexGridSizer4;
    wxButton* Button01;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxButton* Button04;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxFlexGridSizer* FlexGridSizer7;
    wxBoxSizer* BoxSizer1;
    wxStdDialogButtonSizer* StdDialogButtonSizer2;
    wxFlexGridSizer* FlexGridSizer1;
    wxButton* Button03;

    Create(parent, wxID_ANY, _("Model"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    SetHelpText(_("Pixels Start in the upper left and go right or down depending on Vertical or Horizontal orientation.  Trees are always Vertical."));
    OuterSizer = new wxFlexGridSizer(0, 3, 0, 0);
    OuterSizer->AddGrowableCol(2);
    OuterSizer->AddGrowableRow(0);
    LeftGridSizer = new wxFlexGridSizer(15, 2, 0, 0);
    LeftGridSizer->AddGrowableRow(12);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Model Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    LeftGridSizer->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_Name = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    LeftGridSizer->Add(TextCtrl_Name, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Display As"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    LeftGridSizer->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Choice_DisplayAs = new wxChoice(this, ID_CHOICE_DisplayAs, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_DisplayAs"));
    Choice_DisplayAs->SetSelection( Choice_DisplayAs->Append(_("Tree 360")) );
    Choice_DisplayAs->Append(_("Tree 270"));
    Choice_DisplayAs->Append(_("Tree 180"));
    Choice_DisplayAs->Append(_("Tree 90"));
    Choice_DisplayAs->Append(_("Tree Flat"));
    Choice_DisplayAs->Append(_("Tree Ribbon"));
    Choice_DisplayAs->Append(_("Vert Matrix"));
    Choice_DisplayAs->Append(_("Horiz Matrix"));
    Choice_DisplayAs->Append(_("Single Line"));
    Choice_DisplayAs->Append(_("Arches"));
    Choice_DisplayAs->Append(_("Circle"));
    Choice_DisplayAs->Append(_("Window Frame"));
    Choice_DisplayAs->Append(_("Star"));
    Choice_DisplayAs->Append(_("Wreath"));
    Choice_DisplayAs->Append(_("Custom"));
    Choice_DisplayAs->Append(_("Sphere 360"));
    Choice_DisplayAs->Append(_("Sphere 270"));
    Choice_DisplayAs->Append(_("Sphere 180"));
    LeftGridSizer->Add(Choice_DisplayAs, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT12, _("Type of String"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    LeftGridSizer->Add(StaticText9, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    Choice_StringType = new wxChoice(this, ID_CHOICE_STRING_TYPE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_STRING_TYPE"));
    Choice_StringType->SetSelection( Choice_StringType->Append(_("RGB Nodes")) );
    Choice_StringType->Append(_("RBG Nodes"));
    Choice_StringType->Append(_("GBR Nodes"));
    Choice_StringType->Append(_("GRB Nodes"));
    Choice_StringType->Append(_("BRG Nodes"));
    Choice_StringType->Append(_("BGR Nodes"));
    Choice_StringType->Append(_("3 Channel RGB"));
    Choice_StringType->Append(_("4 Channel RGBW"));
    Choice_StringType->Append(_("Single Color Red"));
    Choice_StringType->Append(_("Single Color Green"));
    Choice_StringType->Append(_("Single Color Blue"));
    Choice_StringType->Append(_("Single Color White"));
    Choice_StringType->Append(_("Single Color Custom"));
    Choice_StringType->Append(_("Strobes White 3fps"));
    FlexGridSizer1->Add(Choice_StringType, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ColorPicker = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(255,0,255), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    FlexGridSizer1->Add(ColorPicker, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    LeftGridSizer->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText_Strings = new wxStaticText(this, ID_STATICTEXT2, _("Actual # of Strings"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    LeftGridSizer->Add(StaticText_Strings, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_parm1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(35,-1)), 0, 1, 1000, 1, _T("ID_SPINCTRL1"));
    SpinCtrl_parm1->SetValue(_T("1"));
    LeftGridSizer->Add(SpinCtrl_parm1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Nodes = new wxStaticText(this, ID_STATICTEXT3, _("# of RGB Nodes per String"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    LeftGridSizer->Add(StaticText_Nodes, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_parm2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("50"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(35,-1)), 0, 1, 65535, 50, _T("ID_SPINCTRL2"));
    SpinCtrl_parm2->SetValue(_T("50"));
    LeftGridSizer->Add(SpinCtrl_parm2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Strands = new wxStaticText(this, ID_STATICTEXT4, _("# of Strands per String"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText_Strands->SetHelpText(_("How many times is a string folded\?"));
    LeftGridSizer->Add(StaticText_Strands, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_parm3 = new wxSpinCtrl(this, ID_SPINCTRL3, _T("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(35,-1)), 0, 1, 1000, 1, _T("ID_SPINCTRL3"));
    SpinCtrl_parm3->SetValue(_T("1"));
    LeftGridSizer->Add(SpinCtrl_parm3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Start Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    LeftGridSizer->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(1);
    SpinCtrl_StartChannel = new wxSpinCtrl(this, ID_SPINCTRL4, _T("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(55,-1)), 0, 1, 999999, 1, _T("ID_SPINCTRL4"));
    SpinCtrl_StartChannel->SetValue(_T("1"));
    FlexGridSizer2->Add(SpinCtrl_StartChannel, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _("From Output:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    OutputSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL6, _T("1"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(45,-1)), 0, 1, 64000, 1, _T("ID_SPINCTRL6"));
    OutputSpinCtrl->SetValue(_T("1"));
    FlexGridSizer2->Add(OutputSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT8, _("Starting Corner"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText3->SetHelpText(_("The point at which pixels in your model start."));
    LeftGridSizer->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    RadioButton_TopLeft = new wxRadioButton(this, ID_RADIOBUTTON1, _("Top Left"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioButton_TopLeft->SetValue(true);
    BoxSizer1->Add(RadioButton_TopLeft, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_TopRight = new wxRadioButton(this, ID_RADIOBUTTON2, _("Top Right"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    BoxSizer1->Add(RadioButton_TopRight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    LeftGridSizer->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    RadioButton_BotLeft = new wxRadioButton(this, ID_RADIOBUTTON4, _("Bottom Left"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
    BoxSizer2->Add(RadioButton_BotLeft, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_BotRight = new wxRadioButton(this, ID_RADIOBUTTON3, _("Bottom Right"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    BoxSizer2->Add(RadioButton_BotRight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _("Part of my display"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    LeftGridSizer->Add(StaticText7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_MyDisplay = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_MyDisplay->SetValue(true);
    LeftGridSizer->Add(CheckBox_MyDisplay, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ExtraParameterLabel = new wxStaticText(this, ID_STATICTEXT15, _("Star Sizes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    LeftGridSizer->Add(ExtraParameterLabel, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
    TreeFirstStringForExport = new wxSpinCtrl(this, ID_SPINCTRL5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 1, 1000, 0, _T("ID_SPINCTRL5"));
    FlexGridSizer10->Add(TreeFirstStringForExport, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StarSizes = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer10->Add(StarSizes, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    LeftGridSizer->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDimCurve = new wxButton(this, ID_BUTTON2, _("Dimming Curves"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    LeftGridSizer->Add(ButtonDimCurve, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StdDialogButtonSizer2 = new wxStdDialogButtonSizer();
    StdDialogButtonSizer2->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
    StdDialogButtonSizer2->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
    StdDialogButtonSizer2->Realize();
    LeftGridSizer->Add(StdDialogButtonSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
    Button03 = new wxButton(this, ID_BUTTON3, _("Appearance"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer7->Add(Button03, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button04 = new wxButton(this, ID_BUTTON4, _("Names"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer7->Add(Button04, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button01 = new wxButton(this, ID_BUTTON1, _("Faces"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer7->Add(Button01, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftGridSizer->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OuterSizer->Add(LeftGridSizer, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    cbIndividualStartNumbers = new wxCheckBox(this, ID_CHECKBOX2, _("Individual Start Chans"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    cbIndividualStartNumbers->SetValue(false);
    FlexGridSizer3->Add(cbIndividualStartNumbers, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    gridStartChannels = new wxGrid(this, ID_GRID_START_CHANNELS, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL|wxFULL_REPAINT_ON_RESIZE, _T("ID_GRID_START_CHANNELS"));
    gridStartChannels->CreateGrid(10,2);
    gridStartChannels->EnableEditing(true);
    gridStartChannels->EnableGridLines(true);
    gridStartChannels->SetRowLabelSize(40);
    gridStartChannels->SetColLabelValue(0, _("Start"));
    gridStartChannels->SetColLabelValue(1, _("End"));
    gridStartChannels->SetDefaultCellFont( gridStartChannels->GetFont() );
    gridStartChannels->SetDefaultCellTextColour( gridStartChannels->GetForegroundColour() );
    FlexGridSizer3->Add(gridStartChannels, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
    OuterSizer->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer4->AddGrowableRow(1);
    FlexGridSizer5 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticTextCustomModel = new wxStaticText(this, ID_STATICTEXT14, _("Custom Model"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer5->Add(StaticTextCustomModel, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonCustomCut = new wxBitmapButton(this, ID_BITMAPBUTTON_CUSTOM_CUT, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CUT")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CUSTOM_CUT"));
    FlexGridSizer5->Add(BitmapButtonCustomCut, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonCustomCopy = new wxBitmapButton(this, ID_BITMAPBUTTON_CUSTOM_COPY, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_COPY")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CUSTOM_COPY"));
    BitmapButtonCustomCopy->SetDefault();
    FlexGridSizer5->Add(BitmapButtonCustomCopy, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonCustomPaste = new wxBitmapButton(this, ID_BITMAPBUTTON_CUSTOM_PASTE, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CUSTOM_PASTE"));
    BitmapButtonCustomPaste->SetDefault();
    FlexGridSizer5->Add(BitmapButtonCustomPaste, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonCustomModelHelp = new wxButton(this, ID_BUTTON_CUSTOM_MODEL_HELP, _("Help"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CUSTOM_MODEL_HELP"));
    FlexGridSizer5->Add(ButtonCustomModelHelp, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_CustomModelZoomIn = new wxButton(this, ID_BUTTON_CustomModelZoomIn, _("+"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CustomModelZoomIn"));
    Button_CustomModelZoomIn->SetMinSize(wxSize(24,-1));
    Button_CustomModelZoomIn->SetToolTip(_("Zoom In"));
    FlexGridSizer5->Add(Button_CustomModelZoomIn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_CustomModelZoomOut = new wxButton(this, ID_BUTTON_CustomModelZoomOut, _("-"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CustomModelZoomOut"));
    Button_CustomModelZoomOut->SetMinSize(wxSize(24,-1));
    Button_CustomModelZoomOut->SetToolTip(_("Zoom Out"));
    FlexGridSizer5->Add(Button_CustomModelZoomOut, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GridCustom = new wxGrid(this, ID_GRID_Custom, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_GRID_Custom"));
    GridCustom->CreateGrid(1,1);
    GridCustom->EnableEditing(true);
    GridCustom->EnableGridLines(true);
    GridCustom->SetColLabelSize(20);
    GridCustom->SetRowLabelSize(30);
    GridCustom->SetDefaultColSize(30, true);
    GridCustom->SetDefaultCellFont( GridCustom->GetFont() );
    GridCustom->SetDefaultCellTextColour( GridCustom->GetForegroundColour() );
    FlexGridSizer4->Add(GridCustom, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
    OuterSizer->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(OuterSizer);
    OuterSizer->Fit(this);
    OuterSizer->SetSizeHints(this);
    Center();

    Connect(ID_CHOICE_DisplayAs,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ModelDialog::OnChoice_DisplayAsSelect);
    Connect(ID_CHOICE_STRING_TYPE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ModelDialog::OnChoice_StringTypeSelect);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ModelDialog::OnSpinCtrl_parm1Change);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ModelDialog::OnSpinCtrl_parm2Change);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ModelDialog::OnSpinCtrl_parm3Change);
    Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ModelDialog::OnSpinCtrl_StartChannelChange);
    Connect(ID_SPINCTRL6,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ModelDialog::OnSpinCtrl_StartChannelChange);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnDimmingCurvesClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnAppearanceButtonClicked);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnNamesButtonClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnFacesButtonClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ModelDialog::OncbIndividualStartNumbersClick);
    Connect(ID_GRID_START_CHANNELS,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&ModelDialog::OngridStartChannelsCellChange);
    Connect(ID_BITMAPBUTTON_CUSTOM_CUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnBitmapButtonCustomCutClick);
    Connect(ID_BITMAPBUTTON_CUSTOM_COPY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnBitmapButtonCustomCopyClick);
    Connect(ID_BITMAPBUTTON_CUSTOM_PASTE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnBitmapButtonCustomPasteClick);
    Connect(ID_BUTTON_CUSTOM_MODEL_HELP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnButtonCustomModelHelpClick);
    Connect(ID_BUTTON_CustomModelZoomIn,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnButton_CustomModelZoomInClick);
    Connect(ID_BUTTON_CustomModelZoomOut,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ModelDialog::OnButton_CustomModelZoomOutClick);
    Connect(ID_GRID_Custom,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&ModelDialog::OnGridCustomCellChange);
    //*)

    wxGridCellTextEditor *editor = new wxGridCellTextEditor();
    wxString filter("0123456789:");
    wxTextValidator validator(wxFILTER_INCLUDE_CHAR_LIST);
    validator.SetCharIncludes(filter);

    editor->SetValidator(validator);
    gridStartChannels->SetDefaultEditor(editor);
    GridCustom->SetDefaultEditor(new wxGridCellNumberEditor());
    HasCustomData = false;
}

ModelDialog::~ModelDialog()
{
    //(*Destroy(ModelDialog)
    //*)
}


// make grid the size specified by the spin controls
void ModelDialog::ResizeCustomGrid()
{
    int numCols=SpinCtrl_parm1->GetValue();
    int numRows=SpinCtrl_parm2->GetValue();
    int deltaCols=numCols - GridCustom->GetNumberCols();
    int deltaRows=numRows - GridCustom->GetNumberRows();
    if (deltaCols > 0) GridCustom->AppendCols(deltaCols);
    if (deltaRows > 0) GridCustom->AppendRows(deltaRows);
    if (deltaCols < 0) GridCustom->DeleteCols(numCols,-deltaCols);
    if (deltaRows < 0) GridCustom->DeleteRows(numRows,-deltaRows);
}

bool ModelDialog::IsCustom()
{
    return Choice_DisplayAs->GetStringSelection() == "Custom";
}

// initialize grid with saved values
wxString ModelDialog::GetCustomGridData()
{
    wxString customChannelData, value;
    if (IsCustom())
    {
        int numCols=GridCustom->GetNumberCols();
        int numRows=GridCustom->GetNumberRows();
        for(int row=0; row < numRows; row++)
        {
            if (row > 0) customChannelData+=";";
            for(int col=0; col<numCols; col++)
            {
                if (col > 0) customChannelData+=",";
                value = GridCustom->GetCellValue(row,col);
                if (value == "0" || value.StartsWith("-")) value.clear();
                customChannelData += value;
            }
        }
    }
    return customChannelData;
}

// Initialize custom grid with saved values
// Must be called AFTER Choice_DisplayAs & SpinCtrl_parm1 & SpinCtrl_parm2 have been set
void ModelDialog::SetCustomGridData(const wxString& customChannelData)
{
    wxString value;
    wxArrayString cols;

    if (!IsCustom()) return;

    HasCustomData = true;
    if (customChannelData.IsEmpty())
    {
        ResizeCustomGrid();
        return;
    }

    wxArrayString rows=wxSplit(customChannelData,';');
    for(size_t row=0; row < rows.size(); row++)
    {
        if (row >= GridCustom->GetNumberRows()) GridCustom->AppendRows();
        cols=wxSplit(rows[row],',');
        for(size_t col=0; col < cols.size(); col++)
        {
            if (col >= GridCustom->GetNumberCols()) GridCustom->AppendCols();
            value=cols[col];
            if (!value.IsEmpty() && value != "0")
            {
                GridCustom->SetCellValue(row,col,value);
            }
        }
    }
    SpinCtrl_parm1->SetValue(GridCustom->GetNumberCols());
    SpinCtrl_parm2->SetValue(GridCustom->GetNumberRows());
}


int ModelDialog::GetCustomMaxChannel()
{
    // find max node number
    int numCols=GridCustom->GetNumberCols();
    int numRows=GridCustom->GetNumberRows();
    long val,maxval=0;
    wxString valstr;
    for(int row=0; row < numRows; row++)
    {
        for(int col=0; col<numCols; col++)
        {
            valstr = GridCustom->GetCellValue(row,col);
            if (valstr.ToLong(&val))
            {
                maxval=std::max(val,maxval);
            }
        }
    }
    return maxval;
}

// for models that are not custom
int ModelDialog::GetChannelsPerStringStd()
{
    wxString StringType=Choice_StringType->GetStringSelection();
    wxString DisplayAs=Choice_DisplayAs->GetStringSelection();
    if ("Arches" == DisplayAs) {
        int chanCountPerString = ModelClass::GetNodeChannelCount(StringType);
        return chanCountPerString * SpinCtrl_parm2->GetValue();
    }
    int chanCountPerString = ModelClass::GetNodeChannelCount(StringType);
    if (chanCountPerString != 3) {
        return chanCountPerString;
    }
    if (ModelClass::HasSingleNode(StringType)) return 3;
    if (DisplayAs == "Window Frame")
    {
        return (SpinCtrl_parm1->GetValue()+2*SpinCtrl_parm2->GetValue()+SpinCtrl_parm3->GetValue())*3;
    }
    else
    {
        return SpinCtrl_parm2->GetValue()*3;
    }
}


int ModelDialog::GetNumberOfStrings()
{
    wxString DisplayAs=Choice_DisplayAs->GetStringSelection();
    return (ModelClass::HasOneString(DisplayAs)) ? 1 : SpinCtrl_parm1->GetValue();
}


void ModelDialog::UpdateLabels()
{
    wxString DisplayAs=Choice_DisplayAs->GetStringSelection();
    wxString StringType=Choice_StringType->GetStringSelection();
    wxString NodeLabel = ModelClass::HasSingleChannel(StringType) ? _("lights") : _("RGB Nodes");
    wxString s;

    ExtraParameterLabel->Hide();
    StarSizes->Hide();
    TreeFirstStringForExport->Hide();

    if (StringType == "Single Color Custom") {
        ColorPicker->Enable(true);
        ColorPicker->Show();
    } else {
        ColorPicker->Enable(false);
        ColorPicker->Hide();
    }

    if (DisplayAs == "Arches")
    {
        StaticText_Strings->SetLabelText(_("# of Arches"));
        s=_("# of ") + (ModelClass::HasSingleChannel(StringType) ? "Segments" : "Nodes") + _(" per Arch");
        StaticText_Nodes->SetLabelText(s);
        StaticText_Strands->SetLabelText(_("# of lights per ") + (ModelClass::HasSingleChannel(StringType) ? "Segment" : "Node"));
        //SpinCtrl_parm3->SetValue(1);
        SpinCtrl_parm3->Enable(true);
    }
    else if (DisplayAs == "Circle")
    {
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        s=_("# of ") + NodeLabel + _(" per String");
        StaticText_Nodes->SetLabelText(s);
        StaticText_Strands->SetLabelText(_("Center %"));
        SpinCtrl_parm3->Enable(true);
        ExtraParameterLabel->SetLabel("Circle Sizes (Outer to Inner)");
        ExtraParameterLabel->Show();
        StarSizes->Show();

    }
    else if (DisplayAs == "Tree 360" || DisplayAs == "Tree 270" || DisplayAs == "Sphere 360" || DisplayAs == "Sphere 270")
    {
        ExtraParameterLabel->SetLabel("First Strand for Export");
        ExtraParameterLabel->Show();
        TreeFirstStringForExport->Show();
    }
    else if (DisplayAs == "Window Frame")
    {
        s=_("# of ") + NodeLabel + _(" Top");
        StaticText_Strings->SetLabelText(s);
        s=_("# of ") + NodeLabel + _(" Left/Right");
        StaticText_Nodes->SetLabelText(s);
        s=_("# of ") + NodeLabel + _(" Bottom");
        StaticText_Strands->SetLabelText(s);
        SpinCtrl_parm3->Enable(true);
    }
    else if (DisplayAs == "Star")
    {
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        s=_("# of ") + NodeLabel + _(" per String");
        StaticText_Nodes->SetLabelText(s);
        StaticText_Strands->SetLabelText(_("# of points"));
        SpinCtrl_parm3->Enable(true);
        ExtraParameterLabel->SetLabel("Star Layer Sizes");
        ExtraParameterLabel->Show();
        StarSizes->Show();

    }
    else if (DisplayAs == "Single Line" || DisplayAs == "Wreath")
    {
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        s=_("# of ") + NodeLabel + _(" per String");
        StaticText_Nodes->SetLabelText(s);
        StaticText_Strands->SetLabelText(_("n/a"));
        SpinCtrl_parm3->SetValue(1);
        SpinCtrl_parm3->Enable(false);
    }
    else if (DisplayAs == "Custom")
    {
        StaticText_Strings->SetLabelText(_("Model Width"));
        StaticText_Nodes->SetLabelText(_("Model Height"));
        StaticText_Strands->SetLabelText(_("n/a"));
        SpinCtrl_parm3->SetValue(1);
        SpinCtrl_parm3->Enable(false);
    }
    else
    {
        // matrix or tree or wreath
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        s=_("# of ") + NodeLabel + _(" per String");
        StaticText_Nodes->SetLabelText(s);
        StaticText_Strands->SetLabelText(_("# of Strands per String"));
        SpinCtrl_parm3->Enable(true);
    }
    UpdateStartChannels();
    bool CustomFlag = IsCustom();
    GridCustom->Show(CustomFlag);

    // set start corner text
    if (DisplayAs == "Wreath" || DisplayAs == "Star")
    {
        RadioButton_BotRight->SetLabelText(_("Btm ctr, CCW"));
        RadioButton_TopRight->SetLabelText(_("Top ctr, CW"));
        RadioButton_BotLeft->SetLabelText (_("Btm ctr, CW"));
        RadioButton_TopLeft->SetLabelText (_("Top ctr, CCW"));
    }
    else if (CustomFlag)
    {
        RadioButton_BotRight->SetLabelText(_("n/a"));
        RadioButton_TopRight->SetLabelText(_("n/a"));
        RadioButton_BotLeft->SetLabelText (_("n/a"));
        RadioButton_TopLeft->SetLabelText (_("n/a"));
    }
    else
    {
        RadioButton_BotRight->SetLabelText(_("Bottom Right"));
        RadioButton_TopRight->SetLabelText(_("Top Right"));
        RadioButton_BotLeft->SetLabelText (_("Bottom Left"));
        RadioButton_TopLeft->SetLabelText (_("Top Left"));
    }
    RadioButton_BotRight->Enable(!CustomFlag);
    RadioButton_TopRight->Enable(!CustomFlag);
    RadioButton_BotLeft->Enable(!CustomFlag);
    RadioButton_TopLeft->Enable(!CustomFlag);
    if (CustomFlag && !HasCustomData) ResizeCustomGrid();

    LeftGridSizer->RecalcSizes();
    LeftGridSizer->Layout();
    OuterSizer->RecalcSizes();
    OuterSizer->Layout();
    Layout();
}


void ModelDialog::OnChoice_DisplayAsSelect(wxCommandEvent& event)
{
    UpdateLabels();
}

void ModelDialog::OncbIndividualStartNumbersClick(wxCommandEvent& event)
{
    UpdateStartChannels();
}

void ModelDialog::UpdateStartChannels()
{
    int StringStartChan,StringEndChan;
    long StringStartChanLong,startNetwork;
    wxString tmpStr;
    int StringCnt = GetNumberOfStrings();
    bool OneString = StringCnt == 1;
    int ChannelsPerString = GetChannelsPerStringStd();
    if (IsCustom())
    {
        int maxval = GetCustomMaxChannel();
        switch (ChannelsPerString)
        {
        case 1:
            // traditional strings
            StringCnt = maxval;
            break;
        case 3:
            // dumb rgb
            StringCnt = maxval;
            break;
        case 4:
            //RGBW
            StringCnt = maxval;
            break;
        default:
            // rgb pixels
            ChannelsPerString = maxval*3;
            break;
        }
    }

    // Update number of grid rows
    int curRowCnt = gridStartChannels->GetNumberRows();
    if (StringCnt > curRowCnt )
    {
        gridStartChannels->AppendRows(StringCnt - curRowCnt);
    }
    else if ( StringCnt < curRowCnt )
    {
        gridStartChannels->DeleteRows(StringCnt, curRowCnt - StringCnt);
    }

    // if only 1 string, then disable individual string start channels
    if (OneString) cbIndividualStartNumbers->SetValue(false);
    cbIndividualStartNumbers->Enable(!OneString);

    // update grid
    if(cbIndividualStartNumbers->IsChecked())
    {
        SpinCtrl_StartChannel->Enable(false);
        OutputSpinCtrl->Enable(false);

        // update end channel numbers only
        for (int stringnum=0; stringnum<StringCnt; stringnum++)
        {
            tmpStr = gridStartChannels->GetCellValue(stringnum,0);
            wxString sNet = "";
            wxString pfx = "";
            if (tmpStr.Contains(":")) {
                sNet = tmpStr.SubString(0, tmpStr.Find(":")-1);
                if (sNet.ToLong(&startNetwork) && startNetwork > 0)
                {
                    int endNetwork;
                    int endChannel;
                    startNetwork--; // Zero based index
                    pfx = tmpStr.SubString(0, tmpStr.Find(":"));
                    tmpStr = tmpStr.SubString(tmpStr.Find(":") + 1, tmpStr.size());
                    if (tmpStr.ToLong(&StringStartChanLong) && StringStartChanLong > 0)
                    {
                        if(netInfo->GetEndNetworkAndChannel(startNetwork,(int)StringStartChanLong,ChannelsPerString,endNetwork,endChannel))
                        {
                            gridStartChannels->SetCellValue(stringnum,1,wxString::Format("%i:%i",endNetwork+1,endChannel)); //endNetwork is zero based
                        }
                        else
                        {
                            gridStartChannels->SetCellValue(stringnum,1,wxString::Format("Invalid"));
                        }
                    }
                    else
                    {
                        gridStartChannels->SetCellValue(stringnum,1,wxString::Format("Invalid"));
                    }
                }
            }
            else
            {
                if (tmpStr.ToLong(&StringStartChanLong) && StringStartChanLong > 0)
                {
                    StringEndChan=StringStartChanLong + ChannelsPerString - 1;
                    gridStartChannels->SetCellValue(stringnum,1, pfx + wxString::Format("%i",StringEndChan));
                }
            }
        }
        SetReadOnly(false);
    }
    else
    {
        SpinCtrl_StartChannel->Enable(true);
        OutputSpinCtrl->Enable(true);

        // update start and end channel numbers
        int startchan = SpinCtrl_StartChannel->GetValue();
        wxString pfx = "";
        if (OutputSpinCtrl->GetValue() > 1)
        {
            wxString sNet = "";
            wxString pfx = "";
            int endNetwork;
            int endChannel;
            int sNetwork;
            sNetwork = OutputSpinCtrl->GetValue();
            sNetwork--;  //0 based
            for (int stringnum=0; stringnum<StringCnt; stringnum++)
            {
                if(netInfo->GetEndNetworkAndChannel(sNetwork,startchan,ChannelsPerString,endNetwork,endChannel))
                {
                    gridStartChannels->SetCellValue(stringnum,0, pfx + wxString::Format("%i:%i",sNetwork + 1, startchan));
                    gridStartChannels->SetCellValue(stringnum,1, wxString::Format("%i:%i",endNetwork + 1,endChannel));
                    netInfo->GetStartNetworkAndChannelFromEndInfo(endNetwork,endChannel,sNetwork,startchan);
                }
                else
                {
                    gridStartChannels->SetCellValue(stringnum,0, wxString::Format("Invalid"));
                    gridStartChannels->SetCellValue(stringnum,1, wxString::Format("Invalid"));
                }
            }
        }
        else
        {
            for (int stringnum=0; stringnum<StringCnt; stringnum++)
            {
                StringStartChan=startchan + (stringnum*ChannelsPerString);
                StringEndChan=StringStartChan + ChannelsPerString - 1;
                gridStartChannels->SetCellValue(stringnum,0, pfx + wxString::Format("%i",StringStartChan));
                gridStartChannels->SetCellValue(stringnum,1, pfx + wxString::Format("%i",StringEndChan));
            }
        }
        SetReadOnly(true);
    }

}

void ModelDialog::SetReadOnly(bool readonly)
{
    int ii;

    for(ii=0; ii < gridStartChannels->GetNumberRows(); ii++)
    {
        gridStartChannels->SetReadOnly(ii,0,readonly);
        //End channel is always read only.
        gridStartChannels->SetReadOnly(ii,1,true);
    }
}
void ModelDialog::OnSpinCtrl_parm1Change(wxSpinEvent& event)
{
    if (IsCustom())
    {
        ResizeCustomGrid();
    }
    else
    {
        UpdateStartChannels();
    }
}

void ModelDialog::OnSpinCtrl_parm2Change(wxSpinEvent& event)
{
    if (IsCustom())
    {
        ResizeCustomGrid();
    }
    else
    {
        UpdateStartChannels();
    }
}

void ModelDialog::OnSpinCtrl_StartChannelChange(wxSpinEvent& event)
{
    UpdateStartChannels();
}


void ModelDialog::OngridStartChannelsCellChange(wxGridEvent& event)
{
    int col = event.GetCol();
    if (col==0)
    {
        UpdateStartChannels();
    }
    event.Skip();
}

// does not update name
void ModelDialog::UpdateXml(wxXmlNode* e)
{
    int ii;
    long numStrings;
    wxString tempStr;
    if(e->HasAttribute("Advanced"))
    {
        e->DeleteAttribute("Advanced");
        tempStr = e->GetAttribute("parm1");
        tempStr.ToLong(&numStrings);
        for(ii=0; ii < numStrings; ii++)
        {
            e->DeleteAttribute(ModelClass::StartChanAttrName(ii));
        }
    }
    if (e->HasAttribute("CustomModel"))
    {
        e->DeleteAttribute("CustomModel");
    }
    if (cbIndividualStartNumbers->IsChecked())
    {
        e->AddAttribute("Advanced", "1");
        for(ii=0; ii < gridStartChannels->GetNumberRows(); ii++)
        {
            e->AddAttribute(ModelClass::StartChanAttrName(ii),gridStartChannels->GetCellValue(ii,0));
        }
    }
    if (e->HasAttribute("StartSide")) e->DeleteAttribute("StartSide");
    e->DeleteAttribute("DisplayAs");
    e->DeleteAttribute("StringType");
    e->DeleteAttribute("CustomColor");
    e->DeleteAttribute("parm1");
    e->DeleteAttribute("parm2");
    e->DeleteAttribute("parm3");
    e->DeleteAttribute("ModelBrightness");
    e->DeleteAttribute("StartChannel");
    e->DeleteAttribute("Order");
    e->DeleteAttribute("Dir");
    e->DeleteAttribute("Antialias");
    e->DeleteAttribute("PixelSize");
    e->DeleteAttribute("BlackTransparency");
    e->DeleteAttribute("PreviewBrightness");
    e->DeleteAttribute("Transparency");
    if (e->HasAttribute("starSizes")) e->DeleteAttribute("starSizes");
    if (e->HasAttribute("circleSizes")) e->DeleteAttribute("circleSizes");
    e->DeleteAttribute("exportFirstStrand");
    e->DeleteAttribute("NodeNames");
    e->DeleteAttribute("StrandNames");
    e->AddAttribute("DisplayAs", Choice_DisplayAs->GetStringSelection());
    e->AddAttribute("StringType", Choice_StringType->GetStringSelection());
    if (Choice_DisplayAs->GetStringSelection() == "Star") {
        e->AddAttribute("starSizes", StarSizes->GetValue());
    }
    if (Choice_DisplayAs->GetStringSelection() == "Circle") {
        e->AddAttribute("circleSizes", StarSizes->GetValue());
    }
    if (Choice_DisplayAs->GetStringSelection() == "Tree 360"
        || Choice_DisplayAs->GetStringSelection() == "Tree 270") {
        e->AddAttribute("exportFirstStrand", wxString::Format("%d",TreeFirstStringForExport->GetValue()));
    }
    e->AddAttribute("parm1", wxString::Format("%d",SpinCtrl_parm1->GetValue()));
    e->AddAttribute("parm2", wxString::Format("%d",SpinCtrl_parm2->GetValue()));
    e->AddAttribute("parm3", wxString::Format("%d",SpinCtrl_parm3->GetValue()));
    wxString stch = wxString::Format("%d",SpinCtrl_StartChannel->GetValue());
    if (OutputSpinCtrl->GetValue() > 1) {
        stch = wxString::Format("%d:",OutputSpinCtrl->GetValue()) + stch;
    }
    e->AddAttribute("StartChannel", stch);
    //e->AddAttribute("Order", Choice_Order->GetStringSelection());
    if (RadioButton_TopLeft->GetValue() || RadioButton_TopRight->GetValue() )
        e->AddAttribute("StartSide","T");
    else
        e->AddAttribute("StartSide","B");
    if (RadioButton_TopLeft->GetValue() || RadioButton_BotLeft->GetValue() )
        e->AddAttribute("Dir","L");
    else
        e->AddAttribute("Dir","R");


    if (ColorPicker->IsEnabled()) {
        e->AddAttribute("CustomColor", xlColor(ColorPicker->GetColour()));
    }
    e->AddAttribute("Antialias", wxString::Format("%d", pixelStyle));
    e->AddAttribute("PixelSize", wxString::Format("%d", pixelSize));
    e->AddAttribute("Transparency", wxString::Format("%d", transparency));
    if (blackTransparency > 0) {
        e->AddAttribute("BlackTransparency", wxString::Format("%d", blackTransparency));
    }

    if (Choice_DisplayAs->GetStringSelection() == "Custom")
    {
        e->AddAttribute("CustomModel",GetCustomGridData());
    }
    if ("" != nodeNames) {
        e->AddAttribute("NodeNames", nodeNames);
    }
    if ("" != strandNames) {
        e->AddAttribute("StrandNames", strandNames);
    }
    ModelClass::SetMyDisplay(e,CheckBox_MyDisplay->GetValue());


    wxXmlNode *f = e->GetChildren();
    while (f != nullptr) {
        if ("faceInfo" == f->GetName() || "dimmingCurve" == f->GetName()) {
            e->RemoveChild(f);
            delete f;
            f = e->GetChildren();
        } else {
            f = f->GetNext();
        }
    }
    if (!faceInfo.empty()) {
        for (std::map<wxString, std::map<wxString,wxString> >::iterator it = faceInfo.begin(); it != faceInfo.end(); it++) {
            f = new wxXmlNode(e, wxXML_ELEMENT_NODE , "faceInfo");
            wxString name = it->first;
            f->AddAttribute("Name", name);
            for (std::map<wxString,wxString>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                f->AddAttribute(it2->first, it2->second);
            }
        }
    }
    if (!dimmingInfo.empty()) {
        f = new wxXmlNode(e, wxXML_ELEMENT_NODE , "dimmingCurve");
        for (std::map<wxString, std::map<wxString,wxString> >::iterator it = dimmingInfo.begin(); it != dimmingInfo.end(); it++) {
            wxXmlNode *dc = new wxXmlNode(f, wxXML_ELEMENT_NODE , it->first);
            for (std::map<wxString,wxString>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                dc->AddAttribute(it2->first, it2->second);
            }
        }
    }
}

void ModelDialog::SetFromXml(wxXmlNode* e, NetInfoClass *ni, const wxString& NameSuffix)
{
    netInfo = ni;
    long n;
    wxString name, direction, startSide, tempStr;
    name=e->GetAttribute("name") + NameSuffix;
    TextCtrl_Name->SetValue(name);
    Choice_DisplayAs->SetStringSelection(e->GetAttribute("DisplayAs"));
    Choice_StringType->SetStringSelection(e->GetAttribute("StringType","RGB Nodes"));
    SpinCtrl_parm1->SetValue(e->GetAttribute("parm1"));
    SpinCtrl_parm2->SetValue(e->GetAttribute("parm2"));
    SpinCtrl_parm3->SetValue(e->GetAttribute("parm3"));
    if(e->HasAttribute("starSizes")) {
        StarSizes->SetValue(e->GetAttribute("starSizes"));
    }
    if(e->HasAttribute("circleSizes")) {
        StarSizes->SetValue(e->GetAttribute("circleSizes"));
    }

    SpinCtrl_StartChannel->Enable(true);
    OutputSpinCtrl->Enable(true);

    wxString stch = e->GetAttribute("StartChannel");
    if (stch.Contains(":")) {
        wxString o = stch.SubString(0, stch.Find(":")-1);
        OutputSpinCtrl->SetValue(o);
        stch = stch.SubString(stch.Find(":") + 1, stch.size());
    } else {
        OutputSpinCtrl->SetValue(1);
    }
    SpinCtrl_StartChannel->SetValue(stch);
    if (e->GetAttribute("exportFirstStrand") == "") {
        TreeFirstStringForExport->SetValue("1");
    } else {
        TreeFirstStringForExport->SetValue(e->GetAttribute("exportFirstStrand"));
    }
    if (e->GetAttribute("CustomColor") != "") {
        xlColor c(e->GetAttribute("CustomColor"));
        ColorPicker->SetColour(c.asWxColor());
    }
    //Choice_Order->SetStringSelection(e->GetAttribute("Order"));
    tempStr=e->GetAttribute("Antialias","0");
    tempStr.ToLong(&n);
    pixelStyle = n;
    tempStr=e->GetAttribute("PixelSize","2");
    tempStr.ToLong(&n);
    pixelSize = n;
    tempStr=e->GetAttribute("Transparency","0");
    tempStr.ToLong(&n);
    transparency = n;
    blackTransparency = wxAtoi(e->GetAttribute("BlackTransparency", "0"));

    nodeNames = e->GetAttribute("NodeNames");
    strandNames = e->GetAttribute("StrandNames");

    direction=e->GetAttribute("Dir");
    if(e->HasAttribute("StartSide"))
    {
        startSide=e->GetAttribute("StartSide");
    }
    else
    {
        startSide = "B";
    }
    if(e->HasAttribute("Advanced"))
    {
        cbIndividualStartNumbers->SetValue(true);
        SpinCtrl_StartChannel->Enable(false);
        OutputSpinCtrl->Enable(false);
        tempStr = e->GetAttribute("parm1");
        tempStr.ToLong(&n);  // number of strings
        for(int ii=0; ii < n; ii++)
        {
            gridStartChannels->AppendRows();
            gridStartChannels->SetCellValue(ii,0,e->GetAttribute(ModelClass::StartChanAttrName(ii)));
        }
    }

    if (direction == "R" )
    {
        if(startSide == "B")
            RadioButton_BotRight->SetValue(true);
        else
            RadioButton_TopRight->SetValue(true);
    }
    else
    {
        if(startSide == "B")
            RadioButton_BotLeft->SetValue(true);
        else
            RadioButton_TopLeft->SetValue(true);
    }
    if (e->HasAttribute("CustomModel"))
    {
        e->GetAttribute("CustomModel",&tempStr);
        SetCustomGridData(tempStr);
    }
    CheckBox_MyDisplay->SetValue(ModelClass::IsMyDisplay(e));

    wxFont font = GridCustom->GetDefaultCellFont();
    GridCustom->SetRowMinimalAcceptableHeight(5); //don't need to read text, just see the shape
    GridCustom->SetColMinimalAcceptableWidth(5); //don't need to read text, just see the shape
    for (int c = 0; c < GridCustom->GetCols(); ++c)
        GridCustom->SetColSize(c, 2 * font.GetPixelSize().y); //GridCustom->GetColSize(c) * 4/5);
    for (int r = 0; r < GridCustom->GetRows(); ++r)
        GridCustom->SetRowSize(r, int(1.5 * (float)font.GetPixelSize().y)); //GridCustom->GetRowSize(r) * 4/5);
    font = GridCustom->GetLabelFont();
    GridCustom->SetColLabelSize(int(1.5 * (float)font.GetPixelSize().y));

    UpdateLabels();

    faceInfo.clear();
    dimmingInfo.clear();

    wxXmlNode *f = e->GetChildren();
    while (f != nullptr) {
        if ("faceInfo" == f->GetName()) {
            wxString name = f->GetAttribute("Name");
            wxString type = f->GetAttribute("Type", "SingleNode");
            if (name == "") {
                name = type;
                f->DeleteAttribute("Name");
                f->AddAttribute("Name", type);
            }
            if (!(type == "SingleNode" || type == "NodeRange" || type == "Matrix")) {
                if (type == "Coro") {
                    type = "SingleNode";
                } else {
                    type = "Matrix";
                }
                f->DeleteAttribute("Type");
                f->AddAttribute("Type", type);
            }
            wxXmlAttribute *att = f->GetAttributes();
            while (att != nullptr) {
                if (att->GetName() != "Name") {
                    faceInfo[name][att->GetName()] = att->GetValue();
                }
                att = att->GetNext();
            }
        } else if ("dimmingCurve" == f->GetName()) {
            wxXmlNode *dc = f->GetChildren();
            while (dc != nullptr) {
                wxString name = dc->GetName();
                wxXmlAttribute *att = dc->GetAttributes();
                while (att != nullptr) {
                    dimmingInfo[name][att->GetName()] = att->GetValue();
                    att = att->GetNext();
                }
                dc = dc->GetNext();
            }
        }
        f = f->GetNext();
    }
    if(e->HasAttribute("ModelBrightness") && dimmingInfo.empty()) {
        wxString b = e->GetAttribute("ModelBrightness","0");
        dimmingInfo["all"]["gamma"] = "1.0";
        dimmingInfo["all"]["brightness"] = b;
    }
}

void ModelDialog::OnButtonCustomModelHelpClick(wxCommandEvent& event)
{
    wxMessageBox(_("To create a custom model, set 'Display As' to 'Custom';\nthen set the model width and model height values.\n\nA custom model allows you to represent almost any display element \ncreated from RGB lights. If your element has 12 RGB nodes in it, then \nyou will need to place the numbers 1 through 12 in the grid. \nPlace the numbers so that they are in the shape of your display \nelement. If you enter a number and then need to erase it, enter a 0.\n\nNode 1 will be assigned:\n  StartChannel\n  StartChannel+1\n  StartChannel+2\nNode 2 will be assigned:\n  StartChannel+3\n  StartChannel+4\n  StartChannel+5\netc.\n\nFor example, to model a candy cane with 12 nodes, you could \nstart with a grid 4 columns wide and 10 rows high. You would place the \nnumbers 1-9 up the right-hand side, 10 and 11 would go in the middle \ncells in the top row, and then 12 would go in column A, row 2.\n\n     11 10\n12           9\n               8\n               7\n               6\n               5\n               4\n               3\n               2\n               1"));
}

void ModelDialog::OnChoice_StringTypeSelect(wxCommandEvent& event)
{
    UpdateLabels();
}

void ModelDialog::OnGridCustomCellChange(wxGridEvent& event)
{
    UpdateStartChannels();
}

#ifdef __WXOSX__
wxString GetOSXFormattedClipboardData();
#endif


void ModelDialog::OnBitmapButtonCustomPasteClick(wxCommandEvent& event)
{
    wxString copy_data;
    wxString cur_line;
    wxArrayString fields;
    int i,k,fieldnum;
    long val;

#ifdef __WXOSX__
    //wxDF_TEXT gets a very strange formatted string from the clipboard if using Numbers
    //native ObjectC code can get the proper tab formatted version.
    copy_data = GetOSXFormattedClipboardData();
#endif

    if (copy_data == "") {
        if (wxTheClipboard->Open())
        {
            if (wxTheClipboard->IsSupported(wxDF_TEXT))
            {
                wxTextDataObject data;

                if (wxTheClipboard->GetData(data))
                {
                    copy_data = data.GetText();
                }
                else
                {
                    wxMessageBox(_("Unable to copy data from clipboard."), _("Error"));
                }
            }
            else
            {
                wxMessageBox(_("Non-Text data in clipboard."), _("Error"));
            }
            wxTheClipboard->Close();
        }
        else
        {
            wxMessageBox(_("Error opening clipboard."), _("Error"));
            return;
        }
    }

    i = GridCustom->GetGridCursorRow();
    k = GridCustom->GetGridCursorCol();
    int numrows=GridCustom->GetNumberRows();
    int numcols=GridCustom->GetNumberCols();
    bool errflag=false;
    wxString errdetails; //-DJ

    copy_data.Replace("\r\r", "\n");
    copy_data.Replace("\r\n", "\n");
    copy_data.Replace("\r", "\n");

    do
    {
        cur_line = copy_data.BeforeFirst('\n');
        copy_data = copy_data.AfterFirst('\n');
        fields = wxSplit(cur_line, (cur_line.Find(',') != wxNOT_FOUND)? ',': '\t'); //allow comma or tab delim -DJ
        for(fieldnum=0; fieldnum<fields.Count(); fieldnum++)
        {
            if (i < numrows && k+fieldnum < numcols)
            {
                wxString field = fields[fieldnum].Trim(true).Trim(false);
                if (field.IsEmpty() || field.ToLong(&val))
                {
                    GridCustom->SetCellValue(i, k+fieldnum, fields[fieldnum].Trim(true).Trim(false)); //strip surrounding spaces -DJ
                }
                else
                {
                    errflag=true;
                    errdetails += wxString::Format("\n'%s' row %d/col %d of %d", fields[fieldnum].c_str(), i - GridCustom->GetGridCursorRow(), fieldnum, fields.Count()); //tell the user what was wrong; show relative row#, col# (more user friendly) -DJ
                }
            }
        }
        i++;
    }
    while (copy_data.IsEmpty() == false);
    UpdateStartChannels();
    if (errflag)
    {
        wxMessageBox(_("One or more of the values were not pasted because they did not contain a number") + errdetails,_("Paste Error")); //-DJ
    }
}

// pass true for cutting, false for copying
void ModelDialog::CutOrCopyToClipboard(bool IsCut)
{
    int i,k;
    wxString copy_data;
    bool something_in_this_line;

    for (i=0; i< GridCustom->GetRows(); i++)        // step through all lines
    {
        something_in_this_line = false;             // nothing found yet
        for (k=0; k<GridCustom->GetCols(); k++)     // step through all colums
        {
            if (GridCustom->IsInSelection(i,k))     // this field is selected!!!
            {
                if (!something_in_this_line)        // first field in this line => may need a linefeed
                {
                    if (!copy_data.IsEmpty())       // ... if it is not the very first field
                    {
                        copy_data += "\n";     // next LINE
                    }
                    something_in_this_line = true;
                }
                else                                    // if not the first field in this line we need a field seperator (TAB)
                {
                    copy_data += "\t";  // next COLUMN
                }
                copy_data += GridCustom->GetCellValue(i,k);    // finally we need the field value
                if (IsCut) GridCustom->SetCellValue(i,k,wxEmptyString);
            }
        }
    }

    if (wxTheClipboard->Open())
    {
        if (!wxTheClipboard->SetData(new wxTextDataObject(copy_data)))
        {
            wxMessageBox(_("Unable to copy data to clipboard."), _("Error"));
        }
        wxTheClipboard->Close();
    }
    else
    {
        wxMessageBox(_("Error opening clipboard."), _("Error"));
    }
}

void ModelDialog::OnBitmapButtonCustomCopyClick(wxCommandEvent& event)
{
    CutOrCopyToClipboard(false);
}

void ModelDialog::OnBitmapButtonCustomCutClick(wxCommandEvent& event)
{
    CutOrCopyToClipboard(true);
    UpdateStartChannels();
}

void ModelDialog::OnSpinCtrl_parm3Change(wxSpinEvent& event)
{
    UpdateStartChannels();
}

class myGrid: public wxGrid
{
public:
    int GetColWidth(int col) const { return wxGrid::GetColWidth(col); }
    int GetColLeft(int col) const { return wxGrid::GetColLeft(col); }
    int GetColRight(int col) const { return wxGrid::GetColRight(col); }
    int GetRowTop(int row) const { return wxGrid::GetRowTop(row); }
    int GetRowBottom(int row) const { return wxGrid::GetRowBottom(row); }
    int GetRowHeight(int row) const { return wxGrid::GetRowHeight(row); }
};


void ModelDialog::OnButton_CustomModelZoomOutClick(wxCommandEvent& event)
{
    GridCustom->BeginBatch();
    wxFont font = GridCustom->GetLabelFont();
//    debug(10, "font: was size = %d, %d, pt %d, cell w %d, min w %d", font.GetPixelSize().x, font.GetPixelSize().y, font.GetPointSize(), ((myGrid*)GridCustom)->GetColWidth(0), GridCustom->GetColMinimalAcceptableWidth());
    font.MakeSmaller();
    GridCustom->SetLabelFont(font);
    font = GridCustom->GetDefaultCellFont();
    font.MakeSmaller();
    GridCustom->SetDefaultCellFont(font);
//    for (int r = 0; r < GridCustom->GetRows(); ++r)
//        for (int c = 0; c < GridCustom->GetCols(); ++c)
//            GridCustom->GetCellFont(r, c).MakeSmaller();
    GridCustom->SetRowMinimalAcceptableHeight(5); //don't need to read text, just see the shape
    GridCustom->SetColMinimalAcceptableWidth(5); //don't need to read text, just see the shape
//    GridCustom->AutoSizeColumns(true);
//    GridCustom->AutoSizeRows(true);
    for (int c = 0; c < GridCustom->GetCols(); ++c)
        GridCustom->SetColSize(c, 2 * font.GetPixelSize().y); //GridCustom->GetColSize(c) * 4/5);
    for (int r = 0; r < GridCustom->GetRows(); ++r)
        GridCustom->SetRowSize(r, int(1.5 * (float)font.GetPixelSize().y)); //GridCustom->GetRowSize(r) * 4/5);
//    debug(10, "font-: is now size = %d, %d, pt %d, cell w %d, min w %d", font.GetPixelSize().x, font.GetPixelSize().y, font.GetPointSize(), ((myGrid*)GridCustom)->GetColWidth(0), GridCustom->GetColMinimalAcceptableWidth());
    GridCustom->EndBatch();
}

//allow larger grids to be seen more easily: -DJ
void ModelDialog::OnButton_CustomModelZoomInClick(wxCommandEvent& event)
{
    GridCustom->BeginBatch();
    wxFont font = GridCustom->GetLabelFont();
//    debug(10, "font: was size = %d, %d, pt %d, cell w %d, min w %d", font.GetPixelSize().x, font.GetPixelSize().y, font.GetPointSize(), ((myGrid*)GridCustom)->GetColWidth(0), GridCustom->GetColMinimalAcceptableWidth());
    font.MakeLarger();
    GridCustom->SetLabelFont(font);
    font = GridCustom->GetDefaultCellFont();
    font.MakeLarger();
    GridCustom->SetDefaultCellFont(font);
//    for (int r = 0; r < GridCustom->GetRows(); ++r)
//        for (int c = 0; c < GridCustom->GetCols(); ++c)
//            GridCustom->GetCellFont(r, c).MakeLarger();
//    GridCustom->AutoSizeColumns(true);
//    GridCustom->AutoSizeRows(true);
    for (int c = 0; c < GridCustom->GetCols(); ++c)
        GridCustom->SetColSize(c, 2 * font.GetPixelSize().y); //GridCustom->GetColSize(c) * 5/4);
    for (int r = 0; r < GridCustom->GetRows(); ++r)
        GridCustom->SetRowSize(r, int(1.5 * (float)font.GetPixelSize().y)); //GridCustom->GetRowSize(r) * 5/4);
//    debug(10, "font+: is now size = %d, %d, pt %d, cell w %d, min w %d", font.GetPixelSize().x, font.GetPixelSize().y, font.GetPointSize(), ((myGrid*)GridCustom)->GetColWidth(0), GridCustom->GetColMinimalAcceptableWidth());
    GridCustom->EndBatch();
}

void ModelDialog::OnAppearanceButtonClicked(wxCommandEvent& event)
{
    PixelAppearanceDlg dlg(this);
    dlg.PixelStyleBox->SetSelection(pixelStyle);
    dlg.TransparencySlider->SetValue(transparency);
    dlg.PixelSizeSpinner->SetValue(pixelSize);
    dlg.BlackTransparency->SetValue(blackTransparency);

    dlg.TransparencyText->SetValue(wxString::Format("%d", transparency));
    dlg.BlackTransparencyText->SetValue(wxString::Format("%d", blackTransparency));

    if (dlg.ShowModal() == wxID_OK) {
        pixelStyle = dlg.PixelStyleBox->GetSelection();
        transparency = dlg.TransparencySlider->GetValue();
        pixelSize = dlg.PixelSizeSpinner->GetValue();
        blackTransparency = dlg.BlackTransparency->GetValue();
    }

}

void ModelDialog::OnNamesButtonClick(wxCommandEvent& event)
{
    wxXmlNode xml;
    UpdateXml(&xml);
    ModelClass md;
    md.SetFromXml(&xml, *netInfo);

    StrandNodeNamesDialog dlg(this);
    std::vector<wxString> strands;
    std::vector<wxString> nodes;
    wxString tempstr = strandNames;
    while (tempstr.size() > 0) {
        wxString t2 = tempstr;
        if (tempstr[0] == ',') {
            t2 = "";
            tempstr = tempstr(1, tempstr.length());
        } else if (tempstr.Contains(",")) {
            t2 = tempstr.SubString(0, tempstr.Find(",") - 1);
            tempstr = tempstr.SubString(tempstr.Find(",") + 1, tempstr.length());
        } else {
            tempstr = "";
        }
        strands.push_back(t2);
    }
    if (strands.size() < md.GetNumStrands()) {
        strands.resize(md.GetNumStrands());
    }
    dlg.StrandsGrid->BeginBatch();
    dlg.StrandsGrid->SetMaxSize(dlg.StrandsGrid->GetSize());
    dlg.StrandsGrid->HideColLabels();
    dlg.StrandsGrid->DeleteRows(0, 10);
    dlg.StrandsGrid->AppendRows(strands.size());
    dlg.StrandsGrid->SetRowLabelSize(40);

    for (int x = 0; x < strands.size(); x++) {
        dlg.StrandsGrid->SetCellValue(x, 0, strands[x]);
    }
    dlg.StrandsGrid->EndBatch();

    tempstr=nodeNames;
    nodes.clear();
    while (tempstr.size() > 0) {
        wxString t2 = tempstr;
        if (tempstr[0] == ',') {
            t2 = "";
            tempstr = tempstr(1, tempstr.length());
        } else if (tempstr.Contains(",")) {
            t2 = tempstr.SubString(0, tempstr.Find(",") - 1);
            tempstr = tempstr.SubString(tempstr.Find(",") + 1, tempstr.length());
        } else {
            tempstr = "";
        }
        nodes.push_back(t2);
    }
    if (nodes.size() < md.GetNodeCount()) {
        nodes.resize(md.GetNodeCount());
    }
    dlg.NodesGrid->BeginBatch();
    dlg.NodesGrid->SetMaxSize(dlg.StrandsGrid->GetSize());
    dlg.NodesGrid->HideColLabels();
    dlg.NodesGrid->DeleteRows(0, 10);
    dlg.NodesGrid->SetRowLabelSize(40);

    dlg.NodesGrid->AppendRows(nodes.size());
    for (int x = 0; x < nodes.size(); x++) {
        dlg.NodesGrid->SetCellValue(x, 0, nodes[x]);
    }
    dlg.NodesGrid->EndBatch();

    if (dlg.ShowModal() == wxID_OK) {
        nodeNames.clear();
        for (int x = dlg.NodesGrid->GetNumberRows(); x > 0; x--) {
            if ("" != dlg.NodesGrid->GetCellValue(x-1,0) || nodeNames.size() > 0) {
                if (nodeNames.size() > 0) {
                    nodeNames = "," + nodeNames;
                }
                nodeNames = dlg.NodesGrid->GetCellValue(x-1,0) + nodeNames;
            }
        }
        strandNames.clear();
        for (int x = dlg.StrandsGrid->GetNumberRows(); x > 0; x--) {
            if ("" != dlg.StrandsGrid->GetCellValue(x-1,0) || strandNames.size() > 0) {
                if (strandNames.size() > 0) {
                    strandNames = "," + strandNames;
                }
                strandNames = dlg.StrandsGrid->GetCellValue(x-1,0) + strandNames;
            }
        }
    }
}

void ModelDialog::OnFacesButtonClick(wxCommandEvent& event)
{
    wxXmlNode xml;
    UpdateXml(&xml);
    ModelClass md;
    md.SetFromXml(&xml, *netInfo);

    ModelFaceDialog dlg(this);
    dlg.SetFaceInfo(&md, faceInfo);
    if (dlg.ShowModal()) {
        faceInfo.clear();
        dlg.GetFaceInfo(faceInfo);
    }
}

void ModelDialog::OnDimmingCurvesClick(wxCommandEvent& event)
{
    ModelDimmingCurveDialog d(this);
    d.Init(dimmingInfo);
    if (d.ShowModal()) {
        dimmingInfo.clear();
        d.Update(dimmingInfo);
    }
}
