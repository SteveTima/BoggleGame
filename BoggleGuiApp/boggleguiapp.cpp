#include "boggleguiapp.h"
#include "boggleDialog.h"


#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qtimezone.h>
#include <qplaintextedit.h>


using namespace std;

BoggleGuiApp::BoggleGuiApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	initGame();
}

void BoggleGuiApp::initGame()
{
	if (!readGameWordsDictionary())
	{
		QMessageBox::critical(this, tr("Error"), tr("Failed to open  the dictionary-file."));
		return;
	}

	// init gui-interface
	initGameInterface();

	// init class interface
	m_is_playing = false;
	m_current_player = nullptr;
	m_nbrOfPlayer = 0;
	m_nextPlayerID = 0;
	m_game_time = DEFAULT_GAME_TIME;
}

void BoggleGuiApp::initGameInterface()
{
	//enabled
	ui.actionGame_Dictionary->setEnabled(true);
	ui.actionGame_Instructions->setEnabled(true);
	ui.actionGame_time->setEnabled(true);
	ui.actionNew_game->setEnabled(true);

	ui.defaultGameTime->setText(QString::number(DEFAULT_GAME_TIME));

	//disabled
	ui.centralWidget->setEnabled(false);
	ui.defaultGameTime->setEnabled(false);
	ui.NbrOfPlayer->setEnabled(false);
	ui.listOfPlayer->setEnabled(false);
	ui.currentPlayer->setEnabled(false);
	ui.gameChrono->setEnabled(false);
	ui.StartButton->setEnabled(false);
	ui.stopButton->setEnabled(false);
	ui.diceTable->setEnabled(false);
	ui.playerEntry->setEnabled(false);
	ui.saveButton->setEnabled(false);
	ui.listOfEntries->setEnabled(false);

	// signal-slots
	callBacks();
}

void BoggleGuiApp::callBacks()
{
	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &BoggleGuiApp::UpdateCountDown);
	connect(ui.actionNew_game, &QAction::triggered, this, &BoggleGuiApp::startNewGame);
	connect(ui.actionGame_time, &QAction::triggered, this, &BoggleGuiApp::setGameTime);
	connect(ui.actionGame_Instructions, &QAction::triggered, this, &BoggleGuiApp::displayGameHelp);
	connect(ui.actionGame_Dictionary, &QAction::triggered, this, &BoggleGuiApp::displayGameDictionary);
	connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(startPlaying()));
	connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(stopPlaying()));
	connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
	connect(ui.diceTable, SIGNAL(cellClicked(int, int)), this, SLOT(selectDice(int, int)));
}

bool BoggleGuiApp::readGameWordsDictionary()
{
	string wordsDictPath = getWordsDictDatafilePath();
	m_wordsDict = createEmptyDictionary();
	return fillDictionary(wordsDictPath, m_wordsDict);
}


void BoggleGuiApp::startNewGame()
{
	// enabled
	ui.centralWidget->setEnabled(true);

	if (!updateGameConfig())
	{
		QMessageBox::critical(this, tr("Error"), tr("The number of player given is not valid."));
		return;
	}
	updateListOfPlayers();
	loadPartyGame();
	// clear the windows, the game is finisch
}

bool BoggleGuiApp::updateGameConfig()
{
	ui.defaultGameTime->setEnabled(true);
	ui.NbrOfPlayer->setEnabled(true);

	/* get the number of players */
	if (!setValidNbrOfPlayer())
	{
		return false; 
	}

	/* display nbr of player and game time */
	ui.NbrOfPlayer->setText(QString::number(m_nbrOfPlayer));
	ui.defaultGameTime->setText(QString::number(m_game_time));
	return true;
}


