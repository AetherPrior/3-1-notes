#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define int long long
int tq[3] = {2, 3, 5};
typedef struct
{
    int index;
    int arr_time;
    int cpu_time;
    int priority;
} process;
typedef struct
{
    int n;
    process arr[1000];
} heap;

void init_heap(heap *h)
{
    h->n = 0;
}

void heapify(heap *h1, int node)
{
    int size = h1->n;
    int parent = (node - 1) / 2;
    while (h1->arr[node].cpu_time < h1->arr[parent].cpu_time && parent != node)
    {
        process p1 = h1->arr[node];
        h1->arr[node] = h1->arr[parent];
        h1->arr[parent] = p1;
        node = parent;
        parent = (node - 1) / 2;
    }
}
void buildMinHeap(heap *h1)
{
    int node = 0;
    int child = 1;
    while (child < h1->n)
    {
        child = node * 2 + 1;
        if (h1->arr[node].cpu_time > h1->arr[child].cpu_time)
        {
            process p1 = h1->arr[node];
            h1->arr[node] = h1->arr[child];
            h1->arr[child] = p1;
        }
        else
        {
            break;
        }
        node = child;
    }
}
void insert(heap *h1, process p1)
{
    h1->n++;
    h1->arr[h1->n - 1] = p1;
    heapify(h1, h1->n - 1);
}
void delete (heap *h1)
{
    h1->arr[0] = h1->arr[h1->n - 1];
    h1->n--;
    buildMinHeap(h1);
}
typedef struct
{
    int front, rear;
    process arr[1000];
} queue;
void init_queue(queue *q)
{
    q->front = q->rear = -1;
}
void push(queue *q, process a)
{
    if (q->rear == q->front - 1 || (q->front == 0 && q->rear == 999))
    {
        return;
    }
    else
    {
        if (q->front == -1 && q->rear == -1)
        {
            q->front = 0;
            q->rear = 0;
        }
        else if (q->rear == 999)
        {
            q->rear = 0;
        }
        else
        {
            q->rear++;
        }
        q->arr[q->rear] = a;
    }
}
void pop(queue *q, process *p)
{
    if (q->front != q->rear)
    {
        int temp = q->front;
        q->front++;
        if (q->front == 1000)
        {
            q->front = 0;
        }
        *p = q->arr[temp];
    }
    else if (q->front == q->rear && q->front != -1)
    {
        *p = q->arr[q->front];
        q->front = q->rear = -1;
    }
    else
    {
        return;
    }
}

int32_t compare(const void *a, const void *b)
{
    process *a1 = (process *)a;
    process *b1 = (process *)b;
    if (a1->arr_time == b1->arr_time)
    {
        return a1->priority > b1->priority;
    }
    else
    {
        return a1->arr_time > b1->arr_time;
    }
}

int final_times[1000];
typedef struct
{
    int counter[3];
    queue q1[3];
    heap h1;
} scheduler;

void sched_init(scheduler *s)
{
    for (int i = 0; i < 3; i++)
    {
        s->counter[i] = 0;
    }
    init_queue(&s->q1[0]);
    init_queue(&s->q1[1]);
    init_queue(&s->q1[2]);
    init_heap(&s->h1);
}
int scheduler_do(int time, scheduler *s1)
{
    if (s1->q1[0].rear == -1 &&
        s1->q1[1].rear == -1 &&
        s1->q1[2].rear == -1 &&
        s1->h1.n == 0)
    {
        return -1;
    }
    int has_arrived = 0;
    if (s1->q1[0].front != -1 &&
        s1->q1[0].arr[s1->q1[0].front].arr_time == time &&
        s1->q1[0].arr[s1->q1[0].front].cpu_time != 0)
    {
        has_arrived = 1;
    }
    for (int j = 0; j < 3; j++)
    {
        if (s1->q1[j].front != -1)
        {
            if ((j == 0 &&
                 s1->q1[0].arr[s1->q1[0].front].arr_time <= time &&
                 has_arrived == 0) ||
                j != 0)
            {
                s1->q1[j].arr[s1->q1[j].front].cpu_time--;
                s1->counter[j]++;
                if (s1->q1[j].arr[s1->q1[j].front].cpu_time <= 0)
                {
                    process preempt;
                    pop(&s1->q1[j], &preempt);
                    final_times[preempt.index] = time;
                    s1->counter[j] = 0;
                }
            }
        }
    }

    if (s1->h1.n != 0)
    {
        s1->h1.arr[0].cpu_time--;
        if (s1->h1.arr[0].cpu_time <= 0)
        {
            final_times[s1->h1.arr[0].index] = time;
            delete (&s1->h1);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (s1->counter[i] == tq[i])
        {
            process preempt;
            pop(&s1->q1[i], &preempt);
            s1->counter[i] = 0;
            if (i != 2)
            {
                push(&s1->q1[i + 1], preempt);
            }
            else
            {
                insert(&s1->h1, preempt);
            }
        }
    }
}

//debug
void print(scheduler s, int t)
{
    printf("\n At time %d:\n", t);
    printf("Scheduler 1 contents:\n");
    for (int i = s.q1[0].front; i <= s.q1[0].rear && i != -1; i++)
    {
        printf("%d %d %d\n", s.q1[0].arr[i].arr_time,
               s.q1[0].arr[i].cpu_time,
               s.q1[0].arr[i].priority);
    }
    printf("Scheduler 2 contents:\n");
    for (int i = s.q1[1].front; i <= s.q1[1].rear && i != -1; i++)
    {
        printf("%d %d %d\n", s.q1[1].arr[i].arr_time,
               s.q1[1].arr[i].cpu_time,
               s.q1[1].arr[i].priority);
    }
    printf("Scheduler 3 contents:\n");
    for (int i = s.q1[2].front; i <= s.q1[2].rear && i != -1; i++)
    {
        printf("%d %d %d\n", s.q1[2].arr[i].arr_time,
               s.q1[2].arr[i].cpu_time,
               s.q1[2].arr[i].priority);
    }
    printf("Scheduler 4 contents:\n");
    for (int i = 0; i < s.h1.n; i++)
    {
        printf("%d %d %d\n", s.h1.arr[i].arr_time,
               s.h1.arr[i].cpu_time,
               s.h1.arr[i].priority);
    }
}

int main(void)
{
    for (int i = 0; i < 1000; i++)
    {
        scheduler s;
        sched_init(&s);
        int n;
        scanf("%lld", &n);
        process p1[100];
        for (int i = 0; i < n; i++)
        {
            scanf("%lld %lld %lld", &s.q1[0].arr[i].arr_time,
                  &s.q1[0].arr[i].cpu_time,
                  &s.q1[0].arr[i].priority);
            s.q1[0].arr[i].index = i;
        }
        s.q1[0].front = 0;
        s.q1[0].rear = n - 1;
        s.counter[0] = 0;
        qsort(&s.q1[0].arr, n, sizeof(s.q1[0].arr[0]), compare);
        int time = 0;
        while (1)
        {
            if (time > 100)
            {
                printf("error\n");
                break;
            }
            int res = scheduler_do(time, &s);
            if (res == -1)
            {
                break;
            }
            //print(s, time);
            time++;
        }
        for (int i = 0; i < n; i++)
        {
            printf("%lld ", final_times[i]);
        }
        printf("\n");
    }
}