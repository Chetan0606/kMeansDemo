#include "kmeans.h"
#include "gmm.h"
#include <R_ext/Rdynload.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif
//void euclidean_distance_interface(
//    const double* point1, const double* point2, int* p)
//{
//  euclidean_distance(point1, point2, *p);
//}

RcppExport SEXP euclidean_distance_interface(SEXP point1SEXP, SEXP point2SEXP, SEXP pSEXP) {
  BEGIN_RCPP
    NumericVector point1(point1SEXP);
    NumericVector point2(point2SEXP);
    int p = as<int>(pSEXP);
    
    // Create raw pointers to the NumericVector data
    const double* point1_ptr = REAL(point1);
    const double* point2_ptr = REAL(point2);
    
    // Call the C++ function and get the result
    double result = euclidean_distance(point1_ptr, point2_ptr, p);
    
    // Return the result to R
    return wrap(result);
  
  END_RCPP
}

//void assign_clusters_interface(const double* data, int* n, int* p, const double* cluster_centers, int* k, int* cluster_assignments)
//{
//  assign_clusters(data, *n, *p, cluster_centers, *k, cluster_assignments);
//}
RcppExport SEXP assign_clusters_interface(SEXP dataSEXP, SEXP nSEXP, SEXP pSEXP, SEXP cluster_centersSEXP, SEXP kSEXP, SEXP cluster_assignmentsSEXP) {
  BEGIN_RCPP
  NumericVector data(dataSEXP);
  int n = as<int>(nSEXP);
  int p = as<int>(pSEXP);
  NumericVector cluster_centers(cluster_centersSEXP);
  int k = as<int>(kSEXP);
  IntegerVector cluster_assignments(cluster_assignmentsSEXP);
  
  // Create raw pointers to the NumericVector data
  const double* data_ptr = REAL(data);
  const double* cluster_centers_ptr = REAL(cluster_centers);
  int* cluster_assignments_ptr = INTEGER(cluster_assignments);
  
  // Call the C++ function
  assign_clusters(data_ptr, n, p, cluster_centers_ptr, k, cluster_assignments_ptr);
  
  // No need to return anything since cluster_assignments is modified in-place
  
  END_RCPP
}


// void update_cluster_centers_interface(const double* data, int* n, int* p, int* k, const int* cluster_assignments, double* cluster_centers)
// {
//   update_cluster_centers(data, *n, *p, *k, cluster_assignments, cluster_centers);
// }

RcppExport SEXP update_cluster_centers_interface(SEXP dataSEXP, SEXP nSEXP, SEXP pSEXP, SEXP kSEXP, SEXP cluster_assignmentsSEXP, SEXP cluster_centersSEXP) {
  BEGIN_RCPP
  
  NumericVector data(dataSEXP);
  int n = as<int>(nSEXP);
  int p = as<int>(pSEXP);
  int k = as<int>(kSEXP);
  IntegerVector cluster_assignments(cluster_assignmentsSEXP);
  NumericVector cluster_centers(cluster_centersSEXP);
  
  // Create raw pointers to the NumericVector data
  const double* data_ptr = REAL(data);
  const int* cluster_assignments_ptr = INTEGER(cluster_assignments);
  double* cluster_centers_ptr = REAL(cluster_centers);
  
  // Call the C++ function
  update_cluster_centers(data_ptr, n, p, k, cluster_assignments_ptr, cluster_centers_ptr);
  
  return R_NilValue;
  
  END_RCPP
}


// void kmeans_algorithm_interface(double* data, int* n, int* p, int* k, double* centers, int* cluster_assignments)
// {
//   kmeans_algorithm(data, *n, *p, *k, centers, cluster_assignments);
// }

RcppExport SEXP kmeans_algorithm_interface(SEXP dataSEXP, SEXP nSEXP, SEXP pSEXP, SEXP kSEXP, SEXP centersSEXP, SEXP cluster_assignmentsSEXP) {
  BEGIN_RCPP
  
  NumericVector data(dataSEXP);
  int n = as<int>(nSEXP);
  int p = as<int>(pSEXP);
  int k = as<int>(kSEXP);
  NumericVector centers(centersSEXP);
  IntegerVector cluster_assignments(cluster_assignmentsSEXP);
  
  // Create raw pointers to the NumericVector data
  double* data_ptr = REAL(data);
  double* centers_ptr = REAL(centers);
  int* cluster_assignments_ptr = INTEGER(cluster_assignments);
  
  // Call the C++ function
  kmeans_algorithm(data_ptr, n, p, k, centers_ptr, cluster_assignments_ptr);
  
  return R_NilValue;
  
  END_RCPP
}

RcppExport SEXP fitGMM_interface(SEXP dataSEXP, SEXP KSEXP, SEXP maxIterSEXP) {
  BEGIN_RCPP
  
  // Extract the input values from R
  Rcpp::NumericMatrix data(dataSEXP); // Using NumericMatrix to match the function declaration
  int K = Rcpp::as<int>(KSEXP);
  int maxIter = Rcpp::as<int>(maxIterSEXP);
  
  // Convert Rcpp::NumericMatrix to std::vector<std::vector<double>> (assuming each row is a data point)
  int numRows = data.nrow();
  int numCols = data.ncol();
  std::vector<std::vector<double>> dataVector(numRows, std::vector<double>(numCols));
  
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      dataVector[i][j] = data(i, j);
    }
  }
  
  // Call the C++ function and get the result (2D vector of responsibilities)
  std::vector<std::vector<double>> result = fitGMM(dataVector[0], K, maxIter);
  
  // Convert the result to an R matrix (2D array)
  int resultRows = result.size();
  int resultCols = result[0].size(); // Assuming each data point has the same number of responsibilities
  Rcpp::NumericMatrix resultR(resultRows, resultCols);
  
  for (int i = 0; i < resultRows; i++) {
    for (int j = 0; j < resultCols; j++) {
      resultR(i, j) = result[i][j];
    }
  }
  
  // Return the result as an R matrix
  return resultR;
  
  END_RCPP
}



static const R_CallMethodDef CallEntries[] = {
  {"euclidean_distance_interface", (DL_FUNC) &euclidean_distance_interface, 3},
  {"assign_clusters_interface", (DL_FUNC) &assign_clusters_interface, 6},
  {"update_cluster_centers_interface", (DL_FUNC) &update_cluster_centers_interface, 6},
  {"kmeans_algorithm_interface", (DL_FUNC) &kmeans_algorithm_interface, 6},
  {"fitGMM_interface", (DL_FUNC) &fitGMM_interface, 3},
  {NULL, NULL, 0}
};

RcppExport void R_init_kMeansDemo(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}


// R_CMethodDef cMethods[] = {
//   {"euclidean_distance_interface", (DL_FUNC) &euclidean_distance_interface, 3},
//   {"assign_clusters_interface", (DL_FUNC) &assign_clusters_interface, 6},
//   {"update_cluster_centers_interface", (DL_FUNC) &update_cluster_centers_interface, 6},
//   {"kmeans_algorithm_interface", (DL_FUNC) &kmeans_algorithm_interface, 6},
//   {NULL,NULL,0}
// };
// 
// extern "C"{
//   void R_init_kMeansDemo(DllInfo *info)
//   {
//     R_registerRoutines(info, cMethods, NULL, NULL, NULL);
//     R_useDynamicSymbols(info, FALSE);
//   }
// }