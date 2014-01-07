#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP AddNode(SEXP net_ptr, SEXP node_name, SEXP node_type, SEXP node_states) {
  
  //DSL_network theNet = *net_ptr;
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  // create node
  //int success = 1035;
  int node_handel = net_ptr_mod->AddNode(DSL_CPT,"Success");
  //Rcout<<"got back"<<success<<endl;
  
  // setting number (and name) of outcomes
  //DSL_idArray someNames;
  //someNames.Add("Success");
  //someNames.Add("Failure");
  //theNet.GetNode(success)->Definition()->SetNumberOfOutcomes(someNames);  

  
  return net_ptr_mod;
  
}