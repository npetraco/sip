#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
void PopulateNode(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr, i.e. a smart (Rcpp) pointer to the network
  Rcpp::XPtr<DSL_network> netx(net_ptr);
  
  int node_handle = netx->FindNode( CHAR(STRING_ELT(node_name,0)) );
  DSL_node *theNode = netx->GetNode(node_handle);                    //Pointer to the node object
  DSL_intArray parent_handles = netx->GetParents(node_handle);
  cout << parent_handles.GetSize()  << endl;
  cout << parent_handles.NumItems()  << endl;
  //DSL_Dmatrix *theCpt;
  //cout << netx->GetNode(node_handle)->Definition()->GetDefinition(&theCpt) << endl;
  //DSL_sysCoordinates theCoordinates (*netx.GetNode(nodel_handle)->Definition());
  
}
