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
  for(int i = 0; i < numNodes; i++){
    //DSL_node *childNode = net_ptr_mod->GetNode(i);
    //std::string childNodeName = childNode->Info().Header().GetName();
    //const char * nodeType = childNode->Definition()->GetTypeName();
    //std::string nodeType_s = nodeType;
    //nodeNames.at(i) = childNodeName;
    //nodeTypes.at(i) = nodeType_s;

    nodeNames[i] = net_ptr_mod->GetNode(i)->Info().Header().GetName();
    nodeTypes[i] = net_ptr_mod->GetNode(i)->Definition()->GetTypeName();
    //cout << typeid(net_ptr_mod->GetNode(i)->Info().Header().GetName()).name() << endl;
    //cout << typeid(net_ptr_mod->GetNode(i)->Definition()->GetTypeName()).name() << endl;
  }

  Rcpp::List nodeInfo = 
      List::create(
          numNodes,
          nodeNames,
          nodeTypes
      );
         
  return wrap(nodeInfo);
}
