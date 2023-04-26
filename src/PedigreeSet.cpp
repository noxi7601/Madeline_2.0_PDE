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
// PedigreeSet.cpp
//

#include "PedigreeSet.h"
#include "DataColumn.h"
#include "LabelSet.h"
#include "DrawingMetrics.h"
#include "VT100.h"
#include <algorithm>
#include <set>
#include <map>

//////////////////////////////////////
//
// DESTRUCTORS:
//
//////////////////////////////////////

PedigreeSet::~PedigreeSet()
{
	
	
	std::set<Pedigree*,comparePedigrees>::iterator pit = _pedigrees.begin();
	while(pit != _pedigrees.end()){
		delete *pit;
		++pit;
	}
	_pedigrees.clear();
	
	
}

//////////////////////////////////////
//
// PRIVATE METHODS
//
//////////////////////////////////////

//
// _checkParentChildDOB():
//
void PedigreeSet::_checkParentChildDOB(){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->checkParentChildDOB();
		++it;
	}
	
}

//
// _checkPregnancyStateValidity()
//
void PedigreeSet::_checkPregnancyStateValidity(){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->checkPregnancyStateValidity();
		++it;
	}
	
}

//
// _computeWidths():
//
void PedigreeSet::_computeWidths(const std::string& sortField,bool dobSortOrder ){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->computePedigreeWidth(sortField,dobSortOrder);
		
		++it;
	}
	
	
}

//
// _determineFoundingGroups():
//
void PedigreeSet::_determineFoundingGroups(){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->determineFoundingGroups();
		++it;
	}
	
}

//
// _establishConnections():
//
void PedigreeSet::_establishConnections(){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->addIdentifiedMissingParents();
		(*it)->establishIndividualConnections();
		(*it)->reportUnconnectedIndividuals();
		++it;
	}
	
}

//
// _setCoreOptionalFields():
//
void PedigreeSet::_setCoreOptionalFields(const DataTable* pedigreeTable){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		(*it)->setCoreOptionalFields(pedigreeTable);
		++it;
	}
	
}


//////////////////////////////////////
//
// PUBLIC METHODS
//
//////////////////////////////////////

