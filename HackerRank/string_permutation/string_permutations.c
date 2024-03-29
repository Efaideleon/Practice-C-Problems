#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap_last_two_strings(int n, char **s);
int swap_previous_with_next_in_order(int n, char **s);
int get_index_of_next_in_order_value(int n, int from_value_index, char **s);
void string_sort(char **arr, const int len, int (*cmp_func)(const char *a, const char *b), int from_index);
int lexicographic_sort(const char *a, const char *b);
int lexicographic_comp(const char *a, const char *b);

int next_permutation(int n, char **s)
{
    /**
     * Complete this method
     * Return 0 when there is no next permutation and 1 otherwise
     * Modify array s to its next permutation
     */
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (lexicographic_comp(s[i], s[i + 1]) == 0 || lexicographic_comp(s[i], s[i + 1]) == 2)
        {
            count++;
        }
    }
    if (count == n - 1)
    {
        return 0;
    }

    int index_prev_value;
    if (swap_last_two_strings(n, s) == 0)
    {
        index_prev_value = swap_previous_with_next_in_order(n, s);
        string_sort(s, n, lexicographic_sort, index_prev_value);
    }
    return 1;
}

int swap_previous_with_next_in_order(int n, char **s)
{
    char *prev_value;
    int index_of_next_value;
    int index_of_prev_value = 0;
    for (int i = n - 1; i >= 1; i--)
    {
        if (lexicographic_comp(s[i], s[i - 1]) == 0)
        {
            index_of_prev_value = i - 1;
            // find the next in order
            // if can't find it's program is over
            if (index_of_prev_value < 1)
            {
                index_of_prev_value = 0;
            }
            prev_value = s[index_of_prev_value];
            index_of_next_value = get_index_of_next_in_order_value(n, index_of_prev_value, s);
            if (index_of_next_value == -1)
            {
                return 0;
            }

            s[index_of_prev_value] = s[index_of_next_value];
            s[index_of_next_value] = prev_value;

            return index_of_prev_value;
        }
    }
    return index_of_prev_value;
}

int get_index_of_next_in_order_value(int n, int from_value_index, char **s)
{
    int index_of_next_value = -1;
    if (lexicographic_comp(s[from_value_index + 1], s[from_value_index]) == 0)
    {
        index_of_next_value = from_value_index + 1;
    }

    if (index_of_next_value == -1)
    {
        return 0;
    }

    for (int i = from_value_index + 1; i < n; i++)
    {
        if (lexicographic_comp(s[i], s[index_of_next_value]) == 1 && lexicographic_comp(s[i], s[from_value_index]) == 0)
        {
            index_of_next_value = i;
        }
    }

    return index_of_next_value;
}

int swap_last_two_strings(int n, char **s)
{
    /*
     * Return 0 if can't swap
     * Return 1 if swapped
     */
    char *temp;
    for (int i = 0; i < n - 1; i++)
    {
        if (i == n - 2)
        {
            if (lexicographic_comp(s[i], s[i + 1]) == 1)
            {
                temp = s[i];
                s[i] = s[i + 1];
                s[i + 1] = temp;
                return 1;
            }
        }
    }
    return 0;
}

void string_sort(char **arr, const int len, int (*cmp_func)(const char *a, const char *b), int from_index)
{
    // arr: is the array of strings to sort
    // len: how many strings the arr has
    char *temp_arr = NULL;
    for (int i = from_index + 1; i < len; i++)
    {
        if (i + 1 < len - 1)
        {
            if (cmp_func(arr[i], arr[i + 1]) == 0)
            {
                temp_arr = arr[i];
                arr[i] = (char *)realloc(arr[i + 1], sizeof(char) * strlen(arr[i + 1]));
                arr[i] = arr[i + 1];
                arr[i + 1] = (char *)realloc(temp_arr, sizeof(char) * strlen(temp_arr));
                arr[i + 1] = temp_arr;
            }
        }

        for (int j = i; j > from_index + 1; j--)
        {
            if (cmp_func(arr[j], arr[j - 1]) == 1)
            {
                temp_arr = arr[j];
                arr[j] = (char *)realloc(arr[j - 1], sizeof(char) * strlen(arr[j - 1]));
                arr[j] = arr[j - 1];
                arr[j - 1] = (char *)realloc(temp_arr, sizeof(char) * strlen(temp_arr));
                arr[j - 1] = temp_arr;
            }
        }
    }
}

int lexicographic_sort(const char *a, const char *b)
{
    // a: is a string passed by reference that will be printed later
    // return 0: false, 1: true
    int max_len = 0;
    if (strlen(a) > strlen(b))
    {
        max_len = strlen(a);
    }
    else
    {
        max_len = strlen(b);
    }

    for (int i = 0; i < max_len; i++)
    {
        if (a[i] < b[i])
        {
            return 1;
        }
        else if (a[i] > b[i])
        {
            return 0;
        }
    }
    return 0;
}

int lexicographic_comp(const char *a, const char *b)
{
    // return: a < b = 1
    // return: a > b = 0
    // return: a == b = 2
    int min_len = 0;
    int len_a = strlen(a);
    int len_b = strlen(b);
    min_len = len_a;
    if (min_len > len_b)
    {
        min_len = len_b;
    }

    for (int i = 0; i < min_len; i++)
    {
        if (b[i] > a[i])
            return 1;
        if (b[i] < a[i])
            return 0;
    }

    if (len_a > len_b)
    {
        return 0;
    }
    if (len_a < len_b)
    {
        return 1;
    }

    return 2;
}

int main()
{
    char **s;
    int n;
    scanf("%d", &n);
    s = calloc(n, sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        scanf("%s", s[i]);
    }
    do
    {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));

    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);
    return 0;
}
