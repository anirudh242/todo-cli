#include "TodoList.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

TodoList::TodoList(const std::string& filename) : filename(filename) {
    load();
};

void TodoList::load() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, doneStr;
        std::getline(ss, idStr, '|');
        std::getline(ss, title, '|');
        std::getline(ss, doneStr);
        Todo todo(std::stoi(idStr), title);
        if (doneStr == "1") todo.toggleDone();
        todos.push_back(todo);
    }
}

void TodoList::save() const {
    std::ofstream file(filename, std::ios::trunc);

    for (auto& todo : todos) {
        file << todo.getId()<< "|" << todo.getTitle() << "|" << todo.getDone() << "\n";
    }
}

void TodoList::add(const std::string& title) {
    int id = todos.empty() ? 1 : todos.back().getId() + 1;
    todos.emplace_back(id, title);
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
        std::cout << "NO TODOS\n" << std::endl;
        return;
    }

    for (const auto& todo : todos) {
        std::cout << todo.getId() << "\t" << todo.getTitle() << "\t" << todo.getDone() << "\n";
    }
}
