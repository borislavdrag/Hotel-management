#include "Hotel.h"
using namespace std;
#define STARTING_COMMAND_LENGTH 10
#define DEFAULT_RESIZE_VALUE 10
#define MAX_FUNCTION_LENGTH 15


void copyFirtCommand(char* target, char* source)
{
	int src_len = strlen(source);
	for (int i = 0; i <= src_len; i++)
		if (source[i] == ' ' || source[i] == '\0')
		{
			strncpy(target, source, i);
			target[i] = '\0';
			break;
		}
}

void removeFirstCommand(char* source, char* currentCommand)
{
	if (strlen(source) == 0)
		return;
	int trg_len = strlen(source) - strlen(currentCommand);
	char* command2 = new char[trg_len + 1];
	for (int i = 0; i <= trg_len; i++)
		command2[i] = source[i + strlen(currentCommand) + 1];

	command2[trg_len] = '\0';

	strcpy(source, command2);
	delete[] command2;
}

int main()
{
	/*Hotel t;

	t.getRoom(105).setBeds(3);
	t.getRoom(106).setBeds(3);

	t.checkin(201, "2000-01-01", "2000-01-06", -1, "Only Bobby");
	t.checkin(106, "2000-03-01", "2000-04-08", -1);
	t.repair(106, "2000-02-29", "2000-03-01", "For the couple");

	t.report("2000-01-01", "2001-01-01");
	t.available("2000-01-01", "2001-01-01", 1);

	fstream out;
	out.open("hotel.data", fstream::out | fstream::trunc);
	t.save(out);
	out.close();

	Hotel t2;

	fstream in;
	in.open("hotel.data", fstream::in);
	in.seekg(0, fstream::beg);
	t2.load(in);

	t2.report("2000-01-01", "2001-01-01");
	t2.available("2000-01-01", "2001-01-01", 1);

	out.open("hotel2.data", fstream::out | fstream::trunc);
	t2.save(out);
	out.close();*/
	//t.print();

	Hotel hotel;
	bool opened = false;
	char* filename = nullptr;

	while (true)
	{
		char* command = new char[STARTING_COMMAND_LENGTH + 1];
		command[0] = '\0';
		char symbol;

		unsigned int lengthBoundary = STARTING_COMMAND_LENGTH;
		unsigned int commandLength = 0;

		do
		{
			cin.get(symbol);
			// cout << symbol;

			if (commandLength == lengthBoundary)
			{
				lengthBoundary += DEFAULT_RESIZE_VALUE;

				char* temp = new char[lengthBoundary + 1];
				strcpy(temp, command);

				delete[] command;
				command = temp;
			}
			// strcat(command, &symbol);
			command[commandLength] = symbol;

			// cout << "2 " << command << endl;
			commandLength++;
			command[commandLength] = '\0';


		} while (symbol != '\n');

		command[commandLength - 1] = '\0';
		// cout << "1 " << command << endl;

		// extracting the first word (the function)
		char currentCommand[MAX_FUNCTION_LENGTH];

		copyFirtCommand(currentCommand, command);

		removeFirstCommand(command, currentCommand);

		// cout << currentCommand << endl;        
		// cout << command << endl;

		// check the functionality
		if (strcmp("help", currentCommand) == 0)
		{
			cout << "Help" << endl;
		}
		else if (strcmp("exit", currentCommand) == 0)
		{
			cout << "Sorry to see you go :(" << endl;
			return 0;
		}
		else if (strcmp("open", currentCommand) == 0)
		{
			char* name = new char[strlen(command) + 1];
			copyFirtCommand(name, command);

			if (filename != nullptr)
				delete[] filename;
			filename = new char[strlen(name) + 1];
			strcpy(filename, name);

			fstream in;
			in.open(name, fstream::in);
			in.seekg(0, fstream::beg);
			hotel.load(in);

			cout << "Loaded " << filename << endl;
			opened = true;
			delete[] name;
			in.close();
		}
		else if (strcmp("close", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				opened = false;
				Hotel hotel2;
				hotel = hotel2;
				cout << "Closed the file" << endl;
			}
		}
		else if (strcmp("save", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				fstream out;
				if (filename == nullptr)
				{
					out.open("hotel1.data", fstream::out | fstream::trunc);
					filename = new char[strlen("hotel1.data") + 1];
					strcpy(filename, "hotel1.data");
					hotel.save(out);
				}
				else
				{
					out.open(filename, fstream::out | fstream::trunc);
					hotel.save(out);
				}
				cout << "Saved " << filename << endl;
				out.close();
			}
		}
		else if (strcmp("saveas", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* name = new char[strlen(command) + 1];
				copyFirtCommand(name, command);

				fstream out;
				out.open(name, fstream::out | fstream::trunc);
				hotel.save(out);

				cout << "Saving as " << name << endl;
				delete[] name;
				out.close();
			}
		}
		else if (strcmp("checkin", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* id = new char[strlen(command) + 1];
				copyFirtCommand(id, command);
				removeFirstCommand(command, id);

				char* from = new char[strlen(command) + 1];
				copyFirtCommand(from, command);
				removeFirstCommand(command, from);

				char* to = new char[strlen(command) + 1];
				copyFirtCommand(to, command);
				removeFirstCommand(command, to);

				char* rest = new char[strlen(command) + 1];
				copyFirtCommand(rest, command);
				removeFirstCommand(command, rest);

				if (atoi(rest) == 0)
				{
					hotel.checkin(atoi(id), from, to, -1, rest);
				}
				else
				{					
					hotel.checkin(atoi(id), from, to, atoi(rest), command);
				}

				cout << "Checked in room " << id << " from " << from << " to " << to 
					 << " " << rest << endl;
				delete[] id;
				delete[] from;
				delete[] to;
				delete[] rest;
			}
		}
		else if (strcmp("checkout", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* id = new char[strlen(command) + 1];
				copyFirtCommand(id, command);
				hotel.checkout(atoi(id));

				delete[] id;
			}
			cout << "Ckecked you out, mate" << endl;
		}
		else if (strcmp("unavailable", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* id = new char[strlen(command) + 1];
				copyFirtCommand(id, command);
				removeFirstCommand(command, id);

				char* from = new char[strlen(command) + 1];
				copyFirtCommand(from, command);
				removeFirstCommand(command, from);

				char* to = new char[strlen(command) + 1];
				copyFirtCommand(to, command);
				removeFirstCommand(command, to);

				hotel.repair(atoi(id), from, to, command);

				cout << "Room " << id << " is unavailable from " << from << " to " << to
					<< " " << strlen(command) << endl;
				delete[] id;
				delete[] from;
				delete[] to;
			}
		}
		else if (strcmp("availability", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* date = new char[strlen(command) + 1];
				copyFirtCommand(date, command);

				hotel.available(date);
				delete[] date;
			}
		}
		else if (strcmp("find", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* beds = new char[strlen(command) + 1];
				copyFirtCommand(beds, command);
				removeFirstCommand(command, beds);

				char* from = new char[strlen(command) + 1];
				copyFirtCommand(from, command);
				removeFirstCommand(command, from);

				char* to = new char[strlen(command) + 1];
				copyFirtCommand(to, command);

				hotel.available(from, to, atoi(beds));
			}
		}
		else if (strcmp("report", currentCommand) == 0)
		{
			if (!opened)
				cout << "Open a file first" << endl;
			else
			{
				char* from = new char[strlen(command) + 1];
				copyFirtCommand(from, command);
				removeFirstCommand(command, from);

				char* to = new char[strlen(command) + 1];
				copyFirtCommand(to, command);
				
				hotel.report(from, to);
			}
		}
		else
		{
			cout << "Command not recognised, type \'help\' for a guide." << endl;
		}
	}
}