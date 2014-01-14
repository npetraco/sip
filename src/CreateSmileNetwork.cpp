#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP CreateSmlieNetwork() {
  
  //Declare a SMILE network object
  DSL_network network;
  
  //Wrap it in an Rcpp external pointer and return it for later use:
  // SHOULD const BE SOMEWHERE TO KEEP POINTER CONSTANT?????
  Rcpp::XPtr<DSL_network> network_ptr( new DSL_network(), true ); //See Modules vignette, pp. 2
  
  //NOTE: ERROR TRAPS are on the R side, i.e. create.network()
  
  //Return the pointer. What it's poiting at can be modified by simply sending 
  //it into the various cpp and R wrappers
  return network_ptr;
  
}
