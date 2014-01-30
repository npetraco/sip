#include <iostream>
#include <Rcpp.h>
#include "smile.h"
#include "PrintUtilities.h"

using namespace Rcpp;
using namespace std;

/*=================================================*/
/*Get the levels associated with a chance/decision */
/*node and the levels associated with the node's   */
/*parents.                                         */
/*=================================================*/

// [[Rcpp::export]]
List GetLevelsAssociatedWithChanceOrDecisionNode(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  std::string childNodeName = childNode->Info().Header().GetName();    //Child Node name (cast to a string)

  //We want access to the node levels, nodes parent levels
  int childNumLevels = childNode->Definition()->GetNumberOfOutcomes();        //Number of levels for the child (Outcomes)
  DSL_idArray *childNodeLevels = childNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)
  
  //Put the node levels in an Rcpp CharacterVector
  Rcpp::CharacterVector childNodeLevels_cv(childNumLevels);
  for(int i = 0; i < childNumLevels; i++){
    childNodeLevels_cv[i] = childNodeLevels->Subscript(i);
  }

  //We want the same levels info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);       //Parent handles
  int numParents =  parent_handles.NumItems();                       //Number of parent nodes
  
  Rcpp::CharacterVector allNodeNames_cv(1+numParents);  //Container to hold the child and its parent's names 
  allNodeNames_cv[0] = childNodeName;                   //Store the (child) node name

  Rcpp::List nodeLevelsInfo(1+numParents);              //Container to hold the the levels of the child and it's parents
  nodeLevelsInfo[0] = childNodeLevels_cv;
  
  //Loop over the parent nodes and extract names/levels:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    std::string aParentNodeName = aParentNode->Info().Header().GetName();  //Get its name
    allNodeNames_cv[i+1] = aParentNodeName;                                //Store it
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();        //Number of levels (Outcomes)
    DSL_idArray *parentNodeLevels = aParentNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)

    Rcpp::CharacterVector parentNodeLevels_cv(parentNumLevels);  //Store the parent's levels in a CharacterVector 
    for(int j = 0; j < parentNumLevels; j++){
      parentNodeLevels_cv[j] = parentNodeLevels->Subscript(j);
    }
    nodeLevelsInfo[i+1] = parentNodeLevels_cv;                 //Put into a running List
  }
    
  Rcpp::List allInfo = 
      List::create(
          allNodeNames_cv,
          nodeLevelsInfo
      );
         
  return wrap(allInfo);
 
}


/*=================================================*/
/*Bulky but more readable (for me) to have a       */
/*function for utility nodes.                      */
/*Get the levels associated with a utility         */
/*node's parents.                                  */
/*=================================================*/

// [[Rcpp::export]]
List GetLevelsAssociatedWithUtilityNode(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  std::string childNodeName = childNode->Info().Header().GetName();    //Child Node name (cast to a string)

  //We want access to the parent levels. Utility nodes dont have child levels
  DSL_intArray parent_handles = netx->GetParents(node_handle);       //Parent handles
  int numParents =  parent_handles.NumItems();                       //Number of parent nodes
  
  Rcpp::CharacterVector allNodeNames_cv(numParents);  //Container to hold parent's names 

  Rcpp::List nodeLevelsInfo(numParents);              //Container to hold parent levels
  
  //Loop over the parent nodes and extract names/levels:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    std::string aParentNodeName = aParentNode->Info().Header().GetName();  //Get its name
    allNodeNames_cv[i] = aParentNodeName;                                //Store it
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();        //Number of levels (Outcomes)
    DSL_idArray *parentNodeLevels = aParentNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)

    Rcpp::CharacterVector parentNodeLevels_cv(parentNumLevels);  //Store the parent's levels in a CharacterVector 
    for(int j = 0; j < parentNumLevels; j++){
      parentNodeLevels_cv[j] = parentNodeLevels->Subscript(j);
    }
    nodeLevelsInfo[i] = parentNodeLevels_cv;                 //Put into a running List
  }
    
  Rcpp::List allInfo = 
    List::create(
          allNodeNames_cv,
          nodeLevelsInfo
      );
         
  return wrap(allInfo);
 
}

