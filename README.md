# expense-tracker-cli

A command-line expense management application written in C. It allows users to track, add, edit, delete, and persistently save personal expenses using file I/O and structured data.

### Features
* **File Persistence:** Automatically loads and saves expense records to a local `expenses.txt` file using pipe-delimited formatting.
* **CRUD Operations:** Add new entries, update existing details, or delete expenses by ID with automatic row re-indexing.
* **Safe Input Handling:** Utilizes `fgets` and `sscanf` to prevent buffer overflows and manage user errors safely.
* **Clean Table Output:** Displays recorded expenses in a formatted tabular layout right in the console.

