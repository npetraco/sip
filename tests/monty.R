monty<-function()
{

choices<-c("door.a", "door.b", "door.c")

#Show puts car here:
car<-sample(choices,1)

#contenstant pick:
you<-sample(choices,1)

#Now Monty decides which dor to open:
if(car==you)
 {
  drop.idx<-which(choices==car)
  choices.left<-choices[-drop.idx]
  switch.door<-sample(choices.left,1)	
 }
if(car!=you)
 {
  already.chosen.idx<-which(choices==you)
  choices.left<-choices[-already.chosen.idx]
  switch.door<-which(choices.left==car)
 }
 
#Decide whether or not to switch doors:
switchQ<-sample(c(0,1),1)
#print(switchQ)

result<-NULL
if(switchQ==0)
 {
  final.choice<-you
  result<-c(result,0)	
 }
if(switchQ==1)
 {
  final.choice<-switch.door
  result<-c(result,1)	
 }

#Did you win?
if(final.choice==car)
 {
  #print("You Win!")
  result<-c(result,1)	
 }
if(final.choice!=car)
 {
  #print("You loose asshole.....")
  result<-c(result,0)	
 }     

return(result)
	
}

monty()

results<-NULL
n<-10000000
for(i in 1:n)
 {
  results<-rbind(results,monty())	
 }
num.switches<-sum(results[,1])
num.dont.switch<-(n-num.switches)
num.wins<-sum(results[,2])
num.losses<-(n-num.wins) 

#print(paste("number of games: ",n))
print(paste("%num switches to wins: ",num.wins/num.switches*100))
print(paste("%num NON-switches to wins: ",num.wins/num.dont.switch*100))

#This is as far as we got:
#[1] "%num switches to wins:  33.391852780732"
#> print(paste("%num NON-switches to wins: ",num.wins/num.dont.switch*100))
#[1] "%num NON-switches to wins:  3.48478715938074"
#> i
#[1] 1890952
#> dim(results)
#[1] 1890951       2
