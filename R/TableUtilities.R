#--------------------------------------
#Assemble CPT, (or other table) levels (characters)
#into a Hugin-like CPT table
#--------------------------------------
GenerateTableRowLevels<-function(levelInfoList){
  
  nodeNames <- levelInfoList$Names #Child, Parent 1, Parent 2, etc. See API for info on parent order.
  levelLists <- levelInfoList$Levels
  childLevels <- levelLists[[1]]
  parentLevels <- levelLists[-1]
  
  #num.rows <- length(childLevels) * prod(sapply(1:length(parentLevels),function(x){length(parentLevels[[x]])}))
  #print(num.rows)
  total.tbl<-NULL
  
  for(i in 1:length(childLevels)){
    
    omat <- outer(parentLevels[[1]],parentLevels[[2]], FUN=paste)
    if(length(parentLevels)>2){
      for(j in 3:length(parentLevels)){
        omat <- outer(omat, parentLevels[[j]], FUN=paste)
      }
    }
    tbl <- matrix(omat, nrow=length(omat), ncol=1)
    tbl.tmp <- sapply(1:nrow(tbl),function(x){strsplit(tbl[x,], " ")}) #A hack to split the strings. Do a better way....
    tbl <- array("xx",c(nrow(tbl), 2))
    for(k in 1:length(tbl.tmp)){
      tbl[k,] <- tbl.tmp[[k]]
    }
    #print(tbl)
    child.col<-rep(childLevels[i],nrow(tbl))
    #print()
    tbl<-cbind(child.col,tbl)
    total.tbl<-rbind(total.tbl,tbl)
  }
  colnames(total.tbl)<-nodeNames
  
  return(total.tbl)
    
  
}