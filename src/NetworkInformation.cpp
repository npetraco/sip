#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
List NetworkInfo(SEXP net_ptr) { //Return a List. Clean it up on the R side
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  int numNodes = net_ptr_mod->GetNumberOfNodes();
  
  std::vector<std::string> nodeNames(numNodes);
  std::vector<std::string> nodeTypes(numNodes);
  std::vector<DSL_intArray> childHandleVec(numNodes);
  std::vector<int> childCountVec(numNodes, 0);
  
  List edgelist(numNodes);
  
  for(int i = 0; i < numNodes; i++){
    
    nodeNames[i] = net_ptr_mod->GetNode(i)->Info().Header().GetName();
    nodeTypes[i] = net_ptr_mod->GetNode(i)->Definition()->GetTypeName();
    
    childHandleVec[i] = net_ptr_mod->GetChildren(i);            //Handles of node's children
    childCountVec[i] =  net_ptr_mod->GetChildren(i).NumItems(); //Number of children for node i
    
    IntegerVector tmp(childCountVec[i]);
    for(int j = 0; j < childCountVec[i]; j++){
      int chidx = 1+childHandleVec[i][j];      //Index (NOT HANDLE) of a node's child
      //cout << "Node#: " << i+1 << " "<<nodeNames[i] <<". Child " << j+1 <<" node# is: " << chidx+1 << " " << nodeNames[chidx] << endl;
      tmp[j] = chidx;
    }
    edgelist[i] = tmp;
  }
  
  Rcpp::List nodeInfo = 
      List::create(
          numNodes,
          nodeNames,
          nodeTypes,
          childCountVec,
          edgelist
      );
         
  return wrap(nodeInfo);
}
