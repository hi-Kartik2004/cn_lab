#include <stdio.h>

void dijkstras(int graph[10][10], int src, int n)
{
    int distance[n], visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        distance[i] = __INT_MAX__;
    }

    visited[src] = 1;
    distance[src] = 0;
    for (int i = 0; i < n; i++)
    {
        int mini = __INT_MAX__;
        int u = src;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && distance[i] < mini)
            {
                mini = distance[i];
                u = i;
            }
        }

        for (int v = 0; v < n; v++)
        {
            if (distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = graph[u][v] + distance[u];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", distance[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int graph[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    dijkstras(graph, 0, n);

    return 0;
}