void BoggleGuiApp::updateListOfPlayers()
{
	ui.listOfPlayer->setEnabled(true);

	/* add all player names */
	for (int i = 0; i < m_nbrOfPlayer; i++)
	{
		QString newPlayerName;
		Player newPlayer = Player();
		do
		{
			newPlayerName = getPlayerName(i + 1);

		} while (nameExists(newPlayerName));
		ui.listOfPlayer->addItem(newPlayerName);
		m_gamePlayers.push_back(Player(newPlayerName.toStdString()));
	}
}

void BoggleGuiApp::goToNextPlayer()
{
	m_current_player = &(m_gamePlayers[m_nextPlayerID]);
	ui.currentPlayer->setText(QString::fromStdString(m_current_player->name));
	ui.gameChrono->setText("00:00");
	m_time = new QTime(0, m_game_time, 0);
	if (isReadyToPlay(QString::fromStdString(m_current_player->name)))
	{
		ui.StartButton->setEnabled(true);
		m_is_playing = true;
	}
}

void BoggleGuiApp::loadPartyGame()
{
	ui.currentPlayer->setEnabled(true);
	ui.gameChrono->setEnabled(true);
	goToNextPlayer();
}

void BoggleGuiApp::showGameResults()
{
	if (m_nbrOfPlayer == 1)
	{
		QString text = generateDefaultGameResult();
		BoggleDialog* gameInstruction = new BoggleDialog("Game Results", text, this);
		gameInstruction->exec();
	}
	else
	{
		Player winner = findWinner();
		QString text = generateGameResultWithWinner(winner);
		BoggleDialog* gameInstruction = new BoggleDialog("Game Results", text, this);
		gameInstruction->exec();
	}
}

QString BoggleGuiApp::generateDefaultGameResult()
{
	QString text;
	text += "================================\n\n";
	text += ">>> " + QString::fromStdString(m_gamePlayers[0].name) + ": You got " + QString::number(m_gamePlayers[0].score) +" Point in this game.\n\n" ;
	text += "\n\n\n======   THANKS FOR PLAYING   =====";
	return text;
}

QString BoggleGuiApp::generateGameResultWithWinner(Player winner)
{
	QString text;
	text += "================================\n\n";
	if (winner.score == 0)
	{
		text += ">>> NO WINNER: Nobody won the game.\n\n";
	}
	else
	{
		text += ">>> WINNER: " + QString::fromStdString(winner.name) +  " won the game.\n\n";
	}
	text += "================================\n\n";

	// display result of all players
	for (int i = 0; i < m_nbrOfPlayer; i++)
	{
		text += " - " + QString::fromStdString(m_gamePlayers[i].name) + ": " + QString::number(m_gamePlayers[i].score) + " Point\n";
	}

	text += "\n\n\n =====   THANKS FOR PLAYING   =====";
	return text;
}

Player BoggleGuiApp::findWinner()
{
	Player winner = m_gamePlayers[0];
	for (int i = 1; i < m_nbrOfPlayer; i++)
	{
		if (m_gamePlayers[i].score > winner.score)
		{
			winner = m_gamePlayers[i];
		}
	}
	return winner;
}

/*#########################################################################################*/
/*#########################  SLOTS #########################*/


void BoggleGuiApp::startPlaying()
{
	ui.StartButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.diceTable->setEnabled(true);
	ui.playerEntry->setEnabled(true);
	ui.saveButton->setEnabled(true);
	ui.listOfEntries->setEnabled(true);

	m_newMap = generateListOfDiesValues();
	showGameBoard(m_newMap);
	m_timer->start(1000); // in ms
}

void BoggleGuiApp::showGameBoard(vector<Dice> const& allDies)
{
	for (vector<Dice>::const_iterator it = allDies.begin(); it != allDies.end(); ++it)
	{
		auto item = new QTableWidgetItem(QString((*it).value));
		item->setTextAlignment(Qt::AlignCenter);
		ui.diceTable->setItem((*it).row, (*it).column, item);
	}
}

void BoggleGuiApp::stopPlaying()
{
	stopPlayerGame(true);
	selectNextStep();
}

