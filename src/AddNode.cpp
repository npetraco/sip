#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP AddNode(SEXP net_ptr, SEXP node_name, SEXP node_type, SEXP node_states) {
  
  //as the pointer sent in to a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  //as the node name to a C++ string
  //std::vector<std::string> nde_nme;// = as<string>(node_name);
  
  // create node  
  int node_handel = net_ptr_mod->AddNode(DSL_CPT,"SUCCESS");
  //int node_handel = net_ptr_mod->AddNode(DSL_CPT,nde_nme);
  //Rcout<<"got back "<< ndn <<endl;
  
  // setting number (and name) of outcomes
  //DSL_idArray someNames;
  //someNames.Add("Success");
  //someNames.Add("Failure");
  //theNet.GetNode(success)->Definition()->SetNumberOfOutcomes(someNames);  

  
  return net_ptr_mod;
  
}