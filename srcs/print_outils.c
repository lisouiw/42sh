#include "../twenty.h"

void    print_here(t_froz *fz)
{
    printf("======PRINT_HEREDOC===========\n");
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while(fz->here->next != NULL)
    {
        printf("[%s][%s]\n", fz->here->doc,fz->here->delim);
        fz->here = fz->here->next;
    }
    printf("[%s][%s]\n", fz->here->doc,fz->here->delim);
}

void    print_ex(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("-------------DEBUT---------------------\n");
    while (ex->next != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->next;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("----------------------------------\n");
    printf("----------------------------------\n");
    while (ex->prev != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->prev;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("------------FIN----------------------\n");
}

void    print_ex_up(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("-------------DEBUT---------------------\n");
    while (ex->next != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->next;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("----------------------------------\n");
}
