#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP CreateSmlieNetwork() {
  
  //Declare a SMILE network object
  DSL_network theNet;
  
  //Wrap it in an external pointer and return it for later use:
  const Rcpp::XPtr<DSL_network> theNet_ptr( new DSL_network(), true ); //See Modules vignette, pp. 2
  
  //PUT IN APPROPRIATE ERROR TRAPS FOR PRODUCTION!!!!

  return theNet_ptr ;
}
