//------------------------------------------------------------------------
//InputManager.h
//------------------------------------------------------------------------
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_h
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Responsible for handling player input events
//------------------------------------------------------------------------
class InputManager
{
	StateManager* m_stateManager;
	ItemManager* m_itemManager;
	EnemySpawner* m_enemySpawner;

public:
	InputManager(StateManager*, ItemManager*, EnemySpawner*);

	//------------------------------------------------------------------------
	// Call the corresponding function according to the state of the game
	//------------------------------------------------------------------------
	void Update(float);

	void introUpdate();
	void playingUpdate();
	void pauseUpdate();
	void gameoverUpdate();
	void clearupdate();
};
#endif // !INPUTMANAGER_H
