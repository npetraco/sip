#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
int AddArc(SEXP net_ptr, SEXP parent_node_name, SEXP child_node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  //Connect the nodes with an edge
  int parent_node_handle = net_ptr_mod->FindNode( CHAR(STRING_ELT(parent_node_name,0)) );
  int child_node_handle = net_ptr_mod->FindNode( CHAR(STRING_ELT(child_node_name,0)) );
  //cout<< parent_node_handle <<endl;
  //cout<< child_node_handle <<endl;  
  net_ptr_mod->AddArc(parent_node_handle,child_node_handle); //HAVE TO USE NODE HANDLES.
  
  //return net_ptr_mod;
  return 0; //IMPLEMENT SMILE SIDE ERROR HANDLEING FOR PRODUCTION!!!!!!!!
  
}
