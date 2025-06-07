#pragma once

class StateM;
class Player;

/**
 * @class StateMachine
 * @brief Manages the player's current state and transitions between different states.
 *
 * The StateMachine handles runtime switching of player states (such as movement, attacking, etc.)
 * by holding a pointer to the current state and allowing controlled transitions.
 */
class StateMachine {
private:
    StateM* currentState = nullptr; ///< Pointer to the current active state.

public:
    /**
     * @brief Default constructor.
     */
    StateMachine();
    /**
     * @brief Destructor.
     */
    ~StateMachine();
    /**
     * @brief Changes the current state to a new state.
     *
     * @param newState Pointer to the new state to transition into.
     * @param player Pointer to the player instance.
     * @param override If true, forces transition even if the current state is the same.
     */
    void changeState(StateM* newState, Player* player, bool override = false);
    /**
     * @brief Updates the current state.
     *
     * @param player Pointer to the player.
     * @param dt Delta time since last frame.
     */
    void update(Player* player, float dt);
    /**
     * @brief Returns the current active state.
     *
     * @return Pointer to the current state.
     */
    StateM* getCurrentState() const;
};