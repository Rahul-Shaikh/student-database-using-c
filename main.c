#include <stdio.h>

int sl = 0;

struct student
{
    int sl;
    char name[100];
    char roll[13];
};

typedef struct student student;

student def;

void input(FILE *fa);
void output(FILE *fr);
void entry_no(FILE *fr);


int main(void)
{
    while(1)
    {
        FILE *fr = fopen("student.dat", "ab+");
        entry_no(fr);
        rewind(fr);
        fclose(fr);
        printf("\n\nTOTAL NUMBER OF ENTRIES IS %d\n\n\n", sl);
        printf("1. Enter 'I' to enter input\n");
        printf("2. Enter 'O' to see output\n");
        printf("3. Enter 'Q' to quit\n");
        printf("4. Enter 'C' to change the data");
        printf("\n\nEnter your choice : ");
        char c;
        scanf("%c", &c);
        printf("\n\n");
        if (c == 'I') {
            FILE *fa = fopen("student.dat", "ab+");
            input(fa);
            fclose(fa);
        }
        else if (c=='O')
        {
            FILE *fa = fopen("student.dat", "rb");
            output(fa);
            fclose(fa);
        }
        else if (c=='Q')
        {
            printf("\nYou have chosen to quit\n\n");
            return 0;
        }
        else if (c == 'C')
        {
            printf("\nYou have wanted to change a record\n");
        }
        else
        {
            printf("Wrong input\n\n");
        }
        while (getchar() != '\n');
    }
}

void entry_no(FILE *fr)
{
    sl = 0;
    rewind(fr);
    while(!feof(fr))
    {
        fread(&def, sizeof(def), 1, fr);
        sl++;
    }
    sl--;
}

void input(FILE *fa)
{
    int count;
    printf("\nEnter the number of inputs you will be giving : ");
    scanf("%d", &count);
    student s;
    for(int  i = 0;i < count;i++)
    {
        s.sl = ++sl;
        printf("Enter name : ");
        while(getchar() != '\n');
        scanf("%[^\n]s", s.name);
        while(getchar() != '\n');
        printf("Enter roll no. : ");
        scanf("%s", s.roll);
        fwrite(&s, sizeof(s), 1, fa);
        printf("\n\n");
    }
}

void output(FILE *fr)
{
    rewind(fr);
    student s;
    printf("SL\t\tSTUDENT_NAME\t\tROLL_NO\n");
    fread(&s, sizeof(s), 1, fr);
    while (!feof(fr))
    {
        printf("%-3d\t\t%-20s\t%-20s\n", s.sl, s.name, s.roll);
        fread(&s, sizeof(s), 1, fr);
    }
    printf("\n\n\n");
}