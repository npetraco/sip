library(sip)
detach("package:sip", unload=TRUE)
library(RHugin)

#We want an graphNEL to SMILE newtwork function

np<-create.network()
read.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
dev.off()
show.network(np)
network.info(np)

get.table(np,"LOSESp")
#set.table(np,"LOSESp",    c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98),printQ=TRUE) 

nph <- read.rhd("/Users/npetraco/codes/R/sip/tests/apple_jack_LMID_FROM_RHUGIN.net",type="net")
dev.off()
plot(nph)
RHugin::get.table(nph,"Sick")["Freq"] - sip::get.table(np,"SICK")["value"]
RHugin::get.table(nph,"Dry")["Freq"] - sip::get.table(np,"DRY")["value"]
RHugin::get.table(nph,"Loses")["Freq"] - sip::get.table(np,"LOSES")["value"]
RHugin::get.table(nph,"Treat")
sip::get.table(np,"TREAT")
RHugin::get.table(nph,"Sick1")["Freq"] - sip::get.table(np,"SICKp")["value"]
RHugin::get.table(nph,"Dry1")["Freq"] - sip::get.table(np,"DRYp")["value"]
RHugin::get.table(nph,"Loses1")["Freq"] - sip::get.table(np,"LOSESp")["value"]
RHugin::get.table(nph,"Harv")["Utility"] - 
  sip::get.table(np,"HARV")
