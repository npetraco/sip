library(sip)
detach("package:sip", unload=TRUE)
#library(gRbase)

#We want an graphNEL to SMILE newtwork function

np<-create.network()
read.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
show.network(np)
dev.off()

network.info(np)

