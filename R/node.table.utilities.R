#--------------------------------------
#Assemble CPT, (or other table) levels (characters)
#into a Hugin-like CPT table
#--------------------------------------
generateTableRowLevels<-function(network.pointer, node.name){
   
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("Network Doesn't Exist!!")
  } 
  
  #CHECK TO SEE IF NODES EXISTS
  if(NodeExistsQ(network.pointer, node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",node.name, " Doesn't Exists!")
  }
  
  #Query the node typ to see what algs to use
  nodetyp <- NodeType(network.pointer, node.name)
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  #Decision (LIST) nodes don't have tables/state coordinates in SMILE as far as I can tell.
  if( !(tolower(nodetyp) %in%  c("cpt", "table"))) {
    stop("Node: ",node.name, " Not Supported or Doesn't Have A Table!")
  }
  
  if(nodetyp == "CPT"){ #chance node
    
    levelInfoList <- GetLevelsAssociatedWithChanceOrDecisionNode(network.pointer, node.name)
    
  }
  if(nodetyp == "TABLE"){ #utility node
    
    levelInfoList <- GetLevelsAssociatedWithChanceOrDecisionNode(network.pointer, node.name)
    
  }
  names(levelInfoList) <- c("Names", "Levels")
  
  nodeNames <- levelInfoList$Names #Child, Parent 1, Parent 2, etc. See API for info on parent order.
  levelLists <- levelInfoList$Levels
  childLevels <- levelLists[[1]]
  parentLevels <- levelLists[-1]
  
  #If it's a prior node:
  if(length(levelLists) == 1){
    total.tbl = matrix(levelLists[[1]], nrow=length(childLevels), ncol=1)
    colnames(total.tbl)<-nodeNames
    
    return(total.tbl)
  }
  
  #If it's not a prior node
  if(nodetyp == "CPT"){ #chance node
    
    state.coords.mat <- GetChanceOrUtilityNodeStateCoords(network.pointer, node.name)
    
  }
  if(nodetyp == "TABLE"){ #utility node
    
    state.coords.mat <- GetChanceOrDecisionNodeStateCoords(network.pointer, node.name)
        
  }
  
  #Put the child column first:
  state.coords.mat <- cbind( state.coords.mat[,ncol(state.coords.mat)], state.coords.mat[,-ncol(state.coords.mat)] )
  colnames(state.coords.mat) <- nodeNames
  
  #child (first column)
  state.level.mat <- NULL
  tmp.col <- sapply(1:nrow(state.coords.mat), function(x){childLevels[1+state.coords.mat[x,1]]})
  state.level.mat <- cbind(state.level.mat, tmp.col )
  #parent columns (the rest)
  for(i in 1:length(parentLevels)) {
    tmp.col <- sapply(1:nrow(state.coords.mat), function(x){parentLevels[[i]][1+state.coords.mat[x,i+1]]})
    state.level.mat <- cbind(state.level.mat, tmp.col )
  }
  colnames(state.level.mat) <- nodeNames
  
  return(state.level.mat)
  
}


#--------------------------------------
#Get the node table
#--------------------------------------
get.table<-function(network.pointer, node.name){
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("Network Doesn't Exist!!")
  } 
  
  #CHECK TO SEE IF NODES EXISTS
  if(NodeExistsQ(network.pointer, node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",node.name, " Doesn't Exists!")
  }
  
  #Query the node typ to see what algs to use
  nodetyp <- NodeType(network.pointer, node.name)
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  if( !(tolower(nodetyp) %in%  c("cpt", "list", "table"))) {
    stop("Node type: ", nodetyp, " not supported.")
  }
  
  if(nodetyp == "LIST"){ #decision node
    stop("Decision nodes don't have tables!")    
  }
  
  if(nodetyp == "CPT") { #chance node
    
    #level.info <- GetLevelsAssociatedWithChanceOrDecisionNode(network.pointer, node.name)
    #names(level.info)<-c("Names", "Levels") #Necessary to do this bec having trouble with dyn.load-ing Rcpp compiled code using Rcpp::Names
    state.mat <- generateTableRowLevels(network.pointer, node.name)
    value <- GetNodeTable(network.pointer, node.name)
    
    #print(state.mat)
    #print(value)
    return(data.frame(value,state.mat))
  }
  if(nodetyp == "TABLE"){ #utility node
    
    #BROKEN!!!!!!!!!!
    
    #level.info <- GetLevelsAssociatedWithUtilityNode(network.pointer, node.name)
    #names(level.info)<-c("Names", "Levels") #Necessary to do this bec having trouble with dyn.load-ing Rcpp compiled code using Rcpp::Names
    state.mat <- generateTableRowLevels(network.pointer, node.name)
    value <- GetNodeTable(network.pointer, node.name)
    
    return(data.frame(value,state.mat))
    
  }

}

