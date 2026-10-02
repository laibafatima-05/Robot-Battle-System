#include <iostream>
#include <string>
using namespace std;

// Parent Class
class Robot
{
protected:
    string name;
    string robotType;
    int health;
    int attack;
    int defense;
    int energy;

public:
    Robot(string n, string type, int h, int a, int d)
    {
        name = n;
        robotType = type;
        health = h;
        attack = a;
        defense = d;
        energy = 100;
    }
    string getRobotType()
    {
        return robotType;
    }
    virtual void specialAbility(Robot &enemy)
    {
        cout << name << " used a special ability!" << endl;
    }
    void normalAttack(Robot &enemy)
    {
        int damage = attack - enemy.defense;
        if (damage < 5)
        {
            damage = 5;
        }
        enemy.takeDamage(damage);

        cout << name << " attacked " << enemy.name << "!" << endl;
        cout << "Damage: " << damage << endl;
    }
    void takeDamage(int damage)
    {
        health = health - damage;
    }
    void recharge()
    {
        energy = energy + 20;

        if (energy > 100)
        {
            energy = 100;
        }
        cout << name << " recharged energy." << endl;
        cout << "Energy: " << energy << endl;
    }
    bool isAlive()
    {
        return health > 0;
    }
    void showStatus()
    {
        cout << name << " | Health: " << health
             << " | Energy: " << energy << endl;
    }
    string getName()
    {
        return name;
    }
};

// Attack Robot
class AttackRobot : public Robot
{
public:
    AttackRobot(string n) : Robot(n, "Attack Robot", 100, 35, 10)
    {
    }
    void specialAbility(Robot &enemy) override
    {
        if (energy >= 30)
        {
            int damage = 50;
            energy = energy - 30;
            enemy.takeDamage(damage);

            cout << name << " used POWER ATTACK!" << endl;
            cout << "Damage: " << damage << endl;
        }
        else
        {
            cout << "Not enough energy!" << endl;
        }
    }
};

// Defense Robot
class DefenseRobot : public Robot
{
public:
    DefenseRobot(string n) : Robot(n, "Defence Robot", 130, 25, 25)
    {
    }
    void specialAbility(Robot &enemy) override
    {
        if (energy >= 30)
        {
            int damage = 30;
            energy = energy - 30;

            enemy.takeDamage(damage);

            cout << name << " used SHIELD ATTACK!" << endl;
            cout << "Damage: " << damage << endl;
        }
        else
        {
            cout << "Not enough energy!" << endl;
        }
    }
};
// Speed Robot
class SpeedRobot : public Robot
{
public:
    SpeedRobot(string n) : Robot(n, "Speed Robot", 90, 30, 15)
    {
    }
    void specialAbility(Robot &enemy) override
    {
        if (energy >= 30)
        {
            int damage = 40;
            energy = energy - 30;

            enemy.takeDamage(damage);

            cout << name << " used QUICK ATTACK!" << endl;
            cout << "Damage: " << damage << endl;
        }
        else
        {
            cout << "Not enough energy!" << endl;
        }
    }
};
int main()
{
    string playerName;
    int choice;

    cout << " ROBOT BATTLE ARENA" << endl;

    cout << "Enter your name: ";
    cin >> playerName;

    cout << endl;
    cout << "Choose your Robot:" << endl;
    cout << "1. Attack Robot" << endl;
    cout << "2. Defense Robot" << endl;
    cout << "3. Speed Robot" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    Robot *player;

    if (choice == 1)
    {
        player = new AttackRobot(playerName);
    }
    else if (choice == 2)
    {
        player = new DefenseRobot(playerName);
    }
    else
    {
        player = new SpeedRobot(playerName);
    }

    // Enemy Robot
    Robot *enemy = new DefenseRobot("Enemy");

    cout << endl;
    cout << "Your Robot: " << player->getRobotType() << endl;
    cout << "Enemy Robot: " << enemy->getRobotType() << endl;

    cout << endl;
    cout << " BATTLE START " << endl;

    while (player->isAlive() && enemy->isAlive())
    {
        cout << endl;

        player->showStatus();
        enemy->showStatus();

        cout << endl;
        cout << "Choose your action:" << endl;
        cout << "1. Normal Attack" << endl;
        cout << "2. Special Ability" << endl;
        cout << "3. Recharge Energy" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        cout << endl;

        if (choice == 1)
        {
            player->normalAttack(*enemy);
        }
        else if (choice == 2)
        {
            player->specialAbility(*enemy);
        }
        else if (choice == 3)
        {
            player->recharge();
        }
        else
        {
            cout << "Invalid choice!" << endl;
            continue;
        }

        // Enemy's turn
        if (enemy->isAlive())
        {
            cout << endl;
            cout << "Enemy's turn..." << endl;

            enemy->normalAttack(*player);
        }
    }
    cout << endl;
    cout << " GAME OVER " << endl;
    if (player->isAlive())
    {
        cout << "Congratulations " << playerName << "!" << endl;
        cout << "You won the battle!" << endl;
    }
    else
    {
        cout << "Enemy won the battle!" << endl;
    }
    delete player;
    delete enemy;

    return 0;
}