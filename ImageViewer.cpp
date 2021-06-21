#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::ImageViewerClass)
{
	ui->setupUi(this);
}

//ViewerWidget functions
ViewerWidget* ImageViewer::getViewerWidget(int tabId)
{
	QScrollArea* s = static_cast<QScrollArea*>(ui->tabWidget->widget(tabId));
	if (s) {
		ViewerWidget* vW = static_cast<ViewerWidget*>(s->widget());
		return vW;
	}
	return nullptr;
}
ViewerWidget* ImageViewer::getCurrentViewerWidget()
{
	return getViewerWidget(ui->tabWidget->currentIndex());
}

// Event filters
bool ImageViewer::eventFilter(QObject* obj, QEvent* event)
{
	if (obj->objectName() == "ViewerWidget") {
		return ViewerWidgetEventFilter(obj, event);
	}
	return false;
}

void ImageViewer::drawCircle(QVector<QPoint> bodyK, QColor outlineK, int zValue)
{
	QPoint stred = bodyK[0];
	QPoint bod = bodyK[1];
	int dx = abs(stred.x() - bod.x());
	int dy = abs(stred.y() - bod.y());
	double polomer = sqrt(dx * dx + dy * dy);
	int r = floor(polomer + 0.5);
	int d = 3 - 2 * r;
	int x = 0;
	int y = r;

	drawCircle2(stred.x(), stred.y(), x, y, outlineK, zValue);

	while (y >= x) {
		x++;
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else {
			d = d + 4 * x + 6;
		}
		drawCircle2(stred.x(), stred.y(), x, y, outlineK, zValue);
		update();
	}
}

void ImageViewer::drawCircle2(int xc, int yc, int x, int y, QColor outlineK, int zValue)
{
	ViewerWidget* w = getCurrentViewerWidget();
	int sirka = w->getImgWidth();
	int vyska = w->getImgHeight();

	if (QPoint(xc + x, yc + y).x() > 0 && QPoint(xc + x, yc + y).x() < sirka && QPoint(xc + x, yc + y).y() > 0 && QPoint(xc + x, yc + y).y() < vyska) {
		if (zHodnoty[xc + x][yc + y] < zValue) {
			farbaPlatna[xc + x][yc + y] = outlineK;
			zHodnoty[xc + x][yc + y] = zValue;
		}
	}
	if (QPoint(xc - x, yc + y).x() > 0 && QPoint(xc - x, yc + y).x() < sirka && QPoint(xc - x, yc + y).y() > 0 && QPoint(xc - x, yc + y).y() < vyska) {
		if (zHodnoty[xc - x][yc + y] < zValue) {
			farbaPlatna[xc - x][yc + y] = outlineK;
			zHodnoty[xc - x][yc + y] = zValue;
		}
	}
	if (QPoint(xc + x, yc - y).x() > 0 && QPoint(xc + x, yc - y).x() < sirka && QPoint(xc + x, yc - y).y() > 0 && QPoint(xc + x, yc - y).y() < vyska) {
		if (zHodnoty[xc + x][yc - y] < zValue) {
			farbaPlatna[xc + x][yc - y] = outlineK;
			zHodnoty[xc + x][yc - y] = zValue;
		}
	}
	if (QPoint(xc - x, yc - y).x() > 0 && QPoint(xc - x, yc - y).x() < sirka && QPoint(xc - x, yc - y).y() > 0 && QPoint(xc - x, yc - y).y() < vyska) {
		if (zHodnoty[xc - x][yc - y] < zValue) {
			farbaPlatna[xc - x][yc - y] = outlineK;
			zHodnoty[xc - x][yc - y] = zValue;
		}
	}
	if (QPoint(xc + y, yc + x).x() > 0 && QPoint(xc + y, yc + x).x() < sirka && QPoint(xc + y, yc + x).y() > 0 && QPoint(xc + y, yc + x).y() < vyska) {

		if (zHodnoty[xc + y][yc + x] < zValue) {
			farbaPlatna[xc + y][yc + x] = outlineK;
			zHodnoty[xc + y][yc + x] = zValue;
		}
	}
	if (QPoint(xc - y, yc + x).x() > 0 && QPoint(xc - y, yc + x).x() < sirka && QPoint(xc - y, yc + x).y() > 0 && QPoint(xc - y, yc + x).y() < vyska) {

		if (zHodnoty[xc - y][yc + x] < zValue) {
			farbaPlatna[xc - y][yc + x] = outlineK;
			zHodnoty[xc - y][yc + x] = zValue;
		}
	}
	if (QPoint(xc + y, yc - x).x() > 0 && QPoint(xc + y, yc - x).x() < sirka && QPoint(xc + y, yc - x).y() > 0 && QPoint(xc + y, yc - x).y() < vyska) {

		if (zHodnoty[xc + y][yc - x] < zValue) {
			farbaPlatna[xc + y][yc - x] = outlineK;
			zHodnoty[xc + y][yc - x] = zValue;
		}
	}
	if (QPoint(xc - y, yc - x).x() > 0 && QPoint(xc - y, yc - x).x() < sirka && QPoint(xc - y, yc - x).y() > 0 && QPoint(xc - y, yc - x).y() < vyska) {
		if (zHodnoty[xc - y][yc - x] < zValue) {
			farbaPlatna[xc - y][yc - x] = outlineK;
			zHodnoty[xc - y][yc - x] = zValue;
		}
	}
}

