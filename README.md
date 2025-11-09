# TextEditor

A feature-rich command-line text editor implemented in C with support for undo/redo operations, cursor navigation, and text manipulation.

## Overview

TextEditor is a lightweight, terminal-based text editor built using doubly-linked lists to manage text content. It provides essential editing capabilities including insert, delete, cut, copy, paste operations, along with a robust undo/redo system for tracking changes.

## Features

- **File Operations**: Open, save, save as, and close text files
- **Text Manipulation**: Insert, delete, cut, copy, and paste text
- **Cursor Navigation**: Move cursor up, down, left, right with boundary protection
- **Jump Commands**: Quick navigation to file start/end and line start/end
- **Undo/Redo System**: Track and reverse operations using dynamic array stacks
- **Live Display**: Real-time content display with cursor position tracking
- **Error Handling**: Comprehensive validation and colored error messages

## Technical Details

- **Data Structure**: Doubly-linked list for text lines
- **Undo/Redo**: Dynamic array-based stack implementation
- **Language**: C
- **Platform**: Cross-platform (Linux, macOS, Windows with appropriate compiler)

### Architecture

**Core Components:**
1. **TextEditor Structure** - Manages document state with head, tail, and cursor pointers
2. **Node Structure** - Represents individual lines (100 char limit per line)
3. **Action Structure** - Records operations for undo/redo functionality
4. **DynamicArrayStack** - Implements undo/redo stacks with dynamic capacity

## Prerequisites

- GCC compiler or any C compiler
- Basic knowledge of command line operations
- Terminal with ANSI color support (for colored output)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/TextEditor.git
cd TextEditor
```

2. Compile the project:
```bash
gcc text_editor.c file_ops.c text_ops.c redo_undo.c curser_navigations.c init.c -o texteditor
```

Or compile with a Makefile:
```bash
make
```

## Usage

### Starting the Editor

```bash
./texteditor
```

The editor will display a menu with available commands and wait for your input.

### Available Commands

#### File Operations

| Command | Syntax | Description |
|---------|--------|-------------|
| open | `open <filename>` | Open a text file (must be .txt) |
| save | `save` | Save changes to the current file |
| saveas | `saveas <filename>` | Save to a new file |
| close | `close` | Close the current file |
| exit | `exit` | Exit the editor |

#### Cursor Navigation

| Command | Syntax | Description |
|---------|--------|-------------|
| move up | `move up` | Move cursor one line up |
| move down | `move down` | Move cursor one line down |
| move left | `move left` | Move cursor one character left |
| move right | `move right` | Move cursor one character right |

#### Jump Commands

| Command | Syntax | Description |
|---------|--------|-------------|
| jump to start | `jump to start` | Jump to start of file |
| jump to end | `jump to end` | Jump to end of file |
| jump to start of line | `jump to start of line` | Jump to beginning of current line |
| jump to end of line | `jump to end of line` | Jump to end of current line |

#### Text Operations

| Command | Syntax | Description |
|---------|--------|-------------|
| insert | `insert "text"` | Insert text at cursor position |
| delete | `delete <length>` | Delete specified number of characters |
| cut | `cut <start> <end>` | Cut text from start to end position |
| copy | `copy <start> <end>` | Copy text from start to end position |
| paste | `paste` | Paste previously copied/cut text |

#### Undo/Redo

| Command | Syntax | Description |
|---------|--------|-------------|
| undo | `undo` | Undo last operation |
| redo | `redo` | Redo previously undone operation |

## Example Workflow

```bash
# 1. Start the editor
./texteditor

# 2. Open a file
Enter command: open sample.txt

# 3. Insert text
Enter command: insert "Hello, World!"

# 4. Move cursor
Enter command: move left

# 5. Delete characters
Enter command: delete 5

# 6. Undo the deletion
Enter command: undo

# 7. Copy text
Enter command: copy 0 5

# 8. Move to end of line
Enter command: jump to end of line

# 9. Paste copied text
Enter command: paste

# 10. Save changes
Enter command: save

