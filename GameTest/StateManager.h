//------------------------------------------------------------------------
//StateManager.h
//------------------------------------------------------------------------
#ifndef STATEMANAGER_H
#define STATEMANAGER_H
//------------------------------------------------------------------------

enum class GameStates
{
	INTRODUCTION,
	PLAYING,
	PAUSE,
	GAMEOVER,
	CLEAR
};

class StateManager
{
	GameStates m_state;
	size_t m_life;
	size_t m_gold;

public:
	StateManager() : m_state(GameStates::INTRODUCTION), m_gold(INITIAL_GOLD), m_life(INITIAL_LIFE) {}

	void setState(GameStates state) { m_state = state; }
	GameStates getState() { return m_state; }

	size_t GetGold() { return m_gold; }
	void GoldReduction(size_t cost) { m_gold -= cost; }
	void GoldIncrease(size_t reward) { m_gold += reward; }

	size_t GetLife() { return m_life; }
	void LifeReduction() { m_life--; if (m_life == 0) m_state = GameStates::GAMEOVER; }

	void reset() { m_gold = INITIAL_GOLD; m_life = INITIAL_LIFE; m_state = GameStates::INTRODUCTION; }
};

#endif // GAMESTATE_H
