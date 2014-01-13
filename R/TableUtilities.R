#--------------------------------------
#Assemble CPT, (or other table) levels (characters)
#into a Hugin-like CPT table
#--------------------------------------
generateTableRowLevels<-function(levelInfoList){
  
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
  
  #If it's not a prior node:
  total.tbl<-NULL
  
  for(i in 1:length(childLevels)){
    
    if(length(parentLevels)==1){
      omat <- parentLevels[[1]]
    } else {
      omat <- outer(parentLevels[[1]],parentLevels[[2]], FUN=paste)
    }
    
    if(length(parentLevels)>2){
      for(j in 3:length(parentLevels)){
        omat <- outer(omat, parentLevels[[j]], FUN=paste)
      }
    }
    tbl <- matrix(omat, nrow=length(omat), ncol=1)
    
    #State row comes out as a concatenated string. Split it if there are more than two states
    if(length(parentLevels)>1) {
      tbl.tmp <- sapply(1:nrow(tbl),function(x){strsplit(tbl[x,], " ")}) #A hack to split the strings. Do a better way....
      tbl <- array("xx",c(nrow(tbl), 2))
      for(k in 1:length(tbl.tmp)){
        tbl[k,] <- tbl.tmp[[k]]
      }
      #print(tbl)
    }
    
    #Tack on the child levels, ie. child | parents
    child.col<-rep(childLevels[i],nrow(tbl))
    #print()
    tbl<-cbind(child.col,tbl)
    total.tbl<-rbind(total.tbl,tbl)
  }
  colnames(total.tbl)<-nodeNames
  
  return(total.tbl)

}

#--------------------------------------
#Get the node table
#--------------------------------------
get.table<-function(net.ptr, node.name){
  
  #CHECK THAT NETWORK EXISTS
  if(is.nullptr(net.ptr)==T) {
    print("No Network Defined!")
    return(0)
  }
  
  #CHECK NODE NAME EXISTS
  if(NodeExistsQ(net.ptr, node.name) == -2){ #DSL_OUT_OF_RANGE is -2
    print(paste("No Node:",node.name))
    return(0)
  }
  
  #Query the node typ to see what algs to use
  nodetyp <- NodeType(net.ptr, node.name)
  if(nodetyp == "LIST"){ #decision node
    
    return("NOT SUPPORTED YET.")
    
  } else { #chance or utility node
    level.info <- GetLevelsAssociatedWithNode(net.ptr, node.name)
    state.mat <- generateTableRowLevels(level.info)
    value <- GetNodeTable(net.ptr, node.name)
    
    #print(state.mat)
    #print(value)
    return(data.frame(value,state.mat))
  }
  
    
}

#--------------------------------------
#Set the node table
#If table is a CPT values are probs
#--------------------------------------
set.table<-function(net.ptr, node.name, values){
  
  #PUT IN ERROR TRAPS PRODUCTION!!!!!
  #CHECK NETWORK EXISTS
  #CHECK NODE NAME EXISTS
  #CHECK IF NODE IS A CHANCE NODE, THAT THE PROBS ADD TO 1 WHEN REQUIRED
  
  level.info <- GetLevelsAssociatedWithNode(net.ptr, node.name)
  #COUNT THE LEVELS TO GET THE STATE VECTORS RIGHT!!!!
  state.mat <- generateTableRowLevels(level.info)
  #print(state.mat)
  
  #Count the unique levels for each node involved. The first is the child.
  level.counts.vec <- sapply(1:ncol(state.mat),function(x){length(unique(state.mat[,x]))})
  #Get the state's indices of occurance in the column (node)
  level.idxs.list<-sapply(1:length(level.counts.vec),function(x){list(0:(level.counts.vec[x]-1))})
  
  #print(level.idxs.list)
  #Get the unique state names for each node. The child node is first
  state.level.names <- sapply(1:ncol(state.mat),function(x){list(unique(state.mat[,x]))})
  
  #print(state.level.names)
  
  #Translate each state name to its corresponding integer index. This (interger state vectors) 
  #is what SMILE needs to compute the unique index (row index) for each combination of states 
  state.idx.mat<-array(NA,dim(state.mat))
  for(i in 1:ncol(state.mat)){
    for(j in 1:length(state.level.names[[i]])){
      
      chg.idxs<-which(state.mat[,i] == state.level.names[[i]][j])
      state.idx.mat[chg.idxs,i] <- level.idxs.list[[i]][j]
    }
  }
  
  #SMILE expects the child node levels are the last column:
  state.idx.mat <- cbind(state.idx.mat[,2:ncol(state.idx.mat)], state.idx.mat[,1])
  
  print(state.idx.mat)
  
}