# Поисковый движок / Search Engine

[Русская версия ниже/English version below]

## ru Русская версия

Поисковый движок по запросам с использованием библиотеки nlohmann/json.

Репозиторий содержит код поискового движка на С++17. Для работы с JSON-файлами и данными используется библиотека nlohmann/json.

### Возможности
- **Поиск по ключевым словам**: Поиск документов, содержащих все слова из запроса.
- **Ранжирование результатов**: Сортировка найденных документов по релевантности.
- **Многопоточная индексация**: Параллельная обработка документов при построении индекса с использованием `std::thread`.
- **C++**: Использование лямбда-выражений, `auto`, range-based for и других возможностей C++17.

### Технический стек
- **Язык**: C++17
- **Сборка**: CMake (кроссплатформенная сборка для Windows/Linux/Mac)
- **Тестирование**: Google Test
- **JSON**: nlohmann/json (включена в репозиторий, можно обновить вручную)
- **Многопоточность**: `std::thread` для параллельной индексации

### Принцип работы
1. **Настройка**: В `config.json` указываются пути к файлам для индексации и максимальное количество результатов.
2. **Запрос**: Пользователь формирует поисковые запросы в `requests.json`.
3. **Индексация**: При запуске движок автоматически строит инвертированный индекс всех указанных документов (с многопоточной обработкой).
4. **Обработка**: Запрос разбивается на отдельные слова.
5. **Поиск**: В индексе находятся документы, содержащие все слова запроса.
6. **Выдача**: Результаты ранжируются по релевантности, сортируются и записываются в `answers.json`.

### Старт программы
Скачайте репозиторий. Поместите файлы .json в папку с собранным приложением (по умолчанию они уже там) или в `include/ConverterJSON.h` измените пути к этим файлам.
В файле `config.json` - добавьте пути к файлам для поиска.
В файле `requests.json` - укажите поисковые запросы.

### Требования
Компилятор c поддержкой C++17  
Cmake 3.10  
Google test (включен в репозиторий)  
Библиотека Nlohmann/json (включена в репозиторий, можно обновить вручную)  

### Структура конфигураций
`config.json` - список путей к файлам, лимит результатов поиска.  
`requests.json` - поисковые запросы.  
`answers.json` - результаты поиска (генерируется и очищается от предыдущего ответа автоматически).  


## en English version

Search engine for keyword queries using nlohmann/json library.

This repository contains a C++17 search engine implementation. The nlohmann/json library is used for JSON file handling and data processing.

### Features
- **Keyword search**: Finds documents containing all words from the query.
- **Relevance ranking**: Sorts results by relevance score.
- **Multithreaded indexing**: Parallel document processing during index construction using `std::thread`.
- **C++**: Utilizes lambda expressions, `auto`, range-based for loops, and other C++17 features.

### Tech Stack
- **Language**: C++17
- **Build System**: CMake (cross-platform build for Windows/Linux/Mac)
- **Testing**: Google Test
- **JSON**: nlohmann/json (bundled in repository, can be updated manually)
- **Concurrency**: `std::thread` for parallel indexing

### How It Works
1. **Configuration**: `config.json` specifies file paths for indexing and maximum result count.
2. **Query**: User creates search queries in `requests.json`.
3. **Indexing**: On startup, the engine automatically builds an inverted index of all specified documents (with multithreaded processing).
4. **Processing**: Query is split into individual words.
5. **Search**: Documents containing all query words are found in the index.
6. **Output**: Results are ranked by relevance, sorted, and written to `answers.json`.

### Quick Start
Download the repository. Place the .json files in the folder with the built application (they are already there by default) or change the paths to these files in `include/ConverterJSON.h`.
In `config.json` — add paths to the files for searching.
In `requests.json` — specify search queries.

### Requirements
- Compiler with C++17 support
- CMake 3.10
- Google Test (bundled in the repository)
- Nlohmann/json library (bundled in the repository, can be updated manually)

### Configuration Structure
- `config.json` — list of file paths, search result limit.
- `requests.json` — search queries.
- `answers.json` — search results (auto-generated and cleared from previous output).
