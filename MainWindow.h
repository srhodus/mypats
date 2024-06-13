// vim: tabstop=4 shiftwidth=4 noexpandtab
#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QAction>
#include <QStringList>
#include "Scene.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();
public slots:
	void showStatusMessage(const QString& str);
	void gameWon();
	void move(const QString& str);
private slots:
	void newRandomDeal();
	void newNumberedDeal();
	void undo();
#ifdef QT_DEBUG
	void debug();
#endif
	void exportState();
	void importState();
	void initDeal(int dealNo);
private:
	void createActions();
	void createMenus();
	void initModel(const QList<QStringList>& sl);
	void keyPressEvent(QKeyEvent *event);
	void leaveEvent(QEvent *event);
	void timerEvent(QTimerEvent *event);
	QChar findEmptyReserve() const;
	bool moveCascadeToCascade(int from, int to);
	bool moveCascadeToFoundations(int from);
	bool moveCascadeToReserves(int from, QChar to);
	bool moveReservesToCascade(QChar from, int to);
	bool moveReservesToFoundations(QChar from);
private:
	int width;
	int height;
	int timerId;
	Scene *scene;
	QGraphicsView *view;
	QAction *newRandomDealAction;
	QAction *newNumberedDealAction;
	QAction *serializeStateAction;
	QAction *undoAction;
#ifdef QT_DEBUG
	QAction *debugAction;
#endif
	QAction *exportAction;
	QAction *importAction;
	QMenu *fileMenu;
	QMenu *editMenu;
	QString keyMove;
};
