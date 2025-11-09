
#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"

char copied_Word[100] = {0};
int fileopend;

int main()
{
    // Initialize the text editor and stacks
    TextEditor editor;
    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;

    // initialize the structure members
    init(&editor, &undoStack, &redoStack);

    // buffer to store the command
    char command[256];

    while (1)
    {
        printMenu();
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        // TODO Remove newline character

        if (strcmp(command, "exit") == 0)
            break;
        else
            handleCommand(command, &editor, &undoStack, &redoStack);
    }
    return 0;
}
void printMenu()
{
    printf("\033[1;32m");
    printf("MENU:\n"
           "1. open <filename>       5. move up              9. jump to start              12. insert \"text\"          16. cut <start> <end>\n"
           "2. save                  6. move down           10. jump to end                13. delete <length>         17. copy <start> <end>\n"
           "3. saveas <filename>     7. move left           11. jump to start of line      14. undo                    18. paste\n"
           "4. close                 8. move right          12. jump to end of line        15. redo\n");
    printf("\033[0m");
}

int handleCommand(char *command, TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    char comm[20], buffer[256] = {};
    if (sscanf(command, "%s %[^\n]", comm, buffer) > 0)
    {
        // open the file
        if (strcmp(comm, "open") == 0)
        {
            if(fileopend)
            {
                printf("\033[1;31m");
                printf("%s file is already opened\n",editor->filename);
                printf("\033[0m");
            }
            else if(openFile(editor, buffer) == FAILURE)
            {
                printf("\033[1;31m");
                printf("Failed to open the file\n");
                printf("\033[0m");
                return FAILURE;
            }
            strcpy(editor->filename, buffer);
        }
        //check if file is opened or not
        else if (!fileopend)
        {
            printf("\033[1;31m");
            printf("Please open a file before performing the operation.\n");
            printf("\033[0m");
            return FAILURE;
        }
        else if (strcmp(comm, "save") == 0)
        {
            if (strlen(editor->filename) == 0)
            {
                printf("\033[1;31m");
                printf("\nNo file opened to save.\n\n");
                printf("\033[0m");
                return FAILURE;
            }
            if (saveFile(editor, editor->filename) == FAILURE)
                return FAILURE;
        }
        else if (strcmp(comm, "saveas") == 0)
        {
            if (strlen(buffer) == 0)
            {
                printf("\033[1;31m");
                printf("No file opened to saveas.\n\n");
                printf("\033[0m");
                return FAILURE;
            }
            if (saveFile(editor, buffer) == FAILURE)
                return FAILURE;
        }
        else if (strcmp(comm, "close") == 0)
        {
            if (strlen(editor->filename) == 0)
            {
                printf("\033[1;31m");
                printf("\nNo file opened to close.\n\n");
                printf("\033[0m");
                return FAILURE;
            }
            closeFile(editor);
            fileopend=0;
        }
        else if (strcmp(comm, "insert") == 0)
        {
            if (strlen(buffer) == 0)
            {
                printf("\033[1;31m");
                printf("\nNo text provided to insert.\n\n");
                printf("\033[0m");
                return FAILURE;
            }
            if (insertText(editor, buffer, undoStack) == FAILURE)
            {
                printf("\033[1;31m");
                printf("Failed to insert text");
                printf("\033[0m");
            }
        }
        else if (strcmp(comm, "delete") == 0)
        {
            if (strlen(buffer) == 0)
            {
                printf("\033[1;31m");
                printf("\nNo number provided to delete.\n\n");
                printf("\033[0m");
                return FAILURE;
            }
            if (deleteText(editor, atoi(buffer), undoStack) == FAILURE)
            {
                printf("\033[1;31m");
                printf("\nInvalid delete Range\n");
                printf("\033[0m");
            }
        }
        else if (strcmp(comm, "move") == 0)
        {
            if (strcmp(buffer, "up") == 0)
            {
                moveCursorUp(editor);
            }
            else if (strcmp(buffer, "down") == 0)
            {
                moveCursorDown(editor);
            }
            else if (strcmp(buffer, "left") == 0)
            {
                moveCursorLeft(editor);
            }
            else if (strcmp(buffer, "right") == 0)
            {
                moveCursorRight(editor);
            }
            else
            {
                printf("\033[1;31m");
                printf("Unknown command.\n");
                printf("\033[0m");
            }
        }
        else if (strcmp(comm, "jump") == 0)
        {
            if (strcmp(buffer, "to start") == 0)
            {
                jumpToStartOfFile(editor);
            }
            else if (strcmp(buffer, "to end") == 0)
            {
                jumpToEndOfFile(editor);
            }
            else if (strcmp(buffer, "to start of line") == 0)
            {
                jumpToStartOfLine(editor);
            }
            else if (strcmp(buffer, "to end of line") == 0)
            {
                jumpToEndOfLine(editor);
            }
            else
            {
                printf("\033[1;31m");
                printf("Unknown command.\n");
                printf("\033[0m");
            }
        }

        else if (strcmp(comm, "undo") == 0)
        {
            undo(editor, undoStack, redoStack);
        }
        else if (strcmp(comm, "redo") == 0)
        {
            redo(editor, undoStack, redoStack);
        }
        else if (strcmp(comm, "cut") == 0)
        {
            int st, end;
            if (sscanf(buffer, "%d %d", &st, &end) == 2)
            {
                if (cutText(editor, st, end, copied_Word, undoStack) == FAILURE)
                {
                    printf("\033[1;31m");
                    printf("Invalid Cut range\n");
                    printf("\033[0m");
                }
            }
            else
                printf("Usage: cut <start> <end>\n");
        }
        else if (strcmp(comm, "copy") == 0)
        {
            int st, end;
            if (sscanf(buffer, "%d %d", &st, &end) == 2)
            {
                if (copyText(editor, st, end, copied_Word) == FAILURE)
                {
                    printf("\033[1;31m");
                    printf("Invalid copy range\n");
                    printf("\033[0m");
                }
            }
            else
                printf("Usage: copy <start> <end>\n");
        }
        else if (strcmp(comm, "paste") == 0)
        {
            if (pasteText(editor, copied_Word, undoStack) == FAILURE)
            {
                printf("\033[1;31m");
                printf("Failed to paste the text\n");
                printf("\033[0m");
            }
        }
        else
        {
            printf("\033[1;31m");
            printf("Unknown command.\n");
            printf("\033[0m");
        }
        displayText(editor);
        showCursorPosition(editor);
        return SUCCESS;
    }
}