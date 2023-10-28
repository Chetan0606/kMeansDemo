#' Fit a Gaussian Mixture Model (GMM)
#'
#' This function fits a Gaussian Mixture Model to the input data using C++ implementation.
#' @name fitGMM_interface
#' @param data A numeric vector containing the data points to fit the GMM to.
#' @param K An integer specifying the number of components in the GMM.
#' @param maxIter An integer specifying the maximum number of iterations for the EM algorithm.
#'
#' @return A matrix of responsibilities indicating the probability of each data point belonging to each component.
#'
#' @export
#' 
#' @examples
#' data <- matrix(rnorm(900), ncol = 3)
#' K <- 4
#' maxIter <- 10
#' result <- fitGMM(data, K, maxIter)
#' print(result)
fitGMM <- function(data, K, maxIter) {
  result <- .Call("fitGMM_interface",
                  data,
                  K,
                  maxIter)
  result
}
