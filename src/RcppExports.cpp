// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// AddArc
int AddArc(SEXP net_ptr, SEXP parent_node_name, SEXP child_node_name);
RcppExport SEXP sip_AddArc(SEXP net_ptrSEXP, SEXP parent_node_nameSEXP, SEXP child_node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP parent_node_name = Rcpp::as<SEXP >(parent_node_nameSEXP);
        SEXP child_node_name = Rcpp::as<SEXP >(child_node_nameSEXP);
        int __result = AddArc(net_ptr, parent_node_name, child_node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// AddNode
int AddNode(SEXP net_ptr, SEXP node_name, SEXP node_type, SEXP node_states);
RcppExport SEXP sip_AddNode(SEXP net_ptrSEXP, SEXP node_nameSEXP, SEXP node_typeSEXP, SEXP node_statesSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        SEXP node_type = Rcpp::as<SEXP >(node_typeSEXP);
        SEXP node_states = Rcpp::as<SEXP >(node_statesSEXP);
        int __result = AddNode(net_ptr, node_name, node_type, node_states);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// CreateNetwork_testing_func
int CreateNetwork_testing_func();
RcppExport SEXP sip_CreateNetwork_testing_func() {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        int __result = CreateNetwork_testing_func();
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// CreateSmlieNetwork
SEXP CreateSmlieNetwork();
RcppExport SEXP sip_CreateSmlieNetwork() {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP __result = CreateSmlieNetwork();
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// DeleteArc
int DeleteArc(SEXP net_ptr, SEXP parent_node_name, SEXP child_node_name);
RcppExport SEXP sip_DeleteArc(SEXP net_ptrSEXP, SEXP parent_node_nameSEXP, SEXP child_node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP parent_node_name = Rcpp::as<SEXP >(parent_node_nameSEXP);
        SEXP child_node_name = Rcpp::as<SEXP >(child_node_nameSEXP);
        int __result = DeleteArc(net_ptr, parent_node_name, child_node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// DeleteNode
int DeleteNode(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_DeleteNode(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        int __result = DeleteNode(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// ErrorCode2String
std::string ErrorCode2String(SEXP error_code_);
RcppExport SEXP sip_ErrorCode2String(SEXP error_code_SEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP error_code_ = Rcpp::as<SEXP >(error_code_SEXP);
        std::string __result = ErrorCode2String(error_code_);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// ErrorMessages
List ErrorMessages(SEXP net_ptr);
RcppExport SEXP sip_ErrorMessages(SEXP net_ptrSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        List __result = ErrorMessages(net_ptr);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// NetworkInfo
List NetworkInfo(SEXP net_ptr);
RcppExport SEXP sip_NetworkInfo(SEXP net_ptrSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        List __result = NetworkInfo(net_ptr);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// GetLevelsAssociatedWithChanceOrDecisionNode
List GetLevelsAssociatedWithChanceOrDecisionNode(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_GetLevelsAssociatedWithChanceOrDecisionNode(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        List __result = GetLevelsAssociatedWithChanceOrDecisionNode(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// GetLevelsAssociatedWithUtilityNode
List GetLevelsAssociatedWithUtilityNode(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_GetLevelsAssociatedWithUtilityNode(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        List __result = GetLevelsAssociatedWithUtilityNode(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// GetChanceOrUtilityNodeStateCoords
IntegerMatrix GetChanceOrUtilityNodeStateCoords(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_GetChanceOrUtilityNodeStateCoords(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        IntegerMatrix __result = GetChanceOrUtilityNodeStateCoords(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// GetNodeTable
NumericVector GetNodeTable(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_GetNodeTable(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        NumericVector __result = GetNodeTable(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// SetNodeTable
void SetNodeTable(SEXP net_ptr, SEXP node_name, SEXP node_values);
RcppExport SEXP sip_SetNodeTable(SEXP net_ptrSEXP, SEXP node_nameSEXP, SEXP node_valuesSEXP) {
BEGIN_RCPP
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        SEXP node_values = Rcpp::as<SEXP >(node_valuesSEXP);
        SetNodeTable(net_ptr, node_name, node_values);
    }
    return R_NilValue;
END_RCPP
}
// NodeType
std::string NodeType(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_NodeType(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        std::string __result = NodeType(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// NodeExistsQ
int NodeExistsQ(SEXP net_ptr, SEXP node_name);
RcppExport SEXP sip_NodeExistsQ(SEXP net_ptrSEXP, SEXP node_nameSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP node_name = Rcpp::as<SEXP >(node_nameSEXP);
        int __result = NodeExistsQ(net_ptr, node_name);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// WriteNetwork
int WriteNetwork(SEXP net_ptr, SEXP filepath, SEXP file_format);
RcppExport SEXP sip_WriteNetwork(SEXP net_ptrSEXP, SEXP filepathSEXP, SEXP file_formatSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP filepath = Rcpp::as<SEXP >(filepathSEXP);
        SEXP file_format = Rcpp::as<SEXP >(file_formatSEXP);
        int __result = WriteNetwork(net_ptr, filepath, file_format);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// ReadNetwork
int ReadNetwork(SEXP net_ptr, SEXP filepath, SEXP file_format);
RcppExport SEXP sip_ReadNetwork(SEXP net_ptrSEXP, SEXP filepathSEXP, SEXP file_formatSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        SEXP net_ptr = Rcpp::as<SEXP >(net_ptrSEXP);
        SEXP filepath = Rcpp::as<SEXP >(filepathSEXP);
        SEXP file_format = Rcpp::as<SEXP >(file_formatSEXP);
        int __result = ReadNetwork(net_ptr, filepath, file_format);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
