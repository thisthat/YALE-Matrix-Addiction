matequal <- function(x, y)
  is.matrix(x) && is.matrix(y) && dim(x) == dim(y) && all(x == y)

tmp <- read.csv("a.csv", header = FALSE)
a <- as.matrix(tmp)
tmp <- read.csv("b.csv", header = FALSE)
b <- as.matrix(tmp)
tmp <- read.csv("c.csv", header = FALSE)
c <- as.matrix(tmp)

matequal(a %*% b, c)
