#include "slides.h"
#include "./ui_slides.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>

QString image_directory[128];
QDir path;
int i, count, period;
bool timer_checker;

Slides::Slides(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Slides)
{
	ui->setupUi(this);
}

void Slides::set_image(QString path)
{
	QPixmap image = path;
	ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->label->setPixmap(image.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));
}

void Slides::set_timer()
{
	if (period >= 5)
	{
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(timer_event()));
		timer->start(period*1000);
	}
	else if (period != 0)
	{
		QMessageBox::warning(this, "Warning", "The period is below 5 seconds. Set a higher value.");
	}
}

void Slides::timer_event()
{
	next_image();
}

void Slides::stop_timer()
{
	if(timer_checker)
	{
		timer_checker = false;
		timer->stop();
	}
}

void Slides::next_image()
{
	if (i == count - 1)
	{
		i = 0;
	}
	else
	{
		i++;
	}
	set_image(image_directory[i]);
}

void Slides::previous_image()
{
	if (i == 0)
	{
		i = count - 1;
	}
	else
	{
		i--;
	}
	set_image(image_directory[i]);
}

void Slides::on_pushButton_clicked()
{
	stop_timer();
	next_image();
	set_timer();
}

void Slides::on_pushButton_2_clicked()
{
	stop_timer();
	previous_image();
	set_timer();
}

void Slides::on_pushButton_3_clicked()
{
	count = 0;
	path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	QStringList images = path.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

	foreach(QString filename, images)
	{
		image_directory[count] = path.filePath(filename);
		count++;
	}
	set_image(image_directory[0]);
}

void Slides::on_comboBox_activated(int index)
{
	//	qDebug() << index;
	switch (index) {
		case 1:
			stop_timer();
			timer_checker = true;
			period = 30;
			set_timer();
		break;
		case 2:
			stop_timer();
			timer_checker = true;
			period = 60;
			set_timer();
		break;
		case 3:
			stop_timer();
			timer_checker = true;
			period = 120;
			set_timer();
		break;
		case 4:
			stop_timer();
			timer_checker = true;
			period = 300;
			set_timer();
		break;
		case 5:
			stop_timer();
			timer_checker = true;
			period = 600;
			set_timer();
		break;
		case 6:
			//			period = 10;
			//			set_timer();
		break;
		default:
			stop_timer();
		break;
	}
}

Slides::~Slides()
{
	delete ui;
}
