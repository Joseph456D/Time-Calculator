#include <stdio.h>
#include <stdlib.h>
void main()
{
    int temp1, temp2, choice, choice2 = 1, time2_hh, time2_mm, time2_ss, time1_hh = 0, time1_mm = 0, time1_ss = 0;
    printf("Enter the time in HH MM SS Format : ");
    while (1)
    {
        scanf("%d%d%d", &time1_hh, &time1_mm, &time1_ss);
        if (time1_mm >= 60 || time1_ss >= 60)
        {
            printf("Wrong Input\nType Again : ");
        }
        else
            break;
    }
    do
    {
        printf("Press \e[1m\"1\"\e[m for adding and \e[1m\"2\"\e[m for subtracting : ");
        while (1)
        {
            scanf("%d", &choice2);
            if (choice2 != 1 && choice2 != 2)
            {
                printf("Wrong choice Press Correct Option : ");
            }
            else
                break;
        }
        printf("Enter next time in HH MM SS Format : ");
        while (1)
        {
            scanf("%d%d%d", &time2_hh, &time2_mm, &time2_ss);
            if (time2_mm >= 60 || time2_ss >= 60)
            {
                printf("Wrong Input\nType Again : ");
            }
            else
                break;
        }

        if (choice2 == 1)
        {
            time1_hh += time2_hh;
            time1_mm += time2_mm;
            time1_ss += time2_ss;
            if (time1_ss >= 60)
            {
                temp1 = time1_ss % 60;
                temp2 = time1_ss / 60;
                time1_ss = temp1;
                time1_mm += temp2;
            }
            if (time1_mm >= 60)
            {
                temp1 = time1_mm % 60;
                temp2 = time1_mm / 60;
                time1_mm = temp1;
                time1_hh += temp2;
            }
        }
        else if (choice2 == 2)
        {

            time1_hh -= time2_hh;
            time1_mm -= time2_mm;
            time1_ss -= time2_ss;

            if (time1_ss < 0)
            {
                time1_ss += 60;
                time1_mm--;
            }

            if (time1_mm < 0)
            {
                time1_mm += 60;
                time1_hh--;
            }
        }

        printf("The resultant time is %02d:%02d:%02d\n", time1_hh, time1_mm, time1_ss);

        printf("Press \e[1m\"1\"\e[m to continue and \e[1m\"0\"\e[m to stop : ");
        scanf("%d", &choice);
    } while (choice);
    printf("Stopping...\n");
}

/*
        \e[1m -- Bold
        \e[m --Reset Bold
if bold is started it has to be stopped
*/
