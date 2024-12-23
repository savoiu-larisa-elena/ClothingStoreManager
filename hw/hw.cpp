#include "hw.h"
#include <qboxlayout.h>
#include <qdesktopservices.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <string>

int CoatListModel::rowCount(const QModelIndex& parent) const
{
	return this->service.get_size();
}

QVariant CoatListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	if (role == Qt::DisplayRole)
	{
		auto coats = this->service.get_all_products();
		auto coat = coats->at(row);
		return QString::fromStdString(coat.to_string());
	}
	return QVariant{};
}

int ShoppingBasketModel::rowCount(const QModelIndex& parent) const
{
	return this->service.get_shopping_basket()->size();
}

QVariant ShoppingBasketModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	if (role == Qt::DisplayRole)
	{
		auto coats = this->service.get_shopping_basket();
		auto coat = coats->at(row);
		return QString::fromStdString(coat.to_string());
	}
	return QVariant{};
}

void GUI::initGUI()
{
	//reads the products from the file
	this->service.read_from_file("products.txt");

	this->title = new QLabel{ "<3 TRENCH COAT STORE <3" };
	//change the colour of the background
	this->title->setStyleSheet("QLabel { background-color : pink; font-size : 25px; font-weight : bold; }");
	//changes the font
	this->title->setFont(QFont{ "Times New Roman" });
	this->adminButton = new QPushButton{ "Admin" };
	this->adminButton->setFont(QFont{ "Times New Roman", 17 });
	this->userButton = new QPushButton{ "User" };
	this->userButton->setFont(QFont{ "Times New Roman", 17 });
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setFont(QFont{ "Times New Roman", 17 });

	QVBoxLayout* layout = new QVBoxLayout{ this };
	layout->addWidget(this->title);
	layout->addWidget(this->adminButton);
	layout->addWidget(this->userButton);
	layout->addWidget(this->exitButton);

	this->connectSignalsAndSlots();
}

void GUI::showAdmin()
{
	AdminGUI* admin = new AdminGUI{ this->service, this->validator };
	admin->show();
}

void GUI::showUser()
{
	UserGUI2* user = new UserGUI2{ this->service, this->validator };
	user->show();
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &QWidget::close);
}

GUI::~GUI()
{
}

void AdminGUI::initAdminGUI()
{
	this->title = new QLabel{ "Admin" };
	//change the colour of the background
	this->title->setStyleSheet("QLabel { background-color : pink; font-size : 25px; font-weight : bold; }");
	//changes the font
	this->title->setFont(QFont{ "Times New Roman" });
	this->coatsList = new QListWidget{};
	this->sizeEdit = new QLineEdit{};
	this->colourEdit = new QLineEdit{};
	this->quantityEdit = new QLineEdit{};
	this->priceEdit = new QLineEdit{};
	this->photographEdit = new QLineEdit{};
	this->addButton = new QPushButton{ "Add" };
	this->addButton->setFont(QFont{ "Times New Roman", 17 });
	this->deleteButton = new QPushButton{ "Delete" };
	this->deleteButton->setFont(QFont{ "Times New Roman", 17 });
	this->updateButton = new QPushButton{ "Update" };
	this->updateButton->setFont(QFont{ "Times New Roman", 17 });
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setFont(QFont{ "Times New Roman", 17 });
	this->chartButton = new QPushButton{ "Chart" };
	this->chartButton->setFont(QFont{ "Times New Roman", 17 });
	this->undoButton = new QPushButton{ "Undo" };
	this->undoButton->setFont(QFont{ "Times New Roman", 17 });
	this->redoButton = new QPushButton{ "Redo" };
	this->redoButton->setFont(QFont{ "Times New Roman", 17 });

	//adding labels so the user knows what they are inputting
	QLabel* sizeLabel = new QLabel{ "Size: " };
	sizeLabel->setFont(QFont{ "Times New Roman", 15 });
	QLabel* colourLabel = new QLabel{ "Colour: " };
	colourLabel->setFont(QFont{ "Times New Roman", 15 });
	QLabel* quantityLabel = new QLabel{ "Quantity: " };
	quantityLabel->setFont(QFont{ "Times New Roman", 15 });
	QLabel* priceLabel = new QLabel{ "Price: " };
	priceLabel->setFont(QFont{ "Times New Roman", 15 });
	QLabel* photographLabel = new QLabel{ "Photograph: " };
	photographLabel->setFont(QFont{ "Times New Roman", 15 });

	QVBoxLayout* mainLayout = new QVBoxLayout{ this };
	mainLayout->addWidget(this->title);
	mainLayout->addWidget(this->coatsList);

	QGridLayout* formLayout = new QGridLayout{};
	formLayout->addWidget(sizeLabel, 0, 0);
	formLayout->addWidget(this->sizeEdit, 0, 1);
	formLayout->addWidget(colourLabel, 1, 0);
	formLayout->addWidget(this->colourEdit, 1, 1);
	formLayout->addWidget(quantityLabel, 2, 0);
	formLayout->addWidget(this->quantityEdit, 2, 1);
	formLayout->addWidget(priceLabel, 3, 0);
	formLayout->addWidget(this->priceEdit, 3, 1);
	formLayout->addWidget(photographLabel, 4, 0);
	formLayout->addWidget(this->photographEdit, 4, 1);

	mainLayout->addLayout(formLayout);

	mainLayout->addWidget(this->addButton);
	mainLayout->addWidget(this->deleteButton);
	mainLayout->addWidget(this->updateButton);
	mainLayout->addWidget(this->undoButton);
	mainLayout->addWidget(this->redoButton);
	mainLayout->addWidget(this->exitButton);
	mainLayout->addWidget(this->chartButton);

	this->connectSignalsAndSlots();
	this->populateList();
}



