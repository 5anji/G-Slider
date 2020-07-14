#include "slides.h"
#include "./ui_slides.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

QString image_directory[128];
QDir path;
int i, count, period;
bool timer_checker, shuffle_checker = false, comboBox_checker;

Slides::Slides(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Slides)
{
	ui->setupUi(this);
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
}

int Slides::rand_int(int low, int high)
{
	return qrand() % ((high + 1) - low) + low;
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
		timer_checker = true;
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
	if (shuffle_checker)
	{
		next_shuffle_image();
	}
	else
	{
		next_image();
	}
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

void Slides::next_shuffle_image()
{
	int temp = i;

	LOOP:
	i = rand_int(0, count - 1);
	if (i == temp) goto LOOP;

	set_image(image_directory[i]);
}

void Slides::on_pushButton_clicked()
{
	stop_timer();
	if (shuffle_checker)
	{
		next_shuffle_image();
	}
	else
	{
		next_image();
	}
	set_timer();
}

void Slides::on_pushButton_2_clicked()
{
	stop_timer();
	if (shuffle_checker)
	{
		next_shuffle_image();
	}
	else
	{
		previous_image();
	}

	set_timer();
}

void Slides::on_pushButton_3_clicked()
{
	stop_timer();
	count = 0;
	path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	QStringList images = path.entryList(QStringList() << "*.jpg" << "*.jpeg" << "*.bmp" << "*.pbm" << "*.pgm" << "*.ppm" << "*.xbm" << "*.xpm" << "*.png", QDir::Files);

	foreach(QString filename, images)
	{
		image_directory[count] = path.filePath(filename);
		count++;
	}
	set_image(image_directory[0]);
	set_timer();
}

void Slides::on_comboBox_activated(int index)
{
	switch (index) {
		case 1:
			stop_timer();
			period = 30;
			set_timer();
		break;
		case 2:
			stop_timer();
			period = 60;
			set_timer();
		break;
		case 3:
			stop_timer();
			period = 120;
			set_timer();
		break;
		case 4:
			stop_timer();
			period = 300;
			set_timer();
		break;
		case 5:
			stop_timer();
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

void Slides::on_checkBox_stateChanged(int arg1)
{
	stop_timer();
	if (arg1 == 2) shuffle_checker = true; else shuffle_checker = false;
	set_timer();
}

Slides::~Slides()
{
	delete ui;
}
