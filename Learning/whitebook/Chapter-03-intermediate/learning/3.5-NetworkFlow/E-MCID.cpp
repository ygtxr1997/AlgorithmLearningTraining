// M: 匹配 C: 边覆盖 I: 独立集 D: 支配集
// 设图G=(V,E),
// 匹配...................在G中两两没有公共端点的边集合M⊆E
// 边覆盖.................G中的任意顶点都至少是F中某条边的端点的边集合F⊆E
// 独立集.................在G中两两不相连的顶点集合S⊆V
// 顶点覆盖...............G中的任意边都有至少一个端点属于S的顶点集合S⊆V
// 他们之间有如下关系:
// (a). 对于不存在孤立点的图, |最大匹配| + |最小边覆盖| = |V|
// (b). |最大独立集| + |最小顶点覆盖| = |V| (对于普通图是NP困难的)
// (c). 对于二分图, |最大匹配| = |最小顶点覆盖|