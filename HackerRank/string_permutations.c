#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap_last_two_strings(int n, char **s);
int swap_previous_with_next_in_order(int n, char **s);
int get_index_of_next_in_order_value(int n, int from_value_index, char **s);
int set_remaining_values_in_order(int n, char **s, int from_value_index);

int next_permutation(int n, char **s)
{
    /**
     * Complete this method
     * Return 0 when there is no next permutation and 1 otherwise
     * Modify array s to its next permutation
     */
    if (swap_last_two_strings(n, s) == 0)
    {
        swap_previous_with_next_in_order(n, s);
    }
    return 1;
}

int set_remaining_values_in_order(int n, char **s, int from_value_index)
{
    for (int i = 0; i < n; i++)
    {

    }
}

int swap_previous_with_next_in_order(int n, char **s)
{
    char *prev_value;
    int index_of_next_value;
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i][0] > s[i + 1][0])
        {
            prev_value = s[i - 1];

            // find the next in order
            // if can't find it's program is over
            index_of_next_value = get_index_of_next_in_order_value(n, i - 1, s);
            if (index_of_next_value == -1)
            {
                return 0;
            }
            s[i - 1] = s[index_of_next_value];
            s[index_of_next_value] = prev_value;
        }
    }
    return 1;
}

int get_index_of_next_in_order_value(int n, int from_value_index, char **s)
{
    int index_of_next_value = -1;
    if (s[from_value_index + 1] > s[from_value_index])
    {
        index_of_next_value = from_value_index + 1;
    }

    if (index_of_next_value == -1)
    {
        return 0;
    }

    for (int i = from_value_index + 1; i < n; i++)
    {
        if (s[i][0] < s[index_of_next_value][0] && s[i][0] > s[from_value_index][0])
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
            // BUG: This will need to change to support lexicographical order
            if (s[i][0] < s[i + 1][0])
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

int main()
{
    char **s;
    int n = 5;
    s = calloc(n, sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        scanf("%s", s[i]);
    }

    printf("Output:\n");
    next_permutation(n, s);
    for (int i = 0; i < n; i++)
    {
        printf("%s ", s[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);
    return 0;
}
