#include<stdio.h>
#include<stdlib.h>
struct library
{
    int id;
    char title[50];
    char author[50];
};

struct library books[100];
int n=0;

void savefile()
{
    FILE *file= fopen("hameem.txt","w");
    if(file == NULL)
    {
        printf ("Error opening file\n");
        return;
    }
    for(int i=0; i<n; i++)
    {
        fprintf(file,"%d\t\t%s\t\t%s\n", books[i].id,books[i].title,books[i].author);
    }
    fclose(file);
    printf("Data saved to hameem.txt successfully.\n");
}
void loadfile()
{
    FILE *file= fopen("hameem.txt","r");
    if(file == NULL)
    {
        printf ("No existing data file found\n");
        return;
    }
    n=0;
    while(fscanf(file, "%d\t%[^\t]\t%[^\n]\n", &books[n].id, books[n].title, books[n].author) == 3)
    {
        n++;
    }
    fclose(file);
    printf("Data loaded from hameem.txt successfully.\n");
}

void add_books()
{
    printf("Enter an Id for book:");
    scanf("%d",&books[n].id);
    printf("Enter the book title:");
    getchar();
    scanf("%[^\n]%*c", books[n].title);
    printf("Enter the author name:");
    getchar();
    scanf("%[^\n]%*c", books[n].author);
    n++;
    printf("Book added successfully\n");
    savefile();
}
void remove_books()
{
    int id,found=0;
    printf("Enter the book ID to delete :");
    scanf("%d",&id);
    for(int i=0; i<n; i++)
    {
        if(books[i].id==id)
        {
            found=1;
            for(int j=i; j<n-1; j++)
            {
                books[j]=books[j+1];
            }
            n--;
            printf("%d book deleted successfully\n",id);
            savefile();
            return;
        }
    }
    if(found==0)
    {
        printf("Book not found");
    }
}

void sort()
{
    for(int i = 1; i < n; i++)
    {
        struct library t = books[i];
        int j = i - 1;
        while(j >= 0 && books[j].id > t.id)
        {
            books[j + 1] = books[j];
            j--;
        }
        books[j + 1] = t;
    }
}

void binary_search(int id)
{
    sort();
    int first=0, last=n-1,mid;
    while(first<=last)
    {
        mid=(first+last)/2;
        if(books[mid].id<id)
            first=mid+1;
        else if(books[mid].id==id)
        {
            printf("Book found: ID = %d, Title = %s, Author = %s\n",
                    books[mid].id, books[mid].title, books[mid].author);
            return;
        }
        else
            last=mid-1;
        mid=(first+last)/2;
    }
    printf("Book not found in the list\n");

}
void display_books_sorted()
{
    if (n == 0)
    {
        printf("No books available.\n");
        return;
    }

    sort();

    printf("\nList of Books:\n");
    printf("----------------------------------------------------\n");
    printf("ID\t\tTitle\t\t\tAuthor\n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%s\t\t%s\n", books[i].id, books[i].title, books[i].author);
    }

    printf("----------------------------------------------------\n");
}

int main()
{
    int choice, id;
    loadfile();
    printf("Library Management System\n\n");

    while (1)
    {
        printf("***********************************\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Search Book by ID\n");
        printf("4. Display All Books\n");
        printf("5. Exit\n");
        printf("***********************************\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            add_books();
        }
        else if (choice == 2)
        {
            remove_books();
        }
        else if (choice == 3)
        {
            printf("Enter book ID to search: ");
            scanf("%d", &id);
            binary_search(id);
        }
        else if (choice == 4)
        {
            display_books_sorted();
        }
        else if (choice == 5)
        {
            printf("Exiting program...\n");
            return 0;
        }
        else
        {
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
