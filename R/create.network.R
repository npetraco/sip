#----------------------------------
#R side, create the SMILE network
#----------------------------------
create.network<-function(){
  
  network.pointer <- CreateSmlieNetwork()
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    print("No Network Created!!")
    return(0)
  } else {
    return(network.pointer)
  }  
  
}