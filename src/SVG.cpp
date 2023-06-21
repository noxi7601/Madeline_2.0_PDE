/////////////////////////////////////////////////////////
//
// This file is part of the MADELINE 2 program 
// written by Edward H. Trager and Ritu Khanna
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
// 2006.12.29.RK
//
// Last updated 2015.12.14.ET
//

//
// SVG.cpp
//

#include "SVG.h"

//
// drawLine:
//
void SVG::drawLine(std::ostringstream& os, double x1,double y1,double x2,double y2,const std::string& cssClass,const std::string& id){
	
	os  << "  <line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	
}

//
// drawHorizontalLine:
//
void SVG::drawHorizontalLine(std::ostringstream& os,double y, double x1, double x2,const std::string& cssClass,const std::string& id){
	
	 os << "  <line x1=\"" << x1 << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y << "\" />\n";
	
}

//
// drawVerticalLine:
//
void SVG::drawVerticalLine(std::ostringstream& os,double x, double y1, double y2,const std::string & cssClass, const std::string & id){
	
	os << "  <line ";
	if(cssClass != std::string("") ) os << "class=\"" << cssClass <<"\" ";
	if(id        != std::string("") ) os << "id=\""    << id    <<"\" ";
	os << "x1=\"" << x << "\" y1=\"" << y1 << "\" x2=\"" << x << "\" y2=\"" << y2 << "\" />\n";
	
}

//
// drawPolyline:
//
void SVG::drawPolyline(std::ostringstream& os,const std::string points,const std::string& cssClass,const std::string& id){
	
	os << "  <polyline points=\"" << points << "\" ";
	if(id        != std::string("") ) os << "id=\""    << id    <<"\" ";
	if(cssClass     != std::string("") ) os << "class=\""    << cssClass    <<"\" ";
	os << " />\n";
	
}

//
// drawText:
//
void SVG::drawText(std::ostringstream& os,double x,double y,std::string text,const std::string& cssClass,const std::string& id){
	
	os << "  <text x=\"" << x << "\" y=\"" << y << "\" text-anchor=\"middle\" ";
	if(cssClass!="") os << " class=\"" << cssClass << "\" ";
	if(id!="") os << " id=\"" << id << "\" ";
	os << ">" << text << "</text>\n";
	
}

//
// drawRectangle:
//
void SVG::drawRectangle(std::ostringstream& os,double x,double y,double width,double height,const std::string& cssClass,const std::string& id,const std::string& style){
	
	os  << "  <rect  x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" ";
	if(style != std::string("")) os << "style=\"" << style << "\" ";
	if(cssClass != std::string("")) os << "class=\"" << cssClass << "\" ";
	os << " />\n";
	
}

//
// startGroup:
//
void SVG::startGroup(std::ostringstream& os,const std::string& cssClass,const std::string& id){
	
	os << "  <g"; 
	if(cssClass!=std::string("")) os << " class=\"" << cssClass << "\"";
	os << ">\n";
	
}

//
// endGroup:
//
void SVG::endGroup(std::ostringstream& os){
	
	os << "  </g>\n";
	
}

//
// drawMaleIcon()
//
void SVG::drawMaleIcon(std::ostringstream& os,double x, double y, const std::string &id, const std::string &cssClass){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	x -= r;
	y -= r;
	os << "  <rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << d << "\" height=\"" << d << "\"";
	if(id.size()   ) os << " id=\"" << id << "\"";
	if(cssClass.size()) os << " class=\"" << cssClass << "\"";
	
	if(id.size()){
		os << ">\n";
		os << "\t<title>" << id << "</title>\n";
		os << "</rect>\n";
	}else{
		
		os << "/>\n";
		
	}
	
}

//
// drawMaleIconEdge
//
void SVG::drawMaleIconEdge(std::ostringstream& os,double x, double y){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	double edgeOffset=DrawingMetrics::getScalingFactor();
	x += r;
	y -= r;
	y += edgeOffset;
	double x2 = x + edgeOffset;
	double y2 = y;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	y2 += d;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	x2 -= d;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	y2 -= edgeOffset;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	
}


//
// drawFemaleIcon()
//
void SVG::drawFemaleIcon(std::ostringstream& os,double x, double y, const std::string &id, const std::string &cssClass){
	
	os << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << DrawingMetrics::getIconRadius() << "\"";
	if(id.size()   ) os << " id=\"" << id << "\"";
	if(cssClass.size()) os << " class=\"" << cssClass << "\"";
	
	if(id.size()){
		os << ">\n";
		os << "\t<title>" << id << "</title>\n";
		os << "</circle>\n";
	}else{
		
		os << "/>\n";
		
	}
	
}

