#include "text_editor.h"
// Stack operations
void initStack(DynamicArrayStack *stack);
void pushStack(DynamicArrayStack *stack, Action *action);
Action  *popStack(DynamicArrayStack *stack);
int isStackEmpty(DynamicArrayStack *stack);

// Undo/redo operations
int redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
int undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
// Initialization
void init(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);

void undoinsertfun(TextEditor *editor, const char *text, DynamicArrayStack *undoredo);
