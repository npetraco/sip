#NOTE: Checks for network.pointer and node.name should be implemented in other R side functions!!!!!

#---------------------------------------------------------------------------------
#To make sure that the vector of values to se in the node are the required length
#---------------------------------------------------------------------------------
check.node.values.length<-function(network.pointer, node.name, candidate.node.values){
  
  flg <- 0
  node.table.frame <- get.table(network.pointer, node.name)
  if( nrow(node.table.frame) != length(candidate.node.values) ){
    flg <- -1
  }
  
  return(flg)
}

#----------------------------------------------------------------------------
#For CPT nodes, make shure the probabilities are "coherent", i.e. add to 1
#when they are supposed to. DOES THE SMILE LIBRARY HAVE A FUNCTION FOR THIS??
#----------------------------------------------------------------------------
check.node.probs.coherence<-function(network.pointer, node.name, candidate.node.values){
  
  node.table.frame <- get.table(network.pointer, node.name)
  offst <- length(unique(node.table.frame[,2]))
  
  st.idx <- seq(1,length(candidate.node.values), offst)
  sp.idx <- (offst-1) + st.idx
  idxs <- cbind(st.idx, sp.idx)
  #print(idxs)
  
  flg<-0
  for(i in 1:nrow(idxs)){
    coherentQ <- (sum(candidate.node.values[idxs[i,1] : idxs[i,2]]) == 1)
    if(coherentQ == FALSE){
      print(paste("Incoherent Probs For:", idxs[i,1], "to", idxs[i,2]))
      flg <- -1 #Flag gets flipped if at least one "incoherent" set found
    }
  }
  
  return(flg)
}