void AdminGUI::populateList()
{
	this->coatsList->clear();
	auto coats = this->service.get_all_products();
	for (auto& coat : *coats)
	{
		this->coatsList->addItem(QString::fromStdString(coat.to_string()));
	}
}

void AdminGUI::addCoat()
{
	std::string size = this->sizeEdit->text().toStdString();
	std::string colour = this->colourEdit->text().toStdString();
	int quantity = this->quantityEdit->text().toInt();
	float price = this->priceEdit->text().toFloat();
	std::string photograph = this->photographEdit->text().toStdString();

	this->service.add_product(size, colour, quantity, price, photograph);
	this->populateList();
	this->service.write_to_file("products.txt");
}

void AdminGUI::deleteCoat()
{
	int index = this->coatsList->currentIndex().row();
	auto coat = this->service.get_coat(index);
	this->service.delete_product(coat.get_size(), coat.get_colour(), coat.get_price(), coat.get_photograph());
	this->populateList();
	this->service.write_to_file("products.txt");
}

void AdminGUI::updateCoat()
{
	std::string size = this->sizeEdit->text().toStdString();
	std::string colour = this->colourEdit->text().toStdString();
	int quantity = this->quantityEdit->text().toInt();
	float price = this->priceEdit->text().toFloat();
	std::string photograph = this->photographEdit->text().toStdString();

	int index = this->coatsList->currentIndex().row();

	Coat coat = this->service.get_coat(index);

	this->service.update_product(coat, Coat{ size, colour, quantity, price, photograph });
	this->populateList();
	this->service.write_to_file("products.txt");
}

void AdminGUI::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addCoat);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteCoat);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateCoat);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &QWidget::close);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undo);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redo);
}

void AdminGUI::undo()
{
	this->service.adminUndo();
	this->populateList();
}

void AdminGUI::redo() {
	this->service.adminRedo();
	this->populateList();
}


