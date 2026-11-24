#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *folderBtn = new QPushButton("Choose folder");
    folderBtn->setMinimumHeight(40);
    searchBox = new QLineEdit;
    searchBox->setPlaceholderText("Search...");
    list = new QListWidget;
    status = new QLabel("Pick a folder to index.");

    auto *box = new QVBoxLayout;
    box->addWidget(folderBtn);
    box->addWidget(searchBox);
    box->addWidget(list);
    box->addWidget(status);
    auto *central = new QWidget;
    central->setLayout(box);
    setCentralWidget(central);
    setWindowTitle("DeepFind");
    resize(600, 450);

    setStyleSheet(R"(
        QWidget { background: #FFFF99; color: #000000; font-size: 14px; }
        QPushButton { background: #FFAAC8; border: 2px solid #000000; padding: 6px; font-weight: bold; }
        QPushButton:hover { background: #FF93B9; }
               QLineEdit { background: #9FFCFD; border: 2px solid #000000; padding: 6px; }
        QListWidget { background: #FFAAC8; border: 2px solid #000000; padding: 6px; }
        QListWidget::item:selected { background: #FF93B9; color: #000000; }
        QLabel { background: #FFAAC8; border: 2px solid #000000; padding: 6px; }
    )");
    connect(folderBtn, &QPushButton::clicked, this, &MainWindow::chooseFolder);
    connect(searchBox, &QLineEdit::returnPressed, this, &MainWindow::search);
    connect(list, &QListWidget::itemDoubleClicked, this, &MainWindow::openResult);
}

void MainWindow::chooseFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, "Folder to search");
    if (dir.isEmpty()) return;

    status->setText("Indexing...");
    QApplication::processEvents();

    auto newIndexer = std::make_unique<Indexer>();
    if (!newIndexer->buildIndex(dir.toStdString(), stopWords)) {
        status->setText("Could not index that folder.");
        return;
    }
    indexer = std::move(newIndexer);
    trie = std::make_unique<CustomTrie>();
    buildTrie(*trie, *indexer);

    list->clear();
    status->setText(QString("%1 files, %2 words indexed")
                        .arg(indexer->get_files().size())
                        .arg(indexer->get_index().size()));
}

void MainWindow::search() {
    if (!indexer) { status->setText("Pick a folder first."); return; }
    std::string query = searchBox->text().toStdString();
    if (query.find_first_not_of(' ') == std::string::npos) return;

    CustomVector<SearchResult> results =
        rankResults(findCandidates(query, stopWords, *indexer));

    list->clear();
    for (int i = 0; i < results.size(); i++) {
        const FileInfo &f = indexer->get_files()[results[i].fileId];
        QString text = QString("%1\n   matched %2 term(s), score %3")
                           .arg(QString::fromStdString(f.path))
                           .arg(results[i].termsMatched)
                           .arg(results[i].score, 0, 'f', 2);
        auto *item = new QListWidgetItem(text, list);
        item->setData(Qt::UserRole, QString::fromStdString(f.path));
    }
    status->setText(QString("%1 result(s)").arg(results.size()));
}

void MainWindow::openResult(QListWidgetItem *item) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(item->data(Qt::UserRole).toString()));
}