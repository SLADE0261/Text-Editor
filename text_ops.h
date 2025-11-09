#include "text_editor.h"

int insertText(TextEditor *editor, const char *text, DynamicArrayStack *undoStack);
int deleteText(TextEditor *editor, int length,DynamicArrayStack *undostack);
int copyText(TextEditor *editor,int st,int end,char *copied_Word);
int cutText(TextEditor *editor, int st, int end, char *copied_Word, DynamicArrayStack *undostack);
int pasteText(TextEditor *editor, char *copied_Word, DynamicArrayStack *undostack);