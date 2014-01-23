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


show.network<-function(network.pointer){
  
  network.info<-network.info(network.pointer)
  nodes.names <- network.info$node.info[,"node.name"]
  node.types <- network.info$node.info[,2]
  
  adjac.mat <- adjacency.matrix(nodes.names, network.info$arcs)
  graph.obj <- as(adjac.mat, "graphNEL")
  
  nodes.info <- buildNodeList(graph.obj)
  edges.info <- buildEdgeList(graph.obj)
  
  #Set attributes (shape/color) for the different types of nodes 
  for (i in 1:length(nodes.info)) {
    if(node.types[i] == "utility") {
      nodes.info[[i]]@attrs$shape <- "circle"
      nodes.info[[i]]@attrs$fillcolor <- "green"
    }
    if(node.types[i] == "decision") {
      nodes.info[[i]]@attrs$shape <- "box"
      nodes.info[[i]]@attrs$fillcolor <- "red"
    }
    if(node.types[i] == "chance") {
      nodes.info[[i]]@attrs$shape <- "ellipse"
      nodes.info[[i]]@attrs$fillcolor <- "yellow"
    }  
  }
  
  graph.obj.prettier <- agopen(graph.obj, edges=edges.info, nodes=nodes.info, name="pretty graph")
  plot(graph.obj.prettier)
  
}