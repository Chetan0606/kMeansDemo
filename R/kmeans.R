#' Calculate Euclidean Distance
#'
#' This function calculates the Euclidean distance between two points in a given space.
#'
#' @name euclidean_distance_interface
#' @param point1 A numeric vector representing the coordinates of the first point.
#' @param point2 A numeric vector representing the coordinates of the second point.
#' @param p An integer specifying the number of dimensions or attributes in the data.
#'
#' @return A numeric value representing the Euclidean distance between \code{point1} and \code{point2}.
#'
#' @export
#'
#' @examples
#' # Example 1: Calculate Euclidean distance between two points in 2D space
#' point1 <- c(1.2, 2.3)
#' point2 <- c(4.5, 5.6)
#' p <- length(point1)
#' distance <- euclidean_distance(point1, point2, p)
#' cat("Euclidean Distance:", distance, "\n")
#'
#' # Example 2: Calculate Euclidean distance between two points in 3D space
#' point1 <- c(1.2, 2.3, 3.1)
#' point2 <- c(4.5, 5.6, 6.7)
#' p <- length(point1)
#' distance <- euclidean_distance(point1, point2, p)
#' cat("Euclidean Distance:", distance, "\n")
euclidean_distance <- function(point1, point2, p) {
  result <- .Call("euclidean_distance_interface",
               point1 = as.double(point1),
               point2 = as.double(point2),
               p = as.integer(p))
  result
}

#' Assign Data Points to Nearest Clusters
#'
#' This function assigns data points to the nearest clusters based on their distances to cluster centers.
#' @name assign_clusters_interface
#' @param data A numeric matrix where each row represents a data point and each column represents a feature.
#' @param n An integer specifying the number of data points.
#' @param p An integer specifying the number of features or dimensions.
#' @param cluster_centers A numeric matrix representing cluster centers.
#' @param k An integer specifying the number of clusters.
#'
#' @return A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs.
#'
#' @export
#'
#' @examples
#' # Example: Assign data points to clusters in 2D space
#' data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
#' n <- nrow(data)
#' p <- ncol(data)
#' cluster_centers <- matrix(c(1.0, 2.0, 4.0, 5.0), nrow = 2)
#' k <- nrow(cluster_centers)
#' assignments <- assign_clusters(data, n, p, cluster_centers, k)
#' cat("Cluster Assignments:", assignments, "\n")
assign_clusters <- function(data, n, p, cluster_centers, k) {
  cluster_assignments <- integer(n)
  .Call("assign_clusters_interface",
     data = as.double(data),
     n = as.integer(n),
     p = as.integer(p),
     cluster_centers = as.double(cluster_centers),
     k = as.integer(k),
     cluster_assignments = cluster_assignments)
  cluster_assignments
}

#' Update Cluster Centers
#'
#' This function updates the cluster centers based on data points' assignments to clusters.
#'
#' @name update_cluster_centers_interface
#' @param data A numeric matrix where each row represents a data point and each column represents a feature.
#' @param n An integer specifying the number of data points.
#' @param p An integer specifying the number of features or dimensions.
#' @param k An integer specifying the number of clusters.
#' @param cluster_assignments A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs.
#' @param cluster_centers A numeric matrix representing cluster centers.
#'
#' @export
#'
#' @examples
#' # Example: Update cluster centers in 2D space
#' data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
#' n <- nrow(data)
#' p <- ncol(data)
#' k <- 2
#' cluster_assignments <- c(1, 2)
#' cluster_centers <- matrix(0, nrow = k, ncol = p)
#' updated_centers <- update_cluster_centers(data, n, p, k, cluster_assignments, cluster_centers)
#' cat("Updated Cluster Centers:", updated_centers, "\n")
#'
update_cluster_centers <- function(data, n, p, k, cluster_assignments, cluster_centers) {
  .Call("update_cluster_centers_interface",
     data = as.double(data),
     n = as.integer(n),
     p = as.integer(p),
     k = as.integer(k),
     cluster_assignments = as.integer(cluster_assignments),
     cluster_centers = as.double(cluster_centers))
  cluster_centers
}

#' K-Means Clustering Algorithm
#'
#' This function performs the K-Means clustering algorithm on the given data points.
#'
#' @name kmeans_algorithm_interface
#' @param data A numeric matrix where each row represents a data point and each column represents a feature.
#' @param n An integer specifying the number of data points.
#' @param p An integer specifying the number of features or dimensions.
#' @param k An integer specifying the number of clusters to be formed.
#' @param centers A numeric matrix representing the initial cluster centers.
#' @param cluster_assignments A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs.
#'
#' @return A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs after the K-Means algorithm.
#'
#' @export
#'
#' @examples
#' # Example: Perform K-Means clustering on data in 2D space
#' data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
#' n <- nrow(data)
#' p <- ncol(data)
#' k <- 2
#' initial_centers <- matrix(c(1.0, 2.0, 4.0, 5.0), nrow = k)
#' initial_assignments <- integer(n)
#' final_assignments <- kmeans_algorithm(data, n, p, k, initial_centers, initial_assignments)
#' cat("Final Cluster Assignments:", final_assignments, "\n")
#'
kmeans_algorithm <- function(data, n, p, k, centers, cluster_assignments) {
  .Call("kmeans_algorithm_interface",
     data = as.double(data),
     n = as.integer(n),
     p = as.integer(p),
     k = as.integer(k),
     centers = as.double(centers),
     cluster_assignments = as.integer(cluster_assignments))
  cluster_assignments
}
