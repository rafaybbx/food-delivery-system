#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <bits/stdc++.h>
using namespace std;
const int INF = 999;
const int V = 10;

string sourceLocation;
bool visitedR[10] = {false, false, false, false, false, false, false, false, false, false};
bool restau[10] = {false, false, false, false, false, false, false, false, false, false};
int riderinfo[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int food[] = {-1, -1, -1, -1, -1};
int dist[V];
int parent[V];
bool visited[V];
string locations[] = {"G-10/1", "G-10/2", "G-10/3", "G-10/4", "F-10/1", "F-10/2", "F-10/3", "F-10/4", "E-10/1", "E-10/2"};

int costMatrix[V][V] = {
    {999, 4, 999, 999, 999, 999, 999, 7, 999, 999},
    {4, 999, 8, 999, 999, 999, 999, 999, 999, 3},
    {999, 8, 999, 7, 999, 4, 999, 999, 2, 999},
    {999, 999, 7, 999, 9, 14, 999, 999, 999, 999},
    {999, 999, 999, 9, 999, 10, 999, 999, 999, 999},
    {999, 999, 4, 14, 10, 999, 999, 999, 999, 999},
    {999, 999, 999, 999, 999, 2, 999, 1, 6, 999},
    {8, 11, 999, 999, 999, 999, 1, 999, 7, 9},
    {999, 999, 2, 999, 999, 999, 6, 7, 999, 1},
    {999, 3, 999, 999, 999, 999, 999, 999, 1, 999}};

int getIndex(string src)
{
    int index = 0;

    if (src.compare("G-10/1") == 0)
    {
        index = 0;
    }
    else if (src.compare("G-10/2") == 0)
    {
        index = 1;
    }
    else if (src.compare("G-10/3") == 0)
    {
        index = 2;
    }
    else if (src.compare("G-10/4") == 0)
    {
        index = 3;
    }
    else if (src.compare("F-10/1") == 0)
    {
        index = 4;
    }
    else if (src.compare("F-10/2") == 0)
    {
        index = 5;
    }
    else if (src.compare("F-10/3") == 0)
    {
        index = 6;
    }
    else if (src.compare("F-10/4") == 0)
    {
        index = 7;
    }
    else if (src.compare("E-10/1") == 0)
    {
        index = 8;
    }
    else if (src.compare("E-10/2") == 0)
    {
        index = 9;
    }
    else
    {
        cout << "Delivery At this location not possible." << endl;
        index = -1;
    }

    return index;
}

string getLocation(int index)
{
    return locations[index];
}

void initialize(string src)
{
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = i;
        int s = getIndex(src);
        dist[s] = 0;
    }
}

int getNearest()
{
    int nearest;
    int minNode;
    int minimum = INF;
    for (int i = 0; i < V; i++)
    {
        if ((dist[i] < minimum) && visited[i] == false)
        {
            minimum = dist[i];
            minNode = i;
        }
    }
    return minNode;
}

void dijkstra()
{
    int nearest;
    for (int i = 0; i < V; i++)
    {
        nearest = getNearest();
        visited[nearest] = true;

        for (int adj = 0; adj < V; adj++)
        {
            if ((costMatrix[nearest][adj] != INF) && (dist[nearest] + costMatrix[nearest][adj] < dist[adj]))
            {
                dist[adj] = dist[nearest] + costMatrix[nearest][adj];
                parent[adj] = nearest;
            }
        }
    }
}

void displayRoute(string source, string destination)
{
    int k = 0;
    string path[10];
    int src = getIndex(source);
    int dest = getIndex(destination);
    for (int i = 0; i < V; i++)
    {
        while (dest != src)
        {
            path[k] = locations[dest];
            dest = parent[dest];
            k++;
        }
    }

    cout << " " << endl;

    cout << "The path For moving To is: ( " << destination << ") with the minimum distance of (" << dist[getIndex(destination)] << " km) would be:" << endl;
    cout << " " << endl;
    cout << source << " -> ";
    for (int i = path->length(); i >= 0; i--)
    {
        if (path[i] != "")
        {
            cout << path[i] << " -> ";
        }
    }

    cout << "Arrival at destination";
    cout << " " << endl;
}

static int admin_key = 0;
static int user_key = 0;
static int rider_key = 0;

class user
{
public:
    int user_id;
    string name;
    string username;
    string email;
    int password;

    user()
    {
        this->name = "empty";
        this->username = "empty";
        this->user_id = -1;
        this->email = "empty";
        this->password = -1;
    }
    user(int us)
    {
        this->user_id = us;
    }
    user(string name, string username, string email, int id, int password)
    {
        this->name = name;
        this->username = username;
        this->email = email;
        this->user_id = id;
        this->password = password;
    }

    void setUser(string name, string username, string email, int id, int password)
    {

        this->name = name;
        this->username = username;

        this->email = email;
        this->user_id = id;
        this->password = password;
    }

