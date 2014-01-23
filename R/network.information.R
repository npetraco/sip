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
  
  node.info <- cbind(net.info[[2]], net.info[[3]], net.info[[4]])
  
  edgelist<-NULL
   for(i in 1:net.info$number.of.nodes){
     child.idxs<-net.info[[5]][[i]]
    
     if(length(child.idxs)>0){
       
       parent.node.name <- net.info[[2]][[i]]
       elv.tmp <- strsplit(paste(parent.node.name, net.info$node.names[ child.idxs ]), " ")
       
       elm.tmp <- t(sapply(1:length(elv.tmp), function(x){elv.tmp[[x]]}))
       edgelist<-rbind(edgelist, elm.tmp)
     }
   }
  
  colnames(node.info) <- c("node.name","node.type", "num.node.children")
  net.info2 <- list(net.info[[1]], node.info, edgelist)
  names(net.info2) <- c("number.of.nodes", "node.info", "arcs")
      
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Query Its Info: ", node.name," !!")
  }
  
  return(net.info2)
  
}