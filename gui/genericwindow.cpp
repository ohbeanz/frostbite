#include "genericwindow.h"

GenericWindow::GenericWindow(QWidget *parent) : QPlainTextEdit(parent) {
    mainWindow = (MainWindow*)parent;
    settings = new GeneralSettings();
    wm = mainWindow->getWindowManager();
    snapshot = new Snapshot(this);

    this->buildContextMenu();
    this->loadSettings();

    this->setFocusPolicy(Qt::NoFocus);
    this->setReadOnly(true);
    this->setUndoRedoEnabled(false);
    this->document()->setMaximumBlockCount(1000);

    connect(this, SIGNAL(copyAvailable(bool)), this, SLOT(enableCopy(bool)));
}

void GenericWindow::loadSettings() {
    QFont font = settings->dockWindowFont();
    this->setFont(font);
}

QColor GenericWindow::getBgColor() {
    return viewport()->palette().color(QPalette::Base);
}

QColor GenericWindow::getTextColor() {
    return viewport()->palette().color(QPalette::Text);
}

QTextDocument* GenericWindow::getDocument() {
    return this->document();
}

QString GenericWindow::getObjectName() {
    return this->objectName();
}

QPlainTextEdit* GenericWindow::getMainWindow() {
    return wm->getGameWindow();
}

void GenericWindow::buildContextMenu() {
    menu = new QMenu(this);

    copyAct = new QAction(tr("&Copy\t"), this);
    menu->addAction(copyAct);
    copyAct->setEnabled(false);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copySelected()));

    selectAct = new QAction(tr("&Select all\t"), this);
    menu->addAction(selectAct);
    connect(selectAct, SIGNAL(triggered()), this, SLOT(selectAll()));

    menu->addSeparator();

    saveAct = new QAction(tr("&Save\t"), this);
    menu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveAsHtml()));

    menu->addSeparator();

    clearAct = new QAction(tr("&Clear\t"), this);
    menu->addAction(clearAct);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));
}

void GenericWindow::saveAsHtml() {
    snapshot->save();
}

void GenericWindow::contextMenuEvent(QContextMenuEvent* event) {
    menu->exec(event->globalPos());
}

void GenericWindow::enableCopy(bool enabled) {
    copyAct->setEnabled(enabled);
}

void GenericWindow::copySelected() {
    this->copy();

    QTextCursor textCursor = this->textCursor();
    textCursor.clearSelection();
    this->setTextCursor(textCursor);
}

GenericWindow::~GenericWindow() {
    delete copyAct;
    delete selectAct;
    delete clearAct;
    delete menu;
    delete settings;
}
