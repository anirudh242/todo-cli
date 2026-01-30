#pragma once
#include "Todo.hpp" 
#include <vector>
#include <optional>

class TodoList {
    public:
        explicit TodoList(const std::string& filename);
        void add(const std::string& title);
        void list() const;
        void remove(int id);
        bool edit(int id, const std::string& newTitle);
        std::optional<std::string> toggleTodo(int id);

    private:
        void load();
        void save() const; 

        std::vector<Todo> todos;
        std::string filename;
};