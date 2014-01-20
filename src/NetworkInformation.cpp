#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
void NetworkInfo(SEXP net_ptr) { //Return a List
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  int numNodes = net_ptr_mod->GetNumberOfNodes();
  
  cout<<"SMILE Network Info:"<<endl;
  cout<<"Number of Nodes: "<<numNodes<<endl;
  
  
}
  