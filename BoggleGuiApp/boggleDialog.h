#pragma once

#include <QtWidgets>

class BoggleDialog : public QDialog
{
public:
	BoggleDialog(QString const& dialogTitle, QString const& text, QWidget *parent);
private:
	QTextEdit *dialogText;
	QPushButton *dialogButton;
};
