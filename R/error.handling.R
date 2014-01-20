dsl.error.info<-function(network.pointer, error.code) {
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network!!")
  } 
  
  dsl.err.name <- ErrorCode2String(error.code);
  if(dsl.err.name == "NOT AN ERROR CODE"){
    print(paste(dsl.err.name,": ",error.code,sep=""))
  } else {
    print(dsl.err.name)
  }
  
}
