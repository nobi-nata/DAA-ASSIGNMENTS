#include "header.h"
#include <limits.h>
#include <stdlib.h>

// ANY STATIC FUNCTIONS ARE UP HERE

static void swap(airport_t *a, airport_t *b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}

static int binarySearch(const int arr[], int l, int r, int x)
{
    int m = 0;
    while (l <= r)
    {
        m = l + (r - l) / 2;

        // Check if x is present at mid
        if (arr[m] == x)
            return m + 1;

        // If x greater, ignore left half
        if (arr[m] < x)
            l = m + 1;

        // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    // if we reach here, then element was
    // not present
    return m + 1;
}

static void Shift_table(const char pat[], int size, int Table[])
{

    for (int i = 0; i < 128; i++)
    {
        Table[i] = size;
    }
    for (int j = 0; j <= size - 2; j++)
    {
        Table[pat[j] - '0'] = size - 1 - j;
    }
}

static int predicate(const airport_t *a, const airport_t *b)
{
    int i = 0;
    while (a->airport_name[i] != 0 && b->airport_name[i] != 0)
    {
        if (a->airport_name[i] > b->airport_name[i])
        {
            return 0;
        }
        else if (a->airport_name[i] < b->airport_name[i])
        {
            return 1;
        }
        i += 1;
    }
    return 1;
}

static int partition(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{

    // select the rightmost element as pivot
    airport_t pivot = airport_list[high];

    // pointer for greater element
    int i = (low - 1);

    // compare them with the pivot
    for (int j = low; j < high; j++)
    {
        if (predicate_func(&airport_list[j], &pivot))
        {
            // if element smaller than pivot is found
            i++;
            // swap element at i with element at j
            swap(&airport_list[i], &airport_list[j]);
        }
    }
    // swap the pivot element with the greater element at i
    swap(&airport_list[i + 1], &airport_list[high]);
    // return the partition point
    return (i + 1);
}

static void quickSort(int n, airport_t airport_list[n], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (low < high)
    {
        // find the pivot element such that
        int pi = partition(n, airport_list, low, high, predicate_func);
        // recursive call on the left of pivot
        quickSort(n, airport_list, low, pi - 1, predicate_func);
        // recursive call on the right of pivot
        quickSort(n, airport_list, pi + 1, high, predicate_func);
    }
}

static void enqueue(int *q, int *top, int n)
{
    *top += 1;
    q[*top] = n;
}

static int dequeue(int *q, int *top)
{
    int n = q[0];
    for (int i = 1; i < *top + 1; i++)
        q[i - 1] = q[i];
    *top -= 1;
    return n;
}

// function for bfs traversal
static void bfs(int *q, int *top, int n, int visited[][n], const connection_t connections[][n], int i)
{
    if (*top != -1)
    {
        int k = dequeue(q, top);
        for (int j = 0; j < n; j++)
        {
            if (connections[k][j].distance != INT_MAX && connections[k][j].distance != 0 && visited[i][j] == 0)
            {
                enqueue(q, top, j);
                visited[i][j] = 1;
                bfs(q, top, n, visited, connections, i);
            }
        }
    }
    else
        return;
}

static void Inc_ord(int *r_1, int *r_2, int m, int n, int *min_len, const connection_t connections[m + 2][m + 2], int *path)
{
    int length = 0, paths[m + 1];
    paths[0] = path[0];
    if (n == 2)
    {
        int flag = 0;
        for (int i = 0; i < m; i++)
        {
            if (flag == 0)
            {
                if (connections[paths[i]][r_1[i]].distance != INT_MAX)
                {
                    length += connections[paths[i]][r_1[i]].distance;
                    paths[i + 1] = r_1[i];
                }
                else
                {
                    flag = 1;
                }
            }
        }
        if (flag == 0 && connections[r_1[m - 1]][paths[0]].distance != INT_MAX)
        {
            length += connections[r_1[m - 1]][paths[0]].distance;
        }
        else
        {
            flag = 1;
        }
        if (flag == 0)
        {
            *min_len = length;
            for (int i = 0; i < m + 1; i++)
                path[i] = paths[i];
        }
        int temp = r_2[0];
        r_2[0] = r_2[1];
        r_2[1] = temp;
        flag = 0;
        length = 0;
        for (int i = 0; i < m; i++)
        {
            if (flag == 0)
            {
                if (connections[paths[i]][r_1[i]].distance != INT_MAX)
                {
                    length += connections[paths[i]][r_1[i]].distance;
                    paths[i + 1] = r_1[i];
                }
                else
                {
                    flag = 1;
                }
            }
        }
        if (flag == 0 && connections[r_1[m - 1]][paths[0]].distance != INT_MAX)
        {
            length += connections[r_1[m - 1]][paths[0]].distance;
        }
        else
        {
            flag = 1;
        }
        if (flag == 0)
        {
            *min_len = length;
            for (int i = 0; i < m + 1; i++)
                path[i] = paths[i];
        }
        temp = r_2[0];
        r_2[0] = r_2[1];
        r_2[1] = temp;
    }
    else
    {
        int i = 0;
        while (i < n)
        {
            int temp = r_2[i];
            for (int j = i - 1; j >= 0; j--)
            {
                r_2[j + 1] = r_2[j];
            }
            r_2[0] = temp;
            Inc_ord(r_1, r_2 + 1, m, n - 1, min_len, connections, path);
            temp = r_2[0];
            for (int j = 1; j <= i; j++)
            {
                r_2[j - 1] = r_2[j];
            }
            r_2[i] = temp;
            i++;
        }
    }
}

// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
    connection_t p[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p[i][j].distance = connections[i][j].distance;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (p[k][i].distance == INT_MAX)
                {
                    if (p[k][j].distance != INT_MAX && p[j][i].distance != INT_MAX)
                        p[k][i].distance = p[k][j].distance + p[j][i].distance;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[i][j].distance == INT_MAX)
                return 0;
        }
    }
    return 1;
}