void BoggleGuiApp::UpdateCountDown()
{
	if ((m_time->minute() == 0) && (m_time->second() == 0))
	{
		stopPlayerGame(false);
		selectNextStep();
	}
	else
	{
		*m_time = m_time->addSecs(-1);
		ui.gameChrono->setText(m_time->toString("mm : ss"));
	}
}

void BoggleGuiApp::selectNextStep()
{
	m_is_playing = false;
	m_newMap.clear();
	m_current_player->score = getScore(m_current_player->playerWords, m_wordsDict);
	m_nextPlayerID++;
	if (m_nextPlayerID < m_nbrOfPlayer)
	{
		goToNextPlayer();
	}
	else
	{
		showGameResults();
		resetGame();
	}
}

void BoggleGuiApp::resetGame()
{
	// reset gui-interface
	ui.NbrOfPlayer->clear();
	ui.defaultGameTime->clear();
	ui.listOfPlayer->clear();
	ui.NbrOfPlayer->setEnabled(false);
	ui.defaultGameTime->setEnabled(false);
	ui.listOfPlayer->setEnabled(false);
	ui.currentPlayer->setEnabled(false);
	ui.gameChrono->setEnabled(false);

	// reset class-interface
	m_nbrOfPlayer = 0;
	m_gamePlayers.clear();
	bool m_is_playing = false;
	m_current_player = nullptr;
	m_nextPlayerID = 0;
}

void BoggleGuiApp::stopPlayerGame(bool stopButtonClicked)
{
	stopTimer();
	if (stopButtonClicked)
	{
		// insert dialog-info with ok
		// QMessageBox::information(this, tr("Stop Party"), tr("You stop the party."));
	}
	else
	{
		// insert dialog-info with ok
		// QMessageBox::information(this, tr("Stop Party"), tr("The game time is finisch."));
	}

	ui.diceTable->clear();
	ui.playerEntry->clear();
	ui.listOfEntries->clear();
	ui.currentPlayer->clear();
	ui.gameChrono->clear();

	ui.StartButton->setEnabled(false);
	ui.stopButton->setEnabled(false);
	ui.saveButton->setEnabled(false);
	ui.diceTable->setEnabled(false);
	ui.playerEntry->setEnabled(false);
	ui.listOfEntries->setEnabled(false);
}


void BoggleGuiApp::selectDice(int row, int col)
{
	// get the dice struct
	unsigned int diceID = (row * NBR_OF_ROWS) + col;
	Dice diceSelected = m_newMap[diceID];
	m_playerInput.push_back(diceSelected);

	// display dice-character
	if (ui.playerEntry->text().isEmpty())
	{
		ui.playerEntry->setText(QString(diceSelected.value));
	}
	else
	{
		ui.playerEntry->setText(ui.playerEntry->text() + " - " + QString(diceSelected.value));
	}
}

void BoggleGuiApp::saveButtonClicked()
{
	string strValue = makeStringFromDies(m_playerInput);
	InputString customString = InputString(m_playerInput, strValue);
	if (isWordValid(customString))
	{
		ui.listOfEntries->addItem(QString::fromStdString(strValue));
		(m_current_player->playerWords).push_back(customString);
	}
	else
	{
		//QString notValidMessage = QString("<span style=\" color:#ff0000; \">%1</span>").arg("  >>>  not valid");
		QString notValidMessage = "  >>>  not valid";
		ui.listOfEntries->addItem(QString::fromStdString(strValue) + notValidMessage);
	}
	m_playerInput.clear();
	ui.playerEntry->clear();
}


void BoggleGuiApp::stopTimer()
{
	ui.gameChrono->setText(m_time->toString("mm : ss"));
	m_timer->stop();
}


/*#########################################################################################*/


/*######################### HELP-FUNCTIONS #########################*/


bool BoggleGuiApp::isReadyToPlay(QString playerName)
{
	QString questionLabel = playerName + QString(", did you want to continue playing ?");
	QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Need Confirmation"), questionLabel, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (answer == QMessageBox::Yes)
	{
		return true;
	}
	return false;
}

