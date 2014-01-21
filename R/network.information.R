network.info<-function(network.pointer) {
    
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network!!")
  } 
  
  net.info <- NetworkInfo(network.pointer)
  names(net.info) <- c("number.of.nodes","node.names","node.types")
  
  chance.nodes <- which(net.info[[3]]=="CPT")
  utility.nodes <- which(net.info[[3]]=="TABLE")
  decision.nodes <- which(net.info[[3]]=="LIST")
  
  net.info[[3]][chance.nodes] <- "chance"
  net.info[[3]][utility.nodes] <- "utility"
  net.info[[3]][decision.nodes] <- "decision"
  
  node.info <- cbind(net.info[[2]], net.info[[3]])
  colnames(node.info) <- c("node.name","node.type")
  net.info2 <- list(net.info[[1]], node.info)
  names(net.info2) <- c("number.of.nodes", "node.info")
  
  print(net.info2)
  #print(chance.nodes)
  #print(utility.nodes)
  #print(decision.nodes)
    
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Query Its Info: ", node.name," !!")
  }
  
}