void ImageViewer::drawUsecka(QVector<QPoint> bodyK, QColor outlineK, int zValue)
{
	ViewerWidget* w = getCurrentViewerWidget();
	QPoint start = bodyK[0];
	QPoint end = bodyK[1];

	//cyrus beck algoritmus
	QVector<QPoint> vrcholyPlatna;
	vrcholyPlatna.clear();
	QPoint pt1 = QPoint(0, 0);
	vrcholyPlatna.append(pt1);
	QPoint pt2 = QPoint(w->getImgWidth()-1, 0);
	vrcholyPlatna.append(pt2);
	QPoint pt3 = QPoint(w->getImgWidth()-1, w->getImgHeight()-1);
	vrcholyPlatna.append(pt3);
	QPoint pt4 = QPoint(0, w->getImgHeight()-1);
	vrcholyPlatna.append(pt4);



	if ((0 <= start.x() <= w->getImgWidth() && 0 <= start.y() <= w->getImgHeight()) || (0 <= end.x() <= w->getImgWidth() && 0 <= end.y() <= w->getImgHeight())) {
		double t;
		QPoint dVec = end - start;
		QPoint wVec;
		QPoint nVec;
		int dn;
		int wn;
		double tl = 0.0;
		double tu = 1.0;
		int dx = end.x() - start.x();
		int dy = end.y() - start.y();


		for (size_t i = 0; i < vrcholyPlatna.size(); i++) {

			nVec.setX(-1 * (vrcholyPlatna[(i + 1) % vrcholyPlatna.size()].y() - vrcholyPlatna[i].y()));
			nVec.setY((vrcholyPlatna[(i + 1) % vrcholyPlatna.size()].x() - vrcholyPlatna[i].x()));

			wVec = start - vrcholyPlatna[i];
			dn = QPoint::dotProduct(dVec, nVec);

			wn = QPoint::dotProduct(wVec, nVec);


			if (dn != 0) {
				t = -wn / (double)dn;
				if (dn > 0 && t <= 1) {
					tl = std::max(t, tl);
				}
				else if (dn < 0 && t >= 0) {
					tu = std::min(t, tu);
				}
			}
		}
		if ((tl == 0) && (tu == 1)) {
		}
		else if (tl < tu) {


			QPoint start2 = start + QPoint(round(tl * dx), round(tl * dy));
			QPoint end2 = start + QPoint(round(tu * dx), round(tu * dy));
			start = start2;
			end = end2;

		}
		//qDebug() << "tl:" << tl;
		//qDebug() << "tu:" << tu;
		//qDebug() << "1.:" << start;
		//qDebug() << "2.:" << end;

	}
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye;
	

	dx = end.x() - start.x();
	dy = end.y() - start.y();
	dx1 = fabs(dx);
	dy1 = fabs(dy);

	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = start.x();
			y = start.y();
			xe = end.x();
		}
		else {
			x = end.x();
			y = end.y();
			xe = start.x();
		}
		if (zHodnoty[x][y] < zValue) {
			farbaPlatna[x][y] = outlineK;
			zHodnoty[x][y] = zValue;
		}
		while (x < xe) {
			x = x + 1;
			if (px < 0) {
				px = px + 2 * dy1;
			}
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					y = y + 1;
				}
				else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			if (zHodnoty[x][y] < zValue) {
				farbaPlatna[x][y] = outlineK;
				zHodnoty[x][y] = zValue;
			}
			
		}

	}
	else {
		if (dy >= 0) {
			x = start.x();
			y = start.y();
			ye = end.y();
		}
		else {
			x = end.x();
			y = end.y();
			ye = start.y();
		}
		if (zHodnoty[x][y] < zValue) {
			farbaPlatna[x][y] = outlineK;
			zHodnoty[x][y] = zValue;
		}
		while (y < ye) {
			y = y + 1;
			if (py <= 0) {
				py = py + 2 * dx1;
			}
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					x = x + 1;
				}
				else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			if (zHodnoty[x][y] < zValue) {
				farbaPlatna[x][y] = outlineK;
				zHodnoty[x][y] = zValue;
			}
		}
	}
}

