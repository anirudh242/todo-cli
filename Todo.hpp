#pragma once
#include <string>
#include <vector>


enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

class Todo {
    public:
        Todo(int id, const std::string& title, Priority priority=Priority::LOW);
        std::string getTitle() const;
        void setTitle(const std::string& newTitle);
        int getId() const;
        bool getDone() const;
        void toggleDone();
        Priority getPriority() const;
        void setPriority(Priority newPriority);

    private:
        int id;
        std::string title;
        bool done;
        Priority priority;
};
