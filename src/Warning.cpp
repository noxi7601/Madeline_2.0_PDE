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
// 2005.03.14.ET
//

//
// Warning.cpp
//

#include "Warning.h"
#include "Debug.h"
#include <string.h>
#include "VT100.h"

#include "main2.h"

bool Warning::_suppressWarnings=false;
const char *Warning::_warningSalutation="Warning";

//
// Warning() constructor:
//
Warning::Warning( const char *const methodName , const char *format , ... ){
	
	//
	// The Warning class uses the Warning salutation:
	//
	_salutation = gettext(_warningSalutation);
	_methodName = methodName;
	int n;
	va_list args;
	if(strlen(format) > 0){
		va_start(args,format);
		n=vsnprintf(_message,GENERAL_STRING_BUFFER_SIZE,gettext(format),args);
		va_end(args);
		_truncated=(n==GENERAL_STRING_BUFFER_SIZE);
	}
	
	print();
	
}

//
// suppressWarnings()
//
void Warning::suppressWarnings(bool suppressWarnings){
	
	_suppressWarnings=suppressWarnings;
	
}

//
// print()
//
void Warning::print(void){
	
	std::cerr << vt100::startRed ;
	std::cerr << _salutation << ": ";
	std::cerr << vt100::stopColor;
	if(Debug::DEBUG){
		std::cerr << vt100::startGreen ;
		std::cerr << _methodName << ": ";
		std::cerr << vt100::stopColor  ;
	}
	std::cerr << _message << std::endl;
	if(_truncated){
		std::cerr << gettext("(Message has been truncated)") << std::endl;
	}

	printWarning(_message);
}



