#include "text_ops.h"
#include "text_editor.h"
#include "display_search.h"

void undoinsertfun(TextEditor *editor, const char *text, DynamicArrayStack *undostack)
{
    if (undostack->size >= undostack->capacity)
    {
        printf("\033[1;31m");
        printf("Limit exceed!!!\n");
        printf("\033[0m");
        return;
    }

    Action *action = &undostack->actions[undostack->size];

    action->cursorLine = editor->cursorLine;
    action->cursorPos = editor->cursorPos;
    strcpy(action->operation, "insert");

    // Remove double quotes if present
    int len = strlen(text);
    if (text[0] == '\"' && text[len - 1] == '\"')
    {
        strncpy(action->text, text + 1, len - 2);
        action->text[len - 2] = '\0';
    }
    else
    {
        strcpy(action->text, text);
    }
    undostack->size++;
}

int insertText(TextEditor *editor, const char *text, DynamicArrayStack *undostack)
{
    if (strlen(editor->filename) == 0)
    {
        printf("\033[1;31m");
        printf("\nNo file opened to insert.\n\n");
        printf("\033[0m");
        return FAILURE;
    }

    undoinsertfun(editor, text, undostack);

    char buffer[1000];
    int i = 0, j = 0, k = 0;

    while (j < editor->cursorPos && editor->cursor->line[i] != '\0')
    {
        buffer[j] = editor->cursor->line[i];
        i++;
        j++;
    }

    if (text[0] == '\"')
        k++;

    while (text[k] != '\0')
    {
        buffer[j++] = text[k++];
    }

    if (buffer[j - 1] == '\"')
        j--;
    editor->cursorPos = j;
    while (editor->cursor->line[i] != '\0')
    {
        buffer[j++] = editor->cursor->line[i++];
    }
    buffer[j] = '\0';
    editor->cursor->line[0] = '\0';
    strcpy(editor->cursor->line, buffer);
    // editor->cursorPos = j;

    return SUCCESS;
}
void undodeletefun(TextEditor *editor, const char *text, DynamicArrayStack *undostack)
{
    if (undostack->size >= undostack->capacity)
    {
        printf("\033[1;31m");
        printf("Limit exceed!!!\n");
        printf("\033[0m");
        return;
    }

    Action *action = &undostack->actions[undostack->size];

    action->cursorLine = editor->cursorLine;
    action->cursorPos = editor->cursorPos;
    strcpy(action->operation, "delete");
    strcpy(action->text, text);

    undostack->size++;
}

int deleteText(TextEditor *editor, int length, DynamicArrayStack *undostack)
{
    int lineLen = strlen(editor->cursor->line);
    int deleteLimit = lineLen - editor->cursorPos;

    if (length > deleteLimit || length <= 0)
        return FAILURE;

    int k = 0;
    char buffer[50];

    // Perform the delete
    for (int i = 0; i < length; i++)
    {
        buffer[k++] = editor->cursor->line[editor->cursorPos];
        for (int j = editor->cursorPos; editor->cursor->line[j]; j++)
        {
            editor->cursor->line[j] = editor->cursor->line[j + 1];
        }
    }
    buffer[k] = '\0';
    undodeletefun(editor, buffer, undostack);
    return SUCCESS;
}

int copyText(TextEditor *editor, int st, int end, char *copied_Word)
{
    if (st < 0 || end < st || end >= strlen(editor->cursor->line))
        return FAILURE;

    int len = end - st + 1;
    strncpy(copied_Word, editor->cursor->line + st, len);
    copied_Word[len] = '\0';
    return SUCCESS;
}

int pasteText(TextEditor *editor, char *copied_Word, DynamicArrayStack *undostack)
{
    if (copied_Word[0] == '\0')
        return FAILURE;

    if (insertText(editor, copied_Word, undostack) == FAILURE)
        return FAILURE;
    else
        printf("Pasted : %s", copied_Word);
    return SUCCESS;
}

int cutText(TextEditor *editor, int st, int end, char *copied_Word, DynamicArrayStack *undostack)
{
    if (st < 0 || end < st || end >= strlen(editor->cursor->line))
        return FAILURE;

    int len = end - st + 1;
    // Copy the text to be cut into copied_Word
    strncpy(copied_Word, editor->cursor->line + st, len);
    copied_Word[len] = '\0';

    // Set cursor position to the start of the cut range
    editor->cursorPos = st;

    // Call deleteText
    if (deleteText(editor, len, undostack) == FAILURE)
    {
        printf("\033[1;31m");
        printf("Cut operation failed.\n");
        printf("\033[0m");
        return FAILURE;
    }

    printf("Cut: \"%s\"\n", copied_Word);
    return SUCCESS;
}
