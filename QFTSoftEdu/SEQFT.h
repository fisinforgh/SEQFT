/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// NOTICE OF COPYRIGHT                                                         //
//                                                                             //
// Copyright (C) 2023                                                          //
//                                                                             //
// Authors:								                                       //
//   [1] Ingrid Daiana Cuevas Ruiz*						                       //
//   [2] Julian Andrés Salamanca Bernal**                                      //
//   [3] Diego Julián Rodríguez-Patarroyo***				                   //         			           
//                                                                             //
//   [1] idcuevasr@udistrital.edu.co (Licenciada Universidad Distrital)        //
//   [2] jasalamanca@udistrital.edu.co (profesor Universidad Distrital)        //
//   [3] djrodriguezp@udistrital.edu.co (profesor Universidad Distrital)       //
//									                                           //
//  *,** Grupo de Física e Informática (FISINFOR)		                       //
//  *** Grupo de Laboratorio de Fuentes Alternas de Energía (LIFAE)	           //
//  *,**,*** Universidad Distrital Francisco José de Caldas (Bogotá, Colombia) //	
//                                                                             //
// Web page:								                                   //
//   https://github.com/fisinforgh/SEQFT/tree/main/QFTSoftEdu                  //
//                                                                             //
// This program is free software; you can redistribute it and/or modify        //
// it under the terms of the GNU General Public License as published by        //
// the Free Software Foundation; either version 2 of the License, or           //
// (at your option) any later version.                                         //
//                                                                             //
// This program is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of              //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               //
// GNU General Public License for more details:                                //
//                                                                             //
//               http://www.gnu.org/copyleft/gpl.html                          //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <TQObject.h>
#include <RQ_OBJECT.h>

class TGWindow;
class TGMainFrame;
class TRootEmbeddedCanvas;
class TGComboBox;
class TGButton;
class TGLabel;
class TGTab;
class TRootEmbeddedCanvas;
class TCanvas;
class TLine;
class TLatex;
class TGTextButton;
class TGCompositeFrame;
class TGGroupFrame;
class TPaveText;
class TGHorizontalFrame;
class TGVerticalFrame;
class TPave;
class TMarker;
class TGeoManager;

/////////////////////////////////////////////////////// MAIN CLASS  /////////////////////////////////////////////////////////////////
class MyMainFrame {
	RQ_OBJECT("MyMainFrame")

	private:
		//Desing
		TGMainFrame         *fMain;
		TRootEmbeddedCanvas *fECanvasstate;
		TRootEmbeddedCanvas *fECanvasExp;
		TGCompositeFrame    *fTabQFT;
		TGCompositeFrame    *fTabBC;
		TGTab               *fTabGeneral;
		TGGroupFrame        *fGVariables;
		TCanvas             *fCanvastxt;
		TGTextButton        *fBExit;
		TGTextButton        *fBNext;
		TGTextButton        *fBPrevious; 
		TGTextButton        *fBRestart;
		TGTextButton        *fBHelp;
		TGTextButton        *fBStart;
		TGTextButton        *fBStop;
		TGTextButton        *fBHadamard;
		TGTextButton        *fBQubit;
		TGTextButton        *fBRotation1;
		TGTextButton        *fBRotation2;
		TGTextButton        *fBSwap;
		TGComboBox          *fNQubits;  
		TGComboBox          *fX0;
		TGComboBox          *fX1;
		TGComboBox          *fX2;
		TPaveText           *TPTmath;
		TPaveText           *TPTcircuit;
		TPaveText           *TPTbloch;
		TPaveText           *TPTmatrix;
		TGLabel             *fLNVal;
		TGLabel             *fLNValPrim;
		TGLabel             *fLNQubitsVal; 
		TGHorizontalFrame   *hframe03;
		TGVerticalFrame     *vframe;
		Int_t               Break=0;
		Int_t               Q=0;
		Int_t               X0=0;
		Int_t               X1=0;
		Int_t               X2=0;
		Int_t               Q1=0;
		Int_t               Q2=0;
		Int_t               Q3=0;
		Int_t               XF=0;
		
		//QFT 
		TLatex              *l1;
		TLatex              *l2;
		TLatex              *l3;
		TLatex              *l4;
		TLatex              *l5;
		TLatex              *l6;
		TLatex              *l7;
		TLatex              *l8;
		TLatex              *l9;
		TLatex              *l10;
		TLatex              *l11;
		TLatex              *l12;
		TLatex              *l13;
		TLatex              *l14;
		TLatex              *l15;  
		TLatex              *name1;
		TLatex              *name3;
		TLatex              *name;
		TPave               *Square;
		TMarker             *circle;
		TLatex              *x;
		TLatex              *Rot;
		TLine               *line;
		char                line1[300];
		char                line2[300];
		char                line3[300];
		char                line4[300];
		char                line5[300];
		char                line6[300];
		char                line7[300];
		char                line8[300];
		
		//Para Iconos
		TString pathDIR_ICONS;
		
	public:
		MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
		virtual ~MyMainFrame();

		//FUNCIONES PRINCIPALES
		void DoHelp();
		void DoWelcome();

		//SET QUBIT STATE
		void SelectQState(Int_t);
		void Q1State(Int_t);
		void Q2State(Int_t);
		void Q3State(Int_t);
		void QFState();
		
		//CONTROL QFT
		void DoPrevious();
		void DoNext();
		void DoRestart();
		void DoStop();
		
		//CONCEPTS
		void DoHadamard();
		void DoRotation1();
		void DoRotation2();
		void DoSwap();

		//QFT SIMULATION
		void csDrawQ1();
		void csDrawQ2();
		void csDrawQ3();
};
