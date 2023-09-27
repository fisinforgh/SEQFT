/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// NOTICE OF COPYRIGHT                                                     //
//                                                                         //
// Authors:				                                   //
//   [1] Ingrid Daiana Cuevas Ruiz*			                   //
//   [2] Julian Andrés Salamanca Bernal**			           //         			           
//                                                                         //
//   [1] idcuevasr@udistrital.edu.co (Licenciada Universidad Distrital)    //
//   [2] jasalamanca@udistrital.edu.co (profesor Universidad Distrital)    //
//								           //
//  *,** Grupo de Física e Informática (FISINFOR)		           //
//  *,** Universidad Distrital Francisco José de Caldas (Bogotá, Colombia) //	
//                                                                         //
// Web page:								   //
//   https://github.com/fisinforgh/SEQFT/tree/main/QFTSoftEdu              //
//                                                                         //
// This program is free software; you can redistribute it and/or modify    //
// it under the terms of the GNU General Public License as published by    //
// the Free Software Foundation; either version 2 of the License, or       //
// (at your option) any later version.                                     //
//                                                                         //
// This program is distributed in the hope that it will be useful,         //
// but WITHOUT ANY WARRANTY; without even the implied warranty of          //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
// GNU General Public License for more details:                            //
//                                                                         //
//               http://www.gnu.org/copyleft/gpl.html                      //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


#include <TApplication.h>
#include <TGClient.h>
#include "TGDockableFrame.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TRootBrowser.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGMenu.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGFSContainer.h"
#include "TGuiBldEditor.h"
#include "TGColorSelect.h"
#include "TGTextEdit.h"
#include "TGButton.h"
#include "TRootContextMenu.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGView.h"
#include "TGMsgBox.h"
#include "TRootGuiBuilder.h"
#include "TGFileBrowser.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGTextEditor.h"
#include "TRootCanvas.h"
#include "TGStatusBar.h"
#include "TGListTree.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolTip.h"
#include "TGToolBar.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
#include "TGuiBldDragManager.h"
#include "TGHtmlBrowser.h"
#include "Riostream.h"
#include "TGeoManager.h"

#include <TApplication.h>
#include <TGClient.h>
#include <TImage.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TLine.h>
#include <TArc.h>
#include <TMarker.h>
#include <TGeoManager.h>

#include "SEQFT.h"

Float_t             color = 1;
TLine               *line04;
TLine               *line05;
TLine               *line06;
TLine               *line07;
TLine               *line08;
TTimer              *timer;
TTimer              *timer1;
TCanvas             *fCanvas;
TRootEmbeddedCanvas *fECanvasGen;
TLatex              *name2;
TLatex              *HD;

/////////////////////////////////////////////////////// GUI DESING /////////////////////////////////////////////////////////////////
MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
	TGFont              *ufont;         // will reflect user font changes
	TGGC                *uGC;           // will reflect user GC changes
	ULong_t             ucolor; 
	
	//MAIN FRAME
	fMain = new TGMainFrame(p,w,h);
	
	//----------------------------------------------------- FRAMES -------------------------------------------------------------//
	//HFRAME
	TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,1200,85,kVerticalFrame);
	hframe03 = new TGHorizontalFrame(fMain,1500,85,kVerticalFrame);
  
	//VFRAME 
	vframe = new TGVerticalFrame(hframe03,250,500,kVerticalFrame);

	//-------------------------------------------------------- TAB -------------------------------------------------------------//
	// tab widget
	fTabGeneral = new TGTab(vframe,128,272);

	// container of "Tab1"
	fTabQFT = fTabGeneral->AddTab("QFT");
	fTabQFT->SetLayoutManager(new TGVerticalLayout(fTabQFT));

	// container of "Tab2"
	fTabBC = fTabGeneral->AddTab("B. Concepts");
	fTabBC->SetLayoutManager(new TGVerticalLayout(fTabBC));
	
	//ADD TAB
	fTabGeneral->SetTab(0);

	//------------------------------------------------- SET QUBIT STATE ---------------------------------------------------------//
	//GRAPHICS CONTEXT CHANGES (TGGROUPFRAME.VARIABLES)
	ufont = gClient->GetFont("-bitstream-bitstream charter-bold-r-normal--15-120-100-100-p-0-adobe-standard");
	GCValues_t valvframe;
	valvframe.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valvframe.fForeground);
	gClient->GetColorByName("#e8e8e8",valvframe.fBackground);
	valvframe.fFillStyle = kFillSolid;
	valvframe.fFont = ufont->GetFontHandle();
	valvframe.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valvframe, kTRUE);
	
	//Group Frame
	fGVariables = new TGGroupFrame(fTabQFT," ",kVerticalFrame,uGC->GetGC(),ufont->GetFontStruct());
	fGVariables->SetLayoutBroken(kTRUE);
	fGVariables->DrawBorder();
	
	//CANVAS STATE
  	//canvas texto
	fECanvasstate = new TRootEmbeddedCanvas(0,fGVariables,700,300,kHorizontalFrame);
	fGVariables->AddFrame(fECanvasstate, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fECanvasstate->MoveResize(1,15,130,346);
 
	//GetCanvas
	fCanvas = fECanvasstate->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);

	TLatex *HD = new TLatex(0.24,0.05,"#scale[3.5]{State}");
	HD->Draw();
	
	HD = new TLatex(0.34,0.19,"#scale[3.5]{#cbar x_{2} #GT}");
	HD->Draw();
	
	HD = new TLatex(0.34,0.33,"#scale[3.5]{#cbar x_{1} #GT}");
	HD->Draw();
	
	HD = new TLatex(0.34,0.47,"#scale[3.5]{#cbar x_{0} #GT}");
	HD->Draw();
	
	HD = new TLatex(0.34,0.75,"#scale[3.5]{N = 2^{n}}");
	HD->Draw();
	
	HD = new TLatex(0.24,0.61,"#scale[3.5]{N' = 2^{n-1}}");
	HD->Draw();
	
	HD = new TLatex(0.14,0.89,"#scale[3.5]{Qubits (n)}");
	HD->Draw();
 
	fCanvas->SetEditable(0);

	// combo box  
	fNQubits = new TGComboBox(fGVariables,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fNQubits->AddEntry("1",1);
	fNQubits->AddEntry("2",2);
	fNQubits->AddEntry("3",3);
	fNQubits->Connect("Selected(Int_t)","MyMainFrame",this,"SelectQState(Int_t)");
	fNQubits->Select(0);
	
	fGVariables->AddFrame(fNQubits, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fNQubits->MoveResize(140,33,30,32);
	
	// combo box  
	fX0 = new TGComboBox(fGVariables,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fX0->AddEntry("0",0);
	fX0->AddEntry("1",1);
	fX0->Select(0);
	fGVariables->AddFrame(fX0, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fX0->MoveResize(140,175,30,32);
	fX0->SetEnabled(kFALSE);
	
	// combo box  
	fX1 = new TGComboBox(fGVariables,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fX1->AddEntry("0",0);
	fX1->AddEntry("1",1);
	fX1->Select(0);
	fGVariables->AddFrame(fX1, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fX1->MoveResize(140,225,30,32);
	fX1->SetEnabled(kFALSE);
	
	// combo box  
	fX2 = new TGComboBox(fGVariables,-1,kHorizontalFrame | kSunkenFrame | kOwnBackground);
	fX2->AddEntry("0",0);
	fX2->AddEntry("1",1);
	fX2->Select(0);
	fGVariables->AddFrame(fX2, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fX2->MoveResize(140,275,30,32);
	fX2->SetEnabled(kFALSE);

	// graphics context changes
	ufont = gClient->GetFont("-*-fixed-bold-r-*-*-18-*-*-*-*-*-*-*");
	GCValues_t vall1318;
	vall1318.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",vall1318.fForeground);
	gClient->GetColorByName("#e8e8e8",vall1318.fBackground);
	vall1318.fFillStyle = kFillSolid;
	vall1318.fFont = ufont->GetFontHandle();
	vall1318.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&vall1318, kTRUE);
	
	fLNQubitsVal = new TGLabel(fGVariables," ",uGC->GetGC(),ufont->GetFontStruct());
	fLNQubitsVal->SetTextJustify(36);
	fLNQubitsVal->SetWrapLength(-1);
	
	fLNVal = new TGLabel(fGVariables," ",uGC->GetGC(),ufont->GetFontStruct());
	fLNVal->SetTextJustify(36);
	fLNVal->SetWrapLength(-1);
	
	fLNValPrim = new TGLabel(fGVariables," ",uGC->GetGC(),ufont->GetFontStruct());
	fLNValPrim->SetTextJustify(36);
	fLNValPrim->SetWrapLength(-1);
	
	//Botón Start
	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-14-*-*-*-*-*-iso8859-1");
	GCValues_t valButtonStart;
	valButtonStart.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonStart.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonStart.fBackground);
	valButtonStart.fFillStyle = kFillSolid;
	valButtonStart.fFont = ufont->GetFontHandle();
	valButtonStart.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonStart, kTRUE);
	
	fBStart = new TGTextButton(fGVariables,"Start",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBStart->SetTextJustify(36);
	fBStart->SetWrapLength(-1);
	fBStart->Connect("Clicked()","MyMainFrame",this,"DoRestart()");
	fBStart->SetState(kButtonDisabled, kTRUE);
	fGVariables->AddFrame(fBStart, new TGLayoutHints(kLHintsExpandX,2,2,2,2));
	fBStart->MoveResize(15,370,70,30);
	
	//Botón Stop
	GCValues_t valButtonStop;
	valButtonStop.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonStop.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonStop.fBackground);
	valButtonStop.fFillStyle = kFillSolid;
	valButtonStop.fFont = ufont->GetFontHandle();
	valButtonStop.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonStop, kTRUE);
	
	fBStop = new TGTextButton(fGVariables,"Stop",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBStop->SetTextJustify(36);
	fBStop->SetWrapLength(-1);
	fBStop->Connect("Clicked()","MyMainFrame",this,"DoStop()");
	fBStop->SetState(kButtonDisabled, kTRUE);
	fGVariables->AddFrame(fBStop, new TGLayoutHints(kLHintsExpandX,2,2,2,2));
	fBStop->MoveResize(95,370,70,30);
	
	fGVariables->SetLayoutManager(new TGVerticalLayout(fGVariables));
	
	//------------------------------------------------------ B. CONCEPTS ------------------------------------------------------------//
	//Botón Hadamard
	GCValues_t valButtonHadamard;
	valButtonHadamard.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonHadamard.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonHadamard.fBackground);
	valButtonHadamard.fFillStyle = kFillSolid;
	valButtonHadamard.fFont = ufont->GetFontHandle();
	valButtonHadamard.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonHadamard, kTRUE);
	
	fBHadamard = new TGTextButton(fTabBC,"Hadamard",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBHadamard->SetTextJustify(36);
	fBHadamard->SetWrapLength(-1);
	fBHadamard->Connect("Clicked()","MyMainFrame",this,"DoHadamard()");
	fTabBC->AddFrame(fBHadamard, new TGLayoutHints(kLHintsExpandX,10,10,10,0));
	
	//Botón Rotation1
	GCValues_t valButtonRotation1;
	valButtonRotation1.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonRotation1.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonRotation1.fBackground);
	valButtonRotation1.fFillStyle = kFillSolid;
	valButtonRotation1.fFont = ufont->GetFontHandle();
	valButtonRotation1.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonRotation1, kTRUE);
	
	fBRotation1 = new TGTextButton(fTabBC,"Rotation 1",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBRotation1->SetTextJustify(36);
	fBRotation1->SetWrapLength(-1);
	fBRotation1->Connect("Clicked()","MyMainFrame",this,"DoRotation1()");
	fTabBC->AddFrame(fBRotation1, new TGLayoutHints(kLHintsExpandX,10,10,0,0));
	
	//Botón Rotation2
	GCValues_t valButtonRotation2;
	valButtonRotation2.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonRotation2.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonRotation2.fBackground);
	valButtonRotation2.fFillStyle = kFillSolid;
	valButtonRotation2.fFont = ufont->GetFontHandle();
	valButtonRotation2.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonRotation2, kTRUE);
	
	fBRotation2 = new TGTextButton(fTabBC,"Rotation 2",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBRotation2->SetTextJustify(36);
	fBRotation2->SetWrapLength(-1);
	fBRotation2->Connect("Clicked()","MyMainFrame",this,"DoRotation2()");
	fTabBC->AddFrame(fBRotation2, new TGLayoutHints(kLHintsExpandX,10,10,0,0));
	
	//Botón Swap
	GCValues_t valButtonSwap;
	valButtonSwap.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonSwap.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonSwap.fBackground);
	valButtonSwap.fFillStyle = kFillSolid;
	valButtonSwap.fFont = ufont->GetFontHandle();
	valButtonSwap.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonSwap, kTRUE);
	
	fBSwap = new TGTextButton(fTabBC,"Swap",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBSwap->SetTextJustify(36);
	fBSwap->SetWrapLength(-1);
	fBSwap->Connect("Clicked()","MyMainFrame",this,"DoSwap()");
	fTabBC->AddFrame(fBSwap, new TGLayoutHints(kLHintsExpandX,10,10,0,0));
	
	fECanvasExp = new TRootEmbeddedCanvas(0,fTabBC,155,300,kHorizontalFrame);
  	fTabBC->AddFrame(fECanvasExp, new TGLayoutHints(kLHintsExpandY,10,10,10,10));
	
	//---------------------------------------------------------  ICONS  --------------------------------------------------------------//
	TString spathHIDEN_FILE(gSystem->HomeDirectory());
	spathHIDEN_FILE.Append("/.pathDIR_HDFoSoftEdu_v2.txt");

	ifstream inHidenFile;
	inHidenFile.open(spathHIDEN_FILE);
  
	string spathICONS;
	getline(inHidenFile,spathICONS);
	pathDIR_ICONS.Append(spathICONS);
	pathDIR_ICONS.Append("/icons/");
  
	TGIcon *UDicon = new TGIcon(hframe,pathDIR_ICONS + "logoUD.png");
  	UDicon->SetName("logoUD");
  	
  	TGIcon *FISicon = new TGIcon(vframe, pathDIR_ICONS + "logoFisinfor_v2.png");
  	UDicon->SetName("logoFIS");	
  	
  	TGIcon *QFTicon = new TGIcon(vframe, pathDIR_ICONS + "LogoQFT.jpg");
  	UDicon->SetName("logoQFT");	
	//----------------------------------------------------------  MAIN CANVAS  ------------------------------------------------------//
  	fECanvasGen = new TRootEmbeddedCanvas(0,hframe03,880,580,kHorizontalFrame);
  	fECanvasGen->SetName("fECanvasGen");
	
	//------------------------------------------------------  HORIZONTAL FRAME  ----------------------------------------------------//	
	//ICONO HFRAME
	hframe->AddFrame(UDicon, new TGLayoutHints(0,0,0,0));
	UDicon->MoveResize(0,700,180,60);
	
	//BOTONES HFRAME
	//GRAPHICS CONTEXT CHANGES (BUTTONS)
	ufont = gClient->GetFont("-bitstream-bitstream charter-medium-r-normal--17-120-100-100-p-0-adobe-standard");
	
	//Botón Anterior
	GCValues_t valButtonPrevious;
	valButtonPrevious.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonPrevious.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonPrevious.fBackground);
	valButtonPrevious.fFillStyle = kFillSolid;
	valButtonPrevious.fFont = ufont->GetFontHandle();
	valButtonPrevious.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonPrevious, kTRUE);
	
	fBPrevious = new TGTextButton(hframe,"Previous",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBPrevious->SetTextJustify(36);
	fBPrevious->SetWrapLength(-1);
	fBPrevious->Connect("Clicked()","MyMainFrame",this,"DoPrevious()");
	fBPrevious->SetState(kButtonDisabled, kTRUE);
	hframe->AddFrame(fBPrevious, new TGLayoutHints(kLHintsExpandX,20,20,10,2));
	
	//Botón Siguiente
	GCValues_t valButtonNext;
	valButtonNext.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#e8e8e8",valButtonNext.fBackground);
	valButtonNext.fFillStyle = kFillSolid;
	valButtonNext.fFont = ufont->GetFontHandle();
	valButtonNext.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonNext, kTRUE);
	
	fBNext = new TGTextButton(hframe,"Next",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBNext->SetTextJustify(36);
	fBNext->SetWrapLength(-1);
	fBNext->Connect("Clicked()","MyMainFrame",this,"DoNext()");
	fBNext->SetState(kButtonDisabled, kTRUE);
	hframe->AddFrame(fBNext, new TGLayoutHints(kLHintsExpandX,0,20,10,2));
	
	//Botón Reiniciar
	GCValues_t valButtonRestart;
	valButtonRestart.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonRestart.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonRestart.fBackground);
	valButtonRestart.fFillStyle = kFillSolid;
	valButtonRestart.fFont = ufont->GetFontHandle();
	valButtonRestart.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonRestart, kTRUE);
	
	fBRestart = new TGTextButton(hframe,"Restart",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBRestart->SetTextJustify(36);
	fBRestart->SetWrapLength(-1);
	fBRestart->Connect("Clicked()","MyMainFrame",this,"DoRestart()");
	fBRestart->SetState(kButtonDisabled, kTRUE);
	hframe->AddFrame(fBRestart, new TGLayoutHints(kLHintsExpandX,0,20,10,2));
	
	ufont = gClient->GetFont("-bitstream-bitstream charter-medium-r-normal--17-120-100-100-p-0-adobe-standard");
	
	//Botón Exit
	GCValues_t valButtonExit;
	valButtonExit.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonExit.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonExit.fBackground);
	valButtonExit.fFillStyle = kFillSolid;
	valButtonExit.fFont = ufont->GetFontHandle();
	valButtonExit.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonExit, kTRUE);
	
	fBExit = new TGTextButton(hframe,"Exit",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBExit->SetTextJustify(36);
	fBExit->SetWrapLength(-1);
	fBExit->SetCommand("gApplication->Terminate(0)");
	hframe->AddFrame(fBExit, new TGLayoutHints(kLHintsExpandX,0,20,10,2));

	//Botón Ayuda
	GCValues_t valButtonHelp;
	valButtonHelp.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valButtonHelp.fForeground);
	gClient->GetColorByName("#e8e8e8",valButtonHelp.fBackground);
	valButtonHelp.fFillStyle = kFillSolid;
	valButtonHelp.fFont = ufont->GetFontHandle();
	valButtonHelp.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valButtonHelp, kTRUE);

	fBHelp = new TGTextButton(hframe,"Help",-1,uGC->GetGC(),ufont->GetFontStruct(),kRaisedFrame);
	fBHelp->SetTextJustify(36);
	fBHelp->SetWrapLength(-1);
	fBHelp->Connect("Clicked()","MyMainFrame",this,"DoHelp()");
	hframe->AddFrame(fBHelp, new TGLayoutHints(kLHintsExpandX,0,20,10,2));
	
	//----------------------------------------------------------  ADD ALL  ------------------------------------------------------//
	fTabQFT->AddFrame(fGVariables, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,0,0,0,0));
	vframe->AddFrame(fTabGeneral, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0,0,0,0));
	fTabGeneral->MoveResize(0,0,180,420);	
	vframe->AddFrame(QFTicon, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
	QFTicon->Resize(180,75);
	vframe->AddFrame(FISicon, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
  	FISicon->Resize(180,68);
	
	hframe03->AddFrame(vframe, new TGLayoutHints(kLHintsExpandY,5,5,5,5));	
	hframe03->AddFrame(fECanvasGen, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,10,5,10,10));
	fMain->AddFrame(hframe03, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,10,10,2,2)); 
	fMain->AddFrame(hframe, new TGLayoutHints(kLHintsExpandX,10,5,0,0));
	
	DoWelcome();

	fMain->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
	fMain->SetWindowName("QUANTUM FOURIER TRNSFORM");
	fMain->MapSubwindows();
	fMain->Resize(fMain->GetDefaultSize());
	fMain->MapWindow();
}

///////////////////////////////////////////////////  WELCOME  //////////////////////////////////////////////////////////////////// 
void MyMainFrame::DoWelcome(){
	
	//Set Canvas
	TCanvas *fHelp = fECanvasGen->GetCanvas();
	fHelp->SetEditable(1);
	fHelp->Clear();
	fHelp->SetFillColor(18);
	
	//Titulo
	TPaveText *TPTTitle = new TPaveText(0.005,0.85,0.99,0.987);
	TPTTitle->SetTextFont(62);
	TPTTitle->SetTextSize(0.04);
	TPTTitle->SetFillColor(0);
	TPTTitle->SetShadowColor(18);
	TPTTitle->SetMargin(0);
	TPTTitle->AddText("#scale[1.2]{QFT#color[2]{Soft}#color[4]{Edu} (QFT Educational Software)}");
	TPTTitle->AddText("#scale[2]{#font[102]{QUANTUM FOURIER TRANSFORM}}");
	TPTTitle->Draw();
	
	//ExplainGUI
	TPad *pad1 = new TPad("pad1","This is pad1",0.005,0.45,0.65,0.84);
	TPad *pad3 = new TPad("pad3","This is pad1",0.67,0.45,0.987,0.84);
	TPad *pad2 = new TPad("pad2","This is pad2",0.005,0.005,0.987,0.44);
	pad2->Divide(3,1);
 
	pad1->SetFillColor(18);
	pad2->SetFillColor(18);
	
	pad1->Draw();
	pad2->Draw();
	pad3->Draw();
	
	//EXPLICACION GENERAL	
	pad1->cd();
	TPaveText *TPTExplainG = new TPaveText(0,0.01,1,0.99);
	TPTExplainG->SetTextColor(kBlack);
	TPTExplainG->SetTextSize(0.06);
	TPTExplainG->SetFillColor(kYellow-9);
	TPTExplainG->SetShadowColor(18);
	TPTExplainG->SetMargin(0);
	TPTExplainG->SetTextAlign(1);

	TPTExplainG->AddText(" ");
	TPTExplainG->AddText("           #font[22]{#scale[1.5]{LEARNING QUANTUM FOURIER TRANSFORM}}");
	TPTExplainG->AddText("   The Quantum Fourier Transform is analogous to the Discrete Fourier Transform. It is a");
	TPTExplainG->AddText("   method applied to quantum bits. Given the relevance of this process, it is used in");
	TPTExplainG->AddText("   various theoretical quantum algorithms such as Shor's algorithm, the phase estimation");
	TPTExplainG->AddText("   algorithm, logarithms for HSP (hidden subgroup problem), etc. In general, the algorithms");
	TPTExplainG->AddText("   allow greater calculation efficiency over time, resulting in results that might not be");
	TPTExplainG->AddText("   known in a classical way.");
	TPTExplainG->AddText(" ");
	TPTExplainG->AddText("   This educational resource aims to teach the Quantum Fourier Transform, directed  not");
	TPTExplainG->AddText("   only to teachers and students who belong to the field of computing, but also to anyone");
	TPTExplainG->AddText("   with basic knowledge in physics and mathematics and allows them to learn in a simple");
	TPTExplainG->AddText("   way, direct and interactive concepts and related operations.");

	TPTExplainG->Draw();
	
	//AUTORES	
	pad3->cd();
	TPaveText *TPTExplainA = new TPaveText(0,0.01,1,0.99);
	TPTExplainA->SetTextColor(kBlack);
	TPTExplainA->SetTextSize(0.07);
	TPTExplainA->SetFillColor(kCyan-9);
	TPTExplainA->SetShadowColor(18);
	TPTExplainA->SetMargin(0);
	TPTExplainA->SetTextAlign(1);

	TPTExplainA->AddText(" ");
	TPTExplainA->AddText("        #font[22]{#scale[1.5]{ABOUT AUTORS}}");
	TPTExplainA->AddText(" 1. #font[62]{Ingrid D Cuevas R}");
	TPTExplainA->AddText("     Investigation Group FISINFOR ");
	TPTExplainA->AddText("     Physics degree #font[72]{Universidad Distrital}");
	TPTExplainA->AddText("     #font[72]{Francisco Jose De Caldas}");
	TPTExplainA->AddText(" ");
	TPTExplainA->AddText(" 2. #font[62]{Julian A Salamanca B,} PHD ");
	TPTExplainA->AddText("     Investigation Group FISINFOR ");
	TPTExplainA->AddText("     Faculty of sciences and education.");
	TPTExplainA->AddText("     Teacher #font[72]{Universidad Distrital}");
	TPTExplainA->AddText("     #font[72]{Francisco Jose De Caldas.}");

	TPTExplainA->Draw();

	//SECTIONS
	pad2->cd(2);
	TPaveText *TPTExplainM = new TPaveText(0,0,1,1);
	TPTExplainM->SetTextColor(kBlack);
	TPTExplainM->SetTextSize(0.05);
	TPTExplainM->SetFillColor(kGreen-9);
	TPTExplainM->SetMargin(0);
	TPTExplainM->SetTextAlign(1);
	
	TPTExplainM->AddText(" ");
	TPTExplainM->AddText("            #font[22]{#scale[1.5]{QFT SECTIONS}}");
	TPTExplainM->AddText("  This interface contains a panel to");
	TPTExplainM->AddText("  describe the initial state of the");
	TPTExplainM->AddText("  system where you can choose between");
	TPTExplainM->AddText("  one and three qubits with their");
	TPTExplainM->AddText("  respective state (zero or one), and a");
	TPTExplainM->AddText("  graphic part where you develop the");
	TPTExplainM->AddText("  mathematical form#font[12]{(MATH),} the quantum");
	TPTExplainM->AddText("  circuit#font[12]{(CIRCUIT),} the Visual");
	TPTExplainM->AddText("  representation of the Bloch Sphere");
	TPTExplainM->AddText("  #font[12]{(BLOCHE SPHERE)} and the Matrix#font[12]{(MATRIX)}");
	TPTExplainM->AddText("  for the selected system.");

	TPTExplainM->Draw();
	
	//CONSIDERATIONS
	pad2->cd(1);
	TPaveText *TPTExplainC = new TPaveText(0,0,1,1);
	TPTExplainC->SetTextColor(kBlack);
	TPTExplainC->SetTextSize(0.05);
	TPTExplainC->SetFillColor(kRed-9);
	TPTExplainC->SetMargin(0);
	TPTExplainC->SetTextAlign(1);
	
	TPTExplainC->AddText(" ");
	TPTExplainC->AddText("         #font[22]{#scale[1.4]{CONSIDERATIONS}}");
	TPTExplainC->AddText("   1. To understand how QFT works press");
	TPTExplainC->AddText("      #font[12]{Help}.");
	TPTExplainC->AddText("   2. If you do not have basic knowledge of");
	TPTExplainC->AddText("      quantum gates in QFT press#font[12]{B. Concepts}.");
	TPTExplainC->AddText("      This section will be disabled when you");
	TPTExplainC->AddText("      press#font[12]{Start} and will be enabled");
	TPTExplainC->AddText("      when you press#font[12]{Stop}.");
	TPTExplainC->AddText("   3. To start QFT you need to select the");
	TPTExplainC->AddText("      number of qubits you want to use.");
	TPTExplainC->AddText("      Select the state each qubit will be in");
	TPTExplainC->AddText("      initially. Press#font[12]{Start} to start the");
	TPTExplainC->AddText("      explanation.");
	TPTExplainC->AddText("   4. To exit press#font[12]{Exit}.");
	
	TPTExplainC->Draw();
	
	//PREVIOUS KNOWLEDGE 
	pad2->cd(3);
	TPaveText *TPTExplainB = new TPaveText(0,0,1,1);
	TPTExplainB->SetTextColor(kBlack);
	TPTExplainB->SetTextSize(0.05);
	TPTExplainB->SetFillColor(kBlue-9);
	TPTExplainB->SetMargin(0);
	TPTExplainB->SetTextAlign(1);
	
	TPTExplainB->AddText(" ");
	TPTExplainB->AddText("           #font[22]{#scale[1.4]{PRIOR KNOWLEDGE}}");
	TPTExplainB->AddText("   In general, You should have basic knowledge");
	TPTExplainB->AddText("   about quantum computing, logic gates,");
	TPTExplainB->AddText("   what is a qubit, what is a quantum state");
	TPTExplainB->AddText("   and how it is represented, etc.");
	TPTExplainB->AddText(" ");
	TPTExplainB->AddText("   Sections: ");
	TPTExplainB->AddText("   1. For matemathics, arithmetic and tensor");
	TPTExplainB->AddText("      product.");
	TPTExplainB->AddText("   2. For circuit, how to use a quantum circuit.");
	TPTExplainB->AddText("   3. For bloch Sphere, what is it and how is");
	TPTExplainB->AddText("      it composed.");
	TPTExplainB->AddText("   4. For matrix, nothing.");
	
	TPTExplainB->Draw();
	
	fHelp->Update();
	fHelp->SetEditable(0);
	
}

