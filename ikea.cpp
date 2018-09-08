#include <sstream>
#include <cstring>
#include "ikea.h"
#include "Fabric.h"
#include "Candy.h"
#include "Kitchenware.h"
#include "MoviesAndBooks.h"
#include "TablesAndChairs.h"

/**
 * runs the program
 * @return 0 on success, -1 otherwise
 */
int main()
{
	auto *catalog = new ikea();
	int choice = 0;
	while (choice != 7)
	{
		catalog->printMenu();
		std::cin >> choice;
		switch (choice)
		{
			case 1:
				catalog->inputStock();
				break;
			case 2:
				catalog->findById(true);
				break;
			case 3:
				catalog->findByName();
				break;
			case 4:
				catalog->printById();
				break;
			case 5:
				catalog->printByName();
				break;
			case 6:
				catalog->sell();
				break;
			default:
				break;
		}
	}
	delete catalog;
	return 0;
}

/**
 * checks if the next line is a correct separator
 * @param inFile
 */
void ikea::checkSeparator(std::ifstream &inFile)
{
	string line;
	getline(inFile, line);
	if (line != SEPERATOR)
	{
		std::cerr << MISSING_SEPERATOR << std::endl;
	}
}


void ikea::printMenu()
{
	std::cout << "1. Input stock from file" << std::endl;
	std::cout << "2. Find item by catalog number" << std::endl;
	std::cout << "3. Find item by name" << std::endl;
	std::cout << "4. Print stock by catalog number" << std::endl;
	std::cout << "5. Print stock by name" << std::endl;
	std::cout << "6. Sell item" << std::endl;
	std::cout << "7. Exit" << std::endl;
}

/**
 * gets an item by id given
 * @param id
 * @return
 */
Item& ikea::getById(int id)
{
	for (auto &item: items)
	{
		if (item->getId() == id)
		{
			return *item;
		}
	}
}


void ikea::addItem(bool isInt)
{
	int id = 0;
	string name;
	double quantity = 0;
	double price = 0;
	try
	{
		id = std::stoi(input[0]);
		name = input[1];
		if (isInt)
		{
			quantity = std::stoi(input[2]);
		}
		else
		{
			quantity = std::stod(input[2]);
		}
		price = std::stod(input[3]);
		if (price < 0 || quantity < 0)
		{
			std::cerr << INVALID_INPUT << std::endl;
			return;
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << INVALID_INPUT << std::endl;
		return;
	}

	string to_check = findNameById(id);

	if (to_check == name)
	{
		Item &to_change = getById(id);
		to_change.setQuantity(to_change.getQuantity() + quantity);
		return;
	}
	else if (to_check != NOT_FOUND)
	{
		std::cerr << ITEM_ERROR << std::endl;
		return;
	}

	try
	{
		switch (type)
		{
			case candy:
			{
				double calories = std::stod(input[4]);
				if (calories < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return;
				}
				items.push_back(new Candy(id, name, price, quantity, calories));
				return;
			}
			case fabric:
			{
				double weight = std::stod(input[4]);
				if (weight < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return;
				}
				items.push_back(new Fabric(id, name, price, quantity, weight));
				return;
			}
			case kitchen:
			{
				double x = std::stod(input[4]), y = std::stod(input[5]), z = std::stod(
						input[6]), capacity = std::stod(
						input[7]);
				if (x < 0 || y < 0 || z < 0 || capacity < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return;
				}
				items.push_back(new Kitchenware(id, name, price, quantity, x, y, z, capacity));
				return;
			}
			case movieAndBook:
				items.push_back(
						new MoviesAndBooks(id, name, price, quantity, input[4], input[5],
										   input[6]));
				return;
			case tableAndChair:
			{
				double x = std::stod(input[4]), y = std::stod(input[5]), z = std::stod(input[6]);
				if (x < 0 || y < 0 || z < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return;
				}
				items.push_back(new TablesAndChairs(id, name, price, quantity, x, y, z, input[7],
													input[8]));
				return;
			}
			default:
				break;
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << INVALID_INPUT << std::endl;
		return;
	}
}

/**
 * gets next lines for MovieOrBook
 * @param inFile
 */
void ikea::inputMovieOrBook(std::ifstream &inFile)
{
	string line;
	string inputString;
	unsigned long delimiter;
	for (int i = 0; i < 2; i++)
	{
		std::getline(inFile, line);
		delimiter = line.find(": ");
		if (delimiter == string::npos)
		{
			std::cerr << BAD_FORMAT << std::endl;
			return;
		}
		try
		{
			inputString = line.substr(0, delimiter);
			switch (i)
			{
				case 0:
					if (!checkFormat(inputString, PUBLISH_YEAR))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				case 1:
					if (!checkFormat(inputString, LENGTH))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				default:
					break;
			}
		}
		catch (const std::out_of_range &e)
		{
			std::cerr << BAD_FORMAT << std::endl;
		}
	}
	type = movieAndBook;
}

/**
 * gets next lines for Furniture
 * @param inFile
 */
void ikea::inputFurniture(std::ifstream &inFile)
{
	string line;
	string inputString;
	std::getline(inFile, line);
	unsigned long delimiter = line.find(": ");
	inputString = line.substr(0, delimiter);

	if (inputString == "Capacity")
	{
		input.push_back(line.substr(delimiter + 2, line.length()));
		type = kitchen;
	} else if (inputString == "Material")
	{
		input.push_back(line.substr(delimiter + 2, line.length()));
		std::getline(inFile, line);
		delimiter = line.find(": ");
		inputString = line.substr(0, delimiter);
		if (inputString == "Color")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
		}
		type = tableAndChair;
	} else
	{
		std::cout << BAD_FORMAT << std::endl;
	}
}

void ikea::inputStock()
{
	string path;
	std::cout << ENTER_PATH << std::endl;
	std::cin >> path;

	std::ifstream inFile(path);

	if (!inFile.is_open())
	{
		std::cerr << OPEN_ERROR << std::endl;
		return;
	}

	string line;
	string inputString;
	while (true)
	{
		getFirstLines(inFile);
		if (!std::getline(inFile, line))
		{
			break;
		}
		unsigned long delimiter = line.find(": ");
		inputString = line.substr(0, delimiter);
		if (inputString == "Weight")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			type = fabric;
			checkSeparator(inFile);
			addItem(false);
		} else if (inputString == "Calories")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			type = candy;
			checkSeparator(inFile);
			addItem(false);
		} else if (inputString == "Author")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			inputMovieOrBook(inFile);
			checkSeparator(inFile);
			addItem(true);
		} else if (inputString == "Dimensions")
		{
			string cutLine;
			cutLine = line.substr(delimiter + 2, line.length());
			for (int i = 0; i < 3; i++)
			{
				delimiter = cutLine.find(' ');
				inputString = cutLine.substr(0, delimiter);
				input.push_back(inputString);
				cutLine = cutLine.substr(delimiter + 1, line.length());
			}
			inputFurniture(inFile);
			checkSeparator(inFile);
			addItem(true);
		}
		input.clear();
	}
	inFile.close();
}

