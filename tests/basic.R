library(sip)

np<-CreateSmlieNetwork()
np<-AddNode(np, "SUCCESS", "chance", c("succsess","failure"))
np<-AddNode(np, "FORCAST", "chance", c("good","moderate","poor"))
np<-AddArc(np, "SUCCESS", "FORCAST")
levsinfo <- GetLevelsAssociatedWithNode(np,"FORCAST")
#junk<-AddArc(np, "FORCAST", "SUCCESS")
WriteNetwork(np,"/Users/npetraco/codes/R/sip/tests/anet.net")
#CreateNetwork_testing_func()

np2<-CreateSmlieNetwork()
np2<-AddNode(np2, "Prize", "chance", c("door1p","door2p","door3p"))
np2<-AddNode(np2, "You_Choose", "chance", c("door1y","door2y","door3y"))
np2<-AddNode(np2, "Monty_Chooses", "chance", c("door1m","door2m","door3m"))
np2<-AddArc(np2, "You_Choose", "Monty_Chooses")
np2<-AddArc(np2, "Prize", "Monty_Chooses")
levsinfo2 <- GetLevelsAssociatedWithNode(np2,"Monty_Chooses")
levsinfo2

junk<-GenerateTableRowLevels(levsinfo2)
junk#


levsinfo2

levsinfo3<-list(Names=c("Monty_Chooses","You_Choose","Prize","NextOne"), 
 Levels=list(
  c("door1m", "door2m", "door3m"),
  c("door1y", "door2y", "door3y"),
  c("door1p", "door2p", "door3p"),
  c("door1NN", "door2NN", "door3NN")
  ))
GenerateTableRowLevels(levsinfo3)

levsinfo4<-list(Names=c("Monty_Chooses","You_Choose","Prize","NextOne", "YetAnother"), 
                Levels=list(
                  c("door1m", "door2m", "door3m"),
                  c("door1y", "door2y", "door3y"),
                  c("door1p", "door2p", "door3p","door4p"),
                  c("door1NN", "door2NN", "door3NN"),
                  c("door1YA", "door2YA", "door3YA")
                ))
GenerateTableRowLevels(levsinfo4)

#GetLevelsAssociatedWithNode(np2,"Prize")
#WriteNetwork(np2,"/Users/npetraco/codes/R/sip/tests/monty2.net")
