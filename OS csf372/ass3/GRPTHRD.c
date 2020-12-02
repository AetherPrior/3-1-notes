#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
char combined[100][100], n;
typedef struct
{
    int outputlength;
    char check[100];
    char output[100][100];
} argstruct;
argstruct *query;
void *thread_func(void *arg)
{
    argstruct *q = (argstruct *)arg;
    int count = 0;

    char needle[100];
    strcpy(needle, q->check);
    for (int i = 0; i < strlen(needle); i++)
    {
        needle[i] = tolower(needle[i]);
    }

    for (int i = 0; i < n; i++)
    {
        char haystack[100];
        strcpy(haystack, combined[i]);
        for (int i = 0; i < strlen(haystack); i++)
        {
            haystack[i] = tolower(haystack[i]);
        }
        if (strstr(haystack, needle) != NULL)
        {
            strcpy(q->output[count], combined[i]);
            count++;
        }
    }
    q->outputlength = count;
    pthread_exit(0);
}

int main(void)
{
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        //fgets(combined[i], 100, stdin);
        //combined[i][strlen(combined[i]) - 1] = '\0';
        gets(combined[i]);
        //getchar();
    }
    int k;
    scanf("%d", &k);
    getchar();
    query = malloc(k * sizeof(query));
    for (int i = 0; i < k; i++)
    {
        gets(query[i].check);
        //fgets(query[i].check, 100, stdin);
        //query[i].check[strlen(query[i].check) - 1] = '\0';
        // getchar();
    }
    pthread_t threads[k];
    for (int i = 0; i < k; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, (void *)&query[i]);
    }
    for (int i = 0; i < k; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < query[i].outputlength; j++)
        {
            printf("%s\n", query[i].output[j]);
        }
    }
}