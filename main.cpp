#include "CLI11.hpp"
#include "Todo.hpp" 
#include "TodoList.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char const **argv)
{
    CLI::App app;
    const char* homeDir = std::getenv("HOME");
    std::string filename = "todolist.txt";
    if (homeDir) {
        // We make it a hidden file with the dot (.) prefix so it doesn't clutter your home folder
        filename = std::string(homeDir) + "/.todolist.txt";
    }
    TodoList todoList(filename);
    // NEW TODO
    auto newCmd = app.add_subcommand("new", "Create new todo item");
    std::string newTitle;
    int priorityInt = 1; 
    newCmd->add_option("title", newTitle, "Title of the todo")->required();
    newCmd->add_option("-p,--priority", priorityInt, "Priority (1=Low, 2=Med, 3=High)");
    newCmd->callback([&]() {
        Priority p = Priority::LOW;
        if (priorityInt == 3) p = Priority::HIGH;
        else if (priorityInt == 2) p = Priority::MEDIUM;
        todoList.add(newTitle, p);
        std::cout << "Created todo: " << newTitle << " with priority " << priorityInt << std::endl;
    });
    
    // DELETE TODO
    auto deleteCmd = app.add_subcommand("delete", "Delete specific todo item");
    int deleteTodoID; 
    deleteCmd->add_option("ID", deleteTodoID, "ID of the todo to delete")->required();
    deleteCmd->callback([&]() {
        todoList.remove(deleteTodoID);
        std::cout << "Delete todo " << deleteTodoID << std::endl;
    });

    // LIST ALL TODOS
    auto listCmd = app.add_subcommand("list", "List all todos");
    listCmd->callback([&]() {
       todoList.list(); 
    });
   
    // TOGGLE TODO STATUS
    auto toggleCmd = app.add_subcommand("toggle", "Toggle todo status");
    int toggleTodoID;
    toggleCmd->add_option("ID", toggleTodoID, "ID of todo to toggle")->required();
    toggleCmd->callback([&]() {
        auto result = todoList.toggleTodo(toggleTodoID);
        if (result) {
            std::cout << "Todo " << toggleTodoID << " is now marked as " << *result << std::endl;
        } else {
            std::cout << "Could not find given todo ID" << std::endl;
        }
    });

    // EDIT TODO
    auto editCmd = app.add_subcommand("edit", "Edit todo status");
    int editTodoID;
    std::string editTodoTitle;
    editCmd->add_option("ID", editTodoID, "ID of todo to edit")->required();
    editCmd->add_option("Title", editTodoTitle, "New title of todo to edit")->required();
    editCmd->callback([&]() {
        if (todoList.edit(editTodoID, editTodoTitle)) {
            std::cout << "Updated todo " << editTodoID << " to: " << editTodoTitle << std::endl;
        } else {
            std::cout << "Could not find todo with ID: " << editTodoID << std::endl;
        }
    });

    // CLEAR ALL TODOS
    auto clearCmd = app.add_subcommand("clear", "Clear all completed todos");
    bool clearAll = false;
    clearCmd->add_flag("-a, --all", clearAll, "Flag to set whether to all todos including incomplete");
    clearCmd->callback([&]() {
        if (clearAll) {
            todoList.clearAll();
            std::cout << "Cleared all todos" << std::endl;
        } else {
            todoList.clearComplete();
            std::cout << "Cleared all completed todos" << std::endl;
        }
    });

    // CHANGE PRIORITY
    auto priorityCmd = app.add_subcommand("priority", "Change priority of a todo");
    int pID;
    int pVal;
    priorityCmd->add_option("ID", pID, "ID of the todo")->required();
    priorityCmd->add_option("Level", pVal, "New Priority (1=Low, 2=Med, 3=High)")->required();
    
    priorityCmd->callback([&]() {
        Priority p = Priority::LOW;
        if (pVal == 3) p = Priority::HIGH;
        else if (pVal == 2) p = Priority::MEDIUM;

        if (todoList.setPriority(pID, p)) {
            std::cout << "Updated priority for todo " << pID << " to " << pVal << std::endl;
        } else {
             std::cout << "Could not find todo with ID " << pID << std::endl;
        }
    });

    app.require_subcommand(1);
    CLI11_PARSE(app, argc, argv);

    return 0;
}
