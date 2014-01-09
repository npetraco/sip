#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
void WriteNetwork(SEXP net_ptr, SEXP filepath) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_x(net_ptr);

  //net_ptr_x->WriteFile( (char *)filepath, DSL_HUGIN_FORMAT);
  net_ptr_x->WriteFile( CHAR(STRING_ELT(filepath,0)) , DSL_HUGIN_FORMAT);
  
}