//
// drawFemaleIconEdge()
//
void SVG::drawFemaleIconEdge(std::ostringstream& os,double x, double y){
	
	os << "<g transform=\"translate(" << x << "," << y << ") scale(0.50)\">" << std::endl;
	os << " <path ";
	os << " style=\"fill:none;stroke:#000000;stroke-width:3.77999997\" ";
	os << " d=\""; 
	os << " m -12.875,18.65625 c 4.0926449,5.918156 10.9162147,9.8125 18.65625,9.8125 12.525818,0 22.6875,-10.161682 22.6875,-22.6875 0,-7.7400353 -3.894344,-14.5636051 -9.8125,-18.65625\"";
	os << " />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawGenderUnknownIcon()
//
void SVG::drawGenderUnknownIcon(std::ostringstream& os,double x, double y, const std::string &id, const std::string &cssClass){
	
	double r = DrawingMetrics::getIconRadius();
	double d = 2.0 * r / M_SQRT2;
	y -= r;
	os << "<path d=\"M " << x << " " << y;
	os << " l " << -d << " " << d;
	os << " " << d << " " << d;
	os << " " << d << " " << -d;
	os << " z\"";
	if(id.size()   ) os << " id=\"" << id << "\"";
	if(cssClass.size()) os << " class=\"" << cssClass << "\"";
	
	if(id.size()){
		os << ">\n";
		os << "\t<title>" << id << "</title>\n";
		os << "</path>\n";
	}else{
		
		os << "/>\n";
		
	}
	
}

//
// drawGenderUnknownIconEdge
//
void SVG::drawGenderUnknownIconEdge(std::ostringstream& os,double x, double y){
	
	double c          = DrawingMetrics::getIconDiameter();
	double d          = c / M_SQRT2;
	double r          = DrawingMetrics::getIconRadius() / M_SQRT2;
	double offset     = 0.5 * DrawingMetrics::getScalingFactor();
	double edgeOffset = offset / M_SQRT2;
	y -= d;
	y -= 1.72*offset;
	x += 2*offset;
	double x2 = x + edgeOffset;
	double y2 = y - edgeOffset;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	x2 += d;
	y2 += d;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	x2 -= d;
	y2 += d;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	x  =  x2;
	y  =  y2;
	x2 -= edgeOffset;
	y2 -= edgeOffset;
	os  << "  <line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	
}

//
// drawIconForNoChildren()
//
void SVG::drawIconForNoChildren(std::ostringstream& os,double x, double y){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	x -= r;
	y -= r;
	double x2 = x+d;
	
	os << "<line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y << "\" class=\"solid\" />\n";
	
}

//
// drawIconForInfertility()
//
void SVG::drawIconForInfertility(std::ostringstream& os,double x, double y){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	x -= r;
	y -= r;
	double x2 = x+d;
	
	os << "<line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y << "\" class=\"solid\" />\n";
	// Create 2nd line:
	y+= 1.0*DrawingMetrics::getScalingFactor();
	os << "<line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y << "\" class=\"solid\" />\n";
	
}

//
// drawIconForAbortedPregnancy
// 
void SVG::drawIconForAbortedPregnancy(std::ostringstream& os,double x, double y, const std::string &id, const std::string &cssClass){
	
	double r = DrawingMetrics::getIconRadius();
	y -= r;
	r*=M_SQRT2;
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " << -r << " " << r;
	os << " " << 2.0*r << " " << 0;
	os << " z\"";
	if(id.size()   ) os << " id=\"" << id << "\"";
	if(cssClass.size()) os << " class=\"" << cssClass << "\"";
	
	if(id.size()){
		os << ">\n";
		os << "\t<title>" << id << "</title>\n";
		os << "</path>\n";
	}else{
		
		os << "/>\n";
		
	}
	
}

//
// drawAdoptedIn: - Draws brackets around an individual like this: [ ]
//                - Conforms to PSTF (Bennet et al.)
//
void SVG::drawAdoptedIn(std::ostringstream& os,double x,double y,bool widerMargin){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	double t = DrawingMetrics::getVerticalTick();
	double v = d+t+t;
	
	x -= r;
	if(widerMargin) x -= 2*t;
	y -= r;
	y -= t;
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " << -t << " " << 0;
	os << " "   <<  0 << " " << v;
	os << " "   <<  t << " " << 0;
	os << "\" class=\"solid\" />\n";
	
	x += d;
	if(widerMargin) x += 4*t;
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " <<  t << " " << 0;
	os << " "   <<  0 << " " << v;
	os << " "   << -t << " " << 0;
	os << "\" class=\"solid\" />\n";
	
}

//
// drawAdoptedOut: - Draws brackets around an individual like this: ] [
//                 - This is intentionally different from the PSTF
//                   (Bennet et al.) recommendations.
//
void SVG::drawAdoptedOut(std::ostringstream& os,double x,double y,bool widerMargin){
	
	double d = DrawingMetrics::getIconDiameter();
	double r = 0.5 * d;
	double t = DrawingMetrics::getVerticalTick();
	double v = d+2*t;
	
	x -= r;
	x -= 2*t;
	if(widerMargin) x -= 2*t;
	
	y -= r;
	y -= t;
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " <<  t << " " << 0;
	os << " "   <<  0 << " " << v;
	os << " "   <<  -t << " " << 0;
	os << "\" class=\"solid\" />\n";
	
	x += d;
	x += 4*t;
	if(widerMargin) x += 4*t;
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " << -t << " " << 0;
	os << " "   <<  0 << " " << v;
	os << " "   <<  t << " " << 0;
	os << "\"  class=\"solid\" />\n";
	
}

//
// drawMiniMaleIcon: - Draws a miniature-sized male icon
//                     to indicate gender of terminated or aborted pregnancies
//                     - Not part of PSTF recommendation
//
void SVG::drawMiniMaleIcon(std::ostringstream& os,double x,double y){
	
	double r  = DrawingMetrics::getIconRadius();
	double hr = 0.5*r;
	
	x -= hr;
	y += hr;
	y += DrawingMetrics::getVerticalTick();
	
	os << "<path d=\"M " << x << " " << y;
	os << " l " <<  0 << " " << r;
	os << " "   <<  r << " " << 0;
	os << " "   <<  0 << " " << -r;
	os << " z ";
	os << "\" class=\"solid\" />\n";
	
}

//
// drawMiniFemaleIcon: - Draws a miniature-sized female icon
//                       to indicate gender of terminated or aborted pregnancies
//                     - Not part of PSTF recommendation
//
void SVG::drawMiniFemaleIcon(std::ostringstream& os,double x,double y){
	
	double r  = DrawingMetrics::getIconRadius();
	double hr = 0.5*r;
	
	y += r;
	y += DrawingMetrics::getVerticalTick();
	
	os << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << hr << "\"";
	os << " class=\"solid\" />\n";
	
}

//
// drawMiniCircle: - Draws a small filled circle indicating carrier status
//
void SVG::drawMiniCircle(std::ostringstream& os,double x,double y){
	
	double r  = DrawingMetrics::getIconRadius();
	double hr = 0.40*r;
	
	os << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << hr << "\"";
	os << " class=\"filled\" />\n";
	
}

//
// drawMiniOpenCircle: - Draws a small filled circle indicating obligate carrier status
//
void SVG::drawMiniOpenCircle(std::ostringstream& os,double x,double y){
	
	double r  = DrawingMetrics::getIconRadius();
	double hr = 0.40*r;
	
	os << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << hr << "\"";
	os << " class=\"solid\" />\n";
	
}

//
// drawHeart
//
void SVG::drawHeart(std::ostringstream& os,double x,double y){
	
	double  sc=4;
	std::string sp=" ";
	
	y+=7;
	
	os << "<path class=\"specialIcons\"";
	os << " d=\"M" << x << sp << y << sp;
	os << "c" << -0.7*sc << sp << -0.3*sc << sp <<   -2*sc << sp << -1.5*sc << sp << -2*sc << sp << -2.5*sc << sp;
	os << "c" <<    0*sc << sp << -0.5*sc << sp <<  0.5*sc << sp <<   -1*sc << sp <<  1*sc << sp <<   -1*sc << sp;
	os << "c" <<  0.5*sc << sp <<    0*sc << sp <<    1*sc << sp <<  0.4*sc << sp <<  1*sc << sp <<    1*sc << sp;
	os << "c" <<    0*sc << sp << -0.6*sc << sp <<  0.5*sc << sp <<   -1*sc << sp <<  1*sc << sp <<   -1*sc << sp;
	os << "c" <<  0.5*sc << sp <<    0*sc << sp <<    1*sc << sp <<  0.5*sc << sp <<  1*sc << sp <<    1*sc << sp;
	os << "c" <<    0*sc << sp <<    1*sc << sp << -1.3*sc << sp <<  2.2*sc << sp << -2*sc << sp <<  2.5*sc << sp;
	os << "z\" />\n";

}

//
// drawSquiggle
//
void SVG::drawSquiggle(std::ostringstream& os,double x,double y){
	
	double sc=1.25;
	std::string sp=" ";
	
	x-=10;
	y+=14;
	
	os << "<path class=\"specialLines\"";
	os << " d=\"M" << x << sp << y << sp;
	for(int i=0;i<4;i++){
		os << "c" <<  1.25*sc << sp <<   -1.25*sc << sp << -1.25*sc << sp << -3.75*sc << sp << 0*sc << sp << -5*sc << sp;
		os << "c" <<  1.25*sc << sp <<   -1.25*sc << sp <<  3.75*sc << sp <<  1.25*sc << sp << 5*sc << sp <<  0*sc << sp;
	}
	os << "\" />\n";
	
}


//
// drawCurve -- For showing curved connectors in the background -- NEEDS WORK !
// 2009.05.21.ET ADDENDUM
//
// dxc, dyc specify a *relative* offset from the first end point.  The
// second control point will then be a symmetric reflected control point from the
// second end point.
//
void SVG::drawCurve(std::ostringstream& os, double x1, double y1, double x2, double y2){
	
	//if(x2<x1){
	//	double xx = x1;
	//	x1=x2;
	//	x2=xx;
	//}
	
	//if(y2<y1){
	//	double yy = y1;
	//	y1=y2;
	//	y2=yy;
	//}
	
	std::string sp=" ";
	
	double dx = x2-x1;
	double dy = y2-y1;
	
	double h = sqrt(dx*dx + dy*dy);
	
	//
	// Calculate relative displacement for
	// control points dxc, dyc:
	//
	double dxc = 0.25*h;   // a quarter of distance h seems about right ...
	double dyc = 5*DrawingMetrics::getIconDiameter(); // This just seems about right ...
	
	
	// Control point #1 (when p1 is translated to the origin):
	double c1x = (dxc*dx-dyc*dy)/h;
	double c1y = (dxc*dy+dyc*dx)/h;
	
	// Translate:
	c1x += x1; 
	c1y += y1;
	
	// Control point #2 (when p1 is translated to the origin):
	double c2x = ((h-dxc)*dx-dyc*dy)/h;
	double c2y = ((h-dxc)*dy+dyc*dx)/h;
	
	// Translate:
	c2x += x1; 
	c2y += y1;
	
	os << "<path class=\"curvedConnector\"";
	os << " d=\"M" << x1 << sp << y1 << sp;
	os << "C" <<  c1x << sp << c1y << sp << c2x << sp << c2y << sp << x2 << sp << y2 << sp;
	os << "\" />\n";
	
} 
//
// drawPregnancyLetterP
//
// Double-struck P to indicate a pregnancy
//
void SVG::drawPregnancyLetterP(std::ostringstream& os,double x,double y,const std::string & inkClass){  
	
	// move to x-y position:
	os << "<path class=\"" << inkClass << "\" d=\"M " << x << " " << y;
	// double-struck letter P instructions:
	os << " m 6.73,-3.3 c -2e-5,1.3071 -0.59766,2.3137 -1.79294,3.0197 -0.99258,0.5801 -2.19136,0.8702 -3.59634,0.8702 -0.0979,0 -0.24815,0 -0.45086001,-0.01 -0.20271,-0.01 -0.353,-0.011 -0.45085,-0.011 -0.0979,0 -0.29708003,0 -0.59764003,0.011 l 0,4.3827 c -1e-5,0.5452 0.11533,0.8808 0.346,1.0066 0.13979,0.077 0.51376003,0.1153 1.12189004,0.1153 0.23765,0 0.35648,0.1258 0.35649,0.3775 -1e-5,0.2726 -0.11884,0.4089 -0.35649,0.4089 l -6.19662,0 c -0.23766,0 -0.35649,-0.1363 -0.35649,-0.4089 0,-0.2517 0.1398,-0.3775 0.4194,-0.3775 0.58716,0 0.94365,-0.056 1.06947,-0.1677 0.13281,-0.1189 0.19921,-0.4509 0.19921,-0.9961 l 0,-10.2229 c 0,-0.4962 -0.0629,-0.8073 -0.18873,-0.9331 -0.12582,-0.1258 -0.45435,-0.1887 -0.98558,-0.1888 -0.34251,10e-5 -0.51377,-0.1328 -0.51377,-0.3984 0,-0.2586 0.11883,-0.3879 0.35649,-0.3879 l 6.24905,0 c 1.49585,0 2.70861,0.2726 3.63828,0.8178 1.15334,0.6711 1.73001,1.7021 1.73003,3.0931 m -0.78638,0 c -10e-6,-1.5308 -0.87376,-2.5024 -2.62124,-2.9149 0.4124,0.5523 0.6186,1.5239 0.61861,2.9149 -1e-5,1.3001 -0.22019,2.2542 -0.66055,2.8624 1.77544,-0.4823 2.66317,-1.4365 2.66318,-2.8624 m -2.789,0 c -1e-5,-1.0555 -0.10486,-1.7895 -0.31455,-2.2019 -0.30757,-0.6151 -0.93667,-0.9226 -1.88730001,-0.9227 -0.27261,10e-5 -0.51377,0.063 -0.72346003,0.1888 -0.25863,0.1468 -0.38795,0.346 -0.38794,0.5976 l 0,5.4312 1.10092003,0 c 0.90869001,0 1.53080001,-0.318 1.86632001,-0.9541 0.23066,-0.4473 0.346,-1.1603 0.34601,-2.1389 m -3.85847001,-3.1246 -2.23329999,0 c 0.11183,0.2657 0.16775,0.6396 0.16776,1.1219 l 0,10.2229 c -1e-5,0.5033 -0.0524,0.8912 -0.15728,1.1638 l 2.18087999,0 c -0.13282,-0.2726 -0.19921999,-0.6466 -0.19921999,-1.1219 l 0,-10.6003 c 0,-0.2935 0.0804,-0.5557 0.24115999,-0.7864 \"/>" << std::endl;
	
}

//
// drawCollapsedCount
//
// Draw large, centered numerals indicating the number of individuals who have been "collapsed" into one symbol:
//
void SVG::drawCollapsedCount(std::ostringstream& os,double x,double y,unsigned collapsedCount){
	
	static bool filterDefined=false;
	double radius=0.75*DrawingMetrics::getIconRadius();
	// filled circle at x-y position:
	if(!filterDefined){
		// Define a blur filter:
		os << "<defs>\n <filter id=\"blur_001\">\n  <feGaussianBlur in=\"SourceGraphic\" stdDeviation=\"3\" />\n </filter></defs>\n";
		filterDefined=true;
	}
	os << "<circle filter=\"url(#blur_001)\" cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << radius << "\"";
	os << " class=\"counterFill\" />\n";
	std::ostringstream osscc;
	osscc <<  collapsedCount;
	std::string collapsed = osscc.str();
	//static_cast<std::ostringstream*>( &(std::ostringstream() << collapsedCount) )->str();
	drawText(os,x,y+DrawingMetrics::getCounterFontSize()/3,collapsed,"counter","");
	
}

//
// drawTestTube
//
// fillFraction specifies how filled up the test tube is.
//
void SVG::drawTestTube(std::ostringstream& os,double x,double y,double fillFraction){
	
	double yStart=6;
	// move to x-y position and scale:
	os << "<g transform=\"translate(" << x << "," << y << ") scale(0.75)\">" << std::endl;
	// Draw the sample fill fraction first:
	if(fillFraction>0.0 && fillFraction<=1.0){
		double full=16.0;
		double fillHeight=fillFraction*full;
		double yOffset=yStart+(full-fillHeight);
		os << " <rect class=\"sampleLevel\" x=\"22\" y=\"" << yOffset <<"\" width=\"7\" height=\"" << fillHeight << "\" />" << std::endl;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << fillFraction;
		drawText(os,25.5,35,ss.str());
	}
	// Instructions to draw test tube:
	os << " <path class=\"blackInk\" d=\"";
	os << " M 20,5 c -0.543574,0 -0.98118,0.4376 -0.98118,0.98118 0,0.54357 0.437606,0.98118 0.98118,0.98118 l 0.73098,0 0,11.70426 c 0,2.59953 2.128534,4.72805 4.728062,4.72805 2.599528,0 4.728062,-2.12852 4.728062,-4.72805 l 0,-11.70426 0.73098,0 c 0.543573,0 0.98118,-0.43761 0.98118,-0.98118 0,-0.54358 -0.437607,-0.98118 -0.98118,-0.98118 l -10.918084,0 z m 2.69334,2.02123 5.531404,0 0,1.78452 -2.222374,0 c -0.543573,0 -0.98118,0.4376 -0.98118,0.98118 0,0.54357 0.437607,0.98119 0.98118,0.98119 l 2.222374,0 0,1.84339 -2.222374,0 c -0.543573,0 -0.98118,0.43759 -0.98118,0.98118 0,0.54358 0.437607,0.98117 0.98118,0.98117 l 2.222374,0 0,1.84339 -2.222374,0 c -0.543573,0 -0.98118,0.43762 -0.98118,0.98118 0,0.54358 0.437607,0.98119 0.98118,0.98119 l 2.222374,0 0,0.287 c 0,1.53874 -1.226943,2.76568 -2.765702,2.76568 -1.538759,0 -2.765702,-1.22694 -2.765702,-2.76568 l 0,-11.64539 z\" />" << std::endl;
	os << "</g>" << std::endl;
}

//
// drawLargerUterus: Used to indicate a gestational surrogate (not currently used)
//
void SVG::drawLargerUterus(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << x << "," << y << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m -6.7459211,-7.6 c -0.26099,0.31768 -0.48648,0.63933 -0.64539,0.9681 -0.009,0.018 -0.0183,0.0358 -0.0269,0.0538 -0.46638,0.53635 -1.19847,0.95445 -2.17821,0.69918 -1.4322699,-0.37317 -1.9111999,-0.75373 -2.7160499,-1.64039 -0.73505,-0.80977 -1.73016,-1.27653 -2.82361,-1.34457 -0.1562,-0.01 -0.32479,-0.006 -0.48405,0 -1.27405,0.0519 -2.69964,0.81552 -3.30766,2.44713 -0.94326,3.5664 3.09235,5.17279 3.57657,6.45397 0.39744,-0.46274 0.54462,-1.24685 0.45716,-2.04376 -0.0882,0.0191 -0.19823,0.0336 -0.2958,0.0269 -0.68304,-0.0472 -1.55236,-0.67188 -2.15133,-1.18322 -0.73661,-0.62886 -1.30331,-1.77907 -0.83363,-3.03875 0.46965,-1.25968 1.59247,-1.68077 2.58158,-1.72106 0.98913,-0.0403 1.96599,0.34369 2.58159,1.02188 0.85718,0.94431 1.59278,1.55388 3.2000899,1.93619 0.63659,0.15141 1.34776,0.18512 2.04376,0.13446 0.33033,-0.024 0.65034,-0.08 0.9681,-0.13446 0.31572,-0.0571 0.62442,-0.11951 0.91432,-0.18824 0.30239,-0.0717 0.61532,-0.13402 0.9412,-0.21513 0.11529,-0.0276 0.25551,-0.0764 0.37649,-0.10757 0.2157,-0.0555 0.42538,-0.11106 0.67229,-0.18824 0.44905,-0.11767 0.89186,-0.23981 1.10254,-0.29581 0.18419,-0.0485 0.39328,-0.0916 0.59161,-0.13446 0.6718,-0.14503 1.40508005,-0.23883 2.21856005,-0.23883 0.81346995,0 1.54674995,0.0938 2.21854995,0.23883 0.19833,0.0428 0.40742,0.086 0.59161,0.13446 0.21069,0.056 0.65349,0.17814 1.10256,0.29581 0.24689,0.0772 0.45658,0.13274 0.67229,0.18824 0.12094,0.0311 0.26116,0.08 0.37648,0.10757 0.32587,0.0811 0.6388,0.14343 0.9412,0.21513 0.28989,0.0687 0.59859,0.13113 0.91431,0.18824 0.31776,0.0545 0.63778,0.11042 0.9681,0.13446 0.696,0.0507 1.40717,0.0169 2.0437601,-0.13446 1.60731,-0.38231 2.34291,-0.99188 3.20009,-1.93619 0.61561,-0.67819 1.59247,-1.06215 2.58159,-1.02188 0.98912,0.0403 2.11193,0.46138 2.5816,1.72106 0.46966,1.25968 -0.0971,2.40989 -0.83365,3.03875 -0.59897,0.51134 -1.46828,1.13605 -2.15132,1.18322 -0.0976,0.007 -0.20768,-0.008 -0.2958,-0.0269 -0.0874,0.79691 0.0598,1.58102 0.45715,2.04376 0.48422,-1.28118 4.51983,-2.88757 3.57657,-6.45397 -0.60801,-1.63161 -2.03361,-2.39524 -3.30766,-2.44713 -0.15926,-0.006 -0.32785,-0.01 -0.48404,0 -1.09345,0.068 -2.08857,0.5348 -2.82362,1.34457 -0.80485,0.88666 -1.28378,1.26722 -2.7160401,1.64039 -0.97975,0.25527 -1.71182,-0.16283 -2.17822,-0.69918 -0.009,-0.018 -0.0182,-0.0358 -0.0269,-0.0538 -0.15891,-0.32877 -0.38441,-0.65042 -0.64539,-0.9681 -1.36857,-1.66584 -4.0148,-3.52129 -6.76324995,-3.52129 -2.74845005,-10e-6 -5.39469005,1.85545 -6.76325005,3.52129 z m -8.8204199,0.45716 c -0.73955,0.0301 -1.40538,0.39326 -1.82864,1.23701 -0.27466,1.06398 0.0141,1.65438 0.56472,2.12443 0.53402,0.45589 1.46363,0.81225 2.17823,0.72607 0.43078,-0.20427 0.73876,-0.70232 0.75295,-1.15633 -1.04202,0.41961 -3.0233,0.13603 -2.58159,-1.37147 0.25585,-0.43065 0.55053,-0.5746 0.9681,-0.59162 0.4661,-0.019 1.00652,0.23286 1.21013,0.45716 0.95324,1.05015 2.1729,1.99173 4.08751,2.44713 0.6746799,0.16047 1.3393699,0.22586 1.9899699,0.21513 0.24637,0.0249 0.47851,0.0983 0.6454,0.56473 0.46737,1.50025 1.55911,2.38227 2.68916,3.87238 2.69937,3.55945 -0.24933,6.61286 1.31768,9.17002 0.47878,0.78128 0.97188,0.88742 1.55971,0.88742 0.58786,0 1.67213005,-0.53441 1.26391005,-1.64038 -0.86745005,-2.51827 0.59338,-6.20976 0.29581,-9.78853 -0.17748,-2.13456 -0.82216005,-4.09696 -2.87739005,-4.54467 -0.008,-5e-4 -0.0192,4.4e-4 -0.0269,0 -0.43756,-0.0921 -0.98413,0.0331 -1.64038,0.18824 -0.31371,0.0742 -0.68808,0.13227 -1.10256,0.18824 -0.15872,0.0205 -0.31644,0.0374 -0.48404,0.0538 -0.39103,0.0382 -0.80038,0.0699 -1.21013,0.0807 -0.78907,0.0201 -1.57968,-0.0126 -2.2051,-0.16135 -1.7471999,-0.41558 -2.7025599,-1.18572 -3.6034699,-2.17822 -0.42806,-0.47157 -1.21206,-0.81044 -1.96308,-0.77985 z m 31.16731,0 c -0.75103,-0.0306 -1.53503,0.30828 -1.96309,0.77985 -0.90091,0.99249 -1.85627,1.76263 -3.60347,2.17822 -0.6254201,0.14876 -1.4160301,0.18142 -2.2051001,0.16135 -0.40975,-0.0108 -0.81909,-0.0425 -1.21013,-0.0807 -0.1676,-0.0164 -0.32532,-0.0333 -0.48404,-0.0538 -0.41447,-0.056 -0.78885,-0.1141 -1.10256,-0.18824 -0.65625,-0.1551 -1.20281,-0.28036 -1.64038,-0.18824 -0.008,4.4e-4 -0.019,-5e-4 -0.0269,0 -2.05524,0.44771 -2.69992999,2.41011 -2.87740999,4.54467 -0.29756996,3.57877 1.16325999,7.27026 0.29581,9.78853 -0.40822,1.10598 0.67604999,1.64038 1.26389999,1.64038 0.58784,0 1.08094,-0.10613 1.55972,-0.88742 1.56701,-2.55717 -1.38169,-5.61057 1.31768,-9.17002 1.13005,-1.49011 2.22179,-2.37213 2.68916,-3.87238 0.16689,-0.46638 0.39903,-0.53985 0.6454,-0.56473 0.6506,0.0107 1.3153,-0.0547 1.9899701,-0.21513 1.91461,-0.4554 3.13427,-1.39698 4.08751,-2.44713 0.20361,-0.2243 0.74403,-0.47614 1.21013,-0.45716 0.41757,0.017 0.71225,0.16097 0.9681,0.59162 0.44171,1.5075 -1.53957,1.79108 -2.58159,1.37147 0.0142,0.45401 0.32217,0.95205 0.75295,1.15633 0.7146,0.0862 1.64421,-0.27018 2.17823,-0.72607 0.5506,-0.47005 0.83938,-1.06045 0.56472,-2.12443 -0.42326,-0.84375 -1.08909,-1.2069 -1.82864,-1.23702 z m -27.96722,4.54467 c -0.76652,0.0715 -1.35295,0.47563 -1.53283,1.15634 -0.28778,1.08913 0.59293,2.45135 1.98998,3.03874 1.39704,0.5874 2.7778399,0.17482 3.0656399,-0.91431 0.2878,-1.08913 -0.61982,-2.45135 -2.0168699,-3.03875 -0.52389,-0.22027 -1.04602,-0.28491 -1.50592,-0.24202 z m 24.28307,0 c -0.329,0.0274 -0.67261,0.0952 -1.02188,0.24202 -1.3970301,0.5874 -2.3046501,1.94962 -2.0168601,3.03875 0.28779,1.08913 1.6685901,1.50171 3.0656301,0.91431 1.39705,-0.58739 2.30467,-1.94961 2.01687,-3.03874 -0.21585,-0.81685 -1.05674,-1.2387 -2.04376,-1.15634 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawUterus: Used to indicate a gestational surrogate (this one is used now)
//
void SVG::drawUterus(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-12.900) << "," << (y-7.624) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m 8.3293385,2.37986 c -0.17639,0.21471 -0.32879,0.43209 -0.43618,0.65429 -0.006,0.0122 -0.0124,0.0242 -0.0182,0.0363 -0.31521,0.3625 -0.80999,0.64507 -1.47215,0.47255 -0.968,-0.25221 -1.29168,-0.50941 -1.83564,-1.10866 -0.49679,-0.54729 -1.16933,-0.86275 -1.90834,-0.90873 -0.10557,-0.007 -0.21951,-0.004 -0.32715,0 -0.86106,0.0351 -1.82455,0.55117 -2.23548,1.65389 -0.6375,2.41035 2.08997,3.49604 2.41723,4.36192 0.26861,-0.31274 0.36808,-0.84268 0.30897,-1.38127 -0.0596,0.0129 -0.13397,0.0227 -0.19992,0.0182 -0.46163,-0.0319 -1.04916,-0.45409 -1.45397,-0.79969 -0.49784,-0.42501 -0.88085,-1.20238 -0.56341,-2.05374 0.31741,-0.85135 1.07627,-1.13594 1.74476,-1.16317 0.6685,-0.0272 1.32871,0.23228 1.74477,0.69063 0.57932,0.63822 1.07648,1.0502 2.16278,1.30858 0.43024,0.10233 0.91088,0.12511 1.38127,0.0909 0.22326,-0.0162 0.43954,-0.0541 0.6543,-0.0909 0.21337,-0.0386 0.42201,-0.0808 0.61794,-0.12722 0.20437,-0.0485 0.41586,-0.0906 0.63611,-0.1454 0.0779,-0.0186 0.17269,-0.0517 0.25445,-0.0727 0.14578,-0.0375 0.2874895,-0.0751 0.4543695,-0.12722 0.30349,-0.0795 0.60276,-0.16208 0.74515,-0.19993 0.12448,-0.0328 0.2658,-0.0619 0.39984,-0.0909 0.45404,-0.098 0.94962,-0.16141 1.49941,-0.16141 0.54979,0 1.04538,0.0634 1.49941,0.16141 0.13404,0.0289 0.27536,0.0581 0.39984,0.0909 0.1424,0.0379 0.44166,0.1204 0.74517,0.19993 0.16686,0.0521 0.30858,0.0897 0.45436,0.12722 0.0817,0.021 0.17651,0.0541 0.25445,0.0727 0.22024,0.0548 0.43173,0.0969 0.63611,0.1454 0.19592,0.0465 0.40456,0.0886 0.61794,0.12722 0.21475,0.0368 0.43104,0.0746 0.65429,0.0909 0.47039,0.0342 0.95103,0.0115 1.38127,-0.0909 1.0863,-0.25838 1.58346,-0.67036 2.16278,-1.30858 0.41606,-0.45835 1.07628,-0.71785 1.74477,-0.69063 0.6685,0.0272 1.42735,0.31182 1.74478,1.16317 0.31742,0.85136 -0.0656,1.62873 -0.56342,2.05374 -0.40482,0.3456 -0.99234,0.76781 -1.45397,0.79969 -0.066,0.005 -0.14037,-0.005 -0.19992,-0.0182 -0.0591,0.53859 0.0404,1.06853 0.30896,1.38127 0.32726,-0.86588 3.05473,-1.95157 2.41723,-4.36192 -0.41092,-1.10272 -1.37442,-1.61882 -2.23548,-1.65389 -0.10764,-0.004 -0.22158,-0.007 -0.32714,0 -0.73901,0.046 -1.41156,0.36144 -1.90835,0.90873 -0.54395,0.59925 -0.86764,0.85645 -1.83563,1.10866 -0.66217,0.17252 -1.15694,-0.11005 -1.47215,-0.47255 -0.006,-0.0122 -0.0123,-0.0242 -0.0182,-0.0363 -0.1074,-0.2222 -0.25981,-0.43958 -0.43619,-0.65429 C 16.546208,1.254 14.757748,0 12.900208,0 11.042668,-9.9999402e-6 9.2542085,1.254 8.3292685,2.37986 Z m -5.96128,0.30897 c -0.49983,0.0204 -0.94983,0.26579 -1.23589,0.83604 -0.18563,0.71909 0.01,1.11811 0.38167,1.4358 0.36092,0.30811 0.98919,0.54896 1.47216,0.49071 0.29114,-0.13806 0.49929,-0.47466 0.50888,-0.78151 -0.70425,0.2836 -2.0433,0.0919 -1.74477,-0.92691 0.17291,-0.29105 0.37207,-0.38834 0.65429,-0.39984 0.31501,-0.0128 0.68026,0.15738 0.81787,0.30897 0.64424,0.70975 1.46855,1.34611 2.76254,1.6539 0.45598,0.10845 0.90521,0.15264 1.34492,0.14539 0.16651,0.0168 0.3234,0.0665 0.4362,0.38167 0.31587,1.01395 1.05372,1.61007 1.81747,2.61715 1.8243695,2.40566 -0.16851,4.4693 0.8905495,6.19757 0.32358,0.52803 0.65685,0.59976 1.05413,0.59976 0.39731,0 1.13011,-0.36118 0.85422,-1.10865 -0.58627,-1.70198 0.40103,-4.19687 0.19992,-6.61558 -0.11995,-1.44265 -0.55566,-2.76894 -1.94469,-3.07152 -0.005,-3.4e-4 -0.013,3e-4 -0.0182,0 -0.29572,-0.0623 -0.6651195,0.0224 -1.1086495,0.12722 -0.21202,0.0501 -0.46504,0.0894 -0.74516,0.12722 -0.10727,0.0138 -0.21387,0.0253 -0.32714,0.0363 -0.26428,0.0258 -0.54094,0.0472 -0.81787,0.0545 -0.53329,0.0136 -1.06763,-0.008 -1.49032,-0.10905 -1.18084,-0.28087 -1.82652,-0.80137 -2.4354,-1.47214 -0.28931,-0.31872 -0.81917,-0.54775 -1.32675,-0.52707 z m 21.0644395,0 c -0.50759,-0.0207 -1.03745,0.20836 -1.32676,0.52707 -0.60888,0.67078 -1.25456,1.19127 -2.43541,1.47215 -0.42269,0.10054 -0.95702,0.12261 -1.49031,0.10905 -0.27693,-0.007 -0.55359,-0.0287 -0.81787,-0.0545 -0.11327,-0.0111 -0.21987,-0.0225 -0.32714,-0.0363 -0.28012,-0.0378 -0.53314,-0.0771 -0.74516,-0.12723 -0.44353,-0.10482 -0.81292,-0.18948 -1.10866,-0.12722 -0.005,3e-4 -0.0128,-3.4e-4 -0.0182,0 -1.38903,0.30258 -1.82474,1.62887 -1.94469,3.07152 -0.20112,2.41871 0.78619,4.91361 0.19992,6.61558 -0.2759,0.74748 0.45691,1.10865 0.85421,1.10865 0.39729,0 0.73055,-0.0717 1.05413,-0.59976 1.05907,-1.72826 -0.93381,-3.79191 0.89056,-6.19756 0.76374,-1.00709 1.5016,-1.60321 1.81747,-2.61716 0.11279,-0.31519 0.26968,-0.36485 0.43619,-0.38166 0.43971,0.007 0.88895,-0.0369 1.34492,-0.1454 1.29399,-0.30778 2.1183,-0.94415 2.76255,-1.6539 0.13761,-0.15159 0.50285,-0.3218 0.81787,-0.30897 0.28221,0.0115 0.48137,0.1088 0.65429,0.39985 0.29853,1.01885 -1.04052,1.2105 -1.74477,0.92691 0.01,0.30684 0.21774,0.64345 0.50888,0.78151 0.48296,0.0582 1.11124,-0.18261 1.47216,-0.49072 0.37212,-0.31769 0.56729,-0.7167 0.38166,-1.4358 -0.28606,-0.57025 -0.73606,-0.81568 -1.23588,-0.83603 z M 4.5308385,5.76035 c -0.51805,0.0483 -0.91439,0.32146 -1.03596,0.78151 -0.1945,0.73609 0.40073,1.65675 1.34493,2.05374 0.94419,0.397 1.8774,0.11815 2.07191,-0.61794 0.19451,-0.73609 -0.41891,-1.65674 -1.3631,-2.05373 -0.35407,-0.14888 -0.70696,-0.19256 -1.01778,-0.16358 z m 16.4117195,0 c -0.22235,0.0186 -0.45458,0.0643 -0.69064,0.16358 -0.94418,0.39699 -1.55759,1.31764 -1.36309,2.05373 0.1945,0.73609 1.12772,1.01494 2.07191,0.61794 0.94419,-0.39699 1.55761,-1.31765 1.3631,-2.05374 -0.14588,-0.55206 -0.7142,-0.83717 -1.38128,-0.78151 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawLeftFacingSperm: Used to indicate a sperm donor
//
void SVG::drawLeftFacingSperm(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-13.235) << "," << (y-3.44415) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m 5.3984779,6.888222 c 1.60201,-0.0116 2.83393,-1.02621 3.52928,-1.71595 0.26675,-0.2646 0.41472,-0.30738 0.65048,-0.32275 l 2.2161801,-0.13046 c 0.32189,-0.021 0.51006,-0.21972 0.68365,-0.4672 0.094,-0.13401 0.29306,-0.18286 0.56799,-0.12731 0.44954,0.0908 1.50665,0.14928 2.58423,-0.13894 0.8406,-0.22483 1.35882,-0.72969 1.80961,-1.49621 0.43389,-0.73778 0.98794,-1.33595 2.12525,-1.24875 0.99585,0.0763 1.43774,0.90946 1.77732,2.07899 0.26291,0.90541 0.78311,2.37796 2.5245,2.53053 1.63989,0.0313 2.47623,-1.06217 2.60681,-2.66793 l -0.18936,-0.0269 c -0.22709,1.06193 -0.79415,2.22241 -2.29993,1.97615 -1.3769,-0.12064 -1.70104,-1.26463 -1.96295,-2.42103 -0.2175,-0.96031 -0.95738,-2.32303004 -2.49772,-2.45889004 -1.41599,-0.1249 -2.18341,0.55981 -2.67157,1.28644004 -0.53781,0.80053 -0.6536,1.05378 -1.45703,1.33194 -0.88286,0.30567 -1.80595,0.15828 -2.27624,0.0821 -0.27962,-0.0453 -0.52004,-0.0223 -0.6399,-0.22586 -0.1968,-0.33415 -0.26121,-0.5921 -0.76393,-0.63838 l -2.1376701,-0.0324 c -0.2431,-0.0122 -0.51227,-0.11207 -0.63989,-0.25324 C 8.2003679,0.98666196 6.9568979,0.00142196 5.3456879,1.9566922e-6 2.6473679,-0.00199804 0.02825792,1.529462 2.1792023e-4,3.397332 -0.02788208,5.265212 2.6661879,6.907912 5.3984779,6.888122 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawRightFacingSperm: Used to indicate a sperm donor
//
void SVG::drawRightFacingSperm(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-13.235) << "," << (y-3.44415) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m 21.0753,6.888222 c -1.60201,-0.0116 -2.83393,-1.02621 -3.52928,-1.71595 -0.26675,-0.2646 -0.41472,-0.30738 -0.65048,-0.32275 l -2.21618,-0.13046 c -0.32189,-0.021 -0.51006,-0.21972 -0.68365,-0.4672 -0.094,-0.13401 -0.29306,-0.18286 -0.56799,-0.12731 -0.44954,0.0908 -1.50665,0.14928 -2.58423,-0.13894 C 10.00289,3.760782 9.48467,3.255922 9.03388,2.489402 8.59999,1.751622 8.04594,1.153452 6.90863,1.240652 5.91278,1.316952 5.47089,2.150112 5.13131,3.319642 4.8684,4.225052 4.3482,5.697602 2.60681,5.850172 0.96692,5.881472 0.13058,4.788002 0,3.182242 l 0.18936,-0.0269 c 0.22709,1.06193 0.79415,2.22241 2.29993,1.97615 1.3769,-0.12064 1.70104,-1.26463 1.96295,-2.42103 0.2175,-0.96031 0.95738,-2.32303004 2.49772,-2.45889004 1.41599,-0.1249 2.18341,0.55981 2.67157,1.28644004 0.53781,0.80053 0.6536,1.05378 1.45703,1.33194 0.88286,0.30567 1.80595,0.15828 2.27624,0.0821 0.27962,-0.0453 0.52004,-0.0223 0.6399,-0.22586 0.1968,-0.33415 0.26121,-0.5921 0.76393,-0.63838 l 2.13767,-0.0324 c 0.2431,-0.0122 0.51227,-0.11207 0.63989,-0.25324 C 18.27341,0.98666196 19.51688,0.00142196 21.12809,1.9566922e-6 23.82641,-0.00199804 26.44552,1.529462 26.47356,3.397332 c 0.0281,1.86788 -2.66597,3.51058 -5.39826,3.49079 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawOvum: Used to indicate an ovum donor
//
void SVG::drawOvum(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-7.075) << "," << (y-7.090) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"M 7.09375,0 C 3.18627,0 0,3.18627 0,7.09375 c 0,3.90748 3.18627,7.09375 7.09375,7.09375 3.90748,0 7.0625,-3.18627 7.0625,-7.09375 C 14.15625,3.18627 11.00123,0 7.09375,0 z m 0,1.1875 c 3.26976,0 5.875,2.6365 5.875,5.90625 C 12.96875,10.36351 10.36351,13 7.09375,13 3.82399,13 1.1875,10.36351 1.1875,7.09375 1.1875,3.824 3.82399,1.1875 7.09375,1.1875 z M 7.8125,5.21875 c -1.44062,0 -2.625,1.15314 -2.625,2.59375 0,1.44062 1.18438,2.625 2.625,2.625 1.44062,0 2.59375,-1.18438 2.59375,-2.625 0,-1.44061 -1.15313,-2.59375 -2.59375,-2.59375 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawEntwinedRings: This symbol is generally used to indicate a marriage.
//                    In Madeline, it is specifically used to unambiguously
//                    designate a same-sex relationship and may also be used
//                    to indicate any union without (biological) offspring.
//
void SVG::drawEntwinedRings(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-8.966) << "," << (y-6.216) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"M 6.21875,0 C 2.7946188,0 0,2.7946202 0,6.21875 c 0,3.4241298 2.7946188,6.21875 6.21875,6.21875 0.9873059,0 1.9195394,-0.24374 2.75,-0.65625 0.8304606,0.41251 1.762694,0.65625 2.75,0.65625 3.424131,0 6.21875,-2.7946202 6.21875,-6.21875 C 17.9375,2.7946202 15.142881,0 11.71875,0 10.731444,0 9.7992106,0.24374032 8.96875,0.65625 8.1382894,0.24374032 7.2060559,0 6.21875,0 z m 0,1.75 C 6.573081,1.75 6.9199481,1.7974733 7.25,1.875 6.1599598,2.9957857 5.5,4.5380034 5.5,6.21875 c 0,1.6868875 0.6841705,3.1906132 1.78125,4.3125 -0.3421193,0.0837 -0.6939143,0.125 -1.0625,0.125 C 3.7522807,10.65625 1.75,8.6852198 1.75,6.21875 1.75,3.7522802 3.7522807,1.75 6.21875,1.75 z m 5.5,0 c 2.466469,0 4.4375,2.0022802 4.4375,4.46875 0,2.4664698 -1.971031,4.4375 -4.4375,4.4375 -0.366545,0 -0.722102,-0.0422 -1.0625,-0.125 1.089647,-1.1207232 1.78125,-2.6320966 1.78125,-4.3125 0,-1.6735 -0.699497,-3.1930506 -1.78125,-4.3125 C 10.996648,1.8234513 11.352205,1.75 11.71875,1.75 z m -2.75,0.96875 c 1.038759,0.813877 1.6875,2.0724884 1.6875,3.5 0,1.4275116 -0.648741,2.686123 -1.6875,3.5 C 7.9299909,8.904873 7.25,7.6462616 7.25,6.21875 c 0,-1.4275116 0.6799909,-2.686123 1.71875,-3.5 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawRoundedTriangle: Used to indicate an intersex or DSD individual
//
void SVG::drawRoundedTriangle(std::ostringstream& os, double x, double y){
	// h=25.939 w=26.716
	os << "<g transform=\"translate(" << (x-13.358) << "," << (y-12.969) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"m 1.376316,4.3850361 c -2.6623,4.68441 6.5727,20.6768399 11.9903,20.6682199 5.3139,-0.009 14.6731,-15.9425599 11.9626,-20.6170299 -2.7105,-4.67447995 -21.2681,-4.77509995 -23.9529,-0.0512 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawSquareTopRoundBottom: Used to indicate protoandrous individual
//
void SVG::drawSquareTopRoundBottom(std::ostringstream& os, double x, double y){
	//
	//    height="24.451679" width="24.4517"
	//
	os << "<g transform=\"translate(" << (x-12.226) << "," << (y-12.226) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"M 12.2259,23.56568 A 11.34,11.34 0 0 1 0.88599998,12.22584 l 0,-11.33984002 11.33990002,0 11.3398,0 0,11.33984002 A 11.34,11.34 0 0 1 12.2259,23.56568 Z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawRoundTopSquareBottom: Used to indicate 
//
void SVG::drawRoundTopSquareBottom(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-12.226) << "," << (y-12.226) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"M 12.2259,0.88599998 A 11.34,11.34 0 0 0 0.88599998,12.22584 l 0,11.33984 11.33990002,0 11.3398,0 0,-11.33984 A 11.34,11.34 0 0 0 12.2259,0.88599998 Z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawHermaphrodite: Used to indicate a true hermaphrodite 
//
void SVG::drawHermaphrodite(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-17.398) << "," << (y-12.346) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"M 17.398297,0.88600038 A 17.566586,17.566586 0 0 0 0.94492706,12.36118 17.566586,17.566586 0 0 0 17.398297,23.80641 17.566586,17.566586 0 0 0 33.851667,12.33122 17.566586,17.566586 0 0 0 17.398297,0.88600038 Z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawFlower: Used to indicate a monoecious individual 
//
void SVG::drawFlower(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-12.605) << "," << (y-12.379) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"m 12.530327,23.871684 c -2.51472,0.0384 -4.9195604,-1.70845 -5.6605804,-4.11183 -3.03275,0.0911 -5.80939,-2.48434 -5.96522005,-5.50769 -0.1665,-2.05364 0.82785005,-4.15196 2.53042005,-5.31494 -1.08313,-2.81564 0.39832,-6.27406 3.17977,-7.43544 1.88,-0.85249999 4.1962204,-0.62525999 5.8670204,0.59049 2.33744,-1.84646999 6.02401,-1.50135999 7.97891,0.7457 1.47932,1.59522 1.95055,4.03051 1.17527,6.06298 2.55839,1.60347 3.45593,5.26833 1.92401,7.87132 -1.04719,1.9178 -3.22026,3.14122 -5.40317,3.04111 -0.76374,2.37748 -3.12879,4.08484 -5.62643,4.0583 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawSmallRoundedTriangle: Used to indicate a DSD condition below an individual icon
//
void SVG::drawSmallRoundedTriangle(std::ostringstream& os, double x, double y){
	
	//os << "<g transform=\"translate(" << (x-8.0) << "," << (y-8.0) << ")\" >" << std::endl;
	//os << " <path class=\"solid\" d=\"m 1.1737412,3.3521719 c -1.51900002,2.67282 3.7503,11.7977101 6.8414,11.7928001 3.0319998,-0.005 8.3720998,-9.0964501 6.8255998,-11.7635901 -1.5466,-2.66714995 -12.1350998,-2.72455995 -13.6669998,-0.0292 z\" />" << std::endl;
	//os << "</g>" << std::endl;
	
	// Revised (smaller):
	os << "<g transform=\"translate(" << (x-6.840) << "," << (y-6.645) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"m 1.1294298,2.5537709 c -1.26890003,2.23275 3.13284,9.8553001 5.71501,9.8512001 2.5328,-0.004 6.9937002,-7.5987901 5.7018202,-9.8268001 C 11.2543,0.35014088 2.4091098,0.30218088 1.1294298,2.5537709 Z\" />" << std::endl;
	os << "</g>" << std::endl;
}

//
// drawSmallSquareTopRoundBottom: Used to indicate protandry below an individual icon
//
void SVG::drawSmallSquareTopRoundBottom(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-6.545) << "," << (y-6.545) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"M 6.5448,12.20342 A 5.6587914,5.6587914 0 0 1 0.88599998,6.54471 l 0,-5.65871002 5.65880002,0 5.6587,0 0,5.65871002 a 5.6587914,5.6587914 0 0 1 -5.6587,5.65871 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawSmallRoundTopSquareBottom: Used to indicate protogyny below an individual icon
//
void SVG::drawSmallRoundTopSquareBottom(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-6.545) << "," << (y-6.545) << ")\" >" << std::endl;
	os << " <path class=\"solid\" d=\"M 6.5448,0.88599998 A 5.6587914,5.6587914 0 0 0 0.88599998,6.54471 l 0,5.65871 5.65880002,0 5.6587,0 0,-5.65871 A 5.6587914,5.6587914 0 0 0 6.5448,0.88599998 Z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawPhaseISymbol: Used to indicate a phase I male in certain protandrous species (e.g., certain wrasses)
//
void SVG::drawPhaseISymbol(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-2.645) << "," << (y-5.596) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m 0,0 0,1.77148 1.7598,0 0,7.64884 -1.7598,0 0,1.77148 5.2911,0 0,-1.77148 -1.7598,0 0,-7.64884 1.7598,0 0,-1.77148 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawPhaseIISymbol: Used to indicate a phase II (terminal) male in certain protandrous species (e.g., certain wrasses)
//
void SVG::drawPhaseIISymbol(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-5.257) << "," << (y-5.596) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"m 0,0 0,1.77149 1.75976,0 0,7.64883 -1.75976,0 0,1.77148 10.51367,0 0,-1.77148 -1.75977,0 0,-7.64883 1.75977,0 0,-1.77149 z m 3.53125,1.77149 3.45117,0 0,7.64883 -3.45117,0 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawSmallX: Used to indicate absent parent in a parthenogenetic situation
//
void SVG::drawSmallX(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-4.553) << "," << (y-4.553) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"M 0,1.25262 0.0911,1.34382 3.3007,4.55342 0.09248,7.76165 0.00128,7.85275 1.2539,9.10537 1.345,9.01427 4.55322,5.80605 7.76145,9.01427 7.85265,9.10537 9.10527,7.85275 9.01417,7.76165 5.80595,4.55342 9.01556,1.34382 9.10666,1.25262 7.85404,0 7.76294,0.0911 4.55333,3.30071 1.34373,0.09111 1.25263,1e-5 10e-6,1.25263 Z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

//
// drawMitochondrium: Used to indicate a mitochondrial donor in a pronuclear transfer or maternal spindle transfer
//
void SVG::drawMitochondrium(std::ostringstream& os, double x, double y){
	
	os << "<g transform=\"translate(" << (x-7.08065) << "," << (y-6.73670) << ")\" >" << std::endl;
	os << " <path class=\"blackInk\" d=\"M 10.844744,2.1982012 C 9.2331442,0.86157123 7.3704542,0.11731123 5.6142842,0.01242123 c -1.75619,-0.10491 -3.44259,0.45253 -4.52382,1.75616997 -1.08122001,1.30362 -1.31719001,3.06403 -0.88936001,4.77053 0.42782,1.70651 1.50369001,3.39943 3.11528001,4.7360798 1.61159,1.33663 3.47428,2.0809 5.23046,2.18578 1.7561898,0.10491 3.4425898,-0.45254 4.5238098,-1.75616 1.08122,-1.30364 1.3172,-3.0640398 0.88937,-4.7705498 -0.42783,-1.70649 -1.5037,-3.39944 -3.11528,-4.73607 z m -0.72811,1.26287 c 1.03054,0.90455 1.76884,1.96527 2.19235,3.02802 -1.68477,1.80019 -2.26298,2.64679 -2.8000298,3.9350098 a 0.60552257,0.60552257 0 0 0 1.1176198,0.46641 c 0.44554,-1.0685298 0.83871,-1.6901598 2.05116,-3.0209798 0.15641,1.1348 -0.061,2.1614198 -0.69851,2.9300698 -0.74762,0.90141 -1.93512,1.32977 -3.3479298,1.24539 -0.45675,-0.0272 -0.93539,-0.1313 -1.41825,-0.27054 0.0368,-0.48202 0.15262,-0.73925 0.4234,-1.12873 0.36645,-0.52692 1.08001,-1.2625398 2.18535,-2.6977998 a 0.6050576,0.6050576 0 0 0 -0.11217,-0.86061 0.6050576,0.6050576 0 0 0 -0.84635,0.12088 c -1.0726,1.39275 -1.74998,2.07072 -2.22095,2.74812 -0.2922,0.4203598 -0.46761,0.8656998 -0.5638,1.3868698 -0.63506,-0.29746 -1.26591,-0.6692 -1.85696,-1.15942 -0.83066,-0.6889298 -1.46401,-1.4876598 -1.93226,-2.3087698 0.8004,-0.20624 1.47068,-0.43054 2.03657,-0.83777 0.77982,-0.56122 1.42134,-1.37389 2.55636,-2.80459 a 0.6050576,0.6050576 0 0 0 -0.0989,-0.86184 0.6050576,0.6050576 0 0 0 -0.84728,0.11096 c -1.13216,1.42703 -1.74311,2.15891 -2.31786,2.57254 -0.4495,0.32348 -1.02528,0.50999 -1.84382,0.70902 -0.0679,-0.18988 -0.15038,-0.38136 -0.19741,-0.569 -0.34417,-1.37285 -0.14281,-2.61908 0.60483,-3.52049 0.60884,-0.73409 1.51845,-1.13697 2.59485,-1.22215 l -2.33847,2.81951 a 0.6050576,0.6050576 0 1 0 0.93135,0.77245 l 2.90574,-3.50348 c 0.93189,0.17012 1.90173,0.55225 2.83006,1.15595 -0.68513,1.87624 -2.10019,3.20481 -3.48068,4.78899 a 0.60516476,0.60516476 0 0 0 0.91328,0.79424 c 1.25071,-1.43523 2.7462,-2.81312 3.5786298,-4.81827 z m 0.7731,1.811 a 0.62520109,0.62520109 0 0 0 -0.84397,0.11059 0.62520109,0.62520109 0 0 0 0.0805,0.88033 0.62520109,0.62520109 0 0 0 0.88185,-0.0823 0.62520109,0.62520109 0 0 0 -0.0837,-0.88004 0.62520109,0.62520109 0 0 0 -0.0346,-0.0287 z m -6.0841498,2.96743 a 0.62520109,0.62520109 0 0 0 -0.88185,0.0823 0.62520109,0.62520109 0 0 0 0.0837,0.88003 0.62520109,0.62520109 0 0 0 0.87852,-0.0819 0.62520109,0.62520109 0 0 0 -0.0805,-0.88035 z\" />" << std::endl;
	os << "</g>" << std::endl;
	
}