    //     user(string name, string email, string username, int password)
    // {
    // }
};

class order
{
public:
    user client;
    int to;
    int rest;
    int from;
    int *food;

    order()
    {
        this->to = -1;
        this->from = -1;
        this->rest = -1;

        food = new int[5];

        for (int i = 0; i < 6; i++)
        {
            food[i] = -1;
        }
    }
    order(const order &a)
    {
        this->to = a.to;
        this->from = a.from;
        this->rest = a.rest;
        this->client = a.client;

        food = new int[5];

        for (int i = 0; i < 6; i++)
        {
            food[i] = a.food[i];
        }
    }

    order(int too, int frm, int restr, int *array)
    {
        food = new int[5];

        for (int i = 0; i < 6; i++)
        {
            food[i] = array[i];
        }
        rest = restr;
        to = too;
        from = frm;
    }

    void setUser(user u)
    {
        this->client.name = u.name;
        this->client.username = u.username;
        this->client.email = u.email;
        this->client.user_id = u.user_id;
        this->client.password = u.password;
    }

    void setOrder(int to, int from, int *arr, user u)
    {
        this->to = to;
        this->from = from;
        food = new int[5];
        this->client.name = u.name;
        this->client.username = u.username;
        this->client.email = u.email;
        this->client.user_id = u.user_id;
        this->client.password = u.password;
        for (int i = 0; i < 6; i++)
        {
            food[i] = arr[i];
        }
    }

    int calculatePrice()
    {
        int total = 0;
        for (int i = 0; i < 5; i++)
        {
            switch (food[i])
            {
            case 1:
                total += 1200;
                break;
            case 2:
                total += 800;
                break;
            case 3:
                total += 700;
                break;
            case 4:
                total += 350;
                break;
            case 5:
                total += 1600;
                break;
            default:
                break;
            }
        }

        return total;
    }
};

class rider
{
public:
    int rider_id;
    int location;
    string name;
    string bike_no;
    int password;
    order package;

    rider()
    {
        rider_id = -1;
        location = -1;
        name = "empty";
        bike_no = "empty";
        password = -1;
        this->package = order();
    }

    rider(int l, int id, string n, int p, string b)
    {
        rider_id = id;
        location = l;
        name = n;
        bike_no = b;
        password = p;
    }
    void placeOrder(order package)
    {
        this->package.to = package.to;
        this->package.from = package.from;
        this->package.setOrder(package.to, package.from, package.food, package.client);
    }
};

class admin
{
public:
    string name;
    int admin_id;
    int password;

    admin()
    {

        name = "empty";
        admin_id = -1;
        password = -1;
    }

    admin(string n, int id, int p)
    {
        name = n;
        admin_id = id;
        password = p;
    }

    void delete_user_account()
    {

        // users.delete_values();

        cout << "Yes" << endl;
    }

    // enter rider
    // remove riders
    // view riders
    // view users
};

struct user_node
{
    user u;
    user_node *next = nullptr;
};

struct admins
{
    admin u;
    admins *next = nullptr;
};

admins *tempa = nullptr;

struct riders
{
    rider u;
    riders *next = nullptr;
};

riders *tempr = nullptr;

class linked_list_user
{
public:
    user_node *first;
    user_node *last;

    linked_list_user()
    {
        first = nullptr;
        last = nullptr;
    }

    void display()
    {
        // string name, string username, string email, int id, int password
        cout << "----------------------------DISPLAYING USER DATABASE------------------------" << endl;
        user_node *p = first;
        while (p != nullptr)
        {
            cout << " " << endl;
            cout << "Name: " << p->u.name << endl;
            cout << "UserName: " << p->u.username << endl;
            cout << "Unique id: " << p->u.user_id << endl;
            cout << "Email: " << p->u.email << endl;
            cout << "Password: " << p->u.password << endl;
            p = p->next;
            cout << " " << endl;
        }
    }

    bool check_user_existence(user u)
    {
        user_node *p = first;
        while (p != nullptr)
        {

            if ((p->u.password == u.password) && (p->u.username == u.username))
            {

                return true;
            }
            p = p->next;
        }
        return false;
    }
    user_node *getNode(user u)
    {
        user_node *p = first;
        user_node *z = first;

        while (p != nullptr)
        {

            if ((p->u.password == u.password) && (p->u.username == u.username) && (p->u.email == u.email))
            {

                return p;
            }
            p = p->next;
        }
        return z;
    }
    void insert_values(user p)
    {

        if (!check_user_existence(p))
        {

            user_node *entry;
            entry = new user_node;

            entry->u.name = p.name;
            entry->u.username = p.username;
            entry->u.email = p.email;
            entry->u.password = p.password;
            entry->u.user_id = p.user_id;

            entry->next = nullptr;

            if (first == nullptr)
            {

                first = last = entry;
            }
            else
            {

                last->next = entry;

                last = entry;
            }
        }
        else
        {
            cout << "USER ALREADY EXISTS" << endl;
        }
    }
    void delete_values()
    {

        bool found = false;

        int id;
        cout << "Enter the id you want to delete" << endl;
        cin >> id;

        user_node *p = first;
        user_node *p1;

        while (p != nullptr)
        {
            if ((p->next == nullptr) && (p == first) && (p->u.user_id == id))
            {
                first = nullptr;
                last = nullptr;
                found = true;
                break;
            }
            else if ((p->next == nullptr) && (p == last) && (p->u.user_id == id))
            {
                p1->next = nullptr;
                found = true;
                break;
            }
            else if (p->u.user_id == id)
            {
                p1->next = p->next;
                delete p;
                found = true;
                break;
            }
            p1 = p;
            p = p->next;
        }
        if (found)
        {

            cout << "USER DELETED SUCCESSFULLY!" << endl;
        }
        else
        {
            cout << "USER NOT FOUND" << endl;
        }
    }
};

