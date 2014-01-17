#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
void DeleteNode(SEXP net_ptr, SEXP node_name) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);  
  int node_handle = net_ptr_mod->FindNode( CHAR(STRING_ELT(node_name,0)) );
  net_ptr_mod->DeleteNode( node_handle );
  
}