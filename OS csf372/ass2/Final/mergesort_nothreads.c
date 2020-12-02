#include <stdio.h>
int arr[100];
void mergesort(int l, int r, int n)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergesort(mid + 1, r, n);
        mergesort(l, mid, n);
        int i = l, j = mid + 1, k = 0;
        int arr_n[100];
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
        k = 0;
        for (int i = l; i <= r && k <= r - l; i++, k++)
        {
            arr[i] = arr_n[k];
        }
    }
}
int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    mergesort(0, n - 1, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}