# 11. Exit
Enter command: exit
```

## Project Structure

```
TextEditor/
├── text_editor.c           # Main program and command handler
├── text_editor.h           # Core structure definitions
├── file_ops.c              # File operations implementation
├── file_ops.h              # File operations declarations
├── text_ops.c              # Text manipulation functions
├── text_ops.h              # Text operations declarations
├── redo_undo.c             # Undo/redo implementation
├── redo_undo.h             # Undo/redo declarations
├── curser_navigations.c    # Cursor movement functions
├── curser_navigations.h    # Navigation declarations
├── display_search.h        # Display function declarations
├── init.c                  # Initialization functions
└── README.md               # This file
```

## Important Notes

1. **File Format**: Only .txt files are supported
2. **Line Length**: Maximum 100 characters per line
3. **Stack Capacity**: Initial capacity of 10 operations (expandable)
4. **Insert Format**: Text must be enclosed in double quotes
5. **Cursor Position**: Always displayed after each operation
6. **File State**: Must open a file before performing text operations

## Features in Detail

### Undo/Redo System

The editor maintains two stacks:
- **Undo Stack**: Records all insert and delete operations
- **Redo Stack**: Stores undone operations for redo capability

Operations are automatically tracked, and the system supports:
- Reversing insertions by deleting the inserted text
- Reversing deletions by reinserting the deleted text
- Clearing redo stack when new operations are performed

### Cursor Management

The cursor system ensures:
- Boundary protection (prevents moving beyond text limits)
- Automatic position adjustment when moving between lines
- Cursor position persistence during undo/redo operations
- Real-time position display after each command

### Text Buffer

Each line is managed as a node in a doubly-linked list:
- Forward and backward traversal capability
- Dynamic insertion and deletion
- Efficient memory usage
- Easy line-by-line manipulation

## Error Messages

| Error | Meaning | Solution |
|-------|---------|----------|
| Please open a file before performing the operation | No file is currently open | Use `open <filename>` first |
| file is already opened | Attempting to open another file | Close current file first |
| No file opened to save | No file to save | Open or create a file first |
| Nothing to undo | Undo stack is empty | No operations to reverse |
| Nothing to redo | Redo stack is empty | No undone operations available |
| Invalid delete Range | Delete length exceeds available characters | Check cursor position and line length |
| Invalid Cut/Copy range | Range parameters are invalid | Ensure start < end and within line bounds |
| Cursor is at the beginning/end | Cannot move in that direction | Cursor at boundary |
| Limit exceed!!! | Undo stack capacity reached | Internal capacity limitation |

## Color-Coded Output

The editor uses ANSI color codes for better visibility:
- **Green**: Menu and informational messages
- **Red**: Error messages and warnings
- **Default**: Content display and cursor information

## Limitations

- Single line editing (no multi-line operations)
- Fixed line length (100 characters)
- Text-only files (.txt extension required)
- No syntax highlighting
- No search/replace functionality (header declared but not implemented)

## Security Considerations

- No encryption for saved files
- File permissions depend on operating system
- No backup or auto-save functionality
- Unsaved changes are lost on crash

## Contributing

Contributions are welcome! Areas for improvement:
- Multi-line text operations
- Search and replace functionality
- Syntax highlighting
- Auto-save feature
- Configuration file support
- Extended undo/redo history

Please feel free to submit pull requests or open issues for bugs and feature requests.

## License

This project is open source and available under the [MIT License](LICENSE).

## Author

**Your Name**
- Project: Command-Line Text Editor
- Implementation Date: 2025

## Acknowledgments

- Doubly-linked list data structure
- Dynamic array stack implementation
- ANSI terminal color codes
- C programming community

## Future Enhancements

- [ ] Multi-line selection and operations
- [ ] Search and replace functionality
- [ ] Regex support for advanced text manipulation
- [ ] Line numbering display
- [ ] Word wrap support
- [ ] File change detection
- [ ] Auto-save functionality
- [ ] Configurable key bindings
- [ ] Syntax highlighting for common languages
- [ ] Extended undo/redo history with persistence

---

**⭐ If you find this project useful, please consider giving it a star!**