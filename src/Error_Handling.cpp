#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

/*============================================*/
/*Turn DSL error code into it's corresponding */
/*error variable name                         */
/*============================================*/

// [[Rcpp::export]]
std::string ErrorCode2String(SEXP error_code_) {
    
  int error_code = as<int>(error_code_);
  
  //From the error.h file
  if(error_code == 0){
    return "DSL_OKAY";
  }
  if(error_code == -1){
    return  "DSL_GENERAL_ERROR";
  }
  if(error_code == -2){
    return  "DSL_OUT_OF_RANGE";
  }
  if(error_code == -3){
    return "DSL_NO_ITEM";
  }
  if(error_code == -4){
    return "DSL_INVALID_VALUE";
  }
  if(error_code == -5){
    return "DSL_NO_USEFUL_SAMPLES";
  }
  if(error_code == -6){
    return "DSL_CANT_SOLVE_EQUATION";
  }
  if(error_code == -11){
    return "DSL_CYCLE_DETECTED";
  }
  if(error_code == -19){
    return "DSL_WRONG_NUM_STATES";
  }
  if(error_code == -26){
    return "DSL_CONFLICTING_EVIDENCE";
  }
  if(error_code == -30){
    return "DSL_ILLEGAL_ID";
  }
  if(error_code == -32){
    return "DSL_DUPLICATED_ID";
  }
  if(error_code == -42){
    return "DSL_OUT_OF_MEMORY";
  }
  if(error_code == -43){
    return "DSL_ZERO_POTENTIAL";
  }
  if(error_code == -51){
    return "DSL_WRONG_NODE_TYPE";
  }
  if(error_code == -52){
    return "DSL_WRONG_ELEMENT_TYPE";
  }
  if(error_code == -53){
    return "DSL_WRONG_MESSAGE_TYPE";
  }
  if(error_code == -54){
    return "DSL_WRONG_SAMPLENODE_TYPE";
  }
  if(error_code == -99){
    return "DSL_INTERRUPTED";
  }  
  //textfile
  if(error_code == -100){
    return "DSL_FILE_READ";
  }
  if(error_code == -101){
    return "DSL_FILE_WRITE";
  }
  if(error_code == -102){
    return "DSL_END_OF_FILE";
  }
  if(error_code == -103){
    return "DSL_WRONG_FILE";
  }
  // lexical/syntactical
  if(error_code == -111){
    return "DSL_NO_MORE_TOKENS";
  }
  if(error_code == -126){
    return "DSL_LEXICAL_ERROR";
  }
  if(error_code == -127){
    return "DSL_SYNTAX_ERROR";
  }
  if(error_code == -128){
    return "DSL_UNEXPECTED_EOF";
  }
  if(error_code == -129){
    return "DSL_FIELD_NOT_FOUND";
  }
  if(error_code == -567){
    return "DSL_OBJECT_NOT_READY";
  }
  if(error_code == -568){
    return "DSL_OBJECT_NOT_CONSISTENT";
  } else{
    //cout << error_code << endl;
    //Rcout << error_code << endl;
    return "NOT AN ERROR CODE";
  }
 
}

/*============================================*/
/*Return Rcpp List of DSL error messages for  */
/*printing on the R side                      */
/*                                            */
/*Only spits out errors if the network the    */
/*external pointer is pointing at has an error*/
/*============================================*/

// [[Rcpp::export]]
List ErrorMessages(SEXP net_ptr){
  
  //"as" the pointer sent in into a Rcpp Xptr 
  Rcpp::XPtr<DSL_network> net_ptr_mod(net_ptr);
  
  int num_errors = net_ptr_mod->ErrorHandler().GetNumberOfErrors();
  Rcpp::CharacterVector error_messages(num_errors);
  Rcpp::IntegerVector error_codes(num_errors);
  
  for(int i = 0; i<num_errors; i++){
    error_messages[i] = net_ptr_mod->ErrorHandler().GetErrorMessage(i);
    error_codes[i] = net_ptr_mod->ErrorHandler().GetError(i);
  }
  //std::string error_message = net_ptr_mod->ErrorHandler().GetErrorMessage();
  
  Rcpp::List errorInfo = 
      List::create(
          num_errors,
          error_codes,
          error_messages
      );
         
  return wrap(errorInfo);
  
}