class linked_list_admin
{
public:
    admins *first;
    admins *last;

    linked_list_admin()
    {
        first = nullptr;
        last = nullptr;
    }

    void display()
    {
        // string name, string username, string email, int id, int password
        cout << "----------------------------DISPLAYING ADMIN DATABASE------------------------" << endl;
        admins *p = first;
        while (p != nullptr)
        {
            cout << " " << endl;
            cout << "Name: " << p->u.name << endl;
            cout << "Unique id: " << p->u.admin_id << endl;
            cout << "Password: " << p->u.password << endl;
            p = p->next;
            cout << " " << endl;
        }
    }

    bool check_user_existence(admin u)
    {
        admins *p = first;
        while (p != nullptr)
        {

            if ((p->u.password == u.password) && (p->u.name == u.name))
            {

                return true;
            }
            p = p->next;
        }
        return false;
    }
    void insert_values(admin p)
    {

        if (!check_user_existence(p))
        {

            admins *entry;
            entry = new admins;
            entry->u = p;

            entry->next = nullptr;

            if (first == nullptr)
            {

                first = last = entry;
            }
            else
            {

                last->next = entry;

                last = entry;
            }
        }
        else
        {
            cout << "ADMIN ALREADY EXISTS" << endl;
        }
    }
};

class linked_list_rider
{
public:
    riders *first;
    riders *last;

    linked_list_rider()
    {
        first = nullptr;
        last = nullptr;
    }

    void display()
    {
        // string name, string username, string email, int id, int password
        cout << "----------------------------DISPLAYING RIDERS DATABASE------------------------" << endl;
        riders *p = first;
        while (p != nullptr)
        {

            // int rider_id;
            // int location;
            // string name;
            // string bike_no;
            // int password;
            // order package;

            cout << " " << endl;
            cout << "Name: " << p->u.name << endl;
            cout << "Current Location: " << p->u.location << endl;
            cout << "Unique id: " << p->u.rider_id << endl;
            cout << "Bike No: " << p->u.bike_no << endl;
            cout << "Password: " << p->u.password << endl;

            if (p->u.package.client.user_id == -1)
            {

                cout << "Currently No Orders to be delivered!" << endl;
            }
            else
            {
                cout << "Current Order to  deliver: " << endl;
                cout << "Client Name: " << p->u.package.client.name << endl;
            }
            /* code */

            p = p->next;
            cout << " " << endl;
        }
    }

    bool check_user_existence(rider u)
    {
        riders *p = first;
        while (p != nullptr)
        {

            if ((p->u.password == u.password) && (p->u.name == u.name))
            {

                return true;
            }
            p = p->next;
        }
        return false;
    }

    riders *getNode(rider u)
    {
        riders *p = first;
        riders *z = first;

        while (p != nullptr)
        {

            if ((p->u.password == u.password) && (p->u.name == u.name))
            {

                return p;
            }
            p = p->next;
        }
        return z;
    }
    riders *getRiderFromId(int a)
    {
        riders *p = first;
        riders *z = first;

        while (p != nullptr)
        {

            if ((p->u.rider_id == a))
            {

                return p;
            }
            p = p->next;
        }
        return z;
    }
    void insert_values(rider p)
    {

        if (!check_user_existence(p))
        {

            riders *entry;
            entry = new riders;
            entry->u = p;

            // entry->u.name = p.name;
            // entry->u.username = p.username;
            // entry->u.email = p.email;
            // entry->u.password = p.password;
            // entry->u.user_id = p.user_id;

            entry->next = nullptr;

            if (first == nullptr)
            {

                first = last = entry;
            }
            else
            {

                last->next = entry;

                last = entry;
            }
        }
        else
        {
            cout << "RIDER ALREADY EXISTS" << endl;
        }
    }
    void delete_values()
    {

        bool found = false;

        int id;
        cout << "Enter the id you want to delete" << endl;
        cin >> id;

        riders *p = first;
        riders *p1;
        while (p != nullptr)
        {
            if ((p->next == nullptr) && (p == first) && (p->u.rider_id == id))
            {
                first = nullptr;
                last = nullptr;
                found = true;
                break;
            }
            else if ((p->next == nullptr) && (p == last) && (p->u.rider_id == id))
            {
                p1->next = nullptr;
                found = true;
                break;
            }

            else if (p->u.rider_id == id)
            {
                p1->next = p->next;
                delete p;
                found = true;
                break;
            }
            p1 = p;
            p = p->next;
        }
        if (found)
        {

            cout << "Rider DELETED SUCCESSFULLY!" << endl;
        }
        else
        {
            cout << "Rider NOT FOUND" << endl;
        }
    }
};

