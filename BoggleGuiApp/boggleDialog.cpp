#include "boggleDialog.h"

BoggleDialog::BoggleDialog(QString const& dialogTitle, QString const& text, QWidget *parent = 0) :
	QDialog(parent)
{
	// init text
	dialogText = new QTextEdit();
	dialogText->setPlainText(text);
	dialogText->setReadOnly(true);
	dialogText->setFont(QFont("Courier"));
	dialogText->setLineWrapMode(QTextEdit::NoWrap);

	// init button
	dialogButton = new QPushButton("Close");

	// add layout
	QVBoxLayout *layoutPrincipal = new QVBoxLayout;
	layoutPrincipal->addWidget(dialogText);
	layoutPrincipal->addWidget(dialogButton);

	// config dialog window
	resize(450, 500);
	setLayout(layoutPrincipal);
	setWindowTitle(dialogTitle);

	// signal-slot connection
	connect(dialogButton, SIGNAL(clicked()), this, SLOT(accept()));
}
