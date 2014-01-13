#include <iostream>
#include <Rcpp.h>
#include "smile.h"
#include "PrintUtilities.h"

using namespace Rcpp;
using namespace std;

/*==============================================*/
/*Get the levels associated with the node and   */
/*the levels associated with the node's parents */
/*==============================================*/

// [[Rcpp::export]]
List GetLevelsAssociatedWithNode(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  std::string childNodeName = childNode->Info().Header().GetName();    //Child Node name (cast to a string)

  //We want access to the node levels, nodes parent levels
  int childNumLevels = childNode->Definition()->GetNumberOfOutcomes();        //Number of levels for the child (Outcomes)
  DSL_idArray *childNodeLevels = childNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)
  
  //cout << nodeName << endl;
  //cout << "Number of levels: " << numLevels << endl;
  
  //Put the node levels in an Rcpp CharacterVector
  Rcpp::CharacterVector childNodeLevels_cv(childNumLevels);
  for(int i = 0; i < childNumLevels; i++){
    childNodeLevels_cv[i] = childNodeLevels->Subscript(i);
    //cout << nodeLevels_cv[i] << endl;
  }

  //We want the same levels info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);       //Parent handles
  int numParents =  parent_handles.NumItems();                       //Number of parent nodes
  
  Rcpp::CharacterVector allNodeNames_cv(1+numParents);  //Container to hold the child and its parent's names 
  allNodeNames_cv[0] = childNodeName;                   //Store the (child) node name

  Rcpp::List nodeLevelsInfo(1+numParents);              //Container to hold the the levels of the child and it's parents
  nodeLevelsInfo[0] = childNodeLevels_cv;
  
  //Loop over the parent nodes and extract names/levels:
  //cout<<"Number of parents: "<<numParents<<endl;
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    std::string aParentNodeName = aParentNode->Info().Header().GetName();  //Get its name
    allNodeNames_cv[i+1] = aParentNodeName;                                //Store it
    //cout << aParentNodeName << endl;
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();        //Number of levels (Outcomes)
    DSL_idArray *parentNodeLevels = aParentNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)

    Rcpp::CharacterVector parentNodeLevels_cv(parentNumLevels);  //Store the parent's levels in a CharacterVector 
    for(int j = 0; j < parentNumLevels; j++){
      parentNodeLevels_cv[j] = parentNodeLevels->Subscript(j);
      //cout << "    " <<parentNodeLevels_cv[j] << endl;
    }
    nodeLevelsInfo[i+1] = parentNodeLevels_cv;                 //Put into a running List
  }
    
  Rcpp::List allInfo;
  allInfo = List::create(
         Rcpp::Named("Names")= allNodeNames_cv,
         Rcpp::Named("Levels")= nodeLevelsInfo
         );
         
  return wrap(allInfo);
 
}


/*==============================================*/
/*Get the doubles table for the node            */
/*==============================================*/

// [[Rcpp::export]]
NumericVector GetNodeTable(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  
  //We want to count the node levels and the node's parent levels
  int childNumLevels = childNode->Definition()->GetNumberOfOutcomes(); //Number of levels for the child (Outcomes)
  
  //We want the same level count info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
  
  //Container to hold the number of levels for the node and its parents:
  IntegerVector levelCounts(1+numParents);
  levelCounts[0] = childNumLevels;
    
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)
    levelCounts[i+1] = parentNumLevels;

  }
  //printArray(levelCounts, levelCounts.size());
  
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
  //cout << numStates << endl;
  //printArray(darray, numStates);
  NumericVector darray_nv(numStates);
  //printArray(darray_nv, numStates);
  
  for(int i = 0; i < numStates; i++){
    darray_nv[i] = darray[i];
  }
  //printArray(darray_nv, numStates);
  //cout << darray_nv[0] << endl;
    
  //string s = typeid(childNode->Definition()->GetDefinition(&theCpt)).name();
  //cout<< s << endl;
  //DSL_sysCoordinates theCoordinates (*netx.GetNode(nodel_handle)->Definition());
  
  return(wrap(darray_nv));
  
}