/*===================================================*/
/* Chance or Utility Node state coordinates*/
/*===================================================*/

// [[Rcpp::export]]
IntegerMatrix GetChanceOrUtilityNodeStateCoords(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  
  //Node type for use with decision/utility node handleing below
  const char * nodeType = childNode->Definition()->GetTypeName();
  std::string nodeType_s = nodeType;
  
  //If node is chance, it has levels. 
  int childNumLevels = 0;
  if( nodeType_s == "CPT"){
    //We want to count the node levels and the node's parent levels
    childNumLevels = childNode->Definition()->GetNumberOfOutcomes(); //Number of levels for the child (Outcomes)
  }
  
  //We want the same level count info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
  
  //Container to hold the number of levels.
  //CAREFUL. Don't take decision nodes into account. DO THAT ON THE R SIDE!!!!!!!
  std::vector<int> levelCounts(1);
  if( nodeType_s == "CPT"){                  //For chance node
    levelCounts.resize(1+numParents);
    levelCounts[0] = childNumLevels;
  }
  if( nodeType_s == "TABLE"){               //For utility node
    levelCounts.resize(numParents);
  }
      
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)

    if( nodeType_s == "CPT"){             //For chance node
      levelCounts[i+1] = parentNumLevels;
    }
    if( nodeType_s == "TABLE"){          //For utility node
      levelCounts[i] = parentNumLevels;
    }
    
  }
  
  //Get the indices of each combination of the levels (states):
  int numCoordinates = levelCounts.size();        //Number of coordinates in a state
  DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold the state
  //printIntArray(theCoordinates.Items(), numCoordinates);  

  //Declare a node table (cpt for a chance node) and fill it up
  DSL_Dmatrix *theCpt;
  netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt);  
  int numStates = theCpt->GetItems().GetSize();

  IntegerMatrix stateMat(numStates, numCoordinates);
  for(int i = 0; i < numStates; i++){
    theCpt->IndexToCoordinates(i, theCoordinates);
    //cout << "State " << i << " " <<endl;
    for(int j = 0; j < numCoordinates; j++) {
      stateMat(i,j) = theCoordinates.Items()[j];
    }
    //printIntArray(theCoordinates.Items(), numCoordinates);
    //cout << "==========" << endl;
  }
  

//  double *darray = theCpt->GetItems().Items();       //Grab the doubles array of the DSL_Matrix 
//  NumericVector darray_nv(numStates);
//  
//  for(int i = 0; i < numStates; i++){
//    darray_nv[i] = darray[i];
//  }
  
  return(wrap(stateMat));


}


/*===================================================*/
/*Get the doubles table for chance and utility nodes */
/*NOTE: decision nodes dont have a table             */
/*This is accounted for on the R side                */
/*===================================================*/

// [[Rcpp::export]]
NumericVector GetNodeTable(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  
  //Node type for use with decision/utility node handleing below
  const char * nodeType = childNode->Definition()->GetTypeName();
  std::string nodeType_s = nodeType;
  
  //If node is chance, it has levels. 
  int childNumLevels = 0;
  if( nodeType_s == "CPT"){
    //We want to count the node levels and the node's parent levels
    childNumLevels = childNode->Definition()->GetNumberOfOutcomes(); //Number of levels for the child (Outcomes)
  }
  
  //We want the same level count info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
  
  //Container to hold the number of levels.
  //CAREFUL. Don't take decision nodes into account. DO THAT ON THE R SIDE!!!!!!!
  std::vector<int> levelCounts(1);
  if( nodeType_s == "CPT"){                  //For chance node
    levelCounts.resize(1+numParents);
    levelCounts[0] = childNumLevels;
  }
  if( nodeType_s == "TABLE"){               //For utility node
    levelCounts.resize(numParents);
  }
      
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)

    if( nodeType_s == "CPT"){             //For chance node
      levelCounts[i+1] = parentNumLevels;
    }
    if( nodeType_s == "TABLE"){          //For utility node
      levelCounts[i] = parentNumLevels;
    }
    
  }
  