int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
    int count = INT_MAX, top = -1;
    int visited[n], prev[n], queue[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        prev[i] = -1;
    }
    visited[src->num_id] = 1;
    enqueue(queue, &top, src->num_id);
    // bfs traversal
    while (top != -1)
    {
        int a = dequeue(queue, &top);
        for (int j = 0; j < n; j++)
        {
            if (connections[a][j].distance != INT_MAX && connections[a][j].distance != 0 && visited[j] == 0)
            {
                prev[j] = a;
                enqueue(queue, &top, j);
                visited[j] = 1;
            }
        }
    }
    // count no of flights changed b/w source and destination
    if (prev[dest->num_id] != -1)
    {
        count = 0;
        int ver = dest->num_id;
        while (ver != src->num_id)
        {
            ver = prev[ver];
            count += 1;
        }
    }
    if (count <= k)
        return 1;
    return 0;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int visited[n][n], queue[n], top = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = 0;
        }
        visited[i][i] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        top = -1;
        enqueue(queue, &top, i);
        bfs(queue, &top, n, visited, connections, i);
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[src->num_id][i] == 1 && src->num_id != i)
        {
            if (visited[i][src->num_id] == 1)
                return 1;
        }
    }
    return 0;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    quickSort(n, airport_list, 0, n - 1, predicate_func);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    int Max_prefix;
    int prefix[n - 1];
    quickSort(n, airports, 0, n - 1, predicate);
    for (int k = 0; k < n; k++)
    {
        int count = 0;
        int j = 0;
        int flag = 0;
        while (flag != 1 && airports[k].airport_name[j] != '\0' && airports[k + 1].airport_name[j] != '\0')
        {
            if (airports[k].airport_name[j] == airports[k + 1].airport_name[j])
            {
                count++;
                j++;
            }
            else
            {
                flag = 1;
                j++;
            }
        }
        prefix[k] = count;
    }
    Max_prefix = prefix[0];
    ans.first = airports[0].num_id;
    ans.second = airports[1].num_id;
    for (int i = 1; i < n - 1; i++)
    {
        if (prefix[i] > Max_prefix)
        {
            Max_prefix = prefix[i];
            ans.first = airports[i].num_id;
            ans.second = airports[i + 1].num_id;
        }
    }
    if (Max_prefix == 0)
    {
        ans.first = -1;
        ans.second = -1;
    }
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    return binarySearch(entry_fee, 0, n - 1, amount);
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int size = 0;
    int k = 0;
    while (pat[k] != '\0')
    {
        size++;
        k++;
    }
    int Table[128];
    Shift_table(pat, size, Table);
    for (int j = 0; j < n; j++)
    {
        int i = size - 1;
        int incr = 0;
        int flag = 0;
        while (airports[j].airport_name[incr] != '\0')
        {
            incr++;
        }
        while (!flag && i <= incr - 1)
        {
            int k = 0;
            while (k <= size - 1 && pat[size - 1 - k] == airports[j].airport_name[i - k])
            {
                k += 1;
            }
            if (k == size)
            {
                contains[j] = 1;
                flag = 1;
            }
            else
            {
                i = i + Table[airports[j].airport_name[i] - '0'];
            }
        }
        if (!flag)
        {
            contains[j] = 0;
        }
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int trip_seq[n][n - 1];
    int route[n - 2], path[n - 1];
    int min_len = INT_MAX, length = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                if (j < i)
                {
                    trip_seq[i][j] = j;
                }
                else
                {
                    trip_seq[i][j - 1] = j;
                }
            }
        }
    }
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - 2; i++)
        {
            route[i] = trip_seq[j][i + 1];
        }
        path[0] = trip_seq[j][0];
        Inc_ord(route, route, n - 2, n - 2, &length, connections, path);
        if (length < min_len)
        {
            min_len = length;
            for (int l = 0; l < n - 1; l++)
            {
                trip_order[l] = path[l];
            }
        }
    }
    if (min_len == INT_MAX)
        min_len = -1;
    return min_len;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int ver_1, ver_2, edge = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    visited[0] = 1;
    int min_cost = 0;
    while (edge < n - 1)
    {
        int minimum = INT_MAX;
        ver_1 = 0;
        ver_2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (visited[j] == 0 && connections[i][j].time != INT_MAX)
                    {
                        if (minimum > connections[i][j].time)
                        {
                            minimum = connections[i][j].time;
                            ver_1 = i;
                            ver_2 = j;
                        }
                    }
                }
            }
        }
        min_cost = min_cost + minimum;
        visited[ver_2] = 1;
        edges[edge].first = ver_1;
        edges[edge].second = ver_2;
        edge += 1;
    }
    return min_cost;
}

void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    int startnode = src->num_id;
    {

        connection_t cost[n][n];
        int times[n];
        int visited[n], count, mintime, nextnode, i, j;

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (connections[i][j].time == INT_MAX)
                {
                    cost[i][j].distance = INT_MAX;
                    cost[i][j].time = INT_MAX;
                }
                else
                    cost[i][j] = connections[i][j];
        for (i = 0; i < n; i++)
        {
            times[i] = cost[startnode][i].time;
            visited[i] = 0;
        }
        times[startnode] = 0;
        visited[startnode] = 1;
        count = 1;
        while (count < n - 1)
        {
            mintime = INT_MAX;
            // nextnode gives the node at minimum distance
            for (i = 0; i < n; i++)
                if (times[i] < mintime && !visited[i])
                {
                    mintime = times[i];
                    nextnode = i;
                }
            // check if a better path exists through nextnode
            visited[nextnode] = 1;
            for (i = 0; i < n; i++)
                if (!visited[i])
                    if (mintime + cost[nextnode][i].time < times[i])
                    {
                        times[i] = mintime + cost[nextnode][i].time;
                    }
            count++;
        }

        for (int j = 0; j < k; j++)
        {
            costs[j] = times[destinations[j]];
        }
    }
}
// END
