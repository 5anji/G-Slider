#include "slides.h"
#include "./ui_slides.h"

#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QTimer>

QString image_directory[128], temp_directory;
QDir path;
int i, count, period;
float anim_period = 0.5;
bool timer_checker, shuffle_checker, comboBox_checker, image_checker, mouse_click_checker, anim_checker;

Slides::Slides(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Slides)
{
	ui->setupUi(this);

	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	QPixmap pixmap("extras/right_arrow.png");
	QIcon ButtonIcon(pixmap);
	ui->pushButton->setIcon(ButtonIcon);
	ui->pushButton->setIconSize(pixmap.rect().size());
}

int Slides::rand_int(int low, int high)
{
	return qrand() % ((high + 1) - low) + low;
}

void Slides::image_renderer()
{
	set_image(image_directory[i]);
}

void Slides::set_image(QString a)
{
	QPixmap image = a;
	ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->label->setPixmap(image.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));
}

void Slides::set_animation()
{
	start_animation();
	end_animation();
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
	if (image_checker)
	{
		temp_directory = image_directory[i];

		if (i == count - 1)
		{
			i = 0;
		}
		else
		{
			i++;
		}

		if (anim_checker)
		{
			image_renderer();
		}
		else
		{
			set_animation();
			image_renderer();
		}
	}
}

void Slides::previous_image()
{
	if (image_checker)
	{
		temp_directory = image_directory[i];

		if (i == 0)
		{
			i = count - 1;
		}
		else
		{
			i--;
		}

		set_animation();

		if (anim_checker)
		{
			image_renderer();
		}
		else
		{
			set_animation();
			image_renderer();
		}
	}
}

void Slides::next_shuffle_image()
{
	if (image_checker)
	{
		int temp = i;
		temp_directory = image_directory[i];

LOOP:
		i = rand_int(0, count - 1);
		if (i == temp) goto LOOP;

		if (anim_checker)
		{
			image_renderer();
		}
		else
		{
			set_animation();
			image_renderer();
		}
	}
}

void Slides::start_animation()
{
	QPixmap image = temp_directory;
	ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->label_2->setPixmap(image.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio));

	QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
	QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");

	ui->label->setGraphicsEffect(effect);
	anim->setDuration(anim_period*1000);
	anim->setStartValue(0.0);
	anim->setEndValue(1.0);
	anim->setEasingCurve(QEasingCurve::OutQuad);
	connect(anim, &QPropertyAnimation::finished, [=](){});
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Slides::end_animation()
{
	QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
	QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");

	ui->label_2->setGraphicsEffect(effect);
	anim->setDuration(anim_period*1000);
	anim->setStartValue(1.0);
	anim->setEndValue(0.0);
	connect(anim, &QPropertyAnimation::finished, [=](){});
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Slides::uncheck_mouse_click()
{
	mouse_click_checker = false;
}

void Slides::resizeEvent(QResizeEvent *event)
{
	ui->label->resize(ui->centralwidget->width(), ui->centralwidget->height());
	ui->label_2->resize(ui->centralwidget->width(), ui->centralwidget->height());

	ui->pushButton->resize(ui->centralwidget->width() / 5, ui->centralwidget->height());
	ui->pushButton->move(4 * ui->centralwidget->width() / 5, 0);

	ui->pushButton_2->resize(ui->centralwidget->width() / 5, ui->centralwidget->height());

	ui->pushButton_3->resize(3 * ui->centralwidget->width() / 5, ui->centralwidget->height());
	ui->pushButton_3->move(ui->centralwidget->width() / 5, 0);
	if (image_checker)
	{
		image_renderer();
	}
	QWidget::resizeEvent(event);
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
	if (mouse_click_checker)
	{
		if (image_checker)
		{
			if (isFullScreen())
			{
				ui->menubar->show();
				showNormal();
			}
			else
			{
				ui->menubar->hide();
				showFullScreen();
			}
		}
		else
		{
			on_actionOpen_triggered();
		}
	}
	else
	{
		mouse_click_checker = true;
		QTimer::singleShot(200, this, SLOT(uncheck_mouse_click()));
	}
}

void Slides::on_actionOpen_triggered()
{
	stop_timer();
	image_checker = false;
	count = 0;
	path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	QStringList images = path.entryList(QStringList() << "*.jpg" << "*.jpeg" << "*.bmp" << "*.pbm" << "*.pgm" << "*.ppm" << "*.xbm" << "*.xpm" << "*.png", QDir::Files);

	foreach(QString filename, images)
	{
		image_directory[count] = path.filePath(filename);
		count++;
	}

	if (count > 0)
	{
		image_checker = true;
		set_image(image_directory[0]);
	}
	set_timer();
}

void Slides::on_actionExit_triggered()
{
	close();
}

void Slides::on_actionNext_image_triggered()
{
	next_image();
}

void Slides::on_actionPrevious_image_triggered()
{
	previous_image();
}

void Slides::on_action30_seconds_triggered()
{
	stop_timer();
	period = 30;
	set_timer();
}

void Slides::on_action1_minute_triggered()
{
	stop_timer();
	period = 60;
	set_timer();
}

void Slides::on_action2_minutes_triggered()
{
	stop_timer();
	period = 120;
	set_timer();
}

void Slides::on_action5_minutes_triggered()
{
	stop_timer();
	period = 300;
	set_timer();
}

void Slides::on_action10_minutes_triggered()
{
	stop_timer();
	period = 600;
	set_timer();
}

void Slides::on_actionCustom_triggered()
{
	stop_timer();
	period = QInputDialog::getInt(this, tr("Input period"), tr("Seconds:"), 30, 5, 3600, 5);
	set_timer();
}

void Slides::on_actionStop_triggered()
{
	stop_timer();
}

void Slides::on_actionChange_image_randomly_triggered()
{
	next_shuffle_image();
}

void Slides::on_actionShuffle_toggled(bool arg1)
{
	stop_timer();
	if (arg1) shuffle_checker = true; else shuffle_checker = false;
	set_timer();
}

void Slides::on_actionFull_screen_triggered()
{

	ui->menubar->hide();
	showFullScreen();
}

void Slides::on_actionMaximize_triggered()
{
	if (isFullScreen())
	{
		ui->menubar->show();
		showMaximized();
	}

	if (isMaximized())
	{
		showNormal();
	}
	else
	{
		showMaximized();
	}
}

void Slides::on_actionMinimize_triggered()
{	
	if (isFullScreen())
	{
		ui->menubar->show();
	}

	showMinimized();
}

void Slides::on_actionStandart_1280x720_triggered()
{
	if (isFullScreen())
	{
		ui->menubar->show();
	}

	setGeometry(15, 20, 1280, 720);
}

void Slides::on_actionSlow_triggered()
{
	anim_checker = false;
	anim_period = 1.0;
}

void Slides::on_actionNormal_triggered()
{
	anim_checker = false;
	anim_period = 0.5;
}

void Slides::on_actionFast_triggered()
{
	anim_checker = false;
	anim_period = 0.25;
}

void Slides::on_actionNone_triggered()
{
	anim_checker = true;
}

Slides::~Slides()
{
	delete ui;
}
