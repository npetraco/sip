library(sip)
detach("package:sip", unload=TRUE)

#C++ functions start with Uppercase, R functions do not

np<-create.network()
add.node(np, "SICK", "chance", c("yes","no"))
add.node(np, "DRY", "chance", c("yes","no"))
add.node(np, "LOSES", "chance", c("yes","no"))

add.arc(np, "SICK", "LOSES")
add.arc(np, "DRY", "LOSES")

add.node(np, "SICKp", "chance", c("yes","no"))
add.node(np, "DRYp", "chance", c("yes","no"))
add.node(np, "LOSESp", "chance", c("yes","no"))

add.arc(np, "SICKp", "LOSESp")
add.arc(np, "DRYp", "LOSESp")
add.arc(np, "SICK", "SICKp")
add.arc(np, "DRY", "DRYp")

add.node(np, "TREAT", "decision", c("treat","not"))
add.node(np, "COST", "utility", NULL)
add.node(np, "HARV", "utility", NULL)

add.arc(np, "LOSES","TREAT")
add.arc(np, "TREAT", "COST")
add.arc(np, "SICKp", "HARV")
add.arc(np, "TREAT","SICKp")

dev.off()
show.network(np)
#get.table(np,"SICK")
#set.table(np,"SICK",c(0.1, 0.9),printQ=TRUE)
#Sick.table[["Freq"]] <- c(0.1, 0.9)

generateTableRowLevels(np, "SICK")
generateTableRowLevels(np, "DRY")
generateTableRowLevels(np, "LOSES")
generateTableRowLevels(np, "TREAT")

get.table(np,"DRY")
set.table(np,"DRY",c(0.1, 0.9),printQ=TRUE)
#Dry.table[["Freq"]] <- c(0.1, 0.9)

get.table(np,"LOSES")
set.table(np,"LOSES",    c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98),printQ=TRUE) 
#Loses.table[["Freq"]] <- c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98)
#RHUGIN
  Loses Sick Dry Freq
1   yes  yes yes 0.95
2    no  yes yes 0.05
3   yes   no yes 0.85
4    no   no yes 0.15
5   yes  yes  no 0.90
6    no  yes  no 0.10
7   yes   no  no 0.02
8    no   no  no 0.98
#sip
value   LOSES SICK DRY
1  0.95   yes  yes yes
2  0.05    no  yes yes
3  0.85   yes   no yes
4  0.15    no   no yes
5  0.90   yes  yes  no
6  0.10    no  yes  no
7  0.02   yes   no  no
8  0.98    no   no  no

get.table(np,"SICKp")
set.table(np,"SICKp",   c(0.20, 0.8, 0.01, 0.99, 0.99, 0.01, 0.02, 0.98),printQ=TRUE) 
#Sick1.table[["Freq"]] <- c(0.2, 0.8, 0.01, 0.99, 0.99, 0.01, 0.02, 0.98)

get.table(np,"DRYp")
set.table(np,"DRYp",    c(0.6, 0.4, 0.05, 0.95),printQ=TRUE) 
#Dry1.table[["Freq"]] <- c(0.6, 0.4, 0.05, 0.95)

get.table(np,"LOSESp")
set.table(np,"LOSESp",    c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98),printQ=TRUE) 
#Loses1.table[["Freq"]] <- c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98)

get.table(np,"COST")
set.table(np,"COST",         c(-8000, 0),printQ=TRUE)
#Profit.table[["Utility"]] <- c(-8000, 0)

get.table(np,"HARV")
set.table(np,"HARV",       c(3000, 20000),printQ=TRUE)
#Harv.table[["Utility"]] <- c(3000, 20000)

write.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
