#include "gmm.h"

#include <random> // Include the random header

using namespace std; // Use the std namespace

using namespace Rcpp;

// Function to fit a GMM model
std::vector<std::vector<double>> fitGMM(const std::vector<double>& data, int K, int maxIter) {
  int n = data.size();
  std::vector<std::vector<double>> responsibilities(n, std::vector<double>(K));
  std::vector<std::vector<double>> probabilities(n, std::vector<double>(K));
  
  std::vector<double> means(K);
  std::vector<double> variances(K);
  std::vector<double> weights(K, 1.0 / K); // Initialize weights equally
  
  // Initialize means randomly from the data
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dataDistribution(0, n - 1);
  
  for (int j = 0; j < K; j++) {
    int randomDataIndex = dataDistribution(gen);
    means[j] = data[randomDataIndex];
  }
  
  // Initialize variances with non-zero values
  for (int j = 0; j < K; j++) {
    variances[j] = 1.0;
  }
  
  for (int iteration = 0; iteration < maxIter; iteration++) {
    // Expectation Step: Compute responsibilities
    for (int i = 0; i < n; i++) {
      double sum_responsibilities = 0.0;
      for (int j = 0; j < K; j++) {
        responsibilities[i][j] = weights[j] * exp(-0.5 * pow((data[i] - means[j]) / sqrt(variances[j]), 2)) /
          (sqrt(2.0 * M_PI * variances[j]));
        sum_responsibilities += responsibilities[i][j];
      }
      
      for (int j = 0; j < K; j++) {
        responsibilities[i][j] /= sum_responsibilities;
        probabilities[i][j] = responsibilities[i][j];
      }
    }
    
    // Maximization Step: Update means, weights, and variances
    for (int j = 0; j < K; j++) {
      double sum_responsibilities = 0.0;
      double sum_weighted_data = 0.0;
      double sum_squared_weighted_data = 0.0;
      
      for (int i = 0; i < n; i++) {
        double r = responsibilities[i][j];
        sum_responsibilities += r;
        sum_weighted_data += r * data[i];
        sum_squared_weighted_data += r * data[i] * data[i];
      }
      
      weights[j] = sum_responsibilities / n;
      means[j] = sum_weighted_data / sum_responsibilities;
      variances[j] = sum_squared_weighted_data / sum_responsibilities - means[j] * means[j];
    }
  }
  
  return probabilities;
}