///////////////////////////////////////////////////  B. CONCEPTS ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  HADAMARD  ////////////////////////////////////////////////////////////////////
void MyMainFrame::DoHadamard(){
	fBHadamard->SetState(kButtonDisabled, kTRUE);
	fBRotation1->SetState(kButtonUp, kTRUE);
	fBRotation2->SetState(kButtonUp, kTRUE);
	fBSwap->SetState(kButtonUp, kTRUE);
	fBHelp->SetState(kButtonUp, kTRUE);
	
	// =================================== PHYSICS H ===========================================
	fCanvastxt = fECanvasExp->GetCanvas();
	fCanvastxt->SetEditable(1);
	fCanvastxt->Clear();
	
	TPaveText *TPTExplainP = new TPaveText(0,0,1,1);
	TPTExplainP->SetTextColor(kBlack);
	TPTExplainP->SetTextSize(0.06);
	TPTExplainP->SetFillColor(kGray);
	TPTExplainP->SetShadowColor(18);
	TPTExplainP->SetMargin(0);
	TPTExplainP->SetTextAlign(1);
	
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText("             #font[22]{#scale[1.4]{PHYSICS}}");
	TPTExplainP->AddText("   The Hadamard gate is one of");
	TPTExplainP->AddText("   the fundamental");
	TPTExplainP->AddText("   transformation gates of");
	TPTExplainP->AddText("   quantum computing.");
	TPTExplainP->AddText("   ");
	TPTExplainP->AddText("   The Hadamard operation is a");
	TPTExplainP->AddText("   rotation ( #pi or 180 #circ about");
	TPTExplainP->AddText("   the XY plane on the Bloch");
	TPTExplainP->AddText("   Sphere), applied to a single");
	TPTExplainP->AddText("   qubit. This creates an equal");
	TPTExplainP->AddText("   superposition of the two basis");
	TPTExplainP->AddText("   states (|0 #GT and |1 #GT), in which");
	TPTExplainP->AddText("   the measurement probability");
	TPTExplainP->AddText("   of individual qubits is half");
	TPTExplainP->AddText("   (50/50).");
	
	TPTExplainP->Draw();
	fCanvastxt->Update();
	fCanvastxt->SetEditable(0);
	
	// =================================== MATH DRAW H ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	
	//Desing
	TLine  *line4= new TLine(0.005,0,0,0.97);
	line4->SetLineWidth(1);
	line4->SetLineColor(14);
	line4->Draw();
	
	TLine *line5 = new TLine(0,0.005,1,0.005);
	line5->SetLineWidth(1);
	line5->SetLineColor(14);
	line5->Draw();
	
	TLine *line6 = new TLine(0.995,0,0.995,0.97);
	line6->SetLineWidth(1);
	line6->SetLineColor(14);
	line6->Draw();
	
	TLine *line7 = new TLine(0.17,0.97,0.995,0.97);
	line7->SetLineWidth(1);
	line7->SetLineColor(14);
	line7->Draw();
	
	TLine *line8 = new TLine(0,0.97,0.025,0.97);
	line8->SetLineWidth(1);
	line8->SetLineColor(14);
	line8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	sprintf(line1, "Hadamard Gate: #color[2]{#hat{H}}");	
	sprintf(line2, "#color[2]{#hat{H}}|0#GT =  #frac{1}{#sqrt{2}} #left( |0#GT +  |1 #GT #right) =  |+#GT");
	sprintf(line3, "#color[2]{#hat{H}}|1 #GT =  #frac{1}{#sqrt{2}} #left( |0#GT -  |1 #GT #right) =  |-#GT");	
 	
	l1=new TLatex(0.05,0.85,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.25,0.60,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	l3=new TLatex(0.25,0.27,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT H ===========================================
	//GetTextCanvas
	fCanvas->cd(1);
	
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	TPTmath->AddText("Mathematically, the #font[12]{#font[22]{Hadamard gate}} ");
	TPTmath->AddText("is an operator applied to ket zero or one.");

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW H ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
	name1->SetTextSize(0.06);
	name1->Draw();
		
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.350,0.66,0.650,0.66);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.640,"#scale[1.7]{#cbar 0 #GT}");
	HD->Draw();

	//Compuerta Hadamard2
	Square = new TPave(0.450,0.585,0.505,0.735,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.465,0.630,"#color[2]{#scale[1.7]{H}}");
	HD->SetLineWidth(2);
	HD->Draw();
	
	HD = new TLatex(0.68,0.640,"#scale[1.7]{#cbar + #GT}");
	HD->Draw();
			
	Rot = new TLatex(0.525,0.760,"#color[2]{#scale[1.7]{#pi}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	//Dibujo Base Circuit
	line = new TLine(0.350,0.33,0.650,0.33);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.310,"#scale[1.7]{#cbar 1 #GT}");
	HD->Draw();
	
	HD = new TLatex(0.68,0.310,"#scale[1.7]{#cbar - #GT}");
	HD->Draw();

	//Compuerta Hadamard2
	Square = new TPave(0.450,0.275,0.505,0.425,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.465,0.320,"#color[2]{#scale[1.7]{H}}");
	HD->SetLineWidth(2);
	HD->Draw();
			
	Rot = new TLatex(0.525,0.450,"#color[2]{#scale[1.7]{#pi}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	fCanvas->Update();

	// =================================== CIRCUIT TEXT H ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 	
 	TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}} ");
	TPTcircuit->AddText("to the ket zero and ket one");
	
	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW H ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.36,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
	name2->SetTextSize(0.06);
	name2->Draw();
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	//PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec0= geom->MakeTube("vec",Iron, 0,2,50);
	vec0->SetLineColor(2);
	
	TGeoVolume *vec1= geom->MakeTube("vec",Iron, 0,2,50);
	vec1->SetLineColor(2);

	TGeoVolume *vec2= geom->MakeTube("vec",Iron, 0,2,50);
	vec2->SetLineColor(2);
	
	TGeoVolume *vec3= geom->MakeTube("vec",Iron, 0,2,50);
	vec3->SetLineColor(2);
	
	TGeoVolume *vec4= geom->MakeTube("vec",Iron, 0,2,50);
	vec4->SetLineColor(2);
	
	TGeoVolume *vec5= geom->MakeTube("vec",Iron, 0,2,50);
	vec5->SetLineColor(2);
	
	TGeoVolume *cone0=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone0->SetLineColor(2);
	
	TGeoVolume *cone1=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone1->SetLineColor(2);
	
	TGeoVolume *cone2=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone2->SetLineColor(2);
	
	TGeoVolume *cone3=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone3->SetLineColor(2);
	
	TGeoVolume *cone4=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone4->SetLineColor(2);
	
	TGeoVolume *cone5=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone5->SetLineColor(2);
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
    vec0->SetLineColorAlpha(2,0.05);
    vec1->SetLineColorAlpha(2,0.10);
    vec2->SetLineColorAlpha(2,0.25);
    vec3->SetLineColorAlpha(2,0.40);
    vec4->SetLineColorAlpha(2,0.75);
    vec5->SetLineColorAlpha(2,1);
	cone0->SetLineColorAlpha(2,0.05);
    cone1->SetLineColorAlpha(2,0.10);
    cone2->SetLineColorAlpha(2,0.25);
    cone3->SetLineColorAlpha(2,0.40);
    cone4->SetLineColorAlpha(2,0.75);
	cone5->SetLineColorAlpha(2,1);
	
	//PRIMER QUBIT (0)
	pad31->cd();
	
	sp0->SetLineColorAlpha(13,0.1);
    sp0->SetFillColorAlpha(13,0.1);
    
	//VECTOR
	top->AddNodeOverlap(vec0,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
	top->AddNodeOverlap(vec1,1,new TGeoCombiTrans(-14,0,45,new TGeoRotation("q0",90,-18,0)));
	top->AddNodeOverlap(vec2,1,new TGeoCombiTrans(-28,0,40,new TGeoRotation("q0",90,-36,0)));
	top->AddNodeOverlap(vec3,1,new TGeoCombiTrans(-40,0,28,new TGeoRotation("q0",90,-54,0)));
	top->AddNodeOverlap(vec4,1,new TGeoCombiTrans(-45,0,14,new TGeoRotation("q0",90,-72,0)));
	top->AddNodeOverlap(vec5,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,-90,0)));
	
	//CONO
	top->AddNodeOverlap(cone0,1,new TGeoCombiTrans(0,0,95,new TGeoRotation("q0",0,0,0)));
	top->AddNodeOverlap(cone1,1,new TGeoCombiTrans(-29,0,90,new TGeoRotation("q0",90,342,0)));
	top->AddNodeOverlap(cone2,1,new TGeoCombiTrans(-54,0,76,new TGeoRotation("q0",90,324,0)));
	top->AddNodeOverlap(cone3,1,new TGeoCombiTrans(-76,0,54,new TGeoRotation("q0",90,306,0)));
	top->AddNodeOverlap(cone4,1,new TGeoCombiTrans(-90,0,29,new TGeoRotation("q0",90,288,0)));
	top->AddNodeOverlap(cone5,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,270,0))); 
	
	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();
   	   	
	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{H}|0 #GT}");
	HD->Draw();
   	
	fCanvas->Update();

	//SEGUNDO QUBIT (1)
	pad32->cd();

	sp1->SetLineColorAlpha(13,0.1);
    sp1->SetFillColorAlpha(13,0.1);
    
    //VECTOR
	top1->AddNodeOverlap(vec0,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
	top1->AddNodeOverlap(vec1,1,new TGeoCombiTrans(14,0,-45,new TGeoRotation("q0",90,-18,0)));
	top1->AddNodeOverlap(vec2,1,new TGeoCombiTrans(28,0,-40,new TGeoRotation("q0",90,-36,0)));
	top1->AddNodeOverlap(vec3,1,new TGeoCombiTrans(40,0,-28,new TGeoRotation("q0",90,-54,0)));
	top1->AddNodeOverlap(vec4,1,new TGeoCombiTrans(45,0,-14,new TGeoRotation("q0",90,-72,0)));
	top1->AddNodeOverlap(vec5,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,-90,0)));
	
	//CONO
	top1->AddNodeOverlap(cone0,1,new TGeoCombiTrans(0,0,-95,new TGeoRotation("q0",0,180,0)));
	top1->AddNodeOverlap(cone1,1,new TGeoCombiTrans(29,0,-90,new TGeoRotation("q0",90,162,0)));
	top1->AddNodeOverlap(cone2,1,new TGeoCombiTrans(54,0,-76,new TGeoRotation("q0",90,144,0)));
	top1->AddNodeOverlap(cone3,1,new TGeoCombiTrans(76,0,-54,new TGeoRotation("q0",90,126,0)));
	top1->AddNodeOverlap(cone4,1,new TGeoCombiTrans(90,0,-29,new TGeoRotation("q0",90,108,0)));
	top1->AddNodeOverlap(cone5,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0))); 
   
   	top1->SetVisibility(0);
   	geom->CloseGeometry();
   	top1->Draw();
   			
   	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{H}|1 #GT}");
	HD->Draw();
   	fCanvas->Update();
	// =================================== BLOCH TEXT H ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);

	TPTbloch->AddText("Application of the #font[12]{#font[22]{Hadamard gate}} ");
	TPTbloch->AddText("to the ket zero (ending in state #font[12]{#font[22]{|+#GT}} ) and");
	TPTbloch->AddText("the ket one (ending in state #font[12]{#font[22]{|-#GT}} ).");
	
	TPTbloch->Draw();
	fCanvas->Update();

	// =================================== MATRIX DRAW H ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
	name3->SetTextSize(0.06);
	name3->Draw();

	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
	
	HD = new TLatex(0.3,0.5,"#scale[2]{#color[2]{#hat{H}}} ");
	HD->Draw();
	
	HD = new TLatex(0.35,0.52,"#scale[1.5]{=   #color[2]{#frac{1}{#sqrt{2}}}}");
	HD->Draw();
	
	TArc *arc = new TArc(0.525,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
   
	arc = new TArc(0.625,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
	
	//Base Matrix
	sprintf(line1, "#color[2]{1}      #color[2]{1} ");
	sprintf(line2, "#color[2]{1}      #color[2]{-1}"); 
 	
	l1=new TLatex(0.5,0.6,line1);
	l1->SetTextSize(0.08);
	l1->Draw();
	
	l2=new TLatex(0.5,0.4,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	fCanvas->Update();
	
	// =================================== MATRIX TEXT H ===========================================
	fCanvas->cd(4);

	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	TPTmatrix->AddText("The Hadamard operator applied to a qubit");
	TPTmatrix->AddText("can be represented with a 2x2 ");
	TPTmatrix->AddText("matrix defined as above.");

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

///////////////////////////////////////////////  ROTATION  PI/2   ///////////////////////////////////////////////////////////////
void MyMainFrame::DoRotation1(){
	fBHadamard->SetState(kButtonUp, kTRUE);
	fBRotation1->SetState(kButtonDisabled, kTRUE);
	fBRotation2->SetState(kButtonUp, kTRUE);
	fBSwap->SetState(kButtonUp, kTRUE);
	fBHelp->SetState(kButtonUp, kTRUE);
	
	// =================================== PHYSICS R1 ===========================================
	fCanvastxt = fECanvasExp->GetCanvas();
	fCanvastxt->SetEditable(1);
	fCanvastxt->Clear();
	
	TPaveText *TPTExplainP = new TPaveText(0,0,1,1);
	TPTExplainP->SetTextColor(kBlack);
	TPTExplainP->SetTextSize(0.06);
	TPTExplainP->SetFillColor(kGray);
	TPTExplainP->SetShadowColor(18);
	TPTExplainP->SetMargin(0);
	TPTExplainP->SetTextAlign(1);
	
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText("             #font[22]{#scale[1.4]{PHYSICS}}");
	TPTExplainP->AddText("   The R_{1} gate is a Z-rotation");
	TPTExplainP->AddText("   gate revolves the state");
	TPTExplainP->AddText("   around the Z-axis an angle");
	TPTExplainP->AddText("   of #pi/2. Note that the");
	TPTExplainP->AddText("   state vector rotates in the"); 
	TPTExplainP->AddText("   anti-clockwise direction.");
	TPTExplainP->AddText("   ");
	TPTExplainP->AddText("   Is a unitary gate that");
	TPTExplainP->AddText("   acts on only one qubit.");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	
	
	TPTExplainP->Draw();
	fCanvastxt->Update();
	fCanvastxt->SetEditable(0);

	// =================================== MATH DRAW R1 ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	
	//Desing
	TLine  *line4= new TLine(0.005,0,0,0.97);
	line4->SetLineWidth(1);
	line4->SetLineColor(14);
	line4->Draw();
	
	TLine *line5 = new TLine(0,0.005,1,0.005);
	line5->SetLineWidth(1);
	line5->SetLineColor(14);
	line5->Draw();
	
	TLine *line6 = new TLine(0.995,0,0.995,0.97);
	line6->SetLineWidth(1);
	line6->SetLineColor(14);
	line6->Draw();
	
	TLine *line7 = new TLine(0.17,0.97,0.995,0.97);
	line7->SetLineWidth(1);
	line7->SetLineColor(14);
	line7->Draw();
	
	TLine *line8 = new TLine(0,0.97,0.025,0.97);
	line8->SetLineWidth(1);
	line8->SetLineColor(14);
	line8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	sprintf(line1, "Rotation Gate: #color[2]{#hat{R_{1}}}");	
	sprintf(line2, "#color[2]{#hat{R_{1}}} |+ #GT = #left( |0#GT + #color[2]{e^{#scale[1.1]{#frac{i#pi}{2}}}} |1 #GT #right) =  |i#GT");
	sprintf(line3, "#color[2]{#hat{R_{1}}} |- #GT = #left( |0#GT + #color[2]{e^{#scale[1.2]{#frac{i#pi}{2}}}} |1 #GT #right) =  |-i#GT");	
 	
	l1=new TLatex(0.05,0.85,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.25,0.60,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	l3=new TLatex(0.25,0.27,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT R1 ===========================================
	//GetTextCanvas
	fCanvas->cd(1);
	
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	TPTmath->AddText("The #font[12]{#font[22]{Rotation gate #color[1]{R_{1}}}} is a rotation given by #color[2]{exp#left[ #frac{i#pi}{2} #right)}.");

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW R1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
	name1->SetTextSize(0.06);
	name1->Draw();
		
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.350,0.66,0.650,0.66);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.640,"#scale[1.7]{#cbar + #GT}");
	HD->Draw();
	
	HD = new TLatex(0.68,0.640,"#scale[1.7]{#cbar i #GT}");
	HD->Draw();

	//Compuerta Rotation2
	Square = new TPave(0.451,0.585,0.506,0.735,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.464,0.630,"#color[2]{#scale[1.7]{R_{1}}}");
	HD->SetLineWidth(2);
	HD->Draw();
			
	Rot = new TLatex(0.528,0.760,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	//Dibujo Base Circuit
	line = new TLine(0.350,0.33,0.650,0.33);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.310,"#scale[1.7]{#cbar - #GT}");
	HD->Draw();
	
	HD = new TLatex(0.68,0.310,"#scale[1.7]{#cbar -i #GT}");
	HD->Draw();

	//Compuerta Rotation2
	Square = new TPave(0.451,0.275,0.506,0.425,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.464,0.320,"#color[2]{#scale[1.7]{R_{1}}}");
	HD->SetLineWidth(2);
	HD->Draw();
			
	Rot = new TLatex(0.528,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	fCanvas->Update();

	// =================================== CIRCUIT TEXT R1 ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 	
 	TPTcircuit->AddText("#font[12]{#font[22]{Rotation gate}} #color[1]{R_{1}} applied to");
	TPTcircuit->AddText("to the state plus and minus.");
	
	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW R1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.36,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
	name2->SetTextSize(0.06);
	name2->Draw();
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	//PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec0= geom->MakeTube("vec",Iron, 0,2,50);
	vec0->SetLineColor(2);
	
	TGeoVolume *vec1= geom->MakeTube("vec",Iron, 0,2,50);
	vec1->SetLineColor(2);

	TGeoVolume *vec2= geom->MakeTube("vec",Iron, 0,2,50);
	vec2->SetLineColor(2);
	
	TGeoVolume *vec3= geom->MakeTube("vec",Iron, 0,2,50);
	vec3->SetLineColor(2);
	
	TGeoVolume *vec4= geom->MakeTube("vec",Iron, 0,2,50);
	vec4->SetLineColor(2);
	
	TGeoVolume *vec5= geom->MakeTube("vec",Iron, 0,2,50);
	vec5->SetLineColor(2);
	
	TGeoVolume *cone0=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone0->SetLineColor(2);
	
	TGeoVolume *cone1=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone1->SetLineColor(2);
	
	TGeoVolume *cone2=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone2->SetLineColor(2);
	
	TGeoVolume *cone3=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone3->SetLineColor(2);
	
	TGeoVolume *cone4=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone4->SetLineColor(2);
	
	TGeoVolume *cone5=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone5->SetLineColor(2); 
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	vec0->SetLineColorAlpha(2,0.05);
    vec1->SetLineColorAlpha(2,0.10);
    vec2->SetLineColorAlpha(2,0.25);
    vec3->SetLineColorAlpha(2,0.40);
    vec4->SetLineColorAlpha(2,0.75);
    vec5->SetLineColorAlpha(2,1);
	cone0->SetLineColorAlpha(2,0.05);
    cone1->SetLineColorAlpha(2,0.10);
    cone2->SetLineColorAlpha(2,0.25);
    cone3->SetLineColorAlpha(2,0.40);
    cone4->SetLineColorAlpha(2,0.75);
	cone5->SetLineColorAlpha(2,1);
	
	//PRIMER QUBIT (0)
	pad31->cd();
	
	sp0->SetLineColorAlpha(13,0.1);
    sp0->SetFillColorAlpha(13,0.1);
    
	//VECTOR
	top->AddNodeOverlap(vec0,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("q0",90,90,0)));
	top->AddNodeOverlap(vec1,1,new TGeoCombiTrans(-45,-14,0,new TGeoRotation("q0",-72,90,0)));
	top->AddNodeOverlap(vec2,1,new TGeoCombiTrans(-40,-28,0,new TGeoRotation("q0",-54,90,0)));
	top->AddNodeOverlap(vec3,1,new TGeoCombiTrans(-28,-40,0,new TGeoRotation("q0",-36,90,0)));
	top->AddNodeOverlap(vec4,1,new TGeoCombiTrans(-14,-45,0,new TGeoRotation("q0",-18,90,0)));
	top->AddNodeOverlap(vec5,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
  
	//CONE
	top->AddNodeOverlap(cone0,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("q0",90,270,0)));
	top->AddNodeOverlap(cone1,1,new TGeoCombiTrans(-90,-29,0,new TGeoRotation("q0",-72,90,0)));
	top->AddNodeOverlap(cone2,1,new TGeoCombiTrans(-76,-54,0,new TGeoRotation("q0",-54,90,0)));
	top->AddNodeOverlap(cone3,1,new TGeoCombiTrans(-54,-76,0,new TGeoRotation("q0",-36,90,0)));
	top->AddNodeOverlap(cone4,1,new TGeoCombiTrans(-29,-90,0,new TGeoRotation("q0",-18,90,0)));
	top->AddNodeOverlap(cone5,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0))); 
	
	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();
   	   	
	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{R_{1}}|+ #GT}");
	HD->Draw();
   	
	fCanvas->Update();

	//SEGUNDO QUBIT (1)
	pad32->cd();

	sp1->SetLineColorAlpha(13,0.1);
    sp1->SetFillColorAlpha(13,0.1);
    
    	//VECTOR
	top1->AddNodeOverlap(vec0,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("q0",90,-90,0)));
	top1->AddNodeOverlap(vec1,1,new TGeoCombiTrans(45,14,0,new TGeoRotation("q0",-72,90,0)));
	top1->AddNodeOverlap(vec2,1,new TGeoCombiTrans(40,28,0,new TGeoRotation("q0",-54,90,0)));
	top1->AddNodeOverlap(vec3,1,new TGeoCombiTrans(28,40,0,new TGeoRotation("q0",-36,90,0)));
	top1->AddNodeOverlap(vec4,1,new TGeoCombiTrans(14,45,0,new TGeoRotation("q0",-18,90,0)));
	top1->AddNodeOverlap(vec5,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));

	//CONE
	top1->AddNodeOverlap(cone0,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("q0",90,-270,0)));
	top1->AddNodeOverlap(cone1,1,new TGeoCombiTrans(90,29,0,new TGeoRotation("q0",-72,-90,0)));
	top1->AddNodeOverlap(cone2,1,new TGeoCombiTrans(76,54,0,new TGeoRotation("q0",-54,-90,0)));
	top1->AddNodeOverlap(cone3,1,new TGeoCombiTrans(54,76,0,new TGeoRotation("q0",-36,-90,0)));
	top1->AddNodeOverlap(cone4,1,new TGeoCombiTrans(29,90,0,new TGeoRotation("q0",-18,-90,0)));
	top1->AddNodeOverlap(cone5,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0)));
   
   	top1->SetVisibility(0);
   	geom->CloseGeometry();
   	top1->Draw();
   			
   	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{R_{1}}|- #GT}");
	HD->Draw();
   	fCanvas->Update();
	// =================================== BLOCH TEXT R1 ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);

	TPTbloch->AddText("Application of the #font[12]{#font[22]{Rotation gate}} ");
	TPTbloch->AddText("to the ket zero (ending in state #font[12]{#font[22]{|i#GT}} ) and");
	TPTbloch->AddText("the ket one (ending in state #font[12]{#font[22]{|-i#GT}} ).");
	
	TPTbloch->Draw();
	fCanvas->Update();

	// =================================== MATRIX DRAW R1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
	name3->SetTextSize(0.06);
	name3->Draw();

	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
	
	HD = new TLatex(0.31,0.5,"#scale[2]{#color[2]{#hat{R_{1}}  =}}");
	HD->Draw();
	
	TArc *arc = new TArc(0.5,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
   
	arc = new TArc(0.625,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
	
	//Base Matrix
	sprintf(line1, "#color[2]{1}     #color[2]{0} ");
	sprintf(line2, "#color[2]{0}    #color[2]{e^{#scale[1.1]{#frac{i#pi}{2}}}}"); 
 	
	l1=new TLatex(0.5,0.6,line1);
	l1->SetTextSize(0.08);
	l1->Draw();
	
	l2=new TLatex(0.5,0.4,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	fCanvas->Update();
	
	// =================================== MATRIX TEXT R1 ===========================================
	fCanvas->cd(4);

	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	TPTmatrix->AddText("The Rotation operator applied to a qubit");
	TPTmatrix->AddText("can be represented with a 2x2 ");
	TPTmatrix->AddText("matrix defined as above.");

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

///////////////////////////////////////////////  ROTATION  PI/4   ///////////////////////////////////////////////////////////////
void MyMainFrame::DoRotation2(){
	fBHadamard->SetState(kButtonUp, kTRUE);
	fBRotation1->SetState(kButtonUp, kTRUE);
	fBRotation2->SetState(kButtonDisabled, kTRUE);
	fBSwap->SetState(kButtonUp, kTRUE);
	fBHelp->SetState(kButtonUp, kTRUE);
	
	// =================================== PHYSICS R2 ===========================================
	fCanvastxt = fECanvasExp->GetCanvas();
	fCanvastxt->SetEditable(1);
	fCanvastxt->Clear();
	
	TPaveText *TPTExplainP = new TPaveText(0,0,1,1);
	TPTExplainP->SetTextColor(kBlack);
	TPTExplainP->SetTextSize(0.06);
	TPTExplainP->SetFillColor(kGray);
	TPTExplainP->SetShadowColor(18);
	TPTExplainP->SetMargin(0);
	TPTExplainP->SetTextAlign(1);
	
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText("             #font[22]{#scale[1.4]{PHYSICS}}");
	TPTExplainP->AddText("   The R_{2} gate is a Z-rotation");
	TPTExplainP->AddText("   gate revolves the state");
	TPTExplainP->AddText("   around the Z-axis an angle");
	TPTExplainP->AddText("   of #pi/4. Note that the");
	TPTExplainP->AddText("   state vector rotates in the"); 
	TPTExplainP->AddText("   anti-clockwise direction.");
	TPTExplainP->AddText("   ");
	TPTExplainP->AddText("   Is a unitary gate that");
	TPTExplainP->AddText("   acts on only one qubit.");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText(" ");
	
	TPTExplainP->Draw();
	fCanvastxt->Update();
	fCanvastxt->SetEditable(0);

	// =================================== MATH DRAW R2 ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	
	//Desing
	TLine  *line4= new TLine(0.005,0,0,0.97);
	line4->SetLineWidth(1);
	line4->SetLineColor(14);
	line4->Draw();
	
	TLine *line5 = new TLine(0,0.005,1,0.005);
	line5->SetLineWidth(1);
	line5->SetLineColor(14);
	line5->Draw();
	
	TLine *line6 = new TLine(0.995,0,0.995,0.97);
	line6->SetLineWidth(1);
	line6->SetLineColor(14);
	line6->Draw();
	
	TLine *line7 = new TLine(0.17,0.97,0.995,0.97);
	line7->SetLineWidth(1);
	line7->SetLineColor(14);
	line7->Draw();
	
	TLine *line8 = new TLine(0,0.97,0.025,0.97);
	line8->SetLineWidth(1);
	line8->SetLineColor(14);
	line8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	sprintf(line1, "Rotation Gate: #color[2]{#hat{R_{2}}}");	
	sprintf(line2, "#color[2]{#hat{R_{2}}} |i #GT = #left( |0#GT + #color[2]{e^{#scale[1.1]{#frac{i#pi}{4}}}} |1 #GT #right)");
	sprintf(line3, "#color[2]{#hat{R_{2}}} |-i #GT = #left( |0#GT + #color[2]{e^{#scale[1.1]{#frac{i#pi}{4}}}} |1 #GT #right)");	
 	
	l1=new TLatex(0.05,0.85,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.25,0.60,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	l3=new TLatex(0.25,0.27,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT R2 ===========================================
	//GetTextCanvas
	fCanvas->cd(1);
	
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	TPTmath->AddText("The #font[12]{#font[22]{Rotation gate #color[1]{R_{2}}}} is a rotation given by #color[2]{exp#left[ #frac{i#pi}{4} #right)}.");

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW R2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
	name1->SetTextSize(0.06);
	name1->Draw();
		
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.350,0.66,0.650,0.66);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.640,"#scale[1.7]{#cbar i #GT}");
	HD->Draw();

	//Compuerta Rotation2
	Square = new TPave(0.451,0.585,0.506,0.735,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.464,0.630,"#color[2]{#scale[1.7]{R_{2}}}");
	HD->SetLineWidth(2);
	HD->Draw();
			
	Rot = new TLatex(0.528,0.760,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	//Dibujo Base Circuit
	line = new TLine(0.350,0.33,0.650,0.33);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.310,"#scale[1.7]{#cbar -i #GT}");
	HD->Draw();

	//Compuerta Rotation2
	Square = new TPave(0.451,0.275,0.506,0.425,2,"br");
	Square->Draw();
 
 	HD = new TLatex(0.464,0.320,"#color[2]{#scale[1.7]{R_{2}}}");
	HD->SetLineWidth(2);
	HD->Draw();
			
	Rot = new TLatex(0.528,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
	Rot->SetLineWidth(2);
	Rot->Draw();
	
	fCanvas->Update();

	// =================================== CIRCUIT TEXT R2 ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 	
 	TPTcircuit->AddText("#font[12]{#font[22]{Rotation gate}} #color[1]{R_2}} applied to");
	TPTcircuit->AddText("to the state #font[12]{i} and minus #font[12]{-i}");
	
	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW R2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.36,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
	name2->SetTextSize(0.06);
	name2->Draw();
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	//PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec0= geom->MakeTube("vec",Iron, 0,2,50);
	vec0->SetLineColor(2);
	
	TGeoVolume *vec1= geom->MakeTube("vec",Iron, 0,2,50);
	vec1->SetLineColor(2);

	TGeoVolume *vec2= geom->MakeTube("vec",Iron, 0,2,50);
	vec2->SetLineColor(2);
	
	TGeoVolume *vec3= geom->MakeTube("vec",Iron, 0,2,50);
	vec3->SetLineColor(2);
	
	TGeoVolume *vec4= geom->MakeTube("vec",Iron, 0,2,50);
	vec4->SetLineColor(2);
	
	TGeoVolume *vec5= geom->MakeTube("vec",Iron, 0,2,50);
	vec5->SetLineColor(2);
	
	TGeoVolume *cone0=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone0->SetLineColor(2);
	
	TGeoVolume *cone1=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone1->SetLineColor(2);
	
	TGeoVolume *cone2=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone2->SetLineColor(2);
	
	TGeoVolume *cone3=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone3->SetLineColor(2);
	
	TGeoVolume *cone4=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone4->SetLineColor(2);
	
	TGeoVolume *cone5=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone5->SetLineColor(2);  
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	vec0->SetLineColorAlpha(2,0.05);
    vec1->SetLineColorAlpha(2,0.2);
    vec2->SetLineColorAlpha(2,1);
	cone0->SetLineColorAlpha(2,0.05);
    cone1->SetLineColorAlpha(2,0.2);
    cone2->SetLineColorAlpha(2,1);

	
	//PRIMER QUBIT (0)
	pad31->cd();
	
	sp0->SetLineColorAlpha(13,0.1);
    sp0->SetFillColorAlpha(13,0.1);
    
	//VECTOR
	top->AddNodeOverlap(vec0,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(vec1,1,new TGeoCombiTrans(18,-43,0,new TGeoRotation("q0",22.5,90,0)));
	top->AddNodeOverlap(vec2,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("q0",45,90,0)));
	
	//CONE
	top->AddNodeOverlap(cone0,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(cone1,1,new TGeoCombiTrans(34,-82,0,new TGeoRotation("q0",22.5,90,0)));
	top->AddNodeOverlap(cone2,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("q0",45,90,0)));
	
	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();
   	   	
	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{R_{2}}|i #GT}");
	HD->Draw();
   	
	fCanvas->Update();

	//SEGUNDO QUBIT (1)
	pad32->cd();

	sp1->SetLineColorAlpha(13,0.1);
    sp1->SetFillColorAlpha(13,0.1);
    
    //VECTOR
	top1->AddNodeOverlap(vec0,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(vec1,1,new TGeoCombiTrans(-18,43,0,new TGeoRotation("q0",22.5,90,0)));
	top1->AddNodeOverlap(vec2,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("q0",45,90,0)));
	
	//CONE
	top1->AddNodeOverlap(cone0,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0)));
	top1->AddNodeOverlap(cone1,1,new TGeoCombiTrans(-34,82,0,new TGeoRotation("q0",22.5,-90,0)));
	top1->AddNodeOverlap(cone2,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("q0",45,-90,0)));
   
   	top1->SetVisibility(0);
   	geom->CloseGeometry();
   	top1->Draw();
   			
   	HD = new TLatex(-0.95,0.75,"#scale[2]{#hat{R_{2}}|-i #GT}");
	HD->Draw();
   	fCanvas->Update();
	// =================================== BLOCH TEXT R2 ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);

	TPTbloch->AddText("Application of the #font[12]{#font[22]{Rotation gate}} ");
	TPTbloch->AddText("to the ket #font[12]{|i#GT} ) and");
	TPTbloch->AddText("the ket #font[12]{|-i#GT}).");
	
	TPTbloch->Draw();
	fCanvas->Update();

	// =================================== MATRIX DRAW R2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
	name3->SetTextSize(0.06);
	name3->Draw();

	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
	
	HD = new TLatex(0.31,0.5,"#scale[2]{#color[2]{#hat{R_{2}}  =}}");
	HD->Draw();
	
	TArc *arc = new TArc(0.5,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
   
	arc = new TArc(0.625,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
	
	//Base Matrix
	sprintf(line1, "#color[2]{1}     #color[2]{0} ");
	sprintf(line2, "#color[2]{0}    #color[2]{e^{#scale[1.1]{#frac{i#pi}{4}}}}"); 
 	
	l1=new TLatex(0.5,0.6,line1);
	l1->SetTextSize(0.08);
	l1->Draw();
	
	l2=new TLatex(0.5,0.4,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	fCanvas->Update();
	
	// =================================== MATRIX TEXT R2 ===========================================
	fCanvas->cd(4);

	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	TPTmatrix->AddText("The Rotation operator applied to a qubit");
	TPTmatrix->AddText("can be represented with a 2x2 ");
	TPTmatrix->AddText("matrix defined as above.");

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}



///////////////////////////////////////////////////  SWAP  ////////////////////////////////////////////////////////////////////
void MyMainFrame::DoSwap(){
	fBHadamard->SetState(kButtonUp, kTRUE);
	fBRotation1->SetState(kButtonUp, kTRUE);
	fBRotation2->SetState(kButtonUp, kTRUE);
	fBSwap->SetState(kButtonDisabled, kTRUE);
	fBHelp->SetState(kButtonUp, kTRUE);

	// =================================== PHYSICS S ===========================================
	fCanvastxt = fECanvasExp->GetCanvas();
	fCanvastxt->SetEditable(1);
	fCanvastxt->Clear();
	
	TPaveText *TPTExplainP = new TPaveText(0,0,1,1);
	TPTExplainP->SetTextColor(kBlack);
	TPTExplainP->SetTextSize(0.06);
	TPTExplainP->SetFillColor(kGray);
	TPTExplainP->SetShadowColor(18);
	TPTExplainP->SetMargin(0);
	TPTExplainP->SetTextAlign(1);
	
	TPTExplainP->AddText(" ");
	TPTExplainP->AddText("             #font[22]{#scale[1.4]{PHYSICS}}");
	TPTExplainP->AddText("   The SWAP gate is two-qubit");
	TPTExplainP->AddText("   operation. It is a building");
	TPTExplainP->AddText("   block that allows us to");
	TPTExplainP->AddText("   permute the information");
	TPTExplainP->AddText("   stored in a set of qubits,");
	TPTExplainP->AddText("   that is SWAP gate moves"); 
	TPTExplainP->AddText("   the quantum state");
	TPTExplainP->AddText("   between two qubits.");
	TPTExplainP->AddText("   ");
	TPTExplainP->AddText("   Note: Physically it is");
	TPTExplainP->AddText("   an immediate process,");
	TPTExplainP->AddText("   here the bloch sphere shows");
	TPTExplainP->AddText("   the information transition");
	TPTExplainP->AddText("   with the colors as a visual");
	TPTExplainP->AddText("   reference of the SWAP gate.");
	TPTExplainP->AddText("   ");
	
	TPTExplainP->Draw();
	fCanvastxt->Update();
	fCanvastxt->SetEditable(0);

	// =================================== MATH DRAW S ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	
	//Desing
	line04= new TLine(0.005,0,0,0.97);
	line04->SetLineWidth(1);
	line04->SetLineColor(14);
	line04->Draw();
	
	line05 = new TLine(0,0.005,1,0.005);
	line05->SetLineWidth(1);
	line05->SetLineColor(14);
	line05->Draw();
	
	line06 = new TLine(0.995,0,0.995,0.97);
	line06->SetLineWidth(1);
	line06->SetLineColor(14);
	line06->Draw();
	
	line07 = new TLine(0.17,0.97,0.995,0.97);
	line07->SetLineWidth(1);
	line07->SetLineColor(14);
	line07->Draw();
	
	line08 = new TLine(0,0.97,0.025,0.97);
	line08->SetLineWidth(1);
	line08->SetLineColor(14);
	line08->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	sprintf(line1, "Swap Gate: #color[2]{SWAP}");	
	sprintf(line2, "|#Psi#GT =  #color[2]{#left( #alpha|0#GT + #beta|1 #GT #right)} #otimes #color[4]{#left( #gamma |0#GT + #lambda |1 #GT #right)}");
	sprintf(line3, "SWAP|#Psi#GT =  #color[4]{#left( #gamma |0#GT + #lambda |1 #GT #right)} #otimes #color[2]{#left( #alpha|0#GT + #beta|1 #GT #right)}");
 	
	l1=new TLatex(0.05,0.85,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.05,0.60,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	l3=new TLatex(0.05,0.27,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
	
	l4=new TLatex(0.42,0.15,"#color[4]{x_{1}}                #color[2]{x_{0}}");
	l4->SetTextSize(0.08);
	l4->Draw();
	
	l5=new TLatex(0.29,0.5,"#color[2]{x_{1}}                 #color[4]{x_{0}}");
	l5->SetTextSize(0.08);
	l5->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT S ===========================================
	//GetTextCanvas
	fCanvas->cd(1);
	
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	// he #font[12]{#font[22]{Swap gate}} swaps the state of the two qubits  involved in the operation.
	TPTmath->AddText("Mathematically, the state of the ");
	TPTmath->AddText("qubit#color[2]{x_{1}} swap with the state of the qubit#color[4]{x_{0}.}");

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW S ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	
	//Desing
	line04->Draw();
	line05->Draw();
	line06->Draw();
	
	line07 = new TLine(0.22,0.97,0.995,0.97);
	line07->Draw();
	line08->Draw();
	
	name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
	name1->SetTextSize(0.06);
	name1->Draw();
		
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.350,0.66,0.650,0.66);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.640,"#scale[1.7]{#color[4]{#cbar x_{0} #GT}}");
	HD->Draw();
			
	HD = new TLatex(0.68,0.640,"#scale[1.7]{#color[2]{#cbar x_{0} #GT}}");
	HD->Draw();
	
	//Dibujo Base Circuit
	line = new TLine(0.350,0.33,0.650,0.33);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.310,"#scale[1.7]{#color[2]{#cbar x_{1} #GT}}");
	HD->Draw();
	
	HD = new TLatex(0.68,0.310,"#scale[1.7]{#color[4]{#cbar x_{1} #GT}}");
	HD->Draw();
	
	line = new TLine(0.5,0.33,0.5,0.66);
	line->SetLineWidth(3);
	line->Draw();
	
	x = new TLatex(0.4825,0.6225,"#scale[2.5]{#color[2]{X}}");
	x->SetLineWidth(2);
	x->Draw();

	x = new TLatex(0.4825,0.2925,"#scale[2.5]{#color[4]{X}}");
	x->SetLineWidth(2);
	x->Draw();
	
	fCanvas->Update();

	// =================================== CIRCUIT TEXT S ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 	
	TPTcircuit->AddText("The state of#color[1]{x_{1}} becomes that of#color[1]{x_{0}} and the state of");
	TPTcircuit->AddText("#color[1]{x_{0}} becomes that of#color[1]{x_{1}}.");
	
	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW S ===========================================
	//start a Timer
	fCanvas->cd(3);
	name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
	name2->SetTextSize(0.06);
	name2->Draw();
	
	//Desing
	line04->Draw();
	line05->Draw();
	line06->Draw();
	
	line07 = new TLine(0.36,0.97,0.995,0.97);
	line07->Draw();
	line08->Draw();
	
    timer = new TTimer(600);
    timer->SetCommand("AnimateDown()");
    timer->TurnOn();
    
    timer1 = new TTimer(600);
    timer1->SetCommand("AnimateUp()");
	
	// =================================== BLOCH TEXT S ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);

	TPTbloch->AddText("The state of the ");
	TPTbloch->AddText("qubit #color[1]{x_{1}} swap with the state of the qubit #color[1]{x_{0}}.");
	
	TPTbloch->Draw();
	fCanvas->Update();

	// =================================== MATRIX DRAW S ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	
	//Desing
	line04->Draw();
	line05->Draw();
	line06->Draw();
	
	line07 = new TLine(0.22,0.97,0.995,0.97);
	line07->Draw();
	line08->Draw();
	
	name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
	name3->SetTextSize(0.06);
	name3->Draw();

	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
	
	HD = new TLatex(0.2,0.5,"#scale[2]{#color[2]{SWAP}  =} ");
	HD->Draw();
	
	TArc *arc = new TArc(0.55,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.3);
	arc->SetR2(0.11);
	arc->Draw();
   
	arc = new TArc(0.70,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.3);
	arc->SetR2(0.11);
	arc->Draw();
 	
	l1=new TLatex(0.51,0.65,"#color[2]{1}   #color[2]{0}   #color[2]{0}   #color[2]{0}");
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.51,0.55,"#color[2]{0}   #color[2]{0}   #color[2]{1}   #color[2]{0}");
	l2->SetTextSize(0.08);
	l2->Draw();

	l3=new TLatex(0.51,0.45,"#color[2]{0}   #color[2]{1}   #color[2]{0}   #color[2]{0}");
	l3->SetTextSize(0.08);
	l3->Draw();

	l4=new TLatex(0.51,0.35,"#color[2]{0}   #color[2]{0}   #color[2]{0}   #color[2]{1}");
	l4->SetTextSize(0.08);
	l4->Draw();
	
	// =================================== MATRIX TEXT S ===========================================
	fCanvas->cd(4);

	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	TPTmatrix->AddText("The Swap operator applied to a qubit");
	TPTmatrix->AddText("can be represented with a 4x4 ");
	TPTmatrix->AddText("matrix defined as above.");

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

/////////////////////////////////////////////////// ANIMATE DOWN ////////////////////////////////////////////////////////////////////

void AnimateDown(){
	color -= 0.2; 
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->cd(3);
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	//PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	pad31->cd();

	sp0->SetLineColorAlpha(4,color);
   	sp0->SetFillColorAlpha(4,color);
  
	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();
   	   	
	HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{0} #GT}}");
	HD->Draw();
   	
	fCanvas->Update();

	//SEGUNDO QUBIT
	pad32->cd();

	sp1->SetLineColorAlpha(2,color);
    sp1->SetFillColorAlpha(2,color);
   
   	top1->SetVisibility(0);
   	geom->CloseGeometry();
   	top1->Draw();
   			
   	HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{1} #GT}}");
	HD->Draw();
   	fCanvas->Update();
   	
   	if(color<0.1){
   		timer->TurnOff();
   		timer1->TurnOn();
   	}
}

/////////////////////////////////////////////////// ANIMATE UP ////////////////////////////////////////////////////////////////////

void AnimateUp(){
	color += 0.2; 
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->cd(3);
	
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	//PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	pad31->cd();
	
	sp0->SetLineColorAlpha(2,color);
   	sp0->SetFillColorAlpha(2,color);

	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();
   	   	
	HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{0} #GT}}");
	HD->Draw();
   	
	fCanvas->Update();

	//SEGUNDO QUBIT
	pad32->cd();

	sp1->SetLineColorAlpha(4,color);
    sp1->SetFillColorAlpha(4,color);
   
   	top1->SetVisibility(0);
   	geom->CloseGeometry();
   	top1->Draw();
   			
   	HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{1} #GT}}");
	HD->Draw();
   	fCanvas->Update();
   	
   	if(color==1){
   		timer1->Stop();
   	}
}

///////////////////////////////////////////////////  QFT PROCESS ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  QUBIT  1 //////////////////////////////////////////////////////////////////// 
void MyMainFrame::csDrawQ1(){
	// =================================== MATH DRAW Q1 ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	//Desing
	TLine *line4= new TLine(0.005,0,0,0.97);
	line4->SetLineWidth(1);
	line4->SetLineColor(14);
	line4->Draw();
	
	TLine *line5 = new TLine(0,0.005,1,0.005);
	line5->SetLineWidth(1);
	line5->SetLineColor(14);
	line5->Draw();
	
	TLine *line6 = new TLine(0.995,0,0.995,0.97);
	line6->SetLineWidth(1);
	line6->SetLineColor(14);
	line6->Draw();
	
	TLine *line7 = new TLine(0.17,0.97,0.995,0.97);
	line7->SetLineWidth(1);
	line7->SetLineColor(14);
	line7->Draw();
	
	TLine *line8 = new TLine(0,0.97,0.025,0.97);
	line8->SetLineWidth(1);
	line8->SetLineColor(14);
	line8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	switch(Break){
		case 0: 
			sprintf(line1, "QFT|x#GT = #frac{1}{#sqrt{N}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{n-j-k}  x_{n-j} #right) |1 #GT #right)");
			sprintf(line2, "| #tilde{x}#GT = #frac{1}{#color[2]{#sqrt{2}}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{#color[2]{1}-j-k}  x_{#color[2]{1}-j} #right) |1 #GT #right)");
	 
			sprintf(line3, "| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #color[2]{#otimes} #left( |0#GT +  exp #left(2#pi i #sum 2^{1-j-#color[2]{1}}  x_{1-j} #right) |1 #GT #right)");
	
	
			l4 = new TLatex(0.26,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.273,0.875,"#scale[1.2]{n}");
			l5->Draw();

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{#color[2]{1}}");
			l7->Draw();

			l8 = new TLatex(0.19,0.095,"#scale[1.2]{#color[2]{k=1}}");
			l8->Draw();
	
			l9 = new TLatex(0.205,0.225,"#scale[1.2]{#color[2]{1}}");
			l9->Draw();

			l10 = new TLatex(0.63,0.71,"#scale[1.2]{j=1}");
			l10->Draw();
	
			l11 = new TLatex(0.64,0.895,"#scale[1.2]{n}");
			l11->Draw();

			l12 = new TLatex(0.563,0.41,"#scale[1.2]{j=1}");
			l12->Draw();

			l13 = new TLatex(0.573,0.595,"#scale[1.2]{#color[2]{1}}");
			l13->Draw();

			l14 = new TLatex(0.563,0.06,"#scale[1.2]{j=1}");
			l14->Draw();

			l15 = new TLatex(0.573,0.245,"#scale[1.2]{1}");
			l15->Draw();

		break;  
		case 1: 
			//Formulacion general 1 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{-j}  x_{1-j}} #right) |1 #GT #right)");
			sprintf(line2, "#sum_{j=1}^{1} 2^{-j} x_{1-j} =  2^{-1} x_{1-1}");
			sprintf(line3, "#sum_{j=1}^{1} 2^{-j} x_{1-j} = #frac{x_{0}}{2}"); 
	 
			l4 = new TLatex(0.518,0.720,"#scale[1.2]{#color[2]{j=1}}");
			l4->Draw();

			l5 = new TLatex(0.524,0.895,"#scale[1.2]{#color[2]{1}}");
			l5->Draw();
		 
		break;
		case 2:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{-j}  x_{1-j}} #right) |1 #GT #right)"); 
			sprintf(line2, "#sum_{j=1}^{1} 2^{-j} x_{1-j} = #color[2]{#frac{x_{0}}{2}}"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(2#pi i #bullet #color[2]{#frac{x_{0}}{2}} #right) |1 #GT #right)"); 
	 
			l4 = new TLatex(0.518,0.720,"#scale[1.2]{#color[2]{j=1}}");
			l4->Draw();

			l5 = new TLatex(0.524,0.895,"#scale[1.2]{#color[2]{1}}");
			l5->Draw();
		break;
		case 3:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(#color[2]{2#pi i #bullet #frac{x_{0}}{2}} #right) |1 #GT #right)");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(#color[2]{#pi i x_{0}} #right) |1 #GT #right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #color[2]{#left( |0#GT +  exp #left(#pi i x_{0} #right) |1 #GT #right)}"); 
		break;
		case 4:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{2}}  #left( |0#GT +  exp #left(#color[2]{#pi i x_{0}} #right) |1 #GT #right)"); 
			sprintf(line3," ");
			
		break;
	}
 	
	l1=new TLatex(0.02,0.8,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.02,0.5,line2);
	l2->SetTextSize(0.08);
	l2->Draw();


	l3=new TLatex(0.02,0.15,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT Q1 ===========================================
	fCanvas->cd(1);
	//GetTextCanvas
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTmath->AddText("From the general formula, replace #font[22]{#color[2]{n=1}}. ");
			TPTmath->AddText("The tensor product #font[12]{#font[22]{k}} goes from one ");
			TPTmath->AddText("to #font[12]{#font[22]{n}}. For the first case #font[12]{#font[22]{k=1}}.");
		break;  
		case 1: 
			TPTmath->AddText("The sum is solved.");
		break;
		case 2:
			TPTmath->AddText("It is replaced in the general equation.");
		break;
		case 3:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and the final result is obtained.");
		break;
		case 4:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard gate}} to the qubit.");
		break;
	}	

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW Q1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	switch(Break){
		case 4:
			name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
			name1->SetTextSize(0.06);
			name1->Draw();
		break;
		default:
			name1 = new TLatex(0.05,0.95,"#color[14]{CIRCUIT}");
			name1->SetTextSize(0.06);
			name1->Draw();
		break;
	}
		
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.350,0.500,0.650,0.500);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.225,0.480,"#scale[1.7]{#cbar x_{0}#GT}");
	HD->Draw();


	switch(Break){
		case 4:  
			//Compuerta Hadamard2
			Square = new TPave(0.450,0.425,0.505,0.575,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.465,0.470,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
			
			Rot = new TLatex(0.525,0.600,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
	}

	fCanvas->Update();

	// =================================== CIRCUIT TEXT Q1 ===========================================
	fCanvas->cd(2);
	//GetTextCanvas
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 
	switch(Break){
		case 4:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}} to x_{0}.");
		break;
	}

	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW Q1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.36,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	if (Break == 4){
		name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break==0){
		name2 = new TLatex(0.05,0.95,"BLOCH SPHERE");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else {
		name2 = new TLatex(0.05,0.95,"#color[14]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	
	TPad *pad3 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad3->SetFillColor(0);
	pad3->Draw();	
	pad3->cd();
	
	// PRIMER QUBIT
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
 
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);
	TGeoVolume *sp3=geom->MakeSphere("sp3",Iron,0,100,0,180,0,360);

	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec= geom->MakeTube("vec",Iron, 0,2,50);
	vec->SetLineColor(2);

	TGeoVolume *cone=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone->SetLineColor(2);
	cone->SetFillColor(2); 
  
	top->AddNodeOverlap(sp3,1,new TGeoRotation("sp3",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));		
			
	switch(Break){
		case 0: 	
			if(X0==0){
				sp3->SetLineColorAlpha(2,0.1);
				sp3->SetFillColorAlpha(2,0.1);
				
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
			if(X0==1){
				sp3->SetLineColorAlpha(2,0.2);
				sp3->SetFillColorAlpha(2,0.1);
				
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("ha2",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("ha2",0,180,0)));   
			}
		break;
		case 1:	
			if(X0==0){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
			if(X0==1){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);	
		
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("ha2",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("ha2",0,180,0)));   
			}
		break;
		case 2:	
			if(X0==0){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);
 		
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
			if(X0==1){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("ha2",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("ha2",0,180,0)));   
			}
		break;
		case 3: 	
			if(X0==0){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);
  		
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
			if(X0==1){
				sp3->SetLineColorAlpha(13,0.1);
				sp3->SetFillColorAlpha(13,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("ha2",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("ha2",0,180,0)));   
			}
		break;
		case 4:
			if(X0==0){
				sp3->SetLineColorAlpha(2,0.1);
				sp3->SetFillColorAlpha(2,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp3->SetLineColorAlpha(2,0.2);
				sp3->SetFillColorAlpha(2,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
		break;
	}

	top->SetVisibility(0);
	geom->CloseGeometry();
	top->Draw();

	HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
	HD->Draw();
	
	fCanvas->Update();
	pad3->SetEditable(1);

	// =================================== BLOCH TEXT Q1 ===========================================
	fCanvas->cd(3);
	
	//GetTextCanvas
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTbloch->AddText("Initial state of the qubit x_{0}");
		break;  
		case 4:
			TPTbloch->AddText("State of the qubit x_{0} when applying the #font[12]{#font[22]{Hadamard gate}}.");
		break;
	}
 
	TPTbloch->Draw();
	fCanvas->Update();
	
	// =================================== MATRIX DRAW Q1 ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	
	//Desing
	line4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	switch(Break){ 
		case 4:
			name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
			name3->SetTextSize(0.06);
			name3->Draw();
		break;
		default:
			name3 = new TLatex(0.05,0.95,"MATRIX");
			name3->SetTextSize(0.06);
			name3->Draw();
		break;
	}
	
	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();

	//Base QFT	 
	TArc *arc = new TArc(0.42,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();
   
	arc = new TArc(0.525,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.2);
	arc->SetR2(0.05);
	arc->Draw();

	switch(Break){
		case 0: 
			//Base Matrix
			sprintf(line1, "#color[2]{1}      #color[2]{1} ");
			sprintf(line2, "#color[2]{1}           0       "); 
		break;  
		case 1: 
			sprintf(line1, "1          1");
			sprintf(line2, "1      #color[2]{#omega^{1}}"); 
		break;
		case 2:
			sprintf(line1, "1          1");
			sprintf(line2, "1      #omega^{1}"); 	
		break;
		case 3:
			sprintf(line1, "1          1");
			sprintf(line2, "1      #color[2]{#pi}");
		break; 	
		case 4:
			sprintf(line1, "1          1");
			sprintf(line2, "1      #color[2]{-1}"); 
		break;
	}

 	
	l1=new TLatex(0.4,0.6,line1);
	l1->SetTextSize(0.08);
	l1->Draw();
	
	l2=new TLatex(0.4,0.4,line2);
	l2->SetTextSize(0.08);
	l2->Draw();
		
	fCanvas->Update();
	
	// =================================== MATRIX TEXT Q1 ===========================================

	fCanvas->cd(4);
	
	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTmatrix->AddText("The matrix is of size NxN, in this case 2x2.");
			TPTmatrix->AddText("The first row and column are all #color[2]{1}. The zeros");
			TPTmatrix->AddText("will be replaced by #omega raised to a number.");
		break;  
		case 1: 
			TPTmatrix->AddText("For the second column the exponent of #omega goes from");
			TPTmatrix->AddText("#color[2]{1} one by one. Since we only have a");
			TPTmatrix->AddText("zero, the end result is #omega^{1}");
		break;
		case 2:
			TPTmatrix->AddText("Here #color[2]{#omega} = exp #left[ #frac{2#pi i}{N} #right] = exp #left[ #frac{2#pi i}{2} #right] = exp #left[#pi i #right].");
		break;
		case 3:
			TPTmatrix->AddText("For #omega^{1} =  exp #left[ #pi i #right]^{1} = #color[2]{exp #left[ #pi i #right]}.");
		break;
		case 4:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[2]{exp #left[#pi i #right]=-1} appears #color[2]{1} time.");
			TPTmatrix->AddText("This is the matrix of the #font[12]{#font[22]{Hadamard gate}}.");
		break;
	}

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

///////////////////////////////////////////////////  QUBIT 2 ////////////////////////////////////////////////////////////////////// 
void MyMainFrame::csDrawQ2(){
	// =================================== MATH DRAW Q2 ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	
	gPad->SetEditable(1);
	//Desing
	TLine  *Tline4= new TLine(0.005,0,0,0.97);
	Tline4->SetLineWidth(1);
	Tline4->SetLineColor(14);
	Tline4->Draw();
	
	TLine *line5 = new TLine(0,0.005,1,0.005);
	line5->SetLineWidth(1);
	line5->SetLineColor(14);
	line5->Draw();
	
	TLine *line6 = new TLine(0.995,0,0.995,0.97);
	line6->SetLineWidth(1);
	line6->SetLineColor(14);
	line6->Draw();
	
	TLine *line7 = new TLine(0.17,0.97,0.995,0.97);
	line7->SetLineWidth(1);
	line7->SetLineColor(14);
	line7->Draw();
	
	TLine *line8 = new TLine(0,0.97,0.025,0.97);
	line8->SetLineWidth(1);
	line8->SetLineColor(14);
	line8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	switch(Break){
		case 0: 
			sprintf(line1, "QFT|x#GT = #frac{1}{#sqrt{N}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{n-j-k}  x_{n-j} #right) |1 #GT #right)");
	 
			sprintf(line2, "| #tilde{x}#GT = #frac{1}{#color[2]{#sqrt{4}}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{#color[2]{2}-j-k}  x_{#color[2]{2}-j} #right) |1 #GT #right)");
	 
			sprintf(line3, "| #tilde{x}#GT = #frac{1}{2}  #color[2]{#otimes} #left( |0#GT +  exp #left(2#pi i #sum 2^{2-j-#color[2]{2}}  x_{3-j} #right) |1 #GT #right)");
	
	
			l4 = new TLatex(0.26,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.273,0.875,"#scale[1.2]{n}");
			l5->Draw();

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();
	
			l7 = new TLatex(0.205,0.575,"#scale[1.2]{#color[2]{2}}");
			l7->Draw();

			l8 = new TLatex(0.175,0.095,"#scale[1.2]{#color[2]{k=1}}");
			l8->Draw();

			l9 = new TLatex(0.185,0.225,"#scale[1.2]{#color[2]{1}}");
			l9->Draw();

			l10 = new TLatex(0.63,0.71,"#scale[1.2]{j=1}");
			l10->Draw();

			l11 = new TLatex(0.64,0.895,"#scale[1.2]{n}");
			l11->Draw();

			l12 = new TLatex(0.563,0.41,"#scale[1.2]{j=1}");
			l12->Draw();

			l13 = new TLatex(0.574,0.595,"#scale[1.2]{#color[2]{2}}");
			l13->Draw();

			l14 = new TLatex(0.544,0.06,"#scale[1.2]{j=1}");
			l14->Draw();

			l15 = new TLatex(0.554,0.245,"#scale[1.2]{2}");
			l15->Draw();
		break;  
		case 1: 
			//Formulacion general 1 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{2-j-2}}  x_{2-j} #right) |1 #GT #right)");  
			sprintf(line2, "#sum_{j=1}^{2} 2^{-j} x_{2-j} =  2^{-1} x_{2-1} + 2^{-2} x_{2-2} ");
			sprintf(line3, "#sum_{j=1}^{2} 2^{-j} x_{2-j} = #frac{x_{1}}{2} + #frac{x_{o}}{4} "); 
 
			l4 = new TLatex(0.175,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.185,0.875,"#scale[1.2]{1}");
			l5->Draw();

			l10 = new TLatex(0.543,0.71,"#scale[1.2]{#color[2]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.55,0.895,"#scale[1.2]{#color[2]{2}}");
			l11->Draw();
	 
		break;
		case 2:
			sprintf(line2, "#sum_{j=1}^{2} 2^{-j} x_{2-j} = #color[2]{#frac{x_{1}}{2} + #frac{x_{o}}{4}}");
			sprintf(line1,"| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{-j}  x_{2-j}} #right) |1 #GT #right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(2#pi i #left(#color[2]{ #frac{x_{1}}{2} + #frac{x_{o}}{4}}  #right) #right) |1 #GT #right)"); 
	 
			l4 = new TLatex(0.175,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.185,0.875,"#scale[1.2]{1}");
			l5->Draw();

			l10 = new TLatex(0.543,0.71,"#scale[1.2]{#color[2]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.55,0.895,"#scale[1.2]{#color[2]{2}}");
			l11->Draw();	

			l8 = new TLatex(0.175,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.185,0.225,"#scale[1.2]{1}");
			l9->Draw();
		break;
		case 3:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(#color[2]{2#pi i #left( #frac{x_{1}}{2} + #frac{x_{o}}{4} } #right) #right) |1 #GT #right)");
			 sprintf(line2,"| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(#color[2]{#pi i x_{1} + #frac{#pi i x_{o}}{2}} #right) |1 #GT #right)"); 
			 sprintf(line3,"| #tilde{x}#GT = #frac{1}{2}  #otimes #color[2]{#left( |0#GT +  exp #left(#pi i x_{1} + #frac{#pi i x_{o}}{2} #right) |1 #GT #right)}"); 
	
	
			l4 = new TLatex(0.175,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.185,0.875,"#scale[1.2]{1}");
			l5->Draw();

			l6 = new TLatex(0.175,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.185,0.575,"#scale[1.2]{1}");
			l7->Draw();	
	
			l8 = new TLatex(0.175,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.185,0.225,"#scale[1.2]{1}");
			l9->Draw();		
	
		break;
		case 4:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(#color[2]{#pi i x_{1}} + #frac{#pi i x_{o}}{2} #right) |1 #GT #right)"); 
			sprintf(line3," ");
 
			l6 = new TLatex(0.175,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.185,0.575,"#scale[1.2]{1}");
			l7->Draw();
		break;
		case 5:
			sprintf(line1," ");
			//Aplicando la compuerta UROT1 al segundo Qubit
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{2}  #otimes #left( |0#GT +  exp #left(#pi i x_{1} + #color[2]{#frac{#pi i x_{o}}{2}}  #right) |1 #GT #right)"); 
			sprintf(line3," ");

			l6 = new TLatex(0.175,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.185,0.575,"#scale[1.2]{1}");
			l7->Draw();		
		break;
		case 6: 
			//Formulacion general 2 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{2} #left( |0#GT +  exp #left(2#pi i #color[4]{#sum 2^{2-j-1}}  x_{2-j} #right) |1 #GT #right)  #color[2]{#otimes ...}");  
			sprintf(line2, "#sum_{j=1}^{2} 2^{1-j} x_{2-j} =  2^{1-1}  x_{2-1}  + 2^{1-2} x_{2-2} ");
			sprintf(line3, "#sum_{j=1}^{2} 2^{1-j} x_{2-j} = x_{1}  + #frac{x_{o}}{2}"); 
	 
			l10 = new TLatex(0.490,0.71,"#scale[1.2]{#color[4]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.495,0.895,"#scale[1.2]{#color[4]{2}}");
			l11->Draw();
		break;
		case 7:
			sprintf(line2, "#sum_{j=1}^{2} 2^{1-j} x_{2-j} = #color[4]{x_{1}  + #frac{x_{o}}{2}}");
			sprintf(line1,"| #tilde{x}#GT = #frac{1}{2} #left( |0#GT +  exp #left(2#pi i #color[4]{#sum 2^{1-j}  x_{2-j}} #right) |1 #GT #right) #color[2]{#otimes ...}"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{2} #left( |0#GT +  exp #left(2#pi i #left(#color[4]{  x_{1}  + #frac{x_{o}}{2}} #right) #right) |1 #GT #right)"); 
		
			l10 = new TLatex(0.490,0.71,"#scale[1.2]{#color[4]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.495,0.895,"#scale[1.2]{#color[4]{3}}");
			l11->Draw();

		break;
		case 8:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{2}  #left( |0#GT +  exp #left(#color[4]{2#pi i #left(x_{1}  + #frac{x_{o}}{2}}  #right) #right) |1 #GT #right)");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{2}  #left( |0#GT +  exp #left(#color[4]{2 #pi i x_{1} + #pi i x_{o}}#right) |1 #GT #right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{2} #color[4]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #color[2]{#otimes ...}"); 
		break;
		case 9:
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{2} #left( |0#GT +  exp #left(#color[4]{#pi i x_{o}} #right) |1 #GT #right) #color[2]{#otimes ...}"); 
			sprintf(line3," ");
		break;
		case 10:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{2} #color[4]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #otimes");
			sprintf(line2,"          #color[2]{#left( |0#GT +  exp #left(#pi i x_{1} + #frac{#pi i x_{o}}{2} #right) |1 #GT #right)}"); 
			sprintf(line3," ");
		break;
		case 12:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{2} #left( |0#GT +  exp #left(#color[4]{#pi i x_{o}} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#color[4]{#pi i x_{1}} + #frac{#pi i x_{o}}{2} #right) |1 #GT #right)"); 
			sprintf(line3," ");

		break;
		case 13:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{2} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#pi i x_{1} + #color[6]{#frac{#pi i x_{o}}{2}} #right) |1 #GT #right)"); 
			sprintf(line3," ");
		break;
		case 14:	
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{2} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#color[65]{#pi i x_{1} + #frac{#pi i x_{o}}{2}} #right) |1 #GT #right)"); 
			sprintf(line3," ");
		break;
		case 11:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{2} #color[2]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #otimes");
			sprintf(line2,"          #color[4]{#left( |0#GT +  exp #left(#pi i x_{1} + #frac{#pi i x_{o}}{2} #right) |1 #GT #right)}"); 
			sprintf(line3," ");
		break;
	}
 	
	l1=new TLatex(0.02,0.8,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.02,0.5,line2);
	l2->SetTextSize(0.08);
	l2->Draw();

	l3=new TLatex(0.02,0.15,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
		
	fCanvas->Update();
	
	// =================================== MATH TEXT Q2 ===========================================
	fCanvas->cd(1);
	//GetTextCanvas
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTmath->AddText("From the general formula, replace #font[12]{#font[22]{#color[2]{n=2}}}.");
			TPTmath->AddText("The tensor product #font[12]{#font[22]{k}} goes from one");
			TPTmath->AddText("to #font[12]{#font[22]{n}}. For the first case #font[12]{#font[22]{#color[2]{k=2}}}.");
		break;  
		case 1: 
			TPTmath->AddText("The sum is solved."); 
		break;
		case 2:
			TPTmath->AddText("It is replaced in the general equation.");
		break;
		case 3:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and you get the result of the");
			TPTmath->AddText("First Tensor.");
		break;
		case 4:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard gate}} to the last qubit.");
		break;
		case 5:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}}");
			TPTmath->AddText("to the last qubit.");
		break;
		case 6: 
			TPTmath->AddText("For the second tensor #font[12]{#font[22]{#color[4]{k=1}}}.");
			TPTmath->AddText("The sum is resolved.");
		break;
		case 7:
			TPTmath->AddText("It is replaced in the general equation");
		break;
		case 8:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and you get the result of the");
			TPTmath->AddText("Second Tensor");
		break;
		case 9:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard gate}} to the first qubit.");
		break;
		case 10:
			TPTmath->AddText("This is the general mathematical expression");
			TPTmath->AddText("for a 2 qubit system.");
		break;
		case 12:
			TPTmath->AddText("#color[4]{exp #left[ #pi i #right]}.");
		break;
		case 13:
			TPTmath->AddText("#color[6]{exp #left[ #frac{#pi i}{2} #right]}.");
		break;
		case 14:
			TPTmath->AddText("Sum of exp #left[ #pi + #frac{#pi}{2} #right] = #color[65]{exp #left[ #frac{3#pi}{2} #right]}.");
		break;
		case 11:
			TPTmath->AddText("Application of #font[12]{#font[22]{Swap gate}}. Final mathematical");
			TPTmath->AddText("expression of the Quantum Fourier Transform.");
		break;
	}

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW Q2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	//Desing
	Tline4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	if(Break == 4 or Break == 5 or Break >= 9){
		name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();
	}
	else {
		name1 = new TLatex(0.05,0.95,"#color[14]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();	
	}
	
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.210,0.625,0.870,0.625);
	line->SetLineWidth(3);
	line->Draw();;
	
	line = new TLine(0.210,0.375,0.870,0.375);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.110,0.605,"#scale[1.7]{#cbar x_{0}#GT}");
	HD->Draw();

	HD = new TLatex(0.110,0.355,"#scale[1.7]{#cbar x_{1}#GT}");
	HD->Draw();

	switch(Break){
		case 4: 
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
		break;
		case 5:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 6: 
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 7:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 8:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 9:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
		case 10:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
		case 12:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[4]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[4]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();			
			
			line = new TLine(0.700,0.375,0.700,0.625);
			line->SetLineWidth(3);
			line->Draw();
			
			x = new TLatex(0.6825,0.584,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.6825,0.334,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
			
	   	break;
   		case 13:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[6]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[6]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.700,0.375,0.700,0.625);
			line->SetLineWidth(3);
			line->Draw();
			
			x = new TLatex(0.6825,0.584,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.6825,0.334,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
	   	break;
	   	case 14:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[65]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[65]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[65]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[65]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.700,0.375,0.700,0.625);
			line->SetLineWidth(3);
			line->Draw();
			
			x = new TLatex(0.6825,0.584,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.6825,0.334,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
	   	break;
   		case 11:
			//Compuerta Hadamard1
			Square = new TPave(0.245,0.300,0.300,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.260,0.345,"#scale[1.7]{#color[2]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.320,0.475,"#scale[1.7]{#color[2]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.400,0.375,0.400,0.625);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.375,0.300,0.430,0.450,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.385,0.355,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.400,0.625,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.455,0.475,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta Hadamard2
			Square = new TPave(0.515,0.550,0.570,0.700,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.530,0.595,"#scale[1.7]{#color[4]{H}}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.590,0.725,"#scale[1.7]{#color[4]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			line = new TLine(0.700,0.375,0.700,0.625);
			line->SetLineWidth(3);
			line->Draw();
			
			x = new TLatex(0.6825,0.584,"#color[2]{#scale[2.5]{X}}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.6825,0.334,"#color[4]{#scale[2.5]{X}}");
			x->SetLineWidth(2);
			x->Draw();

		break;
	}

	fCanvas->Update();

	// =================================== CIRCUIT TEXT Q2 ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 
	switch(Break){
		case 4:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}}  to x_{1}.");
		break;
		case 5:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} to x_{1}.");
		break;
		case 9:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}}  to x_{0}.");
		break;
   		case 10:
			TPTcircuit->AddText("Mathematical applications to the circuit.");
		break;
		case 12:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate} (#color[4]{#pi})}.");
   		break;
   		case 13:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{#color[6]{#pi/2} Controlled-Rotation gate}}.");
		break;
		case 14:
			TPTcircuit->AddText("Sum of #pi + #frac{#pi}{2}  = #color[65]{#frac{3#pi}{2} }.");
		break;
		case 11:
			TPTcircuit->AddText("Application of #font[12]{#font[22]{Swap gate}}.");
			TPTcircuit->AddText("Final circuit of the Quantum Fourier Transform.");
		break;
		default:
			TPTcircuit->AddText(" ");
		break;
	}

	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== BLOCH DRAW Q2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	Tline4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.36,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	if((Break == 4 or Break == 5) or (Break > 8 and Break < 12)){
		name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if (Break == 0 or Break == 1){
		name2 = new TLatex(0.05,0.95,"BLOCH SPHERE");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else {
		name2 = new TLatex(0.05,0.95,"#color[14]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.485,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.485,0.22,0.97,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	// PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec= geom->MakeTube("vec",Iron, 0,2,50);
	vec->SetLineColor(2);

	TGeoVolume *cone=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone->SetLineColor(2);
	cone->SetFillColor(2); 
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	switch(Break){
		case 0: 
		//ESTADO PRIMER QUBIT
			//PRIMER QUBIT 
			pad31->cd();;
			if(X0==0){
				sp0->SetLineColorAlpha(4,0.1);
        		sp0->SetFillColorAlpha(4,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(4,0.1);
               	sp0->SetFillColorAlpha(4,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
			}
			if(X1==1){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
		break;
		case 1:
		//ESTADO SEGUNDO QUBIT
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0){
				sp1->SetLineColorAlpha(2,0.1);
        		sp1->SetFillColorAlpha(2,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(2,0.1);
               	sp1->SetFillColorAlpha(2,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 2:
		//ESTADO GENERAL
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 3:
		//NOTHING
			//PRIMER QUBIT
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 4:
		//APLICACION COMPUERTA H ->x1
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();		
		break;
		case 5:
		//APLICACION COMPUERTA R(1/2) ->x1
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();	
		break;
		case 6:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 7:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();	
		break;
		case 8:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 9:
		//APLICACION COMPUERTA H -> x0
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(4,0.1);
				sp0->SetFillColorAlpha(4,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(4,0.2);
				sp0->SetFillColorAlpha(4,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 10:
		//APLICACION COMPUERTA H -> x0
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(4,0.1);
				sp0->SetFillColorAlpha(4,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(4,0.2);
				sp0->SetFillColorAlpha(4,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(2,0.1);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(2,0.2);
				sp1->SetFillColorAlpha(2,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
		case 11:
		//APLICACION COMPUERTA SWAP
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(2,0.1);
				sp0->SetFillColorAlpha(2,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(2,0.2);
				sp0->SetFillColorAlpha(2,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[2]{#color[4]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
		break;
	}
	
	fCanvas->Update();
	
	// =================================== BLOCH TEXT Q2 ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);
	
	switch(Break){
		case 0:
			TPTbloch->AddText("Initial state of the qubit #color[2]{x_{0}}");
 		break;
 		case 1:
			TPTbloch->AddText("Initial state of the qubit #color[2]{x_{1}}");
 		break;
 		case 2:
			TPTbloch->AddText("General state of the qubit system.");
 		break;
 		case 4:
			TPTbloch->AddText("State of the qubit #color[2]{x_{1}} when applying the #font[12]{#font[22]{Hadamard gate}}.");
 		break;
 		case 5:
			TPTbloch->AddText("State of the qubit #color[2]{x_{1}} when applying the ");
			TPTbloch->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} .");
 		break;
 		case 9:
			TPTbloch->AddText("State of the qubit #color[4]{x_{0}} when applying the #font[12]{#font[22]{Hadamard gate}}");
 		break;
 		case 10:
			TPTbloch->AddText("Overall system status");
 		break;
 		case 11:
			TPTbloch->AddText("System state when applying the #font[12]{#font[22]{Swap gate}}.");
			TPTbloch->AddText("Final state of the Quantum Fourier Transform.");
 		break;
 		default:
			TPTbloch->AddText(" ");
 		break;
	}
 
	TPTbloch->Draw();
	fCanvas->Update();
	
	// =================================== MATRIX DRAW Q2 ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	//Desing
	Tline4->Draw();
	line5->Draw();
	line6->Draw();
	
	line7 = new TLine(0.22,0.97,0.995,0.97);
	line7->Draw();
	line8->Draw();
	
	
	if(Break > 10){
		name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
		name3->SetTextSize(0.06);
		name3->Draw();
	}
	else if(Break > 8 and Break <11){
		name3 = new TLatex(0.05,0.95,"#color[14]{MATRIX}");
		name3->SetTextSize(0.06);
		name3->Draw();
	}
	else {
		name3 = new TLatex(0.05,0.95,"MATRIX");
		name3->SetTextSize(0.06);
		name3->Draw();
	}

	
	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
	
	TArc *arc = new TArc(0.33,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(90);
	arc->SetR1(0.6);
	arc->SetR2(0.11);
	arc->Draw();
   
	arc = new TArc(0.68,0.52,0.1,40,140);
	arc->SetLineWidth(2);
	arc->SetNoEdges();
	arc->SetTheta(270);
	arc->SetR1(0.6);
	arc->SetR2(0.11);
	arc->Draw();
	
	//Base QFT	 
	switch(Break){
		case 0: 
			//Base Matrix
			sprintf(line1, "#color[2]{1}      #color[2]{1}       #color[2]{1}       #color[2]{1}");
			sprintf(line2, "#color[2]{1}           0           0          0"); 
			sprintf(line3, "#color[2]{1}           0           0          0"); 
			sprintf(line4, "#color[2]{1}           0           0          0"); 
		break;        
		case 1: 
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #color[2]{#omega^{1}}          0           0"); 
			sprintf(line3, "1      #color[2]{#omega^{2}}          0           0"); 
			sprintf(line4, "1      #color[2]{#omega^{3}}          0           0"); 
		break;
		case 2:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #omega^{1}      #color[2]{#omega^{2}}         0"); 
			sprintf(line3, "1      #omega^{2}      #color[2]{#omega^{4}}         0"); 
			sprintf(line4, "1      #omega^{3}      #color[2]{#omega^{2}}         0"); 
		break;
		case 3:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #omega^{1}      #omega^{2}     #color[2]{#omega^{3}}"); 
			sprintf(line3, "1      #omega^{2}      #omega^{4}     #color[2]{#omega^{2}}"); 
			sprintf(line4, "1      #omega^{3}      #omega^{2}     #color[2]{#omega^{1}}"); 
		break;   
		case 4:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #omega^{1}      #omega^{2}     #omega^{3}"); 
			sprintf(line3, "1      #omega^{2}      #omega^{4}     #omega^{2}"); 
			sprintf(line4, "1      #omega^{3}      #omega^{2}     #omega^{1}"); 
		break;
		case 5: 
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #color[2]{^{#pi}/_{2}}     #omega^{2}      #omega^{3}"); 
			sprintf(line3, "1      #omega^{2}     #omega^{4}      #omega^{2}"); 
			sprintf(line4, "1      #omega^{3}     #omega^{2}      #color[2]{^{#pi}/_{2}}"); 
		break;
		case 6: 
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #color[2]{#pi}      #omega^{3}");
			sprintf(line3, "1      #color[2]{#pi}       #omega^{4}     #color[2]{#pi}"); 
			sprintf(line4, "1      #omega^{3}      #color[2]{#pi}      ^{#pi}/_{2}"); 
		break;
		case 7:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     #color[2]{^{3#pi}/_{2}}");
			sprintf(line3, "1      #pi       #omega^{4}     #pi"); 
			sprintf(line4, "1     #color[2]{^{3#pi}/_{2}}      #pi      ^{#pi}/_{2}");
		break;
		case 8:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     ^{3#pi}/_{2}");
			sprintf(line3, "1      #pi      #color[2]{2#pi}      #pi"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #pi      ^{#pi}/_{2}");
		break;
		case 9:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     ^{3#pi}/_{2}");
			sprintf(line3, "1      #pi          2#pi      #pi"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #pi      ^{#pi}/_{2}");
		break;
		case 10:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     ^{3#pi}/_{2}");
			sprintf(line3, "1      #pi          2#pi      #pi"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #pi      ^{#pi}/_{2}");
		break;
		case 11: 
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     ^{3#pi}/_{2}");
			sprintf(line3, "1      #pi      #color[2]{2#pi}      #pi"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #pi      ^{#pi}/_{2}");
		break;
		case 12:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #color[4]{#pi}     ^{3#pi}/_{2}");
			sprintf(line3, "1      #color[4]{#pi}          2#pi      #color[4]{#pi}"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #color[4]{#pi}      ^{#pi}/_{2}");
		break;
		case 13:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      #color[6]{^{#pi}/_{2}}      #pi     ^{3#pi}/_{2}");
			sprintf(line3, "1      #pi          2#pi      #pi"); 
			sprintf(line4, "1     ^{3#pi}/_{2}      #pi      #color[6]{^{#pi}/_{2}}");
		break;
		case 14:
			sprintf(line1, "1          1           1           1");
			sprintf(line2, "1      ^{#pi}/_{2}      #pi     #color[65]{^{3#pi}/_{2}}");
			sprintf(line3, "1      #pi          2#pi      #pi"); 
			sprintf(line4, "1     #color[65]{^{3#pi}/_{2}}      #pi      ^{#pi}/_{2}");
		break;
	}

 	
	l1=new TLatex(0.3,0.875,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.3,0.625,line2);
	l2->SetTextSize(0.08);
	l2->Draw();

	l3=new TLatex(0.3,0.375,line3);
	l3->SetTextSize(0.08);
	l3->Draw();

	l4=new TLatex(0.3,0.125,line4);
	l4->SetTextSize(0.08);
	l4->Draw();
		
	fCanvas->Update();
	
	// =================================== MATRIX TEXT Q2 ===========================================
	fCanvas->cd(4);
	
	//GetTextCanvas
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTmatrix->AddText("The matrix is of size NxN, in this case 4x4.");
			TPTmatrix->AddText("The first row and column are all #color[2]{1}. The zeros");
			TPTmatrix->AddText("will be replaced by #omega raised to a number.");
		break;
		case 1: 
			TPTmatrix->AddText("For the second column the exponent of #omega goes from");
			TPTmatrix->AddText("#color[2]{1} one by one.");
		break;
		case 2:
			TPTmatrix->AddText("For the third column the exponent of #omega goes from #color[2]{2}");
			TPTmatrix->AddText("two by two. When it reaches #color[2]{4} it starts again.");   
		break;
		case 3:
			TPTmatrix->AddText("For the fourth column the exponent of #omega goes from #color[2]{3}");
			TPTmatrix->AddText("three by three. When it reaches #color[2]{4} it starts again."); 
		break;
		case 4:
			TPTmatrix->AddText("Here #color[2]{#omega} = exp #left[ #frac{2#pi i}{N} #right] = exp #left[ #frac{2#pi i}{4} #right] = exp #left[ #frac{#pi i}{2} #right].");
		break;
		case 5:
			TPTmatrix->AddText("For #omega^{1} =  exp #left[ #frac{#pi i}{2} #right]^{1} = #color[2]{exp #left[ #frac{#pi i}{2} #right]}.");
		break;
		case 6:
			TPTmatrix->AddText("For #omega^{2} =  exp #left[ #frac{#pi i}{2} #right]^{2} = #color[2]{exp #left[ #pi i #right]}.");
		break;
		case 7:
			TPTmatrix->AddText("For #omega^{3} =  exp #left[ #frac{#pi i}{2} #right]^{3} = #color[2]{exp #left[ #frac{3#pi i}{2} #right]}.");
		break;
		case 8: 
			TPTmatrix->AddText("For #omega^{4} =  exp #left[ #frac{#pi i}{2} #right]^{4} = #color[2]{exp #left[ 2#pi i #right]}.");
		break;
		case 11:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[2]{exp #left[2#pi i #right]} is not visible since");
			TPTmatrix->AddText("its result multiplies the entire exponential by #color[2]{1}.");
		break;	
		case 12:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[4]{exp #left[#pi i #right]} appears #color[4]{2} times. So, multiplying by ");
			TPTmatrix->AddText("#font[12]{N'} in the matrix it appears 4 times.");
		break;
		case 13:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[6]{exp #left[#pi i /2 #right]} appears #color[6]{1} time. So, multiplying by ");
			TPTmatrix->AddText("#font[12]{N'} in the matrix it appears 2 times.");
		break;
		case 14:
			TPTmatrix->AddText("The result of the mathematical addition #color[65]{3#pi i/2}");
			TPTmatrix->AddText("appears #color[65]{1} time, multiplying by #font[12]{N'} in the matrix");
			TPTmatrix->AddText("appears 2 times.");	
		break;
		default:
			TPTmatrix->AddText(" ");
		break;
	}

	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

///////////////////////////////////////////////////  QUBIT 3 ////////////////////////////////////////////////////////////////////// 
void MyMainFrame::csDrawQ3(){
	// =================================== MATH DRAW Q3 ===========================================
	//GetBigCanvas 
	fCanvas = fECanvasGen->GetCanvas();
	fCanvas->SetEditable(1);
	fCanvas->Clear();
	fCanvas->SetFillColor(18);
   	
   	fCanvas->Divide(2,2);
	fCanvas->cd(1);
	gPad->SetEditable(1);
	
	//Desing
	TLine  *Tline4= new TLine(0.005,0,0,0.97);
	Tline4->SetLineWidth(1);
	Tline4->SetLineColor(14);
	Tline4->Draw();
	
	TLine *Tline5 = new TLine(0,0.005,1,0.005);
	Tline5->SetLineWidth(1);
	Tline5->SetLineColor(14);
	Tline5->Draw();
	
	TLine *Tline6 = new TLine(0.995,0,0.995,0.97);
	Tline6->SetLineWidth(1);
	Tline6->SetLineColor(14);
	Tline6->Draw();
	
	TLine *Tline7 = new TLine(0.17,0.97,0.995,0.97);
	Tline7->SetLineWidth(1);
	Tline7->SetLineColor(14);
	Tline7->Draw();
	
	TLine *Tline8 = new TLine(0,0.97,0.025,0.97);
	Tline8->SetLineWidth(1);
	Tline8->SetLineColor(14);
	Tline8->Draw();

	name = new TLatex(0.05,0.95,"#color[2]{MATH}");
	name->SetTextSize(0.06);
	name->Draw();
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.03,0.22,0.97,0.925);
	pad1->SetFillColor(0);
	pad1->Draw();	
	pad1->cd();
	
	switch(Break){
		case 0: 
			sprintf(line1, "QFT|x#GT = #frac{1}{#sqrt{N}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{n-j-k}  x_{n-j} #right) |1 #GT #right)");
			sprintf(line2, "| #tilde{x}#GT = #frac{1}{#color[2]{#sqrt{8}}}  #otimes #left( |0#GT +  exp #left(2#pi i #sum 2^{#color[2]{3}-j-k}  x_{#color[2]{3}-j} #right) |1 #GT #right)");
	 
			sprintf(line3, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #color[2]{#otimes} #left( |0#GT +  exp #left(2#pi i #sum 2^{3-j-#color[2]{3}}  x_{3-j} #right) |1 #GT #right)");
	
	
			l4 = new TLatex(0.26,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.27,0.875,"#scale[1.2]{n}");
			l5->Draw();

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();
	
			l7 = new TLatex(0.205,0.575,"#scale[1.2]{#color[2]{3}}");
			l7->Draw();

			l8 = new TLatex(0.19,0.095,"#scale[1.2]{#color[2]{k=1}}");
			l8->Draw();

			l9 = new TLatex(0.205,0.225,"#scale[1.2]{#color[2]{2}}");
			l9->Draw();

			l10 = new TLatex(0.63,0.71,"#scale[1.2]{j=1}");
			l10->Draw();

			l11 = new TLatex(0.64,0.895,"#scale[1.2]{n}");
			l11->Draw();

			l12 = new TLatex(0.563,0.41,"#scale[1.2]{j=1}");
			l12->Draw();

			l13 = new TLatex(0.579,0.595,"#scale[1.2]{#color[2]{3}}");
			l13->Draw();

			l14 = new TLatex(0.563,0.06,"#scale[1.2]{j=1}");
			l14->Draw();

			l15 = new TLatex(0.579,0.245,"#scale[1.2]{3}");
			l15->Draw();
		break;  
		case 1: 
			//Formulacion general 1 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{3-j-3}}  x_{3-j} #right) |1 #GT #right)");  
			sprintf(line2, "#sum_{j=1}^{3} 2^{-j} x_{3-j} =  2^{-1} x_{3-1} + 2^{-2} x_{3-2} + 2^{-3} x_{1-3}");
			sprintf(line3, "#sum_{j=1}^{3} 2^{-j} x_{3-j} = #frac{x_{2}}{2} + #frac{x_{1}}{4}+ #frac{x_{o}}{8} "); 
 
			l4 = new TLatex(0.195,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{2}");
			l5->Draw();

			l10 = new TLatex(0.56,0.71,"#scale[1.2]{#color[2]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.57,0.895,"#scale[1.2]{#color[2]{3}}");
			l11->Draw();
	 
		break;
		case 2:
			sprintf(line2, "#sum_{j=1}^{3} 2^{-j} x_{3-j} = #color[2]{#frac{x_{2}}{2} + #frac{x_{1}}{4}+ #frac{x_{o}}{8}}");
			sprintf(line1,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(2#pi i #color[2]{#sum 2^{-j}  x_{3-j}} #right) |1 #GT #right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(2#pi i #left(#color[2]{ #frac{x_{2}}{2} + #frac{x_{1}}{4}+ #frac{x_{o}}{8}}  #right) #right) |1 #GT#right)"); 
	 
			l4 = new TLatex(0.195,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{2}");
			l5->Draw();

			l10 = new TLatex(0.56,0.71,"#scale[1.2]{#color[2]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.57,0.895,"#scale[1.2]{#color[2]{3}}");
			l11->Draw();	

			l8 = new TLatex(0.19,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.205,0.225,"#scale[1.2]{2}");
			l9->Draw();
		break;
		case 3:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[2]{2#pi i #left( #frac{x_{2}}{2} + #frac{x_{1}}{4}+ #frac{x_{o}}{8} } #right) #right) |1 #GT#right)");
			 sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[2]{#pi i x_{2} + #frac{#pi i x_{1}}{2}+ #frac{#pi i x_{o}}{4} } #right) |1 #GT#right)"); 
			 sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #color[2]{#left( |0#GT +  exp #left(#pi i x_{2} + #frac{#pi i x_{1}}{2}+ #frac{#pi i x_{o}}{4} #right) |1 #GT#right)}"); 
	
	
			l4 = new TLatex(0.19,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{2}");
			l5->Draw();

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{2}");
			l7->Draw();	
	
			l8 = new TLatex(0.19,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.205,0.225,"#scale[1.2]{2}");
			l9->Draw();		
	
		break;
		case 4:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[2]{#pi i x_{2}} + #frac{#pi i x_{1}}{2}+ #frac{#pi i x_{o}}{4} #right) |1 #GT #right)"); 
			sprintf(line3," ");
 
			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{2}");
			l7->Draw();
		break;
		case 5:
			sprintf(line1," ");
			//Aplicando la compuerta UROT1 al segundo Qubit
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#pi i x_{2} + #color[2]{#frac{#pi i x_{1}}{2}} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)"); 
			sprintf(line3," ");

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{2}");
			l7->Draw();		
		break;
		case 6:
			//Aplicando la compuerta UROT2 al tercer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#pi i x_{2} + #frac{#pi i x_{1}}{2} + #color[2]{#frac{#pi i x_{o}}{4}} #right) |1 #GT #right)"); 
			sprintf(line3," ");
 
			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{2}");
			l7->Draw();
		break;
		case 7: 
			//Formulacion general 2 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #color[4]{#otimes} #left( |0#GT +  exp #left(2#pi i #color[4]{#sum 2^{3-j-2}}  x_{3-j} #right) |1 #GT #right) #color[2]{#otimes ...}");  
			sprintf(line2, "#sum_{j=1}^{3} 2^{1-j} x_{3-j} =  2^{1-1}  x_{3-1}  + 2^{1-2} x_{3-2}  + 2^{2-3}  x_{3-3}");
			sprintf(line3, "#sum_{j=1}^{3} 2^{1-j} x_{3-j} = x_{2}  + #frac{x_{1}}{2}+ #frac{x_{o}}{4}"); 
	 
			l4 = new TLatex(0.195,0.745,"#scale[1.2]{#color[4]{k=1}}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{#color[4]{1}}");
			l5->Draw();

			l10 = new TLatex(0.56,0.71,"#scale[1.2]{#color[4]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.57,0.895,"#scale[1.2]{#color[4]{3}}");
			l11->Draw();
		break;
		case 8:
			sprintf(line2, "#sum_{j=1}^{3} 2^{1-j} x_{3-j} = #color[4]{ x_{2}  + #frac{x_{1}}{2}+ #frac{x_{o}}{4}}");
			sprintf(line1,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(2#pi i #color[4]{#sum 2^{1-j}  x_{3-j}} #right) |1 #GT #right) #color[2]{#otimes ...}"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(2#pi i #left(#color[4]{  x_{2}  + #frac{x_{1}}{2}+ #frac{x_{o}}{4}} #right) #right) |1 #GT#right)"); 
	 
			l4 = new TLatex(0.195,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{1}");
			l5->Draw();
	
			l10 = new TLatex(0.56,0.71,"#scale[1.2]{#color[4]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.57,0.895,"#scale[1.2]{#color[4]{3}}");
			l11->Draw();

			l8 = new TLatex(0.19,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.205,0.225,"#scale[1.2]{1}");
			l9->Draw();
		break;
		case 9:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[4]{2#pi i #left(x_{2}  + #frac{x_{1}}{2}+ #frac{x_{o}}{4}} #right)#right) |1 #GT#right) #color[2]{#otimes ...}");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[4]{2 #pi i x_{2} + #pi i x_{1}+ #frac{#pi i x_{o}}{2} }#right) |1 #GT#right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #color[4]{#left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right)} #color[2]{#otimes ...}"); 
	 
			l4 = new TLatex(0.19,0.745,"#scale[1.2]{k=1}");
			l4->Draw();

			l5 = new TLatex(0.205,0.875,"#scale[1.2]{1}");
			l5->Draw();
	
			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();
	
			l7 = new TLatex(0.205,0.575,"#scale[1.2]{1}");
			l7->Draw();
		
			l8 = new TLatex(0.19,0.095,"#scale[1.2]{k=1}");
			l8->Draw();

			l9 = new TLatex(0.205,0.225,"#scale[1.2]{1}");
			l9->Draw();
		break;
		case 10:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#color[4]{#pi i x_{1}}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right) #color[2]{#otimes ...}"); 
			sprintf(line3," ");
  
			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{1}");
			l7->Draw();
		break;
		case 11:
			sprintf(line1," ");
			//Aplicando la compuerta UROT1 al segundo Qubit
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #otimes #left( |0#GT +  exp #left(#pi i x_{1}+ #color[4]{#frac{#pi i x_{o}}{2} }#right) |1 #GT #right) #color[2]{#otimes ...}"); 
			sprintf(line3," ");

			l6 = new TLatex(0.19,0.445,"#scale[1.2]{k=1}");
			l6->Draw();

			l7 = new TLatex(0.205,0.575,"#scale[1.2]{1}");
			l7->Draw();
		break;
		case 12: 
			//Formulación general 3 Tensor
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(2#pi i #color[8]{#sum 2^{3-j-1}}  x_{3-j} #right) |1 #GT#right) #color[4]{#otimes ...} #color[2]{#otimes ...}");  
			sprintf(line2, "#sum_{j=1}^{3} 2^{2-j} x_{3-j} =  2^{2-1}  x_{3-1}  + 2^{2-2} x_{3-2}  + 2^{2-3}  x_{3-3}");
			sprintf(line3, "#sum_{j=1}^{3}  2^{2-j} x_{3-j} = 2 x_{2}  + x_{1}+ #frac{x_{o}}{2}"); 

			l10 = new TLatex(0.50,0.71,"#scale[1.2]{#color[8]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.515,0.895,"#scale[1.2]{#color[8]{3}}");
			l11->Draw();
		break;
		case 13:
			sprintf(line2, "#sum_{j=1}^{3} 2^{2-j} x_{3-j} = #color[8]{  2 x_{2}  + x_{1}+ #frac{x_{o}}{2}}");
			sprintf(line1,"| #tilde{x}#GT = #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(2#pi i #color[8]{#sum 2^{2-j}  x_{3-j}} #right) |1 #GT #right) #color[4]{#otimes ...} #color[2]{#otimes ...}"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(2#pi i #left(#color[8]{   2 x_{2}  + x_{1}+ #frac{x_{o}}{2}} #right) #right) |1 #GT #right)"); 
	 
			l10 = new TLatex(0.50,0.71,"#scale[1.2]{#color[8]{j=1}}");
			l10->Draw();

			l11 = new TLatex(0.515,0.895,"#scale[1.2]{#color[8]{3}}");
			l11->Draw();
		break;
		case 14:
			sprintf(line1, "| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #left( |0#GT +  exp #left(#color[8]{2#pi i #left( 2 x_{2}  + x_{1}+ #frac{x_{o}}{2} }  #right) #right) |1 #GT#right)");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #left( |0#GT +  exp #left(#color[8]{4 #pi i x_{2} + 2 #pi i x_{1}+ #pi i x_{o} }#right) |1 #GT#right)"); 
			sprintf(line3,"| #tilde{x}#GT = #frac{1}{#sqrt{8}} #color[8]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #color[4]{#otimes ...} #color[2]{#otimes ...}"); 
		break;
		case 15:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1," ");
			sprintf(line2,"| #tilde{x}#GT = #frac{1}{#sqrt{8}}  #left( |0#GT +  exp #left(#color[8]{#pi i x_{o}} #right) |1 #GT #right) #color[4]{#otimes ...} #color[2]{#otimes ...}"); 
			sprintf(line3," ");
		break;
		case 16:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #color[8]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #otimes");
			sprintf(line2,"          #color[4]{#left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right)} #otimes"); 
			sprintf(line3,"          #color[2]{#left( |0#GT +  exp #left(#pi i x_{2} + #frac{#pi i x_{1}}{2} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)}");
		break;
		case 18:
			//Aplicando la compuerta H al primer Qubit
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#color[4]{#pi i x_{o}} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#color[4]{#pi i x_{1}}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right) #otimes"); 
			sprintf(line3,"          #left( |0#GT +  exp #left(#color[4]{#pi i x_{2}} + #frac{#pi i x_{1}}{2} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)");
		break;
		case 19:
		//Aplicando la compuerta H al primer Qubit
		sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
		sprintf(line2,"          #left( |0#GT +  exp #left(#pi i x_{1}+ #color[6]{#frac{#pi i x_{o}}{2}} #right) |1 #GT #right) #otimes"); 
		sprintf(line3,"          #left( |0#GT +  exp #left(#pi i x_{2} + #color[6]{#frac{#pi i x_{1}}{2}} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)");
		break;
		case 20:	
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right) #otimes"); 
			sprintf(line3,"          #left( |0#GT +  exp #left(#pi i x_{2} + #frac{#pi i x_{1}}{2} + #color[51]{#frac{#pi i x_{o}}{4}} #right) |1 #GT #right)");
		break;
		case 21:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#color[65]{#pi i x_{1}+ #frac{#pi i x_{o}}{2}} #right) |1 #GT #right) #otimes"); 
			sprintf(line3,"          #left( |0#GT +  exp #left(#color[65]{#pi i x_{2} + #frac{#pi i x_{1}}{2}} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)");
		break;
		case 22:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right) #otimes"); 
			sprintf(line3,"          #left( |0#GT +  exp #left(#color[50]{#pi i x_{2}} + #frac{#pi i x_{1}}{2} + #color[50]{#frac{#pi i x_{o}}{4}} #right) |1 #GT #right)");
		break;
		case 23:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right) #otimes");
			sprintf(line2,"          #left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right) #otimes"); 
			sprintf(line3,"          #left( |0#GT +  exp #left(#color[97]{#pi i x_{2} + #frac{#pi i x_{1}}{2} + #frac{#pi i x_{o}}{4}} #right) |1 #GT #right)");
		break;
		case 17:
			sprintf(line1,"| #tilde{x}#GT   =   #frac{1}{#sqrt{8}} #color[2]{#left( |0#GT +  exp #left(#pi i x_{o} #right) |1 #GT #right)} #otimes");
			sprintf(line2,"          #color[4]{#left( |0#GT +  exp #left(#pi i x_{1}+ #frac{#pi i x_{o}}{2} #right) |1 #GT #right)} #otimes"); 
			sprintf(line3,"          #color[8]{#left( |0#GT +  exp #left(#pi i x_{2} + #frac{#pi i x_{1}}{2} + #frac{#pi i x_{o}}{4} #right) |1 #GT #right)}");
		break;
	}
 	
	l1=new TLatex(0.02,0.8,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.02,0.5,line2);
	l2->SetTextSize(0.08);
	l2->Draw();

	l3=new TLatex(0.02,0.15,line3);
	l3->SetTextSize(0.08);
	l3->Draw();
	
	fCanvas->Update();
	
	// =================================== MATH TEXT Q3 ===========================================
	//GetTextCanvas
	fCanvas->cd(1);
	
	TPTmath = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmath->SetTextColor(kBlack);
	TPTmath->SetTextSize(0.05);
	TPTmath->SetFillColor(18);
	TPTmath->SetShadowColor(18);
	
	switch(Break){
		case 0: 
			TPTmath->AddText("From the general formula, replace #font[12]{#font[22]{#color[2]{n=3}}}.");
			TPTmath->AddText("The tensor product #font[12]{#font[22]{k}} goes from one");
			TPTmath->AddText("to #font[12]{#font[22]{n}}. For the first case #font[12]{#font[22]{#color[2]{k=3}}}.");
		break;  
		case 1: 
			TPTmath->AddText("The sum is solved."); 
		break;
		case 2:
			TPTmath->AddText("It is replaced in the general equation.");
		break;
		case 3:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and you get the result of the");
			TPTmath->AddText("First Tensor.");
		break;
		case 4:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard gate}} to the last qubit.");
		break;
		case 5:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi/ 2)}}");
			TPTmath->AddText("to the last qubit.");
		break;
		case 6:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 4)}}");
			TPTmath->AddText("to the last qubit.");
		break;
		case 7: 
			TPTmath->AddText("For the second tensor #font[12]{#font[22]{#color[4]{k=2}}}.");
			TPTmath->AddText("The sum is resolved.");
		break;
		case 8:
			TPTmath->AddText("It is replaced in the general equation.");
		break;
		case 9:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and you get the result of the");
			TPTmath->AddText("Second Tensor.");
		break;
		case 10:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard  gate}} to the second qubit.");
		break;
		case 11:
			TPTmath->AddText("This expression indicates the application of the ");
			TPTmath->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi/ 2)}}");
			TPTmath->AddText("to the second qubit.");
		break;
		case 12: 
			TPTmath->AddText("For the third tensor #font[12]{#font[22]{#color[8]{k=1}}}.");
		break;
		case 13:
			TPTmath->AddText("It is replaced in the general equation");
		break;
		case 14:
			TPTmath->AddText("Simplify what is inside the");
			TPTmath->AddText("exponential and you get the result of the");
			TPTmath->AddText("Third Tensor.");
		break;
		case 15:
			TPTmath->AddText("This expression indicates the application of the");
			TPTmath->AddText("#font[12]{#font[22]{Hadamard gate}} to the first qubit.");
		break;
		case 16:
			TPTmath->AddText("This is the general mathematical expression");
			TPTmath->AddText("for a 3 qubit system.");
		break;
		case 18:
			TPTmath->AddText("#color[4]{exp #left[ #pi i #right]}.");
		break;
		case 19:
			TPTmath->AddText("#color[6]{exp #left[ #frac{#pi i}{2} #right]}.");
		break;
		case 20:
			TPTmath->AddText("#color[51]{exp #left[ #frac{#pi i}{4} #right]}.");
		break;
		case 21:
			TPTmath->AddText("Sum of exp #left[ #pi + #frac{#pi}{2} #right] = #color[65]{exp #left[ #frac{3#pi}{2} #right]}.");
		break;
		case 22:
			TPTmath->AddText("Sum of exp #left[ #pi + #frac{#pi}{4} #right] = #color[50]{exp #left[ #frac{5#pi}{2} #right]}.");
		break;
		case 23:
			TPTmath->AddText("Sum of exp #left[ #pi + #frac{#pi}{2} + #frac{#pi}{4} #right] = #color[97]{exp #left[ #frac{7#pi}{4} #right]}.");
		break;
		case 17:
			TPTmath->AddText("Application of #font[12]{#font[22]{Swap gate}}. Final mathematical");
			TPTmath->AddText("expression of the Quantum Fourier Transform.");
		break;
	}

	TPTmath->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	// =================================== CIRCUIT DRAW Q3 ===========================================
	//GetBigCanvas 
	fCanvas->cd(2);
	gPad->SetEditable(1);
	//Desing
	Tline4->Draw();
	Tline5->Draw();
	Tline6->Draw();
	
	Tline7 = new TLine(0.22,0.97,0.995,0.97);
	Tline7->Draw();
	Tline8->Draw();
	
	if(Break > 3 and Break < 7){
		name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();
	}
	else if(Break ==10 or Break == 11){
		name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();
	}
	else if(Break > 14){
		name1 = new TLatex(0.05,0.95,"#color[2]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();
	}
	else {
		name1 = new TLatex(0.05,0.95,"#color[14]{CIRCUIT}");
		name1->SetTextSize(0.06);
		name1->Draw();
	}

	
	TPad *pad2 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad2->SetFillColor(0);
	pad2->Draw();	
	pad2->cd();

	//Dibujo Base Circuit
	line = new TLine(0.110,0.250,0.970,0.250);
	line->SetLineWidth(3);
	line->Draw();

	line = new TLine(0.110,0.500,0.970,0.500);
	line->SetLineWidth(3);
	line->Draw();
	
	line = new TLine(0.110,0.750,0.970,0.750);
	line->SetLineWidth(3);
	line->Draw();

	HD = new TLatex(0.010,0.720,"#scale[1.7]{#cbar x_{0}#GT}");
	HD->Draw();

	HD = new TLatex(0.010,0.480,"#scale[1.7]{#cbar x_{1}#GT}");
	HD->Draw();

	HD = new TLatex(0.010,0.230,"#scale[1.7]{#cbar x_{2}#GT}");
	HD->Draw();

	switch(Break){
		case 4: 
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
		break;
		case 5:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 6:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();
	 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 7: 
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
 			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
		case 8:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
 			HD->Draw(); 
 
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
 			Rot->Draw();
		break;
		case 9:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
 			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
 			line->Draw();
 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
 			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.375,0.750,20);
 			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
		case 10:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
 			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
 			circle->Draw();
 
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
 			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
		break;
		case 11:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
 
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
 
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
		 
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.480,0.470,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
		
			Rot = new TLatex(0.540,0.600,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
 
			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
 
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();
 
			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
 
			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();
 
			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  
 
		break;
		case 12:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();
          
			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
	
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
	
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   
		
			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
	   	break;
   		case 13:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
		
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
	   	break;
   		case 14:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
	
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   
			
			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
		
			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
	
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
		break;
		case 15:
   	    	//Compuerta Hadamard1
   	    	Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
		
			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  
	
			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#color[8]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#color[8]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
   		case 16:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
		
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
	
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw();	 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#color[8]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#color[8]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
		break;
	   	case 18:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#scale[1.7]{R_{2}}");
			HD->SetLineWidth(2);
			HD->Draw(); 	

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#scale[1.7]{#frac{#pi}{4}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
		break;
		case 19:
			//Compuerta Hadamard1
   			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
	
			Rot = new TLatex(0.195,0.350,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   
	
			HD = new TLatex(0.235,0.230,"#color[6]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[6]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();	 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#scale[1.7]{R_{2}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#scale[1.7]{#frac{#pi}{4}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   
			
			HD = new TLatex(0.580,0.480,"#color[6]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[6]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
		break;
		case 20:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   
	
			HD = new TLatex(0.235,0.230,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
	
			Rot = new TLatex(0.305,0.350,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[51]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[51]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
	
			Rot = new TLatex(0.540,0.600,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
		break;
		case 21:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[65]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[65]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[65]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
	
			Rot = new TLatex(0.305,0.350,"#color[65]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 
	
			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   
			
			HD = new TLatex(0.355,0.230,"#scale[1.7]{R_{2}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#scale[1.7]{#frac{#pi}{4}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[65]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[65]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   
	
			HD = new TLatex(0.580,0.480,"#color[65]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[65]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
		break;
		case 22:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[50]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[50]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   
	
			HD = new TLatex(0.235,0.230,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#scale[1.7]{#color[50]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[50]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
		
			Rot = new TLatex(0.540,0.600,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
		
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();
			
			Rot = new TLatex(0.765,0.850,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
		break;
		case 23:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[97]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();
		
			Rot = new TLatex(0.195,0.350,"#color[97]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[97]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 
	
			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();
	
			Rot = new TLatex(0.305,0.350,"#color[97]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   
		
			HD = new TLatex(0.355,0.230,"#color[97]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[97]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
			
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#scale[1.7]{R_{1}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#scale[1.7]{#frac{#pi}{2}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#scale[1.7]{H}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#scale[1.7]{#pi}");
			Rot->SetLineWidth(2);
			Rot->Draw();
			
			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#scale[2.5]{X}");
			x->SetLineWidth(2);
			x->Draw();
	   	break;
	   	case 17:
			//Compuerta Hadamard1
			Square = new TPave(0.120,0.175,0.175,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.135,0.220,"#color[2]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.195,0.350,"#color[2]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.25,0.250,0.25,0.500);
			line->SetLineWidth(3);
			line->Draw();
		
			Square = new TPave(0.225,0.175,0.280,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.235,0.230,"#color[2]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.25,0.500,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.305,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw(); 

			//Compuerta URot2
			line = new TLine(0.375,0.250,0.375,0.750);
			line->SetLineWidth(3);
			line->Draw();

			Square = new TPave(0.345,0.175,0.400,0.325,2,"br");
			Square->Draw();   

			HD = new TLatex(0.355,0.230,"#color[2]{#scale[1.7]{R_{2}}}");
			HD->SetLineWidth(2);
			HD->Draw(); 

			circle = new TMarker(0.375,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.425,0.350,"#color[2]{#scale[1.7]{#frac{#pi}{4}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
	
			//Compuerta Hadamard2
			Square = new TPave(0.465,0.425,0.520,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.480,0.470,"#color[4]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.540,0.600,"#color[4]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();

			//Compuerta URot1
			line = new TLine(0.600,0.500,0.600,0.750);
			line->SetLineWidth(3);
			line->Draw();
	
			Square = new TPave(0.570,0.425,0.625,0.575,2,"br");
			Square->Draw();   

			HD = new TLatex(0.580,0.480,"#color[4]{#scale[1.7]{R_{1}}}");
			HD->SetLineWidth(2);
			HD->Draw();	 

			circle = new TMarker(0.600,0.750,20);
			circle->SetMarkerSize(2);
			circle->Draw();

			Rot = new TLatex(0.650,0.600,"#color[4]{#scale[1.7]{#frac{#pi}{2}}}");
			Rot->SetLineWidth(2);
			Rot->Draw();  

			//Compuerta Hadamard2
			Square = new TPave(0.690,0.675,0.745,0.825,2,"br");
			HD->SetLineWidth(2);
			Square->Draw();   

			HD = new TLatex(0.705,0.720,"#color[8]{#scale[1.7]{H}}");
			HD->SetLineWidth(2);
			HD->Draw();

			Rot = new TLatex(0.765,0.850,"#color[8]{#scale[1.7]{#pi}}");
			Rot->SetLineWidth(2);
			Rot->Draw();
            
			line = new TLine(0.85,0.250,0.85,0.750);
			line->SetLineWidth(3);
			line->Draw();

			x = new TLatex(0.8325,0.709,"#color[2]{#scale[2.5]{X}}");
			x->SetLineWidth(2);
			x->Draw();

			x = new TLatex(0.8325,0.209,"#color[8]{#scale[2.5]{X}}");
			x->SetLineWidth(2);
			x->Draw();

		break;
	}
	
	fCanvas->Update();
	
	// =================================== CIRCUIT TEXT Q3 ===========================================
	//GetTextCanvas
	fCanvas->cd(2);
	
	TPTcircuit = new TPaveText(0.03,0.04,0.97,0.2);
	TPTcircuit->SetTextColor(kBlack);
	TPTcircuit->SetTextSize(0.05);
	TPTcircuit->SetFillColor(18);
	TPTcircuit->SetShadowColor(18);
 
	switch(Break){
		case 4:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}}  to x_{2}.");
		break;
		case 5:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} to x_{2}.");
		break;
		case 6:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 4)}} to x_{2}.");
		break;
		case 10:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}}  to x_{1}.");
		break;
   		case 11:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} to x_{1}.");
		break;
		case 15:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate}}  to x_{0}.");
		break;
		case 16:
			TPTcircuit->AddText("Mathematical applications to the circuit.");
		break;
		case 18:
			TPTcircuit->AddText("Application of the #font[12]{#font[22]{Hadamard gate} (#color[4]{#pi})}.");
   		break;
   		case 19:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{#color[6]{#pi/2} Controlled-Rotation gate}}.");
		break;
		case 20:
			TPTcircuit->AddText("Application of");
			TPTcircuit->AddText("#font[12]{#font[22]{#color[51]{#pi/4} Controlled-Rotation gate}}.");
		break;
		case 21:
			TPTcircuit->AddText("Sum of #pi + #frac{#pi}{2}  = #color[65]{#frac{3#pi}{2} }.");
		break;
		case 22:
			TPTcircuit->AddText("Sum of #pi + #frac{#pi}{4} = #color[50]{#frac{5#pi}{2}}.");
		break;
		case 23:
			TPTcircuit->AddText("Sum of #pi + #frac{#pi}{2} + #frac{#pi}{4} = #color[97]{#frac{7#pi}{4}} .");
		break;
		case 17:
			TPTcircuit->AddText("Application of #font[12]{#font[22]{Swap gate}}.");
			TPTcircuit->AddText("Final circuit of the Quantum Fourier Transform.");
		break;
		default:
			TPTcircuit->AddText(" ");
		break;
	}
	
	TPTcircuit->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
	
	// =================================== BLOCH DRAW Q3 ===========================================
	//GetBigCanvas 
	fCanvas->cd(3);
	
	//Desing
	Tline4->Draw();
	Tline5->Draw();
	Tline6->Draw();
	
	Tline7 = new TLine(0.36,0.97,0.995,0.97);
	Tline7->Draw();
	Tline8->Draw();

	if(Break > 3 and Break < 7){
		name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break ==10 or Break == 11){
		name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break > 14 and Break < 18){
		name2 = new TLatex(0.05,0.95,"#color[2]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break > 6 and Break < 10){
		name2 = new TLatex(0.05,0.95,"#color[14]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break > 11 and Break < 15){
		name2 = new TLatex(0.05,0.95,"#color[14]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else if(Break >=0 and Break < 4){
		name2 = new TLatex(0.05,0.95,"BLOCH SPHERE");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	else {
		name2 = new TLatex(0.05,0.95,"#color[14]{BLOCH SPHERE}");
		name2->SetTextSize(0.06);
		name2->Draw();
	}
	
	TPad *pad31 = new TPad("pad2","This is pad2",0.03,0.22,0.323,0.925);
	pad31->SetFillColor(0);
	pad31->Draw();	
	
	TPad *pad32 = new TPad("pad2","This is pad2",0.323,0.22,0.646,0.925);
	pad32->SetFillColor(0);
	pad32->Draw();
	
	TPad *pad33 = new TPad("pad2","This is pad2",0.646,0.22,0.97,0.925);
	pad33->SetFillColor(0);
	pad33->Draw();
	
	TGeoManager *geom = new TGeoManager("geom","Bloch");
	TGeoMaterial *vacuum=new TGeoMaterial("vacuum",0,0,0);
	TGeoMaterial *Fe=new TGeoMaterial("Fe",55.845,26,7.87);
	 
	TGeoMedium *Air=new TGeoMedium("Vacuum",0,vacuum);
	TGeoMedium *Iron=new TGeoMedium("Iron",1,Fe);
	
	// PRIMER QUBIT
	TGeoVolume *top=geom->MakeBox("top",Air,140,140,140);
	geom->SetTopVolume(top);
	geom->SetTopVisible(1);
	
	// If you want to see the boundary, please input the number, 1 instead of 0.
	// Like this, geom->SetTopVisible(1);

	TGeoVolume *sp0=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp1=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	TGeoVolume *sp2=geom->MakeSphere("sp0",Iron,0,100,0,180,0,360);
	
	TGeoVolume *X= geom->MakeTube("X",Iron, 0,1,110);
	X->SetLineColor(13);
 
	TGeoVolume *Y= geom->MakeTube("Y",Iron, 0,1,110);
	Y->SetLineColor(13);

	TGeoVolume *Z= geom->MakeTube("Z",Iron, 0,1,110);
	Z->SetLineColor(13);
	
	TGeoVolume *x1= geom->MakeTube("x1",Iron, 0,1,10);
	x1->SetLineColor(1);
	
	TGeoVolume *x2= geom->MakeTube("x2",Iron, 0,1,10);
	x2->SetLineColor(1);
	
	TGeoVolume *x3= geom->MakeTube("x3",Iron, 0,1,10);
	x3->SetLineColor(1);
	
	TGeoVolume *y1= geom->MakeTube("y1",Iron, 0,1,7);
	y1->SetLineColor(1);
	
	TGeoVolume *y11= geom->MakeTube("y11",Iron, 0,1,1);
	y11->SetLineColor(1);
	
	TGeoVolume *y2= geom->MakeTube("y2",Iron, 0,1,7);
	y2->SetLineColor(1);
	
	TGeoVolume *y21= geom->MakeTube("y21",Iron, 0,1,1);
	y21->SetLineColor(1);
	
	TGeoVolume *y22= geom->MakeTube("y22",Iron, 0,1,3);
	y22->SetLineColor(1);
	
	TGeoVolume *z1=geom->MakeTubs("z1",Iron,3,4,1,0,180);
    z1->SetLineColor(1);
    
    TGeoVolume *z12=geom->MakeTubs("z12",Iron,3,4,1,180,360);
    z12->SetLineColor(1);
	
	TGeoVolume *z13= geom->MakeBox("z13",Iron, 0.5,1,5);
	z13->SetLineColor(1);
	z13->SetFillColor(1);
	
	TGeoVolume *z14= geom->MakeBox("z14",Iron, 0.5,1,5);
	z14->SetLineColor(1);
	z14->SetFillColor(1);
	
	TGeoVolume *z2= geom->MakeTube("z2",Iron, 0,1,7);
	z2->SetLineColor(1);
	
	TGeoVolume *z3= geom->MakeTube("z3",Iron, 0,1,3.5);
	z3->SetLineColor(1);
	
	TGeoVolume *vec= geom->MakeTube("vec",Iron, 0,2,50);
	vec->SetLineColor(2);

	TGeoVolume *cone=geom->MakeCone("cone",Iron,10,0,10,0,0);
	cone->SetLineColor(2);
	cone->SetFillColor(2); 
  
	top->AddNodeOverlap(sp0,1,new TGeoRotation("sp0",0,0,0));
	top->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));	
  
	//SEGUNDO QUBIT
	TGeoVolume *top1=geom->MakeBox("top1",Air,140,140,140);
	geom->SetTopVolume(top1);
	geom->SetTopVisible(1);
	
	top1->AddNodeOverlap(sp1,1,new TGeoRotation("sp0",0,0,0));
	top1->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top1->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top1->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top1->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top1->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top1->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top1->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top1->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
	
	//TERCER QUBIT
	TGeoVolume *top2=geom->MakeBox("top2",Air,140,140,140);
	geom->SetTopVolume(top2);
	geom->SetTopVisible(1);
	
	top2->AddNodeOverlap(sp2,1,new TGeoRotation("sp2",0,0,0));
	top2->AddNodeOverlap(X,1,new TGeoRotation("x",0,90,0));
	top2->AddNodeOverlap(Y,1,new TGeoRotation("y",90,90,0));
	top2->AddNodeOverlap(Z,1,new TGeoRotation("z",0,0,0));
	top2->AddNodeOverlap(x1,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(x2,1,new TGeoCombiTrans(-120,0,0,new TGeoRotation("ha2",0,90,0)));
	top2->AddNodeOverlap(x3,1,new TGeoCombiTrans(120,0,0,new TGeoRotation("ha2",0,90,0)));
	top2->AddNodeOverlap(y1,1,new TGeoCombiTrans(0,-125,0,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(y11,1,new TGeoCombiTrans(0,-125,10,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(y2,1,new TGeoCombiTrans(0,123,0,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(y21,1,new TGeoCombiTrans(0,123,10,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(y22,1,new TGeoCombiTrans(0,130,0,new TGeoRotation("ha2",0,90,0)));
	top2->AddNodeOverlap(z1,1,new TGeoCombiTrans(0,0,130, new TGeoRotation("r14",0,90,0)));
	top2->AddNodeOverlap(z12,1,new TGeoCombiTrans(0,0,120, new TGeoRotation("r14",0,90,0)));
	top2->AddNodeOverlap(z13,1,new TGeoCombiTrans(-3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top2->AddNodeOverlap(z14,1,new TGeoCombiTrans(3.5,0,125, new TGeoRotation("r14",0,0,0)));
	top2->AddNodeOverlap(z2,1,new TGeoCombiTrans(0,0,-130,new TGeoRotation("ha2",0,0,0)));
	top2->AddNodeOverlap(z3,1,new TGeoCombiTrans(0,3,-125,new TGeoRotation("ha2",0,45,0)));
   
	switch(Break){
		case 0: 
		//ESTADO PRIMER QUBIT
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(3,0.1);
        		sp0->SetFillColorAlpha(3,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(3,0.1);
               	sp0->SetFillColorAlpha(3,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[8]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
			}
			if(X1==1){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
   			if(X2==0){
		    	sp2->SetLineColorAlpha(13,0.1);
               	sp2->SetFillColorAlpha(13,0.1);
			}
			else{
				sp2->SetLineColorAlpha(13,0.1);
        		sp2->SetFillColorAlpha(13,0.1);
			
   			}
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();
		break;
		case 1:
		//ESTADO SEGUNDO QUBIT
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0){
				sp1->SetLineColorAlpha(4,0.1);
        		sp1->SetFillColorAlpha(4,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(4,0.1);
               	sp1->SetFillColorAlpha(4,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[4]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
   			if(X2==0){
		    	sp2->SetLineColorAlpha(13,0.1);
               	sp2->SetFillColorAlpha(13,0.1); 
			}
			else{
				sp2->SetLineColorAlpha(13,0.1);
        		sp2->SetFillColorAlpha(13,0.1);
			}
   
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();	
		break;
		case 2:
		//ESTADO TERCER QUBIT
			//PRIMER QUBIT 
			pad31->cd();
			
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
   			if(X2==1){
		    	sp2->SetLineColorAlpha(2,0.1);
               	sp2->SetFillColorAlpha(2,0.1);
		
				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q2",90,0,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q2",0,180,0)));   
			}
			else{
				sp2->SetLineColorAlpha(2,0.1);
        		sp2->SetFillColorAlpha(2,0.1);
			
				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
   
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   
			fCanvas->Update();
		break;
		case 3:
		//ESTADO GENERAL
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
   			if(X2==1){
		    	sp2->SetLineColorAlpha(13,0.1);
               	sp2->SetFillColorAlpha(13,0.1);
		
				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q2",90,0,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q2",0,180,0)));   
			}
			else{
				sp2->SetLineColorAlpha(13,0.1);
        		sp2->SetFillColorAlpha(13,0.1);
			
				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("ha2",0,0,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("ha2",0,0,0)));   
			}
   
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();
		break;
		case 4:
		//APLICACION COMPUERTA H -> x2		
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
			if(X2==0){
				sp2->SetLineColorAlpha(2,0.1);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X2==1){
				sp2->SetLineColorAlpha(2,0.2);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
   
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   
			fCanvas->Update();
		break;
		case 5:
		//APLICACION COMPUERTA R(1/2) -> x2
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			
			if(X2==0 and X1==0){
				sp2->SetLineColorAlpha(2,0.1);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X2==0 and X1==1){
				sp2->SetLineColorAlpha(2,0.1);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X2==1 and X1==0){
				sp2->SetLineColorAlpha(2,0.2);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X2==1 and X1==1){
				sp2->SetLineColorAlpha(2,0.2);
				sp2->SetFillColorAlpha(2,0.1);

				top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0)));   
			}
   
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 6:
		//APLICACION COMPUERTA R(1/4) -> x2
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   
			fCanvas->Update();			
		break;
		case 7:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 8:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 9:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(13,0.1);
        		sp1->SetFillColorAlpha(13,0.1);
			
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q1",0,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q1",0,0,0)));   
			}
			if(X1==1){
		    	sp1->SetLineColorAlpha(13,0.1);
               	sp1->SetFillColorAlpha(13,0.1);
		
				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q1",90,0,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q1",0,180,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();	
		break;
		case 10:
		//APLICACION COMPUERTA H ->x1
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			if(X1==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[4]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 11:
		//APLICACION COMPUERTA R(1/2) ->x1
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[4]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[4]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 12:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 13:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 14:
		//NOTHING
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(13,0.1);
        		sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,50,new TGeoRotation("q0",0,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,96,new TGeoRotation("q0",0,0,0)));   
			}
			if(X0==1){
			   	sp0->SetLineColorAlpha(13,0.1);
               	sp0->SetFillColorAlpha(13,0.1);
			
				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,0,-50,new TGeoRotation("q0",90,0,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,0,-96,new TGeoRotation("q0",0,180,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{0}#GT}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();	
		break;
		case 15:
		//APLICACION COMPUERTA H -> x0
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(3,0.1);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(3,0.2);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[8]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
			
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{2}#GT}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 16:
		//ESTADO GENERAL DEL SISTEMA
			//PRIMER QUBIT 
			pad31->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(3,0.1);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(3,0.2);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[8]{|x_{0}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[4]{|x_{1}#GT}}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad33->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{2}#GT}}");
			HD->Draw();
   
			fCanvas->Update();		
		break;
		case 17:
		//APLICACION COMPUERTA SWAP
			//PRIMER QUBIT 
			pad33->cd();
			if(X0==0){
				sp0->SetLineColorAlpha(3,0.1);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X0==1){
				sp0->SetLineColorAlpha(3,0.2);
				sp0->SetFillColorAlpha(3,0.1);

				top->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
  
			top->SetVisibility(0);
			geom->CloseGeometry();
			top->Draw();
   	   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[8]{|x_{2}#GT}}");
			HD->Draw();
   	
			fCanvas->Update();

			//SEGUNDO QUBIT
			pad32->cd();
			
			if(X1==0 and X0==0){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));   
			}
			if(X1==0 and X0==1){
				sp1->SetLineColorAlpha(4,0.1);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));   
			}
			if(X1==1 and X0==0){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
			}
			if(X1==1 and X0==1){
				sp1->SetLineColorAlpha(4,0.2);
				sp1->SetFillColorAlpha(4,0.1);

				top1->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
				top1->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",180,90,0)));
			}
   
   			top1->SetVisibility(0);
   			geom->CloseGeometry();
   			top1->Draw();
   			
   			HD = new TLatex(-0.95,0.75,"#scale[3]{|x_{1}#GT}");
			HD->Draw();
   	
   			fCanvas->Update();
        
			//TERCER QUBIT
			pad31->cd();
   			if(X1==0){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-96,0,0,new TGeoRotation("ha2",90,-90,0)));    
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,-36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,-68,0,new TGeoRotation("ha2",-45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(50,0,0,new TGeoRotation("ha2",90,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(96,0,0,new TGeoRotation("ha2",90,90,0)));   
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,36,0,new TGeoRotation("ha2",-45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,68,0,new TGeoRotation("ha2",-45,-90,0)));   
				}
   			}
   			
   			if(X1==1){
				if(X2==0 and X0==0){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,-50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,-96,0,new TGeoRotation("ha2",0,90,0)));
				}
				if(X2==0 and X0==1){
					sp2->SetLineColorAlpha(2,0.1);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(36,-36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(68,-68,0,new TGeoRotation("ha2",45,90,0)));   
				}
				if(X2==1 and X0==0){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(0,50,0,new TGeoRotation("ha2",0,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(0,96,0,new TGeoRotation("ha2",0,-90,0))); 
				}
				if(X2==1 and X0==1){
					sp2->SetLineColorAlpha(2,0.2);
					sp2->SetFillColorAlpha(2,0.1);

					top2->AddNodeOverlap(vec,1,new TGeoCombiTrans(-36,36,0,new TGeoRotation("ha2",45,90,0)));
					top2->AddNodeOverlap(cone,1,new TGeoCombiTrans(-68,68,0,new TGeoRotation("ha2",45,-90,0)));     
				}
   			}
   			
			top2->SetVisibility(0);
			geom->CloseGeometry();
			top2->Draw();
   	
			HD = new TLatex(-0.95,0.75,"#scale[3]{#color[2]{|x_{0}#GT}}");
			HD->Draw();
   
			fCanvas->Update();	
		break;
	}
	
	fCanvas->Update();
	
	// =================================== BLOCH TEXT Q3 ===========================================
	//GetTextCanvas
	fCanvas->cd(3);
	
	TPTbloch = new TPaveText(0.03,0.04,0.97,0.2);
	TPTbloch->SetTextColor(kBlack);
	TPTbloch->SetTextSize(0.05);
	TPTbloch->SetFillColor(18);
	TPTbloch->SetShadowColor(18);
	
		switch(Break){
		case 0:
			TPTbloch->AddText("Initial state of the qubit #color[2]{x_{0}}");
 		break;
 		case 1:
			TPTbloch->AddText("Initial state of the qubit #color[2]{x_{1}}");
 		break;
 		case 2:
			TPTbloch->AddText("Initial state of the qubit #color[2]{x_{2}}");
 		break;
 		case 3:
			TPTbloch->AddText("General state of the qubit system.");
 		break;
 		case 4:
			TPTbloch->AddText("State of the qubit #color[2]{x_{2}} when applying the #font[12]{#font[22]{Hadamard gate}}.");
 		break;
 		case 5:
			TPTbloch->AddText("State of the qubit #color[2]{x_{2}} when applying the ");
			TPTbloch->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} .");
 		break;
 		case 6:
			TPTbloch->AddText("State of the qubit #color[2]{x_{2}} when applying the ");
			TPTbloch->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 4)}} .");
 		break;
 		case 10:
			TPTbloch->AddText("State of the qubit #color[4]{x_{1}} when applying the #font[12]{#font[22]{Hadamard gate}}");
 		break;
 		case 11:
			TPTbloch->AddText("State of the qubit #color[2]{x_{1}} when applying the ");
			TPTbloch->AddText("#font[12]{#font[22]{Controlled-Rotation gate (#pi / 2)}} .");
 		break;
 		case 15:
			TPTbloch->AddText("State of the qubit #color[8]{x_{0}} when applying the #font[12]{#font[22]{Hadamard gate}}");
 		break;
 		case 16:
			TPTbloch->AddText("Overall system status");
 		break;
 		case 17:
			TPTbloch->AddText("System state when applying the #font[12]{#font[22]{Swap gate}}.");
			TPTbloch->AddText("Final state of the Quantum Fourier Transform.");
 		break;
 		default:
			TPTbloch->AddText(" ");
 		break;
	}
	 
	TPTbloch->Draw();
	fCanvas->Update();
	
	// =================================== MATRIX DRAW Q3 ===========================================
	//GetBigCanvas 
	fCanvas->cd(4);
	gPad->SetEditable(1);
	//Desing
	Tline4->Draw();
	Tline5->Draw();
	Tline6->Draw();
	
	Tline7 = new TLine(0.22,0.97,0.995,0.97);
	Tline7->Draw();
	Tline8->Draw();
	
	if(Break >= 17){
		name3 = new TLatex(0.05,0.95,"#color[2]{MATRIX}");
		name3->SetTextSize(0.06);
		name3->Draw();
	}
	else {
		name3 = new TLatex(0.05,0.95,"MATRIX");
		name3->SetTextSize(0.06);
		name3->Draw();
	}
	
	TPad *pad4 = new TPad("pad2","This is pad2",0.03,0.22,0.97,0.925);
	pad4->SetFillColor(0);
	pad4->Draw();	
	pad4->cd();
  
	//Base QFT	 
	switch(Break){
		case 0: 
			//Base Matrix
			sprintf(line1, "#color[2]{1}      #color[2]{1}      #color[2]{1}      #color[2]{1}      #color[2]{1}      #color[2]{1}      #color[2]{1}      #color[2]{1}");
			sprintf(line2, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line3, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line4, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line5, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line6, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line7, "#color[2]{1}           0          0           0          0          0           0          0"); 
			sprintf(line8, "#color[2]{1}           0          0           0          0          0           0          0"); 
		break;        
		case 1: 
			//Columna 1
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #color[2]{#omega^{1}}          0          0           0           0           0          0"); 
			sprintf(line3, "1     #color[2]{#omega^{2}}          0          0           0          0           0          0"); 
			sprintf(line4, "1     #color[2]{#omega^{3}}          0          0           0          0           0          0"); 
			sprintf(line5, "1     #color[2]{#omega^{4}}          0          0           0          0           0          0"); 
			sprintf(line6, "1     #color[2]{#omega^{5}}          0          0           0          0           0          0"); 
			sprintf(line7, "1     #color[2]{#omega^{6}}          0          0           0          0           0          0"); 
			sprintf(line8, "1     #color[2]{#omega^{7}}          0          0           0          0           0          0"); 
		break;
		case 2:
			//Columna 2
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #color[2]{#omega^{2}}          0          0           0           0          0"); 
			sprintf(line3, "1     #omega^{2}     #color[2]{#omega^{4}}          0          0          0           0          0"); 
			sprintf(line4, "1     #omega^{3}     #color[2]{#omega^{6}}          0          0          0           0          0"); 
			sprintf(line5, "1     #omega^{4}     #color[2]{#omega^{8}}          0          0          0           0          0"); 
			sprintf(line6, "1     #omega^{5}     #color[2]{#omega^{2}}          0          0          0           0          0"); 
			sprintf(line7, "1     #omega^{6}     #color[2]{#omega^{4}}          0          0          0           0          0"); 
			sprintf(line8, "1     #omega^{7}     #color[2]{#omega^{6}}          0          0          0           0          0");
		break;
		case 3:
			//Columna 3
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #color[2]{#omega^{3}}         0          0           0          0"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #color[2]{#omega^{6}}         0          0           0          0"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #color[2]{#omega^{1}}         0          0           0          0"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #color[2]{#omega^{4}}         0          0           0          0"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #color[2]{#omega^{7}}         0          0           0          0"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #color[2]{#omega^{2}}         0          0           0          0"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #color[2]{#omega^{5}}         0          0           0          0"); 
		break;   
		case 4:
			//Columna 4	
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #omega^{3}    #color[2]{#omega^{4}}          0          0          0"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #color[2]{#omega^{8}}          0          0          0"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #omega^{1}    #color[2]{#omega^{4}}          0          0          0"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #color[2]{#omega^{8}}          0          0          0"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #color[2]{#omega^{4}}          0          0          0"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #color[2]{#omega^{8}}          0          0          0"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #color[2]{#omega^{4}}          0          0          0");
		break;
		case 5:
			//Columna 5
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #omega^{3}    #omega^{4}     #color[2]{#omega^{5}}          0         0"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #omega^{8}     #color[2]{#omega^{2}}          0         0"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #omega^{1}    #omega^{4}     #color[2]{#omega^{7}}          0         0"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #color[2]{#omega^{4}}          0         0"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #omega^{4}     #color[2]{#omega^{1}}          0         0"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #omega^{8}     #color[2]{#omega^{6}}          0         0"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #color[2]{#omega^{3}}          0         0");
		break;
		case 6:
			//Columna 6
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #omega^{3}    #omega^{4}     #omega^{5}     #color[2]{#omega^{6}}         0"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #omega^{8}     #omega^{2}     #color[2]{#omega^{4}}         0"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #omega^{1}    #omega^{4}     #omega^{7}     #color[2]{#omega^{2}}         0"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #color[2]{#omega^{8}}         0"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #omega^{4}     #omega^{1}     #color[2]{#omega^{6}}         0"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #omega^{8}     #omega^{6}     #color[2]{#omega^{4}}         0"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #omega^{3}     #color[2]{#omega^{2}}         0");
		break;
		case 7: 
			//Columna 7
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #omega^{3}    #omega^{4}     #omega^{5}     #omega^{6}    #color[2]{#omega^{7}}");
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #omega^{8}     #omega^{2}     #omega^{4}    #color[2]{#omega^{6}}"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #omega^{1}    #omega^{4}     #omega^{7}     #omega^{2}    #color[2]{#omega^{5}}"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #omega^{8}    #color[2]{#omega^{4}}");  
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #omega^{4}     #omega^{1}     #omega^{6}    #color[2]{#omega^{3}}"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #omega^{8}     #omega^{6}     #omega^{4}    #color[2]{#omega^{2}}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #omega^{3}     #omega^{2}    #color[2]{#omega^{1}}"); 
		break;
		case 8:
			//Matrix General w
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #omega^{1}     #omega^{2}     #omega^{3}    #omega^{4}     #omega^{5}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #omega^{8}     #omega^{2}     #omega^{4}    #omega^{6}"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #omega^{1}    #omega^{4}     #omega^{7}     #omega^{2}    #omega^{5}"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #omega^{8}    #omega^{4}"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #omega^{4}     #omega^{1}     #omega^{6}    #omega^{3}"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #omega^{8}     #omega^{6}     #omega^{4}    #omega^{2}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #omega^{3}     #omega^{2}    #omega^{1}");
		break;
		case 9:
			//w1
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     #color[2]{^{#pi}/_{4}}     #omega^{2}     #omega^{3}    #omega^{4}     #omega^{5}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     #omega^{2}     #omega^{4}     #omega^{6}    #omega^{8}     #omega^{2}     #omega^{4}    #omega^{6}"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     #color[2]{^{#pi}/_{4}}    #omega^{4}     #omega^{7}     #omega^{2}    #omega^{5}"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #omega^{8}    #omega^{4}"); 
			sprintf(line6, "1     #omega^{5}     #omega^{2}     #omega^{7}    #omega^{4}     #color[2]{^{#pi}/_{4}}     #omega^{6}    #omega^{3}"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #omega^{2}    #omega^{8}     #omega^{6}     #omega^{4}    #omega^{2}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #omega^{3}     #omega^{2}    #color[2]{^{#pi}/_{4}}");
		break;
		case 10:
			//w2
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     #color[2]{^{#pi}/_{2}}     #omega^{3}    #omega^{4}     #omega^{5}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     #color[2]{^{#pi}/_{2}}     #omega^{4}     #omega^{6}    #omega^{8}     #color[2]{^{#pi}/_{2}}     #omega^{4}    #omega^{6}"); 
			sprintf(line4, "1     #omega^{3}     #omega^{6}     ^{#pi}/_{4}    #omega^{4}     #omega^{7}     #color[2]{^{#pi}/_{2}}    #omega^{5}"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #omega^{8}    #omega^{4}"); 
			sprintf(line6, "1     #omega^{5}     #color[2]{^{#pi}/_{2}}     #omega^{7}    #omega^{4}     ^{#pi}/_{4}     #omega^{6}    #omega^{3}"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     #color[2]{^{#pi}/_{2}}    #omega^{8}     #omega^{6}     #omega^{4}    #color[2]{^{#pi}/_{2}}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}     #omega^{3}     #color[2]{^{#pi}/_{2}}    ^{#pi}/_{4}");
		break;
		case 11:
			//w3
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    #color[2]{^{3#pi}/_{4}}    #omega^{4}     #omega^{5}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #omega^{4}     #omega^{6}    #omega^{8}     ^{#pi}/_{2}     #omega^{4}    #omega^{6}"); 
			sprintf(line4, "1    #color[2]{^{3#pi}/_{4}}     #omega^{6}     ^{#pi}/_{4}    #omega^{4}     #omega^{7}     ^{#pi}/_{2}    #omega^{5}"); 
			sprintf(line5, "1     #omega^{4}     #omega^{8}     #omega^{4}    #omega^{8}     #omega^{4}     #omega^{8}    #omega^{4}"); 
			sprintf(line6, "1     #omega^{5}     ^{#pi}/_{2}     #omega^{7}    #omega^{4}     ^{#pi}/_{4}     #omega^{6}    #color[2]{^{3#pi}/_{4}}"); 
			sprintf(line7, "1     #omega^{6}     #omega^{4}     ^{#pi}/_{2}    #omega^{8}     #omega^{6}     #omega^{4}    ^{#pi}/_{2}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #omega^{4}    #color[2]{^{3#pi}/_{4}}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 12: 
			//w4
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #color[2]{#pi}      #omega^{5}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #color[2]{#pi}      #omega^{6}    #omega^{8}     ^{#pi}/_{2}     #color[2]{#pi}     #omega^{6}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}     #omega^{6}     ^{#pi}/_{4}    #color[2]{#pi}      #omega^{7}     ^{#pi}/_{2}    #omega^{5}"); 
			sprintf(line5, "1     #color[2]{#pi}      #omega^{8}     #color[2]{#pi}     #omega^{8}     #color[2]{#pi}      #omega^{8}     #color[2]{#pi}"); 
			sprintf(line6, "1     #omega^{5}     ^{#pi}/_{2}     #omega^{7}    #color[2]{#pi}      ^{#pi}/_{4}     #omega^{6}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1     #omega^{6}     #color[2]{#pi}      ^{#pi}/_{2}    #omega^{8}     #omega^{6}     #color[2]{#pi}     ^{#pi}/_{2}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}     #omega^{5}    #color[2]{#pi}     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 13:
			//w5
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     #color[2]{^{5#pi}/_{4}}     #omega^{6}    #omega^{7}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi      #omega^{6}    #omega^{8}     ^{#pi}/_{2}     #pi     #omega^{6}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}     #omega^{6}     ^{#pi}/_{4}    #pi      #omega^{7}     ^{#pi}/_{2}   #color[2]{^{5#pi}/_{4}}"); 
			sprintf(line5, "1     #pi      #omega^{8}     #pi     #omega^{8}     #pi      #omega^{8}     #pi"); 
			sprintf(line6, "1    #color[2]{^{5#pi}/_{4}}     ^{#pi}/_{2}     #omega^{7}    #pi      ^{#pi}/_{4}     #omega^{6}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1     #omega^{6}     #pi      ^{#pi}/_{2}    #omega^{8}     #omega^{6}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1     #omega^{7}     #omega^{6}    #color[2]{^{5#pi}/_{4}}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 14:
			//w6
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    #color[2]{^{3#pi}/_{2}}    #omega^{7}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     #color[2]{^{3#pi}/_{2}}    #omega^{8}     ^{#pi}/_{2}     #pi    #color[2]{^{3#pi}/_{2}}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    #color[2]{^{3#pi}/_{2}}     ^{#pi}/_{4}    #pi      #omega^{7}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi      #omega^{8}     #pi     #omega^{8}     #pi     #omega^{8}     #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}     #omega^{7}    #pi      ^{#pi}/_{4}    #color[2]{^{3#pi}/_{2}}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    #color[2]{^{3#pi}/_{2}}     #pi      ^{#pi}/_{2}    #omega^{8}    #color[2]{^{3#pi}/_{2}}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1     #omega^{7}    #color[2]{^{3#pi}/_{2}}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 15:
			//w7
			sprintf(line1, "1         1           1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   #color[2]{^{7#pi}/_{4}}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}    #omega^{8}     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     #color[2]{^{7#pi}/_{4}}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi      #omega^{8}     #pi     #omega^{8}     #pi      #omega^{8}     #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    #color[2]{^{7#pi}/_{4}}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi      ^{#pi}/_{2}    #omega^{8}    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    #color[2]{^{7#pi}/_{4}}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 16:
			//w8
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}    #color[2]{2#pi}     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     ^{7#pi}/_{4}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi      #color[2]{2#pi}     #pi     #color[2]{2#pi}     #pi      #color[2]{2#pi}     #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}     #color[2]{2#pi}    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 17:
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}    #color[2]{2#pi}     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     ^{7#pi}/_{4}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi      #color[2]{2#pi}     #pi     #color[2]{2#pi}      #pi     #color[2]{2#pi}     #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}     #color[2]{2#pi}    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 18:
			//#color[4]{#pi}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #color[4]{#pi}     ^{5#pi}/_{4}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #color[4]{#pi}     ^{3#pi}/_{2}       2#pi     ^{#pi}/_{2}     #color[4]{#pi}    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #color[4]{#pi}     ^{7#pi}/_{4}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #color[4]{#pi}         2#pi     #color[4]{#pi}         2#pi      #color[4]{#pi}         2#pi    #color[4]{#pi}"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #color[4]{#pi}      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #color[4]{#pi}     ^{#pi}/_{2}        2#pi    ^{3#pi}/_{2}     #color[4]{#pi}     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #color[4]{#pi}     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}"); 
		break;
		case 19:
			//#color[6]{^{#pi}/_{2}}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     #color[6]{^{#pi}/_{2}}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     #color[6]{^{#pi}/_{2}}     #pi     ^{3#pi}/_{2}       2#pi     #color[6]{^{#pi}/_{2}}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     ^{7#pi}/_{4}     #color[6]{^{#pi}/_{2}}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi         2#pi     #pi         2#pi      #pi         2#pi     #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     #color[6]{^{#pi}/_{2}}    ^{7#pi}/_{4}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     #color[6]{^{#pi}/_{2}}        2#pi    ^{3#pi}/_{2}     #pi     #color[6]{^{#pi}/_{2}}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     #color[6]{^{#pi}/_{2}}    ^{#pi}/_{4}");
		break;
		case 20:
			//#color[51]{^{#pi}/_{4}}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     #color[51]{^{#pi}/_{4}}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}       2#pi     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     #color[51]{^{#pi}/_{4}}    #pi     ^{7#pi}/_{4}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi         2#pi     #pi         2#pi      #pi         2#pi    #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #pi      #color[51]{^{#pi}/_{4}}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}        2#pi    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    #color[51]{^{#pi}/_{4}}");
		break;
		case 21:
			//#color[65]{^{3#pi}/_{2}}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    #color[65]{^{3#pi}/_{2}}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     #color[65]{^{3#pi}/_{2}}       2#pi     ^{#pi}/_{2}     #pi    #color[65]{^{3#pi}/_{2}}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    #color[65]{^{3#pi}/_{2}}     ^{#pi}/_{4}    #pi     ^{7#pi}/_{4}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi         2#pi     #pi         2#pi      #pi          2#pi    #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #pi      ^{#pi}/_{4}    #color[65]{^{3#pi}/_{2}}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    #color[65]{^{3#pi}/_{2}}     #pi     ^{#pi}/_{2}        2#pi    #color[65]{^{3#pi}/_{2}}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    #color[65]{^{3#pi}/_{2}}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 22:
			//#color[50]{^{5#pi}/_{4}}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     #color[50]{^{5#pi}/_{4}}    ^{3#pi}/_{2}   ^{7#pi}/_{4}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}       2#pi     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     ^{7#pi}/_{4}     ^{#pi}/_{2}   #color[50]{^{5#pi}/_{4}}"); 
			sprintf(line5, "1     #pi         2#pi     #pi         2#pi      #pi          2#pi    #pi"); 
			sprintf(line6, "1    #color[50]{^{5#pi}/_{4}}     ^{#pi}/_{2}    ^{7#pi}/_{4}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}        2#pi    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    ^{7#pi}/_{4}    ^{3#pi}/_{2}    #color[50]{^{5#pi}/_{4}}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		case 23:
			//#color[97]{^{7#pi}/_{4}}
			sprintf(line1, "1        1            1           1          1           1           1          1");
			sprintf(line2, "1     ^{#pi}/_{4}     ^{#pi}/_{2}    ^{3#pi}/_{4}    #pi     ^{5#pi}/_{4}    ^{3#pi}/_{2}   #color[97]{^{7#pi}/_{4}}"); 
			sprintf(line3, "1     ^{#pi}/_{2}     #pi     ^{3#pi}/_{2}       2#pi     ^{#pi}/_{2}     #pi    ^{3#pi}/_{2}"); 
			sprintf(line4, "1    ^{3#pi}/_{4}    ^{3#pi}/_{2}     ^{#pi}/_{4}    #pi     #color[97]{^{7#pi}/_{4}}     ^{#pi}/_{2}   ^{5#pi}/_{4}"); 
			sprintf(line5, "1     #pi         2#pi     #pi        2#pi      #pi          2#pi    #pi"); 
			sprintf(line6, "1    ^{5#pi}/_{4}     ^{#pi}/_{2}    #color[97]{^{7#pi}/_{4}}    #pi      ^{#pi}/_{4}    ^{3#pi}/_{2}   ^{3#pi}/_{4}"); 
			sprintf(line7, "1    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}        2#pi    ^{3#pi}/_{2}     #pi     ^{#pi}/_{2}"); 
			sprintf(line8, "1    #color[97]{^{7#pi}/_{4}}    ^{3#pi}/_{2}    ^{5#pi}/_{4}    #pi     ^{3#pi}/_{4}     ^{#pi}/_{2}    ^{#pi}/_{4}");
		break;
		/*
		case 24: 
			//Base Matrix
			sprintf(line1, "1          1           1           1          1           1           1          1");
			sprintf(line2, "1           0           i          0          -1          0          -i          0"); 
			sprintf(line3, "1           i          -1         -i           1          i          -1         -i"); 
			sprintf(line4, "1           0          -i          0          -1          0           i          0"); 
			sprintf(line5, "1          -1           1         -1           1         -1           1         -1"); 
			sprintf(line6, "1           0           i          0          -1          0          -i          0"); 
			sprintf(line7, "1          -i          -1          i           1         -i          -1          i"); 
			sprintf(line8, "1           0          -i          0          -1          0           i          0"); 
		break;*/ 
	}

 	
	l1=new TLatex(0.07,0.9,line1);
	l1->SetTextSize(0.08);
	l1->Draw();

	l2=new TLatex(0.07,0.78,line2);
	l2->SetTextSize(0.08);
	l2->Draw();

	l3=new TLatex(0.07,0.66,line3);
	l3->SetTextSize(0.08);
	l3->Draw();

	l4=new TLatex(0.07,0.54,line4);
	l4->SetTextSize(0.08);
	l4->Draw();

	l5=new TLatex(0.07,0.42,line5);
	l5->SetTextSize(0.08);
	l5->Draw();

	l6=new TLatex(0.07,0.3,line6);
	l6->SetTextSize(0.08);
	l6->Draw();

	l7=new TLatex(0.07,0.18,line7);
	l7->SetTextSize(0.08);
	l7->Draw();

	l8=new TLatex(0.07,0.05,line8);
	l8->SetTextSize(0.08);
	l8->Draw();

	fCanvas->Update();
	
	// =================================== MATRIX TEXT Q3 ===========================================
	//GetTextCanvas
	fCanvas->cd(4);
	
	TPTmatrix = new TPaveText(0.03,0.04,0.97,0.2);
	TPTmatrix->SetTextColor(kBlack);
	TPTmatrix->SetTextSize(0.05);
	TPTmatrix->SetFillColor(18);
	TPTmatrix->SetShadowColor(18);
	
		switch(Break){
		case 0: 
			TPTmatrix->AddText("The matrix is of size NxN, in this case 8x8.");
			TPTmatrix->AddText("The first row and column are all #color[2]{1}. The zeros");
			TPTmatrix->AddText("will be replaced by #omega raised to a number.");
		break;
		case 1: 
			TPTmatrix->AddText("For the second column the exponent of #omega goes");
			TPTmatrix->AddText("from #color[2]{1} one by one.");
		break;
		case 2:
			TPTmatrix->AddText("For the third column the exponent of #omega goes from #color[2]{2}");
			TPTmatrix->AddText("Two by two. When it reaches #color[2]{8} it starts again.");   
		break;
		case 3:
			TPTmatrix->AddText("For the fourth column the exponent of #omega goes from #color[2]{3}");
			TPTmatrix->AddText("three by three. When it reaches #color[2]{8} it starts again."); 
		break;
		case 4:
			TPTmatrix->AddText("For the fifth column the exponent of #omega goes from #color[2]{4}");
			TPTmatrix->AddText("four by four. When it reaches #color[2]{8} it starts again.");
		break;
		case 5:
			TPTmatrix->AddText("For the sixth column the exponent of #omega goes from #color[2]{5}");
			TPTmatrix->AddText("five by five. When it reaches #color[2]{8} it starts again.");
		break;
		case 6:
			TPTmatrix->AddText("For the seventh column the exponent of #omega goes from #color[2]{6}");
			TPTmatrix->AddText("six by six. When it reaches #color[2]{8} it starts again.");
		break;
		case 7: 
			TPTmatrix->AddText("For the eighth column the exponent of #omega goes from #color[2]{7}");
			TPTmatrix->AddText("seven by seven. When it reaches #color[2]{8} it starts again.");
		break;
		case 8:
			TPTmatrix->AddText("Here #color[2]{#omega} = exp #left[ #frac{2#pi i}{N} #right] = exp #left[ #frac{2#pi i}{8} #right] = exp #left[ #frac{#pi i}{4} #right].");
		break;
		case 9:
			TPTmatrix->AddText("For #omega^{1} =  exp #left[ #frac{#pi i}{4} #right]^{1} = #color[2]{exp #left[ #frac{#pi i}{4} #right]}.");
		break;
		case 10:
			TPTmatrix->AddText("For #omega^{2} =  exp #left[ #frac{#pi i}{4} #right]^{2} = #color[2]{exp #left[ #frac{#pi i}{2} #right]}.");
		break;
		case 11:
		TPTmatrix->AddText("For #omega^{3} =  exp #left[ #frac{#pi i}{4} #right]^{3} = #color[2]{exp #left[ #frac{3#pi i}{4} #right]}.");
		break;
		case 12: 
			TPTmatrix->AddText("For #omega^{4} =  exp #left[ #frac{#pi i}{4} #right]^{4} = #color[2]{exp #left[ #pi i #right]}.");
		break;
		case 13:
			TPTmatrix->AddText("For #omega^{5} =  exp #left[ #frac{#pi i}{4} #right]^{5} = #color[2]{exp #left[ #frac{5#pi i}{4} #right]}.");
		break;
		case 14:
		TPTmatrix->AddText("For #omega^{6} =  exp #left[ #frac{#pi i}{4} #right]^{6} = #color[2]{exp #left[ #frac{3#pi i}{2} #right]}.");
		break;
		case 15:
			TPTmatrix->AddText("For #omega^{7} =  exp #left[ #frac{#pi i}{4} #right]^{7} = #color[2]{exp #left[ #frac{7#pi i}{4} #right]}.");
		break;
		case 16:
			TPTmatrix->AddText("For #omega^{8} =  exp #left[ #frac{#pi i}{4} #right]^{8} = #color[2]{exp #left[2#pi i #right]}.");
		break;
		case 17:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[2]{exp #left[2#pi i #right]} is not visible since");
			TPTmatrix->AddText("its result multiplies the entire exponential by #color[2]{1}.");
		break;
		case 18:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[4]{exp #left[#pi i #right]} appears #color[4]{3} times. So, multiplying by ");
			TPTmatrix->AddText("#font[12]{N'} in the matrix it appears 12 times.");
		break;
		case 19:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[6]{exp #left[#pi i /2 #right]} appears #color[6]{2} times. So, multiplying by ");
			TPTmatrix->AddText("#font[12]{N'} in the matrix it appears 8 times.");
		break;
		case 20:
			TPTmatrix->AddText("From circuit and mathematics we can see that");
			TPTmatrix->AddText("#color[51]{exp #left[#pi i/4 #right]} appears #color[51]{1} time. So, multiplying by ");
			TPTmatrix->AddText("#font[12]{N'} in the matrix it appears 4 times.");
		break;
		case 21:
			TPTmatrix->AddText("The result of the mathematical addition #color[65]{3#pi i/2}");
			TPTmatrix->AddText("appears #color[65]{2} times, multiplying by #font[12]{N'} in the matrix");
			TPTmatrix->AddText("appears 8 times.");
		break;
		case 22:
			TPTmatrix->AddText("The result of the mathematical addition #color[50]{5#pi i/4}");
			TPTmatrix->AddText("appears #color[50]{1} time, multiplying by #font[12]{N'} in the matrix");
			TPTmatrix->AddText("appears 4 times.");
		break;
		case 23:
			TPTmatrix->AddText("The result of the mathematical addition #color[97]{7#pi i/4}.");
			TPTmatrix->AddText("appears #color[97]{1} time, multiplying by #font[12]{N'} in the matrix");
			TPTmatrix->AddText("appears 4 times.");
		break;
		case 24:
			TPTmatrix->AddText("Each of the #color[2]{exp[#]} expressions is replaced.");
			TPTmatrix->AddText("Final matrix of the Quantum Fourier Transform.");
		break;
	
	}
	
	TPTmatrix->Draw();
	fCanvas->Update();
	gPad->SetEditable(0);
}

//////////////////////////////////////////////////  FUNCION BOTONES ///////////////////////////////////////////////////////////////////
void MyMainFrame::DoStop(){
	fTabGeneral->SetEnabled(1,kTRUE);
	fNQubits->SetEnabled(kTRUE);
	
	fBHadamard->SetState(kButtonUp, kTRUE);
	fBRotation1->SetState(kButtonUp, kTRUE);
	fBRotation2->SetState(kButtonUp, kTRUE);
	fBSwap->SetState(kButtonUp, kTRUE);
	
	fBStart->SetState(kButtonUp, kTRUE);
	fBStop->SetState(kButtonDisabled, kTRUE);
	
	fBNext->SetState(kButtonDisabled, kTRUE);
	fBPrevious->SetState(kButtonDisabled, kTRUE);
	fBRestart->SetState(kButtonDisabled, kTRUE);

   switch(Q){
		case 1:
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->SetEnabled(kFALSE);
			fX2->SetEnabled(kFALSE);
		break;
		case 2:
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->SetEnabled(kTRUE);
			fX1->Connect("Selected(Int_t)","MyMainFrame",this,"Q2State(Int_t)");
			
			fX2->SetEnabled(kFALSE);
		break;
		case 3:
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->SetEnabled(kTRUE);
			fX1->Connect("Selected(Int_t)","MyMainFrame",this,"Q2State(Int_t)");
			
			fX2->SetEnabled(kTRUE);
			fX2->Connect("Selected(Int_t)","MyMainFrame",this,"Q3State(Int_t)");
		break;		
   }
}

void MyMainFrame::DoNext(){
	Break++;
   
	if (Break == 1){
		fBPrevious->SetState(kButtonUp, kTRUE);
		fBRestart->SetState(kButtonUp, kTRUE);
	}
   
	switch(Q){
		case 1:
			if (Break == 4){
				fBNext->SetState(kButtonDisabled, kTRUE);
			}
  
			csDrawQ1();
		break;
		case 2:
			if (Break == 14){
				fBNext->SetState(kButtonDisabled, kTRUE);
			}
			
			csDrawQ2();
		break;
		case 3:
			if (Break == 23){
				fBNext->SetState(kButtonDisabled, kTRUE);
			}

			csDrawQ3();
		break;
	}
}

void MyMainFrame::DoPrevious(){
	Break--;
   
	if (Break == 0){
	fBPrevious->SetState(kButtonDisabled, kTRUE);
	fBRestart->SetState(kButtonDisabled, kTRUE);
	}
	else{
		fBNext->SetState(kButtonUp, kTRUE);
	}
   
	switch(Q){
		case 1:
			csDrawQ1();
		break;
		
		case 2:
			csDrawQ2();
		break;
		case 3:
			csDrawQ3();
		break;
	}   
}

void MyMainFrame::DoRestart(){
	fTabGeneral->SetEnabled(1, kFALSE);
	
	//Variables
	Break=0;
	
	//Estado Botones	
	fNQubits->SetEnabled(kFALSE);
	fX0->SetEnabled(kFALSE);
	fX1->SetEnabled(kFALSE);
	fX2->SetEnabled(kFALSE);
   
	fBStart->SetState(kButtonDisabled, kTRUE);
	fBStop->SetState(kButtonUp, kTRUE);
	
	fBPrevious->SetState(kButtonDisabled, kTRUE);
	fBNext->SetState(kButtonUp, kTRUE);
	fBHelp->SetState(kButtonUp, kTRUE);
   
	switch(Q){
		case 1:
			csDrawQ1();
		break;
		case 2:
			csDrawQ2();
		break;
		case 3:
			csDrawQ3();
		break;
   }
}

void MyMainFrame::DoHelp(){
	fBHelp->SetState(kButtonDisabled, kTRUE);
	DoStop(); 
	
	if (Q==0){
		fBStart->SetState(kButtonDisabled, kTRUE);
	}
	
	//Titulo
	TCanvas *fHelp = fECanvasGen->GetCanvas();
	fHelp->SetEditable(1);
	fHelp->Clear();
	fHelp->SetFillColor(18);
	
	
	TPaveText *TPTTitle = new TPaveText(0.005,0.85,0.99,0.987);
	TPTTitle->SetTextFont(62);
	TPTTitle->SetTextSize(0.04);
	TPTTitle->SetFillColor(0);
	TPTTitle->SetShadowColor(18);
	TPTTitle->SetMargin(0);
	TPTTitle->AddText("#scale[1.2]{QFT#color[2]{Soft}#color[4]{Edu} (QFT Educational Software)}");
	TPTTitle->AddText("#scale[2]{#font[102]{QUANTUM FOURIER TRANSFORM}}");
	TPTTitle->Draw();
	
	//ExplainGUI
	
	TPad *pad1 = new TPad("pad1","This is pad1",0.005,0.005,0.33,0.84);
	TPad *pad2 = new TPad("pad2","This is pad2",0.335,0.005,0.66,0.84);
	TPad *pad3 = new TPad("pad3","This is pad3",0.665,0.005,0.995,0.84);
    pad2->Divide(1,2);
    pad3->Divide(1,2);
    
	pad1->SetFillColor(18);
	pad2->SetFillColor(18);
	pad3->SetFillColor(18);
	
	pad1->Draw();
	pad2->Draw();
	pad3->Draw();
	
	//EXPLICACION GENERAL	
	pad1->cd();
	TPaveText *TPTExplainG = new TPaveText(0,0.01,1,0.99);
	TPTExplainG->SetTextColor(kBlack);
	TPTExplainG->SetTextSize(0.05);
	TPTExplainG->SetFillColor(kYellow-9);
	TPTExplainG->SetShadowColor(18);
	TPTExplainG->SetMargin(0);
	TPTExplainG->SetTextAlign(1);

	TPTExplainG->AddText(" ");
	TPTExplainG->AddText("     #font[22]{#scale[1.4]{GENERAL OPERATION}}");
	TPTExplainG->AddText("   1. To start you need to select the number");
	TPTExplainG->AddText("      of qubits you want to use.");
	TPTExplainG->AddText("   2. Select the state each qubit will be ");
	TPTExplainG->AddText("      in initially.");
	TPTExplainG->AddText("   3. Press#font[12]{Start} to start the explanation.");
	TPTExplainG->AddText("   4. To advance press#font[12]{Next}.");
	TPTExplainG->AddText("   5. To go back press#font[12]{Previous}.");
	TPTExplainG->AddText("   6. To reset press#font[12]{Restart}.");
	TPTExplainG->AddText("   7. To change the number of qubits or the");
	TPTExplainG->AddText("       state of them press#font[12]{Stop}.");
	TPTExplainG->AddText("   8. You can perform these steps as many");
	TPTExplainG->AddText("      times as you need.");
	TPTExplainG->AddText("      ");
	TPTExplainG->AddText("         #font[22]{#scale[1.4]{CONSIDERATIONS}}");
	TPTExplainG->AddText("   1. If you do not have basic knowledge of");
	TPTExplainG->AddText("      quantum gates in QFT press#font[12]{B. Concepts}.");
	TPTExplainG->AddText("      This section will be disabled when you");
	TPTExplainG->AddText("      press#font[12]{Start} and will be enabled");
	TPTExplainG->AddText("      when you press#font[12]{Stop}.");
	TPTExplainG->AddText("   2. To indicate the connected sessions the");
	TPTExplainG->AddText("      title is highlighted in red, in black");
	TPTExplainG->AddText("      they will be independent processes and");
	TPTExplainG->AddText("      gray indicates that the section does");
	TPTExplainG->AddText("      not make any changes.");
	TPTExplainG->AddText("   3. In each section, the modifications made");
	TPTExplainG->AddText("      will be highlighted with color.");
	TPTExplainG->AddText("   4. To exit press#font[12]{Exit}.");

	TPTExplainG->Draw();

	//EXPLICACION MATH
	pad2->cd(1);
	TPaveText *TPTExplainM = new TPaveText(0,0,1,1);
	TPTExplainM->SetTextColor(kBlack);
	TPTExplainM->SetTextSize(0.05);
	TPTExplainM->SetFillColor(kRed-9);
	TPTExplainM->SetMargin(0);
	TPTExplainM->SetTextAlign(1);
	
	TPTExplainM->AddText(" ");
	TPTExplainM->AddText("                   #font[22]{#scale[1.5]{MATH}}");
	TPTExplainM->AddText("  1. The first tensor process will be red, the second");
	TPTExplainM->AddText("      tensor blue and the third tensor green.");
	TPTExplainM->AddText("  2. Getting the result of a tensor will show how");
	TPTExplainM->AddText("     it relates to the different sections.");
	TPTExplainM->AddText("  3. By properties, #font[12]{exp[2n#pii] = 1} (with n as an integer)");
	TPTExplainM->AddText("     and #font[12]{exp[a+b] = e^{a} e^{b}}. Thus, the results of");
	TPTExplainM->AddText("     #font[12]{exp[2n#pii +...]} are rewritten as #font[12]{1*exp[...]}.");
	
	TPTExplainM->Draw();
	
	//EXPLICACION CIRCUIT
	pad2->cd(2);
	TPaveText *TPTExplainC = new TPaveText(0,0,1,1);
	TPTExplainC->SetTextColor(kBlack);
	TPTExplainC->SetTextSize(0.05);
	TPTExplainC->SetFillColor(kGreen-9);
	TPTExplainC->SetMargin(0);
	TPTExplainC->SetTextAlign(1);
	
	TPTExplainC->AddText("                  #font[22]{#scale[1.5]{CIRCUIT}}");
	TPTExplainC->AddText("  1. Quantum gates will be added as indicated");
	TPTExplainC->AddText("     by the mathematical expression.");
	TPTExplainC->AddText("  2. Numerical fractions are not part of the circuit,");
	TPTExplainC->AddText("     but are shown for reference.");
	TPTExplainC->AddText("  3. For the swap gate, the change of colors indicates");
	TPTExplainC->AddText("     that the state of each qubit is exchanged with");
	TPTExplainC->AddText("     each other (see the Bloch Sphere).");
	
	TPTExplainC->Draw();
	
	//EXPLICACION BLOCH
	pad3->cd(1);
	TPaveText *TPTExplainB = new TPaveText(0,0,1,1);
	TPTExplainB->SetTextColor(kBlack);
	TPTExplainB->SetTextSize(0.05);
	TPTExplainB->SetFillColor(kBlue-9);
	TPTExplainB->SetMargin(0);
	TPTExplainB->SetTextAlign(1);
	
	TPTExplainB->AddText(" ");
	TPTExplainB->AddText("             #font[22]{#scale[1.5]{BLOCH SPHERE}}");
	TPTExplainB->AddText("  1. For control gates, the title of the qubit ");
	TPTExplainB->AddText("     on which the operation depends is highlighted,");
	TPTExplainB->AddText("      but it will remain gray indicating that it");
	TPTExplainB->AddText("      did not change.");
	TPTExplainB->AddText("  2. To better observe the Bloch sphere in each");
	TPTExplainB->AddText("     case you can use the following keys");
	TPTExplainB->AddText("  * #font[22]{A:} Increases in size.        *#font[22]{L:} Move it to the right.");
	TPTExplainB->AddText("  * #font[22]{S:} Decreases in size.       *#font[22]{U:} Moves it up.");
	TPTExplainB->AddText("  * #font[22]{H:} Move it to the left.       *#font[22]{I:} Moves it down.");
	
	TPTExplainB->Draw();
	
	//EXPLICACION MATRIX
	pad3->cd(2);
	TPaveText *TPTExplainX = new TPaveText(0,0,1,1);
	TPTExplainX->SetTextColor(kBlack);
	TPTExplainX->SetTextSize(0.05);
	TPTExplainX->SetFillColor(kMagenta-9);
	TPTExplainX->SetMargin(0);
	TPTExplainX->SetTextAlign(1);
	
	TPTExplainX->AddText("                  #font[22]{#scale[1.5]{MATRIX}}");
	TPTExplainX->AddText("  1. In each case#omega is an exponential raised to a");
	TPTExplainX->AddText("     power of the form #font[12]{exp[##pii]}. For practical");
	TPTExplainX->AddText("     purposesonly only the fraction#font[12]{#} was left");
	TPTExplainX->AddText("     in the matrix.");
	TPTExplainX->AddText("  2. The final matrix is the one that will be ");
	TPTExplainX->AddText("     multiplied by the ket of the state of the system.");
	
	TPTExplainX->Draw();
	
	fHelp->Update();
	fHelp->SetEditable(0);
}

///////////////////////////////////////////////////  SET QFT STATE ////////////////////////////////////////////////////////////////////

void MyMainFrame::SelectQState(Int_t Qubits){  
	Q = Qubits;
	QFState();
	
	switch(Q){
		case 1:
			fLNVal->ChangeText("2");
			fLNValPrim->ChangeText("1");
			
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->Select(0);
			fX1->SetEnabled(kFALSE);
			fX2->Select(0);
			fX2->SetEnabled(kFALSE);
			
			
		break;
		case 2:
			fLNVal->SetText("4");
			fLNValPrim->SetText("2");
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->SetEnabled(kTRUE);
			fX1->Connect("Selected(Int_t)","MyMainFrame",this,"Q2State(Int_t)");
			
			fX2->Select(0);
			fX2->SetEnabled(kFALSE);
		break;
		case 3:
			fLNVal->SetText("8");
			fLNValPrim->SetText("4");
			fX0->SetEnabled(kTRUE);
			fX0->Connect("Selected(Int_t)","MyMainFrame",this,"Q1State(Int_t)");
			
			fX1->SetEnabled(kTRUE);
			fX1->Connect("Selected(Int_t)","MyMainFrame",this,"Q2State(Int_t)");
			
			fX2->SetEnabled(kTRUE);
			fX2->Connect("Selected(Int_t)","MyMainFrame",this,"Q3State(Int_t)");
		break;		
	}
	
	fGVariables->AddFrame(fLNVal, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fLNVal->MoveResize(140,79,30,32);
	
	fGVariables->AddFrame(fLNValPrim, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fLNValPrim->MoveResize(140,129,30,32);
}

void MyMainFrame::QFState(){ 
	switch(XF){
		case 0:
			fLNQubitsVal->SetText("0");
		break;
		case 1:
			fLNQubitsVal->SetText("1");
		break;
		case 2:
			fLNQubitsVal->SetText("2");
		break;
		case 3:
			fLNQubitsVal->SetText("3");
		break;
		case 4:
			fLNQubitsVal->SetText("4");
		break;
		case 5:
			fLNQubitsVal->SetText("5");
		break;
		case 6:
			fLNQubitsVal->SetText("6");
		break;
		case 7:
			fLNQubitsVal->SetText("7");
		break;
	}
	
	fGVariables->AddFrame(fLNQubitsVal, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
	fLNQubitsVal->MoveResize(140,322,30,32);	
	
	fBStart->SetState(kButtonUp, kTRUE);
}

void MyMainFrame::Q1State(Int_t q1){  
	X0=q1;
	
	if(X0==0){
		Q1=0;
	}
	if(X0==1){
		Q1=1;
	}	
	
	XF=Q1+Q2+Q3;
	QFState();		
}

void MyMainFrame::Q2State(Int_t q2){  
	X1=q2;
	
	if(X1==0){
		Q2=0;
	}
	if(X1==1){
		Q2=2;
	}
	
	XF=Q1+Q2+Q3;
	QFState();
}

void MyMainFrame::Q3State(Int_t q3){  
	X2=q3;
	
	if(X2==0){
		Q3=0;
	}
	if(X2==1){
		Q3=4;
	}
	
	XF=Q1+Q2+Q3;
	QFState();
}

///////////////////////////////////////////////////  DESTRUCTOR ////////////////////////////////////////////////////////////////////
MyMainFrame::~MyMainFrame() {
	fMain->Cleanup();
	delete fMain;
}

///////////////////////////////////////////////////  MAIN ///////////////////////////////////////////////////////////////////////////
void SEQFT() {
	new MyMainFrame(gClient->GetRoot(),1100,700);
}

int main(int argc, char **argv) {
   TApplication theApp("App",&argc,argv);
   SEQFT();
   theApp.Run();
   return 0;
}