void ImageViewer::drawRectangle(QVector<QPoint> bodyK, QColor fillK, QColor outlineK, int fill, int zValue)
{
	/*ViewerWidget* w = getCurrentViewerWidget();
	if (bodyK[0].y() < 0) {
		bodyK[0].setY(0);
		bodyK[3].setY(0);
	}
	if (bodyK[2].y() < 0) {
		bodyK[2].setY(0);
		bodyK[1].setY(0);
	}
	if (bodyK[0].y() >= w->getImgHeight()) {
		bodyK[0].setY(w->getImgHeight()-1);
		bodyK[3].setY(w->getImgHeight()-1);
	}
	if (bodyK[2].y() >= w->getImgHeight()) {
		bodyK[2].setY(w->getImgHeight() - 1);
		bodyK[1].setY(w->getImgHeight() - 1);
	}
	if (bodyK[0].x() < 0) {
		bodyK[0].setX(0);
		bodyK[1].setX(0);
	}
	if (bodyK[3].x() < 0) {
		bodyK[3].setX(0);
		bodyK[2].setX(0);
	}
	if (bodyK[0].x() >= w->getImgWidth()) {
		bodyK[0].setX(w->getImgWidth() - 1);
		bodyK[1].setX(w->getImgWidth() - 1);
	}
	if (bodyK[3].x() >= w->getImgWidth()) {
		bodyK[3].setX(w->getImgWidth() - 1);
		bodyK[2].setX(w->getImgWidth() - 1);
	}*/
	bodyK = orezBody(bodyK);
	if (fill == 1 && bodyK.size() >= 3 ) {
		hranyPolygonu.clear();
		QPoint prvy, druhy;
		double m, w;
		for (int i = 0; i < bodyK.size(); i++) {
			if (bodyK[i].y() <= bodyK[(i + 1) % bodyK.size()].y()) {
				prvy = bodyK[i];
				druhy = bodyK[(i + 1) % bodyK.size()];
			}
			else {
				druhy = bodyK[i];
				prvy = bodyK[(i + 1) % bodyK.size()];
			}
			//m = (bodyPol[(i + 1) % bodyPol.size()].y() - bodyPol[i].y()) / (double)(bodyPol[(i + 1) % bodyPol.size()].x() - bodyPol[i].x());
			int dy = druhy.y() - prvy.y();
			int dx = druhy.x() - prvy.x();
			m = dy / (double)dx;
			w = 1 / m;
			if (druhy.y() != prvy.y()) {
				druhy.setY(druhy.y() - 1);
				Hrana tempHrana;
				tempHrana.napln(prvy, druhy, m, w);
				hranyPolygonu.append(tempHrana);
			}

		}
		if (hranyPolygonu.size() != 0) {
			for (int i = 0; i < hranyPolygonu.size() - 1; i++) {
				for (int j = 0; j < hranyPolygonu.size() - 1 - i; j++) {
					if (hranyPolygonu[j].prvyBod.y() > hranyPolygonu[j + 1].prvyBod.y()) {
						hranyPolygonu.swapItemsAt(j, j + 1);
					}
				}
			}
		}
		struct Edge {
			int deltaY = 0;
			double x = 0.0;
			double w = 0.0;
			void napln(int y, int xk, double w2) {
				deltaY = y;
				x = xk;
				w = w2;
			}
		};
		int yMin = hranyPolygonu[0].prvyBod.y();
		int yMax = hranyPolygonu[hranyPolygonu.size() - 1].druhyBod.y();

		QVector<QVector<Edge>> tabulkaHran;
		tabulkaHran.resize(yMax - yMin);
		for (int j = 0; j <= yMax - yMin; j++) {
			for (int i = 0; i < hranyPolygonu.size(); i++) {
				if (hranyPolygonu[i].prvyBod.y() - yMin == j) {
					int delta = hranyPolygonu[i].druhyBod.y() - hranyPolygonu[i].prvyBod.y();
					double ws = hranyPolygonu[i].w;
					double x2 = static_cast<double>(hranyPolygonu[i].prvyBod.x());
					Edge tempHrana;
					tempHrana.napln(delta, x2, ws);
					tabulkaHran[j].append(tempHrana);
				}
			}
		}
		int y = yMin;
		QVector<Edge> zozAktivHran;

		for (int i = 0; i < tabulkaHran.size(); i++) {
			if (tabulkaHran[i].isEmpty() == false) {
				for (int j = 0; j < tabulkaHran[i].size(); j++) {
					zozAktivHran.append(tabulkaHran[i][j]);
				}
			}
			//usporiadanie podla x
			for (int j = 0; j < zozAktivHran.size() - 1; j++) {
				for (int k = 0; k < zozAktivHran.size() - 1 - j; k++) {
					if (zozAktivHran[k].x > zozAktivHran[k + 1].x) {
						zozAktivHran.swapItemsAt(k, k + 1);
					}
				}
			}

			for (int j = 0; j < zozAktivHran.size(); j++) {
				if (static_cast<int>(zozAktivHran[j].x + 0.5) != static_cast<int>(zozAktivHran[(j + 1) % zozAktivHran.size()].x + 0.5)) {
					for (int k = static_cast<int>(zozAktivHran[j].x + 0.5); k <= static_cast<int>(zozAktivHran[(j + 1) % zozAktivHran.size()].x + 0.5); k++) {
						if (zHodnoty[k][y] < zValue) {
							farbaPlatna[k][y] = fillK;
							zHodnoty[k][y] = zValue;
						}
					}
				}
			}
			for (int j = 0; j < zozAktivHran.size(); ) {
				if (zozAktivHran[j].deltaY == 0) {
					zozAktivHran.removeAt(j);
				}
				else j++;
			}
			for (int j = 0; j < zozAktivHran.size(); j++) {
				zozAktivHran[j].deltaY = zozAktivHran[j].deltaY - 1;
				zozAktivHran[j].x = zozAktivHran[j].x + zozAktivHran[j].w;
			}
			y = y + 1;
		}
	}
	drawUseckaBrasenham(bodyK[0], bodyK[1], outlineK, zValue);
	drawUseckaBrasenham(bodyK[0], bodyK[3], outlineK, zValue);
	drawUseckaBrasenham(bodyK[2], bodyK[1], outlineK, zValue);
	drawUseckaBrasenham(bodyK[2], bodyK[3], outlineK, zValue);
}