bool BoggleGuiApp::nameExists(QString newName)
{
	std::string currentName = newName.toStdString();
	int const actualPlayerLen = m_gamePlayers.size();
	for (int i = 0; i < actualPlayerLen; i++)
	{
		if (m_gamePlayers[i].name == currentName)
		{
			QMessageBox::warning(this, tr("Already exists"), tr("A player with the same name already exists. Please enter a different name."));
			return  true;
		}
	}
	return  false;
}

QString BoggleGuiApp::getPlayerName(int const playerNbr)
{
	bool ok;
	QString inputLabel = QString("Enter the name of player ") + QString::number(playerNbr) + QString(" :");
	QString text = QInputDialog::getText(this, tr("Set Player Name"), inputLabel, QLineEdit::Normal, QString(), &ok);
	while (!(ok && (!text.isEmpty())))
	{
		QMessageBox::warning(this, tr("Invalid"), tr("A player without name is not authorized."));
		text = QInputDialog::getText(this, tr("Set Player Name"), inputLabel, QLineEdit::Normal, QString(), &ok);
	}
	return text;
}

void BoggleGuiApp::setGameTime()
{
	bool ok;
	const int invalidValue = -1;
	const int minVal = 1;
	const int maxVal = 100;
	int gameTime = QInputDialog::getInt(this, tr("Set Game Time"), tr("How many minutes of play ?"), invalidValue, minVal, maxVal, 1, &ok);

	if (ok)
	{
		if (gameTime == invalidValue)
		{
			QMessageBox::information(this, tr("Invalid"), tr("The time value is out of range [1-100]"));
		}
		else
		{
			m_game_time = gameTime;
		}
	}
}

bool BoggleGuiApp::setValidNbrOfPlayer()
{
	bool ok;
	const int invalidValue = -1;
	const int minPlayer = 1;
	const int maxPlayer = 50;
	int nbrOfPlayer = QInputDialog::getInt(this, tr("Number of players"), tr("Enter the number of players of this new game"), invalidValue, minPlayer, maxPlayer, 1, &ok);
	if (ok)
	{
		if (nbrOfPlayer == invalidValue)
		{
			QMessageBox::information(this, tr("Invalid"), tr("The value is out of range [1-50]"));
		}
		else
		{
			m_nbrOfPlayer = nbrOfPlayer;
			return true;
		}
	}
	return false;
}

void BoggleGuiApp::displayGameHelp()
{
	QString text = generateTextHelp();
	BoggleDialog* gameInstruction = new BoggleDialog("Game Instructions", text, this);
	gameInstruction->exec();
}

void BoggleGuiApp::displayGameDictionary()
{
	QMessageBox::information(this, tr("Oups Sorry!"), tr("function not yet available."));
	/*QString text = generateTextDictionary();
	BoggleDialog* wordsDictionary = new BoggleDialog("Game Dictionary", text, this);
	wordsDictionary->exec();*/
}

/*#########################################################################################*/




QString BoggleGuiApp::generateTextDictionary()
{
	QString words;
	for (map<char, vector<string>>::const_iterator it = m_wordsDict.begin(); it != m_wordsDict.end(); ++it)
	{

		words += it->first;
		words += ":\n";
		int listLenght = (it->second).size();
		int i = 0;
		for (vector<string>::const_iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
		{
			i++;
			words += QString::fromStdString(*it2);
			if (i == listLenght)
			{
				words += ".\n";
			}
			else
			{
				words += ", ";
				if ((i % 5) == 0) // pr afficher 5 mots par ligne
				{
					words += "\n";
				}
			}
		}
		words += "\n\n================================\n\n";
	}
	return words;
}

QString BoggleGuiApp::generateTextHelp()
{
	QString helpText = "W E L C O M E   T O  T H E  G A M E ** B O G G L E **\n\n \
		The Help is comming soon \n \
		...\n";
	return helpText;
}

