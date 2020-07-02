#include "slides.h"
#include "./ui_slides.h"

Slides::Slides(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Slides)
{
	ui->setupUi(this);
}

Slides::~Slides()
{
	delete ui;
}
