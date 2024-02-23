/***************************************************************************
 *   Copyright (C) 2007 by Rodrigo Bronzelle   *
 *   bronzelle@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include "ui_main.h"
#include "kasludolib.h"
#include "aboutkasludo.h"
#include <iostream>
#include <string.h>
#include <qmessagebox.h>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
		Q_OBJECT

	public:
		MainWindow ( QWidget* parent = 0, Qt::WFlags fl = 0 );
		~MainWindow();
		/*$PUBLIC_FUNCTIONS$*/

	public slots:
		void pbEsconderClick();
		void pbSairClick();
		void leImagemLostFocus();
		void escolherArquivo();
		void escolherDiretorio();
		void mudarMensagem ( const QString &msg );
		void sobreKasludoClick ( bool Checked );
		void leArquivoLostFocus();
		void aboutQtClick ( const bool checked );
		/*$PUBLIC_SLOTS$*/

	protected:
		void carregarImage1 ( QString arquivo );
		void carregarImage2 ( QString arquivo );
		void calcSize();
		QGraphicsScene *scene;
		bool canCalculate;
		/*$PROTECTED_FUNCTIONS$*/

	protected slots:
		/*$PROTECTED_SLOTS$*/

private slots:
    void extrairClicked();
};

#endif

