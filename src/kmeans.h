#include <cmath> 
#include <cstdlib>
#include <vector>
#include <Rcpp.h>


double euclidean_distance(const double* point1, const double* point2, int p);
void assign_clusters(const double* data, int n, int p, const double* cluster_centers, int k, int* cluster_assignments);
void update_cluster_centers(const double* data, int n, int p, int k, const int* cluster_assignments, double* cluster_centers);
int kmeans_algorithm(double* data, int n, int p, int k, double* centers, int* cluster_assignments);
