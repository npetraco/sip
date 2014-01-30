library(sip)

#C++ functions start with Uppercase, R functions do not

np<-create.network()
add.node(np, "SICK", "chance", c("sick","not_sick"))
add.node(np, "DRY", "chance", c("dry","not_dry"))
add.node(np, "LOSES", "chance", c("yes","no"))

add.arc(np, "SICK", "LOSES")
add.arc(np, "DRY", "LOSES")

add.node(np, "SICKp", "chance", c("sick","not_sick"))
add.node(np, "DRYp", "chance", c("dry","not_dry"))
add.node(np, "LOSESp", "chance", c("yes","no"))

add.arc(np, "SICKp", "LOSESp")
add.arc(np, "DRYp", "LOSESp")
add.arc(np, "SICK", "SICKp")
add.arc(np, "DRY", "DRYp")

add.node(np, "TREAT", "decision", c("treat","dont_treat"))
add.node(np, "COST", "utility", NULL)
add.node(np, "HARV", "utility", NULL)

add.arc(np, "LOSES","TREAT")
add.arc(np, "TREAT", "COST")
add.arc(np, "SICKp", "HARV")
add.arc(np, "TREAT","SICKp")

show.network(np)

get.table(np,"SICK")
set.table(np,"SICK",c(0.1, 0.9),printQ=TRUE)
get.table(np,"DRY")
set.table(np,"DRY",c(0.1, 0.9),printQ=TRUE)
get.table(np,"LOSES")
set.table(np,"LOSES",c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98),printQ=TRUE) 

get.table(np,"SICKp")
set.table(np,"SICKp",c(0.20, 0.8, 0.01, 0.99, 0.99, 0.01, 0.02, 0.98),printQ=TRUE) 
get.table(np,"DRYp")
set.table(np,"DRYp",c(0.6,0.4,0.05,0.95),printQ=TRUE) 
get.table(np,"LOSESp")
set.table(np,"LOSESp",c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98),printQ=TRUE) 

get.table(np,"COST")
set.table(np,"COST",c(-8000,0),printQ=TRUE)
get.table(np,"HARV")
set.table(np,"HARV",c(3000,20000),printQ=TRUE)

write.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
