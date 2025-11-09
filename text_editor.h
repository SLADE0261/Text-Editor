#ifndef TEXT_EDITOR
#define TEXT_EDITOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curser_navigations.h"

#define INITIAL_CAPACITY 10
#define SUCCESS 0
#define FAILURE 1

// Define the structure for a node in the linked list (each line in the editor)
typedef struct Node {
    char line[100];
    struct Node *prev;
    struct Node *next;
} Node;

// Define the structure for the text editor
typedef struct {
    Node *head;       // Pointer to the first line
    Node *tail;       // Pointer to the last line
    Node *cursor;     // Pointer to the current line where the cursor is
    int cursorLine;   // Line number of the cursor
    int cursorPos;    // Column position of the cursor
    char filename[100]; 
} TextEditor;

// Define the structure for an action (used for undo/redo operations)
typedef struct {
    char operation[20];  // Operation type ("insert" or "delete")
    char text[100];       // Text involved in the operation
    int cursorLine;   // Line number where the operation occurred
    int cursorPos;    // Column position where the operation occurred
} Action;

// Define the structure for a dynamic array stack (used for undo/redo stacks)
typedef struct {
    Action *actions;  // Dynamic array of actions
    int size;         // Current size of the stack
    int capacity;     // Tottal capacity of the stack
} DynamicArrayStack;

void printMenu();
void print_list(Node *head);
int handleCommand(char *command, TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
int insert_last(Node **head, Node **tail, char *data);
void free_list(Node *head);

void moveCursorUp(TextEditor *editor);
void moveCursorDown(TextEditor *editor);
void moveCursorLeft(TextEditor *editor);
void moveCursorRight(TextEditor *editor);
void jumpToStartOfFile(TextEditor *editor);
void jumpToEndOfFile(TextEditor *editor);
void jumpToStartOfLine(TextEditor *editor);
void jumpToEndOfLine(TextEditor *editor);
#endif
