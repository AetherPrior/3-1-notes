#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct argstruct
{
    int l, r;
};
int arr[100];
int arr_n[100];
void *merge(void *a)
{
    struct argstruct *a1 = ((struct argstruct *)a);
    int l = a1->l, r = a1->r;
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        pthread_t t1, t2;

        struct argstruct s1, s2;

        s1.l = l;
        s1.r = mid;
        int rc = pthread_create(&t2, NULL, merge, (void *)&s1);
        if (rc)
        {
            printf("left rip\n");
            exit(1);
        }

        s2.l = mid + 1;
        s2.r = r;
        rc = pthread_create(&t1, NULL, merge, (void *)&s2);
        if (rc)
        {
            printf("right rip\n");
            exit(1);
        }

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        int k = l;
        int i = l, j = mid + 1;
        while (i <= mid && j <= r)
        {
            if (arr[i] < arr[j])
            {
                arr_n[k] = arr[i];
                i++;
            }
            else
            {
                arr_n[k] = arr[j];
                j++;
            }
            k++;
        }
        while (i <= mid)
        {
            arr_n[k] = arr[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            arr_n[k] = arr[j];
            j++;
            k++;
        }
        for (int i = l; i <= r; i++)
        {
            arr[i] = arr_n[i];
        }
    }
    return NULL;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    struct argstruct a1;
    a1.l = 0;
    a1.r = n - 1;
    merge((void *)&a1);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}