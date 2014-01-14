add.node<-function(network.pointer, node.name, node.type, node.levels=NULL) {
    
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("There Is No Network To Add A Node Too!!")
  } 
  
  #CHECK TO SEE IF NODE NAME ALREADY EXISTS
  if(NodeExistsQ(network.pointer, node.name) != -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",node.name, " already exists!")
  }
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  if( !(tolower(node.type) %in%  c("chance", "decision", "utility"))) {
    stop("Node type: ",node.type, " not supported.")
  }
  
  #CHECK THAT IF UTILITY REQUESTED, NO or NULL LEVELS ARE GIVEN
  if(tolower(node.type)=="utility" & !is.null(node.levels) ) {
    stop("Utility nodes dont get levels!")
  }
  
  #CHECK THAT IF CHANCE OR DECISION IS REQUESTED LEVELS ARE GIVEN
  if(tolower(node.type) !="utility" & is.null(node.levels) ) {
    stop("Levels Must Be Given For: ",node.type," Nodes!!")
  }

  #Add the node
  err.cod<-AddNode(network.pointer, node.name, node.type, node.levels)
  
  #Make sure everything went ok
  if(err.cod!=0){
    stop("Something went wrong in AddNode. Check network pointer for problems!!!!!")
  }
  
  if(is.nullptr(network.pointer)==T) {
    stop("Network Got Killed When Attempting To Add Node: ", node.name," !!")
  }
  
}