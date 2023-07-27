

void *mergeSort(void* rango) {
    Rango* r = (Rango*) rango;
    int m = r->inicio+(r->fin-r->inicio)/2;

    if (r->inicio < r->fin) {
        Rango r1, r2;
        r1.inicio = r->inicio;
        r1.fin = m;
        r1.array = r->array;

        r2.inicio = m + 1;
        r2.fin = r->fin;
        r2.array = r->array;

        pthread_t h1, h2;
        pthread_create(&h1, NULL, mergeSort, &r1);
        pthread_create(&h2, NULL, mergeSort, &r2);

        pthread_join(h1, NULL);
        pthread_join(h2, NULL);

        merge(r->array, r->inicio, m, r->fin);
    }
    return NULL;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// path so_lab/lab10/merge.c
// how to exec: gcc merge.c -o merge -lpthread
// how i can view process in ubuntu? -> ps -e | grep merge
// how i can view process and view details, like memory, cpu, etc?  and especific name as "code" -> ps -e -o pid,ppid,cmd,%mem,%cpu --sort=-%mem | grep merge
// how to kill process named as code-insiders -> killall -9 code-insiders