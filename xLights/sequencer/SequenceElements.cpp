#include "wx/wx.h"
#include <wx/utils.h>
#include <algorithm>
#include <wx/tokenzr.h>
#include <wx/filename.h>

#include "SequenceElements.h"
#include "TimeLine.h"
#include "xLightsMain.h"
#include "LyricsDialog.h"
#include "../xLightsXmlFile.h"


static const wxString STR_EMPTY("");
static const wxString STR_NAME("name");
static const wxString STR_EFFECT("Effect");
static const wxString STR_ELEMENT("Element");
static const wxString STR_EFFECTLAYER("EffectLayer");
static const wxString STR_COLORPALETTE("ColorPalette");
static const wxString STR_NODE("Node");
static const wxString STR_STRAND("Strand");
static const wxString STR_INDEX("index");
static const wxString STR_TYPE("type");
static const wxString STR_TIMING("timing");

static const wxString STR_STARTTIME("startTime");
static const wxString STR_ENDTIME("endTime");
static const wxString STR_PROTECTED("protected");
static const wxString STR_ID("id");
static const wxString STR_REF("ref");
static const wxString STR_PALETTE("palette");
static const wxString STR_LABEL("label");
static const wxString STR_ZERO("0");


SequenceElements::SequenceElements()
: undo_mgr(this)
{
    mSelectedTimingRow = -1;
    mTimingRowCount = 0;
    mMaxRowsDisplayed = 0;
    mFirstVisibleModelRow = 0;
    mModelsNode = nullptr;
    mChangeCount = 0;
    mCurrentView = 0;
    std::vector <Element*> master_view;
    mAllViews.push_back(master_view);  // first view must remain as master view that determines render order
    xframe = nullptr;
    hasPapagayoTiming = false;
}

SequenceElements::~SequenceElements()
{
    ClearAllViews();
}

void SequenceElements::ClearAllViews()
{
    for (int y = 0; y < mAllViews[MASTER_VIEW].size(); y++) {
        delete mAllViews[MASTER_VIEW][y];
    }

    for (int x = 0; x < mAllViews.size(); x++) {
        mAllViews[x].clear();
    }
    mAllViews.clear();
}

void SequenceElements::Clear() {
    ClearAllViews();
    mVisibleRowInformation.clear();
    mRowInformation.clear();
    mSelectedRanges.clear();

    mSelectedTimingRow = -1;
    mTimingRowCount = 0;
    mFirstVisibleModelRow = 0;
    mChangeCount = 0;
    mCurrentView = 0;
    std::vector <Element*> master_view;
    mAllViews.push_back(master_view);
    hasPapagayoTiming = false;
}

void SequenceElements::SetSequenceEnd(int ms)
{
    mSequenceEndMS = ms;
}

EffectLayer* SequenceElements::GetEffectLayer(Row_Information_Struct *s) {

    Element* e = s->element;
    if (s->strandIndex == -1) {
        return e->GetEffectLayer(s->layerIndex);
    } else if (s->nodeIndex == -1) {
        return e->GetStrandLayer(s->strandIndex);
    } else {
        return e->GetStrandLayer(s->strandIndex)->GetNodeLayer(s->nodeIndex);
    }
}

EffectLayer* SequenceElements::GetEffectLayer(int row) {
    if(row==-1) return nullptr;
    return GetEffectLayer(GetRowInformation(row));
}

EffectLayer* SequenceElements::GetVisibleEffectLayer(int row) {
    if(row==-1) return nullptr;
    return GetEffectLayer(GetVisibleRowInformation(row));
}

Element* SequenceElements::AddElement(wxString &name,wxString &type,bool visible,bool collapsed,bool active, bool selected)
{
    if(!ElementExists(name))
    {
        mAllViews[MASTER_VIEW].push_back(new Element(this, name,type,visible,collapsed,active,selected));
        Element *el = mAllViews[MASTER_VIEW][mAllViews[MASTER_VIEW].size()-1];
        IncrementChangeCount(el);
        return el;
    }
    return NULL;
}

Element* SequenceElements::AddElement(int index,wxString &name,wxString &type,bool visible,bool collapsed,bool active, bool selected)
{
    if(!ElementExists(name) && index <= mAllViews[MASTER_VIEW].size())
    {
        mAllViews[MASTER_VIEW].insert(mAllViews[MASTER_VIEW].begin()+index,new Element(this, name,type,visible,collapsed,active,selected));
        Element *el = mAllViews[MASTER_VIEW][index];
        IncrementChangeCount(el);
        return el;
    }
    return NULL;
}

int SequenceElements::GetElementCount(int view)
{
    return mAllViews[view].size();
}

bool SequenceElements::ElementExists(wxString elementName, int view)
{
    for(int i=0;i<mAllViews[view].size();i++)
    {
        if(mAllViews[view][i]->GetName() == elementName)
        {
            return true;
        }
    }
    return false;
}

bool SequenceElements::TimingIsPartOfView(Element* timing, int view)
{
    wxString view_name = GetViewName(view);
    wxArrayString views = wxSplit(timing->GetViews(),',');
    for(int v=0;v<views.size();v++)
    {
        wxString viewName = views[v];
        if( view_name == viewName )
        {
            return true;
        }
    }
    return false;
}