void AdminGUI::displayChart()
{
	this->chartWindow = new QWidget{};
	this->chartWindow->setWindowTitle("Chart");
	this->chartWindow->resize(800, 600);

	// create the chart and chart view
	QChart* chart = new QChart();
	chart->setTitle("Quantities of Coats by Color");

	// create a bar series
	QBarSeries* series = new QBarSeries();

	// fetch coats data and aggregate quantities by color
	QList<QColor> colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan, Qt::darkMagenta, Qt::darkGray };
	std::vector<Coat>* coats = this->service.get_all_products();
	std::map<std::string, int> colorQuantities;
	for (auto coat : *coats) {
		colorQuantities[coat.get_colour()] += coat.get_quantity();
	}

	// create a bar set for each color and add to the series
	for (const auto& pair : colorQuantities) {
		QBarSet* set = new QBarSet(QString::fromStdString(pair.first));
		*set << pair.second;
		series->append(set);
	}

	// add the series to the chart
	chart->addSeries(series);

	// create the y-axis and add it to the chart
	QValueAxis* axisY = new QValueAxis();
	axisY->setTitleText("Quantity");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	// customize the chart view and set it as the central widget
	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	// create a layout for the chart window and add the chart view
	QVBoxLayout* layout = new QVBoxLayout{ chartWindow };
	layout->addWidget(chartView);

	// change the colours so is the same as the colour of the coats
	chartWindow->setStyleSheet("background-color: #ff0000;");
	chart->setBackgroundBrush(QBrush(QColor(242, 172, 185)));
	chart->setTheme(QChart::ChartThemeLight);
	chart->setAnimationOptions(QChart::SeriesAnimations);


	// show the chart window
	chartWindow->show();
}



AdminGUI::~AdminGUI()
{
}

void UserGUI::initUserGUI()
{
	this->title = new QLabel{ "User" };
	//change the colour of the background
	this->title->setStyleSheet("QLabel { background-color : pink; font-size : 25px; font-weight : bold; }");
	//changes the font
	this->title->setFont(QFont{ "Times New Roman" });
	this->coatsList = new QListWidget{};
	this->shoppingBasket = new QListWidget{};

	QVBoxLayout* layout = new QVBoxLayout{ this };
	layout->addWidget(this->title);
	layout->addWidget(this->coatsList);
	layout->addWidget(this->shoppingBasket);

	this->addButton = new QPushButton{ "Add" };
	this->addButton->setFont(QFont{ "Times New Roman", 17 });
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setFont(QFont{ "Times New Roman", 17 });
	this->showButton = new QPushButton{ "Show coat" };
	this->showButton->setFont(QFont{ "Times New Roman", 17 });
	this->xsButton = new QPushButton{ "Show XS" };
	this->xsButton->setFont(QFont{ "Times New Roman", 17 });
	this->sButton = new QPushButton{ "Show S" };
	this->sButton->setFont(QFont{ "Times New Roman", 17 });
	this->mButton = new QPushButton{ "Show M" };
	this->mButton->setFont(QFont{ "Times New Roman", 17 });
	this->lButton = new QPushButton{ "Show L" };
	this->lButton->setFont(QFont{ "Times New Roman", 17 });
	this->xlButton = new QPushButton{ "Show XL" };
	this->xlButton->setFont(QFont{ "Times New Roman", 17 });
	this->xxlButton = new QPushButton{ "Show XXL" };
	this->xxlButton->setFont(QFont{ "Times New Roman", 17 });
	this->allButton = new QPushButton{ "Show All" };
	this->allButton->setFont(QFont{ "Times New Roman", 17 });

	layout->addWidget(this->addButton);
	layout->addWidget(this->xsButton);
	layout->addWidget(this->sButton);
	layout->addWidget(this->mButton);
	layout->addWidget(this->lButton);
	layout->addWidget(this->xlButton);
	layout->addWidget(this->xxlButton);
	layout->addWidget(this->allButton);
	layout->addWidget(this->exitButton);

	this->connectSignalsAndSlots();
	this->populateList(this->service.get_all_products());
	this->populateShoppingBasket();

}

void UserGUI::populateShoppingBasket() {
	this->shoppingBasket->clear();
	auto coats = this->service.get_shopping_basket();
	for (auto& coat : *coats)
	{
		this->shoppingBasket->addItem(QString::fromStdString(coat.to_string()));
	}
}

void UserGUI::showXsCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("XS");
	populateList(coats);
}

void UserGUI::showSCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("S");
	populateList(coats);
}

void UserGUI::showMCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("M");
	populateList(coats);
}

void UserGUI::showLCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("L");
	populateList(coats);
}

void UserGUI::showXLCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("XL");
	populateList(coats);
}

void UserGUI::showXXLCoats()
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size("XXL");
	populateList(coats);
}

void UserGUI::showAllCoats()
{
	this->coatsList->clear();
	populateList(this->service.get_all_products());
}

