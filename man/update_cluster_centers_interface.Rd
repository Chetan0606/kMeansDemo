% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/kmeans.R
\name{update_cluster_centers_interface}
\alias{update_cluster_centers_interface}
\alias{update_cluster_centers}
\title{Update Cluster Centers}
\usage{
update_cluster_centers(data, n, p, k, cluster_assignments, cluster_centers)
}
\arguments{
\item{data}{A numeric matrix where each row represents a data point and each column represents a feature.}

\item{n}{An integer specifying the number of data points.}

\item{p}{An integer specifying the number of features or dimensions.}

\item{k}{An integer specifying the number of clusters.}

\item{cluster_assignments}{A numeric vector of cluster assignments, where each element indicates the cluster to which the corresponding data point belongs.}

\item{cluster_centers}{A numeric matrix representing cluster centers.}
}
\description{
This function updates the cluster centers based on data points' assignments to clusters.
}
\examples{
# Example: Update cluster centers in 2D space
data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
n <- nrow(data)
p <- ncol(data)
k <- 2
cluster_assignments <- c(1, 2)
cluster_centers <- matrix(0, nrow = k, ncol = p)
updated_centers <- update_cluster_centers(data, n, p, k, cluster_assignments, cluster_centers)
cat("Updated Cluster Centers:", updated_centers, "\n")

}
