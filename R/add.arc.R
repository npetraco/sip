add.arc<-function(network.pointer, parent.node.name, child.node.name) {
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Add A Node Too!!")
  } 
  
  #CHECK TO SEE IF NODES EXISTS
  if(NodeExistsQ(network.pointer, parent.node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",parent.node.name, " Doesn't Exists!")
  }
  if(NodeExistsQ(network.pointer, child.node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",child.node.name, " Doesn't Exists!")
  }
  
  #err.cod doesn't mean anything at this point NEED TO ADD SMILE ERROR-HANDLEING IN PRODUCTION
  err.cod<-AddArc(network.pointer, parent.node.name, child.node.name)
  
}