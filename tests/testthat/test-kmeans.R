library(kMeansDemo)
library(testthat)
context("kmeans")

test_that("euclidean_distance calculates Euclidean distance correctly in 2D space", {
  point1 <- c(1.2, 2.3)
  point2 <- c(4.5, 5.6)
  p <- length(point1)
  distance <- euclidean_distance(point1, point2, p)
  expect_equal(distance, sqrt((1.2 - 4.5)^2 + (2.3 - 5.6)^2))
})

test_that("assign_clusters assigns data points to clusters correctly in 2D space", {
  data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
  n <- nrow(data)
  p <- ncol(data)
  cluster_centers <- matrix(c(1.0, 2.0, 4.0, 5.0), nrow = 2)
  k <- nrow(cluster_centers)
  assignments <- assign_clusters(data, n, p, cluster_centers, k)
  expect_equal(assignments, c(1, 1))
})

test_that("update_cluster_centers updates cluster centers correctly in 2D space", {
  data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
  n <- nrow(data)
  p <- ncol(data)
  k <- 2
  cluster_assignments <- c(1, 2)
  cluster_centers <- matrix(0, nrow = k, ncol = p)
  updated_centers <- update_cluster_centers(data, n, p, k, cluster_assignments, cluster_centers)
  expect_equal(updated_centers, matrix(c(0, 0, 0, 0, 0, 0), nrow = 2))
})

test_that("kmeans_algorithm performs K-Means clustering correctly in 2D space", {
  data <- matrix(c(1.2, 2.3, 3.1, 4.8, 5.7, 6.6), nrow = 2)
  n <- nrow(data)
  p <- ncol(data)
  k <- 2
  initial_centers <- matrix(c(1.0, 2.0, 4.0, 5.0), nrow = k)
  initial_assignments <- integer(n)
  final_assignments <- kmeans_algorithm(data, n, p, k, initial_centers, initial_assignments)
  expect_equal(final_assignments, c(2, 2))
})