void ImageViewer::drawPolygon(QVector<QPoint> bodyK, QColor fillK, QColor outlineK, int fill, int zValue)
{
	bodyK = orezBody(bodyK);
	if (fill == 1 && bodyK.size() >= 3) {
		hranyPolygonu.clear();
		QPoint prvy, druhy;
		double m, w;
		for (int i = 0; i < bodyK.size(); i++) {
			if (bodyK[i].y() <= bodyK[(i + 1) % bodyK.size()].y()) {
				prvy = bodyK[i];
				druhy = bodyK[(i + 1) % bodyK.size()];
			}
			else {
				druhy = bodyK[i];
				prvy = bodyK[(i + 1) % bodyK.size()];
			}
			//m = (bodyPol[(i + 1) % bodyPol.size()].y() - bodyPol[i].y()) / (double)(bodyPol[(i + 1) % bodyPol.size()].x() - bodyPol[i].x());
			int dy = druhy.y() - prvy.y();
			int dx = druhy.x() - prvy.x();
			m = dy / (double)dx;
			w = 1 / m;
			if (druhy.y() != prvy.y()) {
				druhy.setY(druhy.y() - 1);
				Hrana tempHrana;
				tempHrana.napln(prvy, druhy, m, w);
				hranyPolygonu.append(tempHrana);
			}

		}
		if (hranyPolygonu.size() != 0) {
			for (int i = 0; i < hranyPolygonu.size() - 1; i++) {
				for (int j = 0; j < hranyPolygonu.size() - 1 - i; j++) {
					if (hranyPolygonu[j].prvyBod.y() > hranyPolygonu[j + 1].prvyBod.y()) {
						hranyPolygonu.swapItemsAt(j, j + 1);
					}
				}
			}
		}
		struct Edge {
			int deltaY = 0;
			double x = 0.0;
			double w = 0.0;
			void napln(int y, int xk, double w2) {
				deltaY = y;
				x = xk;
				w = w2;
			}
		};
		int yMin = hranyPolygonu[0].prvyBod.y();
		int yMax = hranyPolygonu[hranyPolygonu.size() - 1].druhyBod.y();

		QVector<QVector<Edge>> tabulkaHran;
		tabulkaHran.resize(yMax - yMin);
		for (int j = 0; j < yMax - yMin; j++) {
			for (int i = 0; i < hranyPolygonu.size(); i++) {
				if (hranyPolygonu[i].prvyBod.y() - yMin == j) {
					int delta = hranyPolygonu[i].druhyBod.y() - hranyPolygonu[i].prvyBod.y();
					double ws = hranyPolygonu[i].w;
					double x2 = static_cast<double>(hranyPolygonu[i].prvyBod.x());
					Edge tempHrana;
					tempHrana.napln(delta, x2, ws);
					tabulkaHran[j].append(tempHrana);
				}
			}
		}
		int y = yMin;
		QVector<Edge> zozAktivHran;

		for (int i = 0; i < tabulkaHran.size(); i++) {
			if (tabulkaHran[i].isEmpty() == false) {
				for (int j = 0; j < tabulkaHran[i].size(); j++) {
					zozAktivHran.append(tabulkaHran[i][j]);
				}
			}
			//usporiadanie podla x
			for (int j = 0; j < zozAktivHran.size() - 1; j++) {
				for (int k = 0; k < zozAktivHran.size() - 1 - j; k++) {
					if (zozAktivHran[k].x > zozAktivHran[k + 1].x) {
						zozAktivHran.swapItemsAt(k, k + 1);
					}
				}
			}

			for (int j = 0; j < zozAktivHran.size(); j++) {
				if (static_cast<int>(zozAktivHran[j].x + 0.5) != static_cast<int>(zozAktivHran[(j + 1) % zozAktivHran.size()].x + 0.5)) {
					for (int k = static_cast<int>(zozAktivHran[j].x + 0.5); k < static_cast<int>(zozAktivHran[(j + 1) % zozAktivHran.size()].x + 0.5); k++) {
						if (zHodnoty[k][y] < zValue) {
							farbaPlatna[k][y] = fillK;
							zHodnoty[k][y] = zValue;
						}
					}
				}
			}
			for (int j = 0; j < zozAktivHran.size(); ) {
				if (zozAktivHran[j].deltaY == 0) {
					zozAktivHran.removeAt(j);
				}
				else j++;
			}
			for (int j = 0; j < zozAktivHran.size(); j++) {
				zozAktivHran[j].deltaY = zozAktivHran[j].deltaY - 1;
				zozAktivHran[j].x = zozAktivHran[j].x + zozAktivHran[j].w;
			}
			y = y + 1;
		}
	}
	for (int i = 0; i < bodyK.size()-1; i++) {
		drawUseckaBrasenham(bodyK[i], bodyK[i + 1], outlineK, zValue);
	}
	drawUseckaBrasenham(bodyK[0], bodyK[bodyK.size()-1], outlineK, zValue);
}

void ImageViewer::drawBrezier(QVector<QPoint> bodyK, QColor outlineK, int zValue)
{
	QVector<QVector<QPointF>> poleBodov;
	poleBodov.resize(bodyK.size());
	for (int i = 0; i < poleBodov.size(); i++) {
		poleBodov[i].resize(poleBodov.size() - i);
	}
	for (int i = 0; i < bodyK.size(); i++) {
		poleBodov[0][i] = bodyK[i];
	}
	double deltaT = 0.01;
	double t = deltaT;
	QPointF q0 = bodyK[0];
	QPointF q1;

	while (t < 1) {
		for (int i = 1; i < bodyK.size(); i++) {
			for (int j = 0; j < bodyK.size() - i; j++) {
				poleBodov[i][j] = (1 - t) * poleBodov[i - 1][j] + t * poleBodov[i - 1][j + 1];
			}
		}
		q1 = poleBodov[bodyK.size() - 1][0];
		QPoint a0 = QPoint(static_cast<int>(q0.x() + 0.5), static_cast<int>(q0.y() + 0.5));
		QPoint a1 = QPoint(static_cast<int>(q1.x() + 0.5), static_cast<int>(q1.y() + 0.5));
		
		drawUseckaBrasenham(a0, a1, outlineK, zValue);
		q0 = q1;
		t = t + deltaT;

	}
	
		QPoint a0 = QPoint(static_cast<int>(q0.x() + 0.5), static_cast<int>(q0.y() + 0.5));
		drawUseckaBrasenham(a0, bodyK[bodyK.size() - 1], outlineK, zValue);

	
}

void ImageViewer::drawUseckaBrasenham(QPoint start, QPoint end, QColor outlineK, int zValue)
{
	ViewerWidget* w = getCurrentViewerWidget();
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye;

	dx = end.x() - start.x();
	dy = end.y() - start.y();
	dx1 = fabs(dx);
	dy1 = fabs(dy);

	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = start.x();
			y = start.y();
			xe = end.x();
		}
		else {
			x = end.x();
			y = end.y();
			xe = start.x();
		}
		if (x >= 0 && y >= 0 && x < w->getImgWidth() && y < w->getImgHeight()) {
			if (zHodnoty[x][y] <= zValue) {
				farbaPlatna[x][y] = outlineK;
				zHodnoty[x][y] = zValue;
			}
		}
		while (x < xe) {
			x = x + 1;
			if (px < 0) {
				px = px + 2 * dy1;
			}
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					y = y + 1;
				}
				else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			if (x >= 0 && y >= 0 && x < w->getImgWidth() && y < w->getImgHeight()) {
				if (zHodnoty[x][y] <= zValue) {
					farbaPlatna[x][y] = outlineK;
					zHodnoty[x][y] = zValue;
				}
			}

		}

	}
	else {
		if (dy >= 0) {
			x = start.x();
			y = start.y();
			ye = end.y();
		}
		else {
			x = end.x();
			y = end.y();
			ye = start.y();
		}
		if (x >= 0 && y >= 0 && x < w->getImgWidth() && y < w->getImgHeight()) {
			if (zHodnoty[x][y] <= zValue) {
				farbaPlatna[x][y] = outlineK;
				zHodnoty[x][y] = zValue;
			}
		}
		while (y < ye) {
			y = y + 1;
			if (py <= 0) {
				py = py + 2 * dx1;
			}
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					x = x + 1;
				}
				else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			if (x >= 0 && y >= 0 && x < w->getImgWidth() && y < w->getImgHeight()) {
				if (zHodnoty[x][y] <= zValue) {
					farbaPlatna[x][y] = outlineK;
					zHodnoty[x][y] = zValue;
				}
			}
		}
	}
}

