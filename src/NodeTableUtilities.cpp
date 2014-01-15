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
  //cout<<"Number of parents: "<<numParents<<endl;
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    std::string aParentNodeName = aParentNode->Info().Header().GetName();  //Get its name
    allNodeNames_cv[i] = aParentNodeName;                                //Store it
    //cout << aParentNodeName << endl;
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();        //Number of levels (Outcomes)
    DSL_idArray *parentNodeLevels = aParentNode->Definition()->GetOutcomesNames(); //Node levels (Outcomes)

    Rcpp::CharacterVector parentNodeLevels_cv(parentNumLevels);  //Store the parent's levels in a CharacterVector 
    for(int j = 0; j < parentNumLevels; j++){
      parentNodeLevels_cv[j] = parentNodeLevels->Subscript(j);
      //cout << "    " <<parentNodeLevels_cv[j] << endl;
    }
    nodeLevelsInfo[i] = parentNodeLevels_cv;                 //Put into a running List
  }
    
  Rcpp::List allInfo;
  allInfo = List::create(
         Rcpp::Named("Names")= allNodeNames_cv,
         Rcpp::Named("Levels")= nodeLevelsInfo
         );
         
  return wrap(allInfo);
 
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
  IntegerVector levelCounts;
  if( nodeType_s == "CPT"){                  //For chance node
    IntegerVector levelCounts(1+numParents);  //Is there a better way to do this other than redeclairing??
    levelCounts[0] = childNumLevels;
  }
  if( nodeType_s == "TABLE"){               //For utility node
    IntegerVector levelCounts(numParents);
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
  //printArray(levelCounts, levelCounts.size());
  
/*  
  //Get the indices of each combination of the levels (states):
  int numCoordinates = levelCounts.size();        //Number of coordinates in a state
  DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold the state
  //printIntArray(theCoordinates.Items(), numCoordinates);  
*/  

  //if(node_type_s == "LIST"){ //The node is a decision node. There is not table. Check for this on the R side
  //  
  //}

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



/*===================================================*/
/*Set the doubles table for chance and utility nodes */
/*NOTE: decision nodes dont have a table             */
/*This is accounted for on the R side                */
/*===================================================*/

// [[Rcpp::export]]
void SetNodeTable(SEXP net_ptr, SEXP node_name) {
  
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
  
  cout<<childNumLevels<<endl;
  
  //We want the level count info for the parent nodes:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
  
  cout<<numParents<<endl;
  
  //Container to hold the number of levels.
  //CAREFUL. Don't take decision nodes into account. DO THAT ON THE R SIDE!!!!!!!
  IntegerVector levelCounts_chance(1+numParents);  //Is there a better way to do this other than declairing two. Declaration in the if block does not compile
  IntegerVector levelCounts_utility(numParents);
  std::vector<int> lci(1);
  if( nodeType_s == "CPT"){                  //For chance node
    cout<<"Do I make it in here??"<<endl;
    lci.resize(10);
    cout<<"Resized: "<< lci.size() << endl;
    levelCounts_chance[0] = childNumLevels;
    cout<<levelCounts_chance[0]<<endl;
    cout<<"And here??"<<endl;
  }
  //if( nodeType_s == "TABLE"){               //For utility node
  //  IntegerVector levelCounts(numParents);
  //}
  cout<<levelCounts_chance[0]<<endl;
  cout<<"Or here??"<<endl;

    
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)

    if( nodeType_s == "CPT"){             //For chance node
      levelCounts_chance[i+1] = parentNumLevels;
    }
    if( nodeType_s == "TABLE"){          //For utility node
      levelCounts_utility[i] = parentNumLevels;
    }
    
  }
  cout<<levelCounts_chance.size()<<endl;
  //printArray(levelCounts, levelCounts.size());
  
  
  //Get the indices of each combination of the levels (states):
  int numCoordinates = 0;
  if(nodeType_s == "CPT"){
    numCoordinates = levelCounts_chance.size();        //Number of coordinates in a state
  }
  if(nodeType_s == "TABLE"){
    numCoordinates = levelCounts_utility.size();        //Number of coordinates in a state
  }
  
  DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold the state
  //printIntArray(theCoordinates.Items(), numCoordinates);  
  cout<<numCoordinates<<endl;

  //Declare a node table (cpt for a chance node) and fill it up
  DSL_Dmatrix *theCpt;        //DSL_nodeDefinition* up  to here
  netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt);  
  int numStates = theCpt->GetItems().GetSize();

/*  
  for(int i = 0; i < numStates; i++){
    theCpt->IndexToCoordinates(i, theCoordinates);
    printIntArray(theCoordinates.Items(), numCoordinates);
    cout << "==========" << endl;
  }


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
    
  //string s = typeid(netx->GetNode(node_handle)->Definition()).name();
  //cout<< s << endl;
  //DSL_sysCoordinates theCoordinates (*netx.GetNode(nodel_handle)->Definition());
  
  return(wrap(darray_nv));
*/  
}
