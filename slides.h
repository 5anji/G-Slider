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
		QTimer *timer;

		Slides(QWidget *parent = nullptr);
		~Slides();

	private slots:
		int rand_int(int low, int high);

		void set_image(QString path);

		void set_timer();

		void timer_event();

		void stop_timer();

		void next_image();

		void previous_image();

		void next_shuffle_image();

		void on_pushButton_clicked();

		void on_pushButton_2_clicked();

		void on_pushButton_3_clicked();

		void on_comboBox_activated(int index);

		void on_checkBox_stateChanged(int arg1);

	private:
		Ui::Slides *ui;
};
#endif // SLIDES_H
