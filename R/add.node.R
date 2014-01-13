add.node<-function(network.pointer, node.name, node.type, node.levels=NULL) {
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    print("There Is No Network To Add A Node Too!!")
    return(0)
  } 
  
  #CHECK TO SEE IF NODE NAME ALREADY EXISTS
  if(NodeExistsQ(network.pointer, node.name) != -2){ #DSL_OUT_OF_RANGE is -2
    print(paste("Node:",node.name, "already exists!"))
    return(0)
  }
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  if( !(tolower(node.type) %in%  c("chance", "decision", "utility"))) {
    print(paste("Node type:",node.type, "not supported."))
  }
  
  #CHECK THAT IF UTILITY REQUESTED, NO or NULL LEVELS ARE GIVEN
  if(tolower(node.type)=="utility" & !is.null(node.levels) ) {
    print("Utility nodes dont get levels!")
    return(0)
  }
  
  #CHECK THAT IF CHANCE OR DECISION IS REQUESTED LEVELS ARE GIVEN
  if(tolower(node.type) !="utility" & is.null(node.levels) ) {
    print(paste("Levels Must Be Given For:",node.type,"nodes!!"))
    return(0)
  }
  
  
  modified.network.pointer<-AddNode(network.pointer, node.name, node.type, node.levels)
  #CHECK TO SEE IF THE POINTER GOT RETURNED
  if(is.nullptr(modified.network.pointer)==T) {
    print("Node Not Added!!")
    return(0)
  } 
  
  return(modified.network.pointer)
  
}