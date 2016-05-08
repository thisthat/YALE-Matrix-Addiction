matequal <- function(x, y)
  is.matrix(x) && is.matrix(y) && dim(x) == dim(y) && all(x == y)
tmp <- read.csv("a.csv", header = FALSE)
a <- as.matrix(tmp)
tmp <- read.csv("b.csv", header = FALSE)
b <- as.matrix(tmp)
tmp <- read.csv("c.csv", header = FALSE)
c <- as.matrix(tmp)
matequal(a + b, c)


pdf("all_single.pdf", useDingbats=FALSE)
single_a <- read.csv("strategy_0_single_thread.csv")
single_b <- read.csv("strategy_1_single_thread.csv")
single_c <- read.csv("strategy_2_single_thread.csv")
g_range <- range(0, single_a$timeTot, single_b$timeTot,single_c$timeTot)
plot(single_a$timeTot, type="o", col="blue",  ylim = c(15000,g_range[2]), axes = FALSE, ann = FALSE)
box()
min_v = floor(min(single_a$timeTot, single_b$timeTot, single_c$timeTot) * 10^4) / 10^4
max_v = floor(max(single_a$timeTot, single_b$timeTot, single_c$timeTot) * 10^4) / 10^4
lines(single_b$timeTot,type="o", pch=22, lty=2, col="red")
lines(single_c$timeTot,type="o", pch=22, lty=2, col="green")
title(main="Single Thread", sub = "", xlab = "lines", ylab="time (ms)")
axis(2,las=1, at=100000*0:g_range[2])
axis(2,las=1, at=max_v)
axis(2,las=1, at=max(single_c$timeTot))
axis(1, at=1:10, lab=single_a$rows)
legend("top",c("strategy 0","strategy 1","strategy 2"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green"))
dev.off()


pdf("all_multiple.pdf", useDingbats=FALSE)
multiple_a <- read.csv("strategy_0_multiple_thread.csv")
multiple_b <- read.csv("strategy_1_multiple_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
par(mar=c(5,5.5,3,3), mgp=c(3.7,1,0))
g_range <- range(0, multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot)
min_v = floor(min(multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot) * 10^4) / 10^4
max_v = floor(max(multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot) * 10^4) / 10^4
plot(multiple_a$timeTot, type="o", col="blue",  ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
lines(multiple_b$timeTot,type="o", pch=22, lty=2, col="red")
lines(multiple_c$timeTot,type="o", pch=22, lty=2, col="green")
title(main="Multiple Thread", sub = "", xlab = "Threads", ylab="time (ms)")
#axis(2,las=1, at=30000*(90000:g_range[2]))
axis(2,las=1, at=seq(90000,256000,30000))
axis(2,las=1, at=max(multiple_c$timeTot))
if(min_v != 0) axis(2,las=1, at=min_v)
axis(2,las=1, at=max_v)
axis(1, at=1:40, lab=multiple_a$threads)
legend("top",c("strategy 0","strategy 1","strategy 2"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green"))
dev.off()


pdf("diff_time_multiple.pdf", useDingbats=FALSE)
multiple_a <- read.csv("strategy_0_multiple_thread.csv")
multiple_b <- read.csv("strategy_1_multiple_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
timeA <- multiple_a$timeTot
timeB <- multiple_b$timeTot
timeC <- multiple_c$timeTot
histoA <- c()
histoB <- c()
maxA <- max(timeA)
maxB <- max(timeB)
for (i in 1:length(timeA)) histoA[i] <- (timeA[i] - timeC[i]) / maxA * 100
for (i in 1:length(timeA)) histoB[i] <- (timeB[i] - timeC[i]) / maxB * 100
boxplot(histoA, histoB, names = c("Strategy 0", "Strategy 1") )
title(main="How much faster is strategy 2?", sub = "", xlab = "", ylab="Performance Gain (%)")
dev.off()


pdf("blow_memory.pdf", useDingbats=FALSE)
blow <- read.csv("strategy_2_blow_memory.csv")
g_range <- range(0, blow$timeTot)
par(mar=c(5,5.5,3,3), mgp=c(3.5,1,0))
plot(blow$timeTot, type="o", col="blue", axes = FALSE, ann = FALSE, log="y" )
box()
title(main="Blow Memory Test (log scale)", sub = "", xlab = "NNZ", ylab="time (ms)")
axis(2,las=1, at=blow$timeTot)
axis(1, at=1:length(blow$NNZ), lab=blow$NNZ)
legend("top",c("strategy 2"), lty=1:2 ,lwd=3, bty="n", col=c("blue"))
dev.off()


pdf("speedup.pdf", useDingbats=FALSE)
single_a <- read.csv("strategy_0_single_thread.csv")
single_b <- read.csv("strategy_1_single_thread.csv")
single_c <- read.csv("strategy_2_single_thread.csv")
multiple_a <- read.csv("strategy_0_multiple_thread.csv")
multiple_b <- read.csv("strategy_1_multiple_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
p_a <- single_a[10,]
p_b <- single_b[10,]
p_c <- single_c[10,]
p_a <- p_a$timeTot
p_b <- p_b$timeTot
p_c <- p_c$timeTot
timeA <- multiple_a$timeTot
timeB <- multiple_b$timeTot
timeC <- multiple_c$timeTot
histoA <- c()
histoB <- c()
histoC <- c()
for (i in 1:length(timeA)) histoA[i] <- p_a / timeA[i]
for (i in 1:length(timeB)) histoB[i] <- p_b / timeB[i]
for (i in 1:length(timeC)) histoC[i] <- p_c / timeC[i]
g_range <- range(0, histoA, histoB, histoC)
min_v <- floor(min( histoA, histoB, histoC) * 10^4) / 10^4
max_v <- floor(max( histoA, histoB, histoC) * 10^4) / 10^4
plot(histoA, type="o", col="blue", ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
lines(histoB,type="o", pch=22, lty=2, col="red")
lines(histoC,type="o", pch=22, lty=2, col="green")
title(main="P value", sub = "", xlab = "threads", ylab="P")
axis(2, las=1, at=0:g_range[2])
axis(2, las=1, at=min_v)
axis(2, las=1, at=max_v)
axis(1, at=1:40, lab=multiple_c$threads)
legend("top",c("strategy 0","strategy 1","strategy 2"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green"))
dev.off()


pdf("init_phase.pdf", useDingbats=FALSE)
single_c <- read.csv("strategy_2_single_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
timeC <- single_c$timeTot
timeInitC <- single_c$timeData
dataC <- c()
m_timeC <- multiple_c$timeTot
m_timeInitC <- multiple_c$timeData
m_dataC <- c()
for (i in 1:length(timeC)) dataC[i] <- timeInitC[i] / (timeC[i] - timeInitC[i]) * 100
for (i in 1:length(timeC)) m_dataC[i] <- m_timeInitC[i] / (m_timeC[i] - m_timeInitC[i]) * 100
boxplot(dataC, m_dataC, names = c("Single Thread", "Multiple Thread"))
title(main="Overhead Strategy 2", sub = "", xlab = "", ylab="Time spent on preprocess (%)")
dev.off()
