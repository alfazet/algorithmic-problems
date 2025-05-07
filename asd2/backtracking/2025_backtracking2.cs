using System;
using System.Collections.Generic;
using System.Linq;
using ASD.Graphs;

namespace ASD
{
    public class Lab08 : MarshalByRefObject
    {
        /// <summary>
        /// Znajduje cykl rozpoczynający się w stolicy, który dla wybranych miast,
        /// przez które przechodzi ma największą sumę liczby ludności w tych wybranych
        /// miastach oraz minimalny koszt.
        /// </summary>
        /// <param name="cities">
        /// Graf miast i połączeń między nimi.
        /// Waga krawędzi jest kosztem przejechania między dwoma miastami.
        /// Koszty transportu między miastami są nieujemne.
        /// </param>
        /// <param name="citiesPopulation">Liczba ludności miast</param>
        /// <param name="meetingCosts">
        /// Koszt spotkania w każdym z miast.
        /// Dla części pierwszej koszt spotkania dla każdego miasta wynosi 0.
        /// Dla części drugiej koszty są nieujemne.
        /// </param>
        /// <param name="budget">Budżet do wykorzystania przez kandydata.</param>
        /// <param name="capitalCity">Numer miasta będącego stolicą, z której startuje kandydat.</param>
        /// <param name="path">
        /// Tablica dwuelementowych krotek opisująca ciąg miast, które powinen odwiedzić kandydat.
        /// Pierwszy element krotki to numer miasta do odwiedzenia, a drugi element decyduje czy
        /// w danym mieście będzie organizowane spotkanie wyborcze.
        /// 
        /// Pierwszym miastem na tej liście zawsze będzie stolica (w której można, ale nie trzeba
        /// organizować spotkania).
        /// 
        /// Zakładamy, że po odwiedzeniu ostatniego miasta na liście kandydat wraca do stolicy
        /// (na co musi mu starczyć budżetu i połączenie między tymi miastami musi istnieć).
        /// 
        /// Jeżeli kandydat nie wyjeżdża ze stolicy (stolica jest jedynym miastem, które odwiedzi),
        /// to lista `path` powinna zawierać jedynie jeden element: stolicę (wraz z informacją
        /// czy będzie tam spotkanie czy nie). Nie są wtedy ponoszone żadne koszty podróży.
        /// 
        /// W pierwszym etapie drugi element krotki powinien być zawsze równy `true`.
        /// </param>
        /// <returns>
        /// Liczba mieszkańców, z którymi spotka się kandydat.
        /// </returns>
        public int ComputeElectionCampaignPath(Graph<int> g, int[] population,
            double[] cost, double budget, int capitalCity, out (int, bool)[] path)
        {
            int n = g.VertexCount;
            State resState = new State(n, budget);
            resState.VisCities.Add(capitalCity);
            State curState = new State(n, budget);
            HashSet<int> visCitiesSet = new HashSet<int>();

            void TravelFrom(int v)
            {
                if (v == capitalCity && visCitiesSet.Count == 1 && curState.IsBetter(resState))
                {
                    resState = new State(curState);
                }

                foreach (var edge in g.OutEdges(v))
                {
                    if ((!curState.VisCities.Contains(edge.To) || edge.To == capitalCity) && curState.RemMoney >= edge.Weight)
                    {
                        curState.RemMoney -= edge.Weight;
                        Rec(edge.To);
                        curState.RemMoney += edge.Weight;
                    }
                }
            }
            
            void Rec(int v)
            {
                if (v == capitalCity && visCitiesSet.Count > 1)
                {
                    if (curState.IsBetter(resState))
                    {
                        resState = new State(curState);
                    }
                    return;
                }
                curState.VisCities.Add(v);
                visCitiesSet.Add(v);
                if (curState.RemMoney >= cost[v])
                {
                    curState.RemMoney -= cost[v];
                    curState.PeopleMet += population[v];
                    curState.IsMeeting[v] = true;
                    TravelFrom(v);
                    curState.RemMoney += cost[v];
                    curState.PeopleMet -= population[v];
                    curState.IsMeeting[v] = false;
                }
                if (cost[v] > 0)
                {
                    TravelFrom(v);   
                }
                curState.VisCities.Remove(v);
                visCitiesSet.Remove(v);
            }
            Rec(capitalCity);
            
            int k = resState.VisCities.Count;
            path = new (int, bool)[k];
            for (int i = 0; i < k; i++)
            {
                path[i] = (resState.VisCities[i], resState.IsMeeting[i]);
            }
            return resState.PeopleMet;
        }
        
        private struct State
        {
            public List<int> VisCities { get; set; }
            public bool[] IsMeeting { get; set; }
            public int PeopleMet { get; set; }
            public double RemMoney { get; set; }

            public State(int n, double budget)
            {
                VisCities = new List<int>();
                IsMeeting = new bool[n];
                PeopleMet = 0;
                RemMoney = budget;
            }

            public State(State other)
            {
                VisCities = new List<int>(other.VisCities);
                IsMeeting = (bool[])other.IsMeeting.Clone();
                PeopleMet = other.PeopleMet;
                RemMoney = other.RemMoney;
            }

            public bool IsBetter(State other)
            {
                if (PeopleMet != other.PeopleMet)
                {
                    return PeopleMet > other.PeopleMet;
                }
                return RemMoney > other.RemMoney;
            }
        }
    }
}
