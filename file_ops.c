#include "redo_undo.h"
#include "text_editor.h"
#include "display_search.h"
extern int fileopend;
int openFile(TextEditor *editor, const char *filename)
{
    if (strstr(filename, ".txt") == NULL)
    {
        printf("\033[1;31m");
        printf("\nInvalid File Name\n");
        printf("\033[0m");
        return FAILURE;
    }

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("");
        return FAILURE;
    }
    fileopend = 1;
    Node *head = NULL;
    Node *tail = NULL;
    char line[250];
    while (fgets(line, sizeof(line), fptr))
    {
        // Remove newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0'; // Remove newline
        }
        if(len<=1) continue;
        if (insert_last(&head, &tail, line) == FAILURE)
        {
            printf("\033[1;31m");
            printf("Unable to create the list\n");
            printf("\033[0m");
        }

        editor->cursorLine++;
    }

    editor->head = head;
    editor->tail = tail;
    editor->cursorPos = strlen(tail->line);
    editor->cursor = tail;
}

int saveFile(TextEditor *editor, const char *filename)
{
    if (editor->head == NULL)
    {
        printf("\033[1;31m");
        printf("\nNo Data to Save\n\n");
        printf("\033[0m");
        return FAILURE;
    }
    if (strstr(filename, ".txt") == NULL)
    {
        printf("\033[1;31m");
        printf("Invalid filename for saveas\n");
        printf("\033[0m");
        return FAILURE;
    }
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("\033[1;31m");
        perror("File open error");
        printf("\033[0m");
        return FAILURE;
    }

    Node *temp = editor->head;
    while (temp)
    {
        fprintf(fptr, "%s\n", temp->line);
        temp = temp->next;
    }

    fclose(fptr);
    printf("\nFile saved successfully to %s\n\n", filename);
    return SUCCESS;
}

int closeFile(TextEditor *editor)
{
    if (editor->head)
        free_list(editor->head);

    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;
    editor->cursorPos = 0;
    editor->cursorLine = 0;
    editor->filename[0] = '\0';

    printf("\nFile closed successfully.\n\n");
    return SUCCESS;
}

void free_list(Node *head)
{
    Node *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int insert_last(Node **head, Node **tail, char *data)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
        return FAILURE;

    new->prev = NULL;
    strcpy(new->line, data);
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

void displayText(TextEditor *editor)
{
    Node *head = editor->head;
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        printf("\nContent:\n\n");
        while (head)
        {
            printf("%s\n", head->line);
            head = head->next;
        }
    }
}

void showCursorPosition(TextEditor *editor)
{
    printf("==================================\n");
    printf("Cursor Position: Line %d, Column %d\n", editor->cursorLine, editor->cursorPos);
    printf("==================================\n");
}
