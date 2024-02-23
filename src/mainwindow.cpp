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


#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent, Qt::WFlags fl)
		: QMainWindow(parent, fl), Ui::MainWindow() {
	setupUi(this);
	QObject::connect(pbEsconder,SIGNAL(clicked()),this,SLOT(pbEsconderClick()));
	QObject::connect(pbSair,SIGNAL(clicked()),this,SLOT(pbSairClick()));
	QObject::connect(leImagem,SIGNAL(lostFocus()),this,SLOT(leImagemLostFocus()));
	QObject::connect(leArquivo,SIGNAL(lostFocus()),this,SLOT(leArquivoLostFocus()));
	QObject::connect(tbImagem,SIGNAL(clicked()),this,SLOT(escolherArquivo()));
	QObject::connect(tbArquivo,SIGNAL(clicked()),this,SLOT(escolherArquivo()));
	QObject::connect(tbNovaImagem,SIGNAL(clicked()),this,SLOT(escolherDiretorio()));
	QObject::connect(sbStatusBar,SIGNAL(messageChanged(QString)),this,SLOT(mudarMensagem(const QString&)));
	QObject::connect(actionSobreKasludo,SIGNAL(triggered(bool)),this,SLOT(sobreKasludoClick(bool)));
	QObject::connect(actionSobreQt,SIGNAL(triggered(bool)),this,SLOT(aboutQtClick(bool)));
	QObject::connect(tbImagemExtrair, SIGNAL(clicked()),this,SLOT(escolherArquivo()));
	QObject::connect(pbExtrair,SIGNAL(clicked()),this,SLOT(extrairClicked()));
	scene=NULL; 
	sbStatusBar->showMessage("Pronto.");
	canCalculate = false;
	pbSize->setValue(0);
}

MainWindow::~MainWindow() {
	if (scene != NULL) 
		delete scene;
}

/*$SPECIALIZATION$*/

void MainWindow::pbEsconderClick() {
	if (canCalculate) {
		if (leImagem->text() != leNovaImagem->text()) {
			QFile *f = new QFile(leNovaImagem->text());
			if (!f->exists()) {
				char imagem[300], arquivo[300], novaImagem[300];
				strcpy(imagem, leImagem->text().toUtf8().data());
				strcpy(arquivo, leArquivo->text().toUtf8().data());
				strcpy(novaImagem, leNovaImagem->text().toUtf8().data());
				kasludolib::esconder(arquivo, imagem, novaImagem);
				carregarImage2(leNovaImagem->text());
				sbStatusBar->showMessage(tr("Arquivo oculto com sucesso."));
			} else {
				sbStatusBar->showMessage(tr("Arquivo de nova imagem já existe."));
			}
		} else {
			sbStatusBar->showMessage(tr("Arquivo de imagem e de nova imagem idênticos."));
		}
	} else {
		sbStatusBar->showMessage(tr("Não é possível efetuar pedido."));
	}
}

void MainWindow::leImagemLostFocus() {
	if (leNovaImagem->text().isEmpty()) {
		leNovaImagem->setText(leImagem->text());
	}
	carregarImage1(leImagem->text());
	calcSize();
}

void MainWindow::escolherArquivo() {
	QString arquivo = QFileDialog::getOpenFileName(this, "Escoha uma imagem","/home/",(this->sender()->objectName().compare("tbImagem")) || (this->sender()->objectName().compare("tbImagemExtrair")) ==0?tr("Arquivos BMP (*.bmp)") :tr("Todos os Arquivos (*)"));
	if (this->sender()->objectName().compare("tbImagem") == 0) {
		leImagem->setText(arquivo);
		carregarImage1(arquivo);
		calcSize();
	} else if (this->sender()->objectName().compare("tbArquivo") == 0) {
		leArquivo->setText(arquivo);
		calcSize();
	} else if (this->sender()->objectName().compare("tbImagemExtrair") == 0) {
		leImagemExtrair->setText(arquivo);
		QGraphicsScene *scene = new QGraphicsScene();
		QPixmap lPixmap;
		lPixmap.load(arquivo);
		scene->addPixmap(lPixmap);
		gvImagemExtrair->setScene(scene);
	}
}

