#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

/*=================================================*/
//Get the coordinates 
/*=================================================*/

// [[Rcpp::export]]
void NodeStates(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *node_ptr = netx->GetNode(node_handle);
  
  //Node type for use with decision/utility node handleing below
  const char * nodeType = node_ptr->Definition()->GetTypeName();
  std::string nodeType_s = nodeType;
  
  //If node is chance or decision, it has more than 1 level. See how many.
  int nodeNumLevels = 1; //Utility nodes only have one "level"
  if( nodeType_s == "CPT" || nodeType_s == "LIST"){
    //We want to count the node levels and the node's parent levels
    nodeNumLevels = node_ptr->Definition()->GetNumberOfOutcomes(); //Number of levels for the child (Outcomes)
  }
  //cout<<"nodeNumLevels: "<<nodeNumLevels<<endl;
  
  //We want the number of levels for each parent node too. (Utility nodes cant be parents, so don't worry about these)
  //First see how many parent nodes there are:
  DSL_intArray parent_handles = netx->GetParents(node_handle);         //Get Parent handles
  int numParents =  parent_handles.NumItems();                         //Number of parent nodes
  
  //STL Container to hold the number of levels for the node and its parents.
  std::vector<int> levelCounts(1);
  if( nodeType_s == "CPT" || nodeType_s == "LIST" ){                  //For chance/decision node
    levelCounts.resize(1+numParents);
    levelCounts[0] = nodeNumLevels;
  }
  if( nodeType_s == "TABLE"){               //For utility node
    levelCounts.resize(numParents);
  }
      
  //Loop over the parent nodes and extract level counts:
  for(int i = 0; i < numParents; i++){         
    DSL_node *aParentNode = netx->GetNode( parent_handles.Subscript(i) );  //Grab a parent node
    
    int parentNumLevels = aParentNode->Definition()->GetNumberOfOutcomes();//Number of levels (Outcomes)

    //cout<<"nodeType_s:      "<<nodeType_s<<endl;
    //cout<<"parentNumLevels: "<<parentNumLevels<<endl;
    if( nodeType_s == "CPT" || nodeType_s == "LIST"){             //For chance node
      levelCounts[i+1] = parentNumLevels;
    }
    if( nodeType_s == "TABLE"){          //For utility node
      levelCounts[i] = parentNumLevels;
    }
    
  }

  //Get the indices of each combination of the levels (states):
  int numCoordinates = levelCounts.size();        //Number of coordinates in a state
  DSL_intArray theCoordinates(numCoordinates);    //Declare a DSL_intArray to hold each state (tuple)
  //printIntArray(theCoordinates.Items(), numCoordinates);
 
 //Compute the number of rows in the node table
 int numStates = std::accumulate(levelCounts.begin(), levelCounts.end(), 1, std::multiplies<int>());
 cout<< "# of states: " <<numStates<<endl;
 
 //DSL_Dmatrix *theCpt;
 //netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt);  
 //int numStates = theCpt->GetItems().GetSize();
 //DSL_nodeDefinition *node_def_ptr = netx->GetNode(node_handle)->Definition();
 //node_def_ptr<-IndexToCoordinates(1, theCoordinates);
 //printIntArray(theCoordinates.Items(), numCoordinates);
 
 
/*  
  for(int i = 0; i < numStates; i++){
    theCpt->IndexToCoordinates(i, theCoordinates);
    printIntArray(theCoordinates.Items(), numCoordinates);
    cout << "==========" << endl;
  }
*/

}