QVector<QPoint> ImageViewer::orezBody(QVector<QPoint> bodyK)
{
	ViewerWidget* w = getCurrentViewerWidget();
	
	QVector<QPoint> orezBody = bodyK;
	
	int xMin = 0;
	orezBody = algoritmusSH(orezBody, xMin);

	for (int i = 0; i < orezBody.size(); i++) {
		int x = orezBody[i].y();
		int y = orezBody[i].x();
		orezBody[i].setX(x);
		orezBody[i].setY(-y);
	}
	xMin = 0;
	orezBody = algoritmusSH(orezBody, xMin);

	for (int j = 0; j < orezBody.size(); j++) {
		int x = orezBody[j].y();
		int y = orezBody[j].x();
		orezBody[j].setX(x);
		orezBody[j].setY(-y);
	}
	xMin = -1 * w->getImgWidth() + 1;
	orezBody = algoritmusSH(orezBody, xMin);

	for (int k = 0; k < orezBody.size(); k++) {
		int x = orezBody[k].y();
		int y = orezBody[k].x();
		orezBody[k].setX(x);
		orezBody[k].setY(-y);
	}
	xMin = -1 * w->getImgHeight() + 1;
	orezBody = algoritmusSH(orezBody, xMin);

	for (int l = 0; l < orezBody.size(); l++) {
		int x = orezBody[l].y();
		int y = orezBody[l].x();
		orezBody[l].setX(x);
		orezBody[l].setY(-y);
	}
	return orezBody;
}

QVector<QPoint> ImageViewer::algoritmusSH(QVector<QPoint> bodyK, int xMin)
{
	QVector<QPoint> bodyOrezanehoPolygonu;

	QPoint sPoint;
	QPoint p1 = QPoint(0, 0);
	sPoint = bodyK[bodyK.size() - 1];
	for (int i = 0; i < bodyK.size(); i++) {
		if (bodyK[i].x() >= xMin) {
			if (sPoint.x() >= xMin) {
				bodyOrezanehoPolygonu.append(bodyK[i]);
			}
			else {
				double y = sPoint.y() + ((double)xMin - sPoint.x()) * (((double)bodyK[i].y() - sPoint.y()) / ((double)bodyK[i].x() - sPoint.x()));
				p1.setX(xMin);
				p1.setY(static_cast<int>(y));
				bodyOrezanehoPolygonu.append(p1);
				bodyOrezanehoPolygonu.append(bodyK[i]);

			}
		}
		else {
			if (sPoint.x() >= xMin) {
				double y = sPoint.y() + ((double)xMin - sPoint.x()) * (((double)bodyK[i].y() - sPoint.y()) / ((double)bodyK[i].x() - sPoint.x()));
				p1.setX(xMin);
				p1.setY(static_cast<int>(y));
				bodyOrezanehoPolygonu.append(p1);
			}

		}
		sPoint = bodyK[i];
	}
	bodyK.clear();
	bodyK = bodyOrezanehoPolygonu;
	return bodyOrezanehoPolygonu;
}

void ImageViewer::vyplnPlatno()
{
	ViewerWidget* w = getCurrentViewerWidget();
	int sirka = w->getImgWidth();
	int vyska = w->getImgHeight();
	zHodnoty.resize(sirka);
	for (int i = 0; i < zHodnoty.size(); i++) {
		zHodnoty[i].resize(vyska);
	}
	farbaPlatna.resize(sirka);
	for (int i = 0; i < farbaPlatna.size(); i++) {
		farbaPlatna[i].resize(vyska);
	}
	for (int i = 0; i < sirka; i++) {
		for (int j = 0; j < vyska; j++) {
			zHodnoty[i][j] = -100;
			farbaPlatna[i][j] = Qt::white;
		}
	}
	for (int i = 0; i < objekty.size(); i++) {
		if (objekty[i].getObjectType() == 1) {
			drawUsecka(objekty[i].getBody(), objekty[i].getOutline(), objekty[i].getZ());
		}
		if (objekty[i].getObjectType() == 2) {
			drawRectangle(objekty[i].getBody(), objekty[i].getFill(), objekty[i].getOutline(), objekty[i].getisFilled(), objekty[i].getZ());
		}
		if (objekty[i].getObjectType() == 3) {
			drawPolygon(objekty[i].getBody(), objekty[i].getFill(), objekty[i].getOutline(), objekty[i].getisFilled(), objekty[i].getZ());
		}
		if (objekty[i].getObjectType() == 4) {
			drawCircle(objekty[i].getBody(), objekty[i].getOutline(), objekty[i].getZ());
		}
		if (objekty[i].getObjectType() == 5) {
			drawBrezier(objekty[i].getBody(), objekty[i].getOutline(), objekty[i].getZ());
		}
	}
	for (int i = 0; i < sirka; i++) {
		for (int j = 0; j < vyska; j++) {
			w->setPixel(i, j, farbaPlatna[i][j]);
			w->update();
		}
	}
}

