#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>
float varvals[1000];
float valstack[1000];
int tops = -1;
char opstack[1000];
int topo = -1;
typedef struct
{
    float r1, r2;
    char op;
} argstruct;
int precedence(char b)
{
    if (b == '+' || b == '-')
    {
        return 1;
    }
    else if (b == '*' || b == '/')
    {
        return 2;
    }
    else if (b == '^')
    {
        return 3;
    }
    return 0;
}
float retval;
void *apply(void *ag)
{
    float r1 = ((argstruct *)ag)->r1;
    float r2 = ((argstruct *)ag)->r2;
    char op = ((argstruct *)ag)->op;
    switch (op)
    {
    case '+':
        retval = (r1 + r2);
        break;
    case '-':
        retval = (r1 - r2);
        break;
    case '*':
        retval = (r1 * r2);
        break;
    case '/':
        retval = (r1 / r2);
        break;
    case '^':
        retval = powl(r1, r2);
        break;
    default:
        printf("op: %c\n", op);
        exit(-1);
    }
    return (void *)&(retval);
}
float eval(char *str, int beg, int end)
{
    int i = beg;
    while (i <= end)
    {
        float result = 0;
        if (str[i] == ' ')
        {
            continue;
        }
        if (isdigit(str[i]))
        {
            int j = i;
            while (isdigit(str[j]) && j <= end)
            {
                result *= 10;
                result += (str[j] - 48);
                j++;
            }

            ++tops;
            valstack[tops] = result;

            i = j;
        }
        else if (isalpha(str[i]))
        {
            result = varvals[str[i] - 97];

            ++tops;
            valstack[tops] = result;

            i++;
        }
        else if (str[i] == '(')
        {
            ++topo;
            opstack[topo] = str[i];
            i++;
        }
        else if (str[i] == ')')
        {
            while (topo != -1 && opstack[topo] != '(')
            {
                float r2 = valstack[tops];
                tops--;

                float r1 = valstack[tops];
                tops--;

                char op = opstack[topo];
                topo--;

                pthread_t tid;
                argstruct s;
                s.r1 = r1;
                s.r2 = r2;
                s.op = op;
                pthread_create(&tid, NULL, apply, (void *)&(s));
                float *r;
                pthread_join(tid, (void *)&r);
                result = *r;
                tops++;
                valstack[tops] = result;
            }
            i++;
            if (topo != -1)
            {
                //opstack[topo];
                topo--;
            }
        }
        else
        {
            while (topo != -1 && precedence(str[i]) <= precedence(opstack[topo]))
            {
                char op = opstack[topo];
                topo--;
                float r2 = valstack[tops];
                tops--;
                float r1 = valstack[tops];
                tops--;

                pthread_t tid;
                argstruct s;
                s.r1 = r1;
                s.r2 = r2;
                s.op = op;
                pthread_create(&tid, NULL, apply, (void *)&(s));
                float *r;
                pthread_join(tid, (void *)&r);
                result = *r;

                tops++;
                valstack[tops] = result;
            }

            topo++;
            opstack[topo] = str[i];

            i++;
        }
    }
    while (topo != -1)
    {
        char op = opstack[topo];
        topo--;
        float r2 = valstack[tops];
        tops--;
        float r1 = valstack[tops];
        tops--;

        pthread_t tid;
        argstruct s;
        s.r1 = r1;
        s.r2 = r2;
        s.op = op;
        pthread_create(&tid, NULL, apply, (void *)&(s));
        float *r;
        pthread_join(tid, (void *)&r);
        float result = *r;

        tops++;
        valstack[tops] = result;
    }
    if (tops > 0)
    {
        exit(2);
    }
    return valstack[tops];
}

int main(void)
{
    char str[10000];
    scanf("%s", str);
    long long n;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++)
        scanf("%f", &varvals[i]);

    printf("%lld", (long)eval(str, 0, strlen(str) - 1));
    return 0;
}