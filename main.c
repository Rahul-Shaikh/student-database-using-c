#include <stdio.h>
#include <string.h>

int sl = 0;

struct student
{
    int sl;
    char name[100];
    char roll[13];
};

typedef struct student student;

student def;

void search_by_name(FILE *fr, char *a);
void input(FILE *fa);
void output(FILE *fr);
void entry_no(FILE *fr);
void search_by_roll(FILE *fr, char *a);
void change(FILE *f);
void del(FILE *f);

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
        printf("4. Enter 'C' to change the data\n");
        printf("5. Enter 'S' to search\n");
        printf("6. Enter 'D' to delete a data\n");
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
            FILE *f = fopen("student.dat", "rb+");
            change(f);
            fclose(f);
        }
        else if (c == 'D')
        {
            FILE *f = fopen("student.dat", "rb");
            del(f);
            fclose(f);
        }
        else if (c == 'S')
        {
            FILE *fr = fopen("student.dat", "rb");
            while (1)
            {
                printf("\n\n1. Enter 'N' to search by name\n");
                printf("2. Enter 'R' to search by roll\n");
                printf("3. Enter 'B' to return to main menu\n");
                printf("\nEnter your choice : ");
                char c1;
                while (getchar() != '\n');
                scanf("%c", &c1);
                printf("\n");
                if (c1 == 'N')
                {
                    char name[100];
                    printf("Enter the name : ");
                    while (getchar() != '\n');
                    scanf("%[^\n]s", name);
                    search_by_name(fr, name);
                }
                else if (c1 == 'R')
                {
                    char roll[13];
                    printf("Enter the roll : ");
                    while (getchar() != '\n');
                    scanf("%s", roll);
                    search_by_roll(fr, roll);
                }
                else if (c1 == 'B')
                {
                    break;
                }
                else
                {
                    printf("Wrong input\n\n");
                }
            }
            fclose(fr);
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
    printf("\nEnter the number of records you will enter : ");
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

void search_by_roll(FILE *fr, char *roll)
{
    printf("\n");
    student s;
    fread(&s, sizeof(s), 1, fr);
    while(!feof(fr))
    {
        if(!strcmp(s.roll, roll))
        {
            printf("SL\t\tSTUDENT_NAME\t\tROLL_NO\n");
            printf("%-3d\t\t%-20s\t%-20s\n", s.sl, s.name, s.roll);
            rewind(fr);
            return;
        }
        fread(&s, sizeof(s), 1, fr);
    }
    rewind(fr);
    printf("No record of that roll exists\n");
    return;
}

void search_by_name(FILE *fr, char *name)
{
    printf("\n");
    student s;
    fread(&s, sizeof(s), 1, fr);
    while(!feof(fr))
    {
        if(!strcmp(s.name, name))
        {
            printf("SL\t\tSTUDENT_NAME\t\tROLL_NO\n");
            printf("%-3d\t\t%-20s\t%-20s\n", s.sl, s.name, s.roll);
            rewind(fr);
            return;
        }
        fread(&s, sizeof(s), 1, fr);
    }
    rewind(fr);
    printf("No record of that name exists\n");
    return;
}
void change(FILE *f)
{
    student s;
    int found = 0;
    printf("Enter the name of the student whose details you want to change : ");
    char name[100];
    while (getchar() != '\n');
    scanf("%[^\n]s", name);
    while(fread(&s, sizeof(s), 1, f))
    {
        if(!strcmp(s.name, name))
        {
            found = 1;
        }
        if (found)
        {
            fseek(f, -sizeof(s), SEEK_CUR);
            printf("Record found\n");
            printf("Enter new name : ");
            char name1[100];
            while ((getchar() != '\n'));
            scanf("%[^\n]s", name1);
            if (name1[0] == '\0')
            {
                printf("\nNull character entered\n\n");
                return;
            }
            printf("Enter new roll no. : ");
            char roll1[13];
            if (roll1[0] == '\0')
            {
                printf("\nNull character entered\n\n");
                return;
            }
            while ((getchar() != '\n'));
            scanf("%[^\n]s", roll1);
            strcpy(s.name, name1);
            strcpy(s.roll, roll1);
            fwrite(&s, sizeof(s), 1, f);
            printf("\nRecord updated successfully\n\n");
            return;
        }
    }
    printf("\nRecord not found\n\n");
    return;
}

void del(FILE *f)
{
    student s;
    printf("Enter the name of the record you want to delete : ");
    char name[100];
    while(getchar() != '\n');
    scanf("%[^\n]s", name);
    while(fread(&s, sizeof(s), 1, f))
    {
        if (!strcmp(s.name, name))
        {
            fseek(f, 0, SEEK_SET);
            FILE *ftemp = fopen("temp.dat", "wb");
            student stemp;
            int i = 0;
            while (fread(&stemp, sizeof(s), 1, f))
            {
                if (!strcmp(s.name, stemp.name)) continue;
                else
                {
                    stemp.sl = ++i;
                    fwrite(&stemp ,sizeof(stemp), 1, ftemp);
                }
            }
            fclose(f);
            fclose(ftemp);
            remove("student.dat");
            rename("temp.dat", "student.dat");
            printf("Record deleted successfully\n");
            return;
        }
    }
    printf("Record not found\n");
}