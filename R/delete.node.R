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
  err.cod <- DeleteNode(network.pointer, node.name)
  
  #Make sure everything went ok
  if(err.cod<0){
    #PRODUCTION ADD ERROR STRING HADLER HERE
    stop("Something went wrong in DeleteNode: ", dsl.error.info(network.pointer, err.cod))
  }  
    
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Delete Node: ", node.name," !!")
  }
  
}