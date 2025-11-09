#include "redo_undo.h"
#include "text_editor.h"

void init(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    editor->head=NULL;
    editor->tail=NULL;
    editor->cursor=NULL;
    editor->cursorPos=0;
    editor->cursorLine=0;
    editor->filename[0]='\0';

    initStack(undoStack);
    initStack(redoStack);
}

void initStack(DynamicArrayStack *stack)
{
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->actions = malloc(sizeof(Action) * stack->capacity);
}