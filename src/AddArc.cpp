#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP AddArc(SEXP net_ptr, SEXP parent_node_name, SEXP child_node_name) {
//SEXP AddArc(SEXP net_ptr, int parent_node_handle, int child_node_handle) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  //Connect the nodes with an edge  ****KEEP TRACK OF THE NODE HANDLES ON THR R SIDE
  //net_ptr_mod->AddArc(parent_node_handle,child_node_handle); //HAVE TO USE NODE HANDLES.
  //net_ptr_mod->AddArc(net_ptr_mod->GetNode(0)->Handle(),net_ptr_mod->GetNode(1)->Handle());
  int parent_node_handle = net_ptr_mod->FindNode( CHAR(STRING_ELT(parent_node_name,0)) );
  int child_node_handle = net_ptr_mod->FindNode( CHAR(STRING_ELT(child_node_name,0)) );
  //cout<< parent_node_handle <<endl;
  //cout<< child_node_handle <<endl;  
  net_ptr_mod->AddArc(parent_node_handle,child_node_handle); //HAVE TO USE NODE HANDLES.
  
  return net_ptr_mod;
  
}