void UserGUI::populateList(std::vector<Coat>* coats)
{
	this->coatsList->clear();
	int i = 0;
	for (auto& coat : *coats)
	{
		i++;
		std::string s = std::to_string(i);
		this->coatsList->addItem(QString::fromStdString(s) + ". " + QString::fromStdString(coat.to_string()));
	}
}

void UserGUI::showLinkClickedCoat() {
	QDesktopServices::openUrl(QUrl(QString::fromStdString(this->service.get_coat(this->coatsList->currentIndex().row()).get_photograph())));
}

void UserGUI::addCoat()
{
	int index = this->coatsList->currentIndex().row();
	this->service.add_to_shopping_basket(this->service.get_coat(index));
	this->populateShoppingBasket();
}

void UserGUI::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addCoat);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &UserGUI::save);
	QObject::connect(this->coatsList, &QListWidget::itemClicked, this, &UserGUI::showLinkClickedCoat);
	QObject::connect(this->xsButton, &QPushButton::clicked, this, &UserGUI::showXsCoats);
	QObject::connect(this->sButton, &QPushButton::clicked, this, &UserGUI::showSCoats);
	QObject::connect(this->mButton, &QPushButton::clicked, this, &UserGUI::showMCoats);
	QObject::connect(this->lButton, &QPushButton::clicked, this, &UserGUI::showLCoats);
	QObject::connect(this->xlButton, &QPushButton::clicked, this, &UserGUI::showXLCoats);
	QObject::connect(this->xxlButton, &QPushButton::clicked, this, &UserGUI::showXXLCoats);
	QObject::connect(this->allButton, &QPushButton::clicked, this, &UserGUI::showAllCoats);
}

void UserGUI::save()
{
	SaveGUI* save = new SaveGUI{ this->service, this->validator };
	save->show();
}

UserGUI::~UserGUI()
{
}

void SaveGUI::initSaveGUI()
{
	this->title = new QLabel{ "Shopping Basket Price: " };
	this->title->setText(QString::fromStdString("Shopping Basket Price: " + std::to_string(this->service.get_total_price())));
	//change the colour of the background
	this->title->setStyleSheet("QLabel { background-color : pink; font-size : 25px; font-weight : bold; }");
	//changes the font
	this->title->setFont(QFont{ "Times New Roman" });
	this->saveHtmlButton = new QPushButton{ "HTML" };
	this->saveHtmlButton->setFont(QFont{ "Times New Roman", 17 });
	this->saveCsvButton = new QPushButton{ "CSV" };
	this->saveCsvButton->setFont(QFont{ "Times New Roman", 17 });
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setFont(QFont{ "Times New Roman", 17 });

	QVBoxLayout* layout = new QVBoxLayout{ this };
	layout->addWidget(this->title);
	layout->addWidget(this->saveHtmlButton);
	layout->addWidget(this->saveCsvButton);
	layout->addWidget(this->exitButton);

	this->connectSignalsAndSlots();
}

void SaveGUI::connectSignalsAndSlots()
{
	QObject::connect(this->saveHtmlButton, &QPushButton::clicked, this, &SaveGUI::store_HTML);
	QObject::connect(this->saveCsvButton, &QPushButton::clicked, this, &SaveGUI::store_CSV);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, QApplication::closeAllWindows); //closes the whole application
}

void SaveGUI::store_HTML()
{
	this->service.set_type("html");
	this->service.store_HTML();
	//opens the file 
	system("start sb.html");
}

void SaveGUI::store_CSV()
{
	this->service.set_type("csv");
	this->service.store_CSV();
	//opens the file in notes
	system("start sb.csv");
}

SaveGUI::~SaveGUI()
{
}