wxString SequenceElements::GetViewName(int which_view)
{
    wxString view_name = "Master View";
    int view_index = 1;
    for(wxXmlNode* view=mViewsNode->GetChildren(); view!=NULL; view=view->GetNext() )
    {
        if( view_index == which_view )
        {
            view_name = view->GetAttribute(STR_NAME);
            break;
        }
        view_index++;
    }
    return view_name;
}

void SequenceElements::SetViewsNode(wxXmlNode* viewsNode)
{
    mViewsNode = viewsNode;
}

void SequenceElements::SetModelsNode(wxXmlNode* node, xLightsFrame *f)
{
    mModelsNode = node;
    xframe = f;
}

void SequenceElements::SetEffectsNode(wxXmlNode* effectsNode)
{
    mEffectsNode = effectsNode;
}

wxString SequenceElements::GetViewModels(wxString viewName)
{
    wxString result="";
    for(wxXmlNode* view=mViewsNode->GetChildren(); view!=NULL; view=view->GetNext() )
    {
        if(view->GetAttribute(STR_NAME)==viewName)
        {
            result = view->GetAttribute("models");
            break;
        }
    }
    return result;
}

Element* SequenceElements::GetElement(const wxString &name)
{
    for(int i=0;i<mAllViews[MASTER_VIEW].size();i++)
    {
        if(name == mAllViews[MASTER_VIEW][i]->GetName())
        {
            return mAllViews[MASTER_VIEW][i];
        }
    }
    return NULL;
}

Element* SequenceElements::GetElement(int index, int view)
{
    if(index < mAllViews[view].size())
    {
        return mAllViews[view][index];
    }
    else
    {
        return nullptr;
    }
}

void SequenceElements::DeleteElement(const wxString &name)
{
    for(wxXmlNode* view=mViewsNode->GetChildren(); view!=NULL; view=view->GetNext() )
    {
        wxString view_models = view->GetAttribute("models");
        wxArrayString all_models = wxSplit(view_models, ',');
        wxArrayString new_models;
        for( int model = 0; model < all_models.size(); model++ )
        {
            if( all_models[model] != name )
            {
                new_models.push_back(all_models[model]);
            }
        }
        view_models = wxJoin(new_models, ',');
        view->DeleteAttribute("models");
        view->AddAttribute("models", view_models);
    }

    // delete element pointer from all views
    for(int i=0;i<mAllViews.size();i++)
    {
        for(int j=0;j<mAllViews[i].size();j++)
        {
            if(name == mAllViews[i][j]->GetName())
            {
                mAllViews[i].erase(mAllViews[i].begin()+j);
                IncrementChangeCount(nullptr);
                break;
            }
        }
    }

    // delete contents of pointer
    for(int j=0;j<mAllViews[MASTER_VIEW].size();j++)
    {
        if(name == mAllViews[MASTER_VIEW][j]->GetName())
        {
            Element *e = mAllViews[MASTER_VIEW][j];
            delete e;
            break;
        }
    }
    PopulateRowInformation();
}

void SequenceElements::DeleteElementFromView(const wxString &name, int view)
{
    // delete element pointer from all views
    for(int j=0;j<mAllViews[view].size();j++)
    {
        if(name == mAllViews[view][j]->GetName())
        {
            mAllViews[view].erase(mAllViews[view].begin()+j);
            break;
        }
    }

    PopulateRowInformation();
}

void SequenceElements::DeleteTimingFromView(const wxString &name, int view)
{
    wxString viewName = GetViewName(view);
    Element* elem = GetElement(name);
    if( elem != nullptr && elem->GetType() == "timing" )
    {
        wxString views = elem->GetViews();
        wxArrayString all_views = wxSplit(views,',');
        int found = -1;
        for( int j = 0; j < all_views.size(); j++ )
        {
            if( all_views[j] == viewName )
            {
                found = j;
                break;
            }
        }
        if( found != -1 )
        {
            all_views.erase(all_views.begin() + found);
            views = wxJoin(all_views, ',');
            elem->SetViews(views);
        }
    }
}

void SequenceElements::RenameModelInViews(const wxString& old_name, const wxString& new_name)
{
    // renames models in any views that have been loaded for a sequence
    for(int view=0; view < mAllViews.size(); view++)
    {
        for(int i=0; i < mAllViews[view].size(); i++)
        {
            if(mAllViews[view][i]->GetName() == old_name)
            {
                mAllViews[view][i]->SetName(new_name);
            }
        }
    }
}

Row_Information_Struct* SequenceElements::GetVisibleRowInformation(int index)
{
    if(index < mVisibleRowInformation.size())
    {
        return &mVisibleRowInformation[index];
    }
    else
    {
        return NULL;
    }
}

Row_Information_Struct* SequenceElements::GetVisibleRowInformationFromRow(int row_number)
{
    for(int i=0;i<mVisibleRowInformation.size();i++)
    {
        if(row_number == mVisibleRowInformation[i].RowNumber)
        {
            return &mVisibleRowInformation[i];
        }
    }
    return NULL;
}