//ViewerWidget Events
bool ImageViewer::ViewerWidgetEventFilter(QObject* obj, QEvent* event)
{
	ViewerWidget* w = static_cast<ViewerWidget*>(obj);

	if (!w) {
		return false;
	}

	if (event->type() == QEvent::MouseButtonPress) {
		ViewerWidgetMouseButtonPress(w, event);
	}
	else if (event->type() == QEvent::MouseButtonRelease) {
		ViewerWidgetMouseButtonRelease(w, event);
	}
	else if (event->type() == QEvent::MouseMove) {
		ViewerWidgetMouseMove(w, event);
	}
	else if (event->type() == QEvent::Leave) {
		ViewerWidgetLeave(w, event);
	}
	else if (event->type() == QEvent::Enter) {
		ViewerWidgetEnter(w, event);
	}
	else if (event->type() == QEvent::Wheel) {
		ViewerWidgetWheel(w, event);
	}

	return QObject::eventFilter(obj, event);
}
void ImageViewer::ViewerWidgetMouseButtonPress(ViewerWidget* w, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	if (ui->kreslenie->isChecked()) {
		if (e->button() == Qt::LeftButton) {
			points.append(e->pos());
			pointsCount = pointsCount + 1;
		}
		if (e->button() == Qt::RightButton) {
			ViewerWidget* w = getCurrentViewerWidget();
			QColor fill = w->fillColor;
			QColor outline = w->outlineColor;
			int type = 0;
			int filling = 0;
			if (ui->rectangle->isChecked()) {
				type = 2;
				points.resize(2);
				pointsCount = 4;
				QPoint bod3 = QPoint(points[0].x(), points[1].y());
				points.append(bod3);
				QPoint bod4 = QPoint(points[1].x(), points[0].y());
				points.append(bod4);
				points.swapItemsAt(1, 2);
				if (ui->vyplnButton->isChecked()) {
					filling = 1;
				}
			}
			if (ui->krivka->isChecked()) {
				type = 5;
			}
			if (ui->usecka->isChecked()) {
				type = 1;
				points.resize(2);
				pointsCount = 2;
			}
			if (ui->polygon->isChecked()) {
				type = 3;
				if (ui->vyplnButton->isChecked()) {
					filling = 1;
				}
			}
			if (ui->kruznica->isChecked()) {
				type = 4;
				points.resize(2);
				pointsCount = 2;
			}
			GeomObject tempObject(type, points, fill, outline, layer, points.size(), layer, filling);
			layer = layer + 1;
			objekty.append(tempObject);
			points.resize(0);
			if (objekty.size() > 1) {
				ui->layer->setMaximum(ui->layer->maximum() + 1);
			}
			vyplnPlatno();
		}
	}
	if (ui->posuvanie->isChecked()) {
		posuvaj = true;
		startpoint = e->pos();
	}
}
void ImageViewer::ViewerWidgetMouseButtonRelease(ViewerWidget* w, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	if (posuvaj == true) {
		posuvaj = false;
	}
}
void ImageViewer::ViewerWidgetMouseMove(ViewerWidget* w, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	if (posuvaj == true) {
		newPoint = e->pos();
		int dx = newPoint.x() - startpoint.x();
		int dy = newPoint.y() - startpoint.y();
		QVector<QPoint> bodyObjektu = objekty[ui->layer->value()].getBody();

		for (int i = 0; i < objekty[ui->layer->value()].getBody().size(); i++) {
			bodyObjektu[i].setX(bodyObjektu[i].x() + dx);
			bodyObjektu[i].setY(bodyObjektu[i].y() + dy);
		}
		objekty[ui->layer->value()].setBody(bodyObjektu);
		startpoint = newPoint;
		vyplnPlatno();
	}
}
void ImageViewer::ViewerWidgetLeave(ViewerWidget* w, QEvent* event)
{
}
void ImageViewer::ViewerWidgetEnter(ViewerWidget* w, QEvent* event)
{
}
void ImageViewer::ViewerWidgetWheel(ViewerWidget* w, QEvent* event)
{
	QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
}

//ImageViewer Events
void ImageViewer::closeEvent(QCloseEvent* event)
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No))
	{
		event->accept();
	}
	else {
		event->ignore();
	}
}

//Image functions
void ImageViewer::openNewTabForImg(ViewerWidget* vW)
{
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidget(vW);

	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	vW->setObjectName("ViewerWidget");
	vW->installEventFilter(this);

	QString name = vW->getName();

	ui->tabWidget->addTab(scrollArea, name);
}
bool ImageViewer::openImage(QString filename)
{
	QFileInfo fi(filename);

	QString name = fi.baseName();
	openNewTabForImg(new ViewerWidget(name, QSize(0, 0)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

	ViewerWidget* w = getCurrentViewerWidget();

	QImage loadedImg(filename);
	return w->setImage(loadedImg);
}
bool ImageViewer::saveImage(QString filename)
{
	QFileInfo fi(filename);
	QString extension = fi.completeSuffix();
	ViewerWidget* w = getCurrentViewerWidget();

	QImage* img = w->getImage();
	return img->save(filename, extension.toStdString().c_str());
}
void ImageViewer::clearImage()
{
	ViewerWidget* w = getCurrentViewerWidget();
	w->clear();
}
void ImageViewer::setBackgroundColor(QColor color)
{
	ViewerWidget* w = getCurrentViewerWidget();
	w->clear(color);
}

//Slots

//Tabs slots
void ImageViewer::on_tabWidget_tabCloseRequested(int tabId)
{
	ViewerWidget* vW = getViewerWidget(tabId);
	delete vW; //vW->~ViewerWidget();
	ui->tabWidget->removeTab(tabId);
}
void ImageViewer::on_actionRename_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image is opened.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	ViewerWidget* w = getCurrentViewerWidget();
	bool ok;
	QString text = QInputDialog::getText(this, QString("Rename image"), tr("Image name:"), QLineEdit::Normal, w->getName(), &ok);
	if (ok && !text.trimmed().isEmpty())
	{
		w->setName(text);
		ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), text);
	}
}

