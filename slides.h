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

		void image_renderer();

		void set_image(QString a);

		void set_animation();

		void set_timer();

		void timer_event();

		void stop_timer();

		void next_image();

		void previous_image();

		void next_shuffle_image();

		void start_animation();

		void end_animation();

		void uncheck_mouse_click();

		void on_pushButton_clicked();

		void on_pushButton_2_clicked();

		void on_pushButton_3_clicked();

		void on_actionExit_triggered();

		void on_actionOpen_triggered();

		void on_actionNext_image_triggered();

		void on_actionPrevious_image_triggered();

		void on_action30_seconds_triggered();

		void on_action1_minute_triggered();

		void on_action2_minutes_triggered();

		void on_action5_minutes_triggered();

		void on_action10_minutes_triggered();

		void on_actionCustom_triggered();

		void on_actionStop_triggered();

		void on_actionChange_image_randomly_triggered();

		void on_actionShuffle_toggled(bool arg1);

		void on_actionFull_screen_triggered();

		void on_actionMaximize_triggered();

		void on_actionMinimize_triggered();

		void on_actionStandart_1280x720_triggered();

	private:
		Ui::Slides *ui;

	protected:
		void resizeEvent(QResizeEvent *event);
};
#endif // SLIDES_H