int SequenceElements::GetVisibleRowInformationSize()
{
    return mVisibleRowInformation.size();
}

Row_Information_Struct* SequenceElements::GetRowInformation(int index)
{
    if(index < mRowInformation.size())
    {
        return &mRowInformation[index];
    }
    else
    {
        return NULL;
    }
}

Row_Information_Struct* SequenceElements::GetRowInformationFromRow(int row_number)
{
    for(int i=0;i<mRowInformation.size();i++)
    {
        if(row_number == mRowInformation[i].Index - GetFirstVisibleModelRow())
        {
            return &mRowInformation[i];
        }
    }
    return NULL;
}

int SequenceElements::GetRowInformationSize()
{
    return mRowInformation.size();
}

void SequenceElements::SortElements()
{
    if (mAllViews[mCurrentView].size()>1)
        std::sort(mAllViews[mCurrentView].begin(),mAllViews[mCurrentView].end(),SortElementsByIndex);
}

void SequenceElements::MoveElement(int index,int destinationIndex)
{
    IncrementChangeCount(nullptr);
    if(index<destinationIndex)
    {
        mAllViews[mCurrentView][index]->Index() = destinationIndex;
        for(int i=index+1;i<destinationIndex;i++)
        {
            mAllViews[mCurrentView][i]->Index() = i-1;
        }
    }
    else
    {
        mAllViews[mCurrentView][index]->Index() = destinationIndex;
        for(int i=destinationIndex;i<index;i++)
        {
            mAllViews[mCurrentView][i]->Index() = i+1;
        }
    }
    SortElements();
}

