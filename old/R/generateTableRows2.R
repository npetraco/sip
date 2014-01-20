generateTableRowLevels2<-function(levelInfoList){
  
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
  tmp.tbls<-rep(list(NULL), length(childLevels))
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
    #print(tbl)
    tmp.tbls[[i]] <- tbl
  }
  
  #print(tmp.tbls)
  chunk.leng <- nrow(tmp.tbls[[1]])
  offst <- length(tmp.tbls)
  nrow.total <- ( offst * chunk.leng )
  ncol.total <- length(unlist(strsplit(tmp.tbls[[1]][1,], " ")))
  total.tbl <- array(-1.0, c(nrow.total, 1+ncol.total) )
  #print(total.tbl)
  
  #Rearrange the rows to be in Hugin order
  count<-1
  for(i in 1:chunk.leng){ #loop over the rows of each sub table
    for(j in 1:offst) {   #loop over the levels of the child node
      trow <- c(childLevels[j], unlist(strsplit(tmp.tbls[[j]][i,], " ")) )
      total.tbl[count, ] <- trow
      count <- count + 1
    }
  }
   
  colnames(total.tbl)<-nodeNames
  
  return(total.tbl)
  
}
