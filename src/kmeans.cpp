//#include <Rcpp.h>

#include "kmeans.h"
using namespace Rcpp;

// Function to calculate the Euclidean distance between two points
double euclidean_distance(const double* point1, const double* point2, int p) {
  double distance = 0.0;
  for (int i = 0; i < p; i++) {
    double diff = point1[i] - point2[i];
    distance += diff * diff;
  }
  return sqrt(distance);
}

// Function to assign each point to the nearest cluster
void assign_clusters(const double* data, int n, int p, const double* cluster_centers, int k, int* cluster_assignments) {
  for (int i = 0; i < n; i++) {
    double min_distance = euclidean_distance(&data[i * p], &cluster_centers[0], p);
    cluster_assignments[i] = 1;
    
    for (int j = 1; j < k; j++) {
      double distance = euclidean_distance(&data[i * p], &cluster_centers[j * p], p);
      if (distance < min_distance) {
        min_distance = distance;
        cluster_assignments[i] = j + 1;
      }
    }
  }
}

// Function to update cluster centers
void update_cluster_centers(const double* data, int n, int p, int k, const int* cluster_assignments, double* cluster_centers) {
  std::vector<int> cluster_sizes(k, 0);
  
  for (int i = 0; i < n; i++) {
    int cluster = cluster_assignments[i] - 1;
    cluster_sizes[cluster]++;
    for (int j = 0; j < p; j++) {
      cluster_centers[cluster * p + j] += data[i * p + j];
    }
  }
  
  for (int i = 0; i < k; i++) {
    if (cluster_sizes[i] > 0) {
      for (int j = 0; j < p; j++) {
        cluster_centers[i * p + j] /= cluster_sizes[i];
      }
    }
  }
}

// K-Means algorithm
int kmeans_algorithm(double* data, int n, int p, int k, double* centers, int* cluster_assignments) {
  // Randomly initialize cluster centers (you may implement a better initialization)
  for (int i = 0; i < k; i++) {
    int random_point = rand() % n;
    for (int j = 0; j < p; j++) {
      centers[i * p + j] = data[random_point * p + j];
    }
  }
  
  const int max_iterations = 100; // You can adjust this as needed
  int iteration = 0;
  
  while (iteration < max_iterations) {
    // Assign each point to the nearest cluster
    assign_clusters(data, n, p, centers, k, cluster_assignments);
    
    // Update cluster centers
    update_cluster_centers(data, n, p, k, cluster_assignments, centers);
    
    iteration++;
    // You can add a convergence criterion here to stop early if needed
  }
  
  // Return success (0)
  return 0;
}


