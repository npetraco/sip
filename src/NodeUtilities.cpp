#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

/*==============================================*/
/*Probe the node type.                          */
/*Handy so as not to apply illeagle opperations */
/*on that node                                  */
/*==============================================*/

// [[Rcpp::export]]
std::string NodeType(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *childNode = netx->GetNode(node_handle);                    //Pointer to the child node object
  
  //int nodeType = childNode->Definition()->GetType();
  const char * nodeType = childNode->Definition()->GetTypeName();
  
  //cout << nodeType << endl;
  std::string nodeType_s = nodeType;
  
  return(nodeType);
  
}

/*==============================================*/
/*Ask the network if the node exists.          */
/*==============================================*/

// [[Rcpp::export]]
int NodeExistsQ(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  
  if(node_handle == DSL_OUT_OF_RANGE) { 
    //cout << "No Node By That Name!!" << endl;
    return(DSL_OUT_OF_RANGE);
  } else {
    return (1);
  }

}
