#include "hw.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	Validator validator;
	Services services = Services(new Repository(new std::vector<Coat>, validator), new std::vector<Coat>);
	GUI gui{ services, validator };
	gui.show();
    return a.exec();
}
