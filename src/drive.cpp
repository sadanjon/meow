#include "infra/meow_di.h"
#include "driver_runner.h"
#include "simple_driver.h"

int main(int argc, char **argv) {
	meow::initializeDI();

	meow::SimpleDriver driver;
	meow::DriverRunner driverRunner;

	return driverRunner.run(driver, argc, argv);
}

