#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_boggleguiapp.h"
#include "../BoggleLIB/boggleConfig.h"
#include "../BoggleLIB/boggleValidation.h"

#include <qtimer.h>


#define DEFAULT_GAME_TIME 2

class BoggleGuiApp : public QMainWindow
{
    Q_OBJECT

public:
    BoggleGuiApp(QWidget *parent = Q_NULLPTR);
	void initGame();
	void callBacks();
	bool setValidNbrOfPlayer();

public slots:
	void startNewGame();
	void setGameTime(); // config game time
	void displayGameHelp();
	void displayGameDictionary();
	void UpdateCountDown(); // timer
	void startPlaying(); 
	void stopPlaying();
	void saveButtonClicked();
	void selectDice(int row, int col);

private: // Functions
	QString getPlayerName(int const playerNbr);
	bool nameExists(QString newName);
	bool isReadyToPlay(QString playerName);
	void showGameBoard(std::vector<Dice> const& allDies);
	void stopTimer();
	void stopPlayerGame(bool stopButtonClicked);
	bool readGameWordsDictionary();
	void initGameInterface();
	bool updateGameConfig();
	void updateListOfPlayers();
	void loadPartyGame();
	QString generateTextDictionary();
	QString generateTextHelp();
	void showGameResults();
	QString generateDefaultGameResult();
	QString generateGameResultWithWinner(Player winner);
	Player findWinner();
	void goToNextPlayer();
	void selectNextStep();
	void resetGame();


private:
	Ui::BoggleGuiAppClass ui;
	int m_nbrOfPlayer;
	int m_game_time;
	std::vector<Player> m_gamePlayers;
	QTimer* m_timer;
	QTime* m_time;
	bool m_is_playing;
	Player* m_current_player;
	int m_nextPlayerID;
	std::map<char, std::vector<std::string>> m_wordsDict;

	std::vector<Dice> m_playerInput;
	std::vector<Dice> m_newMap;
};
