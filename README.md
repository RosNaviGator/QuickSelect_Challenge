# Linear Select function

### Contributors:
Marco Cioci, Francesco Rosnati, Luca Tramacere

## Context
### Course: Algoritmi e Architetture per il Calcolo ad Alte Prestazioni at Politecnico di Milano

The project was developed as part of a Challenge/Project assigned by Professor Fabrizio Ferrandi during the course "Algoritmi e Architetture per il Calcolo ad Alte Prestazioni" at Politecnico di Milano. This course is offered as part of the elective courses in the Mathematical Engineering Bachelor program.

## Purpose of the Algorithm 
Find the i-th smallest element in an unsorted array, with linear time complexity in the worst-case scenario.

## General Description of the Steps of the Select Algorithm
![steps](./img/steps.png)

## Content of the Repo and Instructions
### .ipynb Notebook
The notebook is self-contained, providing a comprehensive explanation and implementation of the project, including a GoogleBenchmark study at the end.
- It can be easily opened in Google Colab or any Notebook reader.
- Requires a C++ compiler; only standard C++ libraries are used.
- Python with matplotlib is required for plotting graphs.
- Google Benchmark will be installed during runtime, with commands already provided in the Notebook.

### cppFiles (Old Versions)
- challenge2.cpp
- challenge3.cpp
- select.cpp
- testScripts.cpp

These CPP files are previous versions of the project or test files, with select.cpp being the final version of the algorithm before moving it to a .ipynb notebook. Each file is standalone, containing main and all required functions. No classes were used in this project, as the primary goal was to achieve a specific threshold in terms of Google Benchmark performance, thus low level coding was the best choice. Compilation requires any standard compiler of C++, only standard C++ libraries are utilized.
