#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP AddNode(SEXP net_ptr, SEXP node_name, SEXP node_type, SEXP node_states) {
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
 
  // create node
  int dsl_node_typ = -1;                                 //initialize node type to an impossible value
  std::string node_type_s = as<std::string>(node_type); //Convert node_type SEXP to string
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
  else{
    cout<< "Unknown node type:" << node_type_s << "!" <<endl;
    cout<< "Exiting!!!!" <<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return wrap(-1);
  }
  //Check to see if the dsl_node_typ is still negative. Indicates there still is a problem.
  if(dsl_node_typ < 0){
    cout<< "There was a problem. Execution for pointers out of order??" <<endl;
    cout<< "Exiting!!!!" <<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return wrap(-1);
  }
  
  //cout<< dsl_node_typ << endl;
  
  int node_handel = net_ptr_mod->AddNode( dsl_node_typ, CHAR(STRING_ELT(node_name,0)) ); //Convert node_name to required const char *
  //int node_handel = net_ptr_mod->AddNode( dsl_node_typ, (const char*)node_name ); //DOESN'T WORK FOR scalar SEXP! Shorter alternative to the above line. Just cast the node_name SEXP into a const char*
  //cout<<"Node:         "<< node_name <<endl;
  //cout<<(const char*)node_name<<endl;
  cout<<"Node         "<<CHAR(STRING_ELT(node_name,0))<<endl;
  cout<<"Node handle: "<<node_handel<<endl;
  if(node_handel < 0){
    cout<<"There is a problem with instantiating the node."<<endl;
    cout<<"Execution for pointers out of order??"<<endl;
    cout<<"node_handle is negative. Exiting!!!! "<<endl; //PUT IN PROPER ERROR HANDELING FOR PRODUCTION!
    return wrap(-1);
  }
  
  // setting number (and names) of the states for the node
  DSL_idArray someNames;
  
  someNames.Flush();
  Rcpp::CharacterVector node_states_cv(node_states); //"as" the node_states SEXP into a CharacterVector
  for(int i = 0; i < node_states_cv.length(); i++){
    //cout<< (const char*)node_states_cv[i] <<endl;
    someNames.Add(node_states_cv[i]); //Each CharacterVector elem can be cast into the required const char*
  }
  
  net_ptr_mod->GetNode( node_handel )->Definition()->SetNumberOfOutcomes(someNames);
  
  //net_ptr_mod->WriteFile("/Users/npetraco/codes/R/sip/tests/anet.net", DSL_HUGIN_FORMAT);
  //DSL_network newNet = *net_ptr_mod;
  //newNet.WriteFile("/Users/npetraco/codes/R/sip/tests/anet.net");

  return net_ptr_mod;
  
}
