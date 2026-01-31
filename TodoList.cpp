#include "TodoList.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <optional>
#include <iomanip>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string YELLOW = "\033[33m";  // Medium
const std::string CYAN = "\033[36m";    // Low
const std::string MAGENTA = "\033[35m"; // High

TodoList::TodoList(const std::string& filename) : filename(filename) {
    load();
};

Priority intToPriority(int p) {
    if (p == 3) return Priority::HIGH;
    if (p == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

void TodoList::load() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, doneStr, priorityStr;
        
        std::getline(ss, idStr, '|');
        std::getline(ss, title, '|');
        std::getline(ss, doneStr, '|'); 
        std::getline(ss, priorityStr);  

        if (idStr.empty()) continue;

        int pVal = priorityStr.empty() ? 1 : std::stoi(priorityStr);
        Todo todo(std::stoi(idStr), title, intToPriority(pVal));
        
        if (doneStr == "1") todo.toggleDone();
        todos.push_back(todo);
    }
}

void TodoList::save() const {
    std::ofstream file(filename, std::ios::trunc);

    for (auto& todo : todos) {
        file << todo.getId()<< "|" 
        << todo.getTitle() << "|" 
        << todo.getDone() << "|"
        << static_cast<int>(todo.getPriority()) << "\n";
    }
}

void TodoList::add(const std::string& title, Priority priority) {
    int id = todos.empty() ? 1 : todos.back().getId() + 1;
    todos.emplace_back(id, title, priority);
    save();
}

void TodoList::remove(int id) {
    auto it = std::remove_if(
        todos.begin(),
        todos.end(),
        [&](Todo& todo) {
            return todo.getId() == id;
        }
    );

    if (it == todos.end()) {
        std::cout << "Todo not found" << std::endl;
        return;
    }

    todos.erase(it, todos.end());
    save();
}

void TodoList::list() const {
    if (todos.empty()) {
        std::cout << BOLD << "NO TODOS\n" << std::endl;
        return;
    }

    std::cout << std::left 
            << std::setw(5) << "ID"
            << std::setw(15) << "PRIORITY" // Increased width slightly for colors
            << std::setw(10) << "STATUS" 
            << "TITLE" 
            << std::endl;

    std::cout << std::string(45, '-') << std::endl;

    for (const auto& todo : todos) {
        std::string statusColor = todo.getDone() ? GREEN : RED;
        
        // Determine Priority String and Color
        std::string priorityStr;
        std::string priorityColor;

        switch(todo.getPriority()) {
            case Priority::HIGH:   
                priorityStr = "HIGH"; 
                priorityColor = MAGENTA; 
                break;
            case Priority::MEDIUM: 
                priorityStr = "MED"; 
                priorityColor = YELLOW; 
                break;
            case Priority::LOW:    
                priorityStr = "LOW"; 
                priorityColor = CYAN; 
                break;
        }

        std::cout << std::left
        << std::setw(5) << todo.getId()
        // Print priority with its color, then RESET before padding
        << priorityColor << BOLD << std::setw(15) << priorityStr << RESET 
        << statusColor << BOLD << std::setw(10) << (todo.getDone() ? "DONE" : "NOT DONE") << RESET
        << todo.getTitle()
        << std::endl;
    }
}

std::optional<std::string> TodoList::toggleTodo(int id) {
    auto it = std::find_if(todos.begin(), todos.end(), [id](const Todo& t) {
        return t.getId() == id;
    });
    
    if (it != todos.end()) {
        it->toggleDone();
        save();
        return it->getDone() ? "DONE" : "NOT DONE";
    }

    return std::nullopt;
}

bool TodoList::edit(int id, const std::string& newTitle) {
    auto it = std::find_if(todos.begin(), todos.end(), [id](const Todo& t) {
        return t.getId() == id;
    });
    if (it != todos.end()) {
        it->setTitle(newTitle);
        save();
        return true;
    }
    return false;
}

void TodoList::clearAll() {
    todos.clear();
    save();
}

void TodoList::clearComplete() {
    auto it = std::remove_if(
        todos.begin(),
        todos.end(),
        [](const Todo& todo) {
            return todo.getDone();
        }
    );
    if (it != todos.end()) {
        todos.erase(it, todos.end());
    }
    save();
}