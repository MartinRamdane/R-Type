/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** Engine.hpp
*/

#ifndef Engine
    #define Engine

class Engine {
    public:
        Engine();
        ~Engine();

        void init();
        void update();
        void drawAll();
        void getInput();
        void gameLoop();

    protected:
    private:
};

#endif /* !Engine */
