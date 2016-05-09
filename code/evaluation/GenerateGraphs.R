pdf("all_single.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,1)) 
single_a <- read.csv("strategy_0_single_thread.csv")
single_b <- read.csv("strategy_1_single_thread.csv")
single_c <- read.csv("strategy_2_single_thread.csv")
single_d <- read.csv("strategy_3_single_thread.csv")
g_range <- range(0, single_a$timeTot, single_b$timeTot,single_c$timeTot, single_d$timeTot)
par(mar=c(5,5.5,3,3), mgp=c(3.7,1,0))
plot(single_a$timeTot, type="o", col="blue",  ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
min_v = floor(min(single_a$timeTot, single_b$timeTot, single_c$timeTot) * 10^4) / 10^4
max_v = floor(max(single_a$timeTot, single_b$timeTot, single_c$timeTot) * 10^4) / 10^4
lines(single_b$timeTot,type="o", pch=22, lty=2, col="red")
lines(single_c$timeTot,type="o", pch=22, lty=2, col="green")
lines(single_d$timeTot,type="o", pch=22, lty=2, col="pink")
title(main="Single Thread", sub = "", xlab = "lines", ylab="time (ms)")
axis(2,las=1, at=10000*0:g_range[2])
axis(2,las=1, at=max_v)
#axis(2,las=1, at=max(single_c$timeTot))
axis(1, at=1:10, lab=single_a$rows)
legend("top",c("strategy 0","strategy 1","strategy 2", "strategy 3"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green","pink"))
dev.off()


pdf("all_multiple.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,1)) 
multiple_a <- read.csv("strategy_0_multiple_thread.csv")
multiple_b <- read.csv("strategy_1_multiple_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
multiple_d <- read.csv("strategy_3_multiple_thread.csv")
par(mar=c(5,5.5,3,3), mgp=c(3.7,1,0))
g_range <- range(0, multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot)
min_v = floor(min(multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot) * 10^4) / 10^4
max_v = floor(max(multiple_a$timeTot, multiple_b$timeTot,multiple_c$timeTot) * 10^4) / 10^4
plot(multiple_a$timeTot, type="o", col="blue",  ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
lines(multiple_b$timeTot,type="o", pch=22, lty=2, col="red")
lines(multiple_c$timeTot,type="o", pch=22, lty=2, col="green")
lines(multiple_d$timeTot,type="o", pch=22, lty=2, col="pink")
title(main="Multiple Thread", sub = "", xlab = "Threads", ylab="time (ms)")
#axis(2,las=1, at=30000*(90000:g_range[2]))
axis(2,las=1, at=seq(20000,60000,10000))
axis(2,las=1, at=max(multiple_c$timeTot))
if(min_v != 0) axis(2,las=1, at=min_v)
axis(2,las=1, at=max_v)
axis(1, at=1:40, lab=multiple_a$threads)
legend("center",c("strategy 0","strategy 1","strategy 2","stategy 3"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green","pink"))
dev.off()


pdf("speedup.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,1)) 
single_a <- read.csv("strategy_0_single_thread.csv")
single_b <- read.csv("strategy_1_single_thread.csv")
single_c <- read.csv("strategy_2_single_thread.csv")
single_d <- read.csv("strategy_3_single_thread.csv")
multiple_a <- read.csv("strategy_0_multiple_thread.csv")
multiple_b <- read.csv("strategy_1_multiple_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
multiple_d <- read.csv("strategy_3_multiple_thread.csv")
p_a <- single_a[3,]
p_b <- single_b[3,]
p_c <- single_c[3,]
p_d <- single_d[3,]
p_a <- p_a$timeTot
p_b <- p_b$timeTot
p_c <- p_c$timeTot
p_d <- p_d$timeTot
timeA <- multiple_a$timeTot
timeB <- multiple_b$timeTot
timeC <- multiple_c$timeTot
timeD <- multiple_d$timeTot
histoA <- c()
histoB <- c()
histoC <- c()
histoD <- c()
for (i in 1:length(timeA)) histoA[i] <- p_a / timeA[i]
for (i in 1:length(timeB)) histoB[i] <- p_b / timeB[i]
for (i in 1:length(timeC)) histoC[i] <- p_c / timeC[i]
for (i in 1:length(timeD)) histoD[i] <- p_d / timeD[i]
g_range <- range(0, histoA, histoB, histoC, histoD)
min_v <- floor(min( histoA, histoB, histoC, histoD) * 10^4) / 10^4
max_v <- floor(max( histoA, histoB, histoC, histoD) * 10^4) / 10^4
plot(histoA, type="o", col="blue", ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
lines(histoB,type="o", pch=22, lty=2, col="red")
lines(histoC,type="o", pch=22, lty=2, col="green")
lines(histoD,type="o", pch=22, lty=2, col="pink")
title(main="P value", sub = "", xlab = "threads", ylab="P")
axis(2, las=1, at=0:g_range[2])
axis(2, las=1, at=min_v)
axis(2, las=1, at=max_v)
axis(1, at=1:40, lab=multiple_c$threads)
legend("center",c("strategy 0","strategy 1","strategy 2", "strategy 3"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green","pink"))
dev.off()


pdf("init_phase.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,2)) 
single_c <- read.csv("strategy_2_single_thread.csv")
multiple_c <- read.csv("strategy_2_multiple_thread.csv")
single_d <- read.csv("strategy_3_single_thread.csv")
multiple_d <- read.csv("strategy_3_multiple_thread.csv")
timeC <- single_c$timeTot
timeInitC <- single_c$timeData
dataC <- c()
timeD <- single_d$timeTot
timeInitD <- single_d$timeData
dataD <- c()
m_timeC <- multiple_c$timeTot
m_timeInitC <- multiple_c$timeData
m_dataC <- c()
m_timeD <- multiple_d$timeTot
m_timeInitD <- multiple_d$timeData
m_dataD <- c()
for (i in 1:length(timeC)) dataC[i] <- timeInitC[i] / (timeC[i] - timeInitC[i]) * 100
for (i in 1:length(timeC)) m_dataC[i] <- m_timeInitC[i] / (m_timeC[i] - m_timeInitC[i]) * 100
for (i in 1:length(timeD)) dataD[i] <- timeInitD[i] / (timeD[i] - timeInitD[i]) * 100
for (i in 1:length(timeD)) m_dataD[i] <- m_timeInitD[i] / (m_timeD[i] - m_timeInitD[i]) * 100
boxplot(dataC, m_dataC, names = c("Single Th.", "Multiple Th."))
title(main="Overhead Strategy 2", sub = "", xlab = "", ylab="Time spent on preprocess (%)")
boxplot(dataD, m_dataD, names = c("Single Th.", "Multiple Th."))
title(main="Overhead Strategy 3", sub = "", xlab = "", ylab="Time spent on preprocess (%)")
dev.off()

pdf("init_phase_strategy_3.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,1)) 
single_d <- read.csv("strategy_3_single_thread.csv")
multiple_d <- read.csv("strategy_3_init.csv")
timeD <- single_d$timeTot
timeInitD <- single_d$timeData
dataD <- c()
m_timeD <- multiple_d$timeTot
m_timeInitD <- multiple_d$timeData
m_dataD <- c()
for (i in 1:length(timeD)) dataD[i] <- timeInitD[i] / (timeD[i] - timeInitD[i]) * 100
for (i in 1:length(timeD)) m_dataD[i] <- m_timeInitD[i] / (m_timeD[i] - m_timeInitD[i]) * 100
boxplot(dataD, m_dataD, names = c("Single Thread", "Multiple Thread"))
title(main="Overhead Strategy 3", sub = "", xlab = "", ylab="Time spent on preprocess (%)")
dev.off()

pdf("strategy_1_3.pdf", useDingbats=FALSE)
attach(mtcars)
par(mfrow=c(1,1)) 
multiple_a <- read.csv("strategy_1_multiple_thread.csv")
multiple_b <- read.csv("strategy_3_multiple_thread.csv")
par(mar=c(5,5.5,3,3), mgp=c(3.7,1,0))
g_range <- range(0, multiple_a$timeTot, multiple_b$timeTot)
min_v = floor(min(multiple_a$timeTot, multiple_b$timeTot) * 10^4) / 10^4
max_v = floor(max(multiple_a$timeTot, multiple_b$timeTot) * 10^4) / 10^4
plot(multiple_a$timeTot, type="o", col="blue",  ylim = c(0,g_range[2]), axes = FALSE, ann = FALSE)
box()
lines(multiple_b$timeTot,type="o", pch=22, lty=2, col="red")
title(main="Multiple Thread", sub = "", xlab = "Threads", ylab="time (ms)")
#axis(2,las=1, at=30000*(90000:g_range[2]))
axis(2,las=1, at=seq(0,2900,500))
axis(2,las=1, at=max(multiple_c$timeTot))
if(min_v != 0) axis(2,las=1, at=min_v)
axis(2,las=1, at=max_v)
axis(1, at=1:40, lab=multiple_a$threads)
legend("top",c("strategy 0","strategy 1"), lty=1:2 ,lwd=3, bty="n", col=c("blue","red","green","pink"))
dev.off()

