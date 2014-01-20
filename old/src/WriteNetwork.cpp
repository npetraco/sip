#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
int WriteNetwork(SEXP net_ptr, SEXP filepath, SEXP file_format) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_x(net_ptr);
  
  //Choose the file format. Error handleing is done on the R side
  std::string file_format_s = as<std::string>(file_format);
  int ftype = 0;
  if(file_format_s == "hugin"){
    ftype = DSL_HUGIN_FORMAT;
  }
  if(file_format_s == "netica"){
    ftype = DSL_NETICA_FORMAT;
  }
  if(file_format_s == "interchange"){
    ftype = DSL_INTERCHANGE_FORMAT;
  }
  if(file_format_s == "xdsl"){
    ftype = DSL_XDSL_FORMAT;
  }
  

  //net_ptr_x->WriteFile( (char *)filepath, DSL_HUGIN_FORMAT);
  int error_code = net_ptr_x->WriteFile( CHAR(STRING_ELT(filepath,0)) , ftype);
  
  return error_code;
  
}
