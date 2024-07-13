#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1900, 800), "Tower Of Hanoi");
bool done = false;


int disks = 10;

int rectangleWidth = window.getSize().x / 3;
int rectangleHeight = window.getSize().y / disks;

void printRodState(const vector<int>& A, const vector<int>& B, const vector<int>& C) {
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) window.close();
    }

    cout << "Rod A: ";
    window.clear();
    for (int i = 1; i <= A.size(); i++)
    {
        int width = (rectangleWidth - (disks - A[i - 1] + 1) * 30) - 10;
        int spaces = (rectangleWidth - width) / 2;
        RectangleShape rectangle;
        rectangle.setSize(Vector2f(width, rectangleHeight));
        rectangle.setPosition(Vector2f(spaces, window.getSize().y - i * rectangleHeight));
        window.draw(rectangle);
        cout << A[i - 1] << " ";
    }
    
    cout << "\nRod B: ";
    for (int i = 1; i <= B.size(); i++)
    {
        int width = (rectangleWidth - (disks - B[i - 1] + 1) * 30) - 10;
        int spaces = (rectangleWidth - width) / 2;
        RectangleShape rectangle;
        rectangle.setSize(Vector2f(width, rectangleHeight));
        rectangle.setPosition(Vector2f(rectangleWidth + spaces, window.getSize().y - i * rectangleHeight));
        window.draw(rectangle);
        cout << B[i - 1] << " ";
    }
    cout << "\nRod C: ";
    for (int i = 1; i <= C.size(); i++)
    {
        int width = (rectangleWidth - (disks - C[i - 1] + 1) * 30) - 10;
        int spaces = (rectangleWidth - width) / 2;
        RectangleShape rectangle;
        rectangle.setSize(Vector2f(width, rectangleHeight));
        rectangle.setPosition(Vector2f(2*rectangleWidth + spaces, window.getSize().y - i * rectangleHeight));
        window.draw(rectangle);
        cout << C[i - 1] << " ";
    }
    window.display();
    if (C.size() == disks) done = true;
    cout << "\n\n";
}

void moveDisk(vector<int>& from, vector<int>& to) {
    int disk = from.back();
    from.pop_back();
    to.push_back(disk);
}

void towerOfHanoi(int n, vector<int>& A, vector<int>& B, vector<int>& C, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        cout << "Move disk 1 from rod " << from_rod << " to rod " << to_rod << endl;
        if (from_rod == 'A' && to_rod == 'C') moveDisk(A, C);
        else if (from_rod == 'A' && to_rod == 'B') moveDisk(A, B);
        else if (from_rod == 'B' && to_rod == 'A') moveDisk(B, A);
        else if (from_rod == 'B' && to_rod == 'C') moveDisk(B, C);
        else if (from_rod == 'C' && to_rod == 'A') moveDisk(C, A);
        else if (from_rod == 'C' && to_rod == 'B') moveDisk(C, B);
        printRodState(A, B, C);
        return;
    }
    towerOfHanoi(n - 1, A, B, C, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << endl;
    if (from_rod == 'A' && to_rod == 'C') moveDisk(A, C);
    else if (from_rod == 'A' && to_rod == 'B') moveDisk(A, B);
    else if (from_rod == 'B' && to_rod == 'A') moveDisk(B, A);
    else if (from_rod == 'B' && to_rod == 'C') moveDisk(B, C);
    else if (from_rod == 'C' && to_rod == 'A') moveDisk(C, A);
    else if (from_rod == 'C' && to_rod == 'B') moveDisk(C, B);
    printRodState(A, B, C);
    if (!done)
    towerOfHanoi(n - 1, A, B, C, aux_rod, to_rod, from_rod);
}

int main() {
    window.setFramerateLimit(30);
   
    vector<int> A, B, C;

    // Initialize rod A with disks of different sizes
    for (int i = disks; i >= 1; i--) {
        A.push_back(i);
    }

    cout << "Initial state:\n";
    printRodState(A, B, C);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            window.clear();
            if (!done) towerOfHanoi(disks, A, B, C, 'A', 'C', 'B');
            printRodState(A, B, C);
            window.display();
        }
    }
    return 0;
}