//
// addPedigreesFromDataTable():
//
void PedigreeSet::addPedigreesFromDataTable(const DataTable * p_pedigreeTable, unsigned tableIndex,const std::string& sortField){
	
	//
	// Use const reference for convenience:
	// (so I don't have to change the code
	//  since the parameter has changed from a
	//  const DataTable & to a const DataTable * )
	//
	const DataTable & pedigreeTable = (*p_pedigreeTable);
	
	std::cout << vt100::startBlue << "┏ Start of    addPedigreesFromDataTable ┓" << vt100::stopColor << std::endl;
	
	//
	// Get all the core columns from the datatable:
	//
	DataColumn *familyIdColumn = pedigreeTable.getColumn( pedigreeTable.labels.FamilyIdField );
	//familyIdColumn->printData();
	DataColumn *individualIdColumn = pedigreeTable.getColumn( pedigreeTable.labels.IndividualIdField );
	//individualIdColumn->printData();
	DataColumn *motherIdColumn = pedigreeTable.getColumn( pedigreeTable.labels.MotherIdField );
	DataColumn *fatherIdColumn = pedigreeTable.getColumn( pedigreeTable.labels.FatherIdField );
	DataColumn *genderColumn   = pedigreeTable.getColumn( pedigreeTable.labels.GenderField );
	
	DataColumn *collapsedColumn= 0;
	if(pedigreeTable.columnExists(pedigreeTable.labels.CollapsedField)){
		// 2015.11.30.ET ADDENDA:
		collapsedColumn=pedigreeTable.getColumn( pedigreeTable.labels.CollapsedField );
	}
	//
	// Insert the Pedigrees in a set:
	//
	std::string currentFamily;
	int numberOfRows = familyIdColumn->getNumberOfRows();
	int index=0;
	
	std::map<std::string,Individual *> collapsedIndicatorSet;
	Individual * collapsedIndividual=0;
	
	while(index < numberOfRows){
		
		currentFamily = familyIdColumn->get(index);
		if(currentFamily == "."){
			Warning("PedigreeSet::addPedigreesFromDataTable()",
			        "Family Id is missing for individual %s and will be ignored.",
			        individualIdColumn->get(index).c_str()
			);
			index++;
			continue;
		}
		std::pair<std::set<Pedigree*,comparePedigrees>::iterator,bool> pp;
		pp = _pedigrees.insert(new Pedigree(currentFamily,tableIndex));
		if(pp.second){
			for(int i=0;i<familyIdColumn->getNumberOfRows();i++) { 
				if(currentFamily.compare(familyIdColumn->get(i)) == 0){
					///////////////////////////////////
					//
					// Handle "collapsing":
					//
					///////////////////////////////////
					if(DrawingMetrics::getCollapsible() && collapsedColumn){
						std::string indicator=collapsedColumn->get(i);
						if(indicator=="."){
							// Add normal, non-collapsed individual, as usual:
							(*pp.first)->addIndividual(individualIdColumn->get(i),motherIdColumn->get(i),fatherIdColumn->get(i),genderColumn->get(i),i,tableIndex,pedigreeTable);
						}else{
							//
							// Handling collapsed individuals:
							//
							std::map<std::string,Individual *>::iterator it=collapsedIndicatorSet.find(indicator);
							if(it==collapsedIndicatorSet.end()){
								//
								// Indicator not yet present in set, so add the first marked individual
								// as the token individual:
								//
								collapsedIndividual = (*pp.first)->addIndividual(individualIdColumn->get(i),motherIdColumn->get(i),fatherIdColumn->get(i),genderColumn->get(i),i,tableIndex,pedigreeTable);
								collapsedIndividual->incrementCollapsedCount();
								collapsedIndicatorSet.insert(std::pair<std::string,Individual *>(indicator,collapsedIndividual));
								// 2015.12.01.ET DEBUG
								std::cout << "*** Individual " << individualIdColumn->get(i) << " used for collapsed group " << indicator << std::endl;
							}else{
								//////////////////////////////////////////////////
								//
								// Is gender of new person consistent?
								// 
								// Note: using Gender.getEnum() guarantees 
								// symbolic equivalency across different
								// string representations, e.g. "M"=="male", 
								// "♀"=="female", etc.
								//
								//////////////////////////////////////////////////
								if( it->second->getGender().getEnum() != Gender(genderColumn->get(i)).getEnum() ){
									// Change to missing on token individual:
									it->second->setGender(".");
								}
								//////////////////////////////////////////////////
								//
								// Is affection status of new person consistent?
								//
								//////////////////////////////////////////////////
								
								//////////////////////////////////////////////////
								//
								// increment collapsed count:
								//
								//////////////////////////////////////////////////
								it->second->incrementCollapsedCount();
								// 2015.12.01.ET DEBUG
								// std::cout << "*** Individual " << it->second->getId() << " with indicator " << indicator << " incremented to " << it->second->getCollapsedCount() << std::endl;
							}
						}
					}else{
						// CollapsedState OFF or Collapsed column not present, so just add everybody:
						(*pp.first)->addIndividual(individualIdColumn->get(i),motherIdColumn->get(i),fatherIdColumn->get(i),genderColumn->get(i),i,tableIndex,pedigreeTable);
					}
				}
			}
		}
		index++;
	}
	
	// Set the core optional fields on the individuals
	_setCoreOptionalFields(p_pedigreeTable);
	
	_establishConnections();
	
	bool dobPresent = false;
	if(pedigreeTable.getDOBColumnIndex() != DataTable::COLUMN_IS_MISSING){
		_checkParentChildDOB();
		dobPresent = true;
	}
	
	if(pedigreeTable.getPregnancyColumnIndex() != DataTable::COLUMN_IS_MISSING){
		_checkPregnancyStateValidity();
	}
	
	_determineFoundingGroups();
	
	bool sortFieldPresent = false;
	if(sortField != std::string("") && sortField != pedigreeTable.labels.DOBField){
		// Check to see if the field actually exists in the data table
		if(pedigreeTable.columnExists(sortField)){
			_computeWidths(sortField);
			sortFieldPresent = true;
		}else{
			Warning("PedigreeSet::addPedigreesFromDataTable()",
			        "Field '%s' specified for sorting the siblings does not exist in the Pedigree Table. Default ordering will be used.",
			        sortField.c_str()
			);
		}
	}
	if(!sortFieldPresent){
		if(dobPresent){
			std::cout << "Siblings are ordered by DOB." << std::endl;
			_computeWidths(pedigreeTable.labels.DOBField,true);
			DrawingMetrics::setDisplayBirthOrder(true);
		}else{    
			std::cout << "Default ordering of siblings." << std::endl;
			_computeWidths(std::string(""));
			
		}
	}
	std::cout << vt100::startBlue << "┗ End of      addPedigreesFromDataTable ┛" << vt100::stopColor << std::endl;
	
}

//
// draw():
//
std::string PedigreeSet::draw(const DataTable *const pedigreeTable){
	std::string result;
	
	std::cout << vt100::startBlue << "┏ Start of    draw                      ┓" << vt100::stopColor << std::endl;
	//
	// Make a note if there is only one pedigree to be drawn: 
	//
	if( _pedigrees.size()==1 ) DrawingMetrics::setHasOnlyOnePedigreeState(true);
	
	//
	// Instantiate a LabelSet object for a pedigree set:
	//
	LabelSet labelSet(pedigreeTable);
	// DEBUG: std::cout << "No of labels: " << labelSet.getNumberOfLabels() << std::endl;
	
	//
	// Iterate over the pedigrees and draw them:
	//
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		result = (*it)->draw(&labelSet);
		//
		// If --outputpedtable flag is set print the core/non-core fields to a tab delimited file with the name "FAMILY_ID"input.txt
		//
		if(DrawingMetrics::getHasOutputPedTable())  pedigreeTable->printPedigreeTableAsTabDelimited((*it)->getId()+"input.txt");
		//
		// If --outputdatatable flag is set print the input pedigree file as a tab delimited file with the name "FAMILY_ID"data.txt
		//
		if(DrawingMetrics::getHasOutputDataTable())  pedigreeTable->printInputTableAsTabDelimited((*it)->getId()+"data.txt");
		++it;
	}
	
	std::cout << vt100::startBlue << "┗ End of      draw                      ┛" << vt100::stopColor << std::endl;

	return result;
}

//
// display():
//
void PedigreeSet::display(){
	
	std::set<Pedigree*,comparePedigrees>::const_iterator it = _pedigrees.begin();
	while(it != _pedigrees.end()){
		std::cout << "Pedigree Id " << (*it)->getId() << " Table Id" << (*it)->getTableId() << std::endl; 
		// Display Individuals in Pedigree Id
		(*it)->display();
		it++;
	}
	
}
