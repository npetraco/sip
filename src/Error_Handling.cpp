#include <iostream>
#include <Rcpp.h>
#include "smile.h"

using namespace Rcpp;
using namespace std;

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
 } else{
   return "NOT AN ERROR CODE";
 }
 
//textfile
/*
#define DSL_FILE_READ         -100
#define DSL_FILE_WRITE        -101
#define DSL_END_OF_FILE       -102   
#define DSL_WRONG_FILE        -103

// lexical/syntactical
#define DSL_NO_MORE_TOKENS        -111
#define DSL_LEXICAL_ERROR         -126
#define DSL_SYNTAX_ERROR          -127
#define DSL_UNEXPECTED_EOF        -128
#define DSL_FIELD_NOT_FOUND       -129

#define DSL_OBJECT_NOT_READY      -567
#define DSL_OBJECT_NOT_CONSISTENT -568
*/
  
}
