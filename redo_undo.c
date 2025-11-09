#include "text_editor.h"
#include "display_search.h"
#include <string.h>
#include <stdio.h>

#define UNDO 0
#define REDO 1

void doInsert(TextEditor *editor, Action *action)
{
    Node *temp = editor->head;
    int line = 0;
    while (temp && line < action->cursorLine - 1)
    {
        temp = temp->next;
        line++;
    }

    editor->cursor = temp;
    editor->cursorLine = action->cursorLine;
    editor->cursorPos = action->cursorPos;

    int len = strlen(action->text);
    for (int i = strlen(temp->line); i >= editor->cursorPos; i--)
    {
        temp->line[i + len] = temp->line[i];
    }
    for (int i = 0; i < len; i++)
    {
        temp->line[editor->cursorPos + i] = action->text[i];
    }
}

void doDelete(TextEditor *editor, Action *action)
{
    Node *temp = editor->head;
    int line = 0;
    while (temp && line < action->cursorLine - 1)
    {
        temp = temp->next;
        line++;
    }

    editor->cursor = temp;
    editor->cursorLine = action->cursorLine;
    editor->cursorPos = action->cursorPos;

    int len = strlen(action->text);
    for (int i = 0; i < len; i++)
    {
        for (int j = editor->cursorPos; temp->line[j]; j++)
        {
            temp->line[j] = temp->line[j + 1];
        }
    }
}

int undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if (undoStack->size == 0)
    {
        printf("\033[1;31m");
        printf("\nNothing to undo.\n");
        printf("\033[0m");
        return FAILURE;
    }

    Action lastAction = undoStack->actions[--undoStack->size];

    if (strcmp(lastAction.operation, "insert") == 0)
        doDelete(editor,  &lastAction);
    else if (strcmp(lastAction.operation, "delete") == 0)
        doInsert(editor,  &lastAction);

    if (redoStack->size < redoStack->capacity)
        redoStack->actions[redoStack->size++] = lastAction;

    printf("\nUndo: %s '%s'\n", lastAction.operation, lastAction.text);
    return SUCCESS;
}

int redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if (redoStack->size == 0)
    {
        printf("\033[1;31m");
        printf("\nNothing to redo.\n");
        printf("\033[0m");
        return FAILURE;
    }

    Action lastAction = redoStack->actions[--redoStack->size];

    if (strcmp(lastAction.operation, "delete") == 0)
        doDelete(editor,  &lastAction);
    else if (strcmp(lastAction.operation, "insert") == 0)
        doInsert(editor,  &lastAction);

    if (undoStack->size < undoStack->capacity)
        undoStack->actions[undoStack->size++] = lastAction;

    printf("\nRedo: %s '%s'\n", lastAction.operation, lastAction.text);
    return SUCCESS;
}
