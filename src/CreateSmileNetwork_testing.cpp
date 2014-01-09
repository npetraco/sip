#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
int CreateNetwork_testing_func() {
  
  DSL_network theNet;
  
  // create node "Success"
  int success = theNet.AddNode(DSL_CPT,"Success");
  //Rcout<<success<<endl;
  
  // setting number (and name) of outcomes
  DSL_idArray someNames;
  someNames.Add("Success");
  someNames.Add("Failure");
  theNet.GetNode(success)->Definition()->SetNumberOfOutcomes(someNames);  
  
  // create node "Forecast"
  int forecast = theNet.AddNode(DSL_CPT,"Forecast");
  
  // setting number (and name) of outcomes
  someNames.Flush();
  someNames.Add("Good");
  someNames.Add("Moderate");
  someNames.Add("Poor");
  theNet.GetNode(forecast)->Definition()->SetNumberOfOutcomes(someNames);
  
  // add arc from "Success" to "Forecast"
  theNet.AddArc(success,forecast);
  
  theNet.WriteFile("/Users/npetraco/codes/R/sip/tests/anet.net");
  
  return 1;
  
}