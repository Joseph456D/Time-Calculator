#include <stdio.h>
#include <stdlib.h>

void input(int *time_hh, int *time_mm, int *time_ss)
{
    printf("Enter the time in HH MM SS format: ");
    while (1)
    {
        scanf("%d%d%d", time_hh, time_mm, time_ss);
        if (*time_mm >= 60 || *time_ss >= 60)
        {
            printf("Wrong Input. Type Again: ");
        }
        else
        {
            break;
        }
    }
}

void calculation(int time1[], int time2[], int choice)
{
    int temp1, temp2;

    if (choice == 1) // Addition
    {
        time1[0] += time2[0];
        time1[1] += time2[1];
        time1[2] += time2[2];

        if (time1[2] >= 60)
        {
            temp1 = time1[2] % 60;
            temp2 = time1[2] / 60;
            time1[2] = temp1;
            time1[1] += temp2;
        }
        if (time1[1] >= 60)
        {
            temp1 = time1[1] % 60;
            temp2 = time1[1] / 60;
            time1[1] = temp1;
            time1[0] += temp2;
        }
    }
    else if (choice == 2) // Subtraction
    {
        time1[0] -= time2[0];
        time1[1] -= time2[1];
        time1[2] -= time2[2];

        if (time1[2] < 0)
        {
            time1[2] += 60;
            time1[1]--;
        }

        if (time1[1] < 0)
        {
            time1[1] += 60;
            time1[0]--;
        }
    }
}

int main()
{
    int choice;
    int time1[3], time2[3];

    input(&time1[0], &time1[1], &time1[2]);

    do
    {

        printf("Press \e[1m\"1\"\e[m for adding and \e[1m\"2\"\e[m for subtracting : ");
        while (1)
        {
            scanf("%d", &choice);
            if (choice != 1 && choice != 2)
            {
                printf("Wrong choice. Press Correct Option: ");
            }
            else
            {
                break;
            }
        }

        input(&time2[0], &time2[1], &time2[2]);

        calculation(time1, time2, choice);

        printf("The resultant time is %02d:%02d:%02d\n", time1[0], time1[1], time1[2]);

        printf("Press \e[1m\"1\"\e[m to continue and \e[1m\"0\"\e[m to stop : ");
        scanf("%d", &choice);
    } while (choice);

    return 0;
}

/*
        \e[1m -- Bold
        \e[m --Reset Bold
if bold is started it has to be stopped
*/