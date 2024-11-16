#ifndef STATE_H
#define STATE_H

class StateStack;

enum class StateName {
	Play_State,

	Player_Idle_State,
};

class State {
    friend StateStack;

    public:
	State();
	virtual ~State() {};

	// i'd rather use templates or a struct but i cant be fucked to do that
    virtual void enter(void* params) = 0; // TODO: Find way to add enter params to method && Implement in StateMachine.h
    virtual void exit() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

	virtual StateName name() = 0;

    private:
    StateName m_name;
};

#endif
