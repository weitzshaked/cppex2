
#include "ikea.h"


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
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
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
int ikea::checkSeparator(std::ifstream &inFile)
{
	string line;
	getline(inFile, line);
	if (line != SEPERATOR)
	{
		std::cerr << MISSING_SEPERATOR << std::endl;
		return -1;
	}
	return 0;
}

/**
 * prints program menu
 */
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
Item &ikea::getById(int id)
{
	for (auto &item: items)
	{
		if (item->getId() == id)
		{
			return *item;
		}
	}
}

/**
 * adds an item to stock
 * @param isInt
 * @return 0 on success, -1 else
 */
int ikea::addItem(bool isInt)
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
		} else
		{
			quantity = std::stod(input[2]);
		}
		price = std::stod(input[3]);
		if (price < 0 || quantity < 0)
		{
			std::cerr << INVALID_INPUT << std::endl;
			return -1;
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << INVALID_INPUT << std::endl;
		return -1;
	}

	string to_check = findNameById(id);

	if (to_check == name)
	{
		Item &to_change = getById(id);
		to_change.setQuantity(to_change.getQuantity() + quantity);
		return -1;
	} else if (to_check != NOT_FOUND)
	{
		std::cerr << ITEM_ERROR << std::endl;
		return -1;
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
					return -1;
				}
				items.push_back(new Candy(id, name, price, quantity, calories));
				return 0;
			}
			case fabric:
			{
				double weight = std::stod(input[4]);
				if (weight < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return -1;
				}
				items.push_back(new Fabric(id, name, price, quantity, weight));
				return 0;
			}
			case kitchen:
			{
				double x = std::stod(input[4]), y = std::stod(input[5]), z = std::stod(
						input[6]), capacity = std::stod(input[7]);
				if (x < 0 || y < 0 || z < 0 || capacity < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return -1;
				}
				items.push_back(new Kitchenware(id, name, price, quantity, x, y, z, capacity));
				return 0;
			}
			case movieAndBook:
				items.push_back(
						new MoviesAndBooks(id, name, price, quantity, input[4], input[5],
										   input[6]));
				return 0;
			case tableAndChair:
			{
				double x = std::stod(input[4]), y = std::stod(input[5]), z = std::stod(input[6]);
				if (x < 0 || y < 0 || z < 0)
				{
					std::cerr << INVALID_INPUT << std::endl;
					return -1;
				}
				items.push_back(new TablesAndChairs(id, name, price, quantity, x, y, z, input[7],
													input[8]));
				return 0;
			}
			default:
				return -1;
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << INVALID_INPUT << std::endl;
		return -1;
	}
}

/**
 * gets next lines for MovieOrBook
 * @param inFile
 */
int ikea::inputMovieOrBook(std::ifstream &inFile)
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
			return -1;
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
			return -1;
		}
	}
	type = movieAndBook;
	return 0;
}

/**
 * gets next lines for Furniture
 * @param inFile
 */
int ikea::inputFurniture(std::ifstream &inFile)
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
		return -1;
	}
	return 0;
}

void ikea::inputStock()
{
	string path;
	std::cout << ENTER_PATH;
	std::cin >> path;
	std::ifstream inFile(path);
	input.clear();

	if (!inFile.is_open())
	{
		std::cerr << OPEN_ERROR << std::endl;
		return;
	}

	string line;
	string inputString;
	while (true)
	{
		if (getFirstLines(inFile) == -1)
		{
			return;
		}
		if (!std::getline(inFile, line))
		{
			break;
		}
		unsigned long delimiter = line.find(": ");
		if (delimiter == string::npos)
		{
			std::cerr << BAD_FORMAT << std::endl;
			break;
		}
		inputString = line.substr(0, delimiter);
		if (inputString == "Weight")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			type = fabric;
			if (checkSeparator(inFile) == -1 || addItem(false) == -1)
			{
				break;
			}
		} else if (inputString == "Calories")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			type = candy;
			if (checkSeparator(inFile) == -1 || addItem(false) == -1)
			{
				break;
			}
		} else if (inputString == "Author")
		{
			input.push_back(line.substr(delimiter + 2, line.length()));
			if (inputMovieOrBook(inFile) == -1 || checkSeparator(inFile) == -1 ||
				addItem(true) == -1)
			{
				break;
			}
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
			if (inputFurniture(inFile) == -1 || checkSeparator(inFile) == -1 || addItem(true) == -1)
			{
				break;
			}
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
int ikea::getFirstLines(std::ifstream &inFile)
{
	string line;
	string inputString;
	for (int i = 0; i < 4; i++)
	{
		if (!std::getline(inFile, line) && i == 0)
		{
			return 0;
		}
		unsigned long delimiter = line.find(": ");
		if (delimiter == string::npos)
		{
			std::cerr << BAD_FORMAT << std::endl;
			return -1;
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
						break;
					} else { return -1; }
				case 1:
					if (!checkFormat(inputString, "Name"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
						break;
					} else { return -1; }
				case 2:
					if (!checkFormat(inputString, "Quantity"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
						break;
					} else { return -1; }
				case 3:
					if (!checkFormat(inputString, "Price"))
					{
						input.push_back(line.substr(delimiter + 2, line.length()));
						break;
					} else { return -1; }
				default:
					return -1;
			}
		}
		catch (const std::out_of_range &e)
		{
			std::cout << BAD_FORMAT << std::endl;
			return -1;
		}
	}
}

/**
 * find a item by it's id from user input
 */
Item *ikea::findById(bool printItem)
{
	std::cout << ENTER_NUMBER;
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
		std::cout << NOT_FOUND << std::endl;
	}
	return nullptr;
}

/**
 * @param id
 * @return item name by it's id
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
	std::cout << ENTER_NAME;
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
	if (to_sell == nullptr)
	{
		return;
	}
	double quantity;
	if (to_sell->quantityIsInt())
	{
		std::cout << ENTER_ITTEM;
	} else
	{
		std::cout << ENTER_QUANTITY;
	}
	if (std::cin >> quantity)
	{
		if (quantity > 0 && to_sell->getQuantity() >= quantity)
		{
			to_sell->setQuantity(to_sell->getQuantity() - quantity);
			to_sell->printItem();
		} else
		{
			std::cout << SELL_ERROR << std::endl;
		}
	} else
	{
		std::cerr << INVALID_INPUT << std::endl;
	}
}


/**
 * gets int input from cin
 * @return
 */
int ikea::getInt()
{
	int input;
	std::cin >> input;
	if (std::cin.fail() || input <0)
	{
		std::cerr << INVALID_INPUT << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}
	return input;
}

/**
 * gets string input from cin
 * @return
 */
string ikea::getString()
{
	string input;
	getline(std::cin, input);
	if (getline(std::cin, input))
	{
		return input;
	} else
	{
		std::cerr << INVALID_INPUT << std::endl;
		return "";
	}
}