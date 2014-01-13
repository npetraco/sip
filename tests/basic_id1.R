library(sip)

#C++ functions start with Uppercase, R functions do not

np<-create.network()
#np<-add.node(np, "SUCCESS", "utility")
np<-add.node(np, "SUCCESS", "chance", c("succsess","failure"))
np<-add.node(np, "FORCAST", "chance", c("good","moderate","poor"))

np<-AddArc(np, "SUCCESS", "FORCAST")
#get.table(np,"SUCCESS")
#get.table(np,"FORCAST")
#set.table(np,"FORCAST",c(6,5,4,3,2,1))

np<-AddNode(np, "INVEST", "decision", c("invest","do_not_invest"))
np<-AddNode(np, "GAIN", "utility", NULL)
np<-AddArc(np, "INVEST", "GAIN")
np<-AddArc(np, "SUCCESS", "GAIN")

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
