# 🔍 DeepFind – Personal Search Engine

**DeepFind** is a C++-based personal content search engine designed to help users quickly find information stored inside their personal files. Instead of searching only through file names and folder locations, DeepFind searches the actual content of files and displays the most relevant results based on word frequency.

The system supports `.txt`, `.cpp`, and `.h` files, making it useful for students who want to search through their notes, assignments, and previously written source code.

DeepFind uses fundamental Data Structures and Algorithms (DSA), including Hash Tables, Tries, Heaps, Vectors, and Sorting Algorithms, to provide efficient indexing, searching, result ranking, and word suggestions.

## 📌 Project Overview

As the number of personal files increases, finding specific information becomes difficult, especially when users remember the content but forget the file name or location.

DeepFind addresses this problem by scanning files, indexing their contents, and retrieving relevant information through a simple graphical user interface (GUI).

Users can search for specific words or multiple words and receive ranked results containing file paths, line numbers, occurrence counts, and matching text snippets.

## 🎯 Objectives

- Develop a personal search engine that searches inside files rather than relying on file names.
- Implement efficient file indexing using appropriate data structures.
- Retrieve relevant search results quickly.
- Rank matching files according to word frequency.
- Provide word suggestions while users type.
- Display matching file paths, line numbers, and text snippets.
- Demonstrate the practical application of Data Structures and Algorithms in C++.

## ✨ Key Features

- **Content-Based Searching:** Searches inside file contents rather than relying only on file names.
- **Multiple File Support:** Indexes and searches `.txt`, `.cpp`, and `.h` source and text files.
- **Recursive Directory Scanning:** Automatically scans a target folder and all nested subdirectories.
- **Inverted Index Architecture:** Maps every unique word to its matching files, frequency counts, and exact line numbers for fast lookup.
- **Stop-Word Filtering:** Ignores common filler words (e.g., *the*, *is*, *and*) to keep indexing fast and results relevant.
- **Ranked Search Results:** Ranks matching files by word frequency and relevance score.
- **Detailed Match Snippets:** Displays file paths, total occurrences, line numbers, and matching lines of text.
- **Multi-Word Search:** Supports searching with single or multiple keywords at once.
- **Word Suggestions:** Suggests matching words based on the prefix entered by the user.
- **Direct File Access:** Lets users open or inspect selected files directly from the search results.
- **Graphical User Interface:** Provides a clean, user-friendly interface for searching and viewing results.

## 🧠 Data Structures and Algorithms

DeepFind implements core data structures from scratch in C++ (without relying on STL containers) to power indexing, lookup, and ranking:

| Data Structure / Algorithm | Purpose |
| :--- | :--- |
| **Custom Hash Table** | Stores the inverted index (`word` $\rightarrow$ `FilePosting` list) for $O(1)$ average-case word lookup. |
| **Custom Dynamic Vector** | Manages collections of indexed files, file lines, posting lists, and occurrences. |
| **Custom Set** | Stores stop words for fast filtering during tokenization and indexing. |
| **Trie (Prefix Tree)** | Provides word autocomplete suggestions based on typed prefixes. |
| **Heap / Priority Queue** | Efficiently extracts the top-$K$ highest-ranked search results. |
| **Sorting Algorithms** | Orders search results by relevance score and occurrence frequency. |

## ⚙️ How It Works

DeepFind follows a modular pipeline to index and retrieve personal files:

1. **Directory Crawling:** Recursively scans the selected root folder and its subdirectories for `.txt`, `.cpp`, and `.h` files.
2. **Tokenization & Cleaning:** Reads file contents line by line, strips formatting characters, converts text to lowercase, and filters out stop words.
3. **Inverted Indexing:** Populates a custom hash table mapping each unique word to its file IDs, word counts, and line occurrences.
4. **Query Processing:** Tokenizes user search queries and retrieves matching posting lists from the inverted index.
5. **Relevance Ranking:** Scores and ranks matching files based on keyword frequency using a heap/sorting pipeline.
6. **Result Display:** Outputs ranked file paths, occurrence counts, line numbers, and matching text snippets.
7. **Prefix Suggestions:** Queries a Trie to suggest matching indexed words for user prefixes.
8. **File Access:** Allows users to open or view the selected file directly from the results.

## 🛠️ Technologies Used

- **Programming Language:** C++ (C++17)
- **User Interface:** Interactive Command-Line Interface (CLI) with real-time keystroke suggestions
- **Custom Data Structures:** `CustomVector`, `CustomHashTable`, `CustomSet`, `CustomTrie`
- **Standard C++ Headers:** `<iostream>`, `<fstream>`, `<filesystem>`, `<string>`, `<cctype>`, `<conio.h>`
- **Compiler & Tools:** GCC / MinGW-w64 (`g++`), Visual Studio / VS Code
- **Operating System:** Windows
- **Version Control:** Git and GitHub

## 🔎 Example Use Case

Suppose a student wants to find information about **Stack** but cannot remember which file contains the relevant notes or code.

Using DeepFind, the student can:

1. Select the folder containing their notes and source code.
2. Enter `stack` in the search bar.
3. View matching files ranked by the number of occurrences.
4. Check the file path, line number, and matching text snippet.
5. Open the required file directly from the search results.

## 🔮 Future Enhancements

- Support for additional file formats such as `.pdf` and `.docx`.
- Advanced search options and filtering.
- Improved relevance-ranking algorithms.
- Search history and recently opened files.
- More advanced text-processing capabilities.

## 👥 Team Members

This project is developed collaboratively by a team of three members.

- Esh tu Razia
- Syeda Eisha Tahir
- Anseeba Ali Jivani

## 📄 License

This project is developed for educational purposes as part of a Data Structures and Algorithms course.


---

<h3 align="center">🔍 DeepFind</h3>
<p align="center">
  <b>Find What You Remember, Not Just What You Named.</b>
</p>