#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Stack
{
    int top;
    int capacity;
    int *array;
};
struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}
int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int peek(struct Stack *stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
int size(struct Stack *stack)
{
    int capa = 0;
    for (int i = 0; i <= stack->top; i++)
        capa++;
    return capa;
}
// displaying logic
void display(struct Stack *g[], int tubes)
{
    for (int b = 0; b < tubes; b++)
    {
        printf("Elements in the stack_%d:\n", b + 1);
        int top = g[b]->top, l = 4 - size(g[b]);
        for (int i = 0; i < 4; i++)
        {
            if (!i)
            {
                printf("* \t  *\n");
            }
            while (l)
            {
                printf("  *     *\n");
                l--;
            }
            if (top >= 0 && top <= 4)
                printf("  *  %d  *\n", g[b]->array[top--]);
        }
        printf("  * * * *\n");
    }
}
void checkpossible(struct Stack *g[], int tube, int colors)
{
    int empty_glass = 0;
    for (int i = 0; i < tube; i++)
    {
        if (isEmpty(g[i]))
            empty_glass++;
    }
    if (colors == 3 && empty_glass == 1)
    {
        display(g, tube);
        printf("You have completed the Game !!\n");
        exit(0);
    }
    if (colors > 3 && empty_glass == 2)
    {
        display(g, tube);
        printf("You have completed the Game !!\n");
        exit(0);
    }
}
void dispose(struct Stack *glass[], int tube)
{
    for (int i = 0; i < tube; i++)
    {
        free(glass[i]->array);
        free(glass[i]);
    }
    free(glass);
}
void makeempty(struct Stack *glass[], int tube)
{
    for (int i = 0; i < tube; i++)
    {
        while (!isEmpty(glass[i]))
            pop(glass[i]);
    }
}
int main()
{
    int choice = 0;
    char reset;
    int colors, tube;
    do
    {
        printf("Enter the no.of.elements(3 to 5) = ");
        scanf("%d", &colors);
    } while (colors < 3 || colors > 5);
    if (colors == 3)
        tube = 4;
    else
        tube = colors + 2;
    struct Stack *glass[tube - 1];
    for (int i = 0; i < tube; i++)
        glass[i] = createStack(4);
    if (colors == 3)
    {
        reset = 'a';
    a:
        push(glass[0], 2);
        push(glass[0], 1);
        push(glass[0], 3);
        push(glass[0], 1); // 2 1 3 1
        push(glass[1], 3);
        push(glass[1], 1);
        push(glass[1], 2);
        push(glass[1], 2); // 3 1 2 2
        push(glass[2], 2);
        push(glass[2], 3);
        push(glass[2], 1);
        push(glass[2], 3);
        display(glass, tube); // 2 3 1 3
    }
    else if (colors == 4)
    {
        reset = 'b';
    b:
        push(glass[0], 4);
        push(glass[0], 2);
        push(glass[0], 4);
        push(glass[0], 1); // 4 2 4 1
        push(glass[1], 3);
        push(glass[1], 2);
        push(glass[1], 2);
        push(glass[1], 4); // 3 2 2 4
        push(glass[2], 1);
        push(glass[2], 3);
        push(glass[2], 2);
        push(glass[2], 1); // 1 3 2 1
        push(glass[3], 3);
        push(glass[3], 1);
        push(glass[3], 4);
        push(glass[3], 3);
        display(glass, tube); // 3 1 4 3
    }
    else if (colors == 5)
    {
        reset = 'c';
    c:
        push(glass[0], 5);
        push(glass[0], 2);
        push(glass[0], 1);
        push(glass[0], 4); // 5 2 1 4
        push(glass[1], 2);
        push(glass[1], 5);
        push(glass[1], 3);
        push(glass[1], 1); // 2 5 3 1
        push(glass[2], 2);
        push(glass[2], 4);
        push(glass[2], 5);
        push(glass[2], 3); // 2 4 5 3
        push(glass[3], 1);
        push(glass[3], 5);
        push(glass[3], 4);
        push(glass[3], 3); // 1 5 4 3
        push(glass[4], 1);
        push(glass[4], 2);
        push(glass[4], 4);
        push(glass[4], 3);
        display(glass, tube); // 1 2 4 3
    }
    do
    {
        printf("MENU\n");
        int i;
        for (i = 0; i < tube; i++)
        {
            printf("%d. Pop_%d\n", i + 1, i + 1);
        }
        printf("%d. Exit\n", ++i);
        printf("%d. Restart\n", ++i);
        printf("Enter choice:");
        scanf("%d", &choice);
        if (choice == tube + 2)
        {
            if (reset == 'a')
            {
                makeempty(glass, tube);
                goto a;
            }
            else if (reset == 'b')
            {
                makeempty(glass, tube);
                goto b;
            }
            else
            {
                makeempty(glass, tube);
                goto c;
            }
        }
        if (choice == tube + 1) // exiting
        {
            printf("Game Over...");
            exit(0);
        }
        else if (choice >= 1 && choice <= tube) // logic
        {
            if (isEmpty(glass[choice - 1]))
            {
                printf("Glass is empty, Cannot pop...\n");
                continue;
            }
            int pushh, flag = 0;
            do
            {
                int j;
                for (j = 0; j < tube; j++)
                {
                    if (j == choice - 1)
                        continue;
                    printf("%d. Pushto_%d\n", j + 1, j + 1);
                }
                printf("%d. Undo Popped element\n", j + 1);
                printf("Popped element = %d\n", peek(glass[choice - 1]));
                printf("Enter choice:");
                scanf("%d", &pushh);
                if (pushh == j + 1) // undo option
                    break;
                if (pushh != choice && (pushh >= 1 && pushh <= tube))
                {
                    flag = 0;
                    if (isFull(glass[pushh - 1]))
                    {
                        display(glass, tube);
                        printf("Glass_%d is full. Cannot push...\n", pushh); // checking full
                    }
                    else if (peek(glass[choice - 1]) != peek(glass[pushh - 1]) && (!isEmpty(glass[pushh - 1])))
                    {
                        display(glass, tube);
                        printf("Cannot push...\n"); // not same
                    }
                    else
                    {
                        int temp = pop(glass[choice - 1]);
                        push(glass[pushh - 1], temp);
                        checkpossible(glass, tube, colors);
                        display(glass, tube);
                        printf("Element %d changed from Glass_%d to Glass_%d\n", temp, choice, pushh); // pushed successfully
                    }
                }
                else
                {
                    printf("Enter a valid choice..\n");
                    flag = 1;
                }
            } while (flag);
        }
        else // invalid
        {
            printf("Enter a valid choice...\n");
        }
    } while (choice != tube + 1);
    dispose(glass, tube);
    return 0;
}