delete.node<-function(network.pointer, node.name) {
    
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Delete A Node From!!")
  } 
  
  #CHECK TO SEE IF NODE NAME ALREADY EXISTS
  if(NodeExistsQ(network.pointer, node.name) == -2){ #DSL_OUT_OF_RANGE is -2
    stop("No Node Named: ",node.name, " In This Network!")
  }
  

  #Delete the node
  DeleteNode(network.pointer, node.name)
    
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Delete Node: ", node.name," !!")
  }
  
}