// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// S4spr
Rcpp::NumericVector S4spr(Rcpp::S4 fullstack);
RcppExport SEXP FBFoptics_S4spr(SEXP fullstackSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::S4 fullstack = Rcpp::as<Rcpp::S4 >(fullstackSEXP);
        Rcpp::NumericVector __result = S4spr(fullstack);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
