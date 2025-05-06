using System;
using System.Linq;
using System.Collections.Generic;
using ASD.Graphs;

namespace ASD
{
    public class Lab10 : MarshalByRefObject
    {

        /// <param name="labyrinth">Graf reprezentujący labirynt</param>
        /// <param name="startingTorches">Ilość pochodni z jaką startują bohaterowie</param>
        /// <param name="roomTorches">Ilość pochodni w poszczególnych pokojach</param>
        /// <param name="debt>">Ilość złota jaką bohaterowie muszą zebrać</param>
        /// <param name="roomGold">Ilość złota w poszczególnych pokojach</param>
        /// <returns>Informację czy istnieje droga przez labirynt oraz tablicę reprezentującą kolejne wierzchołki na drodze. W przypadku, gdy zwracany jest false, wartość tego pola powinna być null.</returns>
        public (bool routeExists, int[] route) FindEscape(Graph g, int startTorches, int[] torches, int targetGold, int[] gold)
        {
            int n = g.VertexCount;
            int[] route = null;
            
            void Rec(int v, int step, int curGold, int curTorches, int[] vis)
            {
                if (route != null)
                {
                    return;
                }
                if (curTorches == 0 && v != n - 1)
                {
                    return;
                }
                
                if (v == n - 1)
                {
                    if (curGold + gold[v] < targetGold)
                    {
                        return;
                    }
                    LinkedList<int> routeList = new LinkedList<int>();
                    for (int i = 1; i <= step; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            if (vis[j] == i)
                            {
                                routeList.AddLast(j);
                                break;
                            }
                        }
                    }
                    int[] routeTemp = routeList.ToArray();
                    route = (int[])routeTemp.Clone();
                    return;
                }

                foreach (int u in g.OutNeighbors(v))
                {
                    if (vis[u] == 0)
                    {
                        vis[u] = step;
                        Rec(u, step + 1, curGold + gold[v], curTorches + torches[v] - 1, vis);
                        vis[u] = 0;
                    }
                }
            }

            int[] vis = new int[n];
            vis[0] = 1;
            Rec(0, 2, 0, startTorches, vis);
            return (route != null, route);
        }

        /// <param name="labyrinth">Graf reprezentujący labirynt</param>
        /// <param name="startingTorches">Ilość pochodni z jaką startują bohaterowie</param>
        /// <param name="roomTorches">Ilość pochodni w poszczególnych pokojach</param>
        /// <param name="debt">Ilość złota jaką bohaterowie muszą zebrać</param>
        /// <param name="roomGold">Ilość złota w poszczególnych pokojach</param>
        /// <param name="dragonDelay">Opóźnienie z jakim wystartuje smok</param>
        /// <returns>Informację czy istnieje droga przez labirynt oraz tablicę reprezentującą kolejne wierzchołki na drodze. W przypadku, gdy zwracany jest false, wartość tego pola powinna być null.</returns>

        public (bool routeExists, int[] route) FindEscapeWithHeadstart(Graph labyrinth, int startingTorches, int[] roomTorches, int debt, int[] roomGold, int dragonDelay)
        {
            // don't enter a vertex if we have been there previously with more of both torches and gold
            return (false, null);
        }
    }
}
