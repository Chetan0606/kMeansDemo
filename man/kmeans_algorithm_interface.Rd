% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/kmeans.R
\name{kmeans_algorithm_interface}
\alias{kmeans_algorithm_interface}
\alias{kmeans_algorithm}
\title{K-Means Clustering Algorithm}
\usage{
kmeans_algorithm(data, n, p, k, centers, cluster_assignments)
}
\arguments{
\item{data}{A numeric matrix where each row represents a data point and each column represents a feature.}

\item{n}{An integer specifying the number of data points.}

\item{p}{An integer specifying the number of features or dimensions.}

\item{k}{An integer specifying the number of clusters to be formed.}

\item{centers}{A numeric matrix representing the initial cluster centers.}

\item{cluster_assignments}{A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs.}
}
\value{
A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs after the K-Means algorithm.
}
\description{
This function performs the K-Means clustering algorithm on the given data points.
}
\examples{
# Example: Perform K-Means clustering on data in 2D space
data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
n <- nrow(data)
p <- ncol(data)
k <- 2
initial_centers <- matrix(c(1.0, 2.0, 4.0, 5.0), nrow = k)
initial_assignments <- integer(n)
final_assignments <- kmeans_algorithm(data, n, p, k, initial_centers, initial_assignments)
cat("Final Cluster Assignments:", final_assignments, "\n")

}