/*  
  //Get the indices of each combination of the levels (states):
  int numCoordinates = levelCounts.size();        //Number of coordinates in a state
  DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold the state
  //printIntArray(theCoordinates.Items(), numCoordinates);  
*/  

  //Declare a node table (cpt for a chance node) and fill it up
  DSL_Dmatrix *theCpt;
  netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt);  
  int numStates = theCpt->GetItems().GetSize();

/*  
  for(int i = 0; i < numStates; i++){
    theCpt->IndexToCoordinates(i, theCoordinates);
    printIntArray(theCoordinates.Items(), numCoordinates);
    cout << "==========" << endl;
  }
*/

  double *darray = theCpt->GetItems().Items();       //Grab the doubles array of the DSL_Matrix 
  NumericVector darray_nv(numStates);
  
  for(int i = 0; i < numStates; i++){
    darray_nv[i] = darray[i];
  }
    
  //string s = typeid(childNode->Definition()->GetDefinition(&theCpt)).name();
  //cout<< s << endl;
  //DSL_sysCoordinates theCoordinates (*netx.GetNode(nodel_handle)->Definition());
  
  return(wrap(darray_nv));
  
}


/*===================================================*/
/*Set the doubles table for chance and utility nodes */
/*NOTE: decision nodes dont have a table             */
/*This is accounted for on the R side                */
/*===================================================*/

// [[Rcpp::export]]
void SetNodeTable(SEXP net_ptr, SEXP node_name, SEXP node_values) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  
  //Node type for use with decision/utility node handleing below
  const char * nodeType = childNode->Definition()->GetTypeName();
  std::string nodeType_s = nodeType;
  
  //If node is chance, it has levels. If it's utility, it doesn't. 
  int childNumLevels = 0;
  if( nodeType_s == "CPT"){
    //We want to count the node levels and the node's parent levels
    childNumLevels = childNode->Definition()->GetNumberOfOutcomes(); //Number of levels for the child (Outcomes)
  }
  
  //We want the level count info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
    
  //Container to hold the number of levels.
  //CAREFUL. Don't take decision nodes into account. DO THAT ON THE R SIDE!!!!!!!
  std::vector<int> levelCounts(1);
  if( nodeType_s == "CPT"){                  //For chance node
    levelCounts.resize(1+numParents);
  }
  if( nodeType_s == "TABLE"){               //For utility node
    levelCounts.resize(numParents);
  }
      
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)

    if( nodeType_s == "CPT"){             //For chance node
      levelCounts[i+1] = parentNumLevels;
    }
    if( nodeType_s == "TABLE"){          //For utility node
      levelCounts[i] = parentNumLevels;
    }
    
  }
    
  //Get the indices of each combination of the levels (states):
  int numCoordinates = levelCounts.size();        //Number of coordinates in a state (a,b,c,...)  
 
  //Declare a node table (cpt for a chance node) and fill it up
  DSL_Dmatrix *theCpt;        //DSL_nodeDefinition* up  to here
  netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt);  
  int numStates = theCpt->GetItems().GetSize();
  
//   DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold the state
//  for(int i = 0; i < numStates; i++){
//    theCpt->IndexToCoordinates(i, theCoordinates);
//    printIntArray(theCoordinates.Items(), numCoordinates);
//    cout << "==========" << endl;
//  }
  
  //Put the desired values in the node
  //NOTE: ASSUMES vector of node values has been put into default state order for SMILE. If in doubt, check get.table for state order
  NumericVector values(node_values);
  for(int i = 0; i < numStates; i++){
    theCpt->Subscript(i) = values[i];
  } 
  
}
