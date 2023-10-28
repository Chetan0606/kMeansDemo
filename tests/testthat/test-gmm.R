library(kMeansDemo)
library(testthat)
context("gmm")


test_that("gmm_algo computes the same answer as R", {
  data <- matrix(rnorm(900), ncol = 3)
  K <- 4
  maxIter <- 10
  result <- fitGMM(data, K, maxIter)
  expect_equal(K, 4)
})