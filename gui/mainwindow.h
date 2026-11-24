#pragma once
#include <QMainWindow>
#include <memory>
#include "QueryEngine.h"
#include "ranker.h"
#include "Indexer.h"

class QLineEdit;
class QListWidget;
class QListWidgetItem;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void chooseFolder();
    void search();
    void openResult(QListWidgetItem *item);

private:
    std::unique_ptr<Indexer> indexer;
    std::unique_ptr<CustomTrie> trie;
        CustomSet<std::string> stopWords = makeStopWords();
    QLineEdit *searchBox;
    QListWidget *list;
    QLabel *status;
};