#--------------------------------------
#Set the node table
#If table is a CPT values are probs
#--------------------------------------
set.table<-function(network.pointer, node.name, values, printQ=FALSE){
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(network.pointer)==T) {
    stop("Network Doesn't Exist!!")
  } 
  
  #CHECK TO SEE IF NODES EXISTS
  if(NodeExistsQ(network.pointer, node.name)== -2){ #DSL_OUT_OF_RANGE is -2
    stop("Node: ",node.name, " Doesn't Exists!")
  }
  
  #Query the node typ to see what algs to use
  nodetyp <- NodeType(network.pointer, node.name)
  
  #CHECK TO SEE THAT ONLY A SUPPORTED NODE TYPE IS REQUESTED
  if( !(tolower(nodetyp) %in%  c("cpt", "table"))) {
    stop("Node type: ", nodetyp, " not supported.")
  }
  
  #CHECK THAT THE VECTOR OF VALUES TO ADD TO THE NODE ARE THE CORRECT LENGTH
  check.node.values.length(network.pointer, node.name, values)
  
  #----
  if(nodetyp == "CPT") { #chance node
    
    #NODE CHECK FOR NULL VALUES
    if(is.null(values)){
      stop("Assign numeric values for the node states!!")
    }
    
    #CHECK PROBS THE RIGHT LENGTH AND ARE "COHERENT" FOR PRODUCTION
    err.cod1 <- check.node.values.length(network.pointer, node.name, values)
    if(err.cod1 == -1){
      stop("Prob vector is the wrong length!!")
    }
    err.cod2 <- check.node.probs.coherence(network.pointer, node.name, values)
    if(err.cod2 == -1){
      stop("Found Incoherent Probs!!")
    }
    
    #Once past all of that, assign the values
    level.info <- GetLevelsAssociatedWithChanceOrDecisionNode(network.pointer, node.name)
    names(level.info)<-c("Names", "Levels") #Necessary to do this bec having trouble with dyn.load-ing Rcpp compiled code using Rcpp::Names
    state.mat <- generateTableRowLevels(level.info)
    value <- SetNodeTable(network.pointer, node.name, values)
  }
  if(nodetyp == "TABLE"){ #utility node
    #NODE CHECK FOR NULL VALUES
    if(is.null(values)){
      stop("Assign numeric values for the node states!!")
    }
    
    #CHECK UTILITIES ARE THE CORRECT LENGTH
    err.cod1 <- check.node.values.length(network.pointer, node.name, values)
    print(err.cod1)
    if(err.cod1 == -1){
      stop("Utility vector is the wrong length!!")
    } 
  
    level.info <- GetLevelsAssociatedWithUtilityNode(network.pointer, node.name)
    names(level.info)<-c("Names", "Levels") #Necessary to do this bec having trouble with dyn.load-ing Rcpp compiled code using Rcpp::Names
    state.mat <- generateTableRowLevels(level.info)
    value <- SetNodeTable(network.pointer, node.name, values)
  }
  
  if(printQ==TRUE){
    print(get.table(network.pointer, node.name))
  }
  
}