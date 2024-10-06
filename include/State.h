#ifndef STATE_H
#define STATE_H

class StateMachine;

class State {
    friend StateMachine;

    public:
    virtual void enter() = 0; // TODO: Find way to add enter params to method && Implement in StateMachine.h
    virtual void exit() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    private:
    char* m_name = nullptr;
};

#endif
