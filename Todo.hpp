#pragma once
#include <string>
#include <vector>

class Todo {
    public:
        Todo(int id, const std::string& title);
        std::string getTitle() const;
        int getId() const;
        bool getDone() const;
        void toggleDone();

    private:
        int id;
        std::string title;
        bool done;

};

std::vector<Todo> listTodos(const std::string& filename);