void UserGUI2::initUserGUI2()
{
	this->title = new QLabel{ "Coats" };
	//change the colour of the background
	this->title->setStyleSheet("QLabel { background-color : pink; font-size : 25px; font-weight : bold; }");
	//changes the font
	this->title->setFont(QFont{ "Times New Roman" });
	this->coatsList = new QListWidget{};
	this->shoppingBasket = new QListWidget{};

	QVBoxLayout* layout = new QVBoxLayout{ this };
	layout->addWidget(this->title);
	layout->addWidget(this->coatsList);
	layout->addWidget(this->shoppingBasket);

	this->prevButton = new QPushButton{ "Previous" };
	this->prevButton->setFont(QFont{ "Times New Roman", 17 });
	this->nextButton = new QPushButton{ "Next" };
	this->nextButton->setFont(QFont{ "Times New Roman", 17 });
	this->addButton = new QPushButton{ "Add" };
	this->addButton->setFont(QFont{ "Times New Roman", 17 });
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setFont(QFont{ "Times New Roman", 17 });

	this->xsButton = new QPushButton{ "Show XS" };
	this->xsButton->setFont(QFont{ "Times New Roman", 17 });
	this->sButton = new QPushButton{ "Show S" };
	this->sButton->setFont(QFont{ "Times New Roman", 17 });
	this->mButton = new QPushButton{ "Show M" };
	this->mButton->setFont(QFont{ "Times New Roman", 17 });
	this->lButton = new QPushButton{ "Show L" };
	this->lButton->setFont(QFont{ "Times New Roman", 17 });
	this->xlButton = new QPushButton{ "Show XL" };
	this->xlButton->setFont(QFont{ "Times New Roman", 17 });
	this->xxlButton = new QPushButton{ "Show XXL" };
	this->xxlButton->setFont(QFont{ "Times New Roman", 17 });
	this->allButton = new QPushButton{ "Show All" };
	this->allButton->setFont(QFont{ "Times New Roman", 17 });

	this->viewButton = new QPushButton{ "View" };
	this->viewButton->setFont(QFont{ "Times New Roman", 17 });

	layout->addWidget(this->prevButton);
	layout->addWidget(this->nextButton);
	layout->addWidget(this->addButton);
	layout->addWidget(this->xsButton);
	layout->addWidget(this->sButton);
	layout->addWidget(this->mButton);
	layout->addWidget(this->lButton);
	layout->addWidget(this->xlButton);
	layout->addWidget(this->xxlButton);
	layout->addWidget(this->allButton);
	layout->addWidget(this->viewButton);
	layout->addWidget(this->exitButton);

	this->currentCoatIndex = 0;  // initialize the current coat index

	this->connectSignalsAndSlots();
	this->showCurrentCoat();
	this->populateShoppingBasket();
}

void UserGUI2::populateShoppingBasket()
{
	this->shoppingBasket->clear();
	auto coats = this->service.get_shopping_basket();
	for (auto& coat : *coats)
	{
		this->shoppingBasket->addItem(QString::fromStdString(coat.to_string()));
	}
}

void UserGUI2::addCoat()
{
	if (nextButton->isEnabled() || prevButton->isEnabled())
	{
		addCurrentCoatToBasket();
	}
	else {
		QListWidgetItem* selectedItem = this->coatsList->currentItem();

		if (selectedItem) {
			QVariant data = selectedItem->data(Qt::UserRole);
			Coat coat = data.value<Coat>();

			this->service.add_to_shopping_basket(coat);
			populateShoppingBasket();
		}
	}

}


void UserGUI2::addCurrentCoatToBasket() {
	auto coats = this->service.get_all_products();
	if (coats->size() > 0 && this->currentCoatIndex >= 0 && this->currentCoatIndex < coats->size()) {
		auto& coat = coats->at(this->currentCoatIndex);
		this->service.add_to_shopping_basket(coat);
		populateShoppingBasket(); // Update the shopping basket display
	}
}

void UserGUI2::populateList(std::vector<Coat>* coats)
{
	this->coatsList->clear();
	int i = 0;
	for (auto& coat : *coats)
	{
		i++;
		std::string s = std::to_string(i);
		QString itemText = QString::fromStdString(s) + ". " + QString::fromStdString(coat.to_string());
		QListWidgetItem* item = new QListWidgetItem(itemText);
		// Set the Coat object as user data for the list item
		QVariant data;
		data.setValue(coat);
		item->setData(Qt::UserRole, data);
		this->coatsList->addItem(item);
	}
}

void UserGUI2::showCoatsBySize(std::string size)
{
	this->coatsList->clear();
	std::vector<Coat>* coats = this->service.get_products_of_size(size);
	populateList(coats);
}

void UserGUI2::showXsCoats()
{
	showCoatsBySize("XS");
}

