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

#Prior node
get.table(np,"SUCCESS")

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

#DECISION NODE
levifo<-GetLevelsAssociatedWithNode(np, "INVEST")
levifo
GenerateTableRowLevels(levifo)

#Kills:
GetNodeTable(np, "INVEST")
#Kills:
get.table(np3,"Treat")
#*****NEED TO CHECK TABLE TYPE IN GetNodeTable

#UTILITY NODE
#Kills: THERE ARE NO LEVELS FOR A UTILITY NODE
levifo<-GetLevelsAssociatedWithNode(np, "GAIN")
levifo

#Kills:
#USES STATE NAMES TO ACCESS THE TABLE, BUT FOR UTILITY, THERE ARE NO STATES
get.table(np,"GAIN")

#WriteNetwork(np,"/Users/npetraco/codes/R/sip/tests/anet.net")



np3<-CreateSmlieNetwork()
np3<-AddNode(np3, "Sick_0", "chance", c("yes","no"))
np3<-AddNode(np3, "Dry_0", "chance", c("yes","no"))
np3<-AddNode(np3, "Losses_0", "chance", c("yes","no"))
np3<-AddArc(np3, "Sick_0", "Losses_0")
np3<-AddArc(np3, "Dry_0", "Losses_0")

np3<-AddNode(np3, "Sick_1", "chance", c("yes","no"))
np3<-AddNode(np3, "Dry_1", "chance", c("yes","no"))
np3<-AddNode(np3, "Losses_1", "chance", c("yes","no"))
np3<-AddArc(np3, "Sick_1", "Losses_1")
np3<-AddArc(np3, "Dry_1", "Losses_1")

np3<-AddArc(np3, "Sick_0", "Sick_1")
np3<-AddArc(np3, "Dry_0", "Dry_1")

get.table(np3,"Sick_1")
set.table(np3,"Sick_1",1:27)

np3<-AddNode(np3, "Treat", "decision", c("yes","no"))
np3<-AddArc(np3, "Treat", "Sick_1")

#DECISION NODE
levifo<-GetLevelsAssociatedWithNode(np3, "Treat")
levifo
GenerateTableRowLevels(levifo)

#Kills:
GetNodeTable(np3, "Treat")
#Kills:
get.table(np3,"Treat")
#*****NEED TO CHECK TABLE TYPE IN GetNodeTable
