////////////////////////////////////////////////////////////////////////////////
// class ExtractDEEPointsGUI is used to extract dE-E points with GUI,
//  modified by gfh, based on the GUI of Fission2014
//
//  [**Note**] gfh just modified this class to be used for Fission2019,
//             the original one comes from Zhang Yan's code
//
// Jan 4, 2021
///////////////////////////////////////////////////////////////////////////////

#ifndef ExtractDEEPointsGUI_h
#define ExtractDEEPointsGUI_h

#include <TGClient.h>
#include <TCanvas.h>
#include "TPad.h"
#include <TF1.h>
#include "TFile.h"
#include "TH1D.h"
#include <TRandom.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGListBox.h>
#include <TGListView.h>
#include <TGLabel.h>
#include <TGSimpleTable.h>
#include <TGFrame.h>
#include <TGNumberEntry.h>
#include <TG3DLine.h>
#include <TRootEmbeddedCanvas.h>
#include "TGFrame.h"
#include <TApplication.h>
#include "fstream"
#include <iomanip>
#include "TMarker.h"
#include "TH2I.h"
#include "TGraph.h"
#include "TCutG.h"
#include "TCut.h"

using namespace std;

#define NUM_FITPARS      8


//******************************************************************************
//           text margins class
//        ------------------------
class TextMargin : public TGHorizontalFrame
{
protected:
  TGNumberEntry *fEntry;

public:
  TextMargin(const TGWindow* p, const char* name) : TGHorizontalFrame(p)
  {
    fEntry = new TGNumberEntry(this, 0, 6, -1, TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
    AddFrame(fEntry, new TGLayoutHints(kLHintsLeft));
    TGLabel* label = new TGLabel(this, name);
    AddFrame(label, new TGLayoutHints(kLHintsLeft, 10));
  }
  TGTextEntry* GetEntry() const { return fEntry->GetNumberEntry(); }
  Double_t GetNumber(){ return fEntry->GetNumber(); }

  ClassDef(TextMargin, 0)
};
//******************************************************************************


//______________________________________________________________________________
//                   GUI constructon
//                -----------------------
//
//  如何在 GUI 里面添加新的功能？
//    1. 先声明 TGTextButton 或 TGGroupFrame 或 TextMargin
//    2. 在初始化中, 定义上述声明
//    3. 再定义相关实现函数
//
class ExtractDEEPointsGUI : public TGMainFrame
{
// 在此添加 GUI “窗口”
private:
  TRootEmbeddedCanvas   *fEcanvas;
  TGTextButton          *drawhist, *exit;
  TGTextButton          *drawmarkers,*deletemakers,*writefile;
  TGTextButton          *fitmarkers,*savepars;
  TGTextButton          *drawbananacut, *deletebananacut, *savebananacut;
  TGGroupFrame          *margins_draw;
  TGGroupFrame          *margins_id;
  TextMargin            *Particle_Entry;
  TextMargin            *Tele_Entry;
  TextMargin            *Charge_Entry;
  TextMargin            *Mass_Entry;

public:
  ExtractDEEPointsGUI(const TGWindow *p, UInt_t w, UInt_t h);
  ~ExtractDEEPointsGUI();

public:
  Int_t        TeleNo, TeleNo_Max;
  Int_t        ParticleNo, ParticleNo_Max;
  Int_t        ChargeNo, MassNo;
  string       HistTile, CutFile_Name, BananaCut_FileName;
  string       pathFitParsOut, histo_FilePath, pathBananaCut;
  TFile       *MarkersFileOut, *BananaCutFileOut;
  ofstream     FitParsFileOut;
  TFile       *f1_histo;
  TH2D        *h2_DEEPlot;
  TGraph      *fgraph;
  Int_t        fNMarkers;
  Double_t     fMarkerX;
  Double_t     fMarkerY;
  TF1         *ffitfunc;
  Double_t    *MarkerFitPars;
  TCutG       *fcutg;

// 初始化
  void         Initial_RootFile(string histo_FilePath_tem);
  void         Initial_GUI(int xPixel,int yPixel);
  void         Initial_Slot();

// 画直方图
  void         Draw_Hist();

// 拟合点的操作: draw_graph, detele, write
  void         Set_MarkersFileName(string FileName_tem, string HistTile_tem);
  void         Draw_Markers();
  void         Delete_Markers();
  void         Write_MarkersCut();

// added by gfh, Jan 2021
// 拟合, 保存拟合参数
  void         Set_FitParsFileName(string pathFitParsOut_tem);
  void         Fit_Markers();
  void         Save_FitPars();

// added by gfh, May 2021
  void         Set_BananaCutFileName(string pathBananaCutName_tem);
  void         Draw_BananaCut();
  void         Delete_BananaCut();
  void         Save_BananaCut();

// 退出 GUI
  void         Exit_GUI();

  ClassDef(ExtractDEEPointsGUI,0)
};

#endif
