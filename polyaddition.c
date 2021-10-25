#include <stdio.h>
#include <stdlib.h>

struct poly
{
    int coef, exp;
};

typedef struct poly poly;

void display(poly *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {

        if (p[i].exp > 1)
        {
            if (i == 0)
                printf("%dx^%d ", p[i].coef, p[i].exp);
            else if (p[i].coef < 0)
                printf("- %dx^%d ", -(p[i].coef), p[i].exp);
            else
                printf("+ %dx^%d ", p[i].coef, p[i].exp);
        }
        else if (p[i].exp == 1)
        {
            if (i == 0)
                printf("%dx ", p[i].coef);
            else if (p[i].coef < 0)
                printf("- %dx ", -(p[i].coef));
            else
                printf("+ %dx ", p[i].coef);
        }
        else
        {
            if (i == 0)
                printf("%d ", p[i].coef);
            else if (p[i].coef < 0)
                printf("- %d ", -(p[i].coef));
            else
                printf("+ %d ", p[i].coef);
        }
    }
}

poly *polyadd(poly *p, int *n, int elem, int power)
{
    p = (poly *)realloc(p, (*n + 1) * sizeof(poly));
    p[*n].coef = elem;
    p[*n].exp = power;
    (*n)++;
    return p;
}

int main()
{
    poly *p1 = NULL, *p2 = NULL, *p = NULL;
    int i, j, max_power, n1 = 0, n2 = 0, n = 0, temp;
    printf("\nEnter the highest degree of the polynomial 1: ");
    scanf("%d", &max_power);
    for (i = max_power; i >= 0; i--)
    {
        printf("Enter the coefficient of x^%d: ", i);
        scanf("%d", &temp);
        if (temp != 0)
            p1 = polyadd(p1, &n1, temp, i);
    }

    printf("\nEnter the highest degree of the polynomial 2: ");
    scanf("%d", &max_power);
    for (i = max_power; i >= 0; i--)
    {
        printf("Enter the coefficient of x^%d: ", i);
        scanf("%d", &temp);
        if (temp != 0)
            p2 = polyadd(p2, &n2, temp, i);
    }

    printf("\nPolynomial 1: ");
    display(p1, n1);

    printf("\nPolynomial 2: ");
    display(p2, n2);
    i = 0;
    j = 0;

    while (i < n1 && j < n2)
    {
        if (p1[i].exp == p2[j].exp)
        {
            temp = p1[i].coef + p2[j].coef;
            if (temp != 0)
                p = polyadd(p, &n, temp, p1[i].exp);
            i++;
            j++;
        }
        else if (p1[i].exp > p2[j].exp)
        {
            p = polyadd(p, &n, p1[i].coef, p1[i].exp);
            i++;
        }
        else
        {
            p = polyadd(p, &n, p2[j].coef, p2[j].exp);
            j++;
        }
    }

    while (i < n1)
    {
        p = polyadd(p, &n, p1[i].coef, p1[i].exp);
        i++;
    }

    while (j < n2)
    {
        p = polyadd(p, &n, p2[j].coef, p2[j].exp);
        j++;
    }

    printf("\nSum: \n");
    display(p, n);

    free(p);
    free(p1);
    free(p2);

    return 0;
}