delete.arc<-function(network.pointer, parent.node.name, child.node.name) {
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Delete An Arc From!!")
  } 
  
  #CHECK TO SEE IF NODES EXISTS
  if(NodeExistsQ(network.pointer, parent.node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",parent.node.name, " Doesn't Exists!")
  }
  if(NodeExistsQ(network.pointer, child.node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",child.node.name, " Doesn't Exists!")
  }
  
  #Delete the Arc
  err.cod <- DeleteArc(network.pointer, parent.node.name, child.node.name)
  
  #Make sure everything went ok
  if(err.cod<0){
    #PRODUCTION ADD ERROR STRING HADLER HERE
    stop("Something went wrong in DeleteArc:  ",dsl.error.info(network.pointer, err.cod))
  }
  
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Delete Arc: ", node.name," !!")
  }
  
}