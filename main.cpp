#include "CLI11.hpp"
#include "Todo.hpp" 
#include "TodoList.hpp"
#include <iostream>

int main(int argc, char const **argv)
{
    CLI::App app;
    TodoList todoList("todolist.txt");

    // NEW TODO
    auto newCmd = app.add_subcommand("new", "Create new todo item");
    std::string newTitle;
    newCmd->add_option("title", newTitle, "Title of the todo")->required();
    newCmd->callback([&]() {
        todoList.add(newTitle);
        std::cout << "Created todo: " << newTitle << std::endl;
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
   
    // auto getByIDCmd = app.add_subcommand("get", "Get specific todo by ID");
    // int getTodoID;
    // getByIDCmd->add_option("ID", getTodoID, "ID of the todo to get")->required();
    // getByIDCmd->callback([&]() {
    //     
    // });
    
    app.require_subcommand(1);
    CLI11_PARSE(app, argc, argv);

    return 0;
}
