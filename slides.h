#ifndef SLIDES_H
#define SLIDES_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Slides; }
QT_END_NAMESPACE

class Slides : public QMainWindow
{
		Q_OBJECT

	public:
		Slides(QWidget *parent = nullptr);
		~Slides();

	private:
		Ui::Slides *ui;
};
#endif // SLIDES_H
