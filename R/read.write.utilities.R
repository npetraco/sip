write.network<-function(network.pointer, file.path){   #ADD FORMAT TYPE!
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Write!!")
  } 
  
  err.cod <- WriteNetwork(network.pointer, file.path)
  
  #Make sure everything went ok
  if(err.cod<0){
    #PRODUCTION ADD ERROR STRING HADLER HERE
    stop("File Not Written:  ",dsl.error.info(network.pointer, err.cod))
  }
  
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting Write File: ", node.name," !!")
  }
  
}
