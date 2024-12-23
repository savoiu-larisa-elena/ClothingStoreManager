#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_hw.h"
#include <QWidget>
#include "services.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "validator.h"
#include <stack>
#include <QTableView>
#include <QAbstractListModel>
#include <QModelIndex>
#include <qheaderview.h>
#include "action.h"

class CoatListModel : public QAbstractListModel
{
private:
    Services& service;
public:
    explicit CoatListModel(Services& service) : service{ service } {};
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

class ShoppingBasketModel : public QAbstractListModel
{
private:
	Services& service;
public:
	explicit ShoppingBasketModel(Services& service) : service{ service } {};
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

class GUI: public QWidget
{
	Q_OBJECT
private:
    Services& service;
	Validator& validator;
    void initGUI();
    QLabel* title;
    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* exitButton;
    void showAdmin();
    void showUser();
    void connectSignalsAndSlots();
public:
    GUI(Services& service, Validator& validator) : service{ service }, validator{ validator } { initGUI(); };
    ~GUI() override;
};

class AdminGUI : public QWidget
{
	Q_OBJECT
private:
	QWidget* chartWindow;
    Services& service;
	Validator& validator;
	void initAdminGUI();
	QLabel* title;
	QListWidget* coatsList;
	QLineEdit* sizeEdit;
	QLineEdit* colourEdit;
	QLineEdit* quantityEdit;
	QLineEdit* priceEdit;
	QLineEdit* photographEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* exitButton;
	QPushButton* chartButton;
	void connectSignalsAndSlots();
	void populateList();
	void addCoat();
	void deleteCoat();
	void updateCoat();
	void displayChart();
	void undo();
	void redo();
	QPushButton* undoButton;
	QPushButton* redoButton;
public:
	explicit AdminGUI(Services& service, Validator& validator) : service{ service }, validator{ validator } { initAdminGUI(); };
	~AdminGUI() override;
};

class UserGUI : public QWidget
{
	Q_OBJECT
private:
	Services& service;
	Validator& validator;
	void initUserGUI();
	QLabel* title;
	QListWidget* coatsList;
	QListWidget* shoppingBasket;
	QLineEdit* sizeEdit;
	QPushButton* addButton;
	QPushButton* exitButton;
	QPushButton* showButton;
	QPushButton* xsButton;
	QPushButton* sButton;
	QPushButton* mButton;
	QPushButton* lButton;
	QPushButton* xlButton;
	QPushButton* xxlButton;
	QPushButton* allButton;
	QPushButton* prevButton;
	QPushButton* nextButton;
	void connectSignalsAndSlots();
	void addCoat();
	void populateShoppingBasket();
	void populateList(std::vector<Coat>* coats);
	void save();
	void showLinkClickedCoat();
	void showXsCoats();
	void showSCoats();
	void showMCoats();
	void showLCoats();
	void showXLCoats();
	void showXXLCoats();
	void showAllCoats();
	int currentBasketIndex;
public:
	explicit UserGUI(Services& service, Validator& validator) : service{ service }, validator{ validator } { initUserGUI(); };
	~UserGUI() override;
};

class SaveGUI : public QWidget
{
	Q_OBJECT
private:
	Services& service;
	Validator& validator;
	void initSaveGUI();
	QLabel* title;
	QPushButton* saveHtmlButton;
	QPushButton* saveCsvButton;
	QPushButton* exitButton;
	void connectSignalsAndSlots();
	void store_HTML();
	void store_CSV();

public:
	explicit SaveGUI(Services& service, Validator& validator) : service{ service }, validator{ validator } { initSaveGUI(); };
	~SaveGUI() override;
};

class UserGUI2 : public QWidget
{
	Q_OBJECT
//this class will display the coats with the next and previous buttons
private:
	QTableView* table;
	std::map<std::string, int> currentCoatIndexes;
	QListWidget* shoppingBasket;
	QPushButton* addButton;
	QPushButton* exitButton;
	QPushButton* xsButton;
	QPushButton* sButton;
	QPushButton* mButton;
	QPushButton* lButton;
	QPushButton* xlButton;
	QPushButton* xxlButton;
	QPushButton* allButton;
	Services& service;
	Validator& validator;
	void initUserGUI2();
	QLabel* title;
	QListWidget* coatsList;
	QPushButton* prevButton;
	QPushButton* nextButton;
	void connectSignalsAndSlots();
	void showCurrentCoat();
	void populateShoppingBasket();
	void showCoatsBySize(std::string size);
	void showXsCoats();
	void showSCoats();
	void showMCoats();
	void showLCoats();
	void showXLCoats();
	void showXXLCoats();
	void showAllCoats();
	void showNext();
	void showPrev();
	void populateList(std::vector<Coat>* coats);
	void addCoat();
	void save();
	int currentCoatIndex;
	void addCurrentCoatToBasket();
	void showLinkClickedCoat();
	QPushButton* viewButton;
	void viewTable();

public:
	explicit UserGUI2(Services& service, Validator& validator) : service{ service }, validator{ validator } { initUserGUI2(); };
	~UserGUI2() override;

};

class Model : public QAbstractTableModel {
	Q_OBJECT
private:
	Services& service;
public:
	explicit Model(Services& service) : service{ service } {};
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void update();
	~Model();
};