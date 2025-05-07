using ASD.Graphs;

/// <summary>
/// Klasa rozszerzająca klasę Graph o rozwiązania problemów największej kliki i izomorfizmu grafów metodą pełnego przeglądu (backtracking)
/// </summary>
public static class Lab10GraphExtender
{
    /// <summary>
    /// Wyznacza największą klikę w grafie i jej rozmiar metodą pełnego przeglądu (backtracking)
    /// </summary>
    /// <param name="g">Badany graf</param>
    /// <param name="clique">Wierzchołki znalezionej największej kliki - parametr wyjściowy</param>
    /// <returns>Rozmiar największej kliki</returns>
    /// <remarks>
    /// Nie wolno modyfikować badanego grafu.
    /// </remarks>
    public static int MaxClique(this Graph g, out int[] clique)
    {
        int n = g.VertexCount;
        var best = new List<int>();

        void Rec(int k, List<int> cur)
        {
            var cand = new List<int>();
            for (int i = k; i < n; i++)
            {
                bool neighborsAll = true;
                foreach (int v in cur)
                {
                    neighborsAll &= g.HasEdge(i, v) && g.HasEdge(v, i);
                }
                if (neighborsAll)
                {
                    cand.Add(i);
                }
            }

            if (cand.Count + cur.Count <= best.Count)
            {
                return;
            }
            if (cur.Count > best.Count)
            {
                best.Clear();
                cur.ForEach(x => best.Add(x));
            }
            foreach (int v in cand)
            {
                cur.Add(v);
                Rec(v + 1, cur);
                cur.RemoveAt(cur.Count - 1);
            }
        }

        Rec(0, new List<int>());
        clique = best.ToArray();
        return best.Count;
    }

    /// <summary>
    /// Bada izomorfizm grafów metodą pełnego przeglądu (backtracking)
    /// </summary>
    /// <param name="g">Pierwszy badany graf</param>
    /// <param name="h">Drugi badany graf</param>
    /// <param name="map">Mapowanie wierzchołków grafu h na wierzchołki grafu g (jeśli grafy nie są izomorficzne to null) - parametr wyjściowy</param>
    /// <returns>Informacja, czy grafy g i h są izomorficzne</returns>
    /// <remarks>
    /// 1) Uwzględniamy wagi krawędzi
    /// 3) Nie wolno modyfikować badanych grafów.
    /// </remarks>
    public static bool IsomorphismTest(this Graph<int> g, Graph<int> h, out int[] map)
    {
        int n = g.VertexCount;
        if (n != h.VertexCount)
        {
            map = null;
            return false;
        }

        int[] p = null;
        void Rec(int v, int[] curMap, bool[] used)
        {
            if (v == n)
            {
                p = (int[])curMap.Clone();
                return;
            }

            for (int u = 0; u < n; u++)
            {
                if (!used[u] && h.Degree(v) == g.Degree(u))
                {
                    // try mapping v (in h) to u (in g)
                    // check if it doesn't break the mapping we've established already
                    bool ok = true;
                    for (int i = 0; i < v; i++)
                    {
                        bool inH = h.HasEdge(i, v), inG = g.HasEdge(curMap[i], u);
                        if (inH && inG)
                        {
                            ok &= h.GetEdgeWeight(i, v) == g.GetEdgeWeight(curMap[i], u);
                        }
                        else if (inH != inG)
                        {
                            ok = false;
                        }
                        if (!ok)
                        {
                            break;
                        }
                    }
                    if (ok)
                    {
                        curMap[v] = u;
                        used[u] = true;
                        Rec(v + 1, curMap, used);
                        used[u] = false;
                    }
                }
            }
        }

        Rec(0, new int[n], new bool[n]);
        map = p;
        return map != null;
    }
}

