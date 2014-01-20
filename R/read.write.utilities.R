#-----------------------------------------
#Write one of the SMILE supported
#file types. There are more than here.
#See the API on DSL_Network object
#-----------------------------------------
write.network<-function(network.pointer, file.path, file.type="hugin"){
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Write!!")
  } 
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  if( !(tolower(file.type) %in%  c("hugin", "netica", "interchange", "xdsl"))) {
    stop("File format: ",file.type, " not supported.")
  }
  
  err.cod <- WriteNetwork(network.pointer, file.path, file.type)
  
  #Make sure everything went ok
  if(err.cod<0){
    stop("File Not Written:  ",dsl.error.info(network.pointer, err.cod))
  }
  
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting Write File: ", node.name," !!")
  }
  
}


#-----------------------------------------
#Read one of the SMILE supported
#file types. There are more than here.
#See the API on DSL_Network object
#-----------------------------------------
read.network<-function(network.pointer, file.path, file.type="hugin"){
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Write!!")
  } 
  
  #CHECK TO SEE THAT ONLY A SUPPORTED FORMAT IS REQUESTED
  if( !(tolower(file.type) %in%  c("hugin", "netica", "interchange", "xdsl"))) {
    stop("File format: ",file.type, " not supported.")
  }
  
  err.cod <- ReadNetwork(network.pointer, file.path, file.type)
  
  #Make sure everything went ok
  if(err.cod<0){
    stop("File Not Read:  ",dsl.error.info(network.pointer, err.cod))
  }
  
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting Read File: ", node.name," !!")
  }
  
}
