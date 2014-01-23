adjacency.matrix<-function(node.names, arc.mat) {
  
  adj.mat <- array(0, c(length(node.names), length(node.names)))
  for(i in 1:nrow(arc.mat)) {
    ridx <- which(node.names == arc.mat[i,1])
    cidx <- which(node.names == arc.mat[i,2])
    adj.mat[ridx, cidx] <- 1
  }
  
  colnames(adj.mat) <- node.names
  rownames(adj.mat) <- node.names
  
  return(adj.mat)
  
}