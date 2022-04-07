using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

struct Road
{
	int begin, end;
	double length;
	string name, type;

	Road(string n, string t, int b, int e, double l)
	{
		begin = b;
		end = e;
		name = n;
		length = l;
	};
};

struct Place
{
	vector<Road> roads;
	int idx;
	string state, name;
	double log, lat, length;
	
	Place(int i, double lo, double la, double l, string s, string n)
	{
		idx = i;
		log = lo;
		lat = la;
		length = l;
		state = s;
		name = n;
	};
	
	void add_road(Road i)
	{
		roads.push_back(i);
	};
};


int main()
{
	vector<Place> places;
	double log, lat, length;
	string state, name, type, negl;
	int begin, end, idx = 0;

	ifstream myfile1("/home/www/class/een318/intersections.txt");
	while(myfile1 >> log >>lat >> length >> state)
	{
		getline(myfile1, name);
		Place place(idx, log, lat, length, state, name);
		places.push_back(place);
		idx++;
	}
	myfile1.close();

	ifstream myfile2("/home/www/class/een318/connections.txt");
	
	while(myfile2 >> name >> type >> begin >> end >> length)
	{
		Road road1(name, type, begin, end, length);
		Road road2(name, type, begin, end, length);
		places[begin].add_road(road1);
		places[end].add_road(road2);
	}
	myfile2.close();
	cout << "data read successfully" << endl;

	cout << "Location to start: ";
	cin >> idx;

	if (idx < 0 || idx >= places.size())
	{
		cout << "Error, please input a number between 0 and "<< places.size() << endl;
		return 0;
	}
	cout << endl;
	
	while(true)
	{
		vector<Road> road = places[idx].roads;
		cout << "Location " << places[idx].idx << ", " << places[idx].length << " miles from " << places[idx].name << ", " << places[idx].state << endl;
		cout << "roads leading away: " << endl;
		
		for (int x = 0; x < road.size(); x++)
		{
			cout << "   " << x+1 << ": " << road[x].name << ", " << road[x].length;
			cout << " miles to place " << road[x].end << endl;
		}
		
		int input;
		while (true)
		{
			cout << "Choose a road to take, or type 0 to terminate the program. ";
			cin >> input;
			if (input == 0)
			{
				cout << "Goodbye!" << endl;
				return(0);
			}
			else if (input < 1 || input > road.size())
			{
				cout << "Error! Road does not exist. Please try again with a valid entry." << endl;

			}
			else if (input > 0 && input <= road.size())
				break;

		}
		idx = road[input-1].end;
	}
}