//Image slots
void ImageViewer::on_actionNew_triggered()
{
	newImgDialog = new NewImageDialog(this);
	connect(newImgDialog, SIGNAL(accepted()), this, SLOT(newImageAccepted()));
	newImgDialog->exec();
}
void ImageViewer::newImageAccepted()
{
	NewImageDialog* newImgDialog = static_cast<NewImageDialog*>(sender());

	int width = newImgDialog->getWidth();
	int height = newImgDialog->getHeight();
	QString name = newImgDialog->getName();
	openNewTabForImg(new ViewerWidget(name, QSize(width, height)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void ImageViewer::openNewImage(int width, int height)
{
	NewImageDialog* newImgDialog = static_cast<NewImageDialog*>(sender());
	QString name = "new_image";
	openNewTabForImg(new ViewerWidget(name, QSize(width, height)));
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void ImageViewer::on_actionOpen_triggered()
{
	QString folder = settings.value("folder_img_load_path", "").toString();

	QString fileFilter = "Image data (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm .*xbm .* xpm);;All files (*)";
	QString fileName = QFileDialog::getOpenFileName(this, "Load image", folder, fileFilter);
	if (fileName.isEmpty()) { return; }

	QFileInfo fi(fileName);
	settings.setValue("folder_img_load_path", fi.absoluteDir().absolutePath());

	if (!openImage(fileName)) {
		msgBox.setText("Unable to open image.");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
}
void ImageViewer::on_actionSave_as_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image to save.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	QString folder = settings.value("folder_img_save_path", "").toString();

	ViewerWidget* w = getCurrentViewerWidget();

	QString fileFilter = "Image data (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm .*xbm .* xpm);;All files (*)";
	QString fileName = QFileDialog::getSaveFileName(this, "Save image", folder + "/" + w->getName(), fileFilter);
	if (fileName.isEmpty()) { return; }

	QFileInfo fi(fileName);
	settings.setValue("folder_img_save_path", fi.absoluteDir().absolutePath());

	if (!saveImage(fileName)) {
		msgBox.setText("Unable to save image.");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
	else {
		msgBox.setText(QString("File %1 saved.").arg(fileName));
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
	}
}
void ImageViewer::on_actionClear_triggered()
{
	if (!isImgOpened()) {
		msgBox.setText("No image is opened.");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		return;
	}
	clearImage();
}
void ImageViewer::on_actionSet_background_color_triggered()
{
	QColor backgroundColor = QColorDialog::getColor(Qt::white, this, "Select color of background");
	if (backgroundColor.isValid()) {
		setBackgroundColor(backgroundColor);
	}
}

void ImageViewer::on_zHore_clicked()
{
	if (ui->layer->value() < objekty.size() - 1) {
		objekty.swapItemsAt(ui->layer->value(), ui->layer->value() + 1);
		int z1 = objekty[ui->layer->value()].getZ();
		int z2 = objekty[ui->layer->value()+1].getZ();
		objekty[ui->layer->value()].setZ(z2);
		objekty[ui->layer->value() + 1].setZ(z1);
		vyplnPlatno();
	}
}
void ImageViewer::on_zDole_clicked() {
	if (ui->layer->value() > 0) {
		objekty.swapItemsAt(ui->layer->value(), ui->layer->value() - 1);
		int z1 = objekty[ui->layer->value()].getZ();
		int z2 = objekty[ui->layer->value() - 1].getZ();
		objekty[ui->layer->value()].setZ(z2);
		objekty[ui->layer->value() - 1].setZ(z1);
		vyplnPlatno();
	}
}

void ImageViewer::on_actionZmenVypln_triggered()
{
	ViewerWidget* w = getCurrentViewerWidget();
	QColor fillC = QColorDialog::getColor(Qt::white, this);
	if (fillC.isValid()) {
		w->fillColor = fillC;
	}
}

void ImageViewer::on_actionZmenOkraj_triggered()
{
	ViewerWidget* w = getCurrentViewerWidget();
	QColor outlineC = QColorDialog::getColor(Qt::white, this);
	if (outlineC.isValid()) {
		w->outlineColor = outlineC;
	}
}

void ImageViewer::on_actionNacitaj_triggered()
{
	objekty.resize(0);
	QFile file = QFileDialog::getOpenFileName(this);
	QVector<QString> riadky;
	if (file.open(QFile::ReadOnly)) {
		QTextStream in(&file);
		while (!in.atEnd()) {
			riadky.append(in.readLine());
		}
		file.close();
	}
	QStringList rozmery = riadky[0].split(' ');
	int sirka = rozmery[0].toInt();
	int vyska = rozmery[1].toInt();
	openNewImage(sirka, vyska);
	QVector<QString> objInfo;
	for (int i = 1; i < riadky.size(); i++) {
		objInfo.append(riadky[i]);
	}
	for (int i = 0; i < objInfo.size(); i++) {
		QStringList info = objInfo[i].split(' ');
		int zVal = info[0].toInt();
		int lay = info[1].toInt();
		int obTyp = info[2].toInt();
		int isFill = info[3].toInt();
		int pointCount = info[6].toInt();

		QStringList fillC = info[4].split(';');
		QStringList outlineC = info[5].split(';');
		QColor fillCol = QColor(fillC[0].toInt(), fillC[1].toInt(), fillC[2].toInt());
		QColor outlineCol = QColor(outlineC[0].toInt(), outlineC[1].toInt(), outlineC[2].toInt());
		QVector<QPoint> bodyTemp;
		for (int j = 0; j < pointCount; j++) {
			QStringList bodXY = info[7 + j].split(';');
			int x1 = bodXY[0].toInt();
			int y1 = bodXY[1].toInt();
			QPoint bod1 = QPoint(x1, y1);
			bodyTemp.append(bod1);
		}
		GeomObject objekt1(obTyp, bodyTemp, fillCol, outlineCol, zVal, pointCount, lay, isFill);
		objekty.append(objekt1);
		ui->layer->setMaximum(ui->layer->maximum() + 1);

	}
	vyplnPlatno();
}

void ImageViewer::on_actionUloz_triggered()
{
	ViewerWidget* w = getCurrentViewerWidget();
	QString fileName = QFileDialog::getSaveFileName(this, "Save File","", "Text files (*.txt)");
	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QTextStream stream(&file);
		stream.setCodec("UTF-8");
		stream << w->getImgWidth() << ' ' << w->getImgHeight() << '\n';
		for (int i = 0; i < objekty.size(); i++) {
			stream << objekty[i].getZ() << ' ' << objekty[i].getLayer() << ' ' << objekty[i].getObjectType() << ' ';
			stream << objekty[i].getisFilled() << ' ';
			stream << objekty[i].getFill().red() << ';' << objekty[i].getFill().green() << ';' << objekty[i].getFill().blue() << ' ';
			stream << objekty[i].getOutline().red() << ';' << objekty[i].getOutline().green() << ';' << objekty[i].getOutline().blue() << ' ';
			stream << objekty[i].getPointCount() << ' ';
			QVector<QPoint> bodyT = objekty[i].getBody();
			for (int j = 0; j < objekty[i].getBody().size(); j++) {
				stream << bodyT[j].x() << ';' << bodyT[j].y() << ' ';

			}
			stream << '\n';
		}
	}
}

void ImageViewer::on_skaluj_clicked()
{
	if (objekty[ui->layer->value()].getObjectType() == 1 || objekty[ui->layer->value()].getObjectType() == 4) {
		QVector<QPoint> bodyScale = objekty[ui->layer->value()].getBody();
		bodyScale[1].setX(static_cast<int>((bodyScale[1].x() - bodyScale[0].x())* ui->koefX->value()) + bodyScale[0].x());
		bodyScale[1].setY(static_cast<int>((bodyScale[1].y() - bodyScale[0].y()) * ui->koefY->value()) + bodyScale[0].y());
		objekty[ui->layer->value()].setBody(bodyScale);
	}
	else {
		QVector<QPoint> bodyScale = objekty[ui->layer->value()].getBody();
		for (int i = 0; i < bodyScale.size(); i++) {
			bodyScale[i].setX(static_cast<int>((bodyScale[i].x() - bodyScale[0].x()) * ui->koefX->value()) + bodyScale[0].x());
			bodyScale[i].setY(static_cast<int>((bodyScale[i].y() - bodyScale[0].y()) * ui->koefX->value()) + bodyScale[0].y());
			
		}
		objekty[ui->layer->value()].setBody(bodyScale);
	}
	vyplnPlatno();
}

void ImageViewer::on_otoc_clicked()
{
	if (objekty[ui->layer->value()].getObjectType() == 1) {
		QPoint prvyBod = objekty[ui->layer->value()].getBody()[0];
		QPoint druhyBod = objekty[ui->layer->value()].getBody()[1];
		QPoint bod2;
		double x;
		double y;
		int angle = ui->spinBox->value();
		double rad = angle * M_PI / 180;
		int dx = druhyBod.x() - prvyBod.x();
		int dy = druhyBod.y() - prvyBod.y();

		x = dx * cos(rad) - dy * sin(rad) + prvyBod.x();
		y = dx * sin(rad) + dy * cos(rad) + prvyBod.y();
		bod2.setX(static_cast<int>(x + 0.5));
		bod2.setY(static_cast<int>(y + 0.5));
		QVector<QPoint> otocBody;
		otocBody.append(prvyBod);
		otocBody.append(bod2);
		objekty[ui->layer->value()].setBody(otocBody);
	}
	if (objekty[ui->layer->value()].getObjectType() == 2 || objekty[ui->layer->value()].getObjectType() == 3 || objekty[ui->layer->value()].getObjectType() == 5) {
		QVector<QPoint> bodyPolygonu = objekty[ui->layer->value()].getBody();
		double x;
		double y;
		int angle = ui->spinBox->value();
		double rad = angle * M_PI / 180;
		QVector<QPoint> bodyNovehoPolygonu = bodyPolygonu;
		for (int i = 0; i < bodyPolygonu.size(); i++) {
			int dx = bodyPolygonu[i].x() - bodyPolygonu[0].x();
			int dy = bodyPolygonu[i].y() - bodyPolygonu[0].y();

			x = dx * cos(rad) - dy * sin(rad) + bodyPolygonu[0].x();
			y = dx * sin(rad) + dy * cos(rad) + bodyPolygonu[0].y();
			bodyNovehoPolygonu[i].setX(static_cast<int>(x + 0.5));
			bodyNovehoPolygonu[i].setY(static_cast<int>(y + 0.5));

		}
		objekty[ui->layer->value()].setBody(bodyNovehoPolygonu);
	}
	vyplnPlatno();
}

void ImageViewer::on_changeFill_clicked()
{
	//ViewerWidget* w = getCurrentViewerWidget();
	QColor fillC = QColorDialog::getColor(Qt::white, this);
	if (fillC.isValid()) {
		objekty[ui->layer->value()].setFill(fillC);
	}
	vyplnPlatno();
}

void ImageViewer::on_changeOutline_clicked()
{
	//ViewerWidget* w = getCurrentViewerWidget();
	QColor outlineC = QColorDialog::getColor(Qt::white, this);
	if (outlineC.isValid()) {
		objekty[ui->layer->value()].setOutline(outlineC);
	}
	vyplnPlatno();
}

void ImageViewer::on_setIsFilled_clicked()
{
	ViewerWidget* w = getCurrentViewerWidget();
	if (objekty[ui->layer->value()].getObjectType() == 2 || objekty[ui->layer->value()].getObjectType() == 3) {
		objekty[ui->layer->value()].setIsFill();
		objekty[ui->layer->value()].setFill(w->fillColor);
	}
	vyplnPlatno();
}