class Que
{
public:
    order *arr;
    int sizee;
    int front;
    int rear;

    Que()
    {
        sizee = 20;
        arr = new order[sizee];
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        if (front == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isFull()
    {
        if (front == (sizee - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void enqueue(order o)
    {
        if (this->isFull())
        {
            cout << "Queue is Full." << endl;
            return;
        }
        else
        {
            if (this->isEmpty())
            {
                front = rear = 0;
            }
            else
            {
                rear++;
            }
            arr[rear] = o;
        }
    }

    order dequeue()
    {
        if (this->isEmpty())
        {
            cout << "Queue is Empty." << endl;
            order z;
            return z;
        }
        else
        {
            order o = arr[front];
            if (front == rear) // If rear is at 0, meaning there is only one element
            {
                front = rear = -1;
            }
            else
            {
                for (int i = 0; i < rear; i++)
                {
                    arr[i] = arr[i + 1]; // Shifting elements to left after dequeue operation
                }
                rear--;
                // cout<<front<<endl;
            }
            cout << "Dequeue successful." << endl;
            return o;
        }
    }

    void display()
    {
        if (this->isEmpty())
        {
            cout << "Queue is Empty." << endl;
        }
        else
        {
            for (int i = front; i <= rear; i++)
            {
                cout << "Order at index " << i << " is: " << arr[i].client.username << endl;
                cout << "Order at index " << i << " is: " << arr[i].from << endl;
            }
            cout << " " << endl;
        }
    }
};

int getIntegerFromUser(const string &prompt, int low, int high)
{
    int input = 0;
    bool check = false;
    do
    {
        cout << prompt << endl;
        try
        {
            string inputString;
            cin >> inputString;
            input = stoi(inputString);
            check = true;
        }
        catch (exception e)
        {
            check = false;
            cout << "Incorrect data Type Entered!!!" << endl;
        }

    } while ((input <= low) || (input >= high) || input == 0);

    return input;
}

int main()
{
    linked_list_admin admins;
    linked_list_user users;
    linked_list_rider riders;

    Que orders;

    // DUMMY DATA FOR MY PERSONAL TESTING

    // admin a("hassan", 1, 1);
    // admin a1("rafay", 54, 9);
    // admin a2("zaleel", 55, 929);
    // admin a3("nigga", 56, 40);

    // user u("Hadia", "hadiabbx", "d", 1, 1);
    // user u1("rafay", "rafaybbx", "rafaybbx@gmail.com", 1, 1);
    // user u2("samad", "samadbbx", "samadbbx@gmail.com", 3, 103);
    // user u3("hassan", "hassanbbx", "hassanbbx@gmail.com", 4, 104);
    // user u4("kulsoom", "kulsoombbx", "kulsoombbx@gmail.com", 5, 105);

    // int arr[] = {1, 2, 3, 4, 5};
    // int arr1[] = {4, 2, 1, -1, -1};
    // int arr2[] = {2, 1, 3, -1, -1};
    // int arr3[] = {3, 2, 4, -1, -1};
    // order
    // rider r1(5, 1, "rafay", 1, "ALN-678");

    // order o(1, 5, 8,arr);
    // orders.enqueue(o);
    // o.setUser(u1);

    // order
    // order o1(10, 50, 5,arr1);

    // o1.setUser(u2);

    // order
    //     o2(10, 50, arr2);
    // o2.setUser(u3);

    // order
    //     o3(10, 50, arr3);
    // o3.setUser(u4);

    // rider r(4, 1, "name", 1, "b");

    // r.placeOrder(o);

    // r1.placeOrder(o1);

    // rider r2(7, 255, "dada2", 1925, "CLN-678");
    // r2.placeOrder(o2);

    // rider r3(8, 925, "dada3", 6524, "DDN-678");
    // r3.placeOrder(o3);

    // admins.insert_values(a);
    // admins.insert_values(a1);
    // admins.insert_values(a2);
    // admins.insert_values(a3);

    // users.insert_values(u1);
    // users.insert_values(u2);
    // users.insert_values(u3);
    // users.insert_values(u4);

    // riders.insert_values(r);
    // riders.insert_values(r1);
    // riders.insert_values(r2);
    // riders.insert_values(r3);

    // admins.display();
    // users.display();
    // riders.display();

    // orders.enqueue(o);
    // orders.enqueue(o1);
    // orders.enqueue(o2);
    // orders.enqueue(o3);

    // orders.display();

    // cout<<" "<<endl;
    // cout<<" "<<endl;
    // cout<<" "<<endl;

    // order o= orders.dequeue();

    // cout<<o.to<<endl;

    int op = -1;
    // cout << " " << endl;

    // riders.display();

    do
    {
        cout << " " << endl;
        cout << " " << endl;
        cout << "----------------- FOOD DELIVERY SYSTEM -----------------" << endl;
        cout << " " << endl;
        cout << " " << endl;
        cout << "Menu" << endl;
        cout << " " << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << " " << endl;
        cout << "Option: ";
        cin >> op;
        cout << "\n"
             << endl;

        if (op == 1)
        {

            int op1 = -1;
            do
            {

                cout << " " << endl;
                cout << "----------------- SIGNUP MENU -----------------" << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "1. Signup as an Admin" << endl;
                cout << "2. Signup as a User" << endl;
                cout << "3. Signup as a Rider" << endl;
                cout << "0. Go Back" << endl;
                cout << " " << endl;
                cout << "Option: ";
                cin >> op1;
                cout << "\n"
                     << endl;

                if (op1 == 1)
                {

                    // name id pass
                    admin_key++;

                    string a_input_name = "empty";
                    int a_input_password = -1;

                    cout << "Enter Your Name" << endl;
                    cin >> a_input_name;

                    string prompt = "Enter Your password: ";
                    a_input_password = getIntegerFromUser(prompt, -1, 99999);

                    admin tadmin(a_input_name, admin_key, a_input_password);

                    // cout << admins.check_user_existence(tadmin) << endl;

                    if (admins.check_user_existence(tadmin))
                    {
                        cout << "ADMIN ALREADY EXISTS!" << endl;
                        admin_key--;
                    }
                    else
                    {
                        admins.insert_values(tadmin);
                        cout << "Sign up Successful!" << endl;
                        cout << "Your Unique id is: " << admin_key << "  DO NOT FORGET IT" << endl;
                        break;
                    }
                }

                else if (op1 == 2)
                {
                    user_key++;

                    cout << " " << endl;

                    string input_name = "empty";
                    string input_username = "empty";
                    string input_email = "empty";
                    int input_password = -1;

                    cout << "Enter Your Name" << endl;
                    cin >> input_name;
                    cout << " " << endl;
                    cout << "Enter Your UserName" << endl;
                    cin >> input_username;
                    cout << " " << endl;
                    cout << "Enter Your email" << endl;
                    cin >> input_email;
                    cout << " " << endl;
                    string prompt = "Enter Your password: ";
                    input_password = getIntegerFromUser(prompt, -1, 99999);

                    user tu(input_name, input_username, input_email, user_key, input_password);

                    if (users.check_user_existence(tu))
                    {
                        cout << "USER ALREADY EXISTS!" << endl;
                        user_key--;
                    }
                    else
                    {
                        users.insert_values(tu);
                        cout << "Sign up Successful!" << endl;
                        break;
                    }
                }

                else if (op1 == 3)
                {
                    // rider signup
                    cout << " " << endl;

                    string input_name = "empty";
                    int input_password = -1;
                    string input_bikeno = "empty";
                    int input_location = -1;

                    cout << "Enter Your Name" << endl;
                    cin >> input_name;

                    cout << " " << endl;
                    string prompt = "Enter Your password: ";
                    string prompt1 = "Enter Your starting location(between 0 - 9): ";
                    input_password = getIntegerFromUser(prompt, -1, 99999);
                    input_location = getIntegerFromUser(prompt1, 0, 9);

                    rider rt(input_location, rider_key, input_name, input_password, input_bikeno);

                    if (riders.check_user_existence(rt))
                    {
                        cout << "RIDER ALREADY EXISTS!" << endl;
                        rider_key--;
                    }
                    else
                    {
                        riders.insert_values(rt);
                        visitedR[input_location] = true;
                        riderinfo[input_location] = rider_key;
                        cout << "Sign up Successful!" << endl;
                        break;
                    }
                }

                else if ((op1 != 0) || (op1 != 1) || (op1 != 2) || (op1 != 3))
                {
                    cout << " " << endl;
                    cout << "Incorrect option!" << endl;
                    cout << " " << endl;
                }
            } while (op1 != 0);

            //=====================================================================================================================================================
        }
        else if (op == 2)
        {
            // login

            int op2 = -1;
            do
            {

                cout << " " << endl;
                cout << "----------------- LOGIN MENU -----------------" << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "1. Login as an Admin" << endl;
                cout << "2. Login as a User" << endl;
                cout << "3. Login as a Rider" << endl;
                cout << "0. Go Back" << endl;
                cout << " " << endl;
                cout << "Option: ";
                cin >> op2;
                cout << "\n"
                     << endl;

                if (op2 == 1)
                {
                    // admin authorization

                    string a_input_name = "empty";
                    int a_input_password = -1;
                    int a_input_admin_id = -1;

                    cout << "Enter Your Name" << endl;
                    cin >> a_input_name;

                    string prompt = "Enter Your password: ";
                    string prompt1 = "Enter Your Unique admin id: ";
                    a_input_password = getIntegerFromUser(prompt, -1, 99999);
                    a_input_admin_id = getIntegerFromUser(prompt1, -1, 999);

                    admin tadmin(a_input_name, admin_key, a_input_password);

                    // cout << admins.check_user_existence(tadmin) << endl;
                    //===================================================================================================================================================
                    if (admins.check_user_existence(tadmin))
                    {
                        cout << " " << endl;
                        cout << "LOGIN SUCCESSFUL" << endl;
                        cout << " " << endl;

                        int op3 = -1;

                        do
                        {
                            cout << " " << endl;
                            cout << "----------------- WELCOME " << tadmin.name << " -----------------" << endl;
                            cout << " " << endl;
                            cout << "Please Select Your Option: " << endl;
                            cout << " " << endl;
                            cout << "1. View All Registered Users " << endl;
                            cout << "2. View All Registered Riders " << endl;
                            cout << "3. Remove a Rider" << endl;
                            cout << "4. Remove a User" << endl;
                            // cout << "5. Complete a Order" << endl;
                            cout << "0. Go Back" << endl;
                            cout << " " << endl;
                            cout << "Option: ";
                            cin >> op3;
                            cout << "\n"
                                 << endl;

                            if (op3 == 1)
                            {
                                users.display();
                            }
                            else if (op3 == 2)
                            {
                                riders.display();
                            }
                            else if (op3 == 3)
                            {
                                riders.delete_values();
                            }
                            else if (op3 == 4)
                            {
                                users.delete_values();
                            }
                            // else if (op3 == 5)
                            {
                                //     if (orders.isEmpty())
                                //     {
                                //         cout << "No Current Orders available to be delivered! " << endl;
                                //     }
                                //     else
                                //     {
                                //         order o(orders.dequeue());
                                //         int rest = o.rest;
                                //         int to = o.to;
                                //         int from = o.from;
                                //         string name = o.client.name;

                                //         cout << " " << endl;
                                //         cout << "Restaurant location: " << rest << endl;
                                //         cout << "User Location: " << to << endl;
                                //         cout << "Rider Location: " << from << endl;
                                //         cout << "Rider Name: " << name << endl;

                                //         cout << "" << endl;

                                //         initialize(getLocation(from));
                                //         dijkstra();
                                //         cout << " " << endl;
                                //         cout << "For rider to Restaurant" << endl;
                                //         cout << " " << endl;

                                //         displayRoute(getLocation(from), getLocation(rest));

                                //         initialize(getLocation(from));
                                //         dijkstra();
                                //         cout << " " << endl;
                                //         cout << "For Restaurant to User" << endl;

                                //         cout << " " << endl;

                                //         displayRoute(getLocation(rest), getLocation(to));
                                //         // visitedR[from]=false;
                                //         // riderinfo[from]=-1;
                                //         // visitedR[to]=true;
                                //         // riderinfo[to]=;

                                //     }
                            }

                        } while (op3 != 0);
                    }
                    else
                    {

                        cout << "ADMIN DOES NOT EXIST!! TRY AGAIN " << endl;
                    }
                }
                else if (op2 == 2)
                {
                    // user login
                    cout << " " << endl;

                    string input_name = "empty";
                    string input_username = "empty";
                    string input_email = "empty";
                    int input_password = -1;

                    // cout << "Enter Your Name" << endl;
                    // cin >> input_name;
                    // cout << " " << endl;
                    cout << "Enter Your UserName" << endl;
                    cin >> input_username;
                    // cout << " " << endl;
                    // cout << "Enter Your email" << endl;
                    // cin >> input_email;
                    // cout << " " << endl;
                    string prompt = "Enter Your password: ";
                    input_password = getIntegerFromUser(prompt, -1, 99999);

                    user tu(input_name, input_username, input_email, user_key, input_password);
                    //========================================================================================================================================================
                    if (users.check_user_existence(tu))
                    {
                        int rest = -1;
                        cout << "LOGIN SUCCESSFUL" << endl;

                        user_node *i = nullptr;
                        i = users.getNode(tu);

                        int op4 = -1;
                        do
                        {
                            // int *food;
                            // food = new int[5];

                            cout << " " << endl;
                            cout << "----------------- Welcome " << i->u.name << "! -----------------" << endl;
                            cout << " " << endl;
                            cout << " " << endl;
                            cout << "1. Select Restaurants" << endl;
                            cout << "2. View Your Selected Restaurants" << endl;
                            cout << "3. Place Order" << endl;
                            cout << "0. Go Back" << endl;
                            cout << " " << endl;
                            cout << "Option: ";
                            cin >> op4;
                            cout << "\n"
                                 << endl;

                            if (op4 == 1)
                            {
                                int foodop = -1;
                                int counter = 0;
                                cout << " " << endl;
                                cout << "NOTE: " << endl;
                                cout << " " << endl;
                                // cout << "You May Select A Maximum Of 5 Food Items at a Time!" << endl;
                                cout << "You May Press 0 at any Time To confirm the order!" << endl;
                                do
                                {
                                    cout << " " << endl;
                                    cout << "SELECT THE RESTAURANT YOU WANT TO ORDER FROM: " << endl;
                                    cout << " " << endl;
                                    cout << "1. Cheezious " << endl;
                                    cout << "2. Pizzahut  " << endl;
                                    cout << "3. Kfc " << endl;
                                    cout << "4. Hardeez " << endl;
                                    cout << "5. Macdonalds  " << endl;
                                    cout << "0. Confirm " << endl;

                                    cout << " " << endl;
                                    cout << "Option: " << endl;

                                    cin >> foodop;
                                    if (foodop == 1)
                                    {
                                        food[counter] = 1;
                                        restau[1] = true;
                                    }
                                    else if (foodop == 2)
                                    {
                                        food[counter] = 3;
                                        restau[3] = true;
                                    }
                                    else if (foodop == 3)
                                    {

                                        food[counter] = 5;
                                        restau[5] = true;
                                    }
                                    else if (foodop == 4)
                                    {

                                        food[counter] = 7;
                                        restau[7] = true;
                                    }
                                    else if (foodop == 5)
                                    {
                                        food[counter] = 9;
                                        restau[9] = true;
                                    }
                                    else if (foodop == 0)
                                    {
                                        break;
                                    }

                                    else
                                    {
                                        cout << "Incorrect option!!" << endl;
                                        counter--;
                                    }

                                    counter++;
                                } while (counter != 5);
                            }

                            else if (op4 == 2)
                            {

                                int k;
                                cout << " " << endl;
                                cout << "Your selected Restaurants are: " << endl;
                                cout << " " << endl;

                                for (int i = 0; i < 5; i++)
                                {
                                    k = food[i];
                                    // cout << k << endl;

                                    switch (k)
                                    {
                                    case 1 /* constant-expression */:
                                        cout << "Cheezious" << endl;
                                        break;
                                    case 3 /* constant-expression */:
                                        cout << "Pizza Hut" << endl;
                                        break;
                                    case 5 /* constant-expression */:
                                        cout << "KFC" << endl;
                                        break;
                                    case 7 /* constant-expression */:
                                        cout << "Hardeez" << endl;
                                        break;
                                    case 9 /* constant-expression */:
                                        cout << "Macdonalds" << endl;
                                        break;
                                    }
                                }
                            }

                            else if (op4 == 3)
                            {
                                // place order
                                string userLocation;
                                string restLocation;
                                int toinput = -1;
                                int a = 100;
                                int riderLocation;
                                int key;
                                cout << " " << endl;
                                cout << "Enter you current location (0-9): " << endl;
                                cout << " " << endl;
                                cout << "0. G-10/1" << endl;
                                cout << "1. G-10/2" << endl;
                                cout << "2. G-10/3" << endl;
                                cout << "3. G-10/4" << endl;
                                cout << "4. F-10/1" << endl;
                                cout << "5. F-10/2" << endl;
                                cout << "6. F-10/3" << endl;
                                cout << "7. F-10/4" << endl;
                                cout << "8. E-10/1" << endl;
                                cout << "9. E-10/2" << endl;
                                cout << "Option: " << endl;

                                cin >> toinput;
                                cout << " " << endl;
                                userLocation = getLocation(toinput);

                                if (food[0] == -1)
                                {
                                    cout << " " << endl;
                                    cout << "No Restaurant Selected" << endl;
                                    cout << " " << endl;
                                    break;
                                }
                                else
                                {
                                    initialize(getLocation(food[0]));
                                    dijkstra();
                                    for (int i = 0; i < V; i++)
                                    {
                                        if (dist[i] < a && visitedR[i] == true)
                                        {
                                            // nearest rider found from the restarunt
                                            riderLocation = i;
                                            a = dist[i];
                                        }
                                    }
                                }

                                order o(toinput, riderLocation, food[0], food);
                                o.setUser(i->u);
                                key = riderinfo[riderLocation];
                                cout << " " << endl;
                                cout << "Order Placed Sucessfully" << endl;

                                tempr = riders.getRiderFromId(key);
                                tempr->u.placeOrder(o);
                                cout << " " << endl;
                                cout << "The rider to deliver your order is : " << tempr->u.name << endl;
                                cout << " " << endl;
                                // cout << "Total price of your order is : " << o.calculatePrice() << endl;
                                // cout << " " << endl;

                                orders.enqueue(o);
                                tempr = nullptr;
                            }
                        } while (op4 != 0);
                    }
                    else
                    {
                        cout << "LOGIN UNSUCCESSFUL  PLEASE TRY AGAIN" << endl;
                    }
                }
                else if (op2 == 3)
                {

                    // rider login

                    string a_input_name = "empty";
                    int a_input_password = -1;
                    int a_input_rider_id = -1;

                    cout << "Enter Your Name" << endl;
                    cin >> a_input_name;

                    string prompt = "Enter Your password: ";
                    a_input_password = getIntegerFromUser(prompt, -1, 99999);

                    rider rt(7, 55, a_input_name, a_input_password, "55");
                    //===================================================================================================================================================
                    if (riders.check_user_existence(rt))
                    {
                        cout << " " << endl;
                        cout << "LOGIN SUCCESSFUL" << endl;
                        cout << " " << endl;

                        tempr = riders.getNode(rt);

                        int op3 = -1;
                        int i = 0;
                        int a = 100;
                        int si = -1;

                        do
                        {
                            cout << " " << endl;
                            cout << "----------------- Welcome " << tempr->u.name << " !! -----------------" << endl;
                            cout << " " << endl;
                            cout << "Please Select Your Option: " << endl;
                            cout << " " << endl;
                            cout << "1. View any orders to be delivered" << endl;
                            cout << "0. Go Back" << endl;
                            cout << " " << endl;
                            cout << "Option: ";
                            cin >> op3;
                            cout << "\n"
                                 << endl;

                            if (op3 == 1)
                            {

                                if (orders.isEmpty())
                                {
                                    cout << "No Current Orders available to be delivered! " << endl;
                                }
                                else
                                {
                                    order o(orders.dequeue());
                                    int Startingrest = o.rest;
                                    int userLocation = o.to;
                                    int riderLocation = o.from;
                                    int s = o.from;
                                    string name = o.client.name;

                                    cout << " " << endl;
                                    cout << "User Name: " << name << endl;
                                    cout << "User Location: " << getLocation(userLocation) << endl;
                                    cout << " " << endl;
                                    cout << "The rider to Restaurants: " << endl;
                                    cout << " " << endl;
                                    while ((o.food[i] != -1) && (i != 5))
                                    {
                                        cout << " " << endl;
                                        cout << "Current Rider Location: " << getLocation(riderLocation) << endl;
                                        cout << " " << endl;
                                        if (i == 0)
                                        {

                                            initialize(getLocation(riderLocation));
                                            dijkstra();
                                            cout << " " << endl;
                                            cout << "Next Restaurant the rider will move to is: " << getLocation(Startingrest) << endl;
                                            cout << " " << endl;

                                            displayRoute(getLocation(riderLocation), getLocation(Startingrest));
                                            riderLocation = Startingrest;
                                            Startingrest = food[i];
                                            restau[1] = false;
                                        }
                                        else
                                        {
                                            initialize(getLocation(riderLocation));
                                            dijkstra();

                                            for (int i = 0; i < V; i++)
                                            {
                                                if ((dist[i] < a) && (restau[i] == true) && (i == 3 || i == 5 || i == 7 || i == 9))
                                                {

                                                    // nearest restaurant found from the user
                                                    si = i;
                                                    a = dist[i];
                                                    Startingrest = i;
                                                }
                                            }
                                            cout << si << endl;

                                            restau[si] = false;
                                            cout << " " << endl;

                                            cout << "Next Restaurant the rider will move to is: " << getLocation(Startingrest) << endl;

                                            cout << " " << endl;

                                            displayRoute(getLocation(riderLocation), getLocation(Startingrest));
                                            riderLocation = Startingrest;
                                        }

                                        a = 100;
                                        i++;
                                    }
                                    cout << " " << endl;
                                    cout << "For Restaurant to User" << endl;
                                    cout << " " << endl;
                                    initialize(getLocation(riderLocation));

                                    dijkstra();

                                    displayRoute(getLocation(riderLocation), getLocation(userLocation));

                                    cout << "" << endl;
                                    cout << "Order Completed!" << endl;
                                    cout << "" << endl;
                                }
                            }

                            else if (op3 != 1 || op3 != 0)
                            {
                                cout << "Incorrect option" << endl;
                            }

                        } while (op3 == 0);
                    }
                    else
                    {

                        cout << "RIDER DOES NOT EXIST!! TRY AGAIN " << endl;
                    }
                }

                else if ((op2 != 0) || (op2 != 1) || (op2 != 2) || (op2 != 3))
                {
                    cout << "INCORRECT OPTION" << endl;
                }

            } while (op2 != 0);
        }
        else if ((op != 0) || (op != 1) || (op != 2))
        {
            cout << " " << endl;
            cout << "INCORRECT OPTION" << endl;
            cout << " " << endl;
        }

    } while (op != 0);
    cout << " " << endl;
    cout << "Program exitted successfully! " << endl;
    cout << " " << endl;

    return 0;
}