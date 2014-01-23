library(sip)
#library(gRbase)
library(Rgraphviz)

#We want an graphNEL to newtork function

np<-create.network()
read.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
show.network(np)

network.info(np)

dev.off()
