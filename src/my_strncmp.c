/*
** EPITECH PROJECT, 2020
** my_strncmp
** File description:
** my_strncmp
*/

int my_strncmp(char *s1, char *s2, int n, int space)
{
    int x = 0;
    int y = 0;

    for (int j = 0; j < n; j++) {
        if (s1[x+space] == s2[y]) {
            x++;
            y++;
        }
    }
    if (s1[x+space] == '\0' || s1[x+space] == ' ')
        return (x == n ? 0 : 1);
    if (s1[x+space-2] == '.' || s1[x+space-1] == '/')
        return (0);
    return (1);
}