void SequenceElements::LoadEffects(EffectLayer *effectLayer,
                                   const wxString &type,
                                   wxXmlNode *effectLayerNode,
                                   const std::vector<wxString> & effectStrings,
                                   const std::vector<wxString> & colorPalettes) {
    for(wxXmlNode* effect=effectLayerNode->GetChildren(); effect!=NULL; effect=effect->GetNext())
    {
        if (effect->GetName() == STR_EFFECT)
        {
            wxString effectName;
            wxString settings;
            int id = 0;
            int effectIndex = 0;
            long palette = -1;
            bool bProtected=false;

            // Start time
            double startTime;
            effect->GetAttribute(STR_STARTTIME).ToDouble(&startTime);
            startTime = TimeLine::RoundToMultipleOfPeriod(startTime,mFrequency);
            // End time
            double endTime;
            effect->GetAttribute(STR_ENDTIME).ToDouble(&endTime);
            endTime = TimeLine::RoundToMultipleOfPeriod(endTime,mFrequency);
            // Protected
            bProtected = effect->GetAttribute(STR_PROTECTED)=='1'?true:false;
            if(type != STR_TIMING)
            {
                // Name
                effectName = effect->GetAttribute(STR_NAME);
                effectIndex = Effect::GetEffectIndex(effectName);
                // ID
                id = wxAtoi(effect->GetAttribute(STR_ID, STR_ZERO));
                if (effect->GetAttribute(STR_REF) != STR_EMPTY) {
                    settings = effectStrings[wxAtoi(effect->GetAttribute(STR_REF))];
                } else {
                    settings = effect->GetNodeContent();
                }

                wxString tmp;
                if (effect->GetAttribute(STR_PALETTE, &tmp)) {
                    tmp.ToLong(&palette);
                }
            }
            else
            {
                // store timing labels in name attribute
                effectName = effect->GetAttribute(STR_LABEL);

            }
            effectLayer->AddEffect(id,effectIndex,effectName,settings,
                                   palette == -1 ? STR_EMPTY : colorPalettes[palette],
                                   startTime,endTime,EFFECT_NOT_SELECTED,bProtected);
        } else if (effect->GetName() == STR_NODE && effectLayerNode->GetName() == STR_STRAND) {
            EffectLayer* neffectLayer = ((StrandLayer*)effectLayer)->GetNodeLayer(wxAtoi(effect->GetAttribute(STR_INDEX)), true);
            if (effect->GetAttribute(STR_NAME, STR_EMPTY) != STR_EMPTY) {
                ((NodeLayer*)neffectLayer)->SetName(effect->GetAttribute(STR_NAME));
            }

            LoadEffects(neffectLayer, type, effect, effectStrings, colorPalettes);
        }
    }

}
bool SequenceElements::LoadSequencerFile(xLightsXmlFile& xml_file)
{
    wxXmlDocument& seqDocument = xml_file.GetXmlDocument();

    wxXmlNode* root=seqDocument.GetRoot();
    std::vector<wxString> effectStrings;
    std::vector<wxString> colorPalettes;
    Clear();
    for(wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() )
    {
       if (e->GetName() == "DisplayElements")
       {
            for(wxXmlNode* element=e->GetChildren(); element!=NULL; element=element->GetNext() )
            {
                bool active=false;
                bool selected=false;
                bool collapsed=false;
                wxString name = element->GetAttribute(STR_NAME);
                wxString type = element->GetAttribute(STR_TYPE);
                bool visible = element->GetAttribute("visible")=='1'?true:false;

                if (type==STR_TIMING)
                {
                    active = element->GetAttribute("active")=='1'?true:false;
                }
                else
                {
                    collapsed = element->GetAttribute("collapsed")=='1'?true:false;
                }
                Element* elem = AddElement(name,type,visible,collapsed,active,selected);
                if (type==STR_TIMING)
                {
                    wxString views = element->GetAttribute("views", "");
                    elem->SetViews(views);
                }
            }
       }
       else if (e->GetName() == "EffectDB")
       {
           effectStrings.clear();
           for(wxXmlNode* elementNode=e->GetChildren(); elementNode!=NULL; elementNode=elementNode->GetNext() )
           {
               if(elementNode->GetName()==STR_EFFECT)
               {
                   effectStrings.push_back(elementNode->GetNodeContent());
               }
           }
       }
       else if (e->GetName() == "ColorPalettes")
       {
           colorPalettes.clear();
           for(wxXmlNode* elementNode=e->GetChildren(); elementNode!=NULL; elementNode=elementNode->GetNext() )
           {
               if(elementNode->GetName() == STR_COLORPALETTE)
               {
                   colorPalettes.push_back(elementNode->GetNodeContent());
               }
           }
       }
       else if (e->GetName() == "ElementEffects")
        {
            for(wxXmlNode* elementNode=e->GetChildren(); elementNode!=NULL; elementNode=elementNode->GetNext() )
            {
                if(elementNode->GetName()==STR_ELEMENT)
                {
                    Element* element = GetElement(elementNode->GetAttribute(STR_NAME));
                    if (element !=NULL)
                    {
                        // check for fixed timing interval
                        int interval = 0;
                        if( elementNode->GetAttribute(STR_TYPE) == STR_TIMING )
                        {
                            interval = wxAtoi(elementNode->GetAttribute("fixed"));
                        }
                        if( interval > 0 )
                        {
                            element->SetFixedTiming(interval);
                            EffectLayer* effectLayer = element->AddEffectLayer();
                            int time = 0;
                            int end_time = xml_file.GetSequenceDurationMS();
                            int startTime, endTime, next_time;
                            while( time <= end_time )
                            {
                                next_time = (time + interval <= end_time) ? time + interval : end_time;
                                startTime = TimeLine::RoundToMultipleOfPeriod(time,mFrequency);
                                endTime = TimeLine::RoundToMultipleOfPeriod(next_time,mFrequency);
                                effectLayer->AddEffect(0,0,wxEmptyString,wxEmptyString,"",startTime,endTime,EFFECT_NOT_SELECTED,false);
                                time += interval;
                            }
                        }
                        else
                        {
                            for(wxXmlNode* effectLayerNode=elementNode->GetChildren(); effectLayerNode!=NULL; effectLayerNode=effectLayerNode->GetNext())
                            {
                                if (effectLayerNode->GetName() == STR_EFFECTLAYER || effectLayerNode->GetName() == STR_STRAND)
                                {
                                    EffectLayer* effectLayer = NULL;
                                    if (effectLayerNode->GetName() == STR_EFFECTLAYER) {
                                        effectLayer = element->AddEffectLayer();
                                    } else {
                                        effectLayer = element->GetStrandLayer(wxAtoi(effectLayerNode->GetAttribute(STR_INDEX)), true);
                                        if (effectLayerNode->GetAttribute(STR_NAME, STR_EMPTY) != STR_EMPTY) {
                                            ((StrandLayer*)effectLayer)->SetName(effectLayerNode->GetAttribute(STR_NAME));
                                        }
                                    }
                                    LoadEffects(effectLayer, elementNode->GetAttribute(STR_TYPE), effectLayerNode, effectStrings, colorPalettes);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Select view and set current view models as visible
    int last_view = xml_file.GetLastView();
    for(wxXmlNode* view=mViewsNode->GetChildren(); view!=NULL; view=view->GetNext() )
    {
        wxString viewName = view->GetAttribute(STR_NAME);
        wxString models = view->GetAttribute("models");
        std::vector <Element*> new_view;
        mAllViews.push_back(new_view);
        int view_index = mAllViews.size()-1;
        if( view_index == last_view )
        {
            AddMissingModelsToSequence(models);
            PopulateView(models, view_index);
            SetCurrentView(view_index);
        }
    }

    if (mModelsNode != nullptr) {
        PopulateRowInformation();
    }
    // Set to the first model/view
    mFirstVisibleModelRow = 0;
    return true;
}

void SequenceElements::AddView(const wxString &viewName)
{
    std::vector <Element*> new_view;
    mAllViews.push_back(new_view);
}

void SequenceElements::RemoveView(int view_index)
{
    mAllViews[view_index].clear();
    mAllViews.erase(mAllViews.begin() + view_index);
}

void SequenceElements::SetCurrentView(int view)
{
    mCurrentView = view;
}

void SequenceElements::AddMissingModelsToSequence(const wxString &models, bool visible)
{
    if(models.length()> 0)
    {
        wxArrayString model=wxSplit(models,',');
        for(int m=0;m<model.size();m++)
        {
            wxString modelName = model[m];
            if(!ElementExists(modelName))
            {
               wxString elementType = "model";
               Element* elem = AddElement(modelName,elementType,visible,false,false,false);
               elem->AddEffectLayer();
            }
        }
    }
}

void SequenceElements::SetTimingVisibility(const wxString& name)
{
    for(int i=0;i<mAllViews[MASTER_VIEW].size();i++)
    {
        Element* elem = mAllViews[MASTER_VIEW][i];
        if( elem->GetType() == "model" )
        {
            break;
        }
        if( name == "Master View" )
        {
            elem->SetVisible(true);
        }
        else
        {
            elem->SetVisible(false);
            wxArrayString views = wxSplit(elem->GetViews(),',');
            for(int v=0;v<views.size();v++)
            {
                wxString viewName = views[v];
                if( name == viewName )
                {
                    elem->SetVisible(true);
                    break;
                }
            }
        }
    }
}

void SequenceElements::AddTimingToAllViews(wxString& timing)
{
    for(wxXmlNode* view=mViewsNode->GetChildren(); view!=NULL; view=view->GetNext() )
    {
        wxString name = view->GetAttribute(STR_NAME);
        AddTimingToView(timing, name);
    }
}

void SequenceElements::AddViewToTimings(wxArrayString& timings, const wxString& name)
{
    for( int i = 0; i < timings.size(); i++ )
    {
        AddTimingToView(timings[i], name);
    }
}

void SequenceElements::AddTimingToView(wxString& timing, const wxString& name)
{
    Element* elem = GetElement(timing);
    if( elem != nullptr && elem->GetType() == "timing" )
    {
        wxString views = elem->GetViews();
        wxArrayString all_views = wxSplit(views,',');
        bool found = false;
        for( int j = 0; j < all_views.size(); j++ )
        {
            if( all_views[j] == name )
            {
                found = true;
                break;
            }
        }
        if( !found )
        {
            all_views.push_back(name);
            views = wxJoin(all_views, ',');
            elem->SetViews(views);
        }
    }
}

void SequenceElements::PopulateView(const wxString &models, int view)
{
    mAllViews[view].clear();

    if(models.length()> 0)
    {
        wxArrayString model=wxSplit(models,',');
        for(int m=0;m<model.size();m++)
        {
            wxString modelName = model[m];
            Element* elem = GetElement(modelName);
            mAllViews[view].push_back(elem);
        }
    }
}

void SequenceElements::SetFrequency(double frequency)
{
    mFrequency = frequency;
}

double SequenceElements::GetFrequency()
{
    return mFrequency;
}

int SequenceElements::GetMinPeriod()
{
    return (int)((double)1000.0/(double)mFrequency);
}

void SequenceElements::SetSelectedTimingRow(int row)
{
    mSelectedTimingRow = row;
}

int SequenceElements::GetSelectedTimingRow()
{
    return mSelectedTimingRow;
}

wxXmlNode *GetModelNode(wxXmlNode *root, const wxString & name) {
    wxXmlNode* e;
    for(e=root->GetChildren(); e!=NULL; e=e->GetNext() )
    {
        if (e->GetName() == "model")
        {
            if (name == e->GetAttribute(STR_NAME)) return e;
        }
    }
    return NULL;
}

void addModelElement(Element *elem, std::vector<Row_Information_Struct> &mRowInformation,
                     int &rowIndex, xLightsFrame *xframe,
                     std::vector <Element*> &elements,
                     bool submodel) {
    if(!elem->GetCollapsed())
    {
        for(int j =0; j<elem->GetEffectLayerCount();j++)
        {
            Row_Information_Struct ri;
            ri.element = elem;
            ri.displayName = elem->GetName();
            ri.Collapsed = elem->GetCollapsed();
            ri.Active = elem->GetActive();
            ri.colorIndex = 0;
            ri.layerIndex = j;
            ri.Index = rowIndex++;
            ri.submodel = submodel;
            mRowInformation.push_back(ri);
        }
    }
    else
    {
        Row_Information_Struct ri;
        ri.element = elem;
        ri.Collapsed = elem->GetCollapsed();
        ri.displayName = elem->GetName();
        ri.Active = elem->GetActive();
        ri.colorIndex = 0;
        ri.layerIndex = 0;
        ri.Index = rowIndex++;
        ri.submodel = submodel;
        mRowInformation.push_back(ri);
    }
    ModelClass *cls = xframe->GetModelClass(elem->GetName());
    elem->InitStrands(*cls);
    if (cls->GetDisplayAs() == "WholeHouse" && elem->ShowStrands()) {
        wxString models = cls->GetModelXml()->GetAttribute("models");
        wxArrayString model=wxSplit(models,',');
        for(int m=0;m<model.size();m++) {
            for (int x = 0; x < elements.size(); x++) {
                if (elements[x]->GetName() == model[m]) {
                    addModelElement(elements[x], mRowInformation, rowIndex, xframe, elements, true);
                }
            }
        }
    } else if (elem->ShowStrands()) {
        for (int s = 0; s < elem->getStrandLayerCount(); s++) {
            StrandLayer * sl = elem->GetStrandLayer(s);
            if (elem->getStrandLayerCount() > 1) {
                Row_Information_Struct ri;
                ri.element = elem;
                ri.Collapsed = !elem->ShowStrands();
                ri.Active = elem->GetActive();
                ri.displayName = sl->GetName();

                ri.colorIndex = 0;
                ri.layerIndex = 0;
                ri.Index = rowIndex++;
                ri.strandIndex = s;
                ri.submodel = submodel;
                mRowInformation.push_back(ri);
            }

            if (sl->ShowNodes()) {
                for (int n = 0; n < sl->GetNodeLayerCount(); n++) {
                    Row_Information_Struct ri;
                    ri.element = elem;
                    ri.Collapsed = sl->ShowNodes();
                    ri.Active = !elem->GetActive();
                    ri.displayName = sl->GetNodeLayer(n)->GetName();
                    ri.colorIndex = 0;
                    ri.layerIndex = 0;
                    ri.Index = rowIndex++;
                    ri.strandIndex = s;
                    ri.nodeIndex = n;
                    ri.submodel = submodel;
                    mRowInformation.push_back(ri);
                }
            }
        }
    }
}

void SequenceElements::addTimingElement(Element *elem, std::vector<Row_Information_Struct> &mRowInformation,
                                        int &rowIndex, int &selectedTimingRow, int &timingRowCount, int &timingColorIndex) {
    if( elem->GetEffectLayerCount() > 1 )
    {
        hasPapagayoTiming = true;
    }

    if(!elem->GetCollapsed())
    {
        for(int j =0; j<elem->GetEffectLayerCount();j++)
        {
            Row_Information_Struct ri;
            ri.element = elem;
            ri.Collapsed = elem->GetCollapsed();
            ri.Active = elem->GetActive();
            ri.colorIndex = timingColorIndex;
            ri.layerIndex = j;
            if(selectedTimingRow<0 && j==0)
            {
                selectedTimingRow = ri.Active?rowIndex:-1;
            }

            ri.Index = rowIndex++;
            mRowInformation.push_back(ri);
            timingRowCount++;
        }
    }
    else
    {
        Row_Information_Struct ri;
        ri.element = elem;
        ri.Collapsed = elem->GetCollapsed();
        ri.displayName = elem->GetName();
        ri.Active = elem->GetActive();
        ri.colorIndex = timingColorIndex;
        ri.layerIndex = 0;
        ri.Index = rowIndex++;
        mRowInformation.push_back(ri);
    }
    timingColorIndex++;
}

void SequenceElements::PopulateRowInformation()
{
    int rowIndex=0;
    int timingColorIndex=0;
    mSelectedTimingRow = -1;
    mRowInformation.clear();
    mTimingRowCount = 0;

    for(int i=0;i<mAllViews[MASTER_VIEW].size();i++)
    {
        Element* elem = mAllViews[MASTER_VIEW][i];
        if(elem->GetType()=="timing")
        {
            if( mCurrentView == MASTER_VIEW || TimingIsPartOfView(elem, mCurrentView))
            {
                addTimingElement(elem, mRowInformation, rowIndex, mSelectedTimingRow, mTimingRowCount, timingColorIndex);
            }
        }
    }

    for(int i=0;i<mAllViews[mCurrentView].size();i++)
    {
        Element* elem = mAllViews[mCurrentView][i];
        if(elem->GetVisible())
        {
            if (elem->GetType()=="model")
            {
                addModelElement(elem, mRowInformation, rowIndex, xframe, mAllViews[MASTER_VIEW], false);
            }
        }
    }
    PopulateVisibleRowInformation();
}

void SequenceElements::PopulateVisibleRowInformation()
{
    mVisibleRowInformation.clear();
    if(mRowInformation.size()==0){return;}
    // Add all timing element rows. They should always be first in the list
    int row=0;
    for(row=0;row<mTimingRowCount;row++)
    {
        if(row<mMaxRowsDisplayed)
        {
            mVisibleRowInformation.push_back(mRowInformation[row]);
        }
    }

    if (mFirstVisibleModelRow >= mRowInformation.size()) {
        mFirstVisibleModelRow = 0;
    }
    for(;row<mMaxRowsDisplayed && row+mFirstVisibleModelRow<mRowInformation.size();row++)
    {
        mRowInformation[row+mFirstVisibleModelRow].RowNumber = row;
        mVisibleRowInformation.push_back(mRowInformation[row+mFirstVisibleModelRow]);
    }
}

void SequenceElements::SetFirstVisibleModelRow(int row)
{
    // They all fit on screen. So set to first model element.
    if(mRowInformation.size() <= mMaxRowsDisplayed)
    {
        mFirstVisibleModelRow = 0;
    }
    else
    {
        int maxModelRowsThatCanBeDisplayed = mMaxRowsDisplayed - mTimingRowCount;
        int totalModelRowsToDisplay = mRowInformation.size() - mTimingRowCount;

        int leastRowToDisplay = (totalModelRowsToDisplay - maxModelRowsThatCanBeDisplayed);
        if(row > leastRowToDisplay)
        {
            mFirstVisibleModelRow = leastRowToDisplay;
        }
        else
        {
            mFirstVisibleModelRow = row;
        }
    }
    PopulateVisibleRowInformation();
}

int SequenceElements::GetNumberOfTimingRows()
{
    return mTimingRowCount;
}

int SequenceElements::GetNumberOfTimingElements() {
    int count = 0;
    for(int i=0;i<mAllViews[MASTER_VIEW].size();i++)
    {
        if(mAllViews[MASTER_VIEW][i]->GetType()=="timing")
        {
            count++;
        }
    }
    return count;
}


void SequenceElements::DeactivateAllTimingElements()
{
    for(int i=0;i<mAllViews[mCurrentView].size();i++)
    {
        if(mAllViews[mCurrentView][i]->GetType()=="timing")
        {
            mAllViews[mCurrentView][i]->SetActive(false);
        }
    }
}

int SequenceElements::SelectEffectsInRowAndTimeRange(int startRow, int endRow, int startMS,int endMS)
{
    int num_selected = 0;
    if(startRow<mVisibleRowInformation.size())
    {
        if(endRow>=mVisibleRowInformation.size())
        {
            endRow = mVisibleRowInformation.size()-1;
        }
        for(int i=startRow;i<=endRow;i++)
        {
            EffectLayer* effectLayer = GetEffectLayer(&mVisibleRowInformation[i]);
            num_selected += effectLayer->SelectEffectsInTimeRange(startMS,endMS);
        }
    }
    return num_selected;
}

int SequenceElements::SelectEffectsInRowAndColumnRange(int startRow, int endRow, int startCol,int endCol)
{
    int num_selected = 0;
    EffectLayer* tel = GetVisibleEffectLayer(GetSelectedTimingRow());
    if( tel != nullptr )
    {
        Effect* eff1 = tel->GetEffect(startCol);
        Effect* eff2 = tel->GetEffect(endCol);
        if( eff1 != nullptr && eff2 != nullptr )
        {
            int startMS = eff1->GetStartTimeMS();
            int endMS = eff2->GetEndTimeMS();
            num_selected = SelectEffectsInRowAndTimeRange(startRow, endRow, startMS, endMS);
        }
    }
    return num_selected;
}

void SequenceElements::UnSelectAllEffects()
{
    for(int i=0;i<mRowInformation.size();i++)
    {
        EffectLayer* effectLayer = GetEffectLayer(&mRowInformation[i]);
        effectLayer->UnSelectAllEffects();
    }
}

void SequenceElements::UnSelectAllElements()
{
    for(int i=0;i<mAllViews[mCurrentView].size();i++)
    {
        mAllViews[mCurrentView][i]->SetSelected(false);
    }
}

// Functions to manage selected ranges
int SequenceElements::GetSelectedRangeCount()
{
    return mSelectedRanges.size();
}

EffectRange* SequenceElements::GetSelectedRange(int index)
{
    return &mSelectedRanges[index];
}

void SequenceElements::AddSelectedRange(EffectRange* range)
{
    mSelectedRanges.push_back(*range);
}

void SequenceElements::DeleteSelectedRange(int index)
{
    if(index < mSelectedRanges.size())
    {
        mSelectedRanges.erase(mSelectedRanges.begin()+index);
    }
}

void SequenceElements::ClearSelectedRanges()
{
    mSelectedRanges.clear();
}

void SequenceElements::SetMaxRowsDisplayed(int maxRows)
{
    mMaxRowsDisplayed = maxRows;
}

int SequenceElements::GetMaxModelsDisplayed()
{
    return mMaxRowsDisplayed - mTimingRowCount;
}

int SequenceElements::GetTotalNumberOfModelRows()
{
    return mRowInformation.size() - mTimingRowCount;
}

int SequenceElements::GetFirstVisibleModelRow()
{
    return mFirstVisibleModelRow;
}

void SequenceElements::SetVisibilityForAllModels(bool visibility, int view)
{
    for(int i=0;i<GetElementCount(view);i++)
    {
        Element * e = GetElement(i, view);
        e->SetVisible(visibility);
    }
}

void SequenceElements::MoveSequenceElement(int index, int dest, int view)
{
    IncrementChangeCount(nullptr);

    if(index<mAllViews[view].size() && dest<mAllViews[view].size())
    {
        Element* e = mAllViews[view][index];
        mAllViews[view].erase(mAllViews[view].begin()+index);
        if(index >= dest)
        {
            mAllViews[view].insert(mAllViews[view].begin()+dest,e);
        }
        else
        {
            mAllViews[view].insert(mAllViews[view].begin()+(dest-1),e);
        }
    }
}

void SequenceElements::MoveElementUp(const wxString &name, int view)
{
    IncrementChangeCount(nullptr);

    for(int i=0;i<mAllViews[view].size();i++)
    {
        if(name == mAllViews[view][i]->GetName())
        {
            // found element
            if( i > 0 )
            {
                MoveSequenceElement(i, i-1, view);
            }
            break;
        }
    }
}

void SequenceElements::MoveElementDown(const wxString &name, int view)
{
    IncrementChangeCount(nullptr);

    for(int i=0;i<mAllViews[view].size();i++)
    {
        if(name == mAllViews[view][i]->GetName())
        {
            // found element
            if( i < mAllViews[view].size()-1 )
            {
                MoveSequenceElement(i+1, i, view);
            }
            break;
        }
    }
}

void SequenceElements::ImportLyrics(Element* element, wxWindow* parent)
{
    LyricsDialog* dlgLyrics = new LyricsDialog(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    if (dlgLyrics->ShowModal() == wxID_OK)
    {
        element->SetFixedTiming(0);
        // remove all existing layers from timing track
        int num_layers = element->GetEffectLayerCount();
        for( int k = num_layers-1; k >= 0; k-- )
        {
            element->RemoveEffectLayer(k);
        }
        EffectLayer* phrase_layer = element->AddEffectLayer();

        int total_num_phrases = dlgLyrics->TextCtrlLyrics->GetNumberOfLines();
        int num_phrases = total_num_phrases;
        for( int i = 0; i < dlgLyrics->TextCtrlLyrics->GetNumberOfLines(); i++ )
        {
            wxString line = dlgLyrics->TextCtrlLyrics->GetLineText(i);
            if( line == "" )
            {
                num_phrases--;
            }
        }
        int start_time = 0;
        int end_time = mSequenceEndMS;
        int interval_ms = (end_time-start_time) / num_phrases;
        for( int i = 0; i < total_num_phrases; i++ )
        {
            wxString line = dlgLyrics->TextCtrlLyrics->GetLineText(i);
            if( line != "" )
            {
                xframe->dictionary.InsertSpacesAfterPunctuation(line);
                end_time = TimeLine::RoundToMultipleOfPeriod(start_time+interval_ms, GetFrequency());
                phrase_layer->AddEffect(0,0,line,wxEmptyString,"",start_time,end_time,EFFECT_NOT_SELECTED,false);
                start_time = end_time;
            }
        }
    }
}

void SequenceElements::BreakdownPhrase(EffectLayer* word_layer, int start_time, int end_time, const wxString& phrase)
{
    if( phrase != "" )
    {
        xframe->dictionary.LoadDictionaries(xframe->CurrentDir);
        wxArrayString words = wxSplit(phrase, ' ');
        int num_words = words.Count();
        double interval_ms = (end_time-start_time) / num_words;
        int word_start_time = start_time;
        for( int i = 0; i < num_words; i++ )
        {
            int word_end_time = TimeLine::RoundToMultipleOfPeriod(start_time+(interval_ms * (i + 1)), GetFrequency());
            if( i == num_words - 1  || word_end_time > end_time)
            {
                word_end_time = end_time;
            }
            word_layer->AddEffect(0,0,words[i],wxEmptyString,"",word_start_time,word_end_time,EFFECT_NOT_SELECTED,false);
            word_start_time = word_end_time;
        }
    }
}

void SequenceElements::BreakdownWord(EffectLayer* phoneme_layer, int start_time, int end_time, const wxString& word)
{
    xframe->dictionary.LoadDictionaries(xframe->CurrentDir);
    wxArrayString phonemes;
    xframe->dictionary.BreakdownWord(word, phonemes);
    if( phonemes.Count() > 0 )
    {
        int phoneme_start_time = start_time;
        double phoneme_interval_ms = (end_time-start_time) / phonemes.Count();
        for( int i = 0; i < phonemes.Count(); i++ )
        {
            int phoneme_end_time = TimeLine::RoundToMultipleOfPeriod(start_time+(phoneme_interval_ms*(i + 1)), GetFrequency());
            if( i == phonemes.Count() - 1 || phoneme_end_time > end_time)
            {
                phoneme_end_time = end_time;
            }
            phoneme_layer->AddEffect(0,0,phonemes[i],wxEmptyString,"",phoneme_start_time,phoneme_end_time,EFFECT_NOT_SELECTED,false);
            phoneme_start_time = phoneme_end_time;
        }
    }
}

void SequenceElements::IncrementChangeCount(Element *el) {
    mChangeCount++;
    if (el != nullptr && el->GetType() == "timing") {
        //need to check if we need to have some models re-rendered due to timing being changed
        wxMutexLocker locker(renderDepLock);
        std::map<wxString, std::set<wxString>>::iterator it = renderDependency.find(el->GetName());
        if (it != renderDependency.end()) {
            int origChangeCount, ss, es;
            el->GetAndResetDirtyRange(origChangeCount, ss, es);
            for (std::set<wxString>::iterator sit = it->second.begin(); sit != it->second.end(); sit++) {
                Element *el = this->GetElement(*sit);
                if (el != nullptr) {
                    el->IncrementChangeCount(ss, es);
                    modelsToRender.insert(*sit);
                }
            }
        }
    }
}
bool SequenceElements::GetElementsToRender(std::vector<Element *> &models) {
    wxMutexLocker locker(renderDepLock);
    if (!modelsToRender.empty()) {
        for (std::set<wxString>::iterator sit = modelsToRender.begin(); sit != modelsToRender.end(); sit++) {
            Element *el = this->GetElement(*sit);
            if (el != nullptr) {
                models.push_back(el);
            }
        }
        modelsToRender.clear();
        return !models.empty();
    }
    return false;
}

void SequenceElements::AddRenderDependency(const wxString &layer, const wxString &model) {
    wxMutexLocker locker(renderDepLock);
    renderDependency[layer].insert(model);
}

