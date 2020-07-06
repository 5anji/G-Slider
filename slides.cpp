#include "slides.h"
#include "./ui_slides.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QFileDialog>

QString image_directory[128];
QDir path;
int i, count = 0;

Slides::Slides(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Slides)
{
	ui->setupUi(this);
}

// Browse Button:
void Slides::on_pushButton_3_clicked()
{
	path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	QStringList images = path.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);

	foreach(QString filename, images)
	{
		image_directory[count] = path.filePath(filename);
		count++;
		qDebug() << "Path: " << image_directory[count-1];
	}

}

Slides::~Slides()
{
	delete ui;
}