void MainWindow::escolherDiretorio() {
	QString arquivo = QFileDialog::getSaveFileName(this,"","");
	leNovaImagem->setText(arquivo);
}

void MainWindow::pbSairClick() {
	close();
}

void MainWindow::carregarImage2(QString arquivo) {
	QGraphicsScene *scene = new QGraphicsScene();
	QPixmap lPixmap;
	lPixmap.load(arquivo);
	scene->addPixmap(lPixmap);
	gvNovaImagem->setScene(scene);
}

void MainWindow::carregarImage1(QString arquivo) {
	if (!arquivo.isEmpty()) {
		if (scene != NULL)
			delete scene;
		scene = new QGraphicsScene();
		QPixmap lPixmap;
		lPixmap.load(arquivo);
		scene->addPixmap(lPixmap);
		gvImagem->setScene(scene);
	}
}

void MainWindow::mudarMensagem(const QString & msg) {
	if (msg.isNull()) {
		sbStatusBar->showMessage("Pronto.");
	}
}

void MainWindow::sobreKasludoClick(bool Checked) {
	aboutKasludo *a = new aboutKasludo(this);
	a->exec();
	delete a;
}


/*!
    \fn MainWindow::calcSize()
 */
void MainWindow::calcSize() {
	qint64 iSize, fSize;
	canCalculate = false;
	pbSize->setValue(0);
	if (!leImagem->text().isEmpty() && !leArquivo->text().isEmpty()) {
		QFile *iFile = new QFile(leImagem->text()), *fFile = new QFile(leArquivo->text());
		if (!iFile->exists())
			sbStatusBar->showMessage(tr("Imagem não existe."));
		else
			if (!fFile->exists())
				sbStatusBar->showMessage(tr("File não existe."));
			else
				if (iFile->size() < fFile->size() *4+70) {
					sbStatusBar->showMessage(tr("Arquivos com tamanhos incompatíveis."));
					pbSize->setValue(100);
				} else {
					sbStatusBar->showMessage(tr("Pronto para calcular..."));
					canCalculate = true;
					pbSize->setValue(((fFile->size() *4+70) *100/iFile->size()));
				}
	} else
		if (!leImagem->text().isEmpty()) {
			QFile *f = new QFile(leImagem->text());
			if (f->exists()) {
				iSize=f->size();
				fSize= (f->size()-70) /4;
				sbStatusBar->showMessage(tr("Imagem de %1 bytes pode esconder um arquivo de %2 bytes ~ %3 kb.").arg(iSize).arg(fSize).arg(fSize/1024));
			} else {
				sbStatusBar->showMessage("Arquivo Inválido.");
			}
			delete f;
		} else
			if (!leArquivo->text().isEmpty()) {
				QFile *f = new QFile(leArquivo->text());
				if (f->exists()) {
					fSize=f->size();
					iSize=f->size() *4+70;
					sbStatusBar->showMessage(tr("Para esconder arquivo de %1 bytes é necessário uma imagem de %2 bytes ~ %3kb.").arg(fSize).arg(iSize).arg(iSize/1024,'f',2));
				} else {
					sbStatusBar->showMessage("Arquivo Inválido.");
				}
				delete f;
			}
}


/*!
    \fn MainWindow::leArquivoLostFocus()
 */
void MainWindow::leArquivoLostFocus() {
	calcSize();
}


/*!
    \fn MainWindow::aboutQtClick(const bool checked)
 */
void MainWindow::aboutQtClick(const bool checked) {
	QMessageBox::aboutQt(this,tr("Kaŝludo"));
}


/*!
    \fn MainWindow::extrairClicked()
 */
void MainWindow::extrairClicked() {
	char imagem[300], arquivo[300];
	strcpy(imagem, leImagemExtrair->text().toUtf8().data());
	kasludolib::mostrar(imagem,arquivo);
	leArquivoSaida->setText(QString(arquivo).toUtf8());
}
