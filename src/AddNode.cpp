#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
int AddNode(SEXP net_ptr, SEXP node_name, SEXP node_type, SEXP node_states) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
 
  // create node
  int dsl_node_typ = -1;                                 //initialize node type to an impossible value
  std::string node_type_s = as<std::string>(node_type); //Convert node_type SEXP to string 
  std::transform(node_type_s.begin(), node_type_s.end(), node_type_s.begin(), ::tolower); //Make lowercase
  
  if( node_type_s == "chance" ){
    dsl_node_typ = DSL_CPT;
  }
  else if ( node_type_s == "decision"){
    dsl_node_typ = DSL_LIST;
  }
  else if ( node_type_s == "utility"){
    dsl_node_typ = DSL_TABLE;
  }
  else if ( node_type_s == "logical"){
    dsl_node_typ = DSL_TRUTHTABLE;
  }
  else if ( node_type_s == "multi"){
    //API: This node represents a continuous linearly additive utility function, i.e. a linear combination of its parents.
    dsl_node_typ = DSL_MAU;
  }
  else{ //FOR PRODUCTION PUT THIS ON THE R SIDE
    cout<< "Unknown node type:" << node_type_s << "!" <<endl;
    cout<< "Exiting!!!!" <<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return -1;
  }
  //Check to see if the dsl_node_typ is still negative. Indicates there still is a problem.
  if(dsl_node_typ < 0){
    cout<< "There was a problem. Execution for pointers out of order??" <<endl;
    cout<< "Exiting!!!!" <<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return -1;
  }
  
  //cout<< dsl_node_typ << endl;
  
  //Add the node
  //NOTE: if an error occurs, node_handle is the ERROR CODE
  int node_handle = net_ptr_mod->AddNode( dsl_node_typ, CHAR(STRING_ELT(node_name,0)) ); //Convert node_name to required const char *

  //PRODUCTION: SHIFT THIS OVER TO THE R SIDE
  cout<<"Added Node:  "<<CHAR(STRING_ELT(node_name,0))<<endl;
  cout<<"Node handle: "<<node_handle<<endl;
  
  if(node_handle < 0){
    cout<<"There is a problem with instantiating the node."<<endl;
    cout<<"Execution for pointers out of order??"<<endl;
    cout<<"node_handle is negative. Error code: " << node_handle << " Exiting!!!! "<<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return node_handle;
  }  

  
  // Setting number (and names) of the states for the node
  
  //If the node is a utlity node, it does not have states. Just return.
  if(node_type_s == "utility") {
    //return net_ptr_mod;
    return node_handle;
  }
  
  //If the node is a chance or decision node, put names to the states
  DSL_idArray someNames;
  
  someNames.Flush();
  Rcpp::CharacterVector node_states_cv(node_states); //"as" the node_states SEXP into a CharacterVector
  int errcod = 0;
  for(int i = 0; i < node_states_cv.length(); i++){
    //cout<< (const char*)node_states_cv[i] <<endl;
    errcod = someNames.Add(node_states_cv[i]); //Each CharacterVector elem can be cast into the required const char*
    if(errcod<0){
      return errcod; //PRODUCTION ADD ERROR HANDLER
    }
  }
  
  //Think the return val for this (i.e. DSL_nodeDefinition::SetNumberOfOutcomes) is an ERROR CODE. 
  errcod = net_ptr_mod->GetNode( node_handle )->Definition()->SetNumberOfOutcomes(someNames);
  if(errcod<0){
    return errcod; //PRODUCTION ADD ERROR HANDLER
  }
  
  return node_handle;  //Again, node_handle is the node index OR a DSL ERROR CODE if there was a problem.
  
}
