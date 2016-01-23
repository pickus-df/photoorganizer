#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDrag>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QImage image("/home/pickus/dev/qt/photoOrganizer/exampleFs/dcim100/graphics-tux.jpeg");



   // QImage image("exampleFs/dcim100/graphics-tux.jpeg");

    ui->label->setText("Arkiv");
    ui->label_2->setText("Album");

    QLabel *archiveThumb = new QLabel(this);
    archiveThumb->setPixmap(QPixmap::fromImage(image));
    archiveThumb->move(20,80);
    archiveThumb->show();
    archiveThumb->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if(!child)
        return;

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QMimeData *mimeData = new QMimeData;


    QPixmap pixmap = *child->pixmap();
    dataStream << pixmap << QPoint(event->pos() - child->pos());
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos()-child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(),QColor(127,127,127,127));
    painter.end();

    child->setPixmap(tempPixmap);

    if(drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction){
        child->close();
    }
    else{
        child->show();
        child->setPixmap(pixmap);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("application/x-dnditemdata")){
        if(event->source()==this){
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else{
            event->acceptProposedAction();
        }
    }
    else{
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("application/x-dnditemdata")){
        if(event->source()==this){
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else{
            event->acceptProposedAction();
        }
    }
    else{
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("application/x-dnditemdata")){
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;

        dataStream >> pixmap >> offset;

        QLabel *newThumbnail = new QLabel(this);
        newThumbnail->setPixmap(pixmap);
        newThumbnail->move(event->pos()-offset);
        newThumbnail->show();
        newThumbnail->setAttribute(Qt::WA_DeleteOnClose);

        if(event->source()==this){
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else{
            event->acceptProposedAction();
        }
    }
    else{
        event->ignore();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
