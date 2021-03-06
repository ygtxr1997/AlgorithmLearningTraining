// ---------------------------------------------------------------------
// 题目描述:
// 给定一个 n 个顶点, 边长为 1 的有向图的邻接矩阵.
// 求这个图里长度为 k 的路径的总数, 路径中同一条边允许通过多次.
// 1 <= n <= 100
// 1 <= k <= 1e9
// ---------------------------------------------------------------------
// 思路:
// 用01邻接矩阵代表路径长度, 矩阵的 k 次幂中为 1 的数量就是长度为 k 的路径长度.
// 时间复杂度O(n^3 * log(n)).
// ---------------------------------------------------------------------