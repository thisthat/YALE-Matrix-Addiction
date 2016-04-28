matequal <- function(x, y)
  is.matrix(x) && is.matrix(y) && dim(x) == dim(y) && all(x == y)

tmp <- read.csv("a.csv", header = FALSE)
a <- as.matrix(tmp)
tmp <- read.csv("b.csv", header = FALSE)
b <- as.matrix(tmp)
tmp <- read.csv("c.csv", header = FALSE)
c <- as.matrix(tmp)

matequal(a %*% b, c)

plot(multi_a$time, type="o", col="blue", ylim = g_range, axes = FALSE, ann = FALSE)
box()
lines(multi_b$time,type="o", pch=22, lty=2, col="red")
title(main="Multi Thread", sub = "500x500 Matrix", xlab = "threads", ylab="time")
axis(2,las=1, at=10000*0:g_range[2])
axis(1, at=1:10, lab=multi_a$threads)
legend("top",c("strategy 0","strategy 1"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red"))


