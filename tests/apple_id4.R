library(sip)
#library(gRbase)
library(Rgraphviz)

np<-create.network()
read.network(np, "/Users/npetraco/codes/R/sip/tests/apple.net", "hugin")
np.info<-network.info(np)
node.types <- np.info$node.info[,2]

nodes <- np.info$node.info[,"node.name"]
adjacm <- adjacency.matrix(nodes, np.info$arcs)
gr <- as(adjacm, "graphNEL")
plot(gr, "neato")
plot(gr, "circo")
plot(gr, "fdp")
plot(gr, "dot")
plot(gr, "twopi")
plot(gr)
plot(gr, attrs=list(node = list(fillcolor="lightgrey", fontcolor="red")))
dev.off()

nodes <- buildNodeList(gr)
nodes
edges <- buildEdgeList(gr)
edges

for (i in 1:length(nodes)) {
  
  if(node.types[i] == "utility") {
    nodes[[i]]@attrs$shape <- "circle"
    nodes[[i]]@attrs$fillcolor <- "green"
  }
  if(node.types[i] == "decision") {
    nodes[[i]]@attrs$shape <- "box"
    nodes[[i]]@attrs$fillcolor <- "red"
  }
  if(node.types[i] == "chance") {
    nodes[[i]]@attrs$shape <- "ellipse"
    nodes[[i]]@attrs$fillcolor <- "yellow"
  }
  
}

gr2 <- agopen(gr, edges=edges, nodes=nodes, name="gr2")
plot(gr2)
dev.off()
