/////////////////////////////////////////////////////////
//
// This file is part of the MADELINE 2 program 
// written by Edward H. Trager, Ritu Khanna and Adrian Marrs
// Copyright (c) 2005 by the
// Regents of the University of Michigan.
// All Rights Reserved.
// 
// The latest version of this program is available from:
// 
//   http://eyegene.ophthy.med.umich.edu/madeline/
//   
// Released under the GNU General Public License.
// A copy of the GPL is included in the distribution
// package of this software, or see:
// 
//   http://www.gnu.org/copyleft/
//   
// ... for licensing details.
// 
/////////////////////////////////////////////////////////
//
// 2006.03.01.RK.
// 2016.01.07.ET: Revised
// 2016.02.03.ET: Revised

//
// DrawingCanvas.h
//
// -- Contains SVG methods used for drawing and graphing
// 
#ifndef DrawingCanvas_INCLUDED
#define DrawingCanvas_INCLUDED

#include <sstream>
#include <fstream>
#include <iostream>
#include "DrawingMetrics.h"
#include "Individual.h"
#include "LabelSet.h"
#include "LabelLegend.h"
#include "IconLegend.h"
#include "SVG.h"
//#include "Utility.h"

#include "DrawingLabelManager.h"

class DrawingCanvas{
	
private:
	std::ostringstream _header;
	std::ostringstream _body;
	std::ostringstream _footer;
	std::ostringstream _layer;
	std::ostringstream _bottomLayer; // For curved connectors ...
	
	bool _layerFlag;
	DrawingMedia _media;
	const LabelSet * _labelSet;
	bool _iconLegendFlag;
	
	//
	// For font metrics and postscript:
	//
	LASiWrapper _lasiWrapper;
	
	//
	// DrawingLabelManager:
	//
	DrawingLabelManager _labelManager;
	LabelLegend _labelLegend;
	IconLegend  _iconLegend;
	SVG _svg;
	void _setHeader();
	void _setFooter();
	
	//
	// _setCSS() and _setJavascript()
	// are used privately by _setHeader():
	// 
	void _setJavascript();
	void _setCSS();
	void _setSVGDefinitions();
	
	std::vector< std::string > _layers;
	
	//
	// ColorSeries: 
	//
	//std::vector<ColorSeries> *pColorSeriesVector=0;
	
	//
	// 2006.09.05.ET ADDENDUM:
	// Keep track of minimum and maximum x and y
	// so that we know true dimensions:
	double _xMinimum;
	double _xMaximum;
	double _yMinimum;
	double _yMaximum;
	
	void _trackMinimaAndMaxima(double x,double y);
	void _drawDeceasedLine(double x,double y);
	void _drawProbandArrow(double x,double y);
	void _drawConsultandArrow(double x, double y);
	void _drawNorthEastArrow(double x, double y, double scale);
	void _drawLegends(void);
	void _drawSampledIndicator(double x, double y);
	void _drawSuperScript(const std::string &label,double x, double y);
	
public:
	//
	// Constructor
	//
	DrawingCanvas(const LabelSet * labelSet,const std::string name);
	
	//
	// Media methods:
	//
	void setDrawingMedia(std::string name);
	double getWidth(); // gets the media width
	double getHeight(); // gets the media height
	
	//
	// Layer Methods:
	// 
	void startLayer();
	void endLayer();
	
	
	// Drawing Methods:
	void startGroup(const std::string& cssClass=std::string(""));
	void endGroup();
	void drawTitle(const std::string title);
	void drawLine(double x1,double y1,double x2,double y2);
	void drawHorizontalLine(double y,double x1,double x2);
	void drawHorizontalDoubleLine(double y,double x1,double x2,char startMiter='|',char endMiter='|');
	void drawVerticalLine(double x,double y1,double y2,const std::string & className=std::string(""), const std::string & id=std::string(""));
	void drawVerticalDoubleLine(double x,double y1,double y2,char startMiter='-',char endMiter='-');
	void drawPolyline(const std::string points,const std::string& id=std::string(""),const std::string& myclass=std::string(""));
	void drawText(double x,double y,std::string text,std::string  myclass="",std::string id="");
	void drawIconText(double x,double y,std::string text,std::string  myclass="");
	void drawRectangle(double x,double y,double width,double height);
	
	void drawIndividual(Individual* pIndividual,double x,double y,bool isDashed=false);
	
	// 2009.05.11.ET ADDENDUM:
	void drawDivorcedLine(double x,double y);
	void drawSeparatedLine(double x,double y);
	void drawRelationshipEndedLine(double x,double y);
	
	void drawLabelSet(Individual* pIndividual);
	void drawSuperscriptData(Individual *pIndividual,double x, double y);
	void drawEncircledText(std::string text,double x,double y,double xradius, double yradius,const std::string& myclass=std::string(""));
	std::string show(const char* filename);
	
	// Getters:
	double getXMinimum();
	double getYMinimum();
	double getXMaximum();
	double getYMaximum();
	double getXRange();
	double getYRange();
	
	void arc( double x, double y, double r, double startAngle, double endAngle,const std::string &color,const std::string &arcLabel,const std::string &arcClass,bool isMale);
	void setClipPath(double x, double y, const std::string &id);
	void setDiamondClipPath(double x, double y, const std::string &id);
	void iconPie( double x, double y, Individual *pIndividual );
	void iconQuadrantFill( double x, double y, Individual *pIndividual );
	
	//
	// 2014.07.08.ET Addendum: useWhiteInk()
	//
	bool useWhiteInk(Individual *pIndividual);
	
	// 2016.01.07.ET Addenda to support Assisted Reproductive Technologies:
	void drawUterusSymbol(double x,double y);
	void drawSpermSymbol(double x,double y,bool facingLeft=false);
	void drawOvumSymbol(double x,double y);
	void drawEntwinedRingsSymbol(double x,double y);
	void drawMitochondrialSymbol(double x,double y);

	static bool saveFlag;
};

#endif