void UserGUI2::showSCoats()
{
	showCoatsBySize("S");
}

void UserGUI2::showMCoats()
{
	showCoatsBySize("M");
}

void UserGUI2::showLCoats()
{
	showCoatsBySize("L");
}

void UserGUI2::showXLCoats()
{
	showCoatsBySize("XL");
}

void UserGUI2::showXXLCoats()
{
	showCoatsBySize("XXL");
}

void UserGUI2::showAllCoats()
{
	showCoatsBySize(" ");
}


void UserGUI2::showNext()
{
	this->currentCoatIndex++;
	if (this->currentCoatIndex == this->service.get_size())
		this->currentCoatIndex = 0;
	this->showCurrentCoat();
}

void UserGUI2::showPrev()
{
	this->currentCoatIndex--;
	if (this->currentCoatIndex == -1)
		this->currentCoatIndex = this->service.get_size() - 1;
	this->showCurrentCoat();
}
void UserGUI2::showCurrentCoat()
{
	this->coatsList->clear();
	auto coats = this->service.get_all_products();
	if (coats->size() > 0) {
		auto& coat = coats->at(this->currentCoatIndex);
		this->coatsList->addItem(QString::fromStdString(coat.to_string())); // add the current coat to the list
	}
}

void UserGUI2::viewTable()
{
	Model* model = new Model{ this->service };
	this->table = new QTableView{};
	this->table->setModel(model);
	this->table->resizeColumnsToContents();
	this->table->resizeRowsToContents();
	this->table->show();
}


void UserGUI2::connectSignalsAndSlots()
{
	QObject::connect(this->prevButton, &QPushButton::clicked, this, &UserGUI2::showPrev);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI2::showNext);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI2::addCoat);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &UserGUI2::save);
	QObject::connect(this->xsButton, &QPushButton::clicked, this, &UserGUI2::showXsCoats);
	QObject::connect(this->sButton, &QPushButton::clicked, this, &UserGUI2::showSCoats);
	QObject::connect(this->mButton, &QPushButton::clicked, this, &UserGUI2::showMCoats);
	QObject::connect(this->lButton, &QPushButton::clicked, this, &UserGUI2::showLCoats);
	QObject::connect(this->xlButton, &QPushButton::clicked, this, &UserGUI2::showXLCoats);
	QObject::connect(this->xxlButton, &QPushButton::clicked, this, &UserGUI2::showXXLCoats);
	QObject::connect(this->allButton, &QPushButton::clicked, this, &UserGUI2::showAllCoats);
	QObject::connect(this->coatsList, &QListWidget::itemClicked, this, &UserGUI2::showLinkClickedCoat);
	QObject::connect(this->viewButton, &QPushButton::clicked, this, &UserGUI2::viewTable);
}

void UserGUI2::save()
{
	SaveGUI* save = new SaveGUI{ this->service, this->validator };
	save->show();
}

void UserGUI2::showLinkClickedCoat() {
	QDesktopServices::openUrl(QUrl(QString::fromStdString(this->service.get_coat(this->coatsList->currentIndex().row()).get_photograph())));
}

UserGUI2::~UserGUI2()
{
}


int Model::rowCount(const QModelIndex& parent) const {
	return this->service.get_shopping_basket()->size();
}

int Model::columnCount(const QModelIndex& parent) const {
	return 4; 
}

QVariant Model::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();
	if (role == Qt::DisplayRole) {
		auto coats = this->service.get_shopping_basket();
		auto coat = coats->at(row);
		switch (column) {
		case 0:
			return QString::fromStdString(coat.get_size());
		case 1:
			return QString::fromStdString(coat.get_colour());
		case 2:
			return coat.get_quantity();
		case 3:
			return coat.get_price();
		default:
			return QVariant{};
		}
	}
	return QVariant{};
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Size");
			case 1:
				return QString("Color");
			case 2:
				return QString("Quantity");
			case 3:
				return QString("Price");
			case 4:
				return QString("Photograph");
			default:
				return QVariant{};
			}
		}
	}
	return QVariant{};
}

void Model::update() {
	emit layoutChanged(); // To notify the view that the model has been updated
}


Model::~Model()
{
}