/**
 * checks if the description is by the correct format
 * @param desc
 * @param format
 * @return 0 on success, -1 otherwise
 */
int ikea::checkFormat(string &desc, const string &format) const
{
	if (desc != format)
	{
		std::cerr << BAD_FORMAT << std::endl;
		return -1;
	}
	return 0;
}

/**
 * gets the first 4 lines from input file
 * @param inFile
 */
void ikea::getFirstLines(std::ifstream &inFile)
{
	string line;
	string inputString;
	for (int i = 0; i < 4; i++)
	{
		if (!std::getline(inFile, line) && i == 0)
		{
			return;
		}
		unsigned long delimiter = line.find(": ");
		if(delimiter == string::npos)
		{
			std::cerr << BAD_FORMAT << std::endl;
			return;
		}
		inputString = line.substr(0, delimiter);
		try
		{
			switch (i)
			{
				case 0:
					if (!checkFormat(inputString, "Item"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				case 1:
					if (!checkFormat(inputString, "Name"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				case 2:
					if (!checkFormat(inputString, "Quantity"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				case 3:
					if (!checkFormat(inputString, "Price"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
					}
					break;
				default:
					break;
			}
		}
		catch (const std::out_of_range &e)
		{
			std::cout << BAD_FORMAT << std::endl;
		}
	}
}

/**
 * find a item by it's id from user input
 */
Item* ikea::findById(bool printItem)
{
	std::cout << ENTER_NUMBER << std::endl;
	int id = getInt();
	if (id > 0)
	{
		for (auto &item: items)
		{
			if (item->getId() == id)
			{
				if (printItem)
				{
					item->printItem();
				}
				return item;
			}
		}
	}
	std::cout << NOT_FOUND << std::endl;
	return nullptr;
}

/**
 * find an item's name by it's id
 * @return
 */
const string &ikea::findNameById(int id)
{
	if (id > 0)
	{
		for (auto &item: items)
		{
			if (item->getId() == id)
			{
				return item->get_name();
			}
		}
		return NOT_FOUND;
	}
	return NOT_FOUND;
}


void ikea::findByName()
{
	std::cout << ENTER_NAME << std::endl;
	string name = getString();
	if (!name.empty())
	{
		for (auto &item: items)
		{
			if (item->get_name() == name)
			{
				item->printItem();
				return;
			}
		}
	}
	std::cout << NOT_FOUND << std::endl;
}


bool compById(const Item *first, const Item *second)
{
	return first->getId() < second->getId();
}

void ikea::printById()
{
	if (!items.empty())
	{
		std::sort(items.begin(), items.end(), compById);
		for (auto &item: items)
		{
			item->printItem();
		}
	}
}

bool compByName(const Item *first, const Item *second)
{
	return first->get_name() < second->get_name();
}


/**
 * prints items by name
 */
void ikea::printByName()
{
	if (!items.empty())
	{
		std::sort(items.begin(), items.end(), compByName);
		for (auto &item: items)
		{
			item->printItem();
		}
	}
}

/**
 * sells a item
 * @return
 */
void ikea::sell()
{
	Item *to_sell = findById(false);
	if(to_sell==nullptr)
	{
		return;
	}
	double quantity;
	try
	{
		if (to_sell->quantityIsInt())
		{
			std::cout << ENTER_ITTEM << std::endl;
		} else
		{
			std::cout << ENTER_QUANTITY << std::endl;
		}
		std::cin >> quantity;
		if (quantity > 0 && to_sell->getQuantity() >= quantity)
		{
			to_sell->setQuantity(to_sell->getQuantity() - quantity);
		} else
		{
			std::cout << SELL_ERROR << std::endl;
		}
	}
	catch (const std::out_of_range &e)
	{
		std::cout << NOT_FOUND << std::endl;
	}
}

int ikea::getInt()
{
	int input;
	if (std::cin >> input && input >= 0)
	{
		return input;
	} else
	{
		std::cerr << INVALID_INPUT << std::endl;
		return -1;
	}
}

string ikea::getString()
{
	string input;
	if (std::cin >> input)
	{
		return input;
	} else
	{
		std::cerr << INVALID_INPUT << std::endl;
		return "";
	}
}