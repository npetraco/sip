library(sip)

#C++ functions start with Uppercase, R functions do not

np<-create.network()
#add.node(np, "SUCCESS", "Utility")
#np<-add.node(np, "SUCCESS", "utility")
add.node(np, "SUCCESS", "chance", c("succsess","failure"))
add.node(np, "FORCAST", "chance", c("good","moderate","poor"))
add.arc(np, "SUCCESS", "FORCAST")

add.node(np, "INVEST", "decision", c("invest","do_not_invest"))
add.node(np, "GAIN", "utility", NULL)
add.arc(np, "INVEST", "GAIN")
add.arc(np, "SUCCESS", "GAIN")

check.node.values.length(np,"SUCCESS",c(1,1,1))

get.table(np,"SUCCESS")
get.table(np,"FORCAST")

delete.arc(np, "FORCAST","SUCCESS")
ErrorMessages(np)
delete.node(np, "XXXXXX")
delete.node(np, "SUCCESS")


#Prior node

get.table(np,"SUCCESS")
set.table(np,"SUCCESS",c(1.3,2.4),printQ=TRUE)

get.table(np,"FORCAST")
set.table(np,"FORCAST",c(1.5,2.9,3.674,4.7,5.21,6),printQ=TRUE)  #MAKE ERROR FOR PROB VECTOR TO LONG OR INCOHERENT!!!!!!!


get.table(np,"GAIN")
set.table(np,"GAIN",c(1.4,2.346673,3.4,0))
set.table(np,"INVEST",NULL)

#Conditional node (one parent)
get.table(np,"FORCAST")

#Decision node (no parents)
get.table(np,"INVEST")
#Decision node (one parents)
#add.arc(np, "SUCCESS", "INVEST")
#get.table(np,"INVEST")

#Utility node 
get.table(np,"GAIN")

#set.table(np,"FORCAST",c(6,5,4,3,2,1))



NodeType(np, "SUCCESS")
NodeType(np, "INVEST")
NodeType(np, "GAIN")

ErrorCode2String(-567)
