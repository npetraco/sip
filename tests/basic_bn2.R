library(sip)

np<-CreateSmlieNetwork()
np<-AddNode(np, "SUCCESS", "chance", c("succsess","failure"))
np<-AddNode(np, "FORCAST", "chance", c("good","moderate","poor"))
np<-AddArc(np, "SUCCESS", "FORCAST")
#get.table(np,"SUCCESS")
#get.table(np,"FORCAST")
set.table(np,"FORCAST",c(6,5,4,3,2,1))
#WriteNetwork(np,"/Users/npetraco/codes/R/sip/tests/anet.net")


np2<-CreateSmlieNetwork()
np2<-AddNode(np2, "Prize", "chance", c("door1p","door2p","door3p"))
np2<-AddNode(np2, "You_Choose", "chance", c("door1y","door2y","door3y"))
np2<-AddNode(np2, "Monty_Chooses", "chance", c("door1m","door2m","door3m"))
np2<-AddArc(np2, "You_Choose", "Monty_Chooses")
np2<-AddArc(np2, "Prize", "Monty_Chooses")
#get.table(np2,"You_Choose")
#get.table(np2,"Prize")
#get.table(np2,"Monty_Chooses")
set.table(np2,"Monty_Chooses",1:27)
#WriteNetwork(np2,"/Users/npetraco/codes/R/sip/tests/monty2.net")

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
