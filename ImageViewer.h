#pragma once

#include <QtWidgets>
#include <QtWidgets>
#include "ui_ImageViewer.h"
#include "ViewerWidget.h"
#include "NewImageDialog.h"
#include "GeomObject.h"

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget* parent = Q_NULLPTR);

private:
	Ui::ImageViewerClass* ui;
	NewImageDialog* newImgDialog;

	QSettings settings;
	QMessageBox msgBox;

	//ViewerWidget functions
	ViewerWidget* getViewerWidget(int tabId);
	ViewerWidget* getCurrentViewerWidget();

	//Event filters
	bool eventFilter(QObject* obj, QEvent* event);

	QVector<GeomObject> objekty;
	int pointsCount;
	QVector<QPoint> points;
	int layer = 0;
	QVector<QVector<QColor>> farbaPlatna;
	QVector<QVector<int>> zHodnoty;

	void drawCircle(QVector<QPoint> bodyK, QColor outlineK, int zValue);
	void drawCircle2(int xc, int yc, int x, int y, QColor outlineK, int zValue);
	void drawUsecka(QVector<QPoint> bodyK, QColor outlineK, int zValue);
	void drawRectangle(QVector<QPoint> bodyK, QColor fillK, QColor outlineK, int fill, int zValue);
	void drawPolygon(QVector<QPoint> bodyK, QColor fillK, QColor outlineK, int fill, int zValue);
	void drawBrezier(QVector<QPoint> bodyK, QColor outlineK, int zValue);
	void drawUseckaBrasenham(QPoint start, QPoint end, QColor outlineK, int zValue);

	QVector<QPoint> orezBody(QVector<QPoint> bodyK);
	QVector<QPoint> algoritmusSH(QVector<QPoint> bodyK, int xMin);


	void vyplnPlatno();

	bool posuvaj = false;
	QPoint startpoint = QPoint(0,0);
	QPoint newPoint = QPoint(0, 0);

	struct Hrana {
		QPoint prvyBod = QPoint(0, 0);
		QPoint druhyBod = QPoint(0, 0);
		double m = 0.0;
		double w = 0.0;
		void napln(QPoint prvy, QPoint druhy, double smer, double we) {
			prvyBod = prvy;
			druhyBod = druhy;
			m = smer;
			w = we;
		};
	};

	QVector<Hrana> hranyPolygonu;

	//ViewerWidget Events
	bool ViewerWidgetEventFilter(QObject* obj, QEvent* event);
	void ViewerWidgetMouseButtonPress(ViewerWidget* w, QEvent* event);
	void ViewerWidgetMouseButtonRelease(ViewerWidget* w, QEvent* event);
	void ViewerWidgetMouseMove(ViewerWidget* w, QEvent* event);
	void ViewerWidgetLeave(ViewerWidget* w, QEvent* event);
	void ViewerWidgetEnter(ViewerWidget* w, QEvent* event);
	void ViewerWidgetWheel(ViewerWidget* w, QEvent* event);

	//ImageViewer Events
	void closeEvent(QCloseEvent* event);

	//Image functions
	void openNewTabForImg(ViewerWidget* vW);
	bool openImage(QString filename);
	bool saveImage(QString filename);
	void clearImage();
	void setBackgroundColor(QColor color);

	//Inline functions
	inline bool isImgOpened() { return ui->tabWidget->count() == 0 ? false : true; }

private slots:
	//Tabs slots
	void on_tabWidget_tabCloseRequested(int tabId);
	void on_actionRename_triggered();

	//Image slots
	void on_actionNew_triggered();
	void newImageAccepted();
	void openNewImage(int width, int height);
	void on_actionOpen_triggered();
	void on_actionSave_as_triggered();
	void on_actionClear_triggered();
	void on_actionSet_background_color_triggered();
	void on_zHore_clicked();
	void on_zDole_clicked();
	void on_actionZmenVypln_triggered();
	void on_actionZmenOkraj_triggered();
	void on_actionNacitaj_triggered();
	void on_actionUloz_triggered();
	void on_skaluj_clicked();
	void on_otoc_clicked();
	void on_changeFill_clicked();
	void on_changeOutline_clicked();
	void on_setIsFilled_clicked();
};
