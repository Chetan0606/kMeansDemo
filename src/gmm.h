#include <Rcpp.h>
#include <vector>

std::vector<std::vector<double>> fitGMM(const std::vector<double>& data, int K, int maxIter);