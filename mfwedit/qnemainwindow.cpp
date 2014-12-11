/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qnemainwindow.h"
#include "ui_qnemainwindow.h"

#include "qneblock.h"
#include "qneconnection.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"



QNEMainWindow::QNEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QNEMainWindow)
{
    ui->setupUi(this);

    _app = new monadic::Application( "../kernels/" );

    QGraphicsScene *s = new QGraphicsScene();
    s->setBackgroundBrush( QBrush(QColor::fromRgb(49,54,56)));
    ui->graphicsView->setScene(s);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    nodesEditor = new QNodesEditor(this);
    nodesEditor->install(s);

    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->action_Load, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(ui->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    ui->toolBar->addAction("Add block", this, SLOT(addBlock()));
}

QNEMainWindow::~QNEMainWindow()
{
    delete ui;
}

void QNEMainWindow::saveFile()
{
	QString fname = QFileDialog::getSaveFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::WriteOnly);
	QDataStream ds(&f);
	nodesEditor->save(ds);
}

void QNEMainWindow::loadFile()
{
	QString fname = QFileDialog::getOpenFileName();
	if (fname.isEmpty())
		return;

    _app->load( fname.toStdString() );
    std::vector< monadic::Node* > lnodes = _app->getNodes();
    for( int k = 0; k < lnodes.size(); ++k )
    {
        monadic::Node* n = lnodes[k];
        QNEBlock *b = new QNEBlock(0, ui->graphicsView->scene());
        _blocks.push_back( b );

        b->setNode( n );
        b->addPort( QString::fromStdString(n->getKernelName()), 0, QNEPort::TypePort );
        vector< monadic::Pin* > pins = n->getPins();
        for( int i = 0; i < pins.size(); ++i )
        {
            monadic::Pin* p = pins[i];
            QNEPort* port;
            if( p->getMode() == monadic::Pin::NODE_INPUT_PIN )
            {
                port = b->addInputPort( QString::fromStdString(p->getLabel()) );
            }
            else if( p->getMode() == monadic::Pin::NODE_OUTPUT_PIN )
            {
                port = b->addOutputPort( QString::fromStdString( p->getLabel() ) );
            }

            port->setPin( p );
            _ports.push_back( port );

        }
    }

    std::vector< monadic::Link* > llinks = _app->getLinks();
    for( int k = 0; k < llinks.size(); ++k )
    {
        monadic::Link* l = llinks[k];
        QNEConnection* conn = new QNEConnection(0, ui->graphicsView->scene());
        conn->setLink( l );
        _connections.push_back( conn );

        monadic::Pin* p1 = l->getStartPin();
        monadic::Pin* p2 = l->getEndPin();

        QNEPort* port1;
        QNEPort* port2;
        for( int i = 0; i < _ports.size(); ++i )
        {
            if( _ports[i]->getPin() == p1 )
                port1 = _ports[i];

            if( _ports[i]->getPin() == p2 )
                port2 = _ports[i];
        }

        conn->setPort1( port1 );
        conn->setPort2( port2 );

    }

    _app->enableAllNodes();
    _app->start();

}

void QNEMainWindow::addBlock()
{
	QNEBlock *b = new QNEBlock(0, ui->graphicsView->scene());
	static const char* names[] = {"Vin", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
	for (int i = 0; i < 4 + rand() % 3; i++)
	{
		b->addPort(names[rand() % 10], rand() % 2, 0, 0);
		b->setPos(ui->graphicsView->sceneRect().center().toPoint());
	}
}
