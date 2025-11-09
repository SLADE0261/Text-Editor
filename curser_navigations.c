#include "text_editor.h"
#include "display_search.h"
#include <string.h>

void moveCursorUp(TextEditor *editor)
{
    if (editor->cursor->prev)
    {
        int curr_pos = editor->cursorPos;
        editor->cursor = editor->cursor->prev;
        editor->cursorLine--;

        int new_len = strlen(editor->cursor->line);

        if (curr_pos >= new_len)
            editor->cursorPos = new_len; 
    }
    else
    {
        printf("\033[1;31m");
        printf("\nAlready at the first line. Cannot move up.\n");
        printf("\033[0m");
    }
}

void moveCursorDown(TextEditor *editor)
{
    if (editor->cursor->next)
    {
        int curr_pos = editor->cursorPos;
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;

        int new_len = strlen(editor->cursor->line);

        if (curr_pos >= new_len)
            editor->cursorPos = new_len;  
    }
    else
    {
        printf("\033[1;31m");
        printf("\nAlready at the last line. Cannot move down.\n");
        printf("\033[0m");
    }
}

void moveCursorLeft(TextEditor *editor)
{
    if (editor->cursorPos > 0)
        editor->cursorPos--;
    else
    {
        printf("\033[1;31m");
        printf("\nCursor is at the beginning of the line. Cannot move left.\n");
        printf("\033[0m");
    }
}

void moveCursorRight(TextEditor *editor)
{
    int len = strlen(editor->cursor->line);
    if (editor->cursorPos < len)
        editor->cursorPos++;
    else
    {
        printf("\033[1;31m");
        printf("\nCursor is at the end of the line. Cannot move right.\n");
        printf("\033[0m");
    }
}


void jumpToStartOfFile(TextEditor *editor)
{
    editor->cursor = editor->head;
    editor->cursorLine = 1;
    editor->cursorPos = 0;
}
void jumpToEndOfFile(TextEditor *editor)
{
    editor->cursor = editor->tail;
    Node *temp = editor->head;
    editor->cursorLine = 0;
    while (temp != NULL)
    {
        editor->cursorLine++;
        temp = temp->next;
    }
    int len = strlen(editor->cursor->line);
    editor->cursorPos = len;
}
void jumpToStartOfLine(TextEditor *editor)
{
    editor->cursorPos = 0;
}
void jumpToEndOfLine(TextEditor *editor)
{
    int len = strlen(editor->cursor->line);
    editor->